#pragma once
#include <nlohmann/json.hpp>
#include "../Framework.hpp"

namespace Paladin
{
#define SPACES_PER_TAB 4

	class CConfiguration;
	extern CConfiguration cfg;

	class CConfiguration
	{
		std::string strPath;

	public:
		nlohmann::json jsGlobalConfiguration;
		nlohmann::json jsConfiguration;

		void LoadConfiguration( std::string strConfig )
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

		void SaveConfiguration( std::string strConfig )
		{
			std::ofstream fFile( strPath + strConfig, std::ofstream::trunc );
			fFile << jsConfiguration.dump( SPACES_PER_TAB );
			fFile.close( );
		}
		CConfiguration( )
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
				LoadConfiguration( jsGlobalConfiguration[ XOR( "Default Configuration" ) ].get_ref< nlohmann::json::string_t&>( ) );
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
	};

	CConfiguration cfg;
}
