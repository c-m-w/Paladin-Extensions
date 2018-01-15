#include "dllmain.h"

bool bExitState { };
HINSTANCE hInst { };
std::mutex mtxMutex { };
std::vector< std::thread > tThreads { };

void Feature( bool bFeatureState, moment mntWait, const std::function< void( ) > &fnFeature, unsigned short usFeatureKey )
{
	while ( !bExitState )
	{
		if ( bFeatureState && GetAsyncKeyState( usFeatureKey ) )
		{
			fnFeature( );
		}
		Wait( mntWait );
	}
}

void Feature( bool bFeatureState, moment mntWait, const std::function< void( ) > &fnFeature )
{
	while ( !bExitState )
	{
		if ( bFeatureState )
		{
			fnFeature( );
		}
		Wait( mntWait );
	}
}

void CleanUp( )
{
	DEBUG( DBG, "Cleaning up" );
	mtxMutex.lock( );
	bExitState = true;
	mtxMutex.unlock( );
	for ( auto &tThread: tThreads )
	{
		if ( tThread.joinable( ) )
		{
			tThread.join( );
		}
	}
}

void Panic( )
{
	DEBUG( WRN, "Panic called" );
	cfg.iQuitReason = EQuitReasons::PANIC;
	CleanUp( );
	FreeLibraryAndExitThread( hInst, 0 ); // TODO figure out how to not display ABORT message
}

void CreateThreads( )
{
	DEBUG( DBG, "Initializing threads..." );

	std::thread tInfoGrabber( [ & ]
	{
		while ( !bExitState )
		{
			eng.GetLocalPlayer( );

			for ( int iEntity { }; iEntity <= 64; iEntity++ )
			{
				eng.GetEntity( iEntity );
			}
		}
	} );
	tThreads.push_back( move( tInfoGrabber ) );

	std::thread tTestThread( [ & ]
	{
		Feature( true, 1, [ & ]
		{
			inv.Inventory( );
		} );
	} );
	tThreads.push_back( move( tTestThread ) );

	DEBUG( SCS, "Created threads" );
	LASTERR( );
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
		LASTERR( );
		Panic( );
	}
	if ( uCurrentUserPremiumStatus == EPremium::NOT_PREMIUM )
	{
		CleanUp( );
		return false;
	}
	if ( uCurrentUserPremiumStatus == EPremium::EXPIRED )
	{
		MESSAGE( "Paladin CSGO", "Notice 1: Premium Time Expired -> No access\nDid you renew your premium?", MB_ICONHAND );
		CleanUp( );
		return false;
	}
	if ( uCurrentUserPremiumStatus == EPremium::PREMIUM )
	{
		DEBUG( SCS, "Authenticated!" );
	}

	return true;
}

int _stdcall Main( )
{
	if ( !GetPremium( ) )
	{
		//return 0;
	}

	if ( all.GetElevationState( ) == EElevation::NOT_ADMIN )
	{
		MESSAGE( "Paladin CSGO", "Warning: Elevation Token State -> Not high enough\nDid you run the middleman/injector as admin?", MB_ICONWARNING );
	}

	if ( cfg.bCheckForAnticheat )
	{
		EAnticheatStatus asCSGO = all.KillAnticheat( "Counter-Strike: Global Offensive", *"csgo.exe" );
		if ( asCSGO == EAnticheatStatus::FAILED )
		{
			Panic( );
			return 0;
		}
		if ( asCSGO == EAnticheatStatus::KILLED )
		{
			MESSAGE( "Paladin CSGO", "Warning: Anticheat -> Terminated\nDid you leave CSGO open during injection?", MB_ICONWARNING );
		}

		EAnticheatStatus asSteam = all.KillAnticheat( "Steam", *"steam.exe" );
		if ( asSteam == EAnticheatStatus::FAILED )
		{
			Panic( );
			return 0;
		}
		if ( asSteam == EAnticheatStatus::KILLED )
		{
			MESSAGE( "Paladin CSGO", "Warning: Anticheat -> Terminated\nDid you leave Steam open during injection?", MB_ICONWARNING );
		}
	}

	// TODO call Config here

	// TODO call Menu here

GameLaunch:
	if ( !mem.AttachToGame( ) )
	{
		MESSAGE( "Paladin CSGO", "Fatal Error 2: Game Attach\nAre you running the cheat as admin?", MB_ICONERROR );
		CleanUp( );
		return 0;
	}
	mem.InitializeAddresses( );
	LASTERR( );

ServerConnect:
	DEBUG( DBG, "Waiting for server connection..." );
	while ( eng.GetSignOnState( ) != ESignOnState::FULL )
	{
		if ( GetAsyncKeyState( VK_F4 ) )
		{
			return 0;
		}
		if ( !FindWindow( nullptr, "Counter-Strike: Global Offensive" ) )
		{
			DEBUG( WRN, "Game closed!" );
			goto GameLaunch;
		}
		Wait( 100 );
	}

	CreateThreads( );

	while ( !bExitState )
	{
		if ( GetAsyncKeyState( VK_F4 ) )
		{
			Panic( );
		}
		else if ( !FindWindow( nullptr, "Counter-Strike: Global Offensive" ) )
		{
			CleanUp( );
			DEBUG( WRN, "Game closed!" );
			goto GameLaunch;
		}
		else if ( eng.GetSignOnState( ) != ESignOnState::FULL )
		{
			CleanUp( );
			DEBUG( DBG, "Disconnected from server!" );
			goto ServerConnect;
		}
		else
		{
			Wait( 100 );
		}
	}
	return 0;
}

#ifdef _DEBUG

void SetDebug( )
{
	FILE *fTemp;
	freopen_s( &fTemp, "CONOUT$", "w", stdout );

	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
	HWND hWndConsole = GetConsoleWindow( );

	CONSOLE_FONT_INFOEX cfiEx;
	cfiEx.cbSize = sizeof( CONSOLE_FONT_INFOEX );
	cfiEx.dwFontSize.X = 6;
	cfiEx.dwFontSize.Y = 8;
	wcscpy_s( cfiEx.FaceName, L"Terminal" );
	SetCurrentConsoleFontEx( hConsole, 0, &cfiEx );

	SetConsoleTitle( "Paladin CSGO" );
	//MoveWindow( hWndConsole, 300, 300, 339, 279, false );
	MoveWindow( hWndConsole, 300, 300, 500, 279, false );
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
	LASTERR( );
}

int CALLBACK WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow )
{
	AllocConsole( );
	SetDebug( );
	Main( );
	FreeConsole( );
}

#else

BOOL WINAPI DllMain( _In_ HINSTANCE hinstDLL, _In_ DWORD fdwReason, _In_ LPVOID lpvReserved )
{
	switch ( fdwReason )
	{
		case DLL_PROCESS_ATTACH:
		{
			hInst = hinstDLL;
			HANDLE hCheat = CreateThread( nullptr, 0, LPTHREAD_START_ROUTINE( Main ), nullptr, 0, nullptr ); // TODO args
			if ( !hCheat || hCheat == INVALID_HANDLE_VALUE )
			{
				cfg.iQuitReason = EQuitReasons::LOAD_LIBRARY_ERROR;
			}
			else
			{
				cfg.iQuitReason = EQuitReasons::SUCCESS;
			}
			DisableThreadLibraryCalls( hinstDLL );
			break;
		}
		case DLL_PROCESS_DETACH:
		{
			CleanUp( );
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

#endif
