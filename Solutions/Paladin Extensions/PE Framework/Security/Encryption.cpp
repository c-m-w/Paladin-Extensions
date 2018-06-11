/// Encryption.cpp

#include "../Framework.hpp"

//namespace Paladin
//{
//	namespace xor
//	{
//		template < int iValueToEnsure > struct SEnsureCompileTime
//		{
//			enum: int
//			{
//				VALUE = iValueToEnsure
//			};
//		};
//
//		constexpr int LinearCongruentGenerator( int iRounds )
//		{
//			return 1013904223 + 1664525 * ( iRounds > 0 ? LinearCongruentGenerator( iRounds - 1 ) : ( __TIME__[ 7 ] - '0' ) * 1 + ( __TIME__[ 6 ] - '0' ) * 10 + ( __TIME__[ 4 ] - '0' ) * 60 + ( __TIME__[ 3 ] - '0' ) * 600 + ( __TIME__[ 1 ] - '0' ) * 3600 + ( __TIME__[ 0 ] - '0' ) * 36000 & 0xFFFFFFFF );
//		}
//
//		template < int... iPack > struct SIndexList
//		{ };
//
//		template < typename _IndexList, int iRight > struct SAppend;
//		template < int... iLeft, int iRight > struct SAppend< SIndexList< iLeft... >, iRight >
//		{
//			typedef SIndexList< iLeft..., iRight > result_t;
//		};
//
//		template < int i > struct SConstructIndexList
//		{
//			typedef typename SAppend< typename SConstructIndexList< i - 1 >::result_t, i - 1 >::result_t result_t;
//		};
//
//		template < > struct SConstructIndexList< 0 >
//		{
//			typedef SIndexList< > result_t;
//		};
//
//		template < typename _char, typename _IndexList > class CXorString;
//
//		template< typename _char, int... iIndex > const _char *CXorString< _char, SIndexList< iIndex... > >::Decrypt( )
//		{
//			for ( int i = 0; i < sizeof...( iIndex ); i++ )
//			{
//				_chValue[ i ] = _chValue[ i ] ^ ( _chXorKey + i );
//			}
//
//			_chValue[ sizeof...( iIndex ) ] = static_cast< _char >( 0 );
//
//			return _chValue;
//		}
//
//		template< typename _char, int... iIndex > const _char *CXorString< _char, SIndexList< iIndex... > >::Get( )
//		{
//			return _chValue;
//		}
//
//		template< typename _char, int... iIndex > constexpr _char CXorString< _char, SIndexList< iIndex... > >::EncryptCharacter( const _char _chCharacter )
//		{
//			return _chCharacter ^ ( _chXorKey + iIndex );
//		}
//
//		template< typename _char, int... iIndex > constexpr CXorString< _char, SIndexList< iIndex... > >::CXorString( const _char * const String ): _chValue { EncryptCharacter( String[ iIndex ] ) }
//		{ }
//	}
//}
