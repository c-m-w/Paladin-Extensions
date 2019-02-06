/// Cryptography.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#include "../../Framework.hpp"

#define CRYPTION_INIT													\
	if ( !Initialize( ) )												\
	return false;														\
																		\
	if ( strKey.empty( ) )												\
	strKey = strEncryptionKey;											\
																		\
	if ( strInitVector.empty( ) )										\
	strInitVector = strInitializationVector;							\
																		\
	if ( strKey.length( ) != ENCRYPTION_KEY_SIZE						\
		 || strInitVector.length( ) != INITIALIZATION_VECTOR_SIZE )		\
		throw std::runtime_error( XOR( "Invalid key sizes." ) );

bool CCryptography::Initialize( )
{
	if ( GetMoment( ) - mmtLastGenerationTime < GENERATION_INTERVAL
		&& !strEncryptionKey.empty( ) && !strInitializationVector.empty( ) )
		return true;

	const auto strUnhashedKey = std::to_string( GetMoment( ) / GENERATION_INTERVAL );

	strEncryptionKey = GenerateHash( strUnhashedKey ).substr( 0, ENCRYPTION_KEY_SIZE );
	strInitializationVector = strEncryptionKey.substr( 0, INITIALIZATION_VECTOR_SIZE );
	return !strEncryptionKey.empty( );
}

void CCryptography::Uninitialize( )
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

bool CCryptography::Encrypt( const std::string &strPlainText, std::string &strCipher, std::string strKey /*= std::string( )*/, std::string strInitVector /*= std::string( )*/ )
{
	CRYPTION_INIT

	std::string strUnEncoded { };
	return Crypt< encrypt_t >( strPlainText, strUnEncoded, strKey, strInitVector ) && Base64< encode_t >( strUnEncoded, strCipher );
}

bool CCryptography::Decrypt( const std::string &strCipher, std::string &strPlainText, std::string strKey /*= std::string( )*/, std::string strInitVector /*= std::string( )*/ )
{
	CRYPTION_INIT

	std::string strDecoded { };
	return Base64< decode_t >( strCipher, strDecoded ) && Crypt< decrypt_t >( strDecoded, strPlainText, strKey, strInitVector );
}
