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
		std::map< Types::cstr_t /* short name */, short /* item def index */ > mpItemDefinitionIndicies
		{
			{ "Flashbang", ITEM_WEAPON_FLASHBANG },
			{ "HE Grenade", ITEM_WEAPON_HEGRENADE },
			{ "CT Knife", ITEM_WEAPON_CTKNIFE },
			{ "T Knife", ITEM_WEAPON_TKNIFE },
			{ "Bayonet", ITEM_WEAPON_KNIFE_BAYONET },
			{ "Flip", ITEM_WEAPON_KNIFE_FLIP },
			{ "Gut", ITEM_WEAPON_KNIFE_GUT },
			{ "Karambit", ITEM_WEAPON_KNIFE_KARAMBIT },
			{ "M9 Bayonet", ITEM_WEAPON_KNIFE_M9_BAYONET },
			{ "Huntsman", ITEM_WEAPON_KNIFE_TACTICAL },
			{ "Falchion", ITEM_WEAPON_KNIFE_FALCHION },
			{ "Bowie", ITEM_WEAPON_KNIFE_SURVIVAL_BOWIE },
			{ "Butterfly", ITEM_WEAPON_KNIFE_BUTTERFLY },
			{ "Shadow Daggers", ITEM_WEAPON_KNIFE_SHADOW_DAGGERS },
			{ "Ursus", ITEM_WEAPON_KNIFE_URSUS },
			{ "Navaja", ITEM_WEAPON_KNIFE_NAVAJA },
			{ "Stilletto", ITEM_WEAPON_KNIFE_STILLETTO },
			{ "Talon", ITEM_WEAPON_KNIFE_TALON },
			{ "Bloodhound", ITEM_GLOVE_BLOODHOUND },
			{ "Sport", ITEM_GLOVE_SPORTY },
			{ "Driver", ITEM_GLOVE_DRIVER },
			{ "Hand Wrap", ITEM_GLOVE_HAND_WRAP },
			{ "Moto", ITEM_GLOVE_MOTORCYCLE },
			{ "Specialist", ITEM_GLOVE_SPECIALIST },
			{ "Hydra", ITEM_GLOVE_HYDRA }
		};

		std::map< short /* item def index */, int /* applicable kits */ > mpModelIndicies;

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

			// todo xor
			std::map< int, std::string > mpCustomNames
			{
				{ 415, ( "Doppler [Ruby]" ) },
				{ 416, ( "Doppler [Sapphire]" ) },
				{ 417, ( "Doppler [Black Pearl]" ) },
				{ 418, ( "Doppler [Phase 1]" ) },
				{ 419, ( "Doppler [Phase 2]" ) },
				{ 420, ( "Doppler [Phase 3]" ) },
				{ 421, ( "Doppler [Phase 4]" ) },

				{ 172, ( "Black Laminate [AK]" ) },
				{ 563, ( "Black Laminate [Bayonet]" ) },
				{ 564, ( "Black Laminate [Flip]" ) },
				{ 565, ( "Black Laminate [Gut]" ) },
				{ 566, ( "Black Laminate [Karambit]" ) },
				{ 567, ( "Black Laminate [M9]" ) },

				{ 558, ( "Lore [Bayonet]" ) },
				{ 559, ( "Lore [Flip]" ) },
				{ 560, ( "Lore [Gut]" ) },
				{ 561, ( "Lore [Karambit]" ) },
				{ 562, ( "Lore [M9]" ) },

				{ 568, ( "Gamma Doppler [Emerald]" ) },
				{ 569, ( "Gamma Doppler [Phase 1]" ) },
				{ 570, ( "Gamma Doppler [Phase 2]" ) },
				{ 571, ( "Gamma Doppler [Phase 3]" ) },
				{ 572, ( "Gamma Doppler [Phase 4]" ) },

				{ 573, ( "Autotronic [Bayonet]" ) },
				{ 574, ( "Autotronic [Flip]" ) },
				{ 575, ( "Autotronic [Gut]" ) },
				{ 576, ( "Autotronic [Karambit]" ) },
				{ 577, ( "Autotronic [M9]" ) },

				{ 38, ( "Fade [Glock/Knife]" ) },
				{ 522, ( "Fade [R8]" ) },
				{ 752, ( "Fade [MP7]" ) },
				{ 10063, ( "Fade [Glove]" ) },

				{ 203, ( "Rust Coat [Bizon]" ) },
				{ 323, ( "Rust Coat [Sawed-Off]" ) },
				{ 414, ( "Rust Coat [Knife]" ) },
				{ 754, ( "Rust Coat [MAG-7]" ) },

				{ 255, ( "Asiimov [M4A4]" ) },
				{ 279, ( "Asiimov [AWP]" ) },
				{ 359, ( "Asiimov [P90]" ) },
				{ 551, ( "Asiimov [P250]" ) },

				{ 312, ( "Cyrex [SCAR]" ) },
				{ 360, ( "Cyrex [M4A1]" ) },
				{ 487, ( "Cyrex [SG]" ) },
				{ 637, ( "Cyrex [USP]" ) },

				{ 430, ( "Hyper Beast [M4A1]" ) },
				{ 475, ( "Hyper Beast [AWP]" ) },
				{ 537, ( "Hyper Beast [Nova]" ) },
				{ 660, ( "Hyper Beast [Five-SeveN]" ) },

				{ 12, ( "Crimson Web [Knife]" ) },
				{ 232, ( "Crimson Web [SCAR/Deagle]" ) },
				{ 10061, ( "Crimson Web [Glove]" ) },

				{ 98, ( "Ultraviolet [SG/Knife]" ) },
				{ 620, ( "Ultraviolet [Huntsman]" ) },
				{ 621, ( "Ultraviolet [Falchion]" ) },

				{ 189, ( "Bright Water [M4A1]" ) },
				{ 578, ( "Bright Water [Knife]" ) },
				{ 579, ( "Bright Water [M9]" ) },

				{ 196, ( "Emerald [SCAR]" ) },
				{ 453, ( "Emerald [CZ]" ) },
				{ 10057, ( "Emerald [Glove]" ) },

				{ 247, ( "Damascus Steel [SG]" ) },
				{ 410, ( "Damascus Steel [Bright??]" ) }, // todo review texture
				{ 411, ( "Damascus Steel [Dark  ??]" ) }, // todo review texture

				{ 254, ( "Nitro [M4A1/Five-SeveN]" ) },
				{ 322, ( "Nitro [CZ]" ) },
				{ 798, ( "Nitro [R8]" ) },

				{ 260, ( "Pulse [FAMAS]" ) },
				{ 287, ( "Pulse [SG]" ) },
				{ 338, ( "Pulse [P2000]" ) },

				{ 354, ( "Urban Hazard [MP7]" ) },
				{ 387, ( "Urban Hazard [Five-SeveN]" ) },
				{ 700, ( "Urban Hazard [P2000]" ) },

				{ 388, ( "Cartel [P250]" ) },
				{ 394, ( "Cartel [AK]" ) },
				{ 528, ( "Cartel [Elites]" ) },

				{ 422, ( "Elite Build [AK]" ) },
				{ 486, ( "Elite Build [P90]" ) },
				{ 525, ( "Elite Build [AWP]" ) },

				{ 580, ( "Freehand [Knife]" ) },
				{ 581, ( "Freehand [M9]" ) },
				{ 582, ( "Freehand [Karambit]" ) },

				{ 597, ( "Bloodsport [SCAR]" ) },
				{ 639, ( "Bloodsport [AK]" ) },
				{ 696, ( "Bloodsport [MP7]" ) },

				{ 2, ( "Bloodsport [TEC/Glock]" ) },
				{ 209, ( "Bloodsport [MP7]" ) },

				{ 5, ( "Forest DDPAT [MP7/Knife/Sawed-Off]" ) },
				{ 10030, ( "Forest DDPAT [Glove]" ) },

				{ 28, ( "Anodized Navy [SG/MP7/Negev/Elites]" ) },
				{ 197, ( "Anodized Navy [AUG]" ) },

				{ 33, ( "Hot Rod [AUG/MP9]" ) },
				{ 445, ( "Hot Rod [M4A1]" ) },

				{ 44, ( "Case Hardened [AK/Knife/Five-SeveN]" ) },
				{ 10060, ( "Case Hardened [Glove]" ) },

				{ 59, ( "Slaughter [Knife]" ) },
				{ 10021, ( "Slaughter [Glove]" ) },

				{ 99, ( "Sand Dune [SSG/MAG-7/Nova/P250]" ) },
				{ 208, ( "Sand Dune [Glock]" ) },

				{ 101, ( "Tornado [SG/Mac/M4A4]" ) },
				{ 206, ( "Tornado [TEC]" ) },

				{ 151, ( "Jungle [Five-SeveN]" ) },
				{ 205, ( "Jungle [XM]" ) },

				{ 157, ( "Palm [Mac/SCAR]" ) },
				{ 201, ( "Palm [Negev]" ) },

				{ 167, ( "Radiation Hazard [M4A4]" ) },
				{ 375, ( "Radiation Hazard [AUG]" ) },

				{ 168, ( "Nuclear Threat [P250]" ) },
				{ 179, ( "Nuclear Threat [TEC]" ) },

				{ 169, ( "Fallout Warning [XM/UMP/P90]" ) },
				{ 378, ( "Fallout Warning [SG]" ) },

				{ 174, ( "BOOM [AWP]" ) },
				{ 10027, ( "Boom! [Glove]" ) },

				{ 181, ( "Corticera [AWP]" ) },
				{ 184, ( "Corticera [P2000]" ) },

				{ 211, ( "Ocean Foam [P2000]" ) },
				{ 213, ( "Ocean Foam [MP7]" ) },

				{ 212, ( "Graphite [AWP]" ) },
				{ 214, ( "Graphite [Nova]" ) },

				{ 246, ( "Amber Fade [Mac/P2000/Sawed-Off]" ) },
				{ 523, ( "Amber Fade [R8]" ) },
				  
				{ 257, ( "Guardian [M4A1]" ) },
				{ 290, ( "Guardian [USP]" ) },
				  
				{ 259, ( "Redline [AWP]" ) },
				{ 282, ( "Redline [AK]" ) },
				  
				{ 264, ( "Sandstorm [Galil]" ) },
				{ 289, ( "Sandstorm [TEC]" ) },
				  
				{ 265, ( "Kami [Five-SeveN]" ) },
				{ 308, ( "Kami [Galil]" ) },
				  
				{ 284, ( "Heat [Mac]" ) },
				{ 431, ( "Heat [MAG-7]" ) },

				{ 286, ( "Antique [Nova]" ) },
				{ 306, ( "Antique [Bizon]" ) },

				{ 291, ( "Heaven Guard [MAG-7]" ) },
				{ 314, ( "Heaven Guard [XM]" ) },

				{ 305, ( "Torque [AUG]" ) },
				{ 489, ( "Torque [USP]" ) },

				{ 336, ( "Desert-Strike [M4A4]" ) },
				{ 355, ( "Desert-Strike [Negev]" ) },

				{ 341, ( "First Class [AK]" ) },
				{ 345, ( "First Class [Sawed-Off]" ) },

				{ 342, ( "Leather [P90]" ) },
				{ 10009, ( "Leather [Glove]" ) },

				{ 372, ( "Nuclear Garden [Mac]" ) },
				{ 789, ( "Nuclear Garden [Glock]" ) },

				{ 380, ( "Wasteland Rebel [AK]" ) },
				{ 586, ( "Wasteland Rebel [Glock]" ) },

				{ 395, ( "Man-o'-war [AWP]" ) },
				{ 432, ( "Man-o'-war [Negev]" ) },

				{ 426, ( "Valence [P250]" ) },
				{ 529, ( "Valence [FAMAS]" ) },

				{ 428, ( "Eco [Galil]" ) },
				{ 709, ( "Eco [CZ]" ) },

				{ 433, ( "Neon Rider [Mac]" ) },
				{ 707, ( "Neon Rider [AK]" ) },

				{ 448, ( "Pandora's Box [MP9]" ) },
				{ 10037, ( "Pandora's Box [Glove]" ) },

				{ 446, ( "Crimson Kimono [P250]" ) },
				{ 10033, ( "Crimson Kimono [Glove]" ) },

				{ 505, ( "Scumbria [XM]" ) },
				{ 605, ( "Scumbria [Five-SeveN]" ) },

				{ 524, ( "Fuel Injector [AK]" ) },
				{ 614, ( "Fuel Injector [TEC]" ) },

				{ 550, ( "Oceanic [P2000]" ) },
				{ 682, ( "Oceanic [Mac]" ) },

				{ 587, ( "Mecha Industries [M4A1]" ) },
				{ 626, ( "Mecha Industries [FAMAS]" ) },

				{ 612, ( "Powercore [SCAR]" ) },
				{ 719, ( "Powercore [MP7]" ) },

				{ 615, ( "Briefing [UMP]" ) },
				{ 663, ( "Briefing [M4A1]" ) },

				{ 629, ( "Black Sand [Galil]" ) },
				{ 697, ( "Black Sand [MP9]" ) },

				{ 641, ( "Jungle Slipstream [Bizon]" ) },
				{ 685, ( "Jungle Slipstream [SCAR]" ) },

				{ 642, ( "Blueprint [SCAR]" ) },
				{ 657, ( "Blueprint [USP]" ) },

				{ 645, ( "Oxide Blaze [Deagle]" ) },
				{ 706, ( "Oxide Blaze [XM]" ) },

				{ 646, ( "Capillary [Five-SeveN]" ) },
				{ 715, ( "Capillary [MP9]" ) },

				{ 653, ( "Neo-Noir [USP]" ) },
				{ 695, ( "Neo-Noir [M4A4]" ) },

				{ 665, ( "Aloha [Mac]" ) },
				{ 702, ( "Aloha [SG]" ) },
			};

			//struct skin_info
			//{
			//	int max_quality_type, // QUALITY_MAX = stattrak
			//		grade;
			//	bool at_least_one_has_exclusive_different_quality,
			//		 at_least_one_different_grade;
			//};

			// https://csgostash.com/family/ add name, spaces are needed in url.
			// https://csgostash.com/skin-rarity/Consumer+Grade?name=&has_st=1&no_st=1&has_souv=1&no_souv=1&sort=date_added&order=asc&page=1 change consumer grade to whatever grade u want
			//std::map< int /*id*/, skin_info > mpInfo
			//{
			//	// page one of rarity consumer
			//	{ 22,    { QUALITY_DEFAULT,   GRADE_CONSUMER,   false, false } },
			//	{ 93,    { QUALITY_DEFAULT,   GRADE_CONSUMER,   false, false } },
			//	{ 101,   { QUALITY_DEFAULT,   GRADE_CONSUMER,   true,  true  } }, // review: tornado, two skins, multiple qualities and grades
			//	{ 206,   { QUALITY_SOUVENIER,  GRADE_INDUSTRIAL, true,  true  } }, // review: tornado, two skins, multiple qualities and grades
			//	{ 26,    { QUALITY_DEFAULT,   GRADE_CONSUMER,   false, false } },
			//	{ 17,    { QUALITY_DEFAULT,   GRADE_CONSUMER,   true,  true  } }, // review: urban ddpat, multiple qualities and grades
			//	{ 171,   { QUALITY_SOUVENIER,  GRADE_CONSUMER,   false, false } },
			//	{ 25,    { QUALITY_DEFAULT,   GRADE_CONSUMER,   true,  true  } }, // review: forest leaves, multiple qualities and grades
			//	{ 151,   { QUALITY_DEFAULT,   GRADE_CONSUMER,   false, false } }, // review: jundle, two skins
			//	{ 205,   { QUALITY_DEFAULT,   GRADE_CONSUMER,   false, false } }, // review: jundle, two skins
			//	{ 135,   { QUALITY_DEFAULT,   GRADE_CONSUMER,   false, false } },
			//	{ 158,   { QUALITY_SOUVENIER,  GRADE_CONSUMER,   false, false } },
			//	{ 99,    { QUALITY_SOUVENIER,  GRADE_CONSUMER,   true,  true  } }, // review: sand dune, two skins, multiple qualities and grades
			//	{ 208,   { QUALITY_DEFAULT,   GRADE_INDUSTRIAL, true,  true  } }, // review: sand dune, two skins, multiple qualities and grades
			//	{ 2,     { QUALITY_SOUVENIER,  GRADE_CONSUMER,   true,  true  } }, // review: groundwater, two skins, multiple qualities and grades
			//	{ 209,   { QUALITY_SOUVENIER,  GRADE_INDUSTRIAL, true,  true  } }, // review: groundwater, two skins, multiple qualities and grades
			//	{ 210,   { QUALITY_DEFAULT,   GRADE_CONSUMER,   false, false } },
			//	{ 202,   { QUALITY_DEFAULT,   GRADE_CONSUMER,   false, false } },
			//	{ 199,   { QUALITY_DEFAULT,   GRADE_CONSUMER,   false, false } },
			//	{ 47,    { QUALITY_SOUVENIER,  GRADE_CONSUMER,   false, false } },
			//	{ 96,    { QUALITY_SOUVENIER,  GRADE_CONSUMER,   false, false } },
			//	{ 77,    { QUALITY_SOUVENIER,  GRADE_CONSUMER,   true,  true  } }, // review: KNIFE, SOUVENIR/STATTRAK, QUALITIES, GRADES, AHHHH
			//	{ 147,   { QUALITY_SOUVENIER,  GRADE_CONSUMER,   false, false } },
			//	// page two of rarity consumer
			//	// page three of rarity consumer
			//	// page four of rarity consumer
			//
			//	// page one of rarity industrial
			//	// page two of rarity industrial
			//	// page three of rarity industrial
			//	// page four of rarity industrial
			//
			//	// page one of rarity milspec
			//	// page two of rarity milspec
			//	// page three of rarity milspec
			//	// page four of rarity milspec
			//	// page five of rarity milspec
			//	// page six of rarity milspec
			//	// page seven of rarity milspec
			//	// page eight of rarity milspec
			//	// page nine of rarity milspec
			//
			//	// page one of rarity restricted
			//	// page two of rarity restricted
			//	// page three of rarity restricted
			//	// page four of rarity restricted
			//	// page five of rarity restricted
			//	// page six of rarity restricted
			//	// page seven of rarity restricted
			//
			//	// page one of rarity classified
			//	// page two of rarity classified
			//	// page three of rarity classified
			//	// page four of rarity classified
			//
			//	// page one of rarity covert
			//	// page two of rarity covert
			//	// page three of rarity covert
			//	// page four of rarity covert
			//
			//	// page one of rarity knife
			//	// page two of rarity knife
			//	// page three of rarity knife
			//	// page four of rarity knife
			//	// page five of rarity knife
			//	// page six of rarity knife
			//	// page seven of rarity knife
			//	// page eight of rarity knife
			//	// page nine of rarity knife
			//	// page ten of rarity knife
			//
			//	// page one of rarity contraband
			//	{ 309,   { QUALITY_MAX,       GRADE_CONSUMER,   false, false } }
			//};

			for( auto i = 0; i < pHead->nLastElement; i++ )
			{
				const auto pPaintKit = pHead->pMemory[ i ].pPaintKit;

				if ( pPaintKit->iIndex == 9001 )
					continue;

				const auto pSearch = mpCustomNames.find( pPaintKit->iIndex );
				const auto strBuffer = pSearch == mpCustomNames.end( )
					? Tools::string_cast< std::string >( pLocalize->Find( pPaintKit->Tag.szBuffer + 0x1 ) )
					: pSearch->second;
				std::string strNew { };
				for ( auto _char : strBuffer )
					if ( _char >= 49
						 || _char <= 122 )
						strNew += _char;

				//const auto pSearch2 = mpInfo.find( pPaintKit->iIndex );
				//if ( pSearch2 == mpInfo.end( ) )
				//	throw std::exception( "jeremy you fucked up" );
				//
				vecPaintKits.emplace_back( paint_kit_t( pPaintKit->iIndex, strNew ) );
			}

			std::map< short /* item def index */, std::vector< paint_kit_t > /* applicable kits */ > mpWeaponKits
			{
				{
					ITEM_WEAPON_DEAGLE,
					{
						paint_kit_t( 711,PX_XOR( "Code Red" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 185,PX_XOR( "Golden Koi" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 527,PX_XOR( "Kumicho Dragon" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 351,PX_XOR( "Conspiracy" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 231,PX_XOR( "Cobalt Disruption" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 61,PX_XOR( "Hypnotic" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 603,PX_XOR( "Directive" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 397,PX_XOR( "Naga" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 232,PX_XOR( "Crimson Web" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 273,PX_XOR( "Heirloom" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 470,PX_XOR( "Sunset Storm ??É" ), GRADE_RESTRICTED, QUALITY_DEFAULT ),
						paint_kit_t( 469,PX_XOR( "Sunset Storm ?ú?" ), GRADE_RESTRICTED, QUALITY_DEFAULT ),
						paint_kit_t( 328,PX_XOR( "Hand Cannon" ), GRADE_RESTRICTED, QUALITY_SOUVENIER ),
						paint_kit_t( 347,PX_XOR( "Pilot" ), GRADE_RESTRICTED, QUALITY_DEFAULT ),
						paint_kit_t( 37,PX_XOR( "Blaze" ), GRADE_RESTRICTED, QUALITY_DEFAULT ),
						paint_kit_t( 645,PX_XOR( "Oxide Blaze" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 509,PX_XOR( "Corinthian" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 425,PX_XOR( "Bronze Deco" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 296,PX_XOR( "Meteorite" ), GRADE_MILSPEC, QUALITY_DEFAULT ),
						paint_kit_t( 237,PX_XOR( "Urban Rubble" ), GRADE_MILSPEC, QUALITY_SOUVENIER ),
						paint_kit_t( 40,PX_XOR( "Night" ), GRADE_INDUSTRIAL, QUALITY_DEFAULT ),
						paint_kit_t( 468,PX_XOR( "Midnight Storm" ), GRADE_INDUSTRIAL, QUALITY_DEFAULT ),
						paint_kit_t( 17,PX_XOR( "Urban DDPAT" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 90,PX_XOR( "Mudder" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER )
					}
				},
				{
					ITEM_WEAPON_ELITE,
					{
						paint_kit_t( 658,PX_XOR( "Cobra Strike" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 747,PX_XOR( "Twin Turbo" ), GRADE_CLASSIFIED, QUALITY_SOUVENIER ),
						paint_kit_t( 625,PX_XOR( "Royal Consorts" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 396,PX_XOR( "Urban Shock" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 261,PX_XOR( "Marina" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 220,PX_XOR( "Hemoglobin" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 447,PX_XOR( "Duelist" ), GRADE_RESTRICTED, QUALITY_DEFAULT ),
						paint_kit_t( 249,PX_XOR( "Cobalt Quartz" ), GRADE_RESTRICTED, QUALITY_SOUVENIER ),
						paint_kit_t( 153,PX_XOR( "Demolition" ), GRADE_RESTRICTED, QUALITY_DEFAULT ),
						paint_kit_t( 710,PX_XOR( "Shred" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 544,PX_XOR( "Ventilators" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 528,PX_XOR( "Cartel" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 491,PX_XOR( "Dualing Dragons" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 307,PX_XOR( "Retribution" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 276,PX_XOR( "Panther" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 190,PX_XOR( "Black Limba" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 28,PX_XOR( "Anodized Navy" ), GRADE_MILSPEC, QUALITY_SOUVENIER ),
						paint_kit_t( 43,PX_XOR( "Stained" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 450,PX_XOR( "Moon in Libra" ), GRADE_CONSUMER, QUALITY_DEFAULT ),
						paint_kit_t( 330,PX_XOR( "Briar" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 46,PX_XOR( "Contractor" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 47,PX_XOR( "Colony" ), GRADE_CONSUMER, QUALITY_SOUVENIER )
					}
				},
				{
					ITEM_WEAPON_FIVESEVEN,
					{
						paint_kit_t( 660,PX_XOR( "Hyper Beast" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 427,PX_XOR( "Monkey Business" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 352,PX_XOR( "Fowl Play" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 530,PX_XOR( "Triumvirate" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 510,PX_XOR( "Retrobution" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 274,PX_XOR( "Copper Galaxy" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 44,PX_XOR( "Case Hardened" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 464,PX_XOR( "Neon Kimono" ), GRADE_RESTRICTED, QUALITY_DEFAULT ),
						paint_kit_t( 693,PX_XOR( "Flame Test" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 646,PX_XOR( "Capillary" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 605,PX_XOR( "Scumbria" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 585,PX_XOR( "Violent Daimyo" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 387,PX_XOR( "Urban Hazard" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 223,PX_XOR( "Nightshade" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 265,PX_XOR( "Kami" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 254,PX_XOR( "Nitro" ), GRADE_MILSPEC, QUALITY_DEFAULT ),
						paint_kit_t( 252,PX_XOR( "Silver Quartz" ), GRADE_MILSPEC, QUALITY_SOUVENIER ),
						paint_kit_t( 377,PX_XOR( "Hot Shot" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 141,PX_XOR( "Orange Peel" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 3,PX_XOR( "Candy Apple" ), GRADE_INDUSTRIAL, QUALITY_DEFAULT ),
						paint_kit_t( 784,PX_XOR( "Coolant" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 46,PX_XOR( "Contractor" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 78,PX_XOR( "Forest Night" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 210,PX_XOR( "Anodized Gunmetal" ), GRADE_CONSUMER, QUALITY_DEFAULT ),
						paint_kit_t( 151,PX_XOR( "Jungle" ), GRADE_CONSUMER, QUALITY_DEFAULT )
					}
				},
				{
					ITEM_WEAPON_GLOCK,
					{
						paint_kit_t( 586,PX_XOR( "Wasteland Rebel" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 353,PX_XOR( "Water Elemental" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 437,PX_XOR( "Twilight Galaxy" ), GRADE_CLASSIFIED, QUALITY_DEFAULT ),
						paint_kit_t( 694,PX_XOR( "Moonrise" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 607,PX_XOR( "Weasel" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 532,PX_XOR( "Royal Legion" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 381,PX_XOR( "Grinder" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 230,PX_XOR( "Steel Disruption" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 48,PX_XOR( "Dragon Tattoo" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 789,PX_XOR( "Nuclear Garden" ), GRADE_RESTRICTED, QUALITY_SOUVENIER ),
						paint_kit_t( 38,PX_XOR( "Fade" ), GRADE_RESTRICTED, QUALITY_DEFAULT ),
						paint_kit_t( 159,PX_XOR( "Brass" ), GRADE_RESTRICTED, QUALITY_DEFAULT ),
						paint_kit_t( 713,PX_XOR( "Warhawk" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 680,PX_XOR( "Off World" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 623,PX_XOR( "Ironwork" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 495,PX_XOR( "Wraiths" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 479,PX_XOR( "Bunsen Burner" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 399,PX_XOR( "Catacombs" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 278,PX_XOR( "Blue Fissure" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 367,PX_XOR( "Reactor" ), GRADE_MILSPEC, QUALITY_SOUVENIER ),
						paint_kit_t( 3,PX_XOR( "Candy Apple" ), GRADE_MILSPEC, QUALITY_SOUVENIER ),
						paint_kit_t( 799,PX_XOR( "High Beam" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 40,PX_XOR( "Night" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 293,PX_XOR( "Death Rattle" ), GRADE_INDUSTRIAL, QUALITY_DEFAULT ),
						paint_kit_t( 2,PX_XOR( "Groundwater" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 208,PX_XOR( "Sand Dune" ), GRADE_INDUSTRIAL, QUALITY_DEFAULT )
					}
				},
				{
					ITEM_WEAPON_AK47,
					{
						paint_kit_t( 707,PX_XOR( "Neon Rider" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 675,PX_XOR( "The Empress" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 639,PX_XOR( "Bloodsport" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 600,PX_XOR( "Neon Revolution" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 524,PX_XOR( "Fuel Injector" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 474,PX_XOR( "Aquamarine Revenge" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 380,PX_XOR( "Wasteland Rebel" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 316,PX_XOR( "Jaguar" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 302,PX_XOR( "Vulcan" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 180,PX_XOR( "Fire Serpent" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 506,PX_XOR( "Point Disarray" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 490,PX_XOR( "Frontside Misty" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 394,PX_XOR( "Cartel" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 282,PX_XOR( "Redline" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 14,PX_XOR( "Red Laminate" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 44,PX_XOR( "Case Hardened" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 456,PX_XOR( "Hydroponic" ), GRADE_CLASSIFIED, QUALITY_DEFAULT ),
						paint_kit_t( 340,PX_XOR( "Jet Set" ), GRADE_CLASSIFIED, QUALITY_DEFAULT ),
						paint_kit_t( 656,PX_XOR( "Orbit Mk01" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 226,PX_XOR( "Blue Laminate" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 795,PX_XOR( "Safety Net" ), GRADE_RESTRICTED, QUALITY_SOUVENIER ),
						paint_kit_t( 341,PX_XOR( "First Class" ), GRADE_RESTRICTED, QUALITY_DEFAULT ),
						paint_kit_t( 300,PX_XOR( "Emerald Pinstripe" ), GRADE_RESTRICTED, QUALITY_DEFAULT ),
						paint_kit_t( 422,PX_XOR( "Elite Build" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 172,PX_XOR( "Black Laminate" ), GRADE_MILSPEC, QUALITY_DEFAULT ),
						paint_kit_t( 72,PX_XOR( "Safari Mesh" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 122,PX_XOR( "Jungle Spray" ), GRADE_INDUSTRIAL, QUALITY_DEFAULT ),
						paint_kit_t( 170,PX_XOR( "Predator" ), GRADE_INDUSTRIAL, QUALITY_DEFAULT )
					}
				},
				{
					ITEM_WEAPON_AUG,
					{
						paint_kit_t( 280,PX_XOR( "Chameleon" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 455,PX_XOR( "Akihabara Accept" ), GRADE_COVERT, QUALITY_DEFAULT ),
						paint_kit_t( 690,PX_XOR( "Stymphalian" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 601,PX_XOR( "Syd Mead" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 541,PX_XOR( "Fleet Flock" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 9,PX_XOR( "Bengal Tiger" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 583,PX_XOR( "Aristocrat" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 305,PX_XOR( "Torque" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 779,PX_XOR( "Random Access" ), GRADE_RESTRICTED, QUALITY_SOUVENIER ),
						paint_kit_t( 708,PX_XOR( "Amber Slipstream" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 674,PX_XOR( "Triqua" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 507,PX_XOR( "Ricochet" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 73,PX_XOR( "Wings" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 197,PX_XOR( "Anodized Navy" ), GRADE_MILSPEC, QUALITY_DEFAULT ),
						paint_kit_t( 33,PX_XOR( "Hot Rod" ), GRADE_MILSPEC, QUALITY_DEFAULT ),
						paint_kit_t( 10,PX_XOR( "Copperhead" ), GRADE_MILSPEC, QUALITY_DEFAULT ),
						paint_kit_t( 375,PX_XOR( "Radiation Hazard" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 110,PX_XOR( "Condemned" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 794,PX_XOR( "Sweeper" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 444,PX_XOR( "Daedalus" ), GRADE_CONSUMER, QUALITY_DEFAULT ),
						paint_kit_t( 100,PX_XOR( "Storm" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 46,PX_XOR( "Contractor" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 47,PX_XOR( "Colony" ), GRADE_CONSUMER, QUALITY_SOUVENIER )
					}
				},
				{
					ITEM_WEAPON_AWP,
					{
						paint_kit_t( 662,PX_XOR( "Oni Taiji" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 475,PX_XOR( "Hyper Beast" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 395,PX_XOR( "Man-o'-War" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 279,PX_XOR( "Asiimov" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 51,PX_XOR( "Lightning Strike" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 446,PX_XOR( "Medusa" ), GRADE_COVERT, QUALITY_DEFAULT ),
						paint_kit_t( 344,PX_XOR( "Dragon Lore" ), GRADE_COVERT, QUALITY_SOUVENIER ),
						paint_kit_t( 691,PX_XOR( "Mortis" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 640,PX_XOR( "Fever Dream" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 525,PX_XOR( "Elite Build" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 181,PX_XOR( "Corticera" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 259,PX_XOR( "Redline" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 227,PX_XOR( "Electric Hive" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 212,PX_XOR( "Graphite" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 174,PX_XOR( "BOOM" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 718,PX_XOR( "PAW" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 584,PX_XOR( "Phobos" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 424,PX_XOR( "Worm God" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 84,PX_XOR( "Pink DDPAT" ), GRADE_RESTRICTED, QUALITY_SOUVENIER ),
						paint_kit_t( 251,PX_XOR( "Pit Viper" ), GRADE_RESTRICTED, QUALITY_SOUVENIER ),
						paint_kit_t( 788,PX_XOR( "Acheron" ), GRADE_MILSPEC, QUALITY_SOUVENIER ),
						paint_kit_t( 30,PX_XOR( "Snake Camo" ), GRADE_MILSPEC, QUALITY_DEFAULT ),
						paint_kit_t( 451,PX_XOR( "Sun in Leo" ), GRADE_INDUSTRIAL, QUALITY_DEFAULT ),
						paint_kit_t( 72,PX_XOR( "Safari Mesh" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER )
					}
				},
				{
					ITEM_WEAPON_FAMAS,
					{
						paint_kit_t( 604,PX_XOR( "Roll Cage" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 723,PX_XOR( "Eye of Athena" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 626,PX_XOR( "Mecha Industries" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 429,PX_XOR( "Djinn" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 154,PX_XOR( "Afterimage" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 529,PX_XOR( "Valence" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 477,PX_XOR( "Neural Net" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 288,PX_XOR( "Sergeant" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 260,PX_XOR( "Pulse" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 371,PX_XOR( "Styx" ), GRADE_RESTRICTED, QUALITY_SOUVENIER ),
						paint_kit_t( 194,PX_XOR( "Spitfire" ), GRADE_RESTRICTED, QUALITY_DEFAULT ),
						paint_kit_t( 659,PX_XOR( "Macabre" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 492,PX_XOR( "Survivor Z" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 218,PX_XOR( "Hexane" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 178,PX_XOR( "Doomkitty" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 244,PX_XOR( "Teardown" ), GRADE_MILSPEC, QUALITY_SOUVENIER ),
						paint_kit_t( 92,PX_XOR( "Cyanospatter" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 47,PX_XOR( "Colony" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 22,PX_XOR( "Contrast Spray" ), GRADE_CONSUMER, QUALITY_DEFAULT )
					}
				},
				{
					ITEM_WEAPON_G3SG1,
					{
						paint_kit_t( 511,PX_XOR( "The Executioner" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 493,PX_XOR( "Flux" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 712,PX_XOR( "High Seas" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 628,PX_XOR( "Stinger" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 438,PX_XOR( "Chronos" ), GRADE_RESTRICTED, QUALITY_DEFAULT ),
						paint_kit_t( 677,PX_XOR( "Hunter" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 606,PX_XOR( "Ventilator" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 545,PX_XOR( "Orange Crash" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 382,PX_XOR( "Murky" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 229,PX_XOR( "Azure Zebra" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 195,PX_XOR( "Demeter" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 294,PX_XOR( "Green Apple" ), GRADE_INDUSTRIAL, QUALITY_DEFAULT ),
						paint_kit_t( 235,PX_XOR( "VariCamo" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 6,PX_XOR( "Arctic Camo" ), GRADE_INDUSTRIAL, QUALITY_DEFAULT ),
						paint_kit_t( 465,PX_XOR( "Orange Kimono" ), GRADE_CONSUMER, QUALITY_DEFAULT ),
						paint_kit_t( 46,PX_XOR( "Contractor" ), GRADE_CONSUMER, QUALITY_DEFAULT ),
						paint_kit_t( 147,PX_XOR( "Jungle Dashed" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 74,PX_XOR( "Polar Camo" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 72,PX_XOR( "Safari Mesh" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 8,PX_XOR( "Desert Storm" ), GRADE_CONSUMER, QUALITY_SOUVENIER )
					}
				},
				{
					ITEM_WEAPON_GALILAR,
					{
						paint_kit_t( 398,PX_XOR( "Chatterbox" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 661,PX_XOR( "Sugar Rush" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 428,PX_XOR( "Eco" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 647,PX_XOR( "Crimson Tsunami" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 546,PX_XOR( "Firefight" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 494,PX_XOR( "Stone Cold" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 83,PX_XOR( "Orange DDPAT" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 379,PX_XOR( "Cerberus" ), GRADE_RESTRICTED, QUALITY_SOUVENIER ),
						paint_kit_t( 629,PX_XOR( "Black Sand" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 478,PX_XOR( "Rocket Pop" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 308,PX_XOR( "Kami" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 216,PX_XOR( "Blue Titanium" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 264,PX_XOR( "Sandstorm" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 192,PX_XOR( "Shattered" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 460,PX_XOR( "Aqua Terrace" ), GRADE_MILSPEC, QUALITY_DEFAULT ),
						paint_kit_t( 297,PX_XOR( "Tuxedo" ), GRADE_MILSPEC, QUALITY_DEFAULT ),
						paint_kit_t( 790,PX_XOR( "Cold Fusion" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 237,PX_XOR( "Urban Rubble" ), GRADE_INDUSTRIAL, QUALITY_DEFAULT ),
						paint_kit_t( 235,PX_XOR( "VariCamo" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 76,PX_XOR( "Winter Forest" ), GRADE_INDUSTRIAL, QUALITY_DEFAULT ),
						paint_kit_t( 119,PX_XOR( "Sage Spray" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 241,PX_XOR( "Hunting Blind" ), GRADE_CONSUMER, QUALITY_SOUVENIER )
					}
				},
				{
					ITEM_WEAPON_M249,
					{
						paint_kit_t( 648,PX_XOR( "Emerald Poison Dart" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 496,PX_XOR( "Nebula Crusader" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 547,PX_XOR( "Spectre" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 401,PX_XOR( "System Lock" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 266,PX_XOR( "Magma" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 452,PX_XOR( "Shipping Forecast" ), GRADE_INDUSTRIAL, QUALITY_DEFAULT ),
						paint_kit_t( 243,PX_XOR( "Gator Mesh" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 75,PX_XOR( "Blizzard Marbleized" ), GRADE_INDUSTRIAL, QUALITY_DEFAULT ),
						paint_kit_t( 472,PX_XOR( "Impact Drill" ), GRADE_CONSUMER, QUALITY_DEFAULT ),
						paint_kit_t( 22,PX_XOR( "Contrast Spray" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 202,PX_XOR( "Jungle DDPAT" ), GRADE_CONSUMER, QUALITY_DEFAULT )
					}
				},
				{
					ITEM_WEAPON_M4A1,
					{
						paint_kit_t( 309,PX_XOR( "Howl" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 695,PX_XOR( "Ne" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 632,PX_XOR( "Buzz Kill" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 533,PX_XOR( "The Battlestar" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 512,PX_XOR( "Royal Paladin" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 155,PX_XOR( "Bullet Rain" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 336,PX_XOR( "Desert-Strike" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 255,PX_XOR( "Asiimov" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 215,PX_XOR( "X-Ray" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 664,PX_XOR( "Hellfire" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 588,PX_XOR( "Desolate Space" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 400,PX_XOR( "Dragon King" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 449,PX_XOR( "Poseidon" ), GRADE_CLASSIFIED, QUALITY_DEFAULT ),
						paint_kit_t( 480,PX_XOR( "Evil Daimyo" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 384,PX_XOR( "Griffin" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 187,PX_XOR( "Zirka" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 471,PX_XOR( "Daybreak" ), GRADE_RESTRICTED, QUALITY_DEFAULT ),
						paint_kit_t( 164,PX_XOR( "Modern Hunter" ), GRADE_RESTRICTED, QUALITY_DEFAULT ),
						paint_kit_t( 176,PX_XOR( "Faded Zebra" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 793,PX_XOR( "Converter" ), GRADE_MILSPEC, QUALITY_SOUVENIER ),
						paint_kit_t( 167,PX_XOR( "Radiation Hazard" ), GRADE_MILSPEC, QUALITY_SOUVENIER ),
						paint_kit_t( 780,PX_XOR( "Mainframe" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 17,PX_XOR( "Urban DDPAT" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 101,PX_XOR( "Tornado" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 16,PX_XOR( "Jungle Tiger" ), GRADE_INDUSTRIAL, QUALITY_DEFAULT ),
						paint_kit_t( 8,PX_XOR( "Desert Storm" ), GRADE_INDUSTRIAL, QUALITY_DEFAULT )
					}
				},
				{
					ITEM_WEAPON_MAC10,
					{
						paint_kit_t( 433,PX_XOR( "Neon Rider" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 651,PX_XOR( "Last Dive" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 402,PX_XOR( "Malachite" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 337,PX_XOR( "Tatter" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 310,PX_XOR( "Curse" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 284,PX_XOR( "Heat" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 188,PX_XOR( "Graven" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 682,PX_XOR( "Oceanic" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 665,PX_XOR( "Aloha" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 589,PX_XOR( "Carnivore" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 534,PX_XOR( "Lapis Gator" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 498,PX_XOR( "Rangeen" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 98,PX_XOR( "Ultraviolet" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 38,PX_XOR( "Fade" ), GRADE_MILSPEC, QUALITY_DEFAULT ),
						paint_kit_t( 372,PX_XOR( "Nuclear Garden" ), GRADE_MILSPEC, QUALITY_SOUVENIER ),
						paint_kit_t( 246,PX_XOR( "Amber Fade" ), GRADE_MILSPEC, QUALITY_SOUVENIER ),
						paint_kit_t( 748,PX_XOR( "Calf Skin" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 343,PX_XOR( "Commuter" ), GRADE_INDUSTRIAL, QUALITY_DEFAULT ),
						paint_kit_t( 32,PX_XOR( "Silver" ), GRADE_INDUSTRIAL, QUALITY_DEFAULT ),
						paint_kit_t( 157,PX_XOR( "Palm" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 3,PX_XOR( "Candy Apple" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 333,PX_XOR( "Indigo" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 101,PX_XOR( "Tornado" ), GRADE_CONSUMER, QUALITY_DEFAULT ),
						paint_kit_t( 17,PX_XOR( "Urban DDPAT" ), GRADE_CONSUMER, QUALITY_DEFAULT )
					}
				},
				{
					ITEM_WEAPON_P90,
					{
						paint_kit_t( 359,PX_XOR( "Asiimov" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 156,PX_XOR( "Death by Kitty" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 636,PX_XOR( "Shallow Grave" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 516,PX_XOR( "Shapewood" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 283,PX_XOR( "Trigon" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 67,PX_XOR( "Cold Blooded" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 182,PX_XOR( "Emerald Dragon" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 669,PX_XOR( "Death Grip" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 593,PX_XOR( "Chopper" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 20,PX_XOR( "Virus" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 228,PX_XOR( "Blind Spot" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 717,PX_XOR( "Traction" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 611,PX_XOR( "Grim" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 486,PX_XOR( "Elite Build" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 335,PX_XOR( "Module" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 311,PX_XOR( "Desert Warfare" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 776,PX_XOR( "Facility Negative" ), GRADE_MILSPEC, QUALITY_SOUVENIER ),
						paint_kit_t( 244,PX_XOR( "Teardown" ), GRADE_MILSPEC, QUALITY_SOUVENIER ),
						paint_kit_t( 111,PX_XOR( "Glacier Mesh" ), GRADE_MILSPEC, QUALITY_DEFAULT ),
						paint_kit_t( 342,PX_XOR( "Leather" ), GRADE_INDUSTRIAL, QUALITY_DEFAULT ),
						paint_kit_t( 234,PX_XOR( "Ash Wood" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 169,PX_XOR( "Fallout Warning" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 100,PX_XOR( "Storm" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 175,PX_XOR( "Scorched" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 124,PX_XOR( "Sand Spray" ), GRADE_CONSUMER, QUALITY_SOUVENIER )
					}
				},
				{
					ITEM_WEAPON_MP5SD,
					{
						paint_kit_t( 781,PX_XOR( "Co-Processor" ), GRADE_MILSPEC, QUALITY_SOUVENIER ),
						paint_kit_t( 753,PX_XOR( "Dirt Drop" ), GRADE_CONSUMER, QUALITY_SOUVENIER )
					}
				},
				{
					ITEM_WEAPON_UMP45,
					{
						paint_kit_t( 556,PX_XOR( "Primal Saber" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 704,PX_XOR( "Arctic Wolf" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 688,PX_XOR( "Exposure" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 652,PX_XOR( "Scaffold" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 436,PX_XOR( "Grand Prix" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 672,PX_XOR( "Metal Flowers" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 615,PX_XOR( "Briefing" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 488,PX_XOR( "Riot" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 392,PX_XOR( "Delusion" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 362,PX_XOR( "Labyrinth" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 281,PX_XOR( "Corporal" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 193,PX_XOR( "Bone Pile" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 441,PX_XOR( "Minotaur's Labyrinth" ), GRADE_MILSPEC, QUALITY_DEFAULT ),
						paint_kit_t( 37,PX_XOR( "Blaze" ), GRADE_MILSPEC, QUALITY_SOUVENIER ),
						paint_kit_t( 70,PX_XOR( "Carbon Fiber" ), GRADE_INDUSTRIAL, QUALITY_DEFAULT ),
						paint_kit_t( 15,PX_XOR( "Gunsmoke" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 169,PX_XOR( "Fallout Warning" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 778,PX_XOR( "Facility Dark" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 90,PX_XOR( "Mudder" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 333,PX_XOR( "Indigo" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 175,PX_XOR( "Scorched" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 17,PX_XOR( "Urban DDPAT" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 93,PX_XOR( "Caramel" ), GRADE_CONSUMER, QUALITY_DEFAULT )
					}
				},
				{
					ITEM_WEAPON_XM1014,
					{
						paint_kit_t( 393,PX_XOR( "Tranquility" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 689,PX_XOR( "Ziggy" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 654,PX_XOR( "Seasons" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 557,PX_XOR( "Black Tie" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 521,PX_XOR( "Teclu Burner" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 314,PX_XOR( "Heaven Guard" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 706,PX_XOR( "Oxide Blaze" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 616,PX_XOR( "Slipstream" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 505,PX_XOR( "Scumbria" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 407,PX_XOR( "Quicksilver" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 320,PX_XOR( "Red Python" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 370,PX_XOR( "Bone Machine" ), GRADE_MILSPEC, QUALITY_SOUVENIER ),
						paint_kit_t( 348,PX_XOR( "Red Leather" ), GRADE_MILSPEC, QUALITY_DEFAULT ),
						paint_kit_t( 238,PX_XOR( "VariCamo Blue" ), GRADE_MILSPEC, QUALITY_SOUVENIER ),
						paint_kit_t( 166,PX_XOR( "Blaze Orange" ), GRADE_MILSPEC, QUALITY_DEFAULT ),
						paint_kit_t( 240,PX_XOR( "CaliCamo" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 42,PX_XOR( "Blue Steel" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 169,PX_XOR( "Fallout Warning" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 96,PX_XOR( "Blue Spruce" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 205,PX_XOR( "Jungle" ), GRADE_CONSUMER, QUALITY_DEFAULT ),
						paint_kit_t( 95,PX_XOR( "Grassland" ), GRADE_CONSUMER, QUALITY_DEFAULT ),
						paint_kit_t( 135,PX_XOR( "Urban Perforated" ), GRADE_CONSUMER, QUALITY_DEFAULT )
					}
				},
				{
					ITEM_WEAPON_PPBIZON,
					{
						paint_kit_t( 542,PX_XOR( "Judgement of Anubis" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 676,PX_XOR( "High Roller" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 508,PX_XOR( "Fuel Rod" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 13,PX_XOR( "Blue Streak" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 349,PX_XOR( "Osiris" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 306,PX_XOR( "Antique" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 692,PX_XOR( "Night Riot" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 641,PX_XOR( "Jungle Slipstream" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 594,PX_XOR( "Harvester" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 526,PX_XOR( "Photic Zone" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 224,PX_XOR( "Water Sigil" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 267,PX_XOR( "Cobalt Halftone" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 159,PX_XOR( "Brass" ), GRADE_MILSPEC, QUALITY_SOUVENIER ),
						paint_kit_t( 203,PX_XOR( "Rust Coat" ), GRADE_MILSPEC, QUALITY_DEFAULT ),
						paint_kit_t( 164,PX_XOR( "Modern Hunter" ), GRADE_MILSPEC, QUALITY_DEFAULT ),
						paint_kit_t( 3,PX_XOR( "Candy Apple" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 376,PX_XOR( "Chemical Green" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 236,PX_XOR( "Night Ops" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 70,PX_XOR( "Carbon Fiber" ), GRADE_INDUSTRIAL, QUALITY_DEFAULT ),
						paint_kit_t( 775,PX_XOR( "Facility Sketch" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 457,PX_XOR( "Bamboo Print" ), GRADE_CONSUMER, QUALITY_DEFAULT ),
						paint_kit_t( 148,PX_XOR( "Sand Dashed" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 149,PX_XOR( "Urban Dashed" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 25,PX_XOR( "Forest Leaves" ), GRADE_CONSUMER, QUALITY_DEFAULT ),
						paint_kit_t( 171,PX_XOR( "Irradiated Alert" ), GRADE_CONSUMER, QUALITY_SOUVENIER )
					}
				},
				{
					ITEM_WEAPON_MAG7,
					{
						paint_kit_t( 703,PX_XOR( "SWAG-7" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 608,PX_XOR( "Petroglyph" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 535,PX_XOR( "Praetorian" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 431,PX_XOR( "Heat" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 787,PX_XOR( "Core Breach" ), GRADE_RESTRICTED, QUALITY_SOUVENIER ),
						paint_kit_t( 39,PX_XOR( "Bulldozer" ), GRADE_RESTRICTED, QUALITY_SOUVENIER ),
						paint_kit_t( 666,PX_XOR( "Hard Water" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 633,PX_XOR( "Sonar" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 499,PX_XOR( "Cobalt Core" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 385,PX_XOR( "Firestarter" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 291,PX_XOR( "Heaven Guard" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 177,PX_XOR( "Memento" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 462,PX_XOR( "Counter Terrace" ), GRADE_MILSPEC, QUALITY_DEFAULT ),
						paint_kit_t( 198,PX_XOR( "Hazard" ), GRADE_MILSPEC, QUALITY_DEFAULT ),
						paint_kit_t( 32,PX_XOR( "Silver" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 34,PX_XOR( "Metallic DDPAT" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 754,PX_XOR( "Rust Coat" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 473,PX_XOR( "Seabird" ), GRADE_CONSUMER, QUALITY_DEFAULT ),
						paint_kit_t( 100,PX_XOR( "Storm" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 171,PX_XOR( "Irradiated Alert" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 99,PX_XOR( "Sand Dune" ), GRADE_CONSUMER, QUALITY_SOUVENIER )
					}
				},
				{
					ITEM_WEAPON_NEGEV,
					{
						paint_kit_t( 698,PX_XOR( "Lionfish" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 514,PX_XOR( "Power Loader" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 483,PX_XOR( "Loudmouth" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 610,PX_XOR( "Dazzle" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 432,PX_XOR( "Man-o'-War" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 317,PX_XOR( "Bratatat" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 355,PX_XOR( "Desert-Strike" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 285,PX_XOR( "Terrain" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 28,PX_XOR( "Anodized Navy" ), GRADE_MILSPEC, QUALITY_DEFAULT ),
						paint_kit_t( 783,PX_XOR( "Bulkhead" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 369,PX_XOR( "Nuclear Waste" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 240,PX_XOR( "CaliCamo" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 201,PX_XOR( "Palm" ), GRADE_INDUSTRIAL, QUALITY_DEFAULT ),
						paint_kit_t( 298,PX_XOR( "Army Sheen" ), GRADE_CONSUMER, QUALITY_DEFAULT )
					}
				},
				{
					ITEM_WEAPON_SAWEDOFF,
					{
						paint_kit_t( 256,PX_XOR( "The Kraken" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 720,PX_XOR( "Devourer" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 638,PX_XOR( "Wasteland Princess" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 596,PX_XOR( "Limelight" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 405,PX_XOR( "Serenity" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 390,PX_XOR( "Highwayman" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 83,PX_XOR( "Orange DDPAT" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 673,PX_XOR( "Morris" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 655,PX_XOR( "Zander" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 552,PX_XOR( "Fubar" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 517,PX_XOR( "Yorick" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 434,PX_XOR( "Origami" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 797,PX_XOR( "Brake Light" ), GRADE_MILSPEC, QUALITY_SOUVENIER ),
						paint_kit_t( 345,PX_XOR( "First Class" ), GRADE_MILSPEC, QUALITY_DEFAULT ),
						paint_kit_t( 250,PX_XOR( "Full Stop" ), GRADE_MILSPEC, QUALITY_SOUVENIER ),
						paint_kit_t( 246,PX_XOR( "Amber Fade" ), GRADE_MILSPEC, QUALITY_SOUVENIER ),
						paint_kit_t( 41,PX_XOR( "Copper" ), GRADE_MILSPEC, QUALITY_DEFAULT ),
						paint_kit_t( 323,PX_XOR( "Rust Coat" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 30,PX_XOR( "Snake Camo" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 204,PX_XOR( "Mosaico" ), GRADE_INDUSTRIAL, QUALITY_DEFAULT ),
						paint_kit_t( 458,PX_XOR( "Bamboo Shadow" ), GRADE_CONSUMER, QUALITY_DEFAULT ),
						paint_kit_t( 119,PX_XOR( "Sage Spray" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 5,PX_XOR( "Forest DDPAT" ), GRADE_CONSUMER, QUALITY_DEFAULT ),
						paint_kit_t( 171,PX_XOR( "Irradiated Alert" ), GRADE_CONSUMER, QUALITY_SOUVENIER )
					}
				},
				{
					ITEM_WEAPON_TEC9,
					{
						paint_kit_t( 614,PX_XOR( "Fuel Injector" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 791,PX_XOR( "Remote Control" ), GRADE_CLASSIFIED, QUALITY_SOUVENIER ),
						paint_kit_t( 555,PX_XOR( "Re-Entry" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 520,PX_XOR( "Avalanche" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 272,PX_XOR( "Titanium Bit" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 248,PX_XOR( "Red Quartz" ), GRADE_RESTRICTED, QUALITY_SOUVENIER ),
						paint_kit_t( 179,PX_XOR( "Nuclear Threat" ), GRADE_RESTRICTED, QUALITY_SOUVENIER ),
						paint_kit_t( 722,PX_XOR( "Snek-9" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 684,PX_XOR( "Cracked Opal" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 671,PX_XOR( "Cut Out" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 599,PX_XOR( "Ice Cap" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 539,PX_XOR( "Jambiya" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 303,PX_XOR( "Isaac" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 289,PX_XOR( "Sandstorm" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 216,PX_XOR( "Blue Titanium" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 463,PX_XOR( "Terrace" ), GRADE_MILSPEC, QUALITY_DEFAULT ),
						paint_kit_t( 374,PX_XOR( "Toxic" ), GRADE_MILSPEC, QUALITY_SOUVENIER ),
						paint_kit_t( 159,PX_XOR( "Brass" ), GRADE_MILSPEC, QUALITY_SOUVENIER ),
						paint_kit_t( 36,PX_XOR( "Ossified" ), GRADE_MILSPEC, QUALITY_DEFAULT ),
						paint_kit_t( 439,PX_XOR( "Hades" ), GRADE_INDUSTRIAL, QUALITY_DEFAULT ),
						paint_kit_t( 235,PX_XOR( "VariCamo" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 459,PX_XOR( "Bamboo Forest" ), GRADE_CONSUMER, QUALITY_DEFAULT ),
						paint_kit_t( 17,PX_XOR( "Urban DDPAT" ), GRADE_CONSUMER, QUALITY_DEFAULT ),
						paint_kit_t( 242,PX_XOR( "Army Mesh" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 2,PX_XOR( "Groundwater" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 206,PX_XOR( "Tornado" ), GRADE_CONSUMER, QUALITY_DEFAULT )
					}
				},
				{
					ITEM_WEAPON_ZEUS,
					{
						paint_kit_t( 389,PX_XOR( "Fire Elemental" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 591,PX_XOR( "Imperial Dragon" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 184,PX_XOR( "Corticera" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 211,PX_XOR( "Ocean Foam" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 667,PX_XOR( "Woodsman" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 485,PX_XOR( "Handgun" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 246,PX_XOR( "Amber Fade" ), GRADE_RESTRICTED, QUALITY_SOUVENIER ),
						paint_kit_t( 71,PX_XOR( "Scorpion" ), GRADE_RESTRICTED, QUALITY_DEFAULT ),
						paint_kit_t( 700,PX_XOR( "Urban Hazard" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 635,PX_XOR( "Turf" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 550,PX_XOR( "Oceanic" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 515,PX_XOR( "Imperial" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 357,PX_XOR( "Ivory" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 338,PX_XOR( "Pulse" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 275,PX_XOR( "Red FragCam" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 327,PX_XOR( "Chainmail" ), GRADE_MILSPEC, QUALITY_SOUVENIER ),
						paint_kit_t( 32,PX_XOR( "Silver" ), GRADE_MILSPEC, QUALITY_DEFAULT ),
						paint_kit_t( 443,PX_XOR( "Pathfinder" ), GRADE_INDUSTRIAL, QUALITY_DEFAULT ),
						paint_kit_t( 95,PX_XOR( "Grassland" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 346,PX_XOR( "Coach Class" ), GRADE_INDUSTRIAL, QUALITY_DEFAULT ),
						paint_kit_t( 21,PX_XOR( "Granite Marbleized" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 104,PX_XOR( "Grassland Leaves" ), GRADE_INDUSTRIAL, QUALITY_DEFAULT )
					}
				},
				{
					ITEM_WEAPON_P2000,
					{
						paint_kit_t( 696,PX_XOR( "Bloodsport" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 481,PX_XOR( "Nemesis" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 719,PX_XOR( "Powercore" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 536,PX_XOR( "Impire" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 500,PX_XOR( "Special Delivery" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 213,PX_XOR( "Ocean Foam" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 752,PX_XOR( "Fade" ), GRADE_RESTRICTED, QUALITY_SOUVENIER ),
						paint_kit_t( 649,PX_XOR( "Akoben" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 627,PX_XOR( "Cirrus" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 423,PX_XOR( "Armor Core" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 354,PX_XOR( "Urban Hazard" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 11,PX_XOR( "Skulls" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 250,PX_XOR( "Full Stop" ), GRADE_MILSPEC, QUALITY_DEFAULT ),
						paint_kit_t( 28,PX_XOR( "Anodized Navy" ), GRADE_MILSPEC, QUALITY_SOUVENIER ),
						paint_kit_t( 102,PX_XOR( "Whiteout" ), GRADE_MILSPEC, QUALITY_DEFAULT ),
						paint_kit_t( 782,PX_XOR( "Motherboard" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 15,PX_XOR( "Gunsmoke" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 141,PX_XOR( "Orange Peel" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 442,PX_XOR( "Asterion" ), GRADE_CONSUMER, QUALITY_DEFAULT ),
						paint_kit_t( 365,PX_XOR( "Olive Plaid" ), GRADE_CONSUMER, QUALITY_DEFAULT ),
						paint_kit_t( 5,PX_XOR( "Forest DDPAT" ), GRADE_CONSUMER, QUALITY_DEFAULT ),
						paint_kit_t( 245,PX_XOR( "Army Recon" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 209,PX_XOR( "Groundwater" ), GRADE_CONSUMER, QUALITY_DEFAULT )
					}
				},
				{
					ITEM_WEAPON_MP7,
					{
						paint_kit_t( 609,PX_XOR( "Airlock" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 679,PX_XOR( "Goo" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 482,PX_XOR( "Ruby Poison Dart" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 262,PX_XOR( "Rose Iron" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 61,PX_XOR( "Hypnotic" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 39,PX_XOR( "Bulldozer" ), GRADE_RESTRICTED, QUALITY_DEFAULT ),
						paint_kit_t( 715,PX_XOR( "Capillary" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 697,PX_XOR( "Black Sand" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 630,PX_XOR( "Sand Scale" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 549,PX_XOR( "Bioleak" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 403,PX_XOR( "Deadly Poison" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 386,PX_XOR( "Dart" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 448,PX_XOR( "Pandora's Box" ), GRADE_MILSPEC, QUALITY_DEFAULT ),
						paint_kit_t( 368,PX_XOR( "Setting Sun" ), GRADE_MILSPEC, QUALITY_SOUVENIER ),
						paint_kit_t( 329,PX_XOR( "Dark Age" ), GRADE_MILSPEC, QUALITY_SOUVENIER ),
						paint_kit_t( 33,PX_XOR( "Hot Rod" ), GRADE_MILSPEC, QUALITY_SOUVENIER ),
						paint_kit_t( 141,PX_XOR( "Orange Peel" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 755,PX_XOR( "Slide" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 366,PX_XOR( "Green Plaid" ), GRADE_CONSUMER, QUALITY_DEFAULT ),
						paint_kit_t( 100,PX_XOR( "Storm" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 148,PX_XOR( "Sand Dashed" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 199,PX_XOR( "Dry Season" ), GRADE_CONSUMER, QUALITY_DEFAULT )
					}
				},
				{
					ITEM_WEAPON_MP9,
					{
						paint_kit_t( 537,PX_XOR( "Hyper Beast" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 62,PX_XOR( "Bloomstick" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 286,PX_XOR( "Antique" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 716,PX_XOR( "Toy Soldier" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 699,PX_XOR( "Wild Six" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 634,PX_XOR( "Gila" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 356,PX_XOR( "Koi" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 263,PX_XOR( "Rising Skull" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 214,PX_XOR( "Graphite" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 590,PX_XOR( "Exo" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 484,PX_XOR( "Ranger" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 225,PX_XOR( "Ghost Camo" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 191,PX_XOR( "Tempest" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 164,PX_XOR( "Modern Hunter" ), GRADE_MILSPEC, QUALITY_DEFAULT ),
						paint_kit_t( 166,PX_XOR( "Blaze Orange" ), GRADE_MILSPEC, QUALITY_DEFAULT ),
						paint_kit_t( 294,PX_XOR( "Green Apple" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 299,PX_XOR( "Caged Steel" ), GRADE_INDUSTRIAL, QUALITY_DEFAULT ),
						paint_kit_t( 3,PX_XOR( "Candy Apple" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 785,PX_XOR( "Mandrel" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 450,PX_XOR( "Moon in Libra" ), GRADE_CONSUMER, QUALITY_DEFAULT ),
						paint_kit_t( 99,PX_XOR( "Sand Dune" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 170,PX_XOR( "Predator" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 107,PX_XOR( "Polar Mesh" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 25,PX_XOR( "Forest Leaves" ), GRADE_CONSUMER, QUALITY_DEFAULT ),
						paint_kit_t( 158,PX_XOR( "Walnut" ), GRADE_CONSUMER, QUALITY_SOUVENIER )
					}
				},
				{
					ITEM_WEAPON_NOVA,
					{
						paint_kit_t( 678,PX_XOR( "See Ya Later" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 551,PX_XOR( "Asiimov" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 404,PX_XOR( "Muertos" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 388,PX_XOR( "Cartel" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 271,PX_XOR( "Undertow" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 258,PX_XOR( "Mehndi" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 295,PX_XOR( "Franklin" ), GRADE_CLASSIFIED, QUALITY_DEFAULT ),
						paint_kit_t( 668,PX_XOR( "Red Rock" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 501,PX_XOR( "Wingshot" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 358,PX_XOR( "Supernova" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 162,PX_XOR( "Splash" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 749,PX_XOR( "Vino Primo" ), GRADE_RESTRICTED, QUALITY_SOUVENIER ),
						paint_kit_t( 168,PX_XOR( "Nuclear Threat" ), GRADE_RESTRICTED, QUALITY_SOUVENIER ),
						paint_kit_t( 650,PX_XOR( "Ripple" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 592,PX_XOR( "Iron Clad" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 426,PX_XOR( "Valence" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 230,PX_XOR( "Steel Disruption" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 219,PX_XOR( "Hive" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 786,PX_XOR( "Exchanger" ), GRADE_MILSPEC, QUALITY_SOUVENIER ),
						paint_kit_t( 102,PX_XOR( "Whiteout" ), GRADE_MILSPEC, QUALITY_DEFAULT ),
						paint_kit_t( 164,PX_XOR( "Modern Hunter" ), GRADE_MILSPEC, QUALITY_DEFAULT ),
						paint_kit_t( 466,PX_XOR( "Crimson Kimono" ), GRADE_INDUSTRIAL, QUALITY_DEFAULT ),
						paint_kit_t( 373,PX_XOR( "Contamination" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 34,PX_XOR( "Metallic DDPAT" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 207,PX_XOR( "Facets" ), GRADE_INDUSTRIAL, QUALITY_DEFAULT ),
						paint_kit_t( 15,PX_XOR( "Gunsmoke" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 777,PX_XOR( "Facility Draft" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 467,PX_XOR( "Mint Kimono" ), GRADE_CONSUMER, QUALITY_DEFAULT ),
						paint_kit_t( 77,PX_XOR( "Boreal Forest" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 99,PX_XOR( "Sand Dune" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 27,PX_XOR( "Bone Mask" ), GRADE_CONSUMER, QUALITY_SOUVENIER )
					}
				},
				{
					ITEM_WEAPON_P250,
					{
						paint_kit_t( 678,PX_XOR( "See Ya Later" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 551,PX_XOR( "Asiimov" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 404,PX_XOR( "Muertos" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 388,PX_XOR( "Cartel" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 271,PX_XOR( "Undertow" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 258,PX_XOR( "Mehndi" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 295,PX_XOR( "Franklin" ), GRADE_CLASSIFIED, QUALITY_DEFAULT ),
						paint_kit_t( 668,PX_XOR( "Red Rock" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 501,PX_XOR( "Wingshot" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 358,PX_XOR( "Supernova" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 162,PX_XOR( "Splash" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 749,PX_XOR( "Vino Primo" ), GRADE_RESTRICTED, QUALITY_SOUVENIER ),
						paint_kit_t( 168,PX_XOR( "Nuclear Threat" ), GRADE_RESTRICTED, QUALITY_SOUVENIER ),
						paint_kit_t( 650,PX_XOR( "Ripple" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 592,PX_XOR( "Iron Clad" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 426,PX_XOR( "Valence" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 230,PX_XOR( "Steel Disruption" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 219,PX_XOR( "Hive" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 786,PX_XOR( "Exchanger" ), GRADE_MILSPEC, QUALITY_SOUVENIER ),
						paint_kit_t( 102,PX_XOR( "Whiteout" ), GRADE_MILSPEC, QUALITY_DEFAULT ),
						paint_kit_t( 164,PX_XOR( "Modern Hunter" ), GRADE_MILSPEC, QUALITY_DEFAULT ),
						paint_kit_t( 466,PX_XOR( "Crimson Kimono" ), GRADE_INDUSTRIAL, QUALITY_DEFAULT ),
						paint_kit_t( 373,PX_XOR( "Contamination" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 34,PX_XOR( "Metallic DDPAT" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 207,PX_XOR( "Facets" ), GRADE_INDUSTRIAL, QUALITY_DEFAULT ),
						paint_kit_t( 15,PX_XOR( "Gunsmoke" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 777,PX_XOR( "Facility Draft" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 467,PX_XOR( "Mint Kimono" ), GRADE_CONSUMER, QUALITY_DEFAULT ),
						paint_kit_t( 77,PX_XOR( "Boreal Forest" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 99,PX_XOR( "Sand Dune" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 27,PX_XOR( "Bone Mask" ), GRADE_CONSUMER, QUALITY_SOUVENIER )
					}
				},
				{
					ITEM_WEAPON_SCAR20,
					{
						paint_kit_t( 487,PX_XOR( "Cyrex" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 750,PX_XOR( "Integrale" ), GRADE_CLASSIFIED, QUALITY_SOUVENIER ),
						paint_kit_t( 686,PX_XOR( "Phantom" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 613,PX_XOR( "Triarch" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 519,PX_XOR( "Tiger Moth" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 287,PX_XOR( "Pulse" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 39,PX_XOR( "Bulldozer" ), GRADE_RESTRICTED, QUALITY_DEFAULT ),
						paint_kit_t( 702,PX_XOR( "Aloha" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 598,PX_XOR( "Aerial" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 553,PX_XOR( "Atlas" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 186,PX_XOR( "Wave Spray" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 98,PX_XOR( "Ultraviolet" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 28,PX_XOR( "Anodized Navy" ), GRADE_MILSPEC, QUALITY_SOUVENIER ),
						paint_kit_t( 247,PX_XOR( "Damascus Steel" ), GRADE_MILSPEC, QUALITY_SOUVENIER ),
						paint_kit_t( 378,PX_XOR( "Fallout Warning" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 363,PX_XOR( "Traveler" ), GRADE_INDUSTRIAL, QUALITY_DEFAULT ),
						paint_kit_t( 243,PX_XOR( "Gator Mesh" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 298,PX_XOR( "Army Sheen" ), GRADE_CONSUMER, QUALITY_DEFAULT ),
						paint_kit_t( 136,PX_XOR( "Waves Perforated" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 101,PX_XOR( "Tornado" ), GRADE_CONSUMER, QUALITY_DEFAULT )
					}
				},
				{
					ITEM_WEAPON_SG553,
					{
						paint_kit_t( 624,PX_XOR( "Dragonfire" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 222,PX_XOR( "Blood in the Water" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 503,PX_XOR( "Big Iron" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 670,PX_XOR( "Death's Head" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 554,PX_XOR( "Ghost Crusader" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 538,PX_XOR( "Necropos" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 60,PX_XOR( "Dark Water" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 361,PX_XOR( "Abyss" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 304,PX_XOR( "Slashed" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 751,PX_XOR( "Hand Brake" ), GRADE_MILSPEC, QUALITY_SOUVENIER ),
						paint_kit_t( 319,PX_XOR( "Detour" ), GRADE_MILSPEC, QUALITY_SOUVENIER ),
						paint_kit_t( 253,PX_XOR( "Acid Fade" ), GRADE_MILSPEC, QUALITY_SOUVENIER ),
						paint_kit_t( 233,PX_XOR( "Tropical Storm" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 200,PX_XOR( "Mayan Dreams" ), GRADE_INDUSTRIAL, QUALITY_DEFAULT ),
						paint_kit_t( 99,PX_XOR( "Sand Dune" ), GRADE_CONSUMER, QUALITY_DEFAULT ),
						paint_kit_t( 96,PX_XOR( "Blue Spruce" ), GRADE_CONSUMER, QUALITY_SOUVENIER ),
						paint_kit_t( 26,PX_XOR( "Lichen Dashed" ), GRADE_CONSUMER, QUALITY_DEFAULT )
					}
				},
				{
					ITEM_WEAPON_SSG08,
					{
						paint_kit_t( 587,PX_XOR( "Mecha Industries" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 548,PX_XOR( "Chantico's Fire" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 497,PX_XOR( "Golden Coil" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 430,PX_XOR( "Hyper Beast" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 360,PX_XOR( "Cyrex" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 714,PX_XOR( "Nightmare" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 681,PX_XOR( "Leaded Glass" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 644,PX_XOR( "Decimator" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 301,PX_XOR( "Atomic Alloy" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 257,PX_XOR( "Guardian" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 792,PX_XOR( "Control Panel" ), GRADE_CLASSIFIED, QUALITY_SOUVENIER ),
						paint_kit_t( 445,PX_XOR( "Hot Rod" ), GRADE_CLASSIFIED, QUALITY_DEFAULT ),
						paint_kit_t( 326,PX_XOR( "Knight" ), GRADE_CLASSIFIED, QUALITY_SOUVENIER ),
						paint_kit_t( 321,PX_XOR( "Master Piece" ), GRADE_CLASSIFIED, QUALITY_SOUVENIER ),
						paint_kit_t( 631,PX_XOR( "Flashback" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 383,PX_XOR( "Basilisk" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 189,PX_XOR( "Bright Water" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 60,PX_XOR( "Dark Water" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 440,PX_XOR( "Icarus Fell" ), GRADE_RESTRICTED, QUALITY_DEFAULT ),
						paint_kit_t( 254,PX_XOR( "Nitro" ), GRADE_RESTRICTED, QUALITY_SOUVENIER ),
						paint_kit_t( 663,PX_XOR( "Briefing" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 217,PX_XOR( "Blood Tiger" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 235,PX_XOR( "VariCamo" ), GRADE_MILSPEC, QUALITY_SOUVENIER ),
						paint_kit_t( 77,PX_XOR( "Boreal Forest" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER )
					}
				},
				{
					ITEM_WEAPON_M4A1S,
					{
						paint_kit_t( 653,PX_XOR( "Neo-Noir" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 504,PX_XOR( "Kill Confirmed" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 705,PX_XOR( "Cortex" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 339,PX_XOR( "Caiman" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 313,PX_XOR( "Orion" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 221,PX_XOR( "Serum" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 637,PX_XOR( "Cyrex" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 290,PX_XOR( "Guardian" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 183,PX_XOR( "Overgrowth" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 60,PX_XOR( "Dark Water" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 318,PX_XOR( "Road Rash" ), GRADE_RESTRICTED, QUALITY_SOUVENIER ),
						paint_kit_t( 657,PX_XOR( "Blueprint" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 540,PX_XOR( "Lead Conduit" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 489,PX_XOR( "Torque" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 217,PX_XOR( "Blood Tiger" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 277,PX_XOR( "Stainless" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 796,PX_XOR( "Check Engine" ), GRADE_MILSPEC, QUALITY_SOUVENIER ),
						paint_kit_t( 364,PX_XOR( "Business Class" ), GRADE_MILSPEC, QUALITY_DEFAULT ),
						paint_kit_t( 236,PX_XOR( "Night Ops" ), GRADE_MILSPEC, QUALITY_SOUVENIER ),
						paint_kit_t( 454,PX_XOR( "Para Green" ), GRADE_INDUSTRIAL, QUALITY_DEFAULT ),
						paint_kit_t( 332,PX_XOR( "Royal Blue" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 25,PX_XOR( "Forest Leaves" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER )
					}
				},
				{
					ITEM_WEAPON_USPS,
					{
						paint_kit_t( 270,PX_XOR( "Victoria" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 643,PX_XOR( "Xiangliu" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 476,PX_XOR( "Yellow Jacket" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 269,PX_XOR( "The Fuschia Is Now" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 709,PX_XOR( "Eco" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 687,PX_XOR( "Tacticat" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 543,PX_XOR( "Red Astor" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 435,PX_XOR( "Pole Position" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 350,PX_XOR( "Tigris" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 268,PX_XOR( "Tread Plate" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 325,PX_XOR( "Chalice" ), GRADE_RESTRICTED, QUALITY_SOUVENIER ),
						paint_kit_t( 622,PX_XOR( "Polymer" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 602,PX_XOR( "Imprint" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 218,PX_XOR( "Hexane" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 334,PX_XOR( "Twist" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 315,PX_XOR( "Poison Dart" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 12,PX_XOR( "Crimson Web" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 453,PX_XOR( "Emerald" ), GRADE_MILSPEC, QUALITY_DEFAULT ),
						paint_kit_t( 322,PX_XOR( "Nitro" ), GRADE_MILSPEC, QUALITY_SOUVENIER ),
						paint_kit_t( 297,PX_XOR( "Tuxedo" ), GRADE_MILSPEC, QUALITY_DEFAULT ),
						paint_kit_t( 298,PX_XOR( "Army Sheen" ), GRADE_CONSUMER, QUALITY_DEFAULT ),
						paint_kit_t( 366,PX_XOR( "Green Plaid" ), GRADE_CONSUMER, QUALITY_DEFAULT )
					}
				},
				{
					ITEM_WEAPON_CZ75AUTO,
					{
						paint_kit_t( 522,PX_XOR( "Fade" ), GRADE_COVERT, QUALITY_STATTRAK ),
						paint_kit_t( 683,PX_XOR( "Llama Cannon" ), GRADE_CLASSIFIED, QUALITY_STATTRAK ),
						paint_kit_t( 523,PX_XOR( "Amber Fade" ), GRADE_CLASSIFIED, QUALITY_SOUVENIER ),
						paint_kit_t( 595,PX_XOR( "Reboot" ), GRADE_RESTRICTED, QUALITY_STATTRAK ),
						paint_kit_t( 721,PX_XOR( "Survivalist" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 701,PX_XOR( "Grip" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 12,PX_XOR( "Crimson Web" ), GRADE_MILSPEC, QUALITY_STATTRAK ),
						paint_kit_t( 798,PX_XOR( "Nitro" ), GRADE_INDUSTRIAL, QUALITY_SOUVENIER ),
						paint_kit_t( 27,PX_XOR( "Bone Mask" ), GRADE_CONSUMER, QUALITY_SOUVENIER )
					}
				},
				{
					ITEM_WEAPON_R8REVOLVER,
					{
						paint_kit_t( 558,PX_XOR( "Lore" ), GRADE_KNIFE, QUALITY_STATTRAK ),
						paint_kit_t( 0,PX_XOR( "Gamma Doppler" ), GRADE_KNIFE, QUALITY_STATTRAK ),
						paint_kit_t( 573,PX_XOR( "Autotronic" ), GRADE_KNIFE, QUALITY_STATTRAK ),
						paint_kit_t( 563,PX_XOR( "Black Laminate" ), GRADE_KNIFE, QUALITY_STATTRAK ),
						paint_kit_t( 580,PX_XOR( "Freehand" ), GRADE_KNIFE, QUALITY_STATTRAK ),
						paint_kit_t( 578,PX_XOR( "Bright Water" ), GRADE_KNIFE, QUALITY_STATTRAK ),
						paint_kit_t( 413,PX_XOR( "Marble Fade" ), GRADE_KNIFE, QUALITY_STATTRAK ),
						paint_kit_t( 0,PX_XOR( "Doppler" ), GRADE_KNIFE, QUALITY_STATTRAK ),
						paint_kit_t( 409,PX_XOR( "Tiger Tooth" ), GRADE_KNIFE, QUALITY_STATTRAK ),
						paint_kit_t( 98,PX_XOR( "Ultraviolet" ), GRADE_KNIFE, QUALITY_STATTRAK ),
						paint_kit_t( 410,PX_XOR( "Damascus Steel" ), GRADE_KNIFE, QUALITY_STATTRAK ),
						paint_kit_t( 414,PX_XOR( "Rust Coat" ), GRADE_KNIFE, QUALITY_STATTRAK ),
						paint_kit_t( 38,PX_XOR( "Fade" ), GRADE_KNIFE, QUALITY_STATTRAK ),
						paint_kit_t( 59,PX_XOR( "Slaughter" ), GRADE_KNIFE, QUALITY_STATTRAK ),
						paint_kit_t( 44,PX_XOR( "Case Hardened" ), GRADE_KNIFE, QUALITY_STATTRAK ),
						paint_kit_t( 12,PX_XOR( "Crimson Web" ), GRADE_KNIFE, QUALITY_STATTRAK ),
						paint_kit_t( 42,PX_XOR( "Blue Steel" ), GRADE_KNIFE, QUALITY_STATTRAK ),
						paint_kit_t( 43,PX_XOR( "Stained" ), GRADE_KNIFE, QUALITY_STATTRAK ),
						paint_kit_t( 40,PX_XOR( "Night" ), GRADE_KNIFE, QUALITY_STATTRAK ),
						paint_kit_t( 143,PX_XOR( "Urban Masked" ), GRADE_KNIFE, QUALITY_STATTRAK ),
						paint_kit_t( 72,PX_XOR( "Safari Mesh" ), GRADE_KNIFE, QUALITY_STATTRAK ),
						paint_kit_t( 5,PX_XOR( "Forest DDPAT" ), GRADE_KNIFE, QUALITY_STATTRAK ),
						paint_kit_t( 175,PX_XOR( "Scorched" ), GRADE_KNIFE, QUALITY_STATTRAK ),
						paint_kit_t( 77,PX_XOR( "Boreal Forest" ), GRADE_KNIFE, QUALITY_STATTRAK )
					}
				},
				{
					ITEM_WEAPON_KNIFE_BAYONET,
					{
paint_kit_t( 558,PX_XOR( "Lore" ),GRADE_KNIFE,QUALITY_STATTRAK ),
paint_kit_t( 0,PX_XOR( "Gamma Doppler" ),GRADE_KNIFE,QUALITY_STATTRAK ), // todo
paint_kit_t( 573,PX_XOR( "Autotronic" ),GRADE_KNIFE,QUALITY_STATTRAK ),
paint_kit_t( 563,PX_XOR( "Black Laminate" ),GRADE_KNIFE,QUALITY_STATTRAK ),
paint_kit_t( 580,PX_XOR( "Freehand" ),GRADE_KNIFE,QUALITY_STATTRAK ),
paint_kit_t( 578,PX_XOR( "Bright Water" ),GRADE_KNIFE,QUALITY_STATTRAK ),
paint_kit_t( 413,PX_XOR( "Marble Fade" ),GRADE_KNIFE,QUALITY_STATTRAK ),
paint_kit_t( 0,PX_XOR( "Doppler" ),GRADE_KNIFE,QUALITY_STATTRAK ), // todo
paint_kit_t( 409,PX_XOR( "Tiger Tooth" ),GRADE_KNIFE,QUALITY_STATTRAK ),
paint_kit_t( 98,PX_XOR( "Ultraviolet" ),GRADE_KNIFE,QUALITY_STATTRAK ),
paint_kit_t( 410,PX_XOR( "Damascus Steel" ),GRADE_KNIFE,QUALITY_STATTRAK ),
paint_kit_t( 414,PX_XOR( "Rust Coat" ),GRADE_KNIFE,QUALITY_STATTRAK ),
paint_kit_t( 38,PX_XOR( "Fade" ),GRADE_KNIFE,QUALITY_STATTRAK ),
paint_kit_t( 59,PX_XOR( "Slaughter" ),GRADE_KNIFE,QUALITY_STATTRAK ),
paint_kit_t( 44,PX_XOR( "Case Hardened" ),GRADE_KNIFE,QUALITY_STATTRAK ),
paint_kit_t( 12,PX_XOR( "Crimson Web" ),GRADE_KNIFE,QUALITY_STATTRAK ),
paint_kit_t( 42,PX_XOR( "Blue Steel" ),GRADE_KNIFE,QUALITY_STATTRAK ),
paint_kit_t( 43,PX_XOR( "Stained" ),GRADE_KNIFE,QUALITY_STATTRAK ),
paint_kit_t( 40,PX_XOR( "Night" ),GRADE_KNIFE,QUALITY_STATTRAK ),
paint_kit_t( 143,PX_XOR( "Urban Masked" ),GRADE_KNIFE,QUALITY_STATTRAK ),
paint_kit_t( 72,PX_XOR( "Safari Mesh" ),GRADE_KNIFE,QUALITY_STATTRAK ),
paint_kit_t( 5,PX_XOR( "Forest DDPAT" ),GRADE_KNIFE,QUALITY_STATTRAK ),
paint_kit_t( 175,PX_XOR( "Scorched" ),GRADE_KNIFE,QUALITY_STATTRAK ),
paint_kit_t( 77,PX_XOR( "Boreal Forest" ),GRADE_KNIFE,QUALITY_STATTRAK )
					}
				},
				{
					ITEM_WEAPON_KNIFE_FLIP,
					{
						paint_kit_t( 0,PX_XOR( "Gamma Doppler" ),GRADE_KNIFE,QUALITY_STATTRAK ), // todo
						paint_kit_t( 574,PX_XOR( "Autotronic" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 559,PX_XOR( "Lore" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 580,PX_XOR( "Freehand" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 578,PX_XOR( "Bright Water" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 564,PX_XOR( "Black Laminate" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 413,PX_XOR( "Marble Fade" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 409,PX_XOR( "Tiger Tooth" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 0,PX_XOR( "Doppler" ),GRADE_KNIFE,QUALITY_STATTRAK ), // todo
						paint_kit_t( 98,PX_XOR( "Ultraviolet" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 410,PX_XOR( "Damascus Steel" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 414,PX_XOR( "Rust Coat" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 38,PX_XOR( "Fade" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 12,PX_XOR( "Crimson Web" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 59,PX_XOR( "Slaughter" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 44,PX_XOR( "Case Hardened" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 42,PX_XOR( "Blue Steel" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 43,PX_XOR( "Stained" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 40,PX_XOR( "Night" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 143,PX_XOR( "Urban Masked" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 77,PX_XOR( "Boreal Forest" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 5,PX_XOR( "Forest DDPAT" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 72,PX_XOR( "Safari Mesh" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 175,PX_XOR( "Scorched" ),GRADE_KNIFE,QUALITY_STATTRAK )
					}
				},
				{
					ITEM_WEAPON_KNIFE_GUT,
					{
						paint_kit_t( 560,PX_XOR( "Lore" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 575,PX_XOR( "Autotronic" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 0,PX_XOR( "Gamma Doppler" ),GRADE_KNIFE,QUALITY_STATTRAK ), // todo
						paint_kit_t( 565,PX_XOR( "Black Laminate" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 580,PX_XOR( "Freehand" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 578,PX_XOR( "Bright Water" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 98,PX_XOR( "Ultraviolet" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 409,PX_XOR( "Tiger Tooth" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 413,PX_XOR( "Marble Fade" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 0,PX_XOR( "Doppler" ),GRADE_KNIFE,QUALITY_STATTRAK ), // todo
						paint_kit_t( 414,PX_XOR( "Rust Coat" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 410,PX_XOR( "Damascus Steel" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 12,PX_XOR( "Crimson Web" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 42,PX_XOR( "Blue Steel" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 44,PX_XOR( "Case Hardened" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 38,PX_XOR( "Fade" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 59,PX_XOR( "Slaughter" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 72,PX_XOR( "Safari Mesh" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 5,PX_XOR( "Forest DDPAT" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 77,PX_XOR( "Boreal Forest" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 40,PX_XOR( "Night" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 43,PX_XOR( "Stained" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 143,PX_XOR( "Urban Masked" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 175,PX_XOR( "Scorched" ),GRADE_KNIFE,QUALITY_STATTRAK )
					}
				},
				{
					ITEM_WEAPON_KNIFE_KARAMBIT,
					{
						paint_kit_t( 561,PX_XOR( "Lore" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 0,PX_XOR( "Gamma Doppler" ),GRADE_KNIFE,QUALITY_STATTRAK ), // todo 
						paint_kit_t( 576,PX_XOR( "Autotronic" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 566,PX_XOR( "Black Laminate" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 582,PX_XOR( "Freehand" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 578,PX_XOR( "Bright Water" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 413,PX_XOR( "Marble Fade" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 409,PX_XOR( "Tiger Tooth" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 0,PX_XOR( "Doppler" ),GRADE_KNIFE,QUALITY_STATTRAK ), // todo
						paint_kit_t( 410,PX_XOR( "Damascus Steel" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 98,PX_XOR( "Ultraviolet" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 414,PX_XOR( "Rust Coat" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 38,PX_XOR( "Fade" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 59,PX_XOR( "Slaughter" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 12,PX_XOR( "Crimson Web" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 44,PX_XOR( "Case Hardened" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 40,PX_XOR( "Night" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 42,PX_XOR( "Blue Steel" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 43,PX_XOR( "Stained" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 77,PX_XOR( "Boreal Forest" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 143,PX_XOR( "Urban Masked" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 5,PX_XOR( "Forest DDPAT" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 175,PX_XOR( "Scorched" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 72,PX_XOR( "Safari Mesh" ),GRADE_KNIFE,QUALITY_STATTRAK )
					}
				},
				{
					ITEM_WEAPON_KNIFE_M9_BAYONET,
					{
						paint_kit_t( 562,PX_XOR( "Lore" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 577,PX_XOR( "Autotronic" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 0,PX_XOR( "Gamma Doppler" ),GRADE_KNIFE,QUALITY_STATTRAK ), // todo
						paint_kit_t( 581,PX_XOR( "Freehand" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 567,PX_XOR( "Black Laminate" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 579,PX_XOR( "Bright Water" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 413,PX_XOR( "Marble Fade" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 0,PX_XOR( "Doppler" ),GRADE_KNIFE,QUALITY_STATTRAK ), // todo
						paint_kit_t( 414,PX_XOR( "Rust Coat" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 409,PX_XOR( "Tiger Tooth" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 411,PX_XOR( "Damascus Steel" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 98,PX_XOR( "Ultraviolet" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 38,PX_XOR( "Fade" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 59,PX_XOR( "Slaughter" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 44,PX_XOR( "Case Hardened" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 12,PX_XOR( "Crimson Web" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 42,PX_XOR( "Blue Steel" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 40,PX_XOR( "Night" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 43,PX_XOR( "Stained" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 143,PX_XOR( "Urban Masked" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 5,PX_XOR( "Forest DDPAT" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 77,PX_XOR( "Boreal Forest" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 175,PX_XOR( "Scorched" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 72,PX_XOR( "Safari Mesh" ),GRADE_KNIFE,QUALITY_STATTRAK )
					}
				},
				{
					ITEM_WEAPON_KNIFE_TACTICAL,
					{
						paint_kit_t( 0,PX_XOR( "Doppler" ),GRADE_KNIFE,QUALITY_STATTRAK ), // todo
						paint_kit_t( 413,PX_XOR( "Marble Fade" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 409,PX_XOR( "Tiger Tooth" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 411,PX_XOR( "Damascus Steel" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 620,PX_XOR( "Ultraviolet" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 414,PX_XOR( "Rust Coat" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 44,PX_XOR( "Case Hardened" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 38,PX_XOR( "Fade" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 12,PX_XOR( "Crimson Web" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 59,PX_XOR( "Slaughter" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 42,PX_XOR( "Blue Steel" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 77,PX_XOR( "Boreal Forest" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 40,PX_XOR( "Night" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 43,PX_XOR( "Stained" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 175,PX_XOR( "Scorched" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 143,PX_XOR( "Urban Masked" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 5,PX_XOR( "Forest DDPAT" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 72,PX_XOR( "Safari Mesh" ),GRADE_KNIFE,QUALITY_STATTRAK )
					}
				},
				{
					ITEM_WEAPON_KNIFE_FALCHION,
					{
						paint_kit_t( 414,PX_XOR( "Rust Coat" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 413,PX_XOR( "Marble Fade" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 409,PX_XOR( "Tiger Tooth" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 0,PX_XOR( "Doppler" ),GRADE_KNIFE,QUALITY_STATTRAK ), // todo
						paint_kit_t( 621,PX_XOR( "Ultraviolet" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 411,PX_XOR( "Damascus Steel" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 38,PX_XOR( "Fade" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 59,PX_XOR( "Slaughter" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 12,PX_XOR( "Crimson Web" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 44,PX_XOR( "Case Hardened" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 42,PX_XOR( "Blue Steel" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 40,PX_XOR( "Night" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 143,PX_XOR( "Urban Masked" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 77,PX_XOR( "Boreal Forest" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 175,PX_XOR( "Scorched" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 43,PX_XOR( "Stained" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 5,PX_XOR( "Forest DDPAT" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 72,PX_XOR( "Safari Mesh" ),GRADE_KNIFE,QUALITY_STATTRAK )
					}
				},
				{
					ITEM_WEAPON_KNIFE_SURVIVAL_BOWIE,
					{
						paint_kit_t( 414,PX_XOR( "Rust Coat" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 413,PX_XOR( "Marble Fade" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 0,PX_XOR( "Doppler" ),GRADE_KNIFE,QUALITY_STATTRAK ), // todo
						paint_kit_t( 409,PX_XOR( "Tiger Tooth" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 98,PX_XOR( "Ultraviolet" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 411,PX_XOR( "Damascus Steel" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 44,PX_XOR( "Case Hardened" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 38,PX_XOR( "Fade" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 5,PX_XOR( "Forest DDPAT" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 59,PX_XOR( "Slaughter" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 12,PX_XOR( "Crimson Web" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 40,PX_XOR( "Night" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 42,PX_XOR( "Blue Steel" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 43,PX_XOR( "Stained" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 77,PX_XOR( "Boreal Forest" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 72,PX_XOR( "Safari Mesh" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 143,PX_XOR( "Urban Masked" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 175,PX_XOR( "Scorched" ),GRADE_KNIFE,QUALITY_STATTRAK )
					}
				},
				{
					ITEM_WEAPON_KNIFE_BUTTERFLY,
					{
					    paint_kit_t( 0,PX_XOR( "Doppler" ),GRADE_KNIFE,QUALITY_STATTRAK ), // todo
						paint_kit_t( 413,PX_XOR( "Marble Fade" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 409,PX_XOR( "Tiger Tooth" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 411,PX_XOR( "Damascus Steel" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 98,PX_XOR( "Ultraviolet" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 414,PX_XOR( "Rust Coat" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 38,PX_XOR( "Fade" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 59,PX_XOR( "Slaughter" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 12,PX_XOR( "Crimson Web" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 44,PX_XOR( "Case Hardened" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 42,PX_XOR( "Blue Steel" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 40,PX_XOR( "Night" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 77,PX_XOR( "Boreal Forest" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 43,PX_XOR( "Stained" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 175,PX_XOR( "Scorched" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 5,PX_XOR( "Forest DDPAT" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 72,PX_XOR( "Safari Mesh" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 143,PX_XOR( "Urban Masked" ),GRADE_KNIFE,QUALITY_STATTRAK )
					}
				},
				{
					ITEM_WEAPON_KNIFE_SHADOW_DAGGERS,
					{
						paint_kit_t( 0,PX_XOR( "Doppler" ),GRADE_KNIFE,QUALITY_STATTRAK ), // todo
						paint_kit_t( 413,PX_XOR( "Marble Fade" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 409,PX_XOR( "Tiger Tooth" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 414,PX_XOR( "Rust Coat" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 98,PX_XOR( "Ultraviolet" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 411,PX_XOR( "Damascus Steel" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 38,PX_XOR( "Fade" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 12,PX_XOR( "Crimson Web" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 59,PX_XOR( "Slaughter" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 42,PX_XOR( "Blue Steel" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 40,PX_XOR( "Night" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 44,PX_XOR( "Case Hardened" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 43,PX_XOR( "Stained" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 5,PX_XOR( "Forest DDPAT" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 143,PX_XOR( "Urban Masked" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 175,PX_XOR( "Scorched" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 72,PX_XOR( "Safari Mesh" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 77,PX_XOR( "Boreal Forest" ),GRADE_KNIFE,QUALITY_STATTRAK )
					}
				},
				{
					ITEM_WEAPON_KNIFE_URSUS,
					{
						paint_kit_t( 38,PX_XOR( "Fade" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 59,PX_XOR( "Slaughter" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 43,PX_XOR( "Stained" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 735,PX_XOR( "Night Stripe" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 12,PX_XOR( "Crimson Web" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 42,PX_XOR( "Blue Steel" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 143,PX_XOR( "Urban Masked" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 44,PX_XOR( "Case Hardened" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 5,PX_XOR( "Forest DDPAT" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 72,PX_XOR( "Safari Mesh" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 175,PX_XOR( "Scorched" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 77,PX_XOR( "Boreal Forest" ),GRADE_KNIFE,QUALITY_STATTRAK )
					}
				},
				{
					ITEM_WEAPON_KNIFE_NAVAJA,
					{
						paint_kit_t( 735,PX_XOR( "Night Stripe" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 38,PX_XOR( "Fade" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 59,PX_XOR( "Slaughter" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 12,PX_XOR( "Crimson Web" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 77,PX_XOR( "Boreal Forest" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 44,PX_XOR( "Case Hardened" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 43,PX_XOR( "Stained" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 42,PX_XOR( "Blue Steel" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 72,PX_XOR( "Safari Mesh" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 143,PX_XOR( "Urban Masked" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 5,PX_XOR( "Forest DDPAT" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 175,PX_XOR( "Scorched" ),GRADE_KNIFE,QUALITY_STATTRAK )
					}
				},
				{
					ITEM_WEAPON_KNIFE_STILLETTO,
					{
						paint_kit_t( 12,PX_XOR( "Crimson Web" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 43,PX_XOR( "Stained" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 38,PX_XOR( "Fade" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 42,PX_XOR( "Blue Steel" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 175,PX_XOR( "Scorched" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 44,PX_XOR( "Case Hardened" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 59,PX_XOR( "Slaughter" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 735,PX_XOR( "Night Stripe" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 77,PX_XOR( "Boreal Forest" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 5,PX_XOR( "Forest DDPAT" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 143,PX_XOR( "Urban Masked" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 72,PX_XOR( "Safari Mesh" ),GRADE_KNIFE,QUALITY_STATTRAK )
					}
				},
				{
					ITEM_WEAPON_KNIFE_TALON,
					{
						paint_kit_t( 38,PX_XOR( "Fade" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 143,PX_XOR( "Urban Masked" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 59,PX_XOR( "Slaughter" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 44,PX_XOR( "Case Hardened" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 12,PX_XOR( "Crimson Web" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 42,PX_XOR( "Blue Steel" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 735,PX_XOR( "Night Stripe" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 43,PX_XOR( "Stained" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 77,PX_XOR( "Boreal Forest" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 5,PX_XOR( "Forest DDPAT" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 175,PX_XOR( "Scorched" ),GRADE_KNIFE,QUALITY_STATTRAK ),
						paint_kit_t( 72,PX_XOR( "Safari Mesh" ),GRADE_KNIFE,QUALITY_STATTRAK )
					}
				}
			};

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

		void PX_API UpdateModelIndicies( )
		{
			static auto bUpdated = false;

			if ( !pEngineClient->IsInGame( ) )
			{
				bUpdated = false;
				return;
			}

			if ( bUpdated
				 || pClientState->m_nSignonState != SIGNONSTATE_FULL )
				return;

			mpModelIndicies = decltype( mpModelIndicies )
			{
				{ ITEM_WEAPON_FLASHBANG, pModelInfo->GetModelIndex( PX_XOR( "models/Weapons/w_eq_flashbang_dropped.mdl" ) ) },
				{ ITEM_WEAPON_HEGRENADE, pModelInfo->GetModelIndex( PX_XOR( "models/Weapons/w_eq_fraggrenade_dropped.mdl" ) ) },
				{ ITEM_WEAPON_CTKNIFE, pModelInfo->GetModelIndex( PX_XOR( "models/weapons/v_knife_default_ct.mdl" ) ) },
				{ ITEM_WEAPON_TKNIFE, pModelInfo->GetModelIndex( PX_XOR( "models/weapons/v_knife_default_t.mdl" ) ) },
				{ ITEM_WEAPON_KNIFE_BAYONET, pModelInfo->GetModelIndex( PX_XOR( "models/weapons/v_knife_bayonet.mdl" ) ) },
				{ ITEM_WEAPON_KNIFE_FLIP, pModelInfo->GetModelIndex( PX_XOR( "models/weapons/v_knife_flip.mdl" ) ) },
				{ ITEM_WEAPON_KNIFE_GUT, pModelInfo->GetModelIndex( PX_XOR( "models/weapons/v_knife_gut.mdl" ) ) },
				{ ITEM_WEAPON_KNIFE_KARAMBIT, pModelInfo->GetModelIndex( PX_XOR( "models/weapons/v_knife_karam.mdl" ) ) },
				{ ITEM_WEAPON_KNIFE_M9_BAYONET, pModelInfo->GetModelIndex( PX_XOR( "models/weapons/v_knife_m9_bay.mdl" ) ) },
				{ ITEM_WEAPON_KNIFE_TACTICAL, pModelInfo->GetModelIndex( PX_XOR( "models/weapons/v_knife_tactical.mdl" ) ) },
				{ ITEM_WEAPON_KNIFE_FALCHION, pModelInfo->GetModelIndex( PX_XOR( "models/weapons/v_knife_falchion_advanced.mdl" ) ) },
				{ ITEM_WEAPON_KNIFE_SURVIVAL_BOWIE, pModelInfo->GetModelIndex( PX_XOR( "models/weapons/v_knife_survival_bowie.mdl" ) ) },
				{ ITEM_WEAPON_KNIFE_BUTTERFLY, pModelInfo->GetModelIndex( PX_XOR( "models/weapons/v_knife_butterfly.mdl" ) ) },
				{ ITEM_WEAPON_KNIFE_SHADOW_DAGGERS, pModelInfo->GetModelIndex( PX_XOR( "models/weapons/v_knife_push.mdl" ) ) },
				{ ITEM_WEAPON_KNIFE_URSUS, pModelInfo->GetModelIndex( PX_XOR( "models/weapons/v_knife_ursus.mdl" ) ) },
				{ ITEM_WEAPON_KNIFE_NAVAJA, pModelInfo->GetModelIndex( PX_XOR( "models/weapons/v_knife_gypsy_jackknife.mdl") ) },
				{ ITEM_WEAPON_KNIFE_STILLETTO, pModelInfo->GetModelIndex( PX_XOR( "models/weapons/v_knife_stiletto.mdl" ) ) },
				{ ITEM_WEAPON_KNIFE_TALON, pModelInfo->GetModelIndex( PX_XOR( "models/weapons/v_knife_widowmaker.mdl" ) ) },
				{ ITEM_GLOVE_BLOODHOUND, pModelInfo->GetModelIndex( PX_XOR( "models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound.mdl" ) ) },
				{ ITEM_GLOVE_SPORTY, pModelInfo->GetModelIndex( PX_XOR( "models/weapons/v_models/arms/glove_sporty/v_glove_sporty.mdl" ) ) },
				{ ITEM_GLOVE_DRIVER, pModelInfo->GetModelIndex( PX_XOR( "models/weapons/v_models/arms/glove_slick/v_glove_slick.mdl" ) ) },
				{ ITEM_GLOVE_HAND_WRAP, pModelInfo->GetModelIndex( PX_XOR( "models/weapons/v_models/arms/glove_handwrap_leathery/v_glove_handwrap_leathery.mdl" ) ) },
				{ ITEM_GLOVE_MOTORCYCLE, pModelInfo->GetModelIndex( PX_XOR( "models/weapons/v_models/arms/glove_motorcycle/v_glove_motorcycle.mdl" ) ) },
				{ ITEM_GLOVE_SPECIALIST, pModelInfo->GetModelIndex( PX_XOR( "models/weapons/v_models/arms/glove_specialist/v_glove_specialist.mdl" )) },
				{ ITEM_GLOVE_HYDRA, pModelInfo->GetModelIndex( PX_XOR( "models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound_hydra.mdl" ) ) }
			};
		}

		int PX_API GetModelIndex( short sItemDefIndex )
		{
			const auto pSecond = mpModelIndicies.find( sItemDefIndex );
			if ( pSecond != mpModelIndicies.end( ) )
				return pSecond->second;
			return 0;
		}

		int PX_API GetModelIndex( cstr_t szModel )
		{
			const auto pFirst = mpItemDefinitionIndicies.find( szModel );
			if( pFirst != mpItemDefinitionIndicies.end( ) )
				return GetModelIndex( pFirst->second );
			return 0;
		}

		short PX_API GetDefinitionIndex( int iModelIndex )
		{
			for ( const auto& iterator : mpModelIndicies )
				if ( iterator.second == iModelIndex )
					return iterator.first;
			return 0;
		}

		int PX_API GetItemDefinitionIndex( cstr_t szName )
		{
			const auto pFirst = mpItemDefinitionIndicies.find( szName );
			if ( pFirst != mpItemDefinitionIndicies.end( ) )
				return pFirst->second;
			return 0;
		}
	}
}
