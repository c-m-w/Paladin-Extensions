#pragma once
#pragma warning( disable : 4996 )
#include <Windows.h>
#include "../Framework.hpp"

#if defined( _DEBUG )
enum
{
	ASSERTION_FAILED
};
#define ASSERT( Expression ) if ( !Expression ) throw ASSERTION_FAILED;
#else
#define ASSERT( Expression ) Expression
#endif

namespace Paladin
{
	namespace dbg
	{
		class CDebugging;
		extern CDebugging out;

		constexpr auto endl = '\n';
		constexpr auto tab = '\t';
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
				ASSERT( typeid( _Datatype ) != typeid( wchar_t ) & typeid( _Datatype ) != typeid( std::wstring ) );
				sstrLog << rhs;
				std::cout << rhs;
				return *this;
			}
		};

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
			{
				out LER << "[0x" << hex << dwError << "] - Unable to retrieve error description" << endl;
			}
			else
			{
				out LER << "[0x" << hex << dwError << "] - " << lpwstrError << endl;
			}
			LocalFree( lpwstrError );
		}

#define DBG << std::put_time( std::localtime( new time_t { std::time( nullptr ) } ), "[%H:%M:%S]" ) << " [DBG] "
#define SCS << std::put_time( std::localtime( new time_t { std::time( nullptr ) } ), "[%H:%M:%S]" ) << " [SCS] "
#define WRN << std::put_time( std::localtime( new time_t { std::time( nullptr ) } ), "[%H:%M:%S]" ) << " [WRN] "
#define ERR << std::put_time( std::localtime( new time_t { std::time( nullptr ) } ), "[%H:%M:%S]" ) << " [ERR] "
#define LER << std::put_time( std::localtime( new time_t { std::time( nullptr ) } ), "[%H:%M:%S]" ) << " [LER] "

#else

		class CDebugging
		{
		public:
			template < typename _Datatype > CDebugging operator<<( const _Datatype & )
			{
				return *this;
			};
		};

#endif

		void lst_err( )
		{ }

		CDebugging out;
	}
}
