/// Connectivity.hpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#include "../../Framework.hpp"

std::size_t WriteCallback( void *pData, std::size_t zMemberSize, std::size_t zMembers, void *pBuffer )
{
	static_cast< std::string* >( pBuffer )->append( reinterpret_cast< char* >( pData ), zMemberSize * zMembers );
	return zMemberSize * zMembers;
}

bool CConnectivity::Initialize( )
{
	const auto _Code = curl_global_init( CURL_GLOBAL_ALL );
	if ( _Code != CURLE_OK )
	{
		_Log.Log( EPrefix::ERROR, ELocation::CONNECTIVITY, XOR( "Could not global initialize cURL. Error code: %i." ), _Code );
		return false;
	}

	if ( ( hConnection = curl_easy_init( ) ) != nullptr )
	{
		_Log.Log( EPrefix::SUCCESS, ELocation::CONNECTIVITY, XOR( "Initialized cURL successfully." ) );
		vecIllegalCharacters.emplace_back( '&', XOR( "AMP" ) );
		vecIllegalCharacters.emplace_back( '=', XOR( "EQUAL" ) );
		vecIllegalCharacters.emplace_back( '<', XOR( "LESS" ) );
		vecIllegalCharacters.emplace_back( '>', XOR( "GREATER" ) );
		vecIllegalCharacters.emplace_back( '\'', XOR( "QUOTE" ) );
		vecIllegalCharacters.emplace_back( '+', XOR( "PLUS" ) );
		return true;
	}

	_Log.Log( EPrefix::ERROR, ELocation::CONNECTIVITY, XOR( "Could not open a cURL instance." ) );
	return false;
}

void CConnectivity::Shutdown( )
{
	return curl_easy_cleanup( hConnection );
}

void CConnectivity::ValidateString( std::string &strToValidate )
{
	for ( auto &_IllegalCharacter: vecIllegalCharacters )
		_IllegalCharacter.ValidateString( strToValidate );
}

bool CConnectivity::Request( const std::string &strUniformResourceLocator, std::initializer_list< post_data_t > initData, std::string &strOut, int iRetries /*= 0*/ )
{
	std::string strPostData { };
	for each ( auto &_Data in initData )
	{
		if ( !strPostData.empty( ) )
			strPostData += '&';

		strPostData += _Data.FormatString( );
	}

	_Filesystem.ChangeWorkingDirectory( CFilesystem::GetAppdataDirectory( ) );
	const auto strCookieFile = _Filesystem.FileToPath( _Filesystem.strCookieFile );
	std::string strErrorBuffer { };
	strErrorBuffer.resize( CURL_ERROR_SIZE );
	const auto bSetErrorBuffer = SetConnectionParameter( CURLOPT_ERRORBUFFER, &strErrorBuffer[ 0 ] );

	if ( !SetConnectionParameter( CURLOPT_URL, strUniformResourceLocator.c_str( ) )
		|| !SetConnectionParameter( CURLOPT_POST, TRUE )
		|| !SetConnectionParameter( CURLOPT_POSTFIELDS, strPostData.c_str( ) )
		|| !SetConnectionParameter( CURLOPT_FOLLOWLOCATION, TRUE )
		|| !SetConnectionParameter( CURLOPT_COOKIESESSION, TRUE )
		|| !SetConnectionParameter( CURLOPT_COOKIEFILE, strCookieFile.c_str( ) )
		|| !SetConnectionParameter( CURLOPT_COOKIEJAR, strCookieFile.c_str( ) )
		|| !SetConnectionParameter( CURLOPT_WRITEFUNCTION, reinterpret_cast< void* >( WriteCallback ) )
		|| !SetConnectionParameter( CURLOPT_WRITEDATA, &strOut )
		|| !SetConnectionParameter( CURLOPT_SSL_OPTIONS, CURLSSLOPT_NO_REVOKE )
		|| !SetConnectionParameter( CURLOPT_TIMEOUT, MAX_TIMEOUT )
		|| !SetConnectionParameter( CURLOPT_SSL_VERIFYHOST, FALSE )
		|| !SetConnectionParameter( CURLOPT_SSL_VERIFYPEER, FALSE ) )
	{
		if ( bSetErrorBuffer )
			_Log.Log( EPrefix::ERROR, ELocation::CONNECTIVITY, XOR( "Setting cURL parameters failed, message: " ) + strErrorBuffer );

		return false;
	}

	const auto _Code = curl_easy_perform( hConnection );
	if ( _Code != CURLE_OK )
	{
		_Log.Log( EPrefix::ERROR, ELocation::CONNECTIVITY, XOR( "Failed to perform connection. Error code: %i. Retries: %i." ), _Code, iRetries );
		if ( bSetErrorBuffer )
			_Log.Log( EPrefix::INFO, ELocation::CONNECTIVITY, XOR( "Error message: " ) + strErrorBuffer );

		return iRetries < MAX_RETRIES ? Request( strUniformResourceLocator, initData, strOut, iRetries++ ) : false;
	}

	if ( strOut.empty( ) )
	{
		_Log.Log( EPrefix::ERROR, ELocation::CONNECTIVITY, XOR( "Response was empty. Retries: %i." ), _Code, iRetries );
		if ( bSetErrorBuffer )
			_Log.Log( EPrefix::INFO, ELocation::CONNECTIVITY, XOR( "Error message: " ) + strErrorBuffer );

		return iRetries < MAX_RETRIES ? Request( strUniformResourceLocator, initData, strOut, iRetries++ ) : false;
	}

	return true;
}

CConnectivity::illegal_post_data_character_t::illegal_post_data_character_t( char _chCharacter, const std::string &_strReplacement ): chCharacter( _chCharacter ), strReplacement( _strReplacement )
{ }

void CConnectivity::illegal_post_data_character_t::ValidateString( std::string &strToValidate )
{
	auto zPlace = std::string::npos;

	while ( ( zPlace = strToValidate.find( chCharacter ) ) != std::string::npos )
	{
		strToValidate.erase( strToValidate.begin( ) + zPlace );
		strToValidate.insert( zPlace, strReplacement );
	}
}

std::string CConnectivity::post_data_t::GenerateIdentifier( ) const
{
	auto strReturn = _Cryptography.GenerateHash( strIdentifier ).substr( 0, IDENTIFIER_LENGTH );
	ValidateString( strReturn );
	return strReturn;
}

std::string CConnectivity::post_data_t::ProcessValue( ) const
{
	std::string strReturn { };
	if ( _Cryptography.Crypt< encrypt_t >( strValue, strReturn ) )
	{
		ValidateString( strReturn );
		return strReturn;
	}

	return { };
}

post_data_t::post_data_t( const std::string &_strName, const std::string &_strValue ): strIdentifier( _strName ), strValue( _strValue )
{ }

std::string post_data_t::FormatString( ) const
{
	auto strReturn = GenerateIdentifier( ) + '=' + ProcessValue( );
	return strReturn;
}
