/// Encryption Manager.cpp

#define PX_USE_NAMESPACES
#include "../PX Framework.hpp"

namespace PX::Cryptography
{
	bool PX_API InitializeEncryption( )
	{
		const auto strUnhashedKey = std::to_string( int( GetMoment< std::chrono::seconds >( ) / 100 ) );
		strEncryptionKey = GenerateHash( strUnhashedKey ).substr( 0, 32 );
		strInitializationVector = strEncryptionKey.substr( 0, 16 );
		return !strEncryptionKey.empty( );
	}

	std::string PX_API GenerateHash( const std::string& strPlainText )
	{
		byte_t bOutput[ CryptoPP::SHA1::DIGESTSIZE ];
		CryptoPP::SHA1( ).CalculateDigest( bOutput, reinterpret_cast< byte_t* >( const_cast< char* >( strPlainText.c_str( ) ) ), strPlainText.length( ) );

		CryptoPP::HexEncoder hHash;
		std::string strOutput;
		hHash.Attach( new CryptoPP::StringSink( strOutput ) );
		hHash.Put( bOutput, sizeof( byte_t[ CryptoPP::SHA1::DIGESTSIZE ] ) );
		hHash.MessageEnd( );
		std::transform( strOutput.begin( ), strOutput.end( ), strOutput.begin( ), tolower );
		// shouldn't we be using strOutput's transform fn?
		return strOutput;
	}

	std::string PX_API Encrypt( const std::string& strPlainText )
	{
		return Base64< CryptoPP::Base64Encoder >( AES256CBC< CryptoPP::CBC_Mode< CryptoPP::AES >::Encryption >( strPlainText ) );
	}

	std::string PX_API Decrypt( const std::string& strCipherText )
	{
		return AES256CBC< CryptoPP::CBC_Mode< CryptoPP::AES >::Decryption >( Base64< CryptoPP::Base64Decoder >( strCipherText ) );
	}

	std::string PX_API GenerateIdentifier( const std::string& strIdentifier )
	{
		return GenerateHash( GenerateHash( strInitializationVector ) + GenerateHash( strIdentifier ) ).substr( 0, 16 );
	}
}
