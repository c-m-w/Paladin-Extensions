/// Entry Manager.hpp

#pragma once

#if !defined PX_ENTRY_AS_WIN && !defined PX_ENTRY_AS_DLL && !defined PX_ENTRY_AS_NONE
#pragma message( "fatal error PX0: No automatic entry creation method defined. Use '#define PX_ENTRY_AS_WIN' or '#define PX_ENTRY_AS_DLL' when including the framework to use automatic entry creation. Use '#define PX_ENTRY_AS_NONE' to disable automatic entry management." )
#elif defined PX_ENTRY_AS_WIN && !defined PX_ENTRY_AS_DLL && !defined PX_ENTRY_AS_NONE

#include <Jeremia-h/Standard Library.hpp>
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

#define PX_SDK inline
#define PX_API __cdecl
#define PX_EXT extern

namespace PX
{
	PX_SDK HINSTANCE hinstWin;
};

PX_EXT void OnLaunch( );

int APIENTRY
#if defined UNICODE
wWinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine,
#else
WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
#endif
		 _In_ int nCmdShow )
{
#if defined UNICODE
#if !defined PX_INSTANCE_ID
#define PX_INSTANCE_ID L"0"
#endif
	HANDLE hSingleInstanceMutex = CreateMutex( NULL, TRUE, L"Paladin Extensions " PX_INSTANCE_ID );
#else
#if !defined PX_INSTANCE_ID
#define PX_INSTANCE_ID "0"
#endif
	HANDLE hSingleInstanceMutex = CreateMutex( NULL, TRUE, "Paladin Extensions " PX_INSTANCE_ID );
#endif
	if ( hSingleInstanceMutex == INVALID_HANDLE_VALUE || GetLastError( ) == ERROR_ALREADY_EXISTS )
		return -1;

	if ( hInstance && hInstance != INVALID_HANDLE_VALUE )
		PX::hinstWin = hInstance;

#if defined _DEBUG
	AllocConsole( );
	freopen_s( new FILE* { nullptr }, "CONOUT$", "w", stdout );
#endif

	OnLaunch( );

	return 0;
}

#undef PX_EXT
#undef PX_API
#undef PX_SDK

#undef NOMINMAX
#undef WIN32_LEAN_AND_MEAN

#elif !defined PX_ENTRY_AS_WIN && defined PX_ENTRY_AS_DLL && !defined PX_ENTRY_AS_NONE

#include <Jeremia-h/Standard Library.hpp>
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

#define PX_SDK inline
#define PX_API __cdecl
#define PX_EXT extern

namespace PX
{
	PX_SDK HINSTANCE hinstDLL;
};

PX_EXT void PX_API OnAttach( );
PX_EXT void PX_API OnDetach( );

PX_SDK void PX_API Detach( )
{
#if defined _DEBUG
	FreeConsole( );
#endif
	OnDetach( );
#if !defined PX_MANUAL_MAP_DLL
	FreeLibraryAndExitThread( PX::hinstDLL, 0 );
#endif
}

namespace
{
	DWORD WINAPI ThreadProc( _In_ LPVOID lpParameter )
	{
#if defined _DEBUG
		AllocConsole( );
		freopen_s( new FILE* { nullptr }, "CONOUT$", "w", stdout );
#endif

		OnAttach( );
		return TRUE;
	}
}

BOOL WINAPI DllMain( _In_ HINSTANCE hinstDLL, _In_ DWORD fdwReason, _In_ LPVOID lpvReserved )
{
#if defined UNICODE
#if !defined PX_INSTANCE_ID
#define PX_INSTANCE_ID L"0"
#endif
	HANDLE hSingleInstanceMutex = CreateMutex( NULL, TRUE, L"Paladin Extensions " PX_INSTANCE_ID );
#else
#if !defined PX_INSTANCE_ID
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

#if defined PX_INSECURE_INITIALIZATION
			HANDLE hThreadProc = CreateThread( nullptr, 0, ThreadProc, lpvReserved, 0, nullptr );
			if ( !hThreadProc || hThreadProc == INVALID_HANDLE_VALUE )
				return FALSE;
#else
			ThreadProc( lpvReserved );
#endif
			return TRUE;
		}
		case DLL_PROCESS_DETACH:
#if defined _DEBUG
			FreeConsole( );
#endif
			OnDetach( );
			return TRUE;
		default:
			return FALSE;
	}
}

#undef PX_EXT
#undef PX_API
#undef PX_SDK

#undef NOMINMAX
#undef WIN32_LEAN_AND_MEAN

#elif !defined PX_ENTRY_AS_WIN && !defined PX_ENTRY_AS_DLL && defined PX_ENTRY_AS_NONE
#pragma message( "warning PX1: You must manage standard console output yourself." )
#else
#pragma message( "fatal error PX2: Too many automatic entry creation methods defined." )
#endif
