/// Debug.inl

#pragma once

namespace PX
{
    namespace dbg
    {
        template< typename _t > bool PX_API Assert( _t _ToAssert )
        {
            static int i;
            if ( _ToAssert == _t( ) )
#if defined _DEBUG
                throw std::exception( "Failed to assert", i );
#else
                return false;
#endif
            i++;
            return true;
        }
        namespace
        {
#if defined _DEBUG 
            std::wofstream wofLogFile;
#endif
        }

        template< typename _t > out_t& PX_API out_t::operator<<( const _t& rhs )
        {
#if defined _DEBUG 
            if ( !wofLogFile.is_open( ) )
            {
                wofLogFile.open( "C:/debug.log", std::ofstream::trunc );
                if ( !wofLogFile.is_open( ) )
                    throw std::exception( "Failed to open debug.log" );

                wofLogFile << std::put_time( std::localtime( new time_t { std::time( nullptr ) } ),
                                             L"[%m/%d/%Y %H:%M:%S]" ) << L" [OPN] " << L"Initialized Paladin Debug" << endl;

                *this << out_clr_t( FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | !FOREGROUND_INTENSITY );
                std::wcout << std::put_time( std::localtime( new time_t { std::time( nullptr ) } ), L"[%m/%d/%Y %H:%M:%S]" );
                *this << out_clr_t( FOREGROUND_BLUE | !FOREGROUND_GREEN | !FOREGROUND_RED | FOREGROUND_INTENSITY );
                std::wcout << L" [OPN] ";
                *this << out_clr_t( FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | !FOREGROUND_INTENSITY );
                std::wcout << L"Initialized Paladin Debug" << endl;
            }

            wofLogFile << rhs;
            std::wcout << rhs;
#endif
            return *this;
        }
    }
}
