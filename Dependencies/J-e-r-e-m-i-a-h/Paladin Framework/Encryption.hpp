#pragma once
#include "Framework.hpp"

namespace Paladin {
	class Encryption;
	extern Encryption enc;

	class Encryption
	{
		std::string Replace( std::string strPlainText, char chSubstitute, char chReplacement ) 
		{
			for ( int i = 0; i < strPlainText.length( ); i++ ) if ( !strcmp( strPlainText.at( i ).c_str( ), chSubstitute ) ) strPlainText.at( i ) = chReplacement;
			return strPlainText;
		}
	public:
		std::string Hash_SHA3_256( const char *szPlainText ) 
		{
			byte bOutput[ CryptoPP::SHA3_256::DIGESTSIZE ];
			CryptoPP::SHA3_256( ).CalculateDigest( bOutput, reinterpret_cast< unsigned char * >( szPlainText ), strlen( szPlainText );

			CryptoPP::HexEncoder hHash;
			std::string strOutput;
			hHash.Attach( new CryptoPP::StringSink( strOutput ) );
			hHash.Put( bOutput, sizeof( byte[ CryptoPP::SHA3_256::DIGESTSIZE ] ) );
			hHash.MessageEnd( );
			return strOutput;
		}
		std::string Encrypt( std::string strPlainText, std::string strKey ) 
		{
			std::string strInitializationVector = strKey.substr(0, 16);
			std::string strOutput;
			CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption encEncryption( reinterpret_cast< unsigned char * >( strKey.c_str( ) ), strKey.length( ), reinterpret_cast< unsigned char * >( strInitializationVector.c_str( ) ) );
			CryptoPP::StringSource( strPlainText, true, new CryptoPP::StreamTransformationFilter( encEncryption, new CryptoPP::Base64Encoder( new CryptoPP::StringSink( strOutput ), false ) ) );
			return Replace( strOutput.substr( 0, strOutput.length( ) - 2 ), '+', ' ' );
		}
	};

	Encryption enc;
}
