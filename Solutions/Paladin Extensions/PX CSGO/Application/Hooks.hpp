/// Hooks.hpp

#pragma once

namespace PX
{
	namespace Types
	{
		typedef int( __stdcall* endscene_t )( IDirect3DDevice9* );
		typedef int( __stdcall* reset_t )( IDirect3DDevice9*, D3DPRESENT_PARAMETERS* );
	}

	namespace VirtualTableIndicies
	{
		PX_DEF uEndScene	= 42u;
		PX_DEF uReset		= 16u;
	}

	namespace Hooks
	{
		bool PX_API Initialize( );
		void PX_API Destruct( );

		PX_SDK CHook* hkDirectXDevice;

		int __stdcall EndScene( IDirect3DDevice9* pDevice );
		int __stdcall Reset( IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pParams );
	}
}