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

unsigned CCryptography::GenerateNumericHash( const std::string &strBytes )
{
	auto strOutput = GenerateHash< CryptoPP::CRC32 >( strBytes ).substr( 0, 8 );
	auto uReturn = 0u;

	try
	{
		char* pBuffer = nullptr;

		uReturn = std::strtoul( &strOutput[0], &pBuffer, 16 );
	}
	catch( std::out_of_range& e )
	{
		LOG( WARNING, CRYPTOGRAPHY, "Unable to get value of CRC32 hash. Message: %s.", e.what( ) );
	}

	return uReturn;
}

unsigned CCryptography::GenerateNumericHash( const void *pData, std::size_t zSize )
{
	std::string strData { };

	strData.resize( zSize );
	for ( auto p = reinterpret_cast< const unsigned char* >( pData ); std::uintptr_t( p ) < std::uintptr_t( pData ) + zSize; p++ )
		strData[ p - pData ] = *p;

	return GenerateNumericHash( strData );
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

CCryptography _Cryptography;
