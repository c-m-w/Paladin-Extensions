/// Entry Manager.hpp

#pragma once

#if !defined PX_ENTRY_AS_WIN && !defined PX_ENTRY_AS_DLL && !defined PX_ENTRY_AS_NONE
#pragma message( "fatal error PX0: No automatic entry creation method defined. Use '#define PX_ENTRY_AS_WIN' or '#define PX_ENTRY_AS_DLL' when including the framework to use automatic entry creation. Use '#define PX_ENTRY_AS_NONE' to disable automatic entry management." )
#elif defined PX_ENTRY_AS_WIN && !defined PX_ENTRY_AS_DLL && !defined PX_ENTRY_AS_NONE

#include "Standard Library.hpp"
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

#if !defined PX_SDK || !defined PX_API || !defined PX_EXT
#define PX_SDK inline
#define PX_API __cdecl
#define PX_EXT extern
#define PX_STAND_ALONE
#endif

namespace PX
{
	PX_SDK HINSTANCE hinstWin;
}

namespace
{
	PX_SDK HANDLE hSingleInstanceMutex;
	PX_SDK FILE* pConsoleOutput;
}

void PX_API OnLaunch( );

#if defined PX_INSTANCE_ID
int APIENTRY
#if defined UNICODE
wWinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine,
#else
WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
#endif
		 _In_ int nCmdShow )
{
#if defined UNICODE
	hSingleInstanceMutex = CreateMutex( nullptr, TRUE, L"Paladin Extensions " PX_INSTANCE_ID );
#else
	hSingleInstanceMutex = CreateMutex( nullptr, TRUE, "Paladin Extensions " PX_INSTANCE_ID );
#endif
	if ( hSingleInstanceMutex == nullptr
	  || GetLastError( ) == ERROR_ALREADY_EXISTS )
		return -1;

	if ( hInstance && hInstance != INVALID_HANDLE_VALUE )
		PX::hinstWin = hInstance;

#if defined _DEBUG
	AllocConsole( );
	if ( 0 != freopen_s( &pConsoleOutput, "CONOUT$", "w", stdout ) )
		return -1;
#endif

	OnLaunch( );

#if defined _DEBUG
	pConsoleOutput && fclose( pConsoleOutput );
	FreeConsole( );
#endif
	CloseHandle( hSingleInstanceMutex );
	return 0;
}
#endif

#if defined PX_STAND_ALONE
#undef PX_EXT
#undef PX_API
#undef PX_SDK
#endif

#undef NOMINMAX
#undef WIN32_LEAN_AND_MEAN

#elif !defined PX_ENTRY_AS_WIN && defined PX_ENTRY_AS_DLL && !defined PX_ENTRY_AS_NONE

#include "Standard Library.hpp"
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

#if !defined PX_SDK || !defined PX_API || !defined PX_EXT
#define PX_SDK inline
#define PX_API __cdecl
#define PX_EXT extern
#define PX_STAND_ALONE
#endif

namespace PX
{
	PX_SDK HINSTANCE hinstDLL;
}

void PX_API OnAttach( );
void PX_API OnDetach( );

namespace
{
	PX_SDK HANDLE hSingleInstanceMutex;
	PX_SDK FILE* pConsoleOutput;
}

PX_SDK void PX_API Detach( )
{
#if defined _DEBUG
	fclose( pConsoleOutput );
	FreeConsole( );
#endif
	CloseHandle( hSingleInstanceMutex );
#if defined PX_INSECURE_INITIALIZATION
	FreeLibraryAndExitThread( PX::hinstDLL, TRUE );
#else
	OnDetach( );
#endif
}

namespace
{
	DWORD WINAPI ThreadProc( _In_ LPVOID lpParameter )
	{
#if defined _DEBUG
		AllocConsole( );
		freopen_s( &pConsoleOutput, "CONOUT$", "w", stdout );
#endif

		OnAttach( );
		return TRUE;
	}
}

#if defined PX_INSTANCE_ID
BOOL WINAPI DllMain( _In_ HINSTANCE hinstDll, _In_ DWORD fdwReason, _In_ LPVOID lpvReserved )
{
	switch ( fdwReason )
	{
		case DLL_PROCESS_ATTACH:
		{
#if defined UNICODE
			hSingleInstanceMutex = CreateMutex( nullptr, TRUE, L"Paladin Extensions " PX_INSTANCE_ID );
#else
			hSingleInstanceMutex = CreateMutex( nullptr, TRUE, "Paladin Extensions " PX_INSTANCE_ID );
#endif
			if ( hSingleInstanceMutex == nullptr
			  || GetLastError( ) == ERROR_ALREADY_EXISTS )
				return FALSE;
		
			if ( hinstDll && hinstDll != INVALID_HANDLE_VALUE )
			{
				DisableThreadLibraryCalls( hinstDll );
				PX::hinstDLL = hinstDll;
			}

#if defined PX_INSECURE_INITIALIZATION
			HANDLE hThreadProc = CreateThread( nullptr, 0, ThreadProc, lpvReserved, 0, nullptr );
			return hThreadProc != nullptr;
#else
			return ThreadProc( lpvReserved );
#endif
		}
		case DLL_PROCESS_DETACH:
		{
			OnDetach( );
			return TRUE;
		}
		default:
		{
			return TRUE; // review: should this be false since it's an unhandled dllmain call?
		}
	}
}
#endif

#if defined PX_STAND_ALONE
#undef PX_EXT
#undef PX_API
#undef PX_SDK
#endif

#undef NOMINMAX
#undef WIN32_LEAN_AND_MEAN

#elif !defined PX_ENTRY_AS_WIN && !defined PX_ENTRY_AS_DLL && defined PX_ENTRY_AS_NONE
#pragma message( "warning PX1: You must manage standard console output yourself." )
#else
#pragma message( "fatal error PX2: Too many automatic entry creation methods defined." )
#endif
