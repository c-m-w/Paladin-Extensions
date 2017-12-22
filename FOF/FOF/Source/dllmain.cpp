#include "dllmain.h"

BOOL WINAPI DllMain( HINSTANCE hInstDll, DWORD fdwReason, LPVOID lpvReserved )
{
	switch ( fdwReason )
	{
		case DLL_PROCESS_ATTACH:
		{
			hInst = hInstDll;
			HANDLE hCheat = CreateThread( nullptr, 0, LPTHREAD_START_ROUTINE( WinMain ), nullptr, 0, nullptr );
			if ( !hCheat || hCheat == INVALID_HANDLE_VALUE )
			{
				cfg.iQuitReason = EQuitReasons::LOAD_LIBRARY_ERROR;
			}
			else
			{
				cfg.iQuitReason = EQuitReasons::SUCCESS;
			}
			DisableThreadLibraryCalls( hInstDll );
			break;
		}
		case DLL_PROCESS_DETACH:
		{
			CleanUp( );
#ifdef _DEBUG
			FreeConsole( );
#endif
			break;
		}
		default:
		{
			cfg.iQuitReason = EQuitReasons::BLACKLISTED_CALL;
			break;
		}
	}
	return BOOL( cfg.iQuitReason );
}

int CALLBACK WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
#ifdef _DEBUG
	AllocConsole( );
	SetDebug( );
#endif

	if ( !GetPremium( ) )
	{
		return 0;
	}

	if ( all.GetElevationState( ) == EElevation::NOT_ADMIN )
	{
		MESSAGE( "Paladin FOF", "Warning: Elevation Token State -> Not high enough\nDid you run the middleman/injector as admin?", MB_ICONWARNING );
	}

	if ( cfg.bCheckForAnticheat )
	{
		EAnticheatStatus asFOF = all.KillAnticheat( "Fistful of Frags", *"hl2.exe" );
		if ( asFOF == EAnticheatStatus::FAILED )
		{
			Panic( );
			return 0;
		}
		if ( asFOF == EAnticheatStatus::KILLED )
		{
			MESSAGE( "Paladin FOF", "Warning: Anticheat -> Terminated\nDid you leave FOF open during injection?", MB_ICONWARNING );
		}

		EAnticheatStatus asSteam = all.KillAnticheat( "Steam", *"steam.exe" );
		if ( asSteam == EAnticheatStatus::FAILED )
		{
			Panic( );
			return 0;
		}
		if ( asSteam == EAnticheatStatus::KILLED )
		{
			MESSAGE( "Paladin FOF", "Warning: Anticheat -> Terminated\nDid you leave Steam open during injection?", MB_ICONWARNING );
		}
	}

	// TODO call Config here

	// TODO call Menu here

	if ( !mem.AttachToGame( ) )
	{
		MESSAGE( "Paladin FOF", "Fatal Error 2: Game Attach\nAre you running the cheat as admin?", MB_ICONERROR );
		CleanUp( );
		return 0;
	}
	mem.InitializeAddresses( );
	LogLastError( );

	LogDebugMsg( DBG, "Waiting for server connection..." );
	// TODO
	/*while ( eng.GetSignOnState( ) != ESignOnState::FULL )
	{
		std::cout << " " << int( eng.GetSignOnState( ) );
		Wait( 1000 );
	}*/

	CreateThreads( );

	Feature( true, 1000, [ & ]
	{
		Panic( );
	}, VK_F4 );
}

void SetDebug( )
{
	FILE *fTemp;
	freopen_s( &fTemp, "CONOUT$", "w", stdout );

	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
	HWND hWndConsole = GetConsoleWindow( );

	CONSOLE_FONT_INFOEX cfiEx;
	cfiEx.cbSize = sizeof( CONSOLE_FONT_INFOEX);
	cfiEx.dwFontSize.X = 6;
	cfiEx.dwFontSize.Y = 8;
	wcscpy_s( cfiEx.FaceName, L"Terminal" );
	SetCurrentConsoleFontEx( hConsole, 0, &cfiEx );

	SetConsoleTitle( "Paladin FOF" );
	MoveWindow( hWndConsole, 300, 300, 339, 279, false );
	EnableMenuItem( GetSystemMenu( hWndConsole, false ), SC_CLOSE, MF_GRAYED );
	SetWindowLong( hWndConsole, GWL_STYLE, GetWindowLong( hWndConsole, GWL_STYLE ) & ~SC_CLOSE & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX );

	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 25;
	cci.bVisible = false;
	SetConsoleCursorInfo( hConsole, &cci );

	SetConsoleTextAttribute( hConsole, 11 );
	std::cout << "[OPN] ";
	strLog.append( "[OPN] " );
	SetConsoleTextAttribute( hConsole, 7 );
	std::cout << "Paladin Debug Interface Setup";
	strLog.append( "Paladin Debug Interface Setup" );
	LogLastError( );
}

bool GetPremium( )
{
	// TODO stop byte patching
	EPremium uCurrentUserPremiumStatus = all.CheckPremiumStatus( );
	if ( uCurrentUserPremiumStatus == EPremium::BANNED )
	{
		//TODO BANNED: DELETE FILE
		char chTemp[ MAX_PATH ];
		GetModuleFileName( hInst, chTemp, MAX_PATH );
		remove( std::string( chTemp ).c_str( ) );
		LogLastError( );
		Panic( );
		return false;
	}
	if ( uCurrentUserPremiumStatus == EPremium::NOT_PREMIUM )
	{
		CleanUp( );
		return false;
	}
	if ( uCurrentUserPremiumStatus == EPremium::EXPIRED )
	{
		MESSAGE( "Paladin FOF", "Notice 1: Premium Time Expired -> No access\nDid you renew your premium?", MB_ICONHAND );
		CleanUp( );
		return false;
	}
	if ( uCurrentUserPremiumStatus == EPremium::PREMIUM )
	{
		LogDebugMsg( SCS, "Authenticated!" );
	}

	return true;
}

void CreateThreads( )
{
	LogDebugMsg( DBG, "Initializing threads..." );
	std::thread tHitSound( [ & ]
	{
		Feature( true, 1, [ & ]
		{
			hit.PlaySoundOnHit( );
		} );
	} );
	tThreads.push_back( move( tHitSound ) );
	std::thread tNoFlash( [ & ]
	{
		Feature( true, 1, [ & ]
		{
			nof.NoFlash( );
		} );
	} );
	tThreads.push_back( move( tNoFlash ) );
	
	std::thread tAutoJump( [ & ]
	{
		Feature( true, 1, [ & ]
		{
			aut.AutoJump( );
		}, VK_SPACE );
	} );
	tThreads.push_back( move( tAutoJump ) );
	std::thread tAutoShoot( [ & ]
	{
		Feature( true, 1, [ & ]
		{
			aut.AutoShoot( );
		}, VK_LBUTTON );
	} );
	tThreads.push_back( move( tAutoShoot ) );
	LogDebugMsg( SCS, "Created threads" );
	LogLastError( );
}

void Panic( )
{
	LogDebugMsg( WRN, "Panic called" );
	cfg.iQuitReason = EQuitReasons::PANIC;
	CleanUp( );
	FreeLibraryAndExitThread( hInst, 0 ); // TODO figure out how to not display ABORT message
}

void CleanUp( )
{
	LogDebugMsg( DBG, "Cleaning up" );
	bExitState = true;
	for ( auto &tThread: tThreads )
	{
		if ( tThread.joinable( ) )
		{
			tThread.join( );
		}
	}
}

void Feature( bool bFeatureState, unsigned nWait, std::function< void( ) > fnFeature, int iFeatureKey )
{
	while ( !bExitState )
	{
		if ( bFeatureState && GetAsyncKeyState( iFeatureKey ) )
		{
			fnFeature( );
		}
		Wait( nWait );
	}
}

void Feature( bool bFeatureState, unsigned nWait, std::function< void( ) > fnFeature )
{
	while ( !bExitState )
	{
		if ( bFeatureState )
		{
			fnFeature( );
		}
		Wait( nWait );
	}
}