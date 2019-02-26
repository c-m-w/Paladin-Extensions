/// Link.hpp

#pragma once

#include "../../CSGO SDK/Code/Inclusion.hpp"

/** \brief Will link the regions of memory from our reconstruction of the SDK to the live runtime memory */
class CLink: public IBase
{
public:
	enum EModules
	{
		// bin
		ENGINE,
		VGUI2,
		VGUIMATSURFACE,

		// csgo/bin
		CLIENT,

		MODULES_MAX
	};

	// todo get from server
	const char* szModuleNames[ MODULES_MAX ]
	{
		ENC( "engine.dll" ),
		ENC( "vgui2.dll" ),
		ENC( "vguimatsurface.dll" ),

		ENC( "client_panorama.dll" )
	};

	HMODULE hEngineBase,
		hVGUI2Base,
		hVGUIMatSurfaceBase,
	
		hClientBase;

	// C++ Standard §8.3.2/4: There shall be no references to references, **no arrays of references**, and no pointers to references.
	// suck my dick, C++. i always find a way.	
	std::array< HMODULE&, MODULES_MAX > hBases
	{
		hEngineBase,
		hVGUI2Base,
		hVGUIMatSurfaceBase,
		hClientBase
	};

	CreateInterfaceFn fnCreateInterface[ MODULES_MAX ];

	struct // Interfaces
	{
		inline static void* pFoo = nullptr;
		inline static void* pBar = nullptr;
	};

	struct // Indices
	{
		inline static std::size_t zFoo = 0,
			zBar = 0;
	};

	struct // Offsets
	{
		inline static std::ptrdiff_t dFoo = 0,
			dBar = 0;
	};

	CVirtualTableHook hkFoo,
		hkBar;

	bool Initialize( ) override;
	void Uninitialize( ) override;
} inline _Link;
