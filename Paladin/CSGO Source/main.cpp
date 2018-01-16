#include "main.h"

bool bExitState { };
HINSTANCE hInst { };
std::vector< std::thread > tThreads { };

void Feature( bool bFeatureState, moment mntWait, std::function<void()> &fnFeature, int iFeatureKey )
{
	if ( !iFeatureKey )
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
	else
	{
		while ( !bExitState )
		{
			if ( bFeatureState && GetAsyncKeyState( iFeatureKey ) )
			{
				fnFeature( );
			}
			Wait( mntWait );
		}
	}
}

void CleanUp( )
{
	LOG_DEBUG( DBG, "Cleaning up" );
	bExitState = true;
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
	LOG_DEBUG( WRN, "Panic called" );
	CleanUp( );
	FreeLibraryAndExitThread( hInst, 0 ); // TODO figure out how to not display ABORT message
}

bool GetPremium( )
{
	// TODO stop byte patching
	EPremium uCurrentUserPremiumStatus = pro.CheckPremiumStatus( );
	if ( uCurrentUserPremiumStatus == EPremium::BANNED )
	{
		//TODO BANNED: DELETE FILE
		char chTemp[ MAX_PATH ];
		GetModuleFileName( hInst, chTemp, MAX_PATH );
		remove( std::string( chTemp ).c_str( ) );
		LOG_LAST_ERROR( );
		Panic( );
	}
	if ( uCurrentUserPremiumStatus == EPremium::NOT_PREMIUM )
	{
		CleanUp( );
		return false;
	}
	if ( uCurrentUserPremiumStatus == EPremium::EXPIRED )
	{
		OPEN_MESSAGE( "Paladin CSGO", "Notice 1: Premium Time Expired -> No access\nDid you renew your premium?", MB_ICONHAND );
		CleanUp( );
		return false;
	}
	if ( uCurrentUserPremiumStatus == EPremium::PREMIUM )
	{
		LOG_DEBUG( SCS, "Authenticated!" );
	}

	return true;
}

void CreateThreads( )
{
	LOG_DEBUG( DBG, "Initializing threads..." );

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

	std::function<void( )> fnTestFunction = std::bind( &CInventory::Inventory, inv );
	std::thread tTestThread(Feature, true, 1, fnTestFunction, 0 );
	tThreads.push_back( move( tTestThread ) );

	LOG_DEBUG( SCS, "Created threads" );
	LOG_LAST_ERROR( );
}

int _stdcall Main( )
{
	if ( !GetPremium( ) )
	{
		return 0;
	}

	if ( pro.GetElevationState( GetCurrentProcess( ) ) == EElevation::NOT_ADMIN )
	{
		OPEN_MESSAGE( "Paladin CSGO", "Warning: Elevation Token State -> Not high enough\nDid you run the middleman/injector as admin?", MB_ICONWARNING );
	}

#ifndef _DEBUG
	if ( pro.bCheckForAnticheat )
	{
		EAnticheatStatus asCSGO = pro.KillAnticheat( "Counter-Strike: Global Offensive", *"csgo.exe" );
		if ( asCSGO == EAnticheatStatus::FAILED )
		{
			Panic( );
			return 0;
		}
		if ( asCSGO == EAnticheatStatus::KILLED )
		{
			MESSAGE( "Paladin CSGO", "Warning: Anticheat -> Terminated\nDid you leave CSGO open during injection?", MB_ICONWARNING );
		}

		EAnticheatStatus asSteam = pro.KillAnticheat( "Steam", *"steam.exe" );
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
#endif

	// TODO call Config here

	// TODO call Menu here

GameLaunch:
	if ( !mem.AttachToGame( ) )
	{
		OPEN_MESSAGE( "Paladin CSGO", "Fatal Error 2: Game Attach\nAre you running the cheat as admin?", MB_ICONERROR );
		CleanUp( );
		return 0;
	}
	mem.InitializeAddresses( );
	LOG_LAST_ERROR( );

ServerConnect:
	LOG_DEBUG( DBG, "Checking for server connection, current Sign On State: %i", eng.GetSignOnState( ) );
	while ( eng.GetSignOnState( ) != ESignOnState::FULL )
	{
		if ( GetAsyncKeyState( VK_F4 ) )
		{
			return 0;
		}
		if ( !FindWindowA( nullptr, "Counter-Strike: Global Offensive" ) )
		{
			LOG_DEBUG( WRN, "Game closed!" );
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
		else if ( !FindWindowA( nullptr, "Counter-Strike: Global Offensive" ) )
		{
			CleanUp( );
			LOG_DEBUG( WRN, "Game closed!" );
			goto GameLaunch;
		}
		else if ( eng.GetSignOnState( ) != ESignOnState::FULL )
		{
			CleanUp( );
			LOG_DEBUG( DBG, "Disconnected from server!" );
			goto ServerConnect;
		}
		else
		{
			Wait( 100 );
		}
	}

	CleanUp( );
	return 0;
}

#ifdef _DEBUG

void SetDebug( )
{
	AllocConsole( );
	FILE *fTemp;
	freopen_s( &fTemp, "CONOUT$", "w", stdout );
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
	HWND hWndConsole = GetConsoleWindow( );
	
	SetConsoleTitleA( "Paladin CSGO" );
	EnableMenuItem( GetSystemMenu( hWndConsole, false ), SC_CLOSE, MF_GRAYED );
	SetWindowLongA( hWndConsole, GWL_STYLE, GetWindowLongA( hWndConsole, GWL_STYLE ) & ~SC_CLOSE & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX );
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 25;
	cci.bVisible = false;
	SetConsoleCursorInfo( hConsole, &cci );

	SetConsoleTextAttribute( hConsole, 11 );
	std::cout << "[OPN] ";
	SetConsoleTextAttribute( hConsole, 7 );
	std::cout << "Paladin Debug Interface Setup";
	LOG_LAST_ERROR( );
}

int CALLBACK WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow )
{
	SetDebug( );
	Main( );
	FreeConsole( );
}

#else

BOOL WINAPI DllMain( _In_ HINSTANCE hInstDll, _In_ DWORD dwReason, _In_ LPVOID lpvReserved )
{
	switch ( dwReason )
	{
		case DLL_PROCESS_ATTACH:
		{
			HANDLE hCheat = CreateThread( nullptr, 0, LPTHREAD_START_ROUTINE( Main ), nullptr, 0, nullptr ); // TODO args
			if ( !hCheat || hCheat == INVALID_HANDLE_VALUE )
			{
				return FALSE;
			}
			else
			{
				hInst = hInstDll;
				DisableThreadLibraryCalls( hInstDll );
				return TRUE;
			}
		}
		default:
		{
			CleanUp( );
			return FALSE;
		}
	}
}

#endif
