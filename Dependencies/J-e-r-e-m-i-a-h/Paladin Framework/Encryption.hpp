#pragma once
#include "Framework.hpp"

namespace Paladin {
	class Encryption;
	extern Encryption enc;

	class Encryption
	{
		std::string Replace( std::string strPlainText, char chReplacee, char chReplacer ) 
		{
			for ( int i = 0; i < strPlainText.length( ); i++ )
				if ( !strcmp( strPlainText.at( i ).c_str( ), chReplacee ) )
					strPlainText.at( i ) = chReplacer;
			return strPlainText;
		}
	public:
		std::string Hash_SHA3_256( const char *szPlainText ) 
		{
			BYTE bOutput[ CryptoPP::SHA3_256::DIGESTSIZE ];
			CryptoPP::SHA3_256( ).CalculateDigest( bOutput, reinterpret_cast< unsigned char * >( szPlainText ), strlen( szPlainText ) );

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
			CryptoPP::CBC_Mode< CryptoPP::AES >::Encryption encEncryption( reinterpret_cast< unsigned char * >( strKey.c_str( ) ), strKey.length( ), reinterpret_cast< unsigned char * >( strInitializationVector.c_str( ) ) );
			CryptoPP::StringSource( strPlainText, true, new CryptoPP::StreamTransformationFilter( encEncryption, new CryptoPP::Base64Encoder( new CryptoPP::StringSink( strOutput ), false ) ) );
			return Replace( strOutput.substr( 0, strOutput.length( ) - 2 ), '+', ' ' );
		}
	};

	Encryption enc;
}
