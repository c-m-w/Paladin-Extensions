/// Memory.hpp

#pragma once

#include "../../CSGO SDK/Code/Inclusion.hpp"

namespace Modules
{
	enum
	{
		MODULE_CLIENT,
		MODULE_ENGINE,
		MODULE_DIRECT_3D,
		MODULE_DIRECT_3D_API,
		MODULE_OVERLAY,
		MODULE_VGUI,
		MODULE_VGUI2,
		MODULE_INPUTSYSTEM,
		MODULE_MATERIALSYSTEM,
		MODULE_VSTLIB,
		MODULE_LOCALIZE,
		MODULE_FILESYSTEM,
		MODULE_MAX
	};

	struct module_info_t
	{

		image_info_t _Module = nullptr;
		CreateInterfaceFn _CreateInterface = nullptr;

		operator HMODULE( ) const;
		void *operator( )( const char *szInterface ) const;

		bool Valid( );
	};

	inline module_info_t _Modules[ MODULE_MAX ];
	inline module_info_t &_Client				= _Modules[ MODULE_CLIENT ];
	inline module_info_t &_Engine				= _Modules[ MODULE_ENGINE ];
	inline module_info_t &_Direct3D				= _Modules[ MODULE_DIRECT_3D ];
	inline module_info_t &_Direct3DAPI			= _Modules[ MODULE_DIRECT_3D_API ];
	inline module_info_t &_Overlay				= _Modules[ MODULE_OVERLAY ];
	inline module_info_t &_VGUI					= _Modules[ MODULE_VGUI ];
	inline module_info_t &_VGUI2				= _Modules[ MODULE_VGUI2 ];
	inline module_info_t &_InputSystem			= _Modules[ MODULE_INPUTSYSTEM ];
	inline module_info_t &_MaterialSystem		= _Modules[ MODULE_MATERIALSYSTEM ];
	inline module_info_t &_ValveStandardLibrary	= _Modules[ MODULE_VSTLIB ];
	inline module_info_t &_Localize				= _Modules[ MODULE_LOCALIZE ];
	inline module_info_t &_Filesystem			= _Modules[ MODULE_FILESYSTEM ];
}

namespace Interfaces
{
	inline IDirect3DDevice9 *pDevice = nullptr;
}

class CLinkage: public IBase
{
private:

	bool Initialize( ) override;
	void Uninitialize( ) override;

public:

#if defined _DEBUG

	static inline std::string strCreateInterfaceImport	= ENC( "CreateInterface" );
	static inline std::string strModules[ Modules::MODULE_MAX ]
	{
		ENC( "client_panorama.dll" ),
		ENC( "engine.dll" ),		
		ENC( "d3d9.dll" ),			
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

	static inline void *pReset = nullptr,
		*pBeginScene = nullptr,
		*pEndScene = nullptr;

	static inline pattern_t _DevicePattern = pattern_t( ENC( "A1 ? ? ? ? 50 8B 08 FF 51 0C" ), reinterpret_cast< void ** >( &Interfaces::pDevice ), 1, [ & ]( )
	{
		Interfaces::pDevice = **reinterpret_cast< decltype( Interfaces::pDevice )** >( Interfaces::pDevice );
	} );
	static inline pattern_t _ResetPattern = pattern_t( ENC( "CC E9 ? ? ? ? 83 E4 F8 81 EC" ), &pReset, 1 );
	static inline pattern_t _BeginScenePattern = pattern_t( ENC( "5F 5E EB CA CC" ), &pBeginScene, 5 );
	static inline pattern_t _EndScenePattern = pattern_t( ENC( "CC CC 6A 18 B8 ? ? ? ? E8 ? ? ? ? 8B 7D 08 8B DF" ), &pEndScene, 2 );

#else

#endif
} inline _Linker;
