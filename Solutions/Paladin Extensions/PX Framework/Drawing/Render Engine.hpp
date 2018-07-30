/// Render.hpp
// TODO: document @Cole
#pragma once

namespace PX
{
    namespace Render
    {
        enum ECursor
        {
            NONE,
            ARROW,
            HAND,
            IBEAM,
            CURSOR_MAX
        };

        PX_SDK HCURSOR hCursors[ CURSOR_MAX ];
        void PX_API SetCursor( ECursor );

        PX_SDK const wchar_t* szWindowTitle = static_cast< wchar_t* >( malloc( 32 ) );
        PX_SDK WNDCLASSEX wndWindow;
        PX_SDK HWND hwWindowHandle;

        PX_SDK unsigned uWindowWidth, uWindowHeight;
        void PX_API SetWindowSize( unsigned, unsigned );
        void PX_API CreateRenderTarget( );

        PX_SDK D3DPRESENT_PARAMETERS dxParameters;
        PX_SDK IDirect3D9Ex* pObjectEx;
        PX_SDK IDirect3DDevice9* pDevice;
        void PX_API InitializeDirectX( );

        PX_SDK unsigned uOldWindowProc;
        PX_SDK HWND hwOldWindowHandle;
        void PX_API SetWindowProc( IDirect3DDevice9* );

        void PX_API BeginRender( );
        void PX_API EndRender( );
    }
}
