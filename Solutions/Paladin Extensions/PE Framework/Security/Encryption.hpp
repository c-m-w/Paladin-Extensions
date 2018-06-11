/// Encryption.hpp

#pragma once

//namespace Paladin
//{
//	namespace xor
//	{
//		template < int > struct SEnsureCompileTime;
//
//		constexpr int LinearCongruentGenerator( int );
//
//		template < int... > struct SIndexList;
//
//		template < typename, int > struct SAppend;
//		template < int... iLeft, int iRight > struct SAppend< SIndexList< iLeft... >, iRight >;
//
//		template < int > struct SConstructIndexList;
//
//		template < > struct SConstructIndexList< 0 >;
//
//		template < typename _char, typename _IndexList > class CXorString;
//		template < typename _char, int... iIndex > class CXorString< _char, SIndexList< iIndex... > >
//		{
//			_char _chValue[ sizeof...( iIndex ) + 1 ];
//
//			static const _char _chXorKey = static_cast< _char >( ( 0 + ( SEnsureCompileTime< LinearCongruentGenerator( 10 ) >::VALUE % ( 0xFFFF - 0 + 1 ) ) ) );
//
//			constexpr _char EncryptCharacter( const _char );
//
//		public:
//			constexpr CXorString( const _char* const );
//
//			const _char *Decrypt( );
//
//			const _char *Get( );
//		};
//	}
//}
//
//#define XOR( String ) ( xor::CXorString< char, xor::SConstructIndexList< sizeof( String ) - 1 >::result_t >( String ).Decrypt( ) )
//#define XORW( String ) ( xor::CXorString< wchar_t, xor::SConstructIndexList< ( sizeof( String ) - 1 ) / 2 >::result_t >( String ).Decrypt( ) )

#define XOR( x ) ( x )
#define XORW( x ) ( x )
