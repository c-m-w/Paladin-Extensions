/// Debug.cpp

#include "../Framework.hpp"

namespace Paladin
{
	namespace dbg
	{
		template< typename _Datatype > void Assert( _Datatype _Var )
		{
#if defined( _DEBUG )
			static int i;
			if ( !_Var )
				throw std::exception( "Failed to assert", i++ );
#endif
		}

#if defined( _DEBUG )
		CDebugPrint::CDebugPrint( )
		{
			strsDebugLog << std::put_time( std::localtime( new time_t { std::time( nullptr ) } ), "[%m/%d/%Y %H:%M:%S]" ) << " [OPN] " << "Initialized Paladin Debug" << endl;
			std::cout << strsDebugLog.str( );
		}

		CDebugPrint::~CDebugPrint( )
		{
			strsDebugLog << std::put_time( std::localtime( new time_t { std::time( nullptr ) } ), "[%m/%d/%Y %H:%M:%S]" ) << " [CLS] " << "Terminated Paladin Debug" << endl;
			std::cout << std::put_time( std::localtime( new time_t { std::time( nullptr ) } ), "[%m/%d/%Y %H:%M:%S]" ) << " [CLS] " << "Terminated Paladin Debug" << endl;

			std::ofstream ofLogFile( "C:/debug.log" );
			ofLogFile << strsDebugLog.str( );
			ofLogFile.close( );
		}

		CDebugPrint::CDebugPrint( const CDebugPrint & rhs )
		{
			strsDebugLog << rhs.strsDebugLog.str( );
		}
#endif

		template< typename _Datatype > CDebugPrint CDebugPrint::operator<<( const _Datatype &rhs )
		{
#if defined( _DEBUG )
			std::cout << rhs;
			strsDebugLog << rhs;
#endif
			return *this;
		}

		CDebugPrint out;

		std::ios_base &__CLRCALL_OR_CDECL binary( std::ios_base &_Iosbase )
		{	// set basefield to binary
			_Iosbase.setf( std::ios_base::binary, std::ios_base::basefield );
			return _Iosbase;
		}

		std::ios_base &( *bin )( std::ios_base &_Iosbase ) = binary;
		std::ios_base &( *oct )( std::ios_base &_Iosbase ) = std::oct;
		std::ios_base &( *dec )( std::ios_base &_Iosbase ) = std::dec;
		std::ios_base &( *hex )( std::ios_base &_Iosbase ) = std::hex;

		void LastError( )
		{
#if defined( _DEBUG )
			DWORD dwError = GetLastError( );
			if ( !dwError )
			{
				out LER << "[0x0] - No errors" << endl;
				return;
			}

			LPWSTR lpwstrError { };
			if ( !FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
								 nullptr, dwError, MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ), lpwstrError, 0, nullptr ) )
				out LER << "[0x" << hex << dwError << "] - Unable to retrieve error description" << endl;
			else
				out LER << "[0x" << hex << dwError << "] - " << *lpwstrError << endl;
			LocalFree( lpwstrError );
#endif
		}

		void Pause( )
		{
#if defined( _DEBUG )
			std::cin.get( );
#endif
		}
	}
}
