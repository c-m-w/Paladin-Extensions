/// Hooks.hpp

#pragma once

namespace PX
{
	namespace Types
	{
		// Device
		typedef HRESULT( __stdcall* endscene_t )( IDirect3DDevice9* );
		typedef HRESULT( __stdcall* reset_t )( IDirect3DDevice9*, D3DPRESENT_PARAMETERS* );

		// Client Base
		typedef void( __stdcall* framestagenotify_t )( ClientFrameStage_t );
		typedef void( __stdcall* createmove_t )( int, float, bool );

		// Surface
		typedef void( __thiscall* lockcursor_t )( ISurface* );
	}

	namespace Hooks
	{
		bool PX_API InitializeHooks( );
		void PX_API Destruct( );

		PX_SDK Tools::CHook* hkDirectXDevice;
		PX_SDK Tools::CHook* hkClientBase;
		PX_SDK Tools::CHook* hkSurface;

		// Device
		HRESULT __stdcall EndScene( IDirect3DDevice9* pDeviceParameter );
		HRESULT __stdcall Reset( IDirect3DDevice9* pDeviceParameter, D3DPRESENT_PARAMETERS* pParams );
		
		void __stdcall FrameStageNotify( ClientFrameStage_t cfsStage );
		void __stdcall CreateMove( int sequence_number, float input_sample_frametime, bool active );

		void __fastcall LockCursor( ISurface* pThisClass, void* edx );
	}
}
