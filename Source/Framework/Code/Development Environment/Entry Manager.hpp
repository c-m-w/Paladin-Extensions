/// Entry Manager.hpp

#pragma once

#if !defined NO_ENTRY && !defined STD_ENTRY && !defined WIN_ENTRY && !defined DLL_ENTRY

#pragma message( ERROR( EENTRY1, No automatic entry creation method defined. Use '#define WIN_ENTRY' or '#define DLL_ENTRY' when including the framework to use automatic entry creation. Use '#define NO_ENTRY' to disable automatic entry management. ) )

#elif defined NO_ENTRY && !defined STD_ENTRY && !defined WIN_ENTRY && !defined DLL_ENTRY

#if defined _DEBUG && !defined ACKNOWLEDGED_ENTRY_WARNING_1
#pragma message( WARNING( WENTRY1, You must manage console output yourself. Use '#define ACKNOWLEDGED_ENTRY_WARNING_1' to stop printing this message. ) )
#endif

#elif defined STD_ENTRY && !defined WIN_ENTRY && !defined DLL_ENTRY

void OnLaunch( );

int main( )
{
	SetLastError( 0u );
	HANDLE hMutex = CreateMutex( NULL, FALSE, ENC( StringizeValue( __TIMESTAMP__ ) ) );
	if ( hMutex == NULL || GetLastError( ) == ERROR_ALREADY_EXISTS )
		return 0;

#if defined _DEBUG
	FILE *pConsoleOutput;
	AllocConsole( );
	if ( freopen_s( &pConsoleOutput, ENC( "CONOUT$" ), ENC( "w" ), stdout ) != 0
		 || pConsoleOutput == nullptr )
		return pConsoleOutput ? CloseHandle( pConsoleOutput ) != 0 : 0;
#endif

	OnLaunch( );

#if defined _DEBUG
	fclose( pConsoleOutput );
	FreeConsole( );
#endif

	CloseHandle( hMutex );
	return 0;
}

#elif !defined STD_ENTRY && defined WIN_ENTRY && !defined DLL_ENTRY

void OnLaunch( );

inline HINSTANCE hinstWin;

int APIENTRY
#if defined UNICODE
wWinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine,
#else
WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
#endif
_In_ int nCmdShow )
{
	SetLastError( 0u );
	HANDLE hMutex = CreateMutex( NULL, FALSE, ENC( StringizeValue( __TIMESTAMP__ ) ) );
	if ( hMutex == NULL )
		return 0;

	if ( hInstance && hInstance != INVALID_HANDLE_VALUE )
		hinstWin = hInstance;

#if defined _DEBUG
	FILE *pConsoleOutput;
	AllocConsole( );
	if ( freopen_s( &pConsoleOutput, ENC( "CONOUT$" ), ENC( "w" ), stdout ) != 0 || pConsoleOutput == nullptr )
		return pConsoleOutput ? CloseHandle( pConsoleOutput ) != 0 : 0;
#endif

	OnLaunch( );

#if defined _DEBUG
	fclose( pConsoleOutput );
	FreeConsole( );
#endif

	CloseHandle( hMutex );
	return 0;
}

#elif !defined STD_ENTRY && !defined WIN_ENTRY && defined DLL_ENTRY

// TDOD when we're injected, we should get the region of memory that we are in order to clear it when we unload

void OnAttach( );
void OnDetach( );

inline HINSTANCE hinstDll;

#if defined _DEBUG
namespace
{
	DWORD WINAPI ThreadProc( _In_ LPVOID lpParameter )
	{
		OnAttach( );
		return TRUE;
	}
}
#endif

BOOL WINAPI DllMain( _In_ HINSTANCE hinstDLL, _In_ DWORD fdwReason, _In_ LPVOID lpvReserved )
{
	switch ( fdwReason )
	{
		case DLL_PROCESS_ATTACH:
		{
			SetLastError( 0u );
			HANDLE hMutex = CreateMutex( NULL, FALSE, ENC( StringizeValue( __TIMESTAMP__ ) ) );
			if ( hMutex == NULL || GetLastError( ) == ERROR_ALREADY_EXISTS )
				return FALSE;

			if ( hinstDLL && hinstDLL != INVALID_HANDLE_VALUE )
#if !defined _DEBUG
				if ( DisableThreadLibraryCalls( hinstDll = hinstDLL ) == 0 )
					return FALSE;
#else
				hinstDll = hinstDLL;
#endif

#if defined _DEBUG
			FILE *pConsoleOutput;
			AllocConsole( );
			if ( freopen_s( &pConsoleOutput, ENC( "CONOUT$" ), ENC( "w" ), stdout ) != 0 || pConsoleOutput == nullptr )
			{
				if ( pConsoleOutput )
					CloseHandle( pConsoleOutput );
				return FALSE;
			}
#endif

#if defined _DEBUG
			HANDLE hThreadProc = CreateThread( nullptr, 0, ThreadProc, lpvReserved, 0, nullptr );
			return hThreadProc != nullptr;
#else
			OnAttach( );
			return TRUE;
#endif
		}
		case DLL_PROCESS_DETACH:
			OnDetach( );
			return TRUE;
		default:
			return TRUE;
	}
}

#else

#pragma message( ERROR( EENTRY2, Too many automatic entry creation methods defined. ) )

#endif
