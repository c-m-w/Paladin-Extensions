/// Window.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#define USE_DEFINITIONS
#include "../../Framework.hpp"

LRESULT CALLBACK DefaultWindowInputProcessor( HWND wnd, UINT uMessage, WPARAM wParam, LPARAM lParam )
{
	switch ( uMessage )
	{
		case WM_NCCREATE:
		{
			return TRUE;
		}

		default:
		{
			IN.HandleEvent( uMessage, wParam, lParam );
		}
			break;
	}

	return DefWindowProc( wnd, uMessage, wParam, lParam );
}

BOOL CALLBACK EnumWindowsProc(
	_In_		 HWND hwnd,
				 _In_		 LPARAM lParam
)
{
	DWORD dwProcessID { };
	GetWindowThreadProcessId( hwnd, &dwProcessID );

	if ( dwProcessID == GetCurrentProcessId( ) )
		reinterpret_cast< std::vector< HWND >* >( lParam )->emplace_back( hwnd );

	return true;
}

std::vector< HWND > CApplicationWindow::GetCurrentProcessWindows( )
{
	std::vector< HWND > vecWindows { };

	EnumWindows( EnumWindowsProc, reinterpret_cast< LPARAM >( &vecWindows ) );
	return vecWindows;
}

CApplicationWindow::CApplicationWindow( const std::string &strTitle, const Utilities::vector2_t &vecSize, HINSTANCE hModule, WNDPROC _WindowInputProcessor /*= DefaultWindowInputProcessor*/ ): pOldWindowInputProcessor( nullptr )
{
	_WindowInformation = WNDCLASSEX { sizeof _WindowInformation, NULL, _WindowInputProcessor, NULL, NULL, hModule, nullptr, nullptr, nullptr, nullptr, strTitle.c_str( ), nullptr };
	if ( NULL == RegisterClassEx( &_WindowInformation ) )
	{
		LOG.Log( EPrefix::ERROR, ELocation::WINDOW, XOR( "Failed to register window class." ) );
		return;
	}

	const auto vecScreenSize = GetScreenSize( );
	hwHandle = CreateWindowEx( WS_EX_APPWINDOW, strTitle.c_str( ), strTitle.c_str( ), WS_VISIBLE | WS_POPUP, int( vecScreenSize.x / 2.f - vecSize.x / 2.f ), int( vecScreenSize.y / 2.f - vecSize.y / 2.f ),
							   int( vecSize.x ), int( vecSize.y ), nullptr, nullptr, hModule, nullptr );
	if ( nullptr == hwHandle )
	{
		LOG.Log( EPrefix::ERROR, ELocation::WINDOW, XOR( "Failed to create window." ) );
		return;
	}

	if ( TRUE != ShowWindow( hwHandle, SW_SHOWDEFAULT )
		|| TRUE != SetWindowText( hwHandle, strTitle.c_str( ) )
		|| TRUE != UpdateWindow( hwHandle ) )
		LOG.Log( EPrefix::WARNING, ELocation::WINDOW, XOR( "Setting window attributes failed." ) );
}

CApplicationWindow::CApplicationWindow( const HWND &hwWindow, WNDPROC _WindowInputProcessor /*= DefaultWindowInputProcessor*/ ): hwHandle( hwWindow )
{
	if ( nullptr == ( pOldWindowInputProcessor = WNDPROC( SetWindowLongPtr( hwHandle, GWLP_WNDPROC, LONG( _WindowInputProcessor ) ) ) ) )
		LOG.Log( EPrefix::ERROR, ELocation::WINDOW, XOR( "Failed to set the new window input processor." ) );
}

CApplicationWindow::~CApplicationWindow( )
{
	if ( pOldWindowInputProcessor != nullptr )
		SetWindowLongPtr( hwHandle, GWLP_WNDPROC, LONG( pOldWindowInputProcessor ) );
}

bool CApplicationWindow::PollInput( )
{
	if ( pOldWindowInputProcessor )
		throw std::runtime_error( XOR( "Attempting to poll a window's input that was not created." ) );

	MSG msgMessage;

	if ( PeekMessage( &msgMessage, nullptr, NULL, NULL, PM_REMOVE ) )
	{
		TranslateMessage( &msgMessage );
		DispatchMessage( &msgMessage );
		return true;
	}

	return false;
}

HWND CApplicationWindow::GetWindowHandle( )
{
	return hwHandle;
}

bool CApplicationWindow::GetBounds( RECT& recOut )
{
	return GetClientRect( hwHandle, &recOut ) != FALSE;
}

bool CApplicationWindow::Move( int iHorizontalAmount, int iVerticalAmount )
{
	if ( iHorizontalAmount == 0 && iVerticalAmount == 0 )
		return false;

	RECT recCurrent { };
	if ( GetWindowRect( hwHandle, &recCurrent ) == FALSE )
		return false;

	MoveWindow( hwHandle, recCurrent.left + iHorizontalAmount, recCurrent.top + iVerticalAmount, recCurrent.right - recCurrent.left, recCurrent.bottom - recCurrent.top, FALSE );
	return true;
}
