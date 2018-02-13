#include "Framework.hpp"

CConfiguration cfg;

void CConfiguration::LoadConfiguration( std::string strConfig )
{
	std::ifstream fFile( strPath + strConfig + std::string( ".json" ) );

	try
	{
		fFile >> jsConfiguration;
	}
	catch ( nlohmann::detail::parse_error &ex )
	{
		// TODO: Formatting Errors
	}
	catch ( nlohmann::json::type_error &ex )
	{
		// TODO: Missing Variables 
	}

	fFile.close( );
}

void CConfiguration::SaveConfiguration( std::string strConfig )
{
	std::ofstream fFile( strPath + strConfig, std::ofstream::trunc );
	fFile << jsConfiguration.dump( SPACES_PER_TAB );
	fFile.close( );
}

CConfiguration::CConfiguration( )
{
	char chTemp[ MAX_PATH ];
	GetModuleFileName( nullptr, chTemp, MAX_PATH );
	strPath = std::string( chTemp ).substr( 0, std::string( chTemp ).find_last_of( "/\\" ) + 1 ) + "Configurations\\";

	std::ifstream fFile( strPath + "global.json" );
	try
	{
		fFile >> jsGlobalConfiguration;
	}
	catch ( nlohmann::detail::parse_error &ex )
	{
		// TODO: Formatting Errors
	}
	catch ( nlohmann::json::type_error &ex )
	{
		// TODO: Missing Variables 
	}

	try
	{
		LoadConfiguration( jsGlobalConfiguration[ "Default Configuration"].get_ref< nlohmann::json::string_t&>( ) );
	}
	catch ( nlohmann::detail::parse_error &ex )
	{
		// TODO: Formatting Errors
	}
	catch ( nlohmann::json::type_error &ex )
	{
		// TODO: Missing Variables 
	}
	fFile.close( );
}
