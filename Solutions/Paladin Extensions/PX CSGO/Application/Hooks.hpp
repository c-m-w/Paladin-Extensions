/// Hooks.hpp

#pragma once

namespace PX
{
	namespace Types
	{
		// Device
		typedef HRESULT( __stdcall* begin_scene_t )( IDirect3DDevice9* );
		typedef HRESULT( __stdcall* end_scene_t )( IDirect3DDevice9* );
		typedef HRESULT( __stdcall* reset_t )( IDirect3DDevice9*, D3DPRESENT_PARAMETERS* );

		// Client Base
		typedef void( __stdcall* frame_stage_notify_t )( ClientFrameStage_t );
		typedef void( __stdcall* create_move_t )( int, float, bool );

		// Client Mode
		typedef int( __thiscall* do_post_screen_effects_t )( IClientMode*, int );

		// Surface
		typedef void( __thiscall* lock_cursor_t )( ISurface* );

		// Panel
		typedef void( __thiscall* paint_traverse_t )( IPanel*, vgui::VPANEL, bool, bool );
	}

	namespace Hooks
	{
		bool PX_API InitializeHooks( );
		void PX_API Destruct( );

		//PX_SDK Tools::CHook* hkDirectXDevice;
		PX_SDK Tools::CStandardHook* hkDirectXDevice;
		PX_SDK Tools::CTrampolineHook* hkClientBase;
		PX_SDK Tools::CTrampolineHook* hkClientMode;
		PX_SDK Tools::CTrampolineHook* hkPanel;

		// Device
		HRESULT __stdcall BeginScene( IDirect3DDevice9* pThis );
		HRESULT __stdcall EndScene( IDirect3DDevice9* pThis );
		HRESULT __stdcall Reset( IDirect3DDevice9* pThis, D3DPRESENT_PARAMETERS* pParams );

		// Client Base
		void __stdcall FrameStageNotify( ClientFrameStage_t cfsStage );
		void __stdcall CreateMove( int sequence_number, float input_sample_frametime, bool active );

		// Client Mode
		int __stdcall DoPostScreenEffects( int iUnknown );

		// Panel
		void __stdcall PaintTraverse( vgui::VPANEL panel, bool forceRepaint, bool allowForce );
	}
}
