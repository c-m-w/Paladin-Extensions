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
            LoadConfiguration( string_cast< std::wstring >( jsGlobalConfiguration[ XOR( "Default Configuration" ) ].get_ref< nlohmann::json::string_t & >( ) ) );
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

    void CConfiguration::LoadConfiguration( std::wstring wstrConfig )
    {
        if ( !PathFileExists( ( wstrPath + wstrConfig + XORW( L".json" ) ).c_str( ) ) )
        {
            // TODO: Missing Configuration File
        }

        std::ifstream fFile( wstrPath + wstrConfig + XORW( L".json" ) );

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

    void CConfiguration::SaveConfiguration( std::wstring wstrConfig ) const
    {
        std::ofstream fFile( wstrPath + wstrConfig + XORW( L".json" ), std::ofstream::trunc );
        if ( !fFile.is_open( ) )
        {
            // TODO: could not open file for writing
        }
        fFile << jsConfiguration.dump( 4 );
        fFile.close( );
    }

    void CConfiguration::DeleteConfiguration( std::wstring wstrConfig )
    {
        if ( string_cast< std::wstring >( jsGlobalConfiguration[ XOR( "Default Configuration" ) ].get_ref< nlohmann::json::string_t & >( ) ) != wstrConfig )
        {
            std::ofstream fFile( wstrPath + wstrConfig + XORW( L".json" ), std::ofstream::trunc );
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
