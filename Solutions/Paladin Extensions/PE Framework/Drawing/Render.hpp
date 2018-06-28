/// Render.hpp

#pragma once

namespace Paladin
{
    LRESULT WINAPI WndProc( HWND, UINT, WPARAM, LPARAM );

    class CRender
    {
    public:
		enum ECursor
    	{
			NONE,
			ARROW,
			HAND,
			IBEAM,
			CURSOR_MAX
		};
    protected:
        IDirect3D9Ex *pObjectEx;
        D3DDEVICE_CREATION_PARAMETERS cpCreationParameters;
		bool bCreatedDevice;

        HWND hwWindowHandle;
		HCURSOR hCursors[ CURSOR_MAX ];
        unsigned uWindowWidth, uWindowHeight;
        unsigned uTitleBarHeight;
        long lWindowStyle;

        unsigned uScreenWidth, uScreenHeight;
        const wchar_t *szWindowTitle;
		WNDCLASSEX wndWindow;

        void CreateRenderTarget( );
        void InitializeDirectX( );
        void BeginRender( );
        void EndRender( );
    public:
		void SetWindowSize( unsigned, unsigned );
	    void SetWindowProc( IDirect3DDevice9 * );
		void SetActiveCursor( ECursor curCursor );
		CRender( );
		~CRender( );

		unsigned uOldWindowProc;
		HWND hwOldWindowHandle;
        IDirect3DDevice9 *pDevice;
        D3DPRESENT_PARAMETERS dxParameters;
    };
}
