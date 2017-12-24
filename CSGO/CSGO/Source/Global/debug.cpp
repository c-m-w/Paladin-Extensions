#include "../dllmain.h"

std::string strLog;

void LogDebugMsg( EDebugMessage dmType, char *szMessage, ... )
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
		//Ideally we want to dynamically allocate this, might do later (for now, stick to a max of 2047 data characters)
		char chBuffer[2048] = { '\0' };
		va_list vaList;
		va_start( vaList, szMessage );
		vsnprintf( chBuffer, sizeof chBuffer, szMessage, vaList );
		va_end( vaList );
		std::cout << chBuffer;
		strLog.append( chBuffer );
	}
}

// Look up errors here: https://msdn.microsoft.com/en-us/library/windows/desktop/ms681381(v=vs.85).aspx
void LogLastError( )
{
	DWORD dwError = GetLastError( );
	if ( !dwError )
	{
		LogDebugMsg( LER, "No error" );
		return;
	}
	LPSTR lpstrError = nullptr;
	if ( !FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, dwError, MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ), LPSTR( &lpstrError ), 0, nullptr ) )
	{
		LogDebugMsg( LER, "[0x%08lu] - Unable to retrieve error description", dwError );
	}
	else
	{
		LogDebugMsg( LER, "[0x%08lu] - %s", dwError, lpstrError );
	}
	strLog.append( lpstrError );
	LocalFree( lpstrError );
}
