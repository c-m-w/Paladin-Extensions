/// Entry Manager.hpp

#pragma once

#if !defined( ENTRY_AS_WIN ) && !defined( ENTRY_AS_DLL ) && !defined( ENTRY_AS_NONE )
#pragma message( "fatal error PE0: No automatic entry creation method defined. Use '#define ENTRY_AS_WIN' or '#define ENTRY_AS_DLL' when including the framework to use automatic entry creation. Use '#define ENTRY_AS_NONE' to disable automatic entry management." )
#elif defined( ENTRY_AS_WIN ) && !defined( ENTRY_AS_DLL ) && !defined( ENTRY_AS_NONE )

#include <J-e-r-e-m-i-a-h/Standard Library.hpp>
#include <Windows.h>

namespace Paladin
{
    static HINSTANCE hinstWin;
};

extern void OnLaunch( );

#if defined( UNICODE )
int WINAPI wWinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow )
#else
int WINAPI WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow )
#endif
{
#if defined( UNICODE )
    HANDLE hSingleInstanceMutex = CreateMutex( NULL, TRUE, L"Paladin Extensions" );
#else
    HANDLE hSingleInstanceMutex = CreateMutex( NULL, TRUE, "Paladin Extensions" );
#endif
    if ( hSingleInstanceMutex == INVALID_HANDLE_VALUE || GetLastError( ) == ERROR_ALREADY_EXISTS )
        return -1;

    if ( hInstance && hInstance != INVALID_HANDLE_VALUE )
        Paladin::hinstWin = hInstance;

#if defined( _DEBUG )
    AllocConsole( );
    freopen_s( new FILE * { nullptr }, "CONOUT$", "w", stdout );
#endif

    OnLaunch( );
    return 0;
}

#elif !defined( ENTRY_AS_WIN ) && defined( ENTRY_AS_DLL ) && !defined( ENTRY_AS_NONE )

#include <J-e-r-e-m-i-a-h/Standard Namespace.hpp>
#include <Windows.h>

namespace Paladin
{
    static HINSTANCE hinstDLL;
};

extern void OnAttach( );
extern void OnDetach( );

inline void Detach( )
{
#if defined( _DEBUG )
    FreeConsole( );
#endif
    OnDetach( );
    FreeLibraryAndExitThread( Paladin::hinstDLL, 0 );
}

inline DWORD WINAPI ThreadProc( _In_ LPVOID lpParameter )
{
#if defined( _DEBUG )
    AllocConsole( );
    freopen_s( new FILE * { nullptr }, "CONOUT$", "w", stdout );
#endif

    OnAttach( );
    return NULL;
}

BOOL WINAPI DllMain( _In_ HINSTANCE hinstDLL, _In_ DWORD fdwReason, _In_ LPVOID lpvReserved )
{
#if defined( UNICODE )
    HANDLE hSingleInstanceMutex = CreateMutex( NULL, TRUE, L"Paladin Extensions" );
#else
    HANDLE hSingleInstanceMutex = CreateMutex( NULL, TRUE, "Paladin Extensions" );
#endif
    if ( GetLastError( ) == ERROR_ALREADY_EXISTS )
        return FALSE;

    switch ( fdwReason )
    {
        case DLL_PROCESS_ATTACH:
        {
            if ( hinstDLL && hinstDLL != INVALID_HANDLE_VALUE )
            {
                DisableThreadLibraryCalls( hinstDLL );
                Paladin::hinstDLL = hinstDLL;
            }

            HANDLE hThreadProc = CreateThread( nullptr, 0, ThreadProc, lpvReserved, 0, nullptr );
            if ( !hThreadProc || hThreadProc == INVALID_HANDLE_VALUE )
                return FALSE;

            return TRUE;
        }
        case DLL_PROCESS_DETACH:
#if defined( _DEBUG )
            FreeConsole( );
#endif
            OnDetach( );
            return TRUE;
        default:
            return FALSE;
    }
}

#elif !defined( ENTRY_AS_WIN ) && !defined( ENTRY_AS_DLL ) && defined( ENTRY_AS_NONE )
#pragma message( "warning PE1: You must manage standard console output yourself." )
#else
#pragma message( "fatal error PE2: Too many automatic entry creation methods defined." )
#endif
