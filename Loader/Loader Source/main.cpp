#include "main.h"

void SetDebug( )
{

#ifdef _DEBUG

	AllocConsole( );
	FILE *fTemp;
	freopen_s( &fTemp, "CONOUT$", "w", stdout );
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
	HWND hWndConsole = GetConsoleWindow( );

	SetConsoleTitleA( "Paladin Loader" );
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

#endif

}

void DrawInterface( )
{
	// call class
	// draw menu
}

void DeleteInterface( )
{
	// call class
	// close all drawings of menu
}

bool Authenticate( )
{
	if ( pro.GetElevationState( GetCurrentProcess( ) ) == EElevation::ADMIN )
	{
		if ( pro.GetPremium( ) <= EPremium::NOT_PREMIUM )
		{
			return false;
		}
		if ( pro.GetPremium( ) <= EPremium::CONNECTION_FAILURE )
		{
			return false;
		}
		if ( pro.GetPremium( ) <= EPremium::HARDWARE_MISMATCH )
		{
			OPEN_MESSAGE( "Paladin Loader", "Your unique identifier has changed - please create a support ticket.", 0 );
			return false;
		}
		if ( pro.GetPremium( ) <= EPremium::EXPIRED )
		{
			OPEN_MESSAGE( "Paladin Loader", "Your premium has expired, please renew your premium on the forum.", 0 );
			return false;
		}
		return pro.GetPremium( ) == EPremium::PREMIUM;
	}
	OPEN_MESSAGE( "Paladin Loader", "Please run the loader as an administrator.", 0 );
	return false;
}

void Verify( )
{
	// create thread, done here
	// check all dlls exist and are correct size
}

void Inject( )
{
	// call class
	// get user input for middleman
	// inject into selected middleman
}

void StartHeartbeat( )
{
	std::thread( [ & ]
	{
		while ( true /* FindWindowA(MIDDLEMAN) IS STILL OPEN */ )
		{
			if ( !Authenticate( ) )
			{
				pro.KillAnticheat( "MIDDLEMAN", "MIDDLEMAN.EXE" );
				std::ofstream fsRegKey( "reg.key", std::ofstream::out | std::ofstream::trunc );
				fsRegKey.close( );
			}
		}
	} );
	// create thread, done here
	// confirm authenticity of run, & used to check for multiple instances
}

int CALLBACK WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR szCmdLine, _In_ int iCmdShow )
{
	SetDebug( );

	DrawInterface( );

	if ( !Authenticate( ) ) return 0;

	Verify( );

	Inject( );

	DeleteInterface( );

	StartHeartbeat( );

#ifdef _DEBUG

	FreeConsole( );

#endif

}
