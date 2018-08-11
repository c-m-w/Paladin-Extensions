/// Functionality.cpp

#include "PX Manager.hpp"

using namespace Net;

namespace Manager
{
	std::wstring wszCredentialsFile = PX_XOR( L"user.license" );

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
		dqPostData.emplace_back( "client", "true" );

		Net::InitializeConnection( );
		Cryptography::Initialize( );

		auto strResponse = Request( strKeyURL, dqPostData );

		Net::CleanupConnection( );

		if ( strResponse.empty( ) )
			return false;

		Files::WriteFile( wszCredentialsFile, string_cast< std::wstring >( strResponse ), true, false );
		return true;
	}

	ELogin PX_API Login( )
	{
		static auto bCreatedLicenseFile = false;
		static auto bRecalled = false;
		std::string strFile { };

		if ( bRecalled )
			bAttemptedLicenceCreation = false;

		if ( !Files::ReadFile( wszCredentialsFile, strFile, true ) )
			bCreatedLicenseFile = CreateLicenseFile( );

		try
		{
			jsCredentials = nlohmann::json::parse( strFile );
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

		Net::InitializeConnection( );
		Cryptography::Initialize( );

		const auto strResponse = Request( strLoginURL, dqLoginData );
		return strResponse.empty( ) ? LOGIN_CONNECTION_FAILURE : ELogin( std::stoi( strResponse ) );
	}

	extensions_t PX_API RetrieveExtensionInformation( )
	{
		auto strSecurityBuffer = Cryptography::Decrypt( Request( "https://www.paladin.rip/auth/extensions.php", post_data_t { } ) );
		if ( strSecurityBuffer.empty( ) )
			return { };

		auto jsFileInformation = nlohmann::json::parse( strSecurityBuffer );
		extensions_t extReturn;
		extReturn.emplace_back( "Empty", "Empty", "Empty", "Empty", "Empty" ); // Extension 0 doesn't exist & we dont want to use default constructor cause itll make the connection fail.

		for each ( auto& extension in jsFileInformation[ "Info" ] )
			extReturn.emplace_back( extension[ "Name" ].get< std::string >( ), extension[ "Status" ].get< std::string >( ),
									extension[ "Estimated Next Update" ].get< std::string >( ), extension[ "Last Update" ].get< std::string >( ),
									extension[ "Version" ].get< std::string >( ) );
		return extReturn;
	}

	std::string* PX_API RetrieveLaunchInformation( )
	{
		auto strSecurityBuffer = Cryptography::Decrypt( Request( "https://www.paladin.rip/auth/lastlaunch.php", post_data_t { } ) );
		if ( strSecurityBuffer.empty( ) )
			return nullptr;

		auto jsLaunchInformation = nlohmann::json::parse(  strSecurityBuffer );
		static std::string strReturn[ PX_EXTENSION_MAX ] { { }, { }, { }, { }, { } };

		for( auto u = PX_EXTENSION_CSGO; u <= PX_EXTENSION_RSIX; u++ )
			strReturn[ u ] = TimeToDate( jsLaunchInformation[ std::to_string( u ) ].get< int >( ) );
		return strReturn;
	}

	std::string PX_API AssembleExtension( unsigned uExtension )
	{
		auto jsFileInformation = nlohmann::json::parse( Cryptography::Decrypt( RequestFile( uExtension, false ) ) );
		CleanupConnection( );

		std::array< std::string, PX_FILE_SECTIONS > strFileSections;
		std::string strAssembledFile { };

		for ( int i { }; i < PX_FILE_SECTIONS; i++ )
			strFileSections.at( jsFileInformation[ "Order" ][ i ].get< int >( ) ) = Cryptography::Decrypt( jsFileInformation[ "Sections" ][ i ].get< std::string >( ) );

		for each ( const auto& strSection in strFileSections )
			strAssembledFile += strSection;

		return strAssembledFile;
	}
}
