/// Window.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#include "../../Framework.hpp"

LRESULT CALLBACK WindowProc( HWND wnd, UINT uMessage, WPARAM wParam, LPARAM lParam )
{
	switch ( uMessage )
	{
		case WM_NCCREATE:
		{
			return TRUE;
		}

		default:
		{
			_Input.HandleEvent( uMessage, wParam, lParam );
		}
			break;
	}

	return DefWindowProc( wnd, uMessage, wParam, lParam );
}

BOOL CALLBACK EnumWindowsProc(
	_In_ HWND hwnd,
	_In_ LPARAM lParam
)
{
	DWORD dwProcessID { };
	GetWindowThreadProcessId( hwnd, &dwProcessID );

	if ( dwProcessID == GetCurrentProcessId( ) )
		reinterpret_cast< std::vector< HWND >* >( lParam )->emplace_back( hwnd );

	return true;
}

std::vector< HWND > CWindow::GetCurrentProcessWindows( )
{
	std::vector< HWND > vecWindows { };

	EnumWindows( EnumWindowsProc, reinterpret_cast< LPARAM >( &vecWindows ) );
	return vecWindows;
}

CWindow::CWindow( const std::string &strTitle, const Utilities::vector2_t &vecSize, HINSTANCE hModule, WNDPROC _WindowInputProcessor /*= DefaultWindowInputProcessor*/ ): pOldWindowInputProcessor( nullptr )
{
	_WindowInformation = WNDCLASSEX { sizeof _WindowInformation, NULL, _WindowInputProcessor, NULL, NULL, hModule, nullptr, nullptr, nullptr, nullptr, strTitle.c_str( ), nullptr };
	if ( NULL == RegisterClassEx( &_WindowInformation ) )
	{
		_Log.Log( EPrefix::ERROR, ELocation::WINDOW, XOR( "Failed to register window class." ) );
		return;
	}

	const auto vecScreenSize = GetScreenSize( );
	hwHandle = CreateWindowEx( WS_EX_APPWINDOW, strTitle.c_str( ), strTitle.c_str( ), WS_VISIBLE, int( vecScreenSize.x / 2.f - vecSize.x / 2.f ), int( vecScreenSize.y / 2.f - vecSize.y / 2.f ),
							   int( vecSize.x ), int( vecSize.y ), nullptr, nullptr, hModule, nullptr );
	if ( nullptr == hwHandle )
	{
		_Log.Log( EPrefix::ERROR, ELocation::WINDOW, XOR( "Failed to create window." ) );
		return;
	}

	if ( TRUE != ShowWindow( hwHandle, SW_SHOWDEFAULT )
		|| TRUE != SetWindowText( hwHandle, strTitle.c_str( ) )
		|| TRUE != UpdateWindow( hwHandle ) )
		_Log.Log( EPrefix::WARNING, ELocation::WINDOW, XOR( "Setting window attributes failed." ) );
}

CWindow::CWindow( const HWND &hwWindow, WNDPROC _WindowInputProcessor /*= DefaultWindowInputProcessor*/ ): hwHandle( hwWindow )
{
	if ( nullptr == ( pOldWindowInputProcessor = WNDPROC( SetWindowLongPtr( hwHandle, GWLP_WNDPROC, LONG( _WindowInputProcessor ) ) ) ) )
		_Log.Log( EPrefix::ERROR, ELocation::WINDOW, XOR( "Failed to set the new window input processor." ) );
}

CWindow::~CWindow( )
{
	if ( pOldWindowInputProcessor != nullptr )
		SetWindowLongPtr( hwHandle, GWLP_WNDPROC, LONG( pOldWindowInputProcessor ) );
}

HWND CWindow::GetWindowHandle( )
{
	return hwHandle;
}
