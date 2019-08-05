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

	inline module_info_t mEngine;
	inline module_info_t mClient;
	inline module_info_t mDirectX;
	inline module_info_t mOverlay;
	inline module_info_t mVGUI;
	inline module_info_t mVGUI2;
	inline module_info_t mInput;
	inline module_info_t mMaterialSystem;
	inline module_info_t mValveStandardLibrary;
	inline module_info_t mLocalize;
	inline module_info_t mFileSystem;

	inline CGlobalVarsBase* pGlobalVariables = nullptr;
	inline CClientState* pClientState = nullptr;
	inline IDirect3DDevice9* pDevice = nullptr;
	inline IBaseClientDLL* pClientBase = nullptr;
	inline IClientMode* pClientMode = nullptr;
	inline CGlowObjectManager* pGlowObjectManager = nullptr;
	inline IInputSystem* pInputSystem = nullptr;
	inline IVEngineClient* pEngineClient = nullptr;
	inline ISurface* pSurface = nullptr;
	inline IPanel* pPanel = nullptr;
	inline IClientEntityList* pEntityList = nullptr;
	inline IEngineTrace* pEngineTrace = nullptr;
	inline IVModelInfoClient* pModelInfo = nullptr;
	inline CInput* pInput = nullptr;
	inline IVModelRender* pModelRender = nullptr;
	inline IMaterialSystem* pMaterialSystem = nullptr;
	inline IVRenderView* pEngineRenderView = nullptr;
	inline ICvar* pConVar = nullptr;
	inline ILocalize* pLocalize = nullptr;
	inline IGameEventManager2* pEvents = nullptr;
	inline IMoveHelperServer* pMoveHelper = nullptr;
	inline IGameMovement* pGameMovement = nullptr;
	inline IPrediction* pPrediction = nullptr;
	inline IEngineSound* pEngineSound = nullptr;
	inline IViewRenderBeams* pRenderBeams = nullptr;
	inline IFileSystem* pFileSystem = nullptr;

	inline std::vector< networked_variable_table_t > vecNetworkedVariables { };

	bool Initialize( );
	std::uintptr_t FindOffset( const char* szTable, const char* szVariable );
}
