#include "Framework.hpp"

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

#else

template< typename xDatatype > dbg::CDebugging dbg::CDebugging::operator<<( const xDatatype & )
{
	return *this;
}

#endif

dbg::CDebugging out;
