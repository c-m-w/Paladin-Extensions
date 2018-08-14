/// Functionality.cpp

#include "PX Manager.hpp"

using namespace Net;
using namespace Files;

namespace Manager
{
	extensions_t PX_API RetrieveExtensionInformation( )
	{
		auto strSecurityBuffer = Cryptography::Decrypt( Request( PX_XOR( "https://www.paladin.rip/auth/extensions.php" ), post_data_t { } ) );
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
		auto strSecurityBuffer = Cryptography::Decrypt( Request( PX_XOR( "https://www.paladin.rip/auth/lastlaunch.php" ), post_data_t { } ) );
		if ( strSecurityBuffer.empty( ) )
			return nullptr;

		auto jsLaunchInformation = nlohmann::json::parse(  strSecurityBuffer );
		static std::string strReturn[ PX_EXTENSION_MAX ] { { }, { }, { }, { }, { } };

		for( auto u = PX_EXTENSION_CSGO; u <= PX_EXTENSION_RSIX; u++ )
			strReturn[ u ] = TimeToDate( jsLaunchInformation[ std::to_string( u ) ].get< int >( ) );
		return strReturn;
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
}
