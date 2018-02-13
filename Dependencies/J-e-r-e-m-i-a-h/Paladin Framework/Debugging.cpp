#include "Framework.hpp"

CDebugging dbg;

CDebugging::CDebugging( )
{
	// TODO: set up file stream to C:/debug.txt
	ofLogFile.open( "debug.txt", std::ofstream::out | std::ofstream::app ); // append debug
	// ofLogFile.open( "debug.txt", std::ofstream::out | std::ofstream::trunc ); // erase debug
	if ( ofLogFile.is_open( ) )
	{
		ofLogFile << std::put_time( std::localtime( new time_t { std::time( nullptr ) } ), "[%m/%d/%Y %H:%M:%S]" ) << " [OPN] " << "Initialized Paladin Debug";
	}

	// TODO: allocate console if not there yet
	hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
};

void CDebugging::LogDebugMsg( const char *szDebugMessageType, std::string, ... )
{
	if ( ofLogFile.is_open( ) )
	{
		ofLogFile << std::endl << std::put_time( std::localtime( new time_t { std::time( nullptr ) } ), "[%H:%M:%S]" ) << szDebugMessageType;

		char chBuffer[ 2048 ] { '\0' };
		va_list vaList;
		const wchar_t *wsz = wstrMessage.c_str( );
		va_start( vaList, wsz );
		vsnprintf( chBuffer, sizeof chBuffer, wsz, vaList );
		va_end( vaList );
		std::cout << chBuffer;
		strLog.append( chBuffer );
	}

	if ( hConsole && hConsole != INVALID_HANDLE_VALUE )
	{
		SetConsoleTextAttribute( hConsole, 15 );
		std::cout << std::endl << std::put_time( std::localtime( new time_t { std::time( nullptr ) } ), "[%H:%M:%S]" );

		switch ( szDebugMessageType )
		{
			case SCS:
				SetConsoleTextAttribute( hConsole, 10 );
				std::cout << " [SCS] ";
				break;
			case WRN:
				SetConsoleTextAttribute( hConsole, 14 );
				std::cout << " [WRN] ";
				break;
			case ERR:
				SetConsoleTextAttribute( hConsole, 12 );
				std::cout << " [ERR] ";
				break;
			case LER:
				SetConsoleTextAttribute( hConsole, 12 );
				std::cout << " [LER] ";
				break;
			default:
				std::cout << " [DBG] ";
		}
		SetConsoleTextAttribute( hConsole, 7 );
		//Ideally we want to dynamically allocate this, might do later (for now, stick to a max of 2047 data characters)
		char chBuffer[2048] { '\0' };
		va_list vaList;
		va_start( vaList, szMessage );
		vsnprintf( chBuffer, sizeof chBuffer, szMessage, vaList );
		va_end( vaList );
		std::cout << chBuffer;
		strLog.append( chBuffer );
	}
}

void CDebugging::LogLastError( )
{
	
}
