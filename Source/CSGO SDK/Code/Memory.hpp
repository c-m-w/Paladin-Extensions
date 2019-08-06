/// Memory.hpp

#pragma once

namespace Memory
{
	struct module_info_t
	{
		image_info_t _Module = nullptr;
		CreateInterfaceFn _CreateInterface = nullptr;

		operator HMODULE( ) const;
		template< typename _t > bool operator( )( const char* szInterface, _t* pOutput ) const;

		bool Valid( );
	};

	struct networked_variable_table_t
	{
		const char* szName = nullptr;
		RecvProp* pProp = nullptr;
		std::uintptr_t ptrOffset = 0;
		std::vector< RecvProp* > vecChildProps;
		std::vector< networked_variable_table_t > vecChildTables;

		networked_variable_table_t( ) = default;
		networked_variable_table_t( const char* szName, RecvProp* _pProp = nullptr, std::uintptr_t ptrOffset = 0u ):
			szName( szName ), pProp( pProp ), ptrOffset( ptrOffset )
		{ }
	};

	enum EModule
	{
		MODULE_ENGINE,
		MODULE_CLIENT,
		MODULE_D3D9,
		MODULE_OVERLAY,
		MODULE_VGUI,
		MODULE_VGUI2,
		MODULE_INPUT,
		MODULE_MATERIAL_SYSTEM,
		MODULE_VSTD,
		MODULE_LOCALIZE,
		MODULE_FILESYSTEM,
		MODULE_MAX
	};

	enum EInterface
	{
		INTERFACE_GLOBAL_VARS,
		INTERFACE_CLIENT_STATE,
		INTERFACE_DEVICE,
		INTERFACE_CLIENT_BASE,
		INTERFACE_CLIENT_MODE,
		INTERFACE_GLOW_OBJECT_MANAGER,
		INTERFACE_INPUT_SYSTEM,
		INTERFACE_ENGINE_CLIENT,
		INTERFACE_SURFACE,
		INTERFACE_PANEL,
		INTERFACE_ENTITY_LIST,
		INTERFACE_ENGINE_TRACE,
		INTERFACE_MODEL_INFO,
		INTERFACE_INPUT,
		INTERFACE_MODEL_RENDER,
		INTERFACE_MATERIAL_SYSTEM,
		INTERFACE_ENGINE_RENDER_VIEW,
		INTERFACE_CONVAR,
		INTERFACE_LOCALIZE,
		INTERFACE_EVENTS,
		INTERFACE_MOVE_HELPER,
		INTERFACE_GAME_MOVEMENT,
		INTERFACE_PREDICTION,
		INTERFACE_ENGINE_SOUND,
		INTERFACE_RENDER_BEAMS,
		INTERFACE_FILE_SYSTEM,
		INTERFACE_MAX
	};

	enum EFunction
	{
		FUNCTION_BEGIN_SCENE,
		FUNCTION_END_SCENE,
		FUNCTION_RESET,
		FUNCTION_CREATE_MOVE,
		FUNCTION_FRAME_STAGE_NOTIFY,
		FUNCTION_OVERRIDE_VIEW,
		FUNCTION_GET_VIEWMODEL_FOV,
		FUNCTION_DO_POST_SCREEN_EFFECTS,
		FUNCTION_LOCK_CURSOR,
		FUNCTION_PAINT_TRAVERSE,
		FUNCTION_DRAW_MODEL_EXECUTE,
		FUNCTION_SCENE_BEGIN,
		FUNCTION_SCENE_END,
		FUNCTION_EMIT_SOUND_ATT,
		FUNCTION_IS_PLAYER,
		FUNCTION_IS_WEAPON,
		FUNCTION_GET_INACCURACY,
		FUNCTION_GET_SPREAD,
		FUNCTION_UPDATE_ACCURACY_PENALTY,
		FUNCTION_MAX
	};

	inline module_info_t _Modules[ MODULE_MAX ] { };
	inline module_info_t& mEngine = _Modules[ MODULE_ENGINE ];
	inline module_info_t& mClient = _Modules[ MODULE_CLIENT ];
	inline module_info_t& mDirectX = _Modules[ MODULE_D3D9 ];
	inline module_info_t& mOverlay = _Modules[ MODULE_OVERLAY ];
	inline module_info_t& mVGUI = _Modules[ MODULE_VGUI ];
	inline module_info_t& mVGUI2 = _Modules[ MODULE_VGUI2 ];
	inline module_info_t& mInput = _Modules[ MODULE_INPUT ];
	inline module_info_t& mMaterialSystem = _Modules[ MODULE_MATERIAL_SYSTEM ];
	inline module_info_t& mValveStandardLibrary = _Modules[ MODULE_VSTD ];
	inline module_info_t& mLocalize = _Modules[ MODULE_LOCALIZE ];
	inline module_info_t& mFileSystem = _Modules[ MODULE_FILESYSTEM ];

	inline void* pInterfaces[ INTERFACE_MAX ] { };
	inline CGlobalVarsBase*& pGlobalVariables		= *reinterpret_cast< CGlobalVarsBase** >( pInterfaces[ INTERFACE_GLOBAL_VARS ] );
	inline CClientState*& pClientState				= *reinterpret_cast< CClientState** >( pInterfaces[ INTERFACE_CLIENT_STATE ] );
	inline IDirect3DDevice9*& pDevice				= *reinterpret_cast< IDirect3DDevice9** >( pInterfaces[ INTERFACE_DEVICE ] );
	inline IBaseClientDLL*& pClientBase				= *reinterpret_cast< IBaseClientDLL** >( pInterfaces[ INTERFACE_CLIENT_BASE ] );
	inline IClientMode*& pClientMode				= *reinterpret_cast< IClientMode** >( &pInterfaces[ INTERFACE_CLIENT_MODE ] );
	inline CGlowObjectManager*& pGlowObjectManager	= *reinterpret_cast< CGlowObjectManager** >( pInterfaces[ INTERFACE_GLOW_OBJECT_MANAGER ] );
	inline IInputSystem*& pInputSystem				= *reinterpret_cast< IInputSystem** >( pInterfaces[ INTERFACE_INPUT_SYSTEM ] );
	inline IVEngineClient*& pEngineClient			= *reinterpret_cast< IVEngineClient** >( pInterfaces[ INTERFACE_ENGINE_CLIENT ] );
	inline ISurface*& pSurface						= *reinterpret_cast< ISurface** >( &pInterfaces[ INTERFACE_SURFACE ] );
	inline IPanel*& pPanel							= *reinterpret_cast< IPanel** >( &pInterfaces[ INTERFACE_PANEL ] );
	inline IClientEntityList*& pEntityList			= *reinterpret_cast< IClientEntityList** >( pInterfaces[ INTERFACE_ENTITY_LIST ] );
	inline IEngineTrace*& pEngineTrace				= *reinterpret_cast< IEngineTrace** >( pInterfaces[ INTERFACE_ENGINE_TRACE ] );
	inline IVModelInfoClient*& pModelInfo			= *reinterpret_cast< IVModelInfoClient** >( pInterfaces[ INTERFACE_MODEL_INFO ] );
	inline CInput*& pInput							= *reinterpret_cast< CInput** >( &pInterfaces[ INTERFACE_INPUT ] );
	inline IVModelRender*& pModelRender				= *reinterpret_cast< IVModelRender** >( pInterfaces[ INTERFACE_MODEL_RENDER ] );
	inline IMaterialSystem*& pMaterialSystem		= *reinterpret_cast< IMaterialSystem** >( pInterfaces[ INTERFACE_MATERIAL_SYSTEM ] );
	inline IVRenderView*& pEngineRenderView			= *reinterpret_cast< IVRenderView** >( pInterfaces[ INTERFACE_ENGINE_RENDER_VIEW ] );
	inline ICvar*& pConVar							= *reinterpret_cast< ICvar** >( &pInterfaces[ INTERFACE_CONVAR ] );
	inline ILocalize*& pLocalize					= *reinterpret_cast< ILocalize** >( &pInterfaces[ INTERFACE_LOCALIZE ] );
	inline IGameEventManager2*& pEvents				= *reinterpret_cast< IGameEventManager2** >( pInterfaces[ INTERFACE_EVENTS ] );
	inline IMoveHelperServer*& pMoveHelper			= *reinterpret_cast< IMoveHelperServer** >( pInterfaces[ INTERFACE_MOVE_HELPER ] );
	inline IGameMovement*& pGameMovement			= *reinterpret_cast< IGameMovement** >( pInterfaces[ INTERFACE_GAME_MOVEMENT ] );
	inline IPrediction*& pPrediction				= *reinterpret_cast< IPrediction** >( &pInterfaces[ INTERFACE_PREDICTION ] );
	inline IEngineSound*& pEngineSound				= *reinterpret_cast< IEngineSound** >( pInterfaces[ INTERFACE_ENGINE_SOUND ] );
	inline IViewRenderBeams*& pRenderBeams			= *reinterpret_cast< IViewRenderBeams** >( pInterfaces[ INTERFACE_RENDER_BEAMS ] );
	inline IFileSystem*& pFileSystem				= *reinterpret_cast< IFileSystem** >( &pInterfaces[ INTERFACE_FILE_SYSTEM ] );

	unsigned uFunctionIndices[ FUNCTION_MAX ] { };

	inline std::vector< networked_variable_table_t > vecNetworkedVariables { };

	inline const std::string strCreateInterfaceIdentifier = ENC( "Create Interface Import" );
	inline const std::string strModuleIdentifier = ENC( "Modules" );
	inline const std::string strVersionIdentifier = ENC( "Version" );
	inline const std::string strPatternIdentifier = ENC( "Pattern" );
	inline const std::string strSignatureIdentifier = ENC( "Signature" );
	inline const std::string strSignatureOffsetIdentifier = ENC( "Offset" );
	inline const std::string strFunctionIndexIdentifier = ENC( "Function" );

#if defined _DEBUG

	struct pattern_info_t
	{
		EInterface _Interface = INTERFACE_GLOBAL_VARS;
		EModule _Module = MODULE_ENGINE;
		std::string strPattern { };
		std::uintptr_t ptrOffset = 0u;
	};

	struct version_info_t
	{
		EInterface _Interface = INTERFACE_GLOBAL_VARS;
		EModule _Module = MODULE_ENGINE;
		std::string strVersion { };
	};

	inline const std::string strCreateInterface = ENC( "CreateInterface" );

	inline const std::string strModules[ MODULE_MAX ]
	{
		ENC( "engine.dll" ),
		ENC( "client_panorama.dll" ),
		ENC( "shaderapidx9.dll" ),
		ENC( "GameOverlayRenderer.dll" ),
		ENC( "vguimatsurface.dll" ),
		ENC( "vgui2.dll" ),
		ENC( "inputsystem.dll" ),
		ENC( "materialsystem.dll" ),
		ENC( "vstdlib.dll" ),
		ENC( "localize.dll" ),
		ENC( "filesystem_stdio.dll" )
	};

	inline const std::vector< pattern_info_t > vecInterfacePatterns
	{
		{ INTERFACE_GLOBAL_VARS, MODULE_CLIENT, ENC( "A1 ? ? ? ? 5E 8B 40 10" ), 1 },
		{ INTERFACE_CLIENT_STATE, MODULE_ENGINE, ENC( "A1 ? ? ? ? 8B 80 ? ? ? ? C3" ), 1 },
		{ INTERFACE_DEVICE, MODULE_D3D9, ENC( "A1 ? ? ? ? 50 8B 08 FF 51 0C" ), 1 },
		{ INTERFACE_CLIENT_MODE, MODULE_CLIENT, ENC( "A1 ? ? ? ? 8B 80 ? ? ? ? 5D" ), 1 },
		{ INTERFACE_GLOW_OBJECT_MANAGER, MODULE_CLIENT, ENC( "0F 11 05 ? ? ? ? 83 C8 01" ), 1 },
		{ INTERFACE_INPUT, MODULE_CLIENT, ENC( "B9 ? ? ? ? 8B 40 38 FF D0 84 C0 0F 85" ), 1 },
		{ INTERFACE_MOVE_HELPER, MODULE_CLIENT, ENC( "8B 0D ? ? ? ? 8B 46 08 68" ), 2 },
		{ INTERFACE_RENDER_BEAMS, MODULE_CLIENT, ENC( "B9 ? ? ? ? A1 ? ? ? ? FF 10 A1 ? ? ? ? B9" ), 1 }
	};
	inline const std::vector< version_info_t > vecVersions
	{
		{ INTERFACE_CLIENT_BASE, MODULE_CLIENT, ENC( "VClient018" ) },
		{ INTERFACE_INPUT_SYSTEM, MODULE_INPUT, ENC( "InputSystemVersion001" ) },
		{ INTERFACE_ENGINE_CLIENT, MODULE_ENGINE, ENC( "VEngineClient014" ) },
		{ INTERFACE_SURFACE, MODULE_VGUI, ENC( "VGUI_Surface031" ) },
		{ INTERFACE_PANEL, MODULE_VGUI2, ENC( "VGUI_Panel009" ) },
		{ INTERFACE_ENTITY_LIST, MODULE_CLIENT, ENC( "VClientEntityList003" ) },
		{ INTERFACE_ENGINE_TRACE, MODULE_ENGINE, ENC( "EngineTraceClient004" ) },
		{ INTERFACE_MODEL_INFO, MODULE_ENGINE, ENC( "VModelInfoClient004" ) },
		{ INTERFACE_MODEL_RENDER, MODULE_ENGINE, ENC( "VEngineModel016" ) },
		{ INTERFACE_MATERIAL_SYSTEM, MODULE_MATERIAL_SYSTEM, ENC( "VMaterialSystem080" ) },
		{ INTERFACE_ENGINE_RENDER_VIEW, MODULE_ENGINE, ENC( "VEngineRenderView014" ) },
		{ INTERFACE_CONVAR, MODULE_VSTD, ENC( "VEngineCvar007" ) },
		{ INTERFACE_LOCALIZE, MODULE_LOCALIZE, ENC( "Localize_001" ) },
		{ INTERFACE_EVENTS, MODULE_ENGINE, ENC( "GAMEEVENTSMANAGER002" ) },
		{ INTERFACE_GAME_MOVEMENT, MODULE_CLIENT, ENC( "GameMovement001" ) },
		{ INTERFACE_PREDICTION, MODULE_CLIENT, ENC( "VClientPrediction001" ) },
		{ INTERFACE_ENGINE_SOUND, MODULE_ENGINE, ENC( "IEngineSoundClient003" ) },
		{ INTERFACE_FILE_SYSTEM, MODULE_FILESYSTEM, ENC( "VFileSystem017" ) }
	};
	inline const std::vector< std::pair< EFunction, unsigned > > vecFunctionIndices
	{
		{ FUNCTION_BEGIN_SCENE, 41 },
		{ FUNCTION_END_SCENE, 42 },
		{ FUNCTION_RESET, 16 },
		{ FUNCTION_CREATE_MOVE, 22 },
		{ FUNCTION_FRAME_STAGE_NOTIFY, 37 },
		{ FUNCTION_OVERRIDE_VIEW, 18 },
		{ FUNCTION_GET_VIEWMODEL_FOV, 35 },
		{ FUNCTION_DO_POST_SCREEN_EFFECTS, 44 },
		{ FUNCTION_LOCK_CURSOR, 67 },
		{ FUNCTION_PAINT_TRAVERSE, 41 },
		{ FUNCTION_DRAW_MODEL_EXECUTE, 21 },
		{ FUNCTION_SCENE_BEGIN, 8 },
		{ FUNCTION_SCENE_END, 9 },
		{ FUNCTION_EMIT_SOUND_ATT, 5 },
		{ FUNCTION_IS_PLAYER, 153 },
		{ FUNCTION_IS_WEAPON, 161 },
		{ FUNCTION_GET_INACCURACY, 471 },
		{ FUNCTION_GET_SPREAD, 440 },
		{ FUNCTION_UPDATE_ACCURACY_PENALTY, 472 },
	};

	std::string CreateDataFile( );
#endif

	bool Initialize( );
	unsigned GetFunctionIndex( EFunction _Function );
	std::uintptr_t FindOffset( const char* szTable, const char* szVariable );
}
