/// Connectivity.hpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#include "../../Framework.hpp"

#define ENSURE_DATA_SET( _PostData )																								\
	if ( !bPostDataSet[ _PostData ] )																								\
		throw std::runtime_error( ( XOR( "Post data ID " ) + std::to_string( int( _PostData ) ) + XOR( " not set." ) ).c_str( ) );	\

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

	if ( ( hInstance = curl_easy_init( ) ) != nullptr )
	{
		_Log.Log( EPrefix::SUCCESS, ELocation::CONNECTIVITY,	XOR( "Initialized cURL successfully." ) );
		strScriptLocator						=				XOR( "https://www.paladin-extensions.com/Run.php" );
		vecIllegalCharacters.emplace_back( '&',					XOR( "AMP" ) );
		vecIllegalCharacters.emplace_back( '=',					XOR( "EQUAL" ) );
		vecIllegalCharacters.emplace_back( '<',					XOR( "LESS" ) );
		vecIllegalCharacters.emplace_back( '>',					XOR( "GREATER" ) );
		vecIllegalCharacters.emplace_back( '\'',				XOR( "QUOTE" ) );
		vecIllegalCharacters.emplace_back( '+',					XOR( "PLUS" ) );
		strPostDataIdentifiers[ USER_ID ]		=				XOR( "id" );
		strPostDataIdentifiers[ SECRET_KEY ]	=				XOR( "sk" );
		strPostDataIdentifiers[ HARDWARE ]		=				XOR( "hw" );
		strPostDataIdentifiers[ HASH ]			=				XOR( "hash" );
		strPostDataIdentifiers[ ACTION ]		=				XOR( "action" );
		memset( bPostDataSet, false, sizeof( bool ) * POST_DATA_MAX );
		return true;
	}

	_Log.Log( EPrefix::ERROR, ELocation::CONNECTIVITY, XOR( "Could not open a cURL instance." ) );
	return false;
}

void CConnectivity::illegal_post_data_character_t::ValidateString( std::string &strToValidate )
{
	auto zPlace = std::string::npos;

	while ( ( zPlace = strToValidate.find( chCharacter ) ) != std::string::npos )
	{
		strToValidate.erase( strToValidate.begin( ) + zPlace );
		strToValidate.insert( zPlace, strReplacement );
	}
}

std::string CConnectivity::GenerateIdentifier( EPostData _Identifier )
{
	auto strReturn = _Cryptography.GenerateHash( strPostDataIdentifiers[ _Identifier ] ).substr( 0, IDENTIFIER_LENGTH );
	ValidateString( strReturn );
	return strReturn;
}

std::string CConnectivity::ProcessValue( const std::string &strValue )
{
	std::string strReturn { };
	if ( _Cryptography.Encrypt( strValue, strReturn ) )
	{
		ValidateString( strReturn );
		return strReturn;
	}

	return { };
}

void CConnectivity::ResetConnection( )
{
	strCurrentPostData.clear( );
	curl_easy_reset( hInstance );
	memset( bPostDataSet, false, sizeof( bool ) * POST_DATA_MAX );
}

bool CConnectivity::TryConnection( std::string &strOut, std::string* pErrorBuffer, int iRetries /*= 0*/ )
{
	const auto _Code = curl_easy_perform( hInstance );
	if ( _Code != CURLE_OK )
	{
		_Log.Log( EPrefix::ERROR, ELocation::CONNECTIVITY, XOR( "Failed to perform connection. Error code: %i. Retries: %i." ), _Code, iRetries );
		if ( pErrorBuffer != nullptr )
			_Log.Log( EPrefix::INFO, ELocation::CONNECTIVITY, XOR( "Error message: " ) + *pErrorBuffer );

		return iRetries < MAX_RETRIES ? TryConnection( strOut, pErrorBuffer, iRetries++ ) : false;
	}

	if ( strOut.empty( ) )
	{
		_Log.Log( EPrefix::ERROR, ELocation::CONNECTIVITY, XOR( "Response was empty. Retries: %i." ), _Code, iRetries );
		if ( pErrorBuffer != nullptr )
			_Log.Log( EPrefix::INFO, ELocation::CONNECTIVITY, XOR( "Error message: " ) + *pErrorBuffer );

		return iRetries < MAX_RETRIES ? TryConnection( strOut, pErrorBuffer, iRetries++ ) : false;
	}

	return true;
}

void CConnectivity::Uninitialize( )
{
	return curl_easy_cleanup( hInstance );
}

void CConnectivity::ValidateString( std::string &strToValidate )
{
	for ( auto &_IllegalCharacter: vecIllegalCharacters )
		_IllegalCharacter.ValidateString( strToValidate );
}

void CConnectivity::AddPostData( EPostData _Identifier, const std::string &strValue )
{
	if ( !strCurrentPostData.empty( ) )
		strCurrentPostData += '&';

	strCurrentPostData += GenerateIdentifier( _Identifier ) + '=' + ProcessValue( strValue );
}

bool CConnectivity::Request( EAction _Action, std::string &strOut )
{
	switch ( _Action )
	{
		case LOGIN:
		{
			ENSURE_DATA_SET( USER_ID )
			ENSURE_DATA_SET( SECRET_KEY )
			ENSURE_DATA_SET( HARDWARE )
			ENSURE_DATA_SET( HASH )
		}
		break;

		case DOWNLOAD:
		case BAN:
		case GET_RESOURCE_HASH:
		case GET_RESOURCES:
			break;

		default:
			throw std::runtime_error( XOR( "Attempting connection with invalid action." ) );
	}

	AddPostData( ACTION, std::to_string( int( _Action ) ) );
	_Filesystem.StoreCurrentWorkingDirectory( );
	_Filesystem.ChangeWorkingDirectory( CFilesystem::GetAppdataDirectory( ) );

	const auto strCookieFile = _Filesystem.FileToPath( _Filesystem.strCookieFile );
	_Filesystem.RestoreWorkingDirectory( );
	std::string strErrorBuffer;

	strErrorBuffer.resize( CURL_ERROR_SIZE );
	const auto bSetErrorBuffer = SetConnectionParameter( CURLOPT_ERRORBUFFER, &strErrorBuffer[ 0 ] );
	if ( !bSetErrorBuffer )
		_Log.Log( EPrefix::WARNING, ELocation::CONNECTIVITY, XOR( "Unable to set error buffer for cURL." ) );

	if ( !SetConnectionParameter( CURLOPT_URL, strScriptLocator.c_str( ) )
		|| !SetConnectionParameter( CURLOPT_POST, TRUE )
		|| !SetConnectionParameter( CURLOPT_POSTFIELDS, strCurrentPostData.c_str( ) )
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

		ResetConnection( );
		return false;
	}

	const auto bReturn = TryConnection( strOut, bSetErrorBuffer ? &strErrorBuffer : nullptr );
	ResetConnection( );
	return bReturn;
}

CConnectivity::illegal_post_data_character_t::illegal_post_data_character_t( char _chCharacter, const std::string &_strReplacement ): chCharacter( _chCharacter ), strReplacement( _strReplacement )
{ }
