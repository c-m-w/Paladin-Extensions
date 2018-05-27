#pragma once
#pragma warning( disable : 4996 )
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "../Framework.hpp"

namespace Paladin
{
	namespace dbg
	{
		class CDebugging;
		extern CDebugging out;

#if defined( _DEBUG )
		class AssertionError: public std::exception
		{ };
#define ASSERT( Expression ) if ( !Expression ) throw Paladin::dbg::AssertionError( )
#else
#define ASSERT( Expression ) Expression
#endif

		constexpr auto tab = '\t';
		constexpr auto endl = '\n';
		constexpr auto quote = '\"';
		constexpr auto hex = std::hex;
		constexpr auto dec = std::dec;

#if defined( _DEBUG )

		class CDebugging
		{
			std::stringstream sstrLog;
		public:
			CDebugging( )
			{
				sstrLog << std::put_time( std::localtime( new time_t { std::time( nullptr ) } ), "[%m/%d/%Y %H:%M:%S]" ) << " [OPN] " << "Initialized Paladin Debug" << endl;
				std::cout << std::put_time( std::localtime( new time_t { std::time( nullptr ) } ), "[%m/%d/%Y %H:%M:%S]" ) << " [OPN] " << "Initialized Paladin Debug" << endl;
			}
			CDebugging( CDebugging & rhs )
			{
				sstrLog << rhs.sstrLog.str( );
			}
			CDebugging( CDebugging && ) = delete;
			CDebugging &operator=( CDebugging & ) = delete;
			CDebugging &operator=( CDebugging && ) = delete;
			~CDebugging( )
			{
				std::ofstream ofLogFile( "C:/debug.log" );
				ofLogFile << sstrLog.str( );
				ofLogFile.close( );
			}
			template < typename _Datatype > CDebugging operator<<( const _Datatype & rhs )
			{
				std::cout << rhs;
				sstrLog << rhs;
				return *this;
			}
		};

#define DBG << std::put_time( std::localtime( new time_t { std::time( nullptr ) } ), "[%H:%M:%S]" ) << " [DBG] "
#define SCS << std::put_time( std::localtime( new time_t { std::time( nullptr ) } ), "[%H:%M:%S]" ) << " [SCS] "
#define WRN << std::put_time( std::localtime( new time_t { std::time( nullptr ) } ), "[%H:%M:%S]" ) << " [WRN] "
#define ERR << std::put_time( std::localtime( new time_t { std::time( nullptr ) } ), "[%H:%M:%S]" ) << " [ERR] "
#define LER << std::put_time( std::localtime( new time_t { std::time( nullptr ) } ), "[%H:%M:%S]" ) << " [LER] "

		void lst_err( )
		{
			DWORD dwError = GetLastError( );
			if ( !dwError )
			{
				out LER << "No errors" << endl;
				return;
			}

			LPWSTR lpwstrError { };
			if ( !FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, dwError, MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ), lpwstrError, 0, nullptr ) )
				out LER << "[0x" << hex << dwError << "] - Unable to retrieve error description" << endl;
			else
				out LER << "[0x" << hex << dwError << "] - " << lpwstrError << endl;
			LocalFree( lpwstrError );
		}

		void pause( )
		{
			std::cin.get( );
		}

#else

		class CDebugging
		{
		public:
			template < typename _Datatype > CDebugging operator<<( const _Datatype & )
			{
				return *this;
			};
		};

		void lst_err( )
		{ }
		void pause( )
		{ }

#endif

		CDebugging out;
	}
}
