/// Render.cpp

#include "../PX Framework.hpp"

namespace PX
{
    namespace Render
    {
        void PX_API SetCursor( ECursor curType )
        {
            SetCursor( hCursors[ curType ] ? hCursors[ curType ] : hCursors[ NONE ] );
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

        void PX_API CreateRenderTarget( )
        {
            static bool bFirstCall = true;
            if ( bFirstCall )
            {
                wndWindow = { sizeof( WNDCLASSEX ), NULL, WndProc, 0, 0, GetModuleHandle( nullptr ), nullptr, LoadCursor( nullptr, IDC_ARROW ), nullptr, nullptr, szWindowTitle, nullptr };

                wndWindow.style = CS_DBLCLKS;
                wndWindow.lpfnWndProc = WndProc;
                wndWindow.hInstance = GetModuleHandle( nullptr );
                const auto strResourceDirectory = Utilities::GetDirectory( PX_DEPENDENCIES_ESCAPE ) + LR"(\Resources\)";
                wndWindow.hIcon = HICON( LoadImage( nullptr, ( strResourceDirectory + LR"(Logo\Paladin Logo.ico)" ).c_str( ),
                                                    IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_SHARED ) );

                hCursors[ NONE ] = LoadCursor( nullptr, IDC_ARROW );
                hCursors[ ARROW ] = LoadCursorFromFile( ( strResourceDirectory + LR"(Cursor\Arrow.cur)" ).c_str( ) );
                hCursors[ HAND ] = LoadCursorFromFile( ( strResourceDirectory + LR"(Cursor\Hand.cur)" ).c_str( ) );
                hCursors[ IBEAM ] = LoadCursorFromFile( ( strResourceDirectory + LR"(Cursor\I Beam.cur)" ).c_str( ) );

                wndWindow.hCursor = hCursors[ ARROW ] ? hCursors[ ARROW ] : hCursors[ NONE ];
                wndWindow.lpszClassName = szWindowTitle;
                RegisterClassEx( &wndWindow );

                RECT rcWindow;
                AdjustWindowRectEx( &rcWindow, WS_OVERLAPPEDWINDOW, false, WS_EX_APPWINDOW );

                hwWindowHandle = CreateWindowEx( WS_EX_APPWINDOW, szWindowTitle, szWindowTitle, WS_VISIBLE | WS_POPUP,
                                                 CW_USEDEFAULT, CW_USEDEFAULT, uWindowWidth, uWindowHeight,
                                                 nullptr, nullptr, wndWindow.hInstance, nullptr );

                ShowWindow( hwWindowHandle, SW_SHOWDEFAULT );
                UpdateWindow( hwWindowHandle );
                SetForegroundWindow( hwWindowHandle );

                bFirstCall = false;
            }
        }

        void PX_API InitializeDirectX( )
        {
            static bool bFirstCall = true;
            if ( bFirstCall )
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
                bFirstCall = false;
            }
        }

        void PX_API SetWindowProc( IDirect3DDevice9* pTargetDevice )
        {
            D3DDEVICE_CREATION_PARAMETERS cpParameters;
            dbg::Assert( pTargetDevice->GetCreationParameters( &cpParameters ) >= 0 );
            hwOldWindowHandle = cpParameters.hFocusWindow;

            uOldWindowProc = SetWindowLongPtr( hwOldWindowHandle, GWLP_WNDPROC, reinterpret_cast< long >( WndProc ) );
            dbg::Assert( uOldWindowProc );
        }

        void PX_API BeginRender( )
        {
            pDevice->Clear( 0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_ARGB( 0, 0, 0, 0 ), 0, 0 );
            pDevice->BeginScene( );
        }

        void PX_API EndRender( )
        {
            pDevice->EndScene( );
            pDevice->Present( nullptr, nullptr, nullptr, nullptr );
        }
    }
}
