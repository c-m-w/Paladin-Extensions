/// Encryption.hpp

#pragma once

namespace Paladin
{
    namespace xors
    {
        template< int iValueToEnsure > struct SEnsureCompileTime
        {
            enum: int
            {
                VALUE = iValueToEnsure
            };
        };

        constexpr int LinearCongruentGenerator( int iRounds )
        {
            return 1013904223 + 1664525 * ( iRounds > 0 ? LinearCongruentGenerator( iRounds - 1 ) : ( __TIME__[ 7 ] - '0' ) * 1 + ( __TIME__[ 6 ] - '0' ) * 10 + ( __TIME__[ 4 ] - '0' ) * 60 + ( __TIME__[ 3 ] - '0' ) * 600 + ( __TIME__[ 1 ] - '0' ) * 3600 + ( __TIME__[ 0 ] - '0' ) * 36000 & 0xFFFFFFFF );
        }

        template< int...iPack > struct SIndexList
        { };

        template< typename, int > struct SAppend;

        template< int...iLeft, int iRight > struct SAppend< SIndexList< iLeft... >, iRight >
        {
            typedef SIndexList< iLeft..., iRight > result_t;
        };

        template< int i > struct SConstructIndexList
        {
            typedef typename SAppend< typename SConstructIndexList< i - 1 >::result_t, i - 1 >::result_t result_t;
        };

        template< > struct SConstructIndexList< 0 >
        {
            typedef SIndexList< > result_t;
        };

        template< typename _char, typename _IndexList > class CXorString;

        template< typename _char, int...iIndex > class CXorString< _char, SIndexList< iIndex... > >
        {
            _char _chValue[ sizeof...( iIndex ) + 1 ];

            static const _char _chXorKey = static_cast< _char >( SEnsureCompileTime< LinearCongruentGenerator( 10 ) >::VALUE % 0x10000 );

            constexpr _char EncryptCharacter( const _char, int );

        public:
            constexpr CXorString( const _char * const );

            const _char *Decrypt( );

            const _char *Get( );
        };
    }
}

/**
 * \brief Encrypts string data on compile, then decrypts for access on run.
 * \param String C-style string
 */
#define XOR( String ) ( Paladin::xors::CXorString< char, Paladin::xors::SConstructIndexList< sizeof( String ) - 1 >::result_t >( String ).Decrypt( ) )
/**
 * \brief Encrypts wide string data on compile, then decrypts for access on run.
 * \param String C-style wide string
 */
#define XORW( String ) ( Paladin::xors::CXorString< wchar_t, Paladin::xors::SConstructIndexList< ( sizeof( String ) - 1 ) / 2 >::result_t >( String ).Decrypt( ) )

#include "Encryption.tpp"
