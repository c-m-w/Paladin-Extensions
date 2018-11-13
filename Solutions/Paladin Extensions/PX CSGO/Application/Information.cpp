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

				{ 38, ( "Fade [Knife/Glock]" ) },
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
				{ 232, ( "Crimson Web [Deagle/SCAR]" ) },
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
				{ 410, ( "Damascus Steel [Broght??]" ) }, // todo review texture
				{ 411, ( "Damascus Steel [Dark??]" ) },

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

			//std::map< short /* item def index */, std::vector< paint_kit_t > /* applicable kits */ > mpModelIndicies
			//{
			//	{
			//		ITEM_WEAPON_DEAGLE,
			//		{
			//			//paint_kit_t( ,  )
			//		}
			//	}
			//};

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
