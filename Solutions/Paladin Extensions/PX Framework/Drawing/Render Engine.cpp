/// Render.cpp

#include "../PX Framework.hpp"

namespace PX
{
	namespace Render
	{
		LPCREATESTRUCT pWindowInformation;

		LRESULT WINAPI WndProc( HWND hwWindowHandle, UINT uMessage, WPARAM uwParam, LPARAM llParam )
		{
			PX_INPUT.OnEvent( hwWindowHandle, uMessage, uwParam, llParam );

			switch ( uMessage )
			{
				case WM_NCCREATE:
				case WM_CREATE:
					pWindowInformation = LPCREATESTRUCT( llParam );
					return true;

				case WM_SETCURSOR:
					if ( llParam == HTCLIENT )
						return true;

				case WM_DESTROY:
					PostQuitMessage( 0 );
					return 0;

				case WM_SIZE:
					if ( pDevice )
					{
						const auto uWidth = LOWORD( llParam );
						const auto uHeight = HIWORD( llParam );
						if ( uWidth != 0 && uHeight != 0 &&
							( uWidth != dxParameters.BackBufferWidth || uHeight != dxParameters.BackBufferHeight ) )
						{
							UI::Manager::OnRelease( );
							dxParameters.BackBufferWidth = uWidth;
							dxParameters.BackBufferHeight = uHeight;
							const auto hrReset = pDevice->Reset( &dxParameters );
							dbg::Assert( hrReset >= 0 );
							UI::Manager::Resize( uWidth, uHeight );
						}
					}
					break;
				default:
					break;
			}
			return UI::Manager::OnEvent( hwWindowHandle, uMessage, uwParam, llParam )
				? ( uOldWindowProc
					? CallWindowProc( reinterpret_cast< WNDPROC >( uOldWindowProc ), hwWindowHandle, uMessage, uwParam, llParam )
					: 0 )
				: DefWindowProc( hwWindowHandle, uMessage, uwParam, llParam );
		}

		void PX_API SetCursor( ECursor curType )
		{
			SetCursor( hCursors[ curType ] ? hCursors[ curType ] : hCursors[ CURSOR_NONE ] );
		}

		void PX_API SetWindowSize( unsigned uWidth, unsigned uHeight )
		{
			uWindowWidth = uWidth;
			uWindowHeight = uHeight;

			if ( !hwWindowHandle )
				return;

			RECT rcWindowRect;
			GetWindowRect( hwWindowHandle, &rcWindowRect );
			SetWindowPos( hwWindowHandle, nullptr, rcWindowRect.left, rcWindowRect.top, uWindowWidth, uWindowHeight, SWP_SHOWWINDOW );
		}

		void PX_API CreateRenderTarget( HINSTANCE hInstance )
		{
			wndWindow.lpfnWndProc = WndProc;
			wndWindow.hInstance = hInstance;

			const auto strResourceDirectory = Tools::GetDirectory( 3 ) + LR"(\Resources\)";
			wndWindow.hIcon = HICON( LoadImage( nullptr, ( strResourceDirectory + LR"(Logo\Paladin Logo.ico)" ).c_str( ),
												IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_SHARED ) );

			hCursors[ CURSOR_NONE ] = LoadCursor( nullptr, IDC_ARROW );
			hCursors[ CURSOR_ARROW ] = LoadCursorFromFile( ( strResourceDirectory + LR"(Cursor\Arrow.cur)" ).c_str( ) );
			hCursors[ CURSOR_HAND ] = LoadCursorFromFile( ( strResourceDirectory + LR"(Cursor\Hand.cur)" ).c_str( ) );
			hCursors[ CURSOR_IBEAM ] = LoadCursorFromFile( ( strResourceDirectory + LR"(Cursor\I Beam.cur)" ).c_str( ) );

			wndWindow.hCursor = hCursors[ CURSOR_ARROW ] ? hCursors[ CURSOR_ARROW ] : hCursors[ CURSOR_NONE ];
			wndWindow.lpszClassName = wszWindowTitle;
			const auto atInstance = RegisterClassEx( &wndWindow );

			RECT rcWindow;
			AdjustWindowRectEx( &rcWindow, WS_OVERLAPPEDWINDOW, false, WS_EX_APPWINDOW );

			hwWindowHandle = CreateWindowEx( WS_EX_APPWINDOW, wszWindowTitle, wszWindowTitle, WS_VISIBLE | WS_POPUP,
											 CW_USEDEFAULT, CW_USEDEFAULT, uWindowWidth, uWindowHeight,
											 nullptr, nullptr, wndWindow.hInstance, nullptr );

			dbg::PrintLastError( );

			ShowWindow( hwWindowHandle, SW_SHOWDEFAULT );
			UpdateWindow( hwWindowHandle );
			SetForegroundWindow( hwWindowHandle );

			bCreatedWindow = true;
		}

		void PX_API InitializeDirectX( )
		{
			if ( bCreatedWindow )
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

				// Windows 7 doesn't support hardware vertexprocessing, so if it fails we need to use software vertexprocessing.
				if ( pObjectEx->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwWindowHandle, D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE | D3DCREATE_FPU_PRESERVE, &dxParameters, &pDevice ) < 0 )
					dbg::Assert( pObjectEx->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwWindowHandle, D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE | D3DCREATE_FPU_PRESERVE, &dxParameters, &pDevice ) >= 0 );
				pDevice->GetCreationParameters( new D3DDEVICE_CREATION_PARAMETERS ); // warning: passing NEW because parameter passed from before was never used
			}
		}

		void PX_API InitializeRenderTarget( unsigned* pDimensions, HINSTANCE hInstance, Tools::wcstr_t szNewWindowTitle )
		{
			wszWindowTitle = szNewWindowTitle;
			SetWindowSize( pDimensions[ 0 ], pDimensions[ 1 ] );
			CreateRenderTarget( hInstance );
			InitializeDirectX( );
		}

		void PX_API SetWindowProc( IDirect3DDevice9* pTargetDevice )
		{
			D3DDEVICE_CREATION_PARAMETERS cpParameters;
			dbg::Assert( pTargetDevice->GetCreationParameters( &cpParameters ) >= 0 );
			hwOldWindowHandle = cpParameters.hFocusWindow;

			uOldWindowProc = SetWindowLongPtr( hwOldWindowHandle, GWLP_WNDPROC, reinterpret_cast< long >( WndProc ) );
			dbg::Assert( uOldWindowProc );
		}
	}
}
