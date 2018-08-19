/// Hooks.hpp

#pragma once

namespace PX
{
	namespace Types
	{
		typedef HRESULT( __stdcall* endscene_t )( IDirect3DDevice9* );
		typedef HRESULT( __stdcall* reset_t )( IDirect3DDevice9*, D3DPRESENT_PARAMETERS* );
		typedef HRESULT( __stdcall* present_t )( IDirect3DDevice9*, CONST RECT*, CONST RECT*, HWND, CONST RGNDATA* );
		typedef void( __thiscall* lockcursor_t )( ISurface* );
	}

	namespace VirtualTableIndicies
	{
		PX_DEF uEndScene	= 42u;
		PX_DEF uReset		= 16u;
		PX_DEF uPresent		= 17u;
		PX_DEF uLockCursor	= 67u;
	}

	namespace Hooks
	{
		bool PX_API InitializeHooks( );
		void PX_API Destruct( );

		PX_SDK Tools::CHook* hkDirectXDevice;
		PX_SDK Tools::CHook* hkClientBase;
		PX_SDK Tools::CHook* hkSurface;

		HRESULT __stdcall EndScene( IDirect3DDevice9* pDeviceParameter );
		HRESULT __stdcall Reset( IDirect3DDevice9* pDeviceParameter, D3DPRESENT_PARAMETERS* pParams );
		HRESULT __stdcall Present( IDirect3DDevice9* pDeviceParameter, CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion );
		void __fastcall LockCursor( ISurface* pThisClass, void* edx );
	}
}
