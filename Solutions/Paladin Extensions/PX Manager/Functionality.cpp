/// Functionality.cpp

#include "PX Precompiled.hpp"
#include "PX Manager.hpp"

namespace Manager
{
	extensions_t PX_API RetrieveExtensionInformation( )
	{
		auto strSecurityBuffer = Decrypt( Request( PX_XOR( "https://www.paladin-extensions.com/auth/extensions.php/" ), post_data_t { } ) );
		if ( strSecurityBuffer.empty( ) )
			return { };

		auto jsFileInformation = nlohmann::json::parse( strSecurityBuffer );
		extensions_t extReturn;
		extReturn.emplace_back( PX_XOR( "Empty" ), PX_XOR( "Empty" ), PX_XOR( "Empty" ), PX_XOR( "Empty" ), PX_XOR( "Empty" ) ); // Extension 0 doesn't exist & we dont want to use default constructor cause itll make the connection fail.

		for each ( auto& extension in jsFileInformation[ PX_XOR( "Info" ) ] )
			extReturn.emplace_back( extension[ PX_XOR( "Name" ) ].get< str_t >( ), extension[ PX_XOR( "Status" ) ].get< str_t >( ),
									extension[ PX_XOR( "Estimated Next Update" ) ].get< str_t >( ), extension[ PX_XOR( "Last Update" ) ].get< str_t >( ),
									extension[ PX_XOR( "Version" ) ].get< str_t >( ) );
		return extReturn;
	}

	str_t* PX_API RetrieveLaunchInformation( )
	{
		auto strSecurityBuffer = Decrypt( Request( PX_XOR( "https://www.paladin-extensions.com/auth/lastlaunch.php/" ), post_data_t { } ) );
		if ( strSecurityBuffer.empty( ) )
			return nullptr;

		auto jsLaunchInformation = nlohmann::json::parse( strSecurityBuffer );
		static str_t strReturn[ PX_EXTENSION_MAX ] { { }, { }, { }, { }, { } };

		for( auto u = PX_EXTENSION_CSGO; u < PX_EXTENSION_MAX; u++ )
			strReturn[ u ] = TimeToDate( jsLaunchInformation[ std::to_string( u ) ].get< int >( ) );
		return strReturn;
	}
}
