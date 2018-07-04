/// Input Manager.cpp

#include "../PX Framework.hpp"

namespace PX
{
    void PX_API IInputManager::ProcessKey( unsigned uKey, UINT uMessage )
    {
        uKeyState[ uKey ] = uMessage % 2 ? DOWN : UP;
        ulKeyDownTime[ uKey ] = Utilities::GetMoment( );
        uLastKeyPressed = uKey;

        for ( auto fnCallback: vecKeyCallback[ uKey ] )
            fnCallback( uKey );
    }

    void PX_API IInputManager::ProcessMouseMessage( UINT uMessage, WPARAM wParam, LPARAM lParam ) // lParam is unused
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

    void PX_API IInputManager::ProcessKeyboardMessage( UINT uMessage, WPARAM wParam, LPARAM lParam ) // lParam is unused
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

    void PX_API IInputManager::OnEvent( HWND hwWindowHandle, UINT uMessage, WPARAM wParam, LPARAM lParam ) // hwWindowHandle is unused
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
            default: ;
        }
    }

    IInputManager::EKeyState PX_API IInputManager::GetKeyState( unsigned uKey )
    {
        return uKeyState[ uKey ];
    }

    unsigned PX_API IInputManager::GetLastPressedKey( )
    {
        return uLastKeyPressed;
    }

    Utilities::moment_t PX_API IInputManager::TimeSinceKeyPress( unsigned uKey )
    {
        return Utilities::GetMoment( ) - ulKeyDownTime[ uKey ];
    }

    void PX_API IInputManager::AddKeyCallback( unsigned uKey, std::function< void( int ) > fnCallback )
    {
        vecKeyCallback[ uKey ].emplace_back( fnCallback );
    }
}
