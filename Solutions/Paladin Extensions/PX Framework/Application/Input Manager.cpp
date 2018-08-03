/// Input Manager.cpp

#include "../PX Framework.hpp"

namespace PX
{
	void PX_API CInputManager::ProcessKey( unsigned uKey, UINT uMessage )
	{
		stateKeys[ uKey ] = uMessage % 2 ? DOWN : UP;
		if ( stateKeys[ uKey ] )
		{
			mmtKeyDownTime[ uKey ] = Tools::GetMoment( );
			uLastKeyPressed = uKey;
		}

		for each ( auto fnCallback in vecfnKeyCallback[ uKey ] )
			fnCallback( uKey );

		for each ( auto fnCallback in vecfnGlobalCallbacks )
			fnCallback( uKey );
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

	void PX_API CInputManager::OnEvent( HWND hwWindowHandle, UINT uMessage, WPARAM wParam, LPARAM lParam ) // hwWindowHandle is unused
	{
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
			default:;
		}
	}

	CInputManager::EKeyState PX_API CInputManager::GetKeyState( unsigned uKey )
	{
		return stateKeys[ uKey ];
	}

	unsigned PX_API CInputManager::GetLastPressedKey( )
	{
		return uLastKeyPressed;
	}

	Tools::moment_t PX_API CInputManager::TimeSinceKeyPress( unsigned uKey )
	{
		return Tools::GetMoment( ) - mmtKeyDownTime[ uKey ];
	}

	void PX_API CInputManager::AddKeyCallback( unsigned uKey, std::function< void( int ) > fnCallback )
	{
		vecfnKeyCallback[ uKey ].emplace_back( fnCallback );
	}

	void PX_API CInputManager::AddGlobalCallback( std::function< void( unsigned ) > fnCallback )
	{
		vecfnGlobalCallbacks.emplace_back( fnCallback );
	}
}
