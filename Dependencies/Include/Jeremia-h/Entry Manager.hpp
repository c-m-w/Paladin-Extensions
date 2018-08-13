/// Entry Manager.hpp

#pragma once

#if !defined( PX_ENTRY_AS_WIN ) && !defined( PX_ENTRY_AS_DLL ) && !defined( PX_ENTRY_AS_NONE )
#pragma message( "fatal error PX0: No automatic entry creation method defined. Use '#define PX_ENTRY_AS_WIN' or '#define PX_ENTRY_AS_DLL' when including the framework to use automatic entry creation. Use '#define PX_ENTRY_AS_NONE' to disable automatic entry management." )
#elif defined( PX_ENTRY_AS_WIN ) && !defined( PX_ENTRY_AS_DLL ) && !defined( PX_ENTRY_AS_NONE )

#include <Windows.h>

namespace PX
{
	inline HINSTANCE hinstWin;
};

extern void OnLaunch( );

namespace
{
#if defined( UNICODE )
	int APIENTRY wWinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow )
#else
	int APIENTRY WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow )
#endif
	{
#if defined( UNICODE )
#if !defined( PX_INSTANCE_ID )
#pragma message( "warning PX2: No instance identifier defined." )
		HANDLE hSingleInstanceMutex = CreateMutex( NULL, TRUE, L"Paladin Extensions" );
#endif
		HANDLE hSingleInstanceMutex = CreateMutex( NULL, TRUE, L"Paladin Extensions " PX_INSTANCE_ID );
#else
#if !defined( PX_INSTANCE_ID )
#pragma message( "warning PX2: No instance identifier defined." )
		HANDLE hSingleInstanceMutex = CreateMutex( NULL, TRUE, "Paladin Extensions" );
#endif
		HANDLE hSingleInstanceMutex = CreateMutex( NULL, TRUE, "Paladin Extensions " PX_INSTANCE_ID );
#endif
		if ( hSingleInstanceMutex == INVALID_HANDLE_VALUE || GetLastError( ) == ERROR_ALREADY_EXISTS )
			return 0;

		if ( hInstance && hInstance != INVALID_HANDLE_VALUE )
			PX::hinstWin = hInstance;

#if defined( _DEBUG )
		AllocConsole( );
		freopen_s( new FILE* { nullptr }, "CONOUT$", "w", stdout );
#endif

		OnLaunch( );

		return 0;
	}
}

#elif !defined( PX_ENTRY_AS_WIN ) && defined( PX_ENTRY_AS_DLL ) && !defined( PX_ENTRY_AS_NONE )

#include <Jeremia-h/Standard Library.hpp>
#include <Windows.h>

namespace PX
{
	inline HINSTANCE hinstDLL;
};

extern void OnAttach( );
extern void OnDetach( );

inline void Detach( )
{
#if defined( _DEBUG )
	FreeConsole( );
#endif
	OnDetach( );
	FreeLibraryAndExitThread( PX::hinstDLL, 0 );
}

namespace
{
	DWORD WINAPI ThreadProc( _In_ LPVOID lpParameter )
	{
#if defined( _DEBUG )
		AllocConsole( );
		freopen_s( new FILE* { nullptr }, "CONOUT$", "w", stdout );
#endif

		OnAttach( );
		return TRUE;
	}

	BOOL WINAPI DllMain( _In_ HINSTANCE hinstDLL, _In_ DWORD fdwReason, _In_ LPVOID lpvReserved )
	{
#if defined( UNICODE )
#if !defined( PX_INSTANCE_ID )
#define PX_INSTANCE_ID L"0"
#endif
		HANDLE hSingleInstanceMutex = CreateMutex( NULL, TRUE, L"Paladin Extensions " PX_INSTANCE_ID );
#else
#if !defined( PX_INSTANCE_ID )
#define PX_INSTANCE_ID "0"
#endif
		HANDLE hSingleInstanceMutex = CreateMutex( NULL, TRUE, "Paladin Extensions " PX_INSTANCE_ID );
#endif
		if ( hSingleInstanceMutex == INVALID_HANDLE_VALUE || GetLastError( ) == ERROR_ALREADY_EXISTS )
			return FALSE;

		switch ( fdwReason )
		{
			case DLL_PROCESS_ATTACH:
			{
				if ( hinstDLL && hinstDLL != INVALID_HANDLE_VALUE )
				{
					DisableThreadLibraryCalls( hinstDLL );
					PX::hinstDLL = hinstDLL;
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
}

#elif !defined( PX_ENTRY_AS_WIN ) && !defined( PX_ENTRY_AS_DLL ) && defined( PX_ENTRY_AS_NONE )
#pragma message( "warning PX1: You must manage standard console output yourself." )
#else
#pragma message( "fatal error PX2: Too many automatic entry creation methods defined." )
#endif
