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
}
