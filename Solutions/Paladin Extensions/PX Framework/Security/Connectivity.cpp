/// Connectivity.cpp

#include "../PX Framework.hpp"

using namespace PX::Files;

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
			const auto strEncryptedValue = Cryptography::Encrypt( pdPostData.strValue );
			// Substr it to length - 1 to remove the \n
			strFormattedData += Cryptography::GenerateIdentifier( pdPostData.strIdentifier ) + PX_XOR( "=" ) + strEncryptedValue.substr( 0, strEncryptedValue.length( ) - 1 );
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
		const static auto strCookieDirectory = szAppdata + ( PX_XOR( "PX\\" ) + strCookieFile );
		std::string strResponseBuffer, strPostDataBuffer = GeneratePostData( dqPostData );

		px_assert(	CURLE_OK == curl_easy_setopt( pConnection, CURLOPT_URL, _strSite.c_str( ) )
		            && CURLE_OK == curl_easy_setopt( pConnection, CURLOPT_POST, 1L )
		            && CURLE_OK == curl_easy_setopt( pConnection, CURLOPT_POSTFIELDS, strPostDataBuffer.c_str( ) )
		            && CURLE_OK == curl_easy_setopt( pConnection, CURLOPT_FOLLOWLOCATION, 1L )
					/// The cookie jar and file do not contain anything stored in the session, only information about the session.
					/// Information stored in $_SESSION is not accessible client side, only server side.
					/// http://php.net/manual/en/intro.session.php
					&& CURLE_OK == curl_easy_setopt( pConnection, CURLOPT_COOKIESESSION, true )
					&& CURLE_OK == curl_easy_setopt( pConnection, CURLOPT_COOKIEFILE, strCookieDirectory.c_str( ) )
					&& CURLE_OK == curl_easy_setopt( pConnection, CURLOPT_COOKIEJAR, strCookieDirectory.c_str( ) )
		            && CURLE_OK == curl_easy_setopt( pConnection, CURLOPT_WRITEFUNCTION, WriteCallback )
					&& CURLE_OK == curl_easy_setopt( pConnection, CURLOPT_WRITEDATA, &strResponseBuffer )
		            && CURLE_OK == curl_easy_perform( pConnection ) );

		return strResponseBuffer;
	}

	std::string PX_API RequestFile( unsigned uGameID, bool bInformation )
	{
		post_data_t dqPostData;
		dqPostData.emplace_back( strExtensionIdentifier, std::to_string( uGameID ) );
		dqPostData.emplace_back( strFileIdentifier, bInformation ? PX_XOR( "1" ) : PX_XOR( "0" ) );

		return Request( strDownloadURL, dqPostData );
	}

	std::wstring wszCredentialsFile = PX_XOR( L"license.px" );

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

		InitializeConnection( );
		Cryptography::Initialize( );

		auto strResponse = Request( strKeyURL, dqPostData );

		CleanupConnection( );

		if ( strResponse.empty( ) )
			return false;

		FileWrite( wszCredentialsFile, string_cast< std::wstring >( strResponse ), true, false );
		return true;
	}

	ELogin PX_API Login( )
	{
		static auto bCreatedLicenseFile = false;
		static auto bRecalled = false;
		std::wstring wstrFile { };

		if ( bRecalled )
			bAttemptedLicenceCreation = false;

		if ( !FileRead( wszCredentialsFile, wstrFile, true ) )
			bCreatedLicenseFile = CreateLicenseFile( );

		try
		{
			jsCredentials = nlohmann::json::parse( string_cast< std::string >( wstrFile ) );
		}
		catch ( nlohmann::detail::parse_error& )
		{
			bCreatedLicenseFile = CreateLicenseFile( );
		}
		catch ( nlohmann::detail::type_error& )
		{
			bCreatedLicenseFile = CreateLicenseFile( );
		}

		if ( jsCredentials[ strUserIDIdentifier ].is_null( ) ||
			 jsCredentials[ strSecretKeyIdentifier ].is_null( ) )
			bCreatedLicenseFile = CreateLicenseFile( );

		if ( bAttemptedLicenceCreation )
		{
			if ( bCreatedLicenseFile && !bRecalled )
			{
				bRecalled = true;
				return Login( );
			}
			sys::Delete( );
			return LOGIN_INVALID_LICENSE_FILE;
		}

		post_data_t dqLoginData;
		dqLoginData.emplace_back( strUserIDIdentifier, jsCredentials[ strUserIDIdentifier ].get< std::string >( ) );
		dqLoginData.emplace_back( strSecretKeyIdentifier, jsCredentials[ strSecretKeyIdentifier ].get< std::string >( ) );
		dqLoginData.emplace_back( strHardwareIdentifier, sys::GetSystemInfo( ).dump( ) );

		InitializeConnection( );
		Cryptography::Initialize( );

		const auto strResponse = Request( strLoginURL, dqLoginData );
		return strResponse.empty( ) ? LOGIN_CONNECTION_FAILURE : ELogin( std::stoi( strResponse ) );
	}

	std::string PX_API RequestExtensionInformation( unsigned uExtension )
	{
		auto strBuffer = Cryptography::Decrypt( RequestFile( uExtension, false ) );
		auto jsFileInformation = nlohmann::json::parse( strBuffer );
		CleanupConnection( );

		sys::uLoadDLLSize = jsFileInformation[ PX_XOR( "Functions" ) ][ PX_XOR( "LoadDLL" ) ][ PX_XOR( "Size" ) ].get< int >( );
		sys::bLoadDLL = new byte_t[ sys::uLoadDLLSize + 1 ];
		for ( auto u = 0u; u < sys::uLoadDLLSize; u++ )
			sys::bLoadDLL[ u ] = byte_t( jsFileInformation[ PX_XOR( "Functions" ) ][ PX_XOR( "LoadDLL" ) ][ PX_XOR( "Shellcode" ) ][ u ].get< int >( ) );

		sys::uStubSize = jsFileInformation[ PX_XOR( "Functions" ) ][ PX_XOR( "Stub" ) ][ PX_XOR( "Size" ) ].get< int >( );
		sys::bStub = new byte_t[ sys::uStubSize + 1 ];
		for ( auto u = 0u; u < sys::uStubSize; u++ )
			sys::bStub[ u ] = byte_t( jsFileInformation[ PX_XOR( "Functions" ) ][ PX_XOR( "Stub" ) ][ PX_XOR( "Shellcode" ) ][ u ].get< int >( ) );

		std::array< std::string, PX_EXTENSION_SECTIONS > strFileSections;
		std::string strAssembledFile { };

		for ( int i { }; i < PX_EXTENSION_SECTIONS; i++ )
			strFileSections.at( jsFileInformation[ PX_XOR( "DLL" ) ][ PX_XOR( "Order" ) ][ i ].get< int >( ) ) = Cryptography::Decrypt( jsFileInformation[ PX_XOR( "DLL" ) ][ PX_XOR( "Sections" ) ][ i ].get< std::string >( ) );

		for each ( const auto& strSection in strFileSections )
			strAssembledFile += strSection;

		return strAssembledFile;
	}

	bool Heartbeat( )
	{
		// assert appdata data.px is there
		// assert login
		// assert anything else
		return true;
	}
}
