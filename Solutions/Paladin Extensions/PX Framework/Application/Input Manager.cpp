/// Input Manager.cpp

#define PX_USE_NAMESPACES
#include "../PX Framework.hpp"

namespace PX
{
	void PX_API CInputManager::ProcessKey( unsigned uKey, UINT uMessage )
	{
		ksKeys[ uKey ] = uMessage % 2 ? CKeyState::DOWN : CKeyState::UP;
		if ( ksKeys[ uKey ] )
		{
			mmtKeyDownTime[ uKey ] = GetMoment( );
			uLastKeyPressed = uKey;
		}

		for each ( auto fnCallback in vecfnKeyCallback[ uKey ] )
			fnCallback( bool( ksKeys[ uKey ] ) );

		for each ( auto fnCallback in vecfnGlobalCallbacks )
			fnCallback( uKey, bool( ksKeys[ uKey ] ) );
	}

	void PX_API CInputManager::ProcessMouseMessage( UINT uMessage, WPARAM wParam, LPARAM lParam ) // lParam is unused
	{
		unsigned uKey;

		switch ( uMessage )
		{
			case WM_MBUTTONDOWN:
			case WM_MBUTTONUP:
				uKey = VK_MBUTTON;
				break;
			case WM_RBUTTONDOWN:
			case WM_RBUTTONUP:
				uKey = VK_RBUTTON;
				break;
			case WM_LBUTTONDOWN:
			case WM_LBUTTONUP:
				uKey = VK_LBUTTON;
				break;
			case WM_XBUTTONDOWN:
			case WM_XBUTTONUP:
				uKey = HIWORD( wParam );
				break;
			default:
				return;
		}

		ProcessKey( uKey, uMessage );
	}

	void PX_API CInputManager::ProcessKeyboardMessage( UINT uMessage, WPARAM wParam, LPARAM lParam ) // lParam is unused
	{
		switch ( uMessage )
		{
			case WM_KEYDOWN:
			case WM_SYSKEYDOWN:
			case WM_KEYUP:
			case WM_SYSKEYUP:
				break;
			default:
				return;
		}

		ProcessKey( wParam, uMessage );
	}

	CInputManager::CInputManager( ): ksKeys( ), mmtKeyDownTime( ), uLastKeyPressed( )
	{ }

	void PX_API CInputManager::OnEvent( HWND hwWindowHandle, UINT uMessage, WPARAM wParam, LPARAM lParam ) // hwWindowHandle is unused
	{
		if ( uMessage == WM_SIZE && wParam == SIZE_MINIMIZED )
		{
			// When the window is minimized, set all the key states to up so that when the window becomes back in focus it won't be fucked up.
			for each( auto& key in ksKeys )
				key = CKeyState::UP;
			return;
		}

		switch ( uMessage )
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
				ProcessMouseMessage( uMessage, wParam, lParam );
				break;
			case WM_KEYDOWN:
			case WM_KEYUP:
			case WM_SYSKEYDOWN:
			case WM_SYSKEYUP:
				ProcessKeyboardMessage( uMessage, wParam, lParam );
				break;
			default:
				break;
		}
	}

	CKeyState PX_API CInputManager::GetKeyState( unsigned uKey )
	{
		return ksKeys[ uKey ];
	}

	unsigned PX_API CInputManager::GetLastPressedKey( )
	{
		return uLastKeyPressed;
	}

	moment_t PX_API CInputManager::TimeSinceKeyPress( unsigned uKey )
	{
		return GetMoment( ) - mmtKeyDownTime[ uKey ];
	}

	void PX_API CInputManager::AddKeyCallback( unsigned uKey, std::function< void( bool ) > fnCallback )
	{
		vecfnKeyCallback[ uKey ].emplace_back( fnCallback );
	}

	void PX_API CInputManager::AddGlobalCallback( std::function< void( unsigned, bool ) > fnCallback )
	{
		vecfnGlobalCallbacks.emplace_back( fnCallback );
	}
}
