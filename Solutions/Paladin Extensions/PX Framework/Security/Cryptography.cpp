/// Encryption Manager.cpp

#include "../PX Framework.hpp"

namespace PX::Cryptography
{
	bool PX_API Initialize( )
	{
		const auto strUnhashedKey = std::to_string( int( Tools::GetMoment< std::chrono::seconds >( ) / 100 ) );
		strEncryptionKey = GenerateHash( strUnhashedKey ).substr( 0, 32 );
		strInitializationVector = strEncryptionKey.substr( 0, 16 );
		return !strEncryptionKey.empty( );
	}

	std::string PX_API GenerateHash( const std::string& strPlainText )
	{
		Types::byte_t bOutput[ CryptoPP::SHA1::DIGESTSIZE ];
		CryptoPP::SHA1( ).CalculateDigest( bOutput, reinterpret_cast< Types::byte_t* >( const_cast< char* >( strPlainText.c_str( ) ) ), strPlainText.length( ) );

		CryptoPP::HexEncoder hHash;
		std::string strOutput;
		hHash.Attach( new CryptoPP::StringSink( strOutput ) );
		hHash.Put( bOutput, sizeof( Types::byte_t[ CryptoPP::SHA1::DIGESTSIZE ] ) );
		hHash.MessageEnd( );
		std::transform( strOutput.begin( ), strOutput.end( ), strOutput.begin( ), tolower );
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

	std::string PX_API CreateIdentifier( const std::string& strIdentifier )
	{
		return Encrypt( strIdentifier ).substr( 0, 10 );
	}
}
