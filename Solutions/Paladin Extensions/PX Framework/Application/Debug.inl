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
            {
#if defined( _DEBUG )
                throw std::exception( "Failed to assert", i );
#endif
                return false;
            }
            i++;
            return true;
        }

        template< typename _t > out_t& PX_API out_t::operator<<( const _t& rhs )
        {
#if defined( _DEBUG )
            if ( !ofLogFile.is_open( ) )
            {
                ofLogFile.open( "C:/debug.log" );
                ofLogFile << std::put_time( std::localtime( new time_t { std::time( nullptr ) } ), "[%m/%d/%Y %H:%M:%S]" )
                          << " [OPN] " << "Initialized Paladin Debug" << endl;
                *this << out_clr_t( FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | !FOREGROUND_INTENSITY );
                std::cout << std::put_time( std::localtime( new time_t { std::time( nullptr ) } ), "[%m/%d/%Y %H:%M:%S]" );
                *this << out_clr_t( FOREGROUND_BLUE | !FOREGROUND_GREEN | !FOREGROUND_RED | FOREGROUND_INTENSITY );
                std::cout << " [OPN] ";
                *this << out_clr_t( FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | !FOREGROUND_INTENSITY );
                std::cout << "Initialized Paladin Debug" << endl;
            }

            ofLogFile << rhs;
            std::cout << rhs;
#endif
            return *this;
        }
    }
}
