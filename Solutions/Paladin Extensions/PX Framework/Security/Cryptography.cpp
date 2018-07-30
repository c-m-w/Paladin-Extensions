/// Encryption Manager.cpp

#include "../PX Framework.hpp"

namespace PX
{
    namespace Cryptography
    {
        std::string GenerateHash( const std::string& strPlainText )
        {
            BYTE bOutput[ CryptoPP::SHA3_256::DIGESTSIZE ];
            CryptoPP::SHA3_256( ).CalculateDigest( bOutput, reinterpret_cast< byte* >( const_cast< char* >( strPlainText.c_str( ) ) ), strPlainText.length( ) );

            CryptoPP::HexEncoder hHash;
            std::string strOutput;
            hHash.Attach( new CryptoPP::StringSink( strOutput ) );
            hHash.Put( bOutput, sizeof( BYTE[ CryptoPP::SHA3_256::DIGESTSIZE ] ) );
            hHash.MessageEnd( );
            return strOutput;
        }

        std::string Encrypt( const std::string& strPlainText, const std::string& strKey )
        {
            auto strInitializationVector = strKey.substr( 0, 16 );
            std::string strOutput;
            CryptoPP::CBC_Mode< CryptoPP::AES >::Encryption encEncryption( reinterpret_cast< byte* >( const_cast< char* >( Tools::string_cast< std::string >( strKey ).c_str( ) ) ),
                                                                           strKey.length( ), reinterpret_cast< byte* >( const_cast< char* >( strInitializationVector.c_str( ) ) ) );
            CryptoPP::StringSource( Tools::string_cast< std::string >( strPlainText ), true, new
                                    CryptoPP::StreamTransformationFilter( encEncryption, new CryptoPP::Base64Encoder( new CryptoPP::StringSink( strOutput ), false ) ) );
            strOutput.replace( strOutput.begin( ), strOutput.end( ), '+', '-' );
            return strOutput;
        }
    }
}
