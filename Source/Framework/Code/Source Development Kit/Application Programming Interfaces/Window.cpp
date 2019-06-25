/// Window.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#include "../../Framework.hpp"

LRESULT CALLBACK DefaultWindowInputProcessor( HWND wnd, UINT uMessage, WPARAM wParam, LPARAM lParam )
{
	switch ( uMessage )
	{
		case WM_NCCREATE:
		{
			return TRUE;
		}

		case WM_KILLFOCUS:
		{
			while ( ShowCursor( TRUE ) <= 0 );
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

CApplicationWindow::CApplicationWindow( const std::string &strTitle, const Utilities::vector2_t &vecSize, HINSTANCE hModule, WNDPROC _WindowInputProcessor /*= DefaultWindowInputProcessor*/ ): pOldWindowInputProcessor( nullptr )
{
	_WindowInformation = WNDCLASSEX { sizeof _WindowInformation, NULL, _WindowInputProcessor, NULL, NULL, hModule, nullptr, nullptr, nullptr, nullptr, strTitle.c_str( ), nullptr };
	if ( NULL == RegisterClassEx( &_WindowInformation ) )
	{
		_Log.Log( EPrefix::ERROR, ELocation::WINDOW, ENC( "Failed to register window class." ) );
		return;
	}

	const auto vecScreenSize = _SystemInformation.GetScreenSize( );
	hwHandle = CreateWindowEx( WS_EX_APPWINDOW, strTitle.c_str( ), strTitle.c_str( ), WS_VISIBLE | WS_POPUP, int( vecScreenSize.x / 2.f - vecSize.x / 2.f ), int( vecScreenSize.y / 2.f - vecSize.y / 2.f ),
							   int( vecSize.x ), int( vecSize.y ), nullptr, nullptr, hModule, nullptr );
	if ( nullptr == hwHandle )
	{
		_Log.Log( EPrefix::ERROR, ELocation::WINDOW, ENC( "Failed to create window." ) );
		return;
	}

	if ( TRUE != ShowWindow( hwHandle, SW_SHOWDEFAULT )
		|| TRUE != SetWindowText( hwHandle, strTitle.c_str( ) )
		|| TRUE != UpdateWindow( hwHandle ) )
		_Log.Log( EPrefix::WARNING, ELocation::WINDOW, ENC( "Setting window attributes failed." ) );
}

CApplicationWindow::CApplicationWindow( const HWND &hwWindow, WNDPROC _WindowInputProcessor /*= DefaultWindowInputProcessor*/ ): hwHandle( hwWindow )
{
	if ( _WindowInputProcessor != nullptr
		 && nullptr == ( pOldWindowInputProcessor = WNDPROC( SetWindowLongPtr( hwHandle, GWLP_WNDPROC, LONG( _WindowInputProcessor ) ) ) ) )
		_Log.Log( EPrefix::ERROR, ELocation::WINDOW, ENC( "Failed to set the new window input processor." ) );
}

CApplicationWindow::~CApplicationWindow( )
{
	if ( pOldWindowInputProcessor != nullptr )
		SetWindowLongPtr( hwHandle, GWLP_WNDPROC, LONG( pOldWindowInputProcessor ) );
}

bool CApplicationWindow::PollInput( )
{
	if ( pOldWindowInputProcessor )
		throw std::runtime_error( ENC( "Polling input from non-existent window." ) );

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

	return MoveWindow( hwHandle, recCurrent.left + iHorizontalAmount, recCurrent.top + iVerticalAmount, recCurrent.right - recCurrent.left, recCurrent.bottom - recCurrent.top, FALSE ) != FALSE;
}

bool CApplicationWindow::Resize( int iWidth, int iHeight )
{
	RECT recCurrent;
	if ( GetWindowRect( hwHandle, &recCurrent ) == FALSE )
		return false;

	return MoveWindow( hwHandle, recCurrent.left, recCurrent.top, iWidth, iHeight, TRUE ) != FALSE;
}

bool CApplicationWindow::SetTitle( const std::string &strTitle )
{
	return SetWindowText( hwHandle, strTitle.c_str( ) ) != FALSE;
}

void CApplicationWindow::Hide( )
{
	auto lCurrent = GetWindowLong( hwHandle, GWL_STYLE );

	lCurrent &= ~WS_VISIBLE;
	if ( !SetWindowLong( hwHandle, GWL_STYLE, lCurrent ) == FALSE )
		_Log.Log( EPrefix::WARNING, ELocation::WINDOW, ENC( "Error setting window long to hide window." ) );
}

void CApplicationWindow::Show( )
{
	auto lCurrent = GetWindowLong( hwHandle, GWL_STYLE );

	lCurrent |= WS_VISIBLE;
	if ( !SetWindowLong( hwHandle, GWL_STYLE, lCurrent ) == FALSE )
		_Log.Log( EPrefix::WARNING, ELocation::WINDOW, ENC( "Error setting window long to show window." ) );
	
}

void CApplicationWindow::Destroy( )
{
	if ( UnregisterClass( _WindowInformation.lpszClassName, _WindowInformation.hInstance ) == FALSE )
		_Log.Log( EPrefix::ERROR, ELocation::WINDOW, ENC( "Unable to unregister window." ) );

	if ( DestroyWindow( hwHandle ) == FALSE )
		_Log.Log( EPrefix::ERROR, ELocation::WINDOW, ENC( "Unable to destroy window." ) );
}

bool CApplicationWindow::CursorOnWindow( )
{
	RECT recCurrent { };
	POINT pntCursor { };

	if ( GetWindowRect( hwHandle, &recCurrent ) == FALSE
		 || GetCursorPos( &pntCursor ) == FALSE )
		return false;

	const rectangle_t recBounds { recCurrent };
	return recBounds.LocationInRectangle( pntCursor );
}
