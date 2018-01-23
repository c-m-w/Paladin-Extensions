#include "main.h"

int _stdcall Main( )
{
	return 0;
}

#ifdef _DEBUG
#define SET_DEBUG SetDebug
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
}
#else
#define SET_DEBUG void
#endif

BOOL WINAPI DllMain( _In_ HINSTANCE hInstDll, _In_ DWORD dwReason, _In_ LPVOID lpvReserved )
{
	switch ( dwReason )
	{
		case DLL_PROCESS_ATTACH:
		{
			DisableThreadLibraryCalls( hInstDll );
			SET_DEBUG( );
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
