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

void Authenticate( )
{
	// call class
	// get hwid, check with server information
}

void Verify( )
{
	// create thread, done here
	// check all dlls exist and are correct size
}

void Inject( )
{
	// call class
	// inject into selected middleman
}

void StartHeartbeat( )
{
	// create thread, done here
	// confirm authenticity of run, & used to check for multiple instances
}

int CALLBACK WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR szCmdLine, _In_ int iCmdShow )
{
	SetDebug( );

	DrawInterface( );

	Authenticate( );

	Verify( );

	Inject( );

	StartHeartbeat( );

#ifdef _DEBUG

	FreeConsole( );

#endif

}
