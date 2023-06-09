/// Input.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#include "../../Framework.hpp"

void callbacks_t::AddCallback( const key_callback_t &_Callback, const key_t &_Key )
{
	vecKeyCallbacks[ _Key ].emplace_back( _Callback );
}

void callbacks_t::AddCallback( const key_typed_callback_t &_Callback )
{
	vecKeyTypedCallbacks.emplace_back( _Callback );
}

void callbacks_t::AddCallback( const global_key_callback_t &_Callback )
{
	vecGlobalKeyCallbacks.emplace_back( _Callback );
}

void callbacks_t::AddCallback( const mouse_move_callback_t &_Callback )
{
	vecMouseMoveCallbacks.emplace_back( _Callback );
}

void callbacks_t::AddCallback( const scroll_callback_t &_Callback )
{
	vecScrollCallbacks.emplace_back( _Callback );
}

std::vector< key_callback_t > &callbacks_t::GetCallbacks( const key_t &_Key )
{
	return vecKeyCallbacks[ _Key ];
}

bool CInputHandler::Initialize( )
{
	iMouseX = iMouseY = _LastPressedKey = 0;
	memset( _KeyStates, 0, sizeof( CKeyState ) * UCHAR_MAX );
	memset( mmtLastKeyPressTime, 0, sizeof( moment_t ) * UCHAR_MAX );
	return true;
}

bool CInputHandler::ProcessKey( key_t _Key, CKeyState _KeyState )
{
	if ( ( _KeyStates[ _Key ] = _KeyState ) == true )
	{
		mmtLastKeyPressTime[ _Key ] = GetMoment( );
		_LastPressedKey = _Key;
	}

	auto bReturn = false;

	for ( const auto &fnCallback: _Callbacks.GetCallbacks( _Key ) )
		bReturn |= fnCallback( _KeyState );

	for ( const auto &fnCallback: _Callbacks.GetCallbacks< global_key_callback_t >( ) )
		bReturn |= fnCallback( _Key, _KeyState );

	return bReturn;
}

bool CInputHandler::ProcessMouseMessage( UINT uMsg, WPARAM wParam )
{
	key_t _Key = 0;
	auto _KeyState = CKeyState::UP;

	switch ( uMsg )
	{
		case WM_MBUTTONDOWN:
			_KeyState = CKeyState::DOWN;
		case WM_MBUTTONUP:
			_Key = VK_MBUTTON;
			break;
		case WM_RBUTTONDOWN:
			_KeyState = CKeyState::DOWN;
		case WM_RBUTTONUP:
			_Key = VK_RBUTTON;
			break;
		case WM_LBUTTONDOWN:
			_KeyState = CKeyState::DOWN;
		case WM_LBUTTONUP:
			_Key = VK_LBUTTON;
			break;
		case WM_XBUTTONDOWN:
			_KeyState = CKeyState::DOWN;
		case WM_XBUTTONUP:
			_Key = HIWORD( wParam ) == XBUTTON1 ? VK_XBUTTON1 : VK_XBUTTON2;
			break;
		default:
			return false;
	}

	return ProcessKey( _Key, _KeyState );
}

bool CInputHandler::ProcessKeyboardMessage( UINT uMsg, WPARAM wParam )
{
	auto bReturn = false;
	auto _KeyState = CKeyState::UP;

	switch ( uMsg )
	{
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
			_KeyState = CKeyState::DOWN;
		case WM_KEYUP:
		case WM_SYSKEYUP:
			break;

		case WM_CHAR:
		{
			if ( wParam >= ' ' || wParam == VK_BACK )
				for ( const auto &_Callback: _Callbacks.GetCallbacks< key_typed_callback_t >( ) )
					bReturn |= _Callback( wParam );
		}
		break;

		default:
			return false;
	}

	return bReturn | ProcessKey( wParam, _KeyState );
}

void CInputHandler::Uninitialize( )
{ }

bool CInputHandler::HandleEvent( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	if ( uMsg == WM_SIZE && wParam == SIZE_MINIMIZED )
	{
		// When the window is minimized, set all the key states to up so that when the window becomes back in focus it won't be fucked up.
		for ( auto &key: _KeyStates )
			key = CKeyState::UP;
		return false;
	}

	auto bReturn = false;

	switch ( uMsg )
	{
		case WM_MBUTTONDBLCLK:
		case WM_RBUTTONDBLCLK:
		case WM_LBUTTONDBLCLK:
		case WM_XBUTTONDBLCLK:
		case WM_MBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_LBUTTONDOWN:
		case WM_XBUTTONDOWN:
		case WM_MBUTTONUP:
		case WM_RBUTTONUP:
		case WM_LBUTTONUP:
		case WM_XBUTTONUP:
			bReturn |= ProcessMouseMessage( uMsg, wParam );
			break;
		case WM_KEYDOWN:
		case WM_KEYUP:
		case WM_SYSKEYDOWN:
		case WM_SYSKEYUP:
		case WM_CHAR:
			bReturn |= ProcessKeyboardMessage( uMsg, wParam );
			break;
		case WM_MOUSEMOVE:
		{
			iMouseX = *reinterpret_cast< short* >( &lParam );
			iMouseY = *reinterpret_cast< short* >( uintptr_t( &lParam ) + sizeof( short ) );

			for ( const auto &_Callback: _Callbacks.GetCallbacks< mouse_move_callback_t >( ) )
				bReturn |= _Callback( iMouseX, iMouseY );
		}
		break;

		case WM_MOUSEWHEEL:
		{
			const auto sDelta = GET_WHEEL_DELTA_WPARAM( wParam );
			const POINT pntMouse { *reinterpret_cast< short* >( &lParam ), *reinterpret_cast< short* >( uintptr_t( &lParam ) + sizeof( short ) ) };

			for ( const auto &_Callback: _Callbacks.GetCallbacks< scroll_callback_t >( ) )
				bReturn |= _Callback( sDelta, pntMouse.x, pntMouse.y );
		}

		default:
			break;
	}

	return bReturn;
}

void CInputHandler::AddCallback( const key_callback_t &_Callback, const key_t &_Key )
{
	_Callbacks.AddCallback( _Callback, _Key );
}

CKeyState CInputHandler::GetKeyState( const key_t &_KeyCode )
{
	return _KeyStates[ _KeyCode ];
}

vector2_t CInputHandler::GetMouseLocation( )
{
	return { double( iMouseX ), double( iMouseY ) };
}

moment_t CInputHandler::GetTimeSinceKeyPress( const key_t &_Key )
{
	return GetMoment( ) - mmtLastKeyPressTime[ _Key ];
}

void CInputHandler::GetMousePos( int &x, int &y )
{
	x = iMouseX;
	y = iMouseY;
}

CInputHandler _Input;
