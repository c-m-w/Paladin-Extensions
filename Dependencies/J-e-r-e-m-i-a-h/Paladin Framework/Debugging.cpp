#include "Framework.hpp"

dbg::CDebugging out;
const char endl = '\n';

#ifdef _DEBUG

dbg::CDebugging::CDebugging( )
{
	ofLogFile.open( "C:/debug.txt", std::ofstream::out | std::ofstream::trunc ); // erase debug
	if ( ofLogFile.is_open( ) )
	{
		ofLogFile << std::put_time( std::localtime( new time_t{ std::time( nullptr ) } ), "[%m/%d/%Y %H:%M:%S]" ) << " [OPN] " << "Initialized Paladin Debug" << std::endl;
	}

	// TODO: allocate console if not there yet
	hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
	std::cout << std::put_time( std::localtime( new time_t { std::time( nullptr ) } ), "[%m/%d/%Y %H:%M:%S]" ) << " [OPN] " << "Initialized Paladin Debug" << std::endl;
}

dbg::CDebugging::CDebugging( CDebugging & )
{
	ofLogFile.open( "C:/debug.txt", std::ofstream::out | std::ofstream::app ); // append debug

	// TODO: allocate console if not there yet
	hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
}

dbg::CDebugging::~CDebugging( )
{
	ofLogFile.close( );
	CloseHandle( hConsole );
} 

template< typename xDatatype > dbg::CDebugging dbg::CDebugging::operator<<( const xDatatype &rhs )
{
	if ( ofLogFile.is_open( ) )
	{
		ofLogFile << rhs;
	}
	if ( hConsole && hConsole != INVALID_HANDLE_VALUE )
	{
		std::cout << rhs;
	}
	return *this;
}

void dbg::ler( )
{
	DWORD dwError = GetLastError( );
	if ( !dwError )
	{
		out LER << "No error" << endl;
		return;
	}

	LPSTR lpstrError { };
	if ( !FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
						 nullptr, dwError, MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ), &lpstrError, 0, nullptr ) )
	{
		out LER << "[0x" << std::hex << dwError << "] - Unable to retrieve error description" << endl;
	}
	else
	{
		out LER << "[0x" << std::hex << dwError << "] - " << lpstrError << endl;
	}
	LocalFree( lpstrError );
}

#else

template< typename xDatatype > dbg::CDebugging dbg::CDebugging::operator<<( const xDatatype & )
{
	return *this;
}

void dbg::ler( ) { }

#endif
