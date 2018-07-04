/// Encryption.hpp

#pragma once

namespace PX
{
    namespace Cryptography
    {
        std::string GenerateHash( const std::string& );
        std::string Encrypt( const std::string&, const std::string& );
    }

    namespace XOR
    {
        constexpr int PX_API LinearCongruentGenerator( int iRounds )
        {
            return 1013904223 + 1664525 * ( iRounds > 0 ? LinearCongruentGenerator( iRounds - 1 )
                                            : ( __TIME__[ 7 ] - '0' ) * 1 + ( __TIME__[ 6 ] - '0' ) * 10 + ( __TIME__[ 4 ] - '0' ) * 60 +
                                            ( __TIME__[ 3 ] - '0' ) * 600 + ( __TIME__[ 1 ] - '0' ) * 3600 + ( __TIME__[ 0 ] - '0' ) * 36000
                                            & 0xFFFFFFFF );
        }

        template< int > PX_ABSTRACT_STRUCT IEnsureCompileTime;
        template< typename > PX_ABSTRACT_STRUCT ICStringTraits;
        template< int ... > PX_ABSTRACT_STRUCT IIndexList;
        template< typename, int > PX_ABSTRACT_STRUCT IAppend;
        template< int > struct SConstructIndexList;
        template< typename, typename > PX_ABSTRACT_CLASS IXorString;
    }
}

#include "Cryptography.inl"
