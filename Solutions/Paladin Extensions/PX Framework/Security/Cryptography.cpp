/// Encryption Manager.cpp

#include "../PX Framework.hpp"

namespace PX
{
	namespace Cryptography
	{
		bool PX_API Initialize( )
		{
			const auto strUnhashedKey = std::to_string( Tools::GetMoment< std::chrono::seconds >( ) );
			strEncryptionKey = GenerateHash( strUnhashedKey ).substr( 0, 32 );
			strInitializationVector = strEncryptionKey.substr( 0, 16 );
			return !strEncryptionKey.empty( );
		}

		std::string PX_API GenerateHash( const std::string& strPlainText )
		{
			Types::byte_t bOutput[ CryptoPP::SHA3_256::DIGESTSIZE ];
			CryptoPP::SHA3_256( ).CalculateDigest( bOutput, reinterpret_cast< Types::byte_t* >( const_cast< char* >( strPlainText.c_str( ) ) ), strPlainText.length( ) );

			CryptoPP::HexEncoder hHash;
			std::string strOutput;
			hHash.Attach( new CryptoPP::StringSink( strOutput ) );
			hHash.Put( bOutput, sizeof( Types::byte_t[ CryptoPP::SHA3_256::DIGESTSIZE ] ) );
			hHash.MessageEnd( );
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
	}
}