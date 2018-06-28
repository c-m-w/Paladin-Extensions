#pragma once

namespace Paladin
{
    namespace dbg
    {
        template< typename _Datatype > void Assert( _Datatype _Var )
        {
#if defined( _DEBUG )
            static int i;
            if ( _Var == _Datatype { } )
                throw std::exception( "Failed to assert", i++ );
#endif
        }

        template< typename _Datatype > CDebugPrint CDebugPrint::operator<<( const _Datatype &rhs )
        {
#if defined( _DEBUG )
            std::cout << rhs;
            strsDebugLog << rhs;
#endif
            return *this;
        }

        template< > CDebugPrint CDebugPrint::operator<<< SetPrintColor >( const SetPrintColor &rhs )
        {
#if defined( _DEBUG )
            SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), rhs.m_wDesiredAttributes );
#endif
            return *this;
        }

        template< > CDebugPrint CDebugPrint::operator<<< std::wstring >( const std::wstring &rhs )
        {
#if defined( _DEBUG )
            std::cout << string_cast< std::string >( rhs );
            strsDebugLog << string_cast< std::string >( rhs );
#endif
            return *this;
        }

        template< > CDebugPrint CDebugPrint::operator<<< const wchar_t * >( const wchar_t *const &rhs )
        {
#if defined( _DEBUG )
            std::cout << string_cast< std::string >( rhs );
            strsDebugLog << string_cast< std::string >( rhs );
#endif
            return *this;
        }
    }
}
