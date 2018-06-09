/// Configuration.cpp

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <nlohmann/json.hpp>

#include "../../Framework.hpp"

namespace Paladin
{
	CConfiguration::CConfiguration( )
	{
		LPWSTR wchTemp = new wchar_t[ MAX_PATH ];
		GetModuleFileName( nullptr, wchTemp, MAX_PATH );
		char chTemp[ MAX_PATH ];
		wcstombs( chTemp, wchTemp, MAX_PATH );
		strPath = std::string( chTemp ).substr( 0, std::string( chTemp ).find_last_of( XOR( "/\\" ) ) + 1 ) + XOR( "Configurations\\" );

		std::ifstream fFile( strPath + XOR( "global.json" ) );
		try
		{
			fFile >> jsGlobalConfiguration;
		}
		catch ( nlohmann::detail::parse_error & )
		{
			// TODO: Formatting Errors
		}
		catch ( nlohmann::json::type_error & )
		{
			// TODO: Missing Variables 
		}

		try
		{
			LoadConfiguration( jsGlobalConfiguration[ XOR( "Default Configuration" ) ].get_ref< nlohmann::json::string_t & >( ) );
		}
		catch ( nlohmann::detail::parse_error & )
		{
			// TODO: Formatting Errors
		}
		catch ( nlohmann::json::type_error & )
		{
			// TODO: Missing Variables 
		}
		fFile.close( );
	}

	void CConfiguration::LoadConfiguration( std::string strConfig )
	{
		std::ifstream fFile( strPath + strConfig + std::string( XOR( ".json" ) ) );

		try
		{
			fFile >> jsConfiguration;
		}
		catch ( nlohmann::detail::parse_error & )
		{
			// TODO: Formatting Errors
		}
		catch ( nlohmann::json::type_error & )
		{
			// TODO: Missing Variables 
		}

		fFile.close( );
	}

	void CConfiguration::SaveConfiguration( std::string strConfig )
	{
		std::ofstream fFile( strPath + strConfig, std::ofstream::trunc );
		fFile << jsConfiguration.dump( 4 );
		fFile.close( );
	}

	void CConfiguration::DeleteConfiguration( std::string strConfig )
	{
		std::ofstream fFile( strPath + strConfig, std::ofstream::trunc );
		jsConfiguration.clear( );
		fFile.close( );
	}

	CConfiguration cfg;
}
