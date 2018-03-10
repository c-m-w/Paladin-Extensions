#pragma once
#include <cryptopp/base64.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/modes.h>
#include <cryptopp/sha3.h>
#include <cryptopp/aes.h>
#include "../Framework.hpp"

namespace Paladin
{
	class Encryption;
	extern Encryption enc;

	class Encryption
	{
		std::string Replace( std::string strPlainText, char chReplacee, char chReplacer )
		{
			for ( auto i = 0u; i < strPlainText.length( ); i++ )
				if ( strPlainText.at( i ) != chReplacee )
					strPlainText.at( i ) = chReplacer;
			return strPlainText;
		}
	public:
		std::string Hash_SHA3_256( std::string szPlainText )
		{
			BYTE bOutput[ CryptoPP::SHA3_256::DIGESTSIZE ];
			CryptoPP::SHA3_256( ).CalculateDigest( bOutput, reinterpret_cast< unsigned char * >( const_cast< char * >( szPlainText.c_str( ) ) ), szPlainText.length( ) );

			CryptoPP::HexEncoder hHash;
			std::string strOutput;
			hHash.Attach( new CryptoPP::StringSink( strOutput ) );
			hHash.Put( bOutput, sizeof( BYTE[ CryptoPP::SHA3_256::DIGESTSIZE ] ) );
			hHash.MessageEnd( );
			return strOutput;
		}
		std::string Encrypt( std::string strPlainText, std::string strKey )
		{
			std::string strInitializationVector = strKey.substr( 0, 16 );
			std::string strOutput;
			CryptoPP::CBC_Mode< CryptoPP::AES >::Encryption encEncryption( reinterpret_cast< unsigned char * >( const_cast< char * >( strKey.c_str( ) ) ), strKey.length( ), reinterpret_cast< unsigned char * >( const_cast< char * >( strInitializationVector.c_str( ) ) ) );
			CryptoPP::StringSource( strPlainText, true, new CryptoPP::StreamTransformationFilter( encEncryption, new CryptoPP::Base64Encoder( new CryptoPP::StringSink( strOutput ), false ) ) );
			return Replace( strOutput.substr( 0, strOutput.length( ) - 2 ), '+', ' ' );
		}
	};

	Encryption enc;


	constexpr long long LinearCongruentialGenerator( const int iRounds )
	{
		return 1013904223ll + 1664525ll * long long( iRounds > 0 ? LinearCongruentialGenerator( iRounds - 1 ) : ( __TIME__[ 7 ] - '0' ) * 1 + ( __TIME__[ 6 ] - '0' ) * 10 + ( __TIME__[ 4 ] - '0' ) * 60 + ( __TIME__[ 3 ] - '0' ) * 600 + ( __TIME__[ 1 ] - '0' ) * 3600 + ( __TIME__[ 0 ] - '0' ) * 36000 & 0xFFFFFFFF );
	}

	template< int... iPack > struct index_list_t
	{ };

	template< typename _IndexList, int _Right > struct append_t;

	template< int... _Left, int _Right > struct append_t< index_list_t< _Left... >, _Right >
	{
		typedef index_list_t< _Left..., _Right > Result;
	};

	template< int i > struct construct_index_list_t
	{
		typedef typename append_t< typename construct_index_list_t< i - 1 >::Result, i - 1 >::Result Result;
	};

	template< > struct construct_index_list_t< 0 >
	{
		using Result = index_list_t< >;
	};

	template< typename _chType, typename _IndexList > class CXorString;

	template< typename _chType, int... iIndex > class CXorString< _chType, index_list_t< iIndex... > >
	{
		_chType _chValue[ sizeof...( iIndex )+1 ];

		static const _chType XOR_KEY = _chType( LinearCongruentialGenerator( 10 ) % ( 0xFFFF + 1 ) );

		constexpr _chType EncryptCharacter( const _chType _chCharacter, const int iIndexBuffer )
		{
			return _chCharacter ^ ( XOR_KEY + iIndexBuffer );
		}

	public:
		__forceinline constexpr explicit CXorString( const _chType * const _chString ): _chValue { EncryptCharacter( _chString[ iIndex ], iIndex )... }
		{ }

		const _chType *Decrypt( )
		{
			for ( unsigned u = 0; u < sizeof...( iIndex ); u++ )
			{
				_chValue[ u ] = _chValue[ u ] ^ ( XOR_KEY + u );
			}

			_chValue[ sizeof...( iIndex ) ] = static_cast< _chType >( 0 );

			return _chValue;
		}
	};

#define XOR( String ) ( Paladin::CXorString< char, Paladin::construct_index_list_t< sizeof( String ) - 1 >::Result >( String ).Decrypt( ) )
#define XORW( String ) ( Paladin::CXorString< wchar_t, Paladin::construct_index_list_t< ( sizeof( String ) - 1 ) / 2 >::Result >( String ).Decrypt( ) )
}
