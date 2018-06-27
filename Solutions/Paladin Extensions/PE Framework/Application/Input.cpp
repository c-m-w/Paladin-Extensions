#include "../Framework.hpp"

namespace Paladin 
{
	void CWindowInput::OnEvent( HWND hwHWND, UINT uMessage, WPARAM uwParam, LPARAM llParam ) 
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
				ProcessMouseMessage( uMessage, uwParam, llParam );
				break;
			case WM_KEYDOWN:
			case WM_KEYUP:
			case WM_SYSKEYDOWN:
			case WM_SYSKEYUP:
				ProcessKeyboardMessage( uMessage, uwParam, llParam );
				break;
			default:
				return;
		}
	}

	void CWindowInput::ProcessMouseMessage( UINT uMessage, WPARAM uwParam, LPARAM llParam ) 
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
				uKey = HIWORD( uwParam );
				break;
			default:
				return;
		}

		ProcessKey( uKey, uMessage );
	}

	void CWindowInput::ProcessKeyboardMessage( UINT uMessage, WPARAM uwParam, LPARAM llParam )
	{
		const auto uKey = uwParam;

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

		ProcessKey( uKey, uMessage );
	}

	void CWindowInput::ProcessKey( unsigned uKey, UINT uMessage )
	{
		uKeyState[ uKey ] = uMessage % 2 ? EKeyState::DOWN : EKeyState::UP;
		ulKeyDownTime[ uKey ] = GetMoment( );
		uLastKeyPressed = uKey;

		for ( auto fnCallback : vecKeyCallback[ uKey ] )
			fnCallback( uKey );
	}

	EKeyState CWindowInput::GetKeyState( unsigned uKey )
	{
		return uKeyState[ uKey ];
	}

	unsigned CWindowInput::GetLastPressedKey( )
	{
		return uLastKeyPressed;
	}

	moment_t CWindowInput::TimeSinceKeyPress( unsigned uKey )
	{
		return GetMoment( ) - ulKeyDownTime[ uKey ];
	}

	void CWindowInput::AddKeyCallback( unsigned uKey, std::function< void( int ) > fnCallback ) 
	{
		vecKeyCallback[ uKey ].emplace_back( fnCallback );
	}
}
