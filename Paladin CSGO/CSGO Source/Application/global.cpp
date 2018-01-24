#include "../main.h"

#ifdef _DEBUG

void SetDebug( )
{
	hStandardIn[ 0 ] = GetStdHandle( STD_INPUT_HANDLE );
	hStandardOut[ 0 ] = GetStdHandle( STD_OUTPUT_HANDLE );
	hStandardError[ 0 ] = GetStdHandle( STD_ERROR_HANDLE );

	AllocConsole( );
	AttachConsole( GetCurrentProcessId( ) );

	hStandardIn[ 1 ] = GetStdHandle( STD_INPUT_HANDLE );
	hStandardOut[ 1 ] = GetStdHandle( STD_OUTPUT_HANDLE );
	hStandardError[ 1 ] = GetStdHandle( STD_ERROR_HANDLE );

	SetConsoleMode( hStandardIn[ 1 ], ENABLE_PROCESSED_INPUT | ENABLE_INSERT_MODE | ENABLE_QUICK_EDIT_MODE | ENABLE_EXTENDED_FLAGS );
	SetConsoleMode( hStandardOut[ 1 ], ENABLE_PROCESSED_OUTPUT | ENABLE_WRAP_AT_EOL_OUTPUT );



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

void RestoreDebug( )
{
FreeConsole( );

SetStdHandle( STD_INPUT_HANDLE, hStandardIn[ 0 ] );
SetStdHandle( STD_OUTPUT_HANDLE, hStandardOut[ 0 ] );
SetStdHandle( STD_ERROR_HANDLE, hStandardError[ 0 ] );
}

void LogDebugMessage( EDebugMessage dmType, char *szMessage, ... )
{
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
	if ( hConsole && hConsole != INVALID_HANDLE_VALUE )
	{
		std::cout << std::endl;
		switch ( dmType )
		{
			case SCS:
				SetConsoleTextAttribute( hConsole, 10 );
				std::cout << "[SCS] ";
				break;
			case WRN:
				SetConsoleTextAttribute( hConsole, 14 );
				std::cout << "[WRN] ";
				break;
			case ERR:
				SetConsoleTextAttribute( hConsole, 12 );
				std::cout << "[ERR] ";
				break;
			case LER:
				SetConsoleTextAttribute( hConsole, 12 );
				std::cout << "[LER] ";
				break;
			default:
				SetConsoleTextAttribute( hConsole, 15 );
				std::cout << "[DBG] ";
		}
		SetConsoleTextAttribute( hConsole, 7 );
		// Ideally we want to dynamically allocate this, might do later (for now, stick to a max of 2047 data characters)
		char chBuffer[ 2048 ] { '\0' };
		va_list vaList;
		va_start( vaList, szMessage );
		vsnprintf( chBuffer, sizeof chBuffer, szMessage, vaList );
		va_end( vaList );
		std::cout << chBuffer;
	}
}

void LogLastError( )
{
	DWORD dwError = GetLastError( );
	if ( !dwError )
	{
		LOG_DEBUG( LER, "None" );
		return;
	}
	LPSTR lpstrError = nullptr;
	if ( !FormatMessageA( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, dwError, MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ), LPSTR( &lpstrError ), 0, nullptr ) )
	{
		LOG_DEBUG( LER, "[0x%08lu] - Unable to retrieve error description", dwError );
	}
	else
	{
		LOG_DEBUG( LER, "[0x%08lu] - %s", dwError, lpstrError );
	}
	LocalFree( lpstrError );
}

#endif

moment GetMoment( )
{
	return std::chrono::duration_cast< std::chrono::milliseconds >( std::chrono::system_clock::now( ).time_since_epoch( ) ).count( );
}
