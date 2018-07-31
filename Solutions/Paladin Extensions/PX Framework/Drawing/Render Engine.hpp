/// Render.hpp
// TODO: document @Cole
#pragma once

namespace PX
{
    namespace Render
    {
        enum ECursor
        {
            CURSOR_NONE,
            CURSOR_ARROW,
            CURSOR_HAND,
            CURSOR_IBEAM,
            CURSOR_MAX
        };

        PX_SDK HCURSOR hCursors[ CURSOR_MAX ];
        void PX_API SetCursor( ECursor );

        PX_SDK Tools::wcstr_t szWindowTitle = static_cast< wchar_t* >( malloc( 32 ) );
		PX_SDK unsigned uWindowWidth, uWindowHeight;
        PX_SDK WNDCLASSEX wndWindow;
        PX_SDK HWND hwWindowHandle;

		PX_SDK D3DPRESENT_PARAMETERS dxParameters;
		PX_SDK IDirect3D9Ex* pObjectEx;
		PX_SDK IDirect3DDevice9* pDevice;
        void PX_API SetWindowSize( unsigned, unsigned );
		void PX_API InitializeRenderTarget( unsigned*, Tools::wcstr_t = nullptr );

        PX_SDK unsigned uOldWindowProc;
        PX_SDK HWND hwOldWindowHandle;
        void PX_API SetWindowProc( IDirect3DDevice9* );

        void PX_API BeginRender( );
        void PX_API EndRender( );
    }
}
