#include "main.h"

int _stdcall Main( )
{
	return 0;
}

#ifdef _DEBUG

/*
int CALLBACK WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow )
{
	SET_DEBUG( );

	int argc { };
	LPWSTR *argv = CommandLineToArgvW( GetCommandLine( ), &argc );

	if ( !argv )
	{
		LOG_DEBUG( ERR, L"Unable to get argument list" );
		Sleep( 7000 );
		RESTORE_DEBUG( );
		return 1;
	}

	if ( argc < 2 )
	{
		LOG_DEBUG( ERR, L"Invalid argument count" );
		Sleep( 7000 );
		RESTORE_DEBUG( );
		return 1;
	}

	LOG_DEBUG( DBG, L"Injecting %s", argv[ 1 ] );

	DWORD csgo = getFirstCSGO( );

	LOG_DEBUG( DBG, L"Process ID: %lu", csgo );

	if ( !Inject( argv[ 1 ], csgo ) )
	{
		LOG_DEBUG( ERR, L"Error injecting" );
	}
	else
	{
		LOG_DEBUG( SCS, L"Injected" );
	}

	LOG_DEBUG( DBG, L"Done" );

	LocalFree( argv );

	//Wait( 7000 );
	Sleep( 7000 );

	Main( );
	RESTORE_DEBUG( );
	return 0;
}
*/
int CALLBACK WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	dbg = new Debug( );

	dbg->Init( );

	int argc { };
	LPWSTR *argv = CommandLineToArgvW( GetCommandLine( ), &argc );

	if ( !argv )
	{
		dbg->LogDebugMsg( ERR, L"Unable to get argument list" );
		Sleep( 7000 );
		delete dbg;
		return 1;
	}

	if ( argc < 2 )
	{
		dbg->LogDebugMsg( ERR, L"Invalid argument count" );
		Sleep( 7000 );
		delete dbg;
		return 1;
	}

	dbg->LogDebugMsg( DBG, L"Injecting %s", argv[ 1 ] );

	DWORD csgo = getFirstCSGO( );

	dbg->LogDebugMsg( DBG, L"Process ID: %lu", csgo );

	if ( !Inject( argv[ 1 ], csgo ) )
	{
		dbg->LogDebugMsg( ERR, L"Error injecting" );
	}
	else
	{
		dbg->LogDebugMsg( SCS, L"Injected" );
	}

	dbg->LogDebugMsg( DBG, L"Done" );

	LocalFree( argv );

	//Wait( 7000 );
	Sleep( 7000 );

	Main( );

	delete dbg;

	return 0;
}

#else

BOOL WINAPI DllMain( _In_ HINSTANCE hInstDll, _In_ DWORD dwReason, _In_ LPVOID lpvReserved )
{
	switch ( dwReason )
	{
		case DLL_PROCESS_ATTACH:
		{
			DisableThreadLibraryCalls( hInstDll );
			HANDLE hCheat = CreateThread( nullptr, 0, LPTHREAD_START_ROUTINE( Main ), nullptr, 0, nullptr );
			if ( !hCheat || hCheat == INVALID_HANDLE_VALUE )
			{
				return FALSE;
			}
			return TRUE;
		}
		case DLL_PROCESS_DETACH:
		{
			if ( lpvReserved == nullptr )
			{
				// Cleanup
				return TRUE;
			}
		}
		default:
		{
			return FALSE;
		}
	}
}

#endif
