/// Connectivity.hpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#define USE_DEFINITIONS
#include "../../Framework.hpp"

#define ENSURE_DATA_SET( _PostData )																								\
	if ( !bPostDataSet[ _PostData ] )																								\
		throw std::runtime_error( ( ENC( "Post data ID " ) + std::to_string( int( _PostData ) ) + ENC( " not set." ) ).c_str( ) );

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
		_Log.Log( EPrefix::ERROR, ELocation::CONNECTIVITY, ENC( "Could not global initialize cURL. Error code: %i." ), _Code );
		return false;
	}

	if ( ( hInstance = curl_easy_init( ) ) != nullptr )
	{
		_Log.Log( EPrefix::SUCCESS, ELocation::CONNECTIVITY, ENC( "Initialized cURL successfully." ) );
		strScriptLocator = ENC( "https://www.paladin-extensions.com/Run.php" );
		vecIllegalCharacters.emplace_back( '&', ENC( "AMP" ) );
		vecIllegalCharacters.emplace_back( '=', ENC( "EQUAL" ) );
		vecIllegalCharacters.emplace_back( '<', ENC( "LESS" ) );
		vecIllegalCharacters.emplace_back( '>', ENC( "GREATER" ) );
		vecIllegalCharacters.emplace_back( '\'', ENC( "QUOTE" ) );
		vecIllegalCharacters.emplace_back( '+', ENC( "PLUS" ) );
		strPostDataIdentifiers[ PURCHASE_KEY ] = ENC( "key" );
		strPostDataIdentifiers[ HARDWARE ] = ENC( "hw" );
		strPostDataIdentifiers[ LIBRARY ] = ENC( "library" );
		strPostDataIdentifiers[ BAN_REASON ] = ENC( "reason" );
		strPostDataIdentifiers[ PROCESS_LIST ] = ENC( "process_list" );
		strPostDataIdentifiers[ INSTALLED_PROGRAMS ] = ENC( "installed_programs" );
		strPostDataIdentifiers[ OPEN_WINDOWS ] = ENC( "open_windows" );
		strPostDataIdentifiers[ ACTION ] = ENC( "action" );
		memset( bPostDataSet, false, sizeof( bool ) * POST_DATA_MAX );
		return true;
	}

	_Log.Log( EPrefix::ERROR, ELocation::CONNECTIVITY, ENC( "Could not open a cURL instance." ) );
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

bool CConnectivity::TryConnection( std::string &strOut, std::string *pErrorBuffer, int iRetries /*= 0*/ )
{
	const auto _Code = curl_easy_perform( hInstance );
	if ( _Code != CURLE_OK )
	{
		_Log.Log( EPrefix::ERROR, ELocation::CONNECTIVITY, ENC( "Failed to perform connection. Error code: %i. Retries: %i." ), _Code, iRetries );
		if ( pErrorBuffer != nullptr )
			_Log.Log( EPrefix::INFO, ELocation::CONNECTIVITY, ENC( "Error message: " ) + *pErrorBuffer );

		return iRetries < MAX_RETRIES ? TryConnection( strOut, pErrorBuffer, ++iRetries ) : false;
	}

	if ( strOut.empty( ) )
	{
		_Log.Log( EPrefix::ERROR, ELocation::CONNECTIVITY, ENC( "Response was empty. Retries: %i." ), _Code, iRetries );
		if ( pErrorBuffer != nullptr )
			_Log.Log( EPrefix::INFO, ELocation::CONNECTIVITY, ENC( "Error message: " ) + *pErrorBuffer );

		return iRetries < MAX_RETRIES ? TryConnection( strOut, pErrorBuffer, ++iRetries ) : false;
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
	bPostDataSet[ int( _Identifier ) ] = true;
}

bool CConnectivity::Request( EAction _Action, std::string &strOut )
{
	switch ( _Action )
	{
		case LOGIN:
		{
			ENSURE_DATA_SET( PURCHASE_KEY );
			ENSURE_DATA_SET( HARDWARE )
		}
		break;

		case GET_LIBRARY:
		case GET_LIBRARY_DATA:
		{
			ENSURE_DATA_SET( LIBRARY )
		}
			break;

		case BAN:
		{
			ENSURE_DATA_SET( PURCHASE_KEY )
			ENSURE_DATA_SET( BAN_REASON )
			ENSURE_DATA_SET( PROCESS_LIST )
			ENSURE_DATA_SET( INSTALLED_PROGRAMS )
		}
		break;

		case GET_PROTOCOL:
		case GET_DATA:
		case GET_SHELLCODE:
		case GET_RESOURCE_HASH:
		case GET_RESOURCES:
			break;

		default:
			throw std::runtime_error( ENC( "Attempting connection with invalid action." ) );
	}

	AddPostData( ACTION, std::to_string( int( _Action ) ) );
	_Filesystem.StoreCurrentWorkingDirectory( );
	_Filesystem.ChangeWorkingDirectory( CFilesystem::GetAppdataDirectory( ) );
	_Filesystem.DecryptFile( CFilesystem::strCookieFile );

	const auto strCookieFile = _Filesystem.FileToPath( _Filesystem.strCookieFile );
	std::string strErrorBuffer;

	strErrorBuffer.resize( CURL_ERROR_SIZE );
	const auto bSetErrorBuffer = SetConnectionParameter( CURLOPT_ERRORBUFFER, &strErrorBuffer[ 0 ] );
	if ( !bSetErrorBuffer )
		_Log.Log( EPrefix::WARNING, ELocation::CONNECTIVITY, ENC( "Unable to set error buffer for cURL." ) );

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
			_Log.Log( EPrefix::ERROR, ELocation::CONNECTIVITY, ENC( "Setting cURL parameters failed, message: " ) + strErrorBuffer );

		ResetConnection( );
		_Filesystem.EncryptFile( CFilesystem::strCookieFile );
		_Filesystem.RestoreWorkingDirectory( );
		return false;
	}

	const auto bReturn = TryConnection( strOut, bSetErrorBuffer ? &strErrorBuffer : nullptr );
	ResetConnection( );
	_Filesystem.EncryptFile( CFilesystem::strCookieFile );
	_Filesystem.RestoreWorkingDirectory( );
	return bReturn;
}

CConnectivity::illegal_post_data_character_t::illegal_post_data_character_t( char _chCharacter, const std::string &_strReplacement ): chCharacter( _chCharacter ), strReplacement( _strReplacement )
{ }

CConnectivity _Connection;
