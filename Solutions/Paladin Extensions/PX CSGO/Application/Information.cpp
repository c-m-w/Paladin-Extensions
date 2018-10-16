/// Interfaces.cpp

#include "PX Precompiled.hpp"
#include "../PX CSGO.hpp"

namespace PX::Information
{
	nlohmann::json jsMemoryInformation;

	bool PX_API InitializeInformation( )
	{
		return Memory::Setup( )
			&& Modules::Setup( )
			&& Pointers::FindPointers( )
			&& FindNetworkedVariables( );
	}

	namespace Memory
	{
		bool PX_API Setup( )
		{		
#ifdef _DEBUG
			std::wstring wstrBuffer;
			Files::FileRead( Files::GetPXDirectory( ) + LR"(PX Website\PX CSGO.px)", wstrBuffer, false, false );
			jsMemoryInformation = nlohmann::json::parse( Tools::string_cast< std::string >( wstrBuffer ) );
#else
			jsMemoryInformation = nlohmann::json::parse( Cryptography::Decrypt( Net::RequestExtension( PX_EXTENSION_CSGO, true ) ) );
#endif
			return true;
		}
	}

	namespace Modules
	{
		bool SModule::Setup( std::wstring wstrModule )
		{
			wstrName = wstrModule;
			hModule = GetModuleHandle( wstrName.c_str( ) );
			if ( hModule )
			{
				ciFactory = reinterpret_cast< CreateInterfaceFn >( GetProcAddress( hModule, strCreateInterfaceName.c_str( ) ) );
				return true;
			}
			return false;
		}

		bool PX_API Setup( )
		{
			constexpr auto mmtMaxWaitTime = 7500000ull;
			const auto mmtStart = Tools::GetMoment( );
			do
			{
				if( Tools::GetMoment( ) - mmtStart >= mmtMaxWaitTime )
					return false;
			}
			while( !mEngine.Setup( Tools::string_cast< std::wstring >( jsMemoryInformation[ PX_XOR( "Modules" ) ][ PX_XOR( "Engine" ) ].get< std::string >( ) ) )
				|| !mClient.Setup( Tools::string_cast< std::wstring >( jsMemoryInformation[ PX_XOR( "Modules" ) ][ PX_XOR( "Client" ) ].get< std::string >( ) ) )
				|| !mDirectX.Setup( Tools::string_cast< std::wstring >( jsMemoryInformation[ PX_XOR( "Modules" ) ][ PX_XOR( "DirectX API" ) ].get< std::string >( ) ) )
				|| !mOverlay.Setup( Tools::string_cast< std::wstring >( jsMemoryInformation[ PX_XOR( "Modules" ) ][ PX_XOR( "Overlay" ) ].get< std::string >( ) ) )
				|| !mVGUI.Setup( Tools::string_cast< std::wstring >( jsMemoryInformation[ PX_XOR( "Modules" ) ][ PX_XOR( "VGUI" ) ].get< std::string >( ) ) )
				|| !mVGUI2.Setup( Tools::string_cast< std::wstring >( jsMemoryInformation[ PX_XOR( "Modules" ) ][ PX_XOR( "VGUI2" ) ].get< std::string >( ) ) )
				|| !mInput.Setup( Tools::string_cast< std::wstring >( jsMemoryInformation[ PX_XOR( "Modules" ) ][ PX_XOR( "Input" ) ].get< std::string >( ) ) ) );
			return true;
		}
	}

	namespace Pointers
	{
		bool PX_API FindPointers( )
		{
			pSendPackets = reinterpret_cast< bool* >( Modules::mEngine.FindPattern( jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Signatures" ) ][ PX_XOR( "Send Packets" ) ].get< std::string >( ) )
													  + jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Offsets" ) ][ PX_XOR( "Send Packets" ) ].get< int >( ) );
			pGlobalVariables = **reinterpret_cast< CGlobalVarsBase*** >( Modules::mClient.FindPattern( jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Signatures" ) ][ PX_XOR( "Global Variables" ) ].get< std::string >( ) )
																		 + jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Offsets" ) ][ PX_XOR( "Global Variables" ) ].get< int >( ) );
			pClientState = **reinterpret_cast< CClientState*** >( Modules::mEngine.FindPattern( jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Signatures" ) ][ PX_XOR( "Client State" ) ].get< std::string >( ) )
																  + jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Offsets" ) ][ PX_XOR( "Client State" ) ].get< int >( ) );
			// Interfaces
			pDevice = **reinterpret_cast< IDirect3DDevice9*** >( Modules::mDirectX.FindPattern( jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Signatures" ) ][ PX_XOR( "Device" ) ].get< std::string >( ) )
																 + jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Offsets" ) ][ PX_XOR( "Device" ) ].get< int >( ) );
			pClientMode = *reinterpret_cast< IClientMode** >( Modules::mClient.FindPattern( jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Signatures" ) ][ PX_XOR( "Client Mode" ) ].get< std::string >( ) )
																			   + jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Offsets" ) ][ PX_XOR( "Client Mode" ) ].get< int >( ) );
			pGlowObjectManager = *reinterpret_cast< CGlowObjectManager** >( Modules::mClient.FindPattern( jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Signatures" ) ][ PX_XOR( "Glow Object Manager" ) ].get< std::string >( ) )
															  + jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Offsets" ) ][ PX_XOR( "Glow Object Manager" ) ].get< int >( ) );

			pClientBase = reinterpret_cast< IBaseClientDLL* >( Modules::mClient.ciFactory( 
				jsMemoryInformation[ PX_XOR( "Versions" ) ][ PX_XOR( "Client Base" ) ].get< std::string >( ).c_str( ), nullptr ) );
			pEngineClient = reinterpret_cast< IVEngineClient* >( Modules::mEngine.ciFactory(
				jsMemoryInformation[ PX_XOR( "Versions" ) ][ PX_XOR( "Engine Client" ) ].get< std::string >( ).c_str( ), nullptr ) );
			pSurface = reinterpret_cast< ISurface* >( Modules::mVGUI.ciFactory(
				jsMemoryInformation[ PX_XOR( "Versions" ) ][ PX_XOR( "VGUI Surface" ) ].get< std::string >( ).c_str( ), nullptr ) );
			pPanel = reinterpret_cast< IPanel* >( Modules::mVGUI2.ciFactory(
				jsMemoryInformation[ PX_XOR( "Versions" ) ][ PX_XOR( "VGUI Panel" ) ].get< std::string >( ).c_str( ), nullptr ) );
			pEntityList = reinterpret_cast< IClientEntityList* >( Modules::mClient.ciFactory(
				jsMemoryInformation[ PX_XOR( "Versions" ) ][ PX_XOR( "Entity List" ) ].get< std::string >( ).c_str( ), nullptr ) );
			pEngineTrace = reinterpret_cast< IEngineTrace* >( Modules::mEngine.ciFactory(
				jsMemoryInformation[ PX_XOR( "Versions" ) ][ PX_XOR( "Engine Trace" ) ].get< std::string >( ).c_str( ), nullptr ) );
			pModelInfo = reinterpret_cast< IVModelInfoClient* >( Modules::mEngine.ciFactory(
				jsMemoryInformation[ PX_XOR( "Versions" ) ][ PX_XOR( "Model Info" ) ].get< std::string >( ).c_str( ), nullptr ) );
			pInputSystem = reinterpret_cast< IInputSystem* >( Modules::mInput.ciFactory(
				jsMemoryInformation[ PX_XOR( "Versions" ) ][ PX_XOR( "Input" ) ].get< std::string >( ).c_str( ), nullptr ) );

			return nullptr != pSendPackets
				&& nullptr != pGlobalVariables
				&& nullptr != pDevice
				&& nullptr != pClientMode
				&& nullptr != pGlowObjectManager
				&& nullptr != pClientState
				&& nullptr != pClientBase
				&& nullptr != pEngineClient
				&& nullptr != pSurface
				&& nullptr != pPanel
				&& nullptr != pEntityList
				&& nullptr != pEngineTrace
				&& nullptr != pModelInfo
				&& nullptr != pInputSystem;
		}
	}

	namespace NetworkedVariableManager
	{
		networked_variable_table_t PX_API ParseTable( RecvTable* pTable )
		{
			networked_variable_table_t nvtCurrent( pTable->m_pNetTableName );

			for ( auto i = 0; i < pTable->m_nProps; i++ )
			{
				const auto pProp = &pTable->m_pProps[ i ];
				if ( nullptr == pProp
					 || std::isdigit( pProp->m_pVarName[ 0 ] )
					 || !strcmp( pProp->m_pVarName, PX_XOR( "baseclass" ) ) )
					continue;
				if ( pProp->m_RecvType == DPT_DataTable && pProp->m_pDataTable != nullptr )
				{
					nvtCurrent.vecChildTables.emplace_back( ParseTable( pProp->m_pDataTable ) );
					nvtCurrent.vecChildTables.back( ).ptrOffset = pProp->m_Offset;
					nvtCurrent.vecChildTables.back( ).pProp = pProp;
				}
				else
					nvtCurrent.vecChildProps.emplace_back( pProp );
			}

			return nvtCurrent;
		}

		bool PX_API FindNetworkedVariables( )
		{
			for ( auto pClass = Pointers::pClientBase->GetAllClasses( ); nullptr != pClass; pClass = pClass->m_pNext )
				if ( pClass->m_pRecvTable )
					vecNetworkedVariables.push_back( ParseTable( pClass->m_pRecvTable ) );
			return !vecNetworkedVariables.empty( );
		}

		ptr_t PX_API FindOffset( networked_variable_table_t& nvtTable, cstr_t szVariable )
		{
			for each ( auto& pProp in nvtTable.vecChildProps )
				if ( !strcmp( pProp->m_pVarName, szVariable ) )
					return nvtTable.ptrOffset + pProp->m_Offset;

			for each ( networked_variable_table_t pChild in nvtTable.vecChildTables )
			{
				auto ptrPropOffset = FindOffset( pChild, szVariable );
				if( ptrPropOffset != 0 )
					return nvtTable.ptrOffset + ptrPropOffset;
			}

			for each ( auto& pChild in nvtTable.vecChildTables )
				if ( !strcmp( pChild.pProp->m_pVarName, szVariable ) )
					return nvtTable.ptrOffset + pChild.ptrOffset;

			return 0u;
		}

		ptr_t PX_API FindOffset( cstr_t szTable, cstr_t szVariable )
		{
			for each( auto pTable in vecNetworkedVariables )
				if( !strcmp( pTable.szName, szTable ) )
				{
					const auto ptrResult = FindOffset( pTable, szVariable );
					if ( 0u != ptrResult )
						return ptrResult;
				}
			return 0u;
		}
	}
}
