/// Encryption.hpp

#pragma once

namespace PX
{
    namespace XOR
    {
        template< int iValueToEnsure > PX_ABSTRACT_STRUCT IEnsureCompileTime
        {
            enum: int
            {
                VALUE = iValueToEnsure
            };
        };

        template< > PX_ABSTRACT_STRUCT ICStringTraits< Tools::cstr_t >
        {
            static PX_DEF int_trait_t = 1;
            typedef char char_trait_t;
        };
        template< > PX_ABSTRACT_STRUCT ICStringTraits< Tools::wcstr_t >
        {
            static PX_DEF int_trait_t = 2;
            typedef wchar_t char_trait_t;
        };

        template< typename, int > PX_ABSTRACT_STRUCT IAppend;
        template< int... iLeft, int iRight > struct IAppend< IIndexList< iLeft... >, iRight >
        {
            typedef IIndexList< iLeft..., iRight > result_t;
        };

        template< int i > struct SConstructIndexList
        {
            typedef typename IAppend< typename SConstructIndexList< i - 1 >::result_t, i - 1 >::result_t result_t;
        };
        template< > struct SConstructIndexList< 0 >
        {
            typedef IIndexList< > result_t;
        };

        template< typename, typename > PX_ABSTRACT_CLASS IXorString;
        template< typename _char, int... iIndex > PX_ABSTRACT_CLASS IXorString< _char, IIndexList< iIndex... > >
        {
            _char _chValue[ sizeof... ( iIndex ) + 1 ];

            static const _char _chXorKey = static_cast< _char >( IEnsureCompileTime< LinearCongruentialGenerator( 10 ) >::VALUE % 0x10000 );

            constexpr _char PX_API EncryptCharacter( const _char _chCharacter, int iIndexParam )
            {
                return _chCharacter ^ ( _chXorKey + iIndexParam );
            }

        public:
            explicit constexpr PX_API IXorString( const _char* const _String ): _chValue { EncryptCharacter( _String[ iIndex ], iIndex )... }
            { }

            const _char* PX_API Decrypt( )
            {
                for ( int i = 0; i < sizeof... ( iIndex ); i++ )
                {
                    _chValue[ i ] = _chValue[ i ] ^ ( _chXorKey + i );
                }

                _chValue[ sizeof... ( iIndex ) ] = static_cast< _char >( 0 );

                return _chValue;
            }

            const _char* PX_API Get( ){
                return _chValue;
            }
        };
    }
}
