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
        inline HCURSOR hCursors[ CURSOR_MAX ];
        void SetCursor( ECursor );

        inline const wchar_t* szWindowTitle = static_cast< wchar_t* >( malloc( 32 ) );
        LRESULT WINAPI WndProc( HWND, UINT, WPARAM, LPARAM );
        inline WNDCLASSEX wndWindow;
        inline HWND hwWindowHandle;

        inline unsigned uWindowWidth, uWindowHeight;
        void SetWindowSize( unsigned, unsigned );
        void CreateRenderTarget( );

        inline D3DPRESENT_PARAMETERS dxParameters;
        inline IDirect3D9Ex* pObjectEx;
        inline IDirect3DDevice9* pDevice;
        void InitializeDirectX( );

        inline unsigned uOldWindowProc;
        inline HWND hwOldWindowHandle;
        void SetWindowProc( IDirect3DDevice9* );

        void BeginRender( );
        void EndRender( );
    }
}
