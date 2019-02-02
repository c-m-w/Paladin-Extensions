/// Cryptography.cpp

#include "Precompile.hpp"

#define USE_NAMESPACES
#include "../../Framework.hpp"

bool CCryptography::Initialize( )
{
	const auto strUnhashedKey = std::to_string( GetMoment( ) / 1000000000ull );

	strEncryptionKey = GenerateHash( strUnhashedKey ).substr( 0, ENCRYPTION_KEY_SIZE );
	strInitializationVector = strEncryptionKey.substr( 0, INITIALIZATION_VECTOR_SIZE );
	return !strEncryptionKey.empty( );
}

void CCryptography::Shutdown( )
{ }

std::string CCryptography::GenerateHash( const std::string &strBytes )
{
	unsigned char bOutput[ CryptoPP::SHA1::DIGESTSIZE ];
	CryptoPP::SHA1( ).CalculateDigest( bOutput, reinterpret_cast< unsigned char* >( const_cast< char* >( strBytes.c_str( ) ) ), strBytes.length( ) );
	CryptoPP::HexEncoder hHash;
	std::string strOutput;

	hHash.Attach( new CryptoPP::StringSink( strOutput ) );
	hHash.Put( bOutput, sizeof( unsigned char[ CryptoPP::SHA1::DIGESTSIZE ] ) );
	hHash.MessageEnd( );
	std::transform( strOutput.begin( ), strOutput.end( ), strOutput.begin( ), tolower );
	return strOutput;
}
