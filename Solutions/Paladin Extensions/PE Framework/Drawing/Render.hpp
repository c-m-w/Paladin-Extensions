/// Render.hpp

#pragma once

namespace Paladin
{
    LRESULT WINAPI WndProc( HWND, UINT, WPARAM, LPARAM );

    class CRender
    {
    protected:
        IDirect3D9Ex *pObjectEx;
        D3DDEVICE_CREATION_PARAMETERS cpCreationParameters;

        HWND hwWindowHandle;
        unsigned uWindowWidth, uWindowHeight;
        unsigned uTitleBarHeight;
        long lWindowStyle;

        unsigned uScreenWidth, uScreenHeight;
        unsigned uWindowStartPosition[ 2 ];
        const wchar_t *szWindowTitle;
		WNDCLASSEX wndWindow;

        void CreateRenderTarget( );
        void InitializeDirectX( );
        void BeginRender( );
        void EndRender( );
    public:
		void SetWindowSize( unsigned, unsigned );
		void SetWindowProc( IDirect3DDevice9 * );
		CRender( );
		~CRender( );

		unsigned uOldWindowProc;
		HWND hwOldWindowHandle;
        IDirect3DDevice9 *pDevice;
        D3DPRESENT_PARAMETERS dxParameters;
    };
}
