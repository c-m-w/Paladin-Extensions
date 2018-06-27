/// Render.cpp

#include "../Framework.hpp"

namespace Paladin
{
    void CRender::CreateRenderTarget( )
    {
        RegisterClassExW( &wndWindow );
        hWnd = CreateWindowExW( 0, szWindowTitle, szWindowTitle, WS_POPUP,
                                uWindowStartPosition[ 0 ], uWindowStartPosition[ 1 ], uWindowWidth, uWindowHeight,
                                nullptr, nullptr, wndWindow.hInstance, nullptr );
        //SetLayeredWindowAttributes( hWnd, 0, 1.0f, LWA_ALPHA );
        //SetLayeredWindowAttributes( hWnd, 0, 0, LWA_COLORKEY );
        ShowWindow( hWnd, SW_SHOWDEFAULT );
        UpdateWindow( hWnd );
    }

    void CRender::InitializeDirectX( )
    {
        Direct3DCreate9Ex( D3D_SDK_VERSION, &pObjectEx );

        dxParameters.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
        dxParameters.BackBufferWidth = uWindowWidth;
        dxParameters.BackBufferHeight = uWindowHeight;
        dxParameters.BackBufferFormat = D3DFMT_X8R8G8B8;
        dxParameters.BackBufferCount = 1;
        dxParameters.MultiSampleType = D3DMULTISAMPLE_NONE;
        dxParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
        dxParameters.hDeviceWindow = hWnd;
        dxParameters.EnableAutoDepthStencil = true;
        dxParameters.AutoDepthStencilFormat = D3DFMT_D24S8;
        dxParameters.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;
        dxParameters.Windowed = true;

        pObjectEx->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &dxParameters, &pDevice );
        pDevice->GetCreationParameters( &cpCreationParameters );
    }

    void CRender::BeginRender( )
    {
        pDevice->Clear( 0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_ARGB( 0, 0, 0, 0 ), 0, 0 );
        pDevice->BeginScene( );
    }

    void CRender::EndRender( )
    {
        pDevice->EndScene( );
        pDevice->Present( nullptr, nullptr, nullptr, nullptr );
    }

	void CRender::SetWindowProc( IDirect3DDevice9 *pTargetDevice )
	{
		D3DDEVICE_CREATION_PARAMETERS cpParameters;
		dbg::Assert( pTargetDevice->GetCreationParameters( &cpParameters ) >= 0 );
		uOldHWND = cpParameters.hFocusWindow;

		uOldWindowProc = SetWindowLongPtr( uOldHWND, GWLP_WNDPROC, reinterpret_cast< long >( WndProc ) );
		dbg::Assert( uOldWindowProc );
    }

	void CRender::SetWindowSize( unsigned uWidth, unsigned uHeight )
	{
		uWindowWidth = uWidth;
		uWindowHeight = uHeight;

		if ( !hWnd )
			return;

		RECT rcWindowRect;
		GetWindowRect( hWnd, &rcWindowRect );
		SetWindowPos( hWnd, nullptr, rcWindowRect.left, rcWindowRect.top, uWindowWidth, uWindowHeight, SWP_SHOWWINDOW );
	}

	CRender::~CRender( )
	{
		if ( uOldWindowProc )
			SetWindowLongPtr( uOldHWND, GWLP_WNDPROC, uOldWindowProc );
		if ( hWnd )
			UnregisterClass( szWindowTitle, wndWindow.hInstance );
	}
}
