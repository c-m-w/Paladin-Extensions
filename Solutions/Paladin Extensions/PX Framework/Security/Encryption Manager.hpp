/// Encryption.hpp

#pragma once

namespace PX
{
    template< int iValueToEnsure > PX_ABSTRACT_STRUCT IEnsureCompileTime
    {
        enum: int
    {
        VALUE = iValueToEnsure
    };
    };

    constexpr int PX_API LinearCongruentGenerator( int iRounds )
    {
        return 1013904223 + 1664525 * ( iRounds > 0 ? LinearCongruentGenerator( iRounds - 1 )
                                        : ( __TIME__[ 7 ] - '0' ) * 1 + ( __TIME__[ 6 ] - '0' ) * 10 + ( __TIME__[ 4 ] - '0' ) * 60 +
                                        ( __TIME__[ 3 ] - '0' ) * 600 + ( __TIME__[ 1 ] - '0' ) * 3600 + ( __TIME__[ 0 ] - '0' ) * 36000
                                        & 0xFFFFFFFF );
    }
}

#include "Encryption Manager.inl"
