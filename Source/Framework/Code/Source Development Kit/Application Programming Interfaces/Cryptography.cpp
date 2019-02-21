/// Cryptography.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#define USE_DEFINITIONS
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
		throw std::runtime_error( ENC( "Invalid key sizes." ) );

bool CCryptography::Initialize( )
{
	static auto b = false;
	if ( GetMoment( ) - mmtLastGenerationTime < GENERATION_INTERVAL
		&& !strEncryptionKey.empty( ) && !strInitializationVector.empty( ) )
		return true;

	auto strUnhashedKey = std::to_string( GetMoment( ) / GENERATION_INTERVAL );
	if ( !strProtocol.empty( ) )
		strUnhashedKey += strProtocol;

	strEncryptionKey = GenerateHash( strUnhashedKey ).substr( 0, ENCRYPTION_KEY_SIZE );
	strInitializationVector = strEncryptionKey.substr( 0, INITIALIZATION_VECTOR_SIZE );
	if ( !strProtocol.empty( ) 
		 || !GetInitializationState( )
		 || b )
		return !strEncryptionKey.empty( );

	b = true;
	std::string strEncryptedProtocol { };
	if ( !NET.Request( EAction::GET_PROTOCOL, strEncryptedProtocol ) )
		return false;

	const auto bReturn = Decrypt( strEncryptedProtocol, strProtocol );
	mmtLastGenerationTime = 0;
	return bReturn && Initialize( );
}

void CCryptography::Uninitialize( )
{ }

CCryptography::CCryptography( ): mmtLastGenerationTime( 0ui64 )
{
	strStaticEncryptionKey = ENC( "ExgrEV9yIlF3xgocqy53ipLAwFHuDznk" );
	strStaticInitializationVector = ENC( "4ZNqNqIaJqZqPJS1" );
}

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

bool CCryptography::Encode( const std::string &strSubject, std::string &strOut )
{
	if ( strSubject.empty( ) )
		return false;

	auto _Encoder = CryptoPP::Base64Encoder( nullptr, false );
	_Encoder.Put( reinterpret_cast< unsigned char* >( const_cast< char* >( strSubject.c_str( ) ) ), strSubject.size( ) );
	_Encoder.MessageEnd( );

	strOut.clear( );
	const auto uSize = unsigned( _Encoder.MaxRetrievable( ) );
	strOut.resize( uSize );
	_Encoder.Get( reinterpret_cast< unsigned char* >( &strOut[ 0 ] ), uSize );
	return !strOut.empty( );
}

bool CCryptography::Decode( const std::string &strEncoded, std::string &strOut )
{
	if ( strEncoded.empty( ) )
		return false;

	auto _Decoder = CryptoPP::Base64Decoder( );
	_Decoder.Put( reinterpret_cast< unsigned char* >( const_cast< char* >( strEncoded.c_str( ) ) ), strEncoded.size( ) );
	_Decoder.MessageEnd( );

	strOut.clear( );
	const auto uSize = unsigned( _Decoder.MaxRetrievable( ) );
	strOut.resize( uSize );
	_Decoder.Get( reinterpret_cast< unsigned char* >( &strOut[ 0 ] ), uSize );
	return !strOut.empty( );
}

bool CCryptography::Encrypt( const std::string &strPlainText, std::string &strCipher, std::string strKey /*= std::string( )*/, std::string strInitVector /*= std::string( )*/ )
{
	CRYPTION_INIT

	std::string strUnEncoded { };
	return Crypt< encrypt_t >( strPlainText, strUnEncoded, strKey, strInitVector ) && Encode( strUnEncoded, strCipher );
}

bool CCryptography::Decrypt( const std::string &strCipher, std::string &strPlainText, std::string strKey /*= std::string( )*/, std::string strInitVector /*= std::string( )*/ )
{
	CRYPTION_INIT

	std::string strDecoded { };
	return Decode( strCipher, strDecoded ) && Crypt< decrypt_t >( strDecoded, strPlainText, strKey, strInitVector );
}
