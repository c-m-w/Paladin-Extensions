/// Render.hpp

#pragma once

namespace PX
{
    namespace Render
    {
        // note: does not include any of the unused variables from old CRender. also does not include any variable unused with currently declared functions
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
        LRESULT WINAPI WndProc( HWND, UINT, WPARAM, LPARAM );
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
