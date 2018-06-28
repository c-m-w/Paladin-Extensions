/// Render.cpp

#include "../Framework.hpp"

namespace Paladin
{
	void CRender::CreateRenderTarget( )
	{
		RegisterClassEx( &wndWindow );
		hwWindowHandle = CreateWindowEx( 0, szWindowTitle, szWindowTitle, WS_POPUP,
										  uWindowStartPosition[ 0 ], uWindowStartPosition[ 1 ], uWindowWidth, uWindowHeight,
										  nullptr, nullptr, wndWindow.hInstance, nullptr );
				  //SetLayeredWindowAttributes( hWnd, 0, 1.0f, LWA_ALPHA );
				  //SetLayeredWindowAttributes( hWnd, 0, 0, LWA_COLORKEY );
		ShowWindow( hwWindowHandle, SW_SHOWDEFAULT );
		UpdateWindow( hwWindowHandle );
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
		dxParameters.hDeviceWindow = hwWindowHandle;
		dxParameters.EnableAutoDepthStencil = true;
		dxParameters.AutoDepthStencilFormat = D3DFMT_D24S8;
		dxParameters.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;
		dxParameters.Windowed = true;

		pObjectEx->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwWindowHandle, D3DCREATE_HARDWARE_VERTEXPROCESSING, &dxParameters, &pDevice );
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
		hwOldWindowHandle = cpParameters.hFocusWindow;

		uOldWindowProc = SetWindowLongPtr( hwOldWindowHandle, GWLP_WNDPROC, reinterpret_cast< long >( WndProc ) );
		dbg::Assert( uOldWindowProc );
	}

	CRender::CRender( ): pObjectEx { }, cpCreationParameters { }, hwWindowHandle { },
	                     uWindowWidth { }, uWindowHeight { }, uTitleBarHeight { },
	                     lWindowStyle { WS_EX_TRANSPARENT | WS_EX_TOPMOST | WS_EX_NOACTIVATE | WS_EX_LAYERED },
	                     uScreenWidth { unsigned( GetSystemMetrics( SM_CXSCREEN ) ) }, uScreenHeight { unsigned( GetSystemMetrics( SM_CYSCREEN ) ) },
	                     uWindowStartPosition { uScreenWidth / 2 - uWindowWidth / 2, uScreenHeight / 2 - uWindowHeight / 2 },
	                     szWindowTitle { static_cast< wchar_t* >( malloc( 32 ) ) },
	                     wndWindow { sizeof( WNDCLASSEX ), NULL, WndProc, 0, 0, GetModuleHandle( nullptr ), nullptr, LoadCursor( nullptr, IDC_ARROW ), nullptr, nullptr, szWindowTitle, nullptr },
		                 uOldWindowProc { }, hwOldWindowHandle { }, pDevice { }, dxParameters { }
	{ }

	void CRender::SetWindowSize( unsigned uWidth, unsigned uHeight )
	{
		uWindowWidth = uWidth;
		uWindowHeight = uHeight;

		if ( !hwWindowHandle )
			return;

		RECT rcWindowRect;
		GetWindowRect( hwWindowHandle, &rcWindowRect );
		SetWindowPos( hwWindowHandle, nullptr, rcWindowRect.left, rcWindowRect.top, uWindowWidth, uWindowHeight, SWP_SHOWWINDOW );
	}

	CRender::~CRender( )
	{
		if ( hwOldWindowHandle && uOldWindowProc )
			SetWindowLongPtr( hwOldWindowHandle, GWLP_WNDPROC, uOldWindowProc );
		if ( hwWindowHandle )
			UnregisterClass( szWindowTitle, wndWindow.hInstance );
	}
}
