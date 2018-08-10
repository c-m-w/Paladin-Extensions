/// Functionality.cpp

#include "PX Manager.hpp"

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

		std::deque < Net::post_data_t > dqPostData;
		dqPostData.emplace_back( "client", "true" );

		Net::InitializeConnection( );
		Cryptography::Initialize( );

		auto strResponse = Request( Net::strKeyURL, dqPostData );

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
		catch( nlohmann::detail::parse_error& )
		{
			bCreatedLicenseFile = CreateLicenseFile( );
		}
		catch( nlohmann::detail::type_error& )
		{
			bCreatedLicenseFile = CreateLicenseFile( );
		}

		if ( jsCredentials[ Net::strUserIDIdentifier ].is_null( ) ||
			 jsCredentials[ Net::strSecretKeyIdentifier ].is_null( ) )
			bCreatedLicenseFile = CreateLicenseFile( );

		if( bAttemptedLicenceCreation )
		{
			if ( bCreatedLicenseFile && !bRecalled )
			{
				bRecalled = true;
				return Login( );
			}
			sys::Delete( );
			return LOGIN_INVALID_LICENSE_FILE;
		}

		std::deque< Net::post_data_t > dqLoginData;
		dqLoginData.emplace_back( Net::strUserIDIdentifier, jsCredentials[ Net::strUserIDIdentifier ].get< std::string >( ) );
		dqLoginData.emplace_back( Net::strSecretKeyIdentifier, jsCredentials[ Net::strSecretKeyIdentifier ].get< std::string >( ) );
		dqLoginData.emplace_back( Net::strHardwareIdentifier, sys::GetSystemInfo( ).dump( ) );

		Net::InitializeConnection( );
		Cryptography::Initialize( );

		const auto strResponse = Request( Net::strLoginURL, dqLoginData );
		return strResponse.empty( ) ? LOGIN_CONNECTION_FAILURE : ELogin( std::stoi( strResponse ) );
	}

	std::string PX_API AssembleCheat( unsigned uGame )
	{
		auto jsFileInformation = nlohmann::json::parse( Cryptography::Decrypt( Net::RequestFile( PX_GAME_CSGO, false ) ) );
		Net::CleanupConnection( );

		std::array< std::string, PX_FILE_SECTIONS > strFileSections;
		std::string strAssembledFile { };

		for ( int i { }; i < PX_FILE_SECTIONS; i++ )
		{
			strFileSections.at( jsFileInformation[ "Order" ][ i ].get< int >( ) ) = Cryptography::Decrypt( jsFileInformation[ "Sections" ][ i ].get< std::string >( ) );
		}
		for each ( const auto& strSection in strFileSections )
			strAssembledFile += strSection;

		return strAssembledFile;
	}
}
