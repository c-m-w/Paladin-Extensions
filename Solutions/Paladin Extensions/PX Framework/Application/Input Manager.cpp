/// Input Manager.cpp

#include "PX Precompiled.hpp"
#define PX_USE_NAMESPACES
#include "../PX Framework.hpp"

namespace PX
{
	void PX_API CInputManager::ProcessKey( unsigned uKey, bool bKeyDown )
	{
		if ( ( ksKeys[ uKey ] = bKeyDown ? CKeyState::DOWN : CKeyState::UP ) == true )
		{
			mmtKeyDownTime[ uKey ] = GetMoment( );
			uLastKeyPressed = uKey;
		}

		for each ( auto fnCallback in vecfnKeyCallback[ uKey ] )
			fnCallback( bKeyDown );

		const auto uSize = vecfnGlobalCallbacks.size( );
		for( auto u = 0u; u < uSize; u++ )
			vecfnGlobalCallbacks[ u ]( uKey, bKeyDown );
	}

	void PX_API CInputManager::ProcessMouseMessage( UINT uMessage, WPARAM wParam )
	{
		unsigned uKey;
		auto bKeyDown = false;

		switch ( uMessage )
		{
			case WM_MBUTTONDOWN:
				bKeyDown = true;
			case WM_MBUTTONUP:
				uKey = VK_MBUTTON;
				break;
			case WM_RBUTTONDOWN:
				bKeyDown = true;
			case WM_RBUTTONUP:
				uKey = VK_RBUTTON;
				break;
			case WM_LBUTTONDOWN:
				bKeyDown = true;
			case WM_LBUTTONUP:
				uKey = VK_LBUTTON;
				break;
			case WM_XBUTTONDOWN:
				bKeyDown = true;
			case WM_XBUTTONUP:
				uKey = HIWORD( wParam ) == XBUTTON1 ? VK_XBUTTON1 : VK_XBUTTON2;
				break;
			default:
				return;
		}

		ProcessKey( uKey, bKeyDown );
	}

	void PX_API CInputManager::ProcessKeyboardMessage( UINT uMessage, WPARAM wParam ) // lParam is unused
	{
		auto bKeyDown = false;

		switch ( uMessage )
		{
			case WM_KEYDOWN:
			case WM_SYSKEYDOWN:
				bKeyDown = true;
			case WM_KEYUP:
			case WM_SYSKEYUP:
				break;
			default:
				return;
		}

		ProcessKey( wParam, bKeyDown );
	}

	CInputManager::CInputManager( ) PX_NOX: ksKeys( ), mmtKeyDownTime( ), uLastKeyPressed( )
	{ }

	void PX_API CInputManager::OnEvent( HWND _hwWindowHandle, UINT uMessage, WPARAM wParam, LPARAM lParam )
	{
		if ( uMessage == WM_SIZE && wParam == SIZE_MINIMIZED )
		{
			// When the window is minimized, set all the key states to up so that when the window becomes back in focus it won't be fucked up.
			for each ( auto &key in ksKeys )
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
				ProcessMouseMessage( uMessage, wParam );
				break;
			case WM_KEYDOWN:
			case WM_KEYUP:
			case WM_SYSKEYDOWN:
			case WM_SYSKEYUP:
				ProcessKeyboardMessage( uMessage, wParam );
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
