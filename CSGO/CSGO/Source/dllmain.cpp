#include "dllmain.h"
void Feature( bool, unsigned int, std::function< void( ) > );
void Feature( bool, unsigned int, std::function< void( ) >, int );
void CleanUp( );
void Panic( );
void CreateThreads( );
bool GetPremium( );
void SetDebug( );
int CALLBACK WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow );
BOOL WINAPI DllMain( HINSTANCE hInstDll, DWORD fdwReason, LPVOID lpvReserved );

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
		MessageBox( nullptr, "Warning 1: Elevation Token State -> No access\nDid you run the middleman as admin?", "Paladin CSGO", MB_ICONWARNING | MB_OK );
	}

	if ( cfg.bCheckForAnticheat )
	{
		EAnticheatStatus kacCSGO = all.KillAnticheat( "Counter-Strike: Global Offensive", *"csgo.exe" );
		if ( kacCSGO != EAnticheatStatus::FAILED )
		{
			if ( kacCSGO == EAnticheatStatus::KILLED )
			{
				MessageBox( nullptr, "Warning 2: Anticheat -> Terminated\nDid you leave CSGO open during injection?", "Paladin CSGO", MB_ICONWARNING | MB_OK );
			}
			if ( all.KillAnticheat( "Steam", *"steam.exe" ) == EAnticheatStatus::KILLED )
			{
				MessageBox( nullptr, "Warning 2: Anticheat -> Terminated\nDid you leave Steam open during injection?", "Paladin CSGO", MB_ICONWARNING | MB_OK );
			}
		}
		else
		{
			MessageBox( nullptr, "Fatal Error 1: Elevation Token State -> No anticheat termination access\nDid you run the middleman as admin?", "Paladin CSGO", MB_ICONERROR | MB_OK );
			CleanUp( );
			return 0;
		}
	}

	if ( !cfg.LoadConfig( ) )
	{
		MessageBox( nullptr, "Warning 3: Config File -> Using Defaults\nIs there a config file?", "Paladin CSGO", MB_ICONWARNING | MB_OK );
	}
	if ( !cfg.ReadConfig( ) )
	{
		MessageBox( nullptr, "Warning 4: Config File -> Using Defaults\nIs the config file formatted for this version?", "Paladin CSGO", MB_ICONWARNING | MB_OK );
	}

	// TODO call Menu here

	if ( !mem.AttachToGame( ) )
	{
		MessageBox( nullptr, "Fatal Error 2: Game Attach\nAre you running the cheat as admin?", "Paladin CSGO", MB_ICONERROR | MB_OK );
		CleanUp( );
		return 0;
	}
	mem.InitializeAddresses( );
	LogLastError( );

	LogDebugMsg( DBG, "Waiting for server connection... " );
	// TODO
	/*while ( eng.GetSignOnState( ) != ESignOnState::FULL )
	{
		printf( "%i", int( eng.GetSignOnState( ) ) );
		Wait( 1000 );
	}*/

	CreateThreads( );

	while ( true/*eng.GetSignOnState( ) == ESignOnState::FULL*/ )
	{
		Wait( 1000 );
	}
	//CleanUp( );
	//WinMain( hInstance, hPrevInstance, pCmdLine, nCmdShow );
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

	SetConsoleTitle( "Paladin CSGO" );
	MoveWindow( hWndConsole, 300, 300, 339, 279, false );
	EnableMenuItem( GetSystemMenu( hWndConsole, false ), SC_CLOSE, MF_GRAYED );
	SetWindowLong( hWndConsole, GWL_STYLE, GetWindowLong( hWndConsole, GWL_STYLE ) & ~SC_CLOSE & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX );

	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 25;
	cci.bVisible = false;
	SetConsoleCursorInfo( hConsole, &cci );
	SetConsoleTextAttribute( hConsole, 15 );

	printf( "[OPN] " );
	strLog.append( "[OPN] " );
	SetConsoleTextAttribute( hConsole, 7 );
	printf( "Paladin Debug Interface Setup\n" );
	strLog.append( "Paladin Debug Interface Setup\n" );
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
		MessageBox( nullptr, "Notice 1: Premium Time Expired -> No access\nDid you renew your premium?", "Paladin CSGO", MB_ICONHAND | MB_OK );
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
	//
	// general
	//
	std::thread tPanic( [ & ]
	{
		Feature( true, 1, [ & ]
		{
			Panic( );
		}, VK_F4 );
	} );
	tThreads.push_back( move( tPanic ) );
	//
	// awareness
	//
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
	std::thread tRadar( [&]
	{
		Feature( true, 1, [&]
		{
			rad.Radar( );
		} );
	} );
	tThreads.push_back( move( tRadar ) );
	//
	// combat
	//
	std::thread tRecoilControl( [ & ]
	{
		Feature( true, 1, [ & ]
		{
			rcs.RecoilControl( );
		} );
	} );
	tThreads.push_back( move( tRecoilControl ) );
	//
	// miscellaneous
	//
	std::thread tAirStuck( [ & ]
	{
		Feature( true, 1, [ & ]
		{
			air.AirStuck( );
		}, 'L' );
	} );
	tThreads.push_back( move( tAirStuck ) );
	std::thread tAutoJump( [ & ]
	{
		Feature( true, 1, [ & ]
		{
			aut.AutoJump( );
		}, VK_SPACE );
	} );
	tThreads.push_back( move( tAutoJump ) );
	// TODO
	/*std::thread tAutoNade( [&]
	{
	Feature( true, 1, [&]
	{
	aut.AutoNade( );
	} );
	} );
	tThreads.push_back( move( tAutoNade ) );*/
	std::thread tAutoShoot( [ & ]
	{
		Feature( true, 1, [ & ]
		{
			aut.AutoShoot( );
		}, VK_LBUTTON );
	} );
	tThreads.push_back( move( tAutoShoot ) );
	std::thread tFOV( [&]
	{
		Feature( true, 1, [&]
		{
			fov.FOV( );
		} );
	} );
	tThreads.push_back( move( tFOV ) );
	// TODO
	/*std::thread tWeaponFOV( [&]
	{
	Feature( true, 1, [&]
	{
	fov.WeaponFOV( );
	} );
	} );
	tThreads.push_back( move( tWeaponFOV ) );*/
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

void Feature( bool bFeatureState, unsigned int nWait, std::function< void( ) > fnFeature, int iFeatureKey )
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

void Feature( bool bFeatureState, unsigned int nWait, std::function< void( ) > fnFeature )
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
