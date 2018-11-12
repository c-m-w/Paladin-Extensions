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
			&& FindPointers( )
			&& FindNetworkedVariables( )
			&& Other::RetrievePaintKits( );
	}

	namespace Memory
	{
		bool PX_API Setup( )
		{		
#ifdef _DEBUG
			wstr_t wstrBuffer;
			Files::FileRead( Files::GetPXDirectory( ) + LR"(PX Website\PX CSGO.px)", wstrBuffer, false, false );
			jsMemoryInformation = nlohmann::json::parse( Tools::string_cast< Types::str_t >( wstrBuffer ) );
#else
			jsMemoryInformation = nlohmann::json::parse( Cryptography::Decrypt( Net::RequestExtension( PX_EXTENSION_CSGO, true ) ) );
#endif
			return true;
		}
	}

	namespace Modules
	{
		bool SModule::Setup( wstr_t wstrModule )
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
				if ( Tools::GetMoment( ) - mmtStart >= mmtMaxWaitTime )
					return false;
			} while ( !mEngine.Setup( Tools::string_cast< wstr_t >( jsMemoryInformation[ PX_XOR( "Modules" ) ][ PX_XOR( "Engine" ) ].get< Types::str_t >( ) ) )
					  || !mClient.Setup( Tools::string_cast< wstr_t >( jsMemoryInformation[ PX_XOR( "Modules" ) ][ PX_XOR( "Client" ) ].get< Types::str_t >( ) ) )
					  || !mDirectX.Setup( Tools::string_cast< wstr_t >( jsMemoryInformation[ PX_XOR( "Modules" ) ][ PX_XOR( "DirectX API" ) ].get< Types::str_t >( ) ) )
					  || !mOverlay.Setup( Tools::string_cast< wstr_t >( jsMemoryInformation[ PX_XOR( "Modules" ) ][ PX_XOR( "Overlay" ) ].get< Types::str_t >( ) ) )
					  || !mVGUI.Setup( Tools::string_cast< wstr_t >( jsMemoryInformation[ PX_XOR( "Modules" ) ][ PX_XOR( "VGUI" ) ].get< Types::str_t >( ) ) )
					  || !mVGUI2.Setup( Tools::string_cast< wstr_t >( jsMemoryInformation[ PX_XOR( "Modules" ) ][ PX_XOR( "VGUI2" ) ].get< Types::str_t >( ) ) )
					  || !mInput.Setup( Tools::string_cast< wstr_t >( jsMemoryInformation[ PX_XOR( "Modules" ) ][ PX_XOR( "Input" ) ].get< Types::str_t >( ) ) )
					  || !mMaterialSystem.Setup( Tools::string_cast< wstr_t >( jsMemoryInformation[ PX_XOR( "Modules" ) ][ PX_XOR( "Material System" ) ].get< Types::str_t >( ) ) ) 
					  || !mValveStandardLibrary.Setup( Tools::string_cast< wstr_t >( jsMemoryInformation[ PX_XOR( "Modules" ) ][ PX_XOR( "Valve Standard Library" ) ].get< Types::str_t >( ) ) )
					  || !mLocalize .Setup( Tools::string_cast< wstr_t >( jsMemoryInformation[ PX_XOR( "Modules" ) ][ PX_XOR( "Localize" ) ].get< Types::str_t >( ) ) ) );
			return true;
		}
	}

	namespace Pointers
	{
		bool PX_API FindPointers( )
		{
			pSendPackets = reinterpret_cast< bool* >( Modules::mEngine.FindPattern( jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Signatures" ) ][ PX_XOR( "Send Packets" ) ].get< str_t >( ) )
													  + jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Offsets" ) ][ PX_XOR( "Send Packets" ) ].get< int >( ) );
			pGlobalVariables = **reinterpret_cast< CGlobalVarsBase*** >( Modules::mClient.FindPattern( jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Signatures" ) ][ PX_XOR( "Global Variables" ) ].get< str_t >( ) )
																		 + jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Offsets" ) ][ PX_XOR( "Global Variables" ) ].get< int >( ) );
			pClientState = **reinterpret_cast< CClientState*** >( Modules::mEngine.FindPattern( jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Signatures" ) ][ PX_XOR( "Client State" ) ].get< str_t >( ) )
																  + jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Offsets" ) ][ PX_XOR( "Client State" ) ].get< int >( ) );
			// Interfaces
			pDevice = **reinterpret_cast< IDirect3DDevice9*** >( Modules::mDirectX.FindPattern( jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Signatures" ) ][ PX_XOR( "Device" ) ].get< str_t >( ) )
																 + jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Offsets" ) ][ PX_XOR( "Device" ) ].get< int >( ) );
			pClientMode = *reinterpret_cast< IClientMode** >( Modules::mClient.FindPattern( jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Signatures" ) ][ PX_XOR( "Client Mode" ) ].get< str_t >( ) )
																			   + jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Offsets" ) ][ PX_XOR( "Client Mode" ) ].get< int >( ) );
			pGlowObjectManager = *reinterpret_cast< CGlowObjectManager** >( Modules::mClient.FindPattern( jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Signatures" ) ][ PX_XOR( "Glow Object Manager" ) ].get< str_t >( ) )
															  + jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Offsets" ) ][ PX_XOR( "Glow Object Manager" ) ].get< int >( ) );
			pInput = *reinterpret_cast< CInput** >( Modules::mClient.FindPattern( jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Signatures" ) ][ PX_XOR( "Input" ) ].get< str_t >( ) )
																+ jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Offsets" ) ][ PX_XOR( "Input" ) ].get< int >( ) );
			//pEngineRenderView = *reinterpret_cast< IViewRender** >( Modules::mClient.FindPattern( jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Signatures" ) ][ PX_XOR( "View Render" ) ].get< str_t >( ) )
			//										+ jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Offsets" ) ][ PX_XOR( "View Render" ) ].get< int >( ) );

			pClientBase = reinterpret_cast< IBaseClientDLL* >( Modules::mClient.ciFactory( 
				jsMemoryInformation[ PX_XOR( "Versions" ) ][ PX_XOR( "Client Base" ) ].get< str_t >( ).c_str( ), nullptr ) );
			pEngineClient = reinterpret_cast< IVEngineClient* >( Modules::mEngine.ciFactory(
				jsMemoryInformation[ PX_XOR( "Versions" ) ][ PX_XOR( "Engine Client" ) ].get< str_t >( ).c_str( ), nullptr ) );
			pSurface = reinterpret_cast< ISurface* >( Modules::mVGUI.ciFactory(
				jsMemoryInformation[ PX_XOR( "Versions" ) ][ PX_XOR( "VGUI Surface" ) ].get< str_t >( ).c_str( ), nullptr ) );
			pPanel = reinterpret_cast< IPanel* >( Modules::mVGUI2.ciFactory(
				jsMemoryInformation[ PX_XOR( "Versions" ) ][ PX_XOR( "VGUI Panel" ) ].get< str_t >( ).c_str( ), nullptr ) );
			pEntityList = reinterpret_cast< IClientEntityList* >( Modules::mClient.ciFactory(
				jsMemoryInformation[ PX_XOR( "Versions" ) ][ PX_XOR( "Entity List" ) ].get< str_t >( ).c_str( ), nullptr ) );
			pEngineTrace = reinterpret_cast< IEngineTrace* >( Modules::mEngine.ciFactory(
				jsMemoryInformation[ PX_XOR( "Versions" ) ][ PX_XOR( "Engine Trace" ) ].get< str_t >( ).c_str( ), nullptr ) );
			pModelInfo = reinterpret_cast< IVModelInfoClient* >( Modules::mEngine.ciFactory(
				jsMemoryInformation[ PX_XOR( "Versions" ) ][ PX_XOR( "Model Info" ) ].get< str_t >( ).c_str( ), nullptr ) );
			pInputSystem = reinterpret_cast< IInputSystem* >( Modules::mInput.ciFactory(
				jsMemoryInformation[ PX_XOR( "Versions" ) ][ PX_XOR( "Input" ) ].get< str_t >( ).c_str( ), nullptr ) );
			pModelRender = reinterpret_cast< IVModelRender* >( Modules::mEngine.ciFactory(
				jsMemoryInformation[ PX_XOR( "Versions" ) ][ PX_XOR( "Model Render" ) ].get< str_t >( ).c_str( ), nullptr ) );
			pMaterialSystem = reinterpret_cast< IMaterialSystem* >( Modules::mMaterialSystem.ciFactory(
				jsMemoryInformation[ PX_XOR( "Versions" ) ][ PX_XOR( "Material System" ) ].get< str_t >( ).c_str( ), nullptr ) );
			pEngineRenderView = reinterpret_cast< IVRenderView* >( Modules::mEngine.ciFactory(
				jsMemoryInformation[ PX_XOR( "Versions" ) ][ PX_XOR( "Engine Render View" ) ].get< str_t >( ).c_str( ), nullptr ) );
			pConVar = reinterpret_cast< ICvar* >( Modules::mValveStandardLibrary.ciFactory(
				jsMemoryInformation[ PX_XOR( "Versions" ) ][ PX_XOR( "CVar" ) ].get< str_t >( ).c_str( ), nullptr ) );
			pLocalize = reinterpret_cast< ILocalize* >( Modules::mLocalize.ciFactory(
				jsMemoryInformation[ PX_XOR( "Versions" ) ][ PX_XOR( "Localize" ) ].get< str_t >( ).c_str( ), nullptr ) );

			return nullptr != pSendPackets
				&& nullptr != pGlobalVariables
				&& nullptr != pDevice
				&& nullptr != pClientMode
				&& nullptr != pGlowObjectManager
				&& nullptr != pInput
				&& nullptr != pClientState
				&& nullptr != pClientBase
				&& nullptr != pEngineClient
				&& nullptr != pSurface
				&& nullptr != pPanel
				&& nullptr != pEntityList
				&& nullptr != pEngineTrace
				&& nullptr != pModelInfo
				&& nullptr != pInputSystem
				&& nullptr != pModelRender
				&& nullptr != pMaterialSystem
				&& nullptr != pEngineRenderView
				&& nullptr != pConVar
				&& nullptr != pLocalize;
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

	namespace Other
	{
		bool PX_API RetrievePaintKits( )
		{
			const auto ptrAddress = ptr_t( Modules::mClient.FindPattern( jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Signatures" ) ][ PX_XOR( "Paint Kits" ) ].get< str_t >( ) )
				+ jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Offsets" ) ][ PX_XOR( "Paint Kits" ) ].get< int >( ) );
			const auto ptrItemSystemOffset = *reinterpret_cast< ptr_t* >( ptrAddress + 0x1 );
			const auto pItemSystem = reinterpret_cast< CCStrike15ItemSystem*( *)( ) >( ptrAddress + 0x5 + ptrItemSystemOffset );
			const auto ptrGetPaintKitDefinitionOffset = *reinterpret_cast< ptr_t* >( ptrAddress + 0xC );
			const auto fnGetPaintKitDefinition = reinterpret_cast< CPaintKit*( __thiscall* )( int ) >( ptrAddress + 0x10 + ptrGetPaintKitDefinitionOffset );
			const auto ptrStartElementOffset = *reinterpret_cast< ptr_t* >( ptr_t( fnGetPaintKitDefinition ) + 0xA );
			const auto ptrHeadOffset = ptrStartElementOffset - 0xC;
			const auto pItemSchema = reinterpret_cast< CCStrike15ItemSchema* >( ptr_t( pItemSystem( ) ) + 0x4 );
			const auto pHead = reinterpret_cast< Head_t* >( ptr_t( pItemSchema ) + ptrHeadOffset );

			std::map< int, std::string > mpCustomNames
			{
				{ 42, "Dragon King" }
			};

			std::map< int, paint_kit_t::info_t > mpInfo
			{
				{ 42, { 2, QUALITY_DEFAULT } }
			};

			for( auto i = 1; i < pHead->nLastElement; i++ )
			{
				const auto pPaintKit = pHead->pMemory[ i ].pPaintKit;

				if ( pPaintKit->iIndex == 9001 )
					continue;

				const auto pSearch = mpCustomNames.find( pPaintKit->iIndex );
				const auto strBuffer = pSearch == mpCustomNames.end( )
					? Tools::string_cast< std::string >( pLocalize->Find( pPaintKit->Tag.szBuffer + 0x1 ) )
					: pSearch->second;
				const auto pSearch2 = mpInfo.find( pPaintKit->iIndex );
				if ( pSearch2 == mpInfo.end( ) )
					throw std::exception( "jeremy you fucked up" );

				vecPaintKits.emplace_back( paint_kit_t( pPaintKit->iIndex, strBuffer, pSearch2->second ) );
			}

			return !vecPaintKits.empty( );
		}

		std::vector< paint_kit_t > PX_API FindPaintKit( int iIndex )
		{
			std::vector< paint_kit_t > vecReturn;
			for ( const auto& paintkit : vecPaintKits )
				if ( paintkit.iIdentifier == iIndex )
					vecReturn.emplace_back( paintkit );
			return vecReturn;
		}

		std::vector< paint_kit_t > PX_API FindPaintKit( wcstr_t wszName )
		{
			return FindPaintKit( Tools::string_cast< str_t >( std::wstring( wszName ) ).c_str( ) );
		}

		std::vector< paint_kit_t > PX_API FindPaintKit( cstr_t szName )
		{
			std::vector< paint_kit_t > vecReturn;
			for ( const auto& paintkit : vecPaintKits )
				if ( paintkit.strName == szName )
					vecReturn.emplace_back( paintkit );
			return vecReturn;
		}

		std::vector< std::pair< paint_kit_t, int > > PX_API FindWeaponPaintKits( short sDefinitionIndex )
		{
			const auto pSearch = mpWeaponSkins.find( sDefinitionIndex );
			if ( pSearch == mpWeaponSkins.end( ) )
				return { };
			return pSearch->second;
		}
	}
}
