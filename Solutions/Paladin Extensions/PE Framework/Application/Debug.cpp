/// Debug.cpp

#include "../Framework.hpp"

namespace Paladin
{
    namespace dbg
    {
#if defined( _DEBUG )
        SetPrintColor::SetPrintColor( const WORD wDesiredAttributes ): m_wDesiredAttributes( wDesiredAttributes )
        { }

        CDebugPrint::CDebugPrint( )
        {
            strsDebugLog << std::put_time( std::localtime( new time_t{ std::time( nullptr ) } ), "[%m/%d/%Y %H:%M:%S]" ) << " [OPN] " << "Initialized Paladin Debug" << endl;
            std::cout << std::put_time( std::localtime( new time_t{ std::time( nullptr ) } ), "[%m/%d/%Y %H:%M:%S]" );
            SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), FOREGROUND_INTENSITY | ~FOREGROUND_RED | ~FOREGROUND_GREEN | FOREGROUND_BLUE );
            std::cout << " [OPN] ";
            SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), ~FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE );
            std::cout << "Initialized Paladin Debug" << endl;
        }

        CDebugPrint::~CDebugPrint( )
        {
            strsDebugLog << std::put_time( std::localtime( new time_t{ std::time( nullptr ) } ), "[%m/%d/%Y %H:%M:%S]" ) << " [CLS] " << "Terminated Paladin Debug" << endl;
            std::cout << std::put_time( std::localtime( new time_t{ std::time( nullptr ) } ), "[%m/%d/%Y %H:%M:%S]" );
            SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), FOREGROUND_INTENSITY | ~FOREGROUND_RED | ~FOREGROUND_GREEN | FOREGROUND_BLUE );
            std::cout << " [CLS] ";
            SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), ~FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE );
            std::cout << "Terminated Paladin Debug" << endl;

            std::ofstream ofLogFile( "C:/debug.log" );
            ofLogFile << strsDebugLog.str( );
            ofLogFile.close( );
        }

        CDebugPrint::CDebugPrint( const CDebugPrint &rhs )
        {
            strsDebugLog << rhs.strsDebugLog.str( );
        }
#endif

        std::ios_base &__CLRCALL_OR_CDECL bin( std::ios_base &_Iosbase )
        {	// set basefield to binary
            _Iosbase.setf( std::ios_base::binary, std::ios_base::basefield );
            return _Iosbase;
        }
        std::ios_base &__CLRCALL_OR_CDECL oct( std::ios_base &_Iosbase )
        {	// set basefield to binary
            _Iosbase.setf( std::ios_base::oct, std::ios_base::basefield );
            return _Iosbase;
        }
        std::ios_base &__CLRCALL_OR_CDECL dec( std::ios_base &_Iosbase )
        {	// set basefield to binary
            _Iosbase.setf( std::ios_base::dec, std::ios_base::basefield );
            return _Iosbase;
        }
        std::ios_base &__CLRCALL_OR_CDECL hex( std::ios_base &_Iosbase )
        {	// set basefield to hex
            _Iosbase.setf( std::ios_base::hex, std::ios_base::basefield );
            return ( _Iosbase );
        }

        void LastError( )
        {
#if defined( _DEBUG )
            auto dwError = GetLastError( );
            if ( !dwError )
            {
                out M_LER << "[0x0] - No errors" << endl;
                return;
            }

            LPWSTR lpwstrError { };
            if ( !FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                 nullptr, dwError, MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ), lpwstrError, 0, nullptr ) )
                out M_LER << "[0x" << hex << dwError << "] - Unable to retrieve error description" << endl;
            else
                out M_LER << "[0x" << hex << dwError << "] - " << *lpwstrError << endl;
            LocalFree( lpwstrError );
#endif
        }
    }
}
