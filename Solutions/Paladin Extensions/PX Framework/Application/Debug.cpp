/// Debug.cpp

#include "../PX Framework.hpp"

namespace PX
{
    namespace dbg
    {
        out_clr_t::out_clr_t( const WORD wDesiredAttributes ): m_wDesiredAttributes( wDesiredAttributes )
        { }

        template< > out_t& out_t::operator<<< out_clr_t >( const out_clr_t& rhs )
        {
#if defined( _DEBUG )
            SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), rhs.m_wDesiredAttributes );
#endif
            return *this;
        }

        void PX_API PrintLastError( )
        {
#if defined( _DEBUG )
            auto dwError = GetLastError( );
            if ( !dwError )
            {
                out PX_LER << "[0x0] - No errors" << '\n';
                return;
            }

            LPWSTR lpwstrError { };
            if ( !FormatMessageW( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                  nullptr, dwError, MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ), lpwstrError, 0, nullptr ) )
                out PX_LER << "[0x" << std::hex << dwError << "] - Unable to retrieve error description" << endl;
            else
                out PX_LER << "[0x" << std::hex << dwError << "] - " << *lpwstrError << endl;
            LocalFree( lpwstrError );
#endif
        }

        std::ios_base& __CLRCALL_OR_CDECL bin( std::ios_base& _Iosbase )
        {   // set basefield to binary
            _Iosbase.setf( std::ios_base::binary, std::ios_base::basefield );
            return _Iosbase;
        }
        std::ios_base& __CLRCALL_OR_CDECL oct( std::ios_base& _Iosbase )
        {   // set basefield to binary
            _Iosbase.setf( std::ios_base::oct, std::ios_base::basefield );
            return _Iosbase;
        }
        std::ios_base& __CLRCALL_OR_CDECL dec( std::ios_base& _Iosbase )
        {   // set basefield to binary
            _Iosbase.setf( std::ios_base::dec, std::ios_base::basefield );
            return _Iosbase;
        }
        std::ios_base& __CLRCALL_OR_CDECL hex( std::ios_base& _Iosbase )
        {   // set basefield to hex
            _Iosbase.setf( std::ios_base::hex, std::ios_base::basefield );
            return _Iosbase;
        }
    }
}
