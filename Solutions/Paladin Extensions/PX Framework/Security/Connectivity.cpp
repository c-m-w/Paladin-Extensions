/// Connectivity.cpp

#define PX_USE_NAMESPACES
#include "../PX Framework.hpp"

namespace PX::Net
{
	std::string strCookieFile = PX_XOR( R"(cookie.px)" );

	static size_t WriteCallback( void *contents, size_t size, size_t nmemb, void *userp )
	{
		static_cast< std::string* >( userp )->append( static_cast< char* >( contents ), size * nmemb );
		return size * nmemb;
	}

	std::string PX_API GeneratePostData( const post_data_t& dqPostData )
	{
		std::string strFormattedData { };
		for each ( auto pdPostData in dqPostData )
		{
			if ( !strFormattedData.empty( ) )
				strFormattedData += PX_XOR( "&" );
			//strFormattedData += pdPostData.strIdentifier + "=" + pdPostData.strValue;
			const auto strEncryptedValue = Encrypt( pdPostData.strValue );
			// Substr it to length - 1 to remove the \n
			strFormattedData += GenerateIdentifier( pdPostData.strIdentifier ) + PX_XOR( "=" ) + strEncryptedValue.substr( 0, strEncryptedValue.length( ) - 1 );
		}
		// Post data doesn't like plus symbols.
		std::replace( strFormattedData.begin( ), strFormattedData.end( ), '+', ' ' );
		return strFormattedData;
	}

	bool PX_API InitializeConnection( )
	{
		return curl_global_init( CURL_GLOBAL_ALL ) == CURLE_OK && ( pConnection = curl_easy_init( ) ) != nullptr;
	}

	void PX_API CleanupConnection( )
	{
		return curl_easy_cleanup( pConnection );
	}

	std::string PX_API Request( const std::string& _strSite, const post_data_t& dqPostData )
	{
		const static auto szAppdata = getenv( PX_XOR( "APPDATA" ) );
		const static auto strCookieDirectory = szAppdata + ( PX_XOR( R"(\PX\)" ) + strCookieFile );
		std::string strResponseBuffer, strPostDataBuffer = GeneratePostData( dqPostData );

#ifdef _DEBUG
		std::string strErrorBuffer;
		strErrorBuffer.resize( CURL_ERROR_SIZE );
		px_assert( CURLE_OK == curl_easy_setopt( pConnection, CURLOPT_ERRORBUFFER, &strErrorBuffer[ 0 ] ) );
#endif

		px_assert( CURLE_OK == curl_easy_setopt( pConnection, CURLOPT_URL, _strSite.c_str( ) )
				   && CURLE_OK == curl_easy_setopt( pConnection, CURLOPT_POST, 1L )
				   && CURLE_OK == curl_easy_setopt( pConnection, CURLOPT_POSTFIELDS, strPostDataBuffer.c_str( ) )
				   && CURLE_OK == curl_easy_setopt( pConnection, CURLOPT_FOLLOWLOCATION, 1L )
				   // The cookie jar and file do not contain anything stored in the session, only information about the session.
				   // Information stored in $_SESSION is not accessible client side, only server side.
				   // http://php.net/manual/en/intro.session.php
				   && CURLE_OK == curl_easy_setopt( pConnection, CURLOPT_COOKIESESSION, true )
				   && CURLE_OK == curl_easy_setopt( pConnection, CURLOPT_COOKIEFILE, strCookieDirectory.c_str( ) )
				   && CURLE_OK == curl_easy_setopt( pConnection, CURLOPT_COOKIEJAR, strCookieDirectory.c_str( ) )
				   && CURLE_OK == curl_easy_setopt( pConnection, CURLOPT_WRITEFUNCTION, WriteCallback )
				   && CURLE_OK == curl_easy_setopt( pConnection, CURLOPT_WRITEDATA, &strResponseBuffer )
				   // cURL has issues communicating with the revocation server for validating an SSL certificate.
				   // Since we only connect to our site, this isn't an issue so we can just disable the check.
				   && CURLE_OK == curl_easy_setopt( pConnection, CURLOPT_SSL_OPTIONS, CURLSSLOPT_NO_REVOKE )
				   && CURLE_OK == curl_easy_perform( pConnection ) );

		return strResponseBuffer;
	}

	std::string PX_API RequestExtension( unsigned uGameID, bool bInformation )
	{
		post_data_t dqPostData;
		dqPostData.emplace_back( strExtensionIdentifier, std::to_string( uGameID ) );
		dqPostData.emplace_back( strFileIdentifier, bInformation ? PX_XOR( "1" ) : PX_XOR( "0" ) );

		return Request( strDownloadURL, dqPostData );
	}

	wcstr_t wszCredentialsFile = PX_XOR( L"license.px" );

	nlohmann::json jsCredentials = nlohmann::json::parse( PX_XOR( R"(
	{
		"id":"0",
		"sk":"none"	
	})" ) );

	auto bAttemptedLicenceCreation = false;

	bool PX_API CreateLicenseFile( )
	{
		bAttemptedLicenceCreation = true;

		post_data_t dqPostData;
		dqPostData.emplace_back( PX_XOR( "client" ), PX_XOR( "true" ) );

		// BUG should really be checking the return on these
		InitializeConnection( );
		InitializeEncryption( );

		auto strResponse = Request( strKeyURL, dqPostData );

		CleanupConnection( );

		if ( strResponse.empty( ) )
			return false;

		FileWrite( PX_APPDATA + wszCredentialsFile, string_cast< std::wstring >( strResponse ), false, false );
		return true;
	}

	ELogin PX_API Login( bool* bHasExtension /*= nullptr*/ )
	{
		constexpr int iGroupIDS[ PX_EXTENSION_MAX ] { -1, -1, 7, 8, 10 };
		static auto bCreatedLicenseFile = false;
		static auto bRecalled = false;
		std::wstring wstrFile { };

		if ( bRecalled )
			bAttemptedLicenceCreation = false;

		if ( !FileRead( PX_APPDATA + wszCredentialsFile, wstrFile, false ) )
			bCreatedLicenseFile = CreateLicenseFile( );

		try
		{
			jsCredentials = nlohmann::json::parse( string_cast< std::string >( wstrFile ) );
		}
		catch ( nlohmann::detail::parse_error& )
		{
			if ( !bCreatedLicenseFile )
				bCreatedLicenseFile = CreateLicenseFile( );
		}
		catch ( nlohmann::detail::type_error& )
		{
			if ( !bCreatedLicenseFile )
				bCreatedLicenseFile = CreateLicenseFile( );
		}

		if ( !bCreatedLicenseFile
		&& ( jsCredentials[ strUserIDIdentifier ].is_null( )
		  || jsCredentials[ strSecretKeyIdentifier ].is_null( ) ) )
			bCreatedLicenseFile = CreateLicenseFile( );

		if ( bAttemptedLicenceCreation )
		{
			if ( bCreatedLicenseFile && !bRecalled )
			{
				bRecalled = true;
				return Login( bHasExtension );
			}
			return LOGIN_INVALID_LICENSE_FILE;
		}

		post_data_t dqLoginData;
		dqLoginData.emplace_back( strUserIDIdentifier, jsCredentials[ strUserIDIdentifier ].get< std::string >( ) );
		dqLoginData.emplace_back( strSecretKeyIdentifier, jsCredentials[ strSecretKeyIdentifier ].get< std::string >( ) );
		dqLoginData.emplace_back( strHardwareIdentifier, sys::GetSystemInfo( ).dump( ) );

		px_assert( InitializeConnection( )
				   && InitializeEncryption( ) );

		const auto strResponse = Request( strLoginURL, dqLoginData );
		if ( strResponse.empty( ) )
			return LOGIN_CONNECTION_FAILURE;

		auto jsResponse = nlohmann::json::parse( Decrypt( strResponse ) );
		const auto strSecondaryGroups = jsResponse[ "Secondary Groups" ].get< std::string >( );

		if ( bHasExtension != nullptr )
			for ( auto i = PX_EXTENSION_CSGO; i <= PX_EXTENSION_RSIX; i++ )
				bHasExtension[ i ] = strSecondaryGroups.find( std::to_string( iGroupIDS[ i ] ) ) != std::string::npos;

		return ELogin( std::stoi( jsResponse[ "Return Code" ].get< std::string >( ) ) );
	}

	std::string PX_API RequestExtensionInformation( unsigned uExtension )
	{
		auto jsFileInformation = nlohmann::json::parse( Decrypt( RequestExtension( uExtension, false ) ) );
		CleanupConnection( );

		uLoadDLLSize = jsFileInformation[ PX_XOR( "Functions" ) ][ PX_XOR( "LoadDLL" ) ][ PX_XOR( "Size" ) ].get< int >( );
		bLoadDLL = new byte_t[ uLoadDLLSize + 1 ];
		for ( auto u = 0u; u < uLoadDLLSize; u++ )
			bLoadDLL[ u ] = byte_t( jsFileInformation[ PX_XOR( "Functions" ) ][ PX_XOR( "LoadDLL" ) ][ PX_XOR( "Shellcode" ) ][ u ].get< int >( ) );

		uStubSize = jsFileInformation[ PX_XOR( "Functions" ) ][ PX_XOR( "Stub" ) ][ PX_XOR( "Size" ) ].get< int >( );
		bStub = new byte_t[ uStubSize + 1 ];
		for ( auto u = 0u; u < uStubSize; u++ )
			bStub[ u ] = byte_t( jsFileInformation[ PX_XOR( "Functions" ) ][ PX_XOR( "Stub" ) ][ PX_XOR( "Shellcode" ) ][ u ].get< int >( ) );

		std::array< std::string, PX_EXTENSION_SECTIONS > strFileSections;
		std::string strAssembledFile { };

		for ( int i { }; i < PX_EXTENSION_SECTIONS; i++ )
			strFileSections.at( jsFileInformation[ PX_XOR( "DLL" ) ][ PX_XOR( "Order" ) ][ i ].get< int >( ) ) = Decrypt( jsFileInformation[ PX_XOR( "DLL" ) ][ PX_XOR( "Sections" ) ][ i ].get< std::string >( ) );

		for each ( const auto& strSection in strFileSections )
			strAssembledFile += strSection;

		return strAssembledFile;
	}
}
