/// Configuration.cpp

#include "../../Framework.hpp"

namespace Paladin
{
	CConfiguration::CConfiguration( )
	{
		auto wchTemp = new wchar_t[ MAX_PATH ];
		GetModuleFileName( nullptr, wchTemp, MAX_PATH );
		wstrPath = std::wstring( wchTemp ).substr( 0, std::wstring( wchTemp ).find_last_of( XORW( L"/\\" ) ) + 1 ) + XORW( L"Configurations\\" );

		if ( !PathFileExists( ( wstrPath + XORW( L"global.json" ) ).c_str( ) ) )
		{
			// TODO: Missing Global Configuration File
		}

		std::ifstream fFile( wstrPath + XORW( L"global.json" ) );

		if ( !fFile.is_open( ) )
		{
			// TODO: could not open file for reading
		}

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
			LoadConfiguration( string_cast< std::wstring >( jsGlobalConfiguration[ XOR( "Default Configuration" ) ].get_ref< nlohmann::json::string_t & >( ) ).c_str( ) );
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

	void CConfiguration::LoadConfiguration( const wchar_t *wszConfig )
	{
		if ( !PathFileExists( ( wstrPath + wszConfig + XORW( L".json" ) ).c_str( ) ) )
		{
			// TODO: Missing Configuration File
		}

		std::ifstream fFile( wstrPath + wszConfig + XORW( L".json" ) );

		if ( !fFile.is_open( ) )
		{
			// TODO: could not open file for reading
		}

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

	void CConfiguration::SaveConfiguration( const wchar_t *wszConfig ) const
	{
		std::ofstream fFile( wstrPath + wszConfig + XORW( L".json" ), std::ofstream::trunc );
		if ( !fFile.is_open( ) )
		{
			// TODO: could not open file for writing
		}
		fFile << jsConfiguration.dump( 4 );
		fFile.close( );
	}

	void CConfiguration::DeleteConfiguration( const wchar_t *wszConfig )
	{
		if ( string_cast< std::wstring >( jsGlobalConfiguration[ XOR( "Default Configuration" ) ].get_ref< nlohmann::json::string_t & >( ) ) != wszConfig )
		{
			std::ofstream fFile( wstrPath + wszConfig + XORW( L".json" ), std::ofstream::trunc );
			if ( !fFile.is_open( ) )
			{
				// TODO: could not open file for writing
			}
			jsConfiguration.clear( );
			fFile.close( );
		}
		else
		{
			// TODO: Attempted to delete global configuration
		}
	}

	CConfiguration *cfg;
}
