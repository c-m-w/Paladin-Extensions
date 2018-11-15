/// Interfaces.hpp

#pragma once

namespace PX::Information
{
	extern nlohmann::json jsMemoryInformation;

	bool PX_API InitializeInformation( );

	namespace Memory
	{
		bool PX_API Setup( );

		namespace VirtualTableIndicies
		{
			// Device
			PX_DEF uBeginScene = 41u;
			PX_DEF uEndScene = 42u;
			PX_DEF uReset = 16u;

			// Client Base
			PX_DEF uCreateMove = 22u;
			PX_DEF uFrameStageNotify = 37u;

			// Client Mode
			PX_DEF uOverrideView = 18u;
			PX_DEF uGetViewmodelFOV = 35u;
			PX_DEF uDoPostScreenEffects = 44u;

			// Surface
			PX_DEF uLockCursor = 67u;

			// Panel
			PX_DEF uPaintTraverse = 41u;

			// ModelRender
			PX_DEF uDrawModelExecute = 21u;

			// View Render
			PX_DEF uSceneBegin = 8u;
			PX_DEF uSceneEnd = 9u;

			// Engine Sound
			PX_DEF uEmitSoundATT = 5u;

			// CBaseEntity
			PX_DEF uIsPlayer = 152u;
			PX_DEF uIsWeapon = 160u;

			// CBaseCombatWeapon
			PX_DEF uGetInaccuracy = 467u;
			PX_DEF uGetSpread = 436u;
			PX_DEF uUpdateAccuracyPenalty = 468u;
		}

		namespace Offsets
		{
			PX_DEF ptrBombTimer = 0x297C;
			PX_DEF ptrDefuseTimer = 0x2994;
		}
	}
	
	namespace Modules
	{
		PX_SDK Types::str_t strCreateInterfaceName = PX_XOR( "CreateInterface" );
		struct SModule: Types::module_t
		{
			CreateInterfaceFn ciFactory { };

			bool Setup( Types::wstr_t wstrModule );
		};

		bool PX_API Setup( );

		PX_SDK SModule mEngine;
		PX_SDK SModule mClient;
		PX_SDK SModule mDirectX;
		PX_SDK SModule mOverlay;
		PX_SDK SModule mVGUI;
		PX_SDK SModule mVGUI2;
		PX_SDK SModule mInput;
		PX_SDK SModule mMaterialSystem;
		PX_SDK SModule mValveStandardLibrary;
		PX_SDK SModule mLocalize;
	}

	namespace Pointers
	{
		bool PX_API FindPointers( );

		PX_SDK bool* pSendPackets = nullptr; // Only modify in CreateMove
		PX_SDK CGlobalVarsBase* pGlobalVariables = nullptr;
		PX_SDK CClientState* pClientState = nullptr;

		PX_SDK IDirect3DDevice9* pDevice = nullptr;
		PX_SDK IBaseClientDLL* pClientBase = nullptr;
		PX_SDK IClientMode* pClientMode = nullptr;
		PX_SDK CGlowObjectManager* pGlowObjectManager = nullptr;
		PX_SDK IInputSystem* pInputSystem = nullptr;
		PX_SDK IVEngineClient* pEngineClient = nullptr;
		PX_SDK ISurface* pSurface = nullptr;
		PX_SDK IPanel* pPanel = nullptr;
		PX_SDK IClientEntityList* pEntityList = nullptr;
		PX_SDK IEngineTrace* pEngineTrace = nullptr;
		PX_SDK IVModelInfoClient* pModelInfo = nullptr;
		PX_SDK CInput* pInput = nullptr;
		PX_SDK IVModelRender* pModelRender = nullptr;
		PX_SDK IMaterialSystem* pMaterialSystem = nullptr;
		PX_SDK IVRenderView* pEngineRenderView = nullptr;
		PX_SDK ICvar* pConVar = nullptr;
		PX_SDK ILocalize* pLocalize = nullptr;
		PX_SDK IGameEventManager2* pEvents = nullptr;
		PX_SDK IMoveHelperServer* pMoveHelper = nullptr;
		PX_SDK IGameMovement* pGameMovement = nullptr;
		PX_SDK IPrediction* pPrediction = nullptr;
		PX_SDK IEngineSound* pEngineSound = nullptr;
		PX_SDK IViewRenderBeams* pRenderBeams = nullptr;
	}

	namespace NetworkedVariableManager // http://www.bailopan.net/table_dump.txt
	{
		struct networked_variable_table_t
		{
			Types::cstr_t szName { };
			RecvProp* pProp { };
			Types::ptr_t ptrOffset { };
			std::vector< RecvProp* > vecChildProps;
			std::vector< networked_variable_table_t > vecChildTables;

			networked_variable_table_t( ) = default; // review why even have constructors here? just use initializer lists
			networked_variable_table_t( Types::cstr_t _szName, RecvProp* _pProp = nullptr, Types::ptr_t _ptrOffset = 0u ):
				szName( _szName ), pProp( _pProp ), ptrOffset( _ptrOffset ) { }
		};

		PX_SDK std::vector< networked_variable_table_t > vecNetworkedVariables { };

		bool PX_API FindNetworkedVariables( );
		Types::ptr_t PX_API FindOffset( Types::cstr_t szTable, Types::cstr_t szVariable );
	}

	namespace Other
	{
		struct paint_kit_t
		{
			int iIdentifier;
			std::string strName;
			int iGrade;
			int iQuality;

			paint_kit_t( ) = default;
			paint_kit_t( int i, std::string s, int g = GRADE_DEFAULT, int q = -1 ): iIdentifier( i ), strName( s ), iGrade(g), iQuality( -1 )
			{ }
		};

		bool PX_API RetrievePaintKits( );
		std::vector< paint_kit_t > PX_API FindPaintKit( int iIndex );
		std::vector< paint_kit_t > PX_API FindPaintKit( Types::wcstr_t wszName );
		std::vector< paint_kit_t > PX_API FindPaintKit( Types::cstr_t szName );
		std::vector< paint_kit_t > PX_API GetWeaponKits( short sIndex );

		PX_SDK std::vector< paint_kit_t > vecPaintKits;

		// Models
		void PX_API UpdateModelIndicies( );
		int PX_API GetModelIndex( short sItemDefIndex );
		int PX_API GetModelIndex( Types::cstr_t szName );
		short PX_API GetDefinitionIndex( int iModelIndex );
		int PX_API GetItemDefinitionIndex( Types::cstr_t szName );
	}
}
