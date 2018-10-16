/// Encryption Manager.cpp

#include "PX Precompiled.hpp"
#define PX_USE_NAMESPACES
#include "../PX Framework.hpp"

namespace PX::Cryptography
{
	bool PX_API InitializeEncryption( )
	{
		const auto strUnhashedKey = std::to_string( GetMoment( ) / 1000000000ull );
		strEncryptionKey = GenerateHash( strUnhashedKey ).substr( 0, 32 );
		strInitializationVector = strEncryptionKey.substr( 0, 16 );
		return !strEncryptionKey.empty( );
	}

	str_t PX_API GenerateHash( const str_t& strPlainText )
	{
		byte_t bOutput[ CryptoPP::SHA1::DIGESTSIZE ];
		CryptoPP::SHA1( ).CalculateDigest( bOutput, reinterpret_cast< byte_t* >( const_cast< char* >( strPlainText.c_str( ) ) ), strPlainText.length( ) );

		CryptoPP::HexEncoder hHash;
		str_t strOutput;
		hHash.Attach( new CryptoPP::StringSink( strOutput ) );
		hHash.Put( bOutput, sizeof( byte_t[ CryptoPP::SHA1::DIGESTSIZE ] ) );
		hHash.MessageEnd( );
		std::transform( strOutput.begin( ), strOutput.end( ), strOutput.begin( ), tolower );
		// shouldn't we be using strOutput's transform fn?
		return strOutput;
	}

	str_t PX_API Encrypt( const str_t& strPlainText )
	{
		return Base64< CryptoPP::Base64Encoder >( AES256CBC< CryptoPP::CBC_Mode< CryptoPP::AES >::Encryption >( strPlainText ) );
	}

	str_t PX_API Decrypt( const str_t& strCipherText )
	{
		return AES256CBC< CryptoPP::CBC_Mode< CryptoPP::AES >::Decryption >( Base64< CryptoPP::Base64Decoder >( strCipherText ) );
	}

	str_t PX_API GenerateIdentifier( const str_t& strIdentifier )
	{
		return GenerateHash( GenerateHash( strInitializationVector ) + GenerateHash( strIdentifier ) ).substr( 0, 16 );
	}
}
