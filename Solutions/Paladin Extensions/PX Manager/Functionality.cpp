/// Functionality.cpp

#include "PX Manager.hpp"

namespace Manager
{
	extensions_t PX_API RetrieveExtensionInformation( )
	{
		auto strSecurityBuffer = Decrypt( Request( PX_XOR( "https://www.paladin.rip/auth/extensions.php/" ), post_data_t { } ) );
		if ( strSecurityBuffer.empty( ) )
			return { };

		auto jsFileInformation = nlohmann::json::parse( strSecurityBuffer );
		extensions_t extReturn;
		extReturn.emplace_back( PX_XOR( "Empty" ), PX_XOR( "Empty" ), PX_XOR( "Empty" ), PX_XOR( "Empty" ), PX_XOR( "Empty" ) ); // Extension 0 doesn't exist & we dont want to use default constructor cause itll make the connection fail.

		for each ( auto& extension in jsFileInformation[ PX_XOR( "Info" ) ] )
			extReturn.emplace_back( extension[ PX_XOR( "Name" ) ].get< std::string >( ), extension[ PX_XOR( "Status" ) ].get< std::string >( ),
									extension[ PX_XOR( "Estimated Next Update" ) ].get< std::string >( ), extension[ PX_XOR( "Last Update" ) ].get< std::string >( ),
									extension[ PX_XOR( "Version" ) ].get< std::string >( ) );
		return extReturn;
	}

	std::string* PX_API RetrieveLaunchInformation( )
	{
		auto strSecurityBuffer = Decrypt( Request( PX_XOR( "https://www.paladin.rip/auth/lastlaunch.php/" ), post_data_t { } ) );
		if ( strSecurityBuffer.empty( ) )
			return nullptr;

		auto jsLaunchInformation = nlohmann::json::parse( strSecurityBuffer );
		static std::string strReturn[ PX_EXTENSION_MAX ] { { }, { }, { }, { }, { } };

		for( auto u = PX_EXTENSION_CSGO; u <= PX_EXTENSION_RSIX; u++ )
			strReturn[ u ] = TimeToDate( jsLaunchInformation[ std::to_string( u ) ].get< int >( ) );
		return strReturn;
	}
}
