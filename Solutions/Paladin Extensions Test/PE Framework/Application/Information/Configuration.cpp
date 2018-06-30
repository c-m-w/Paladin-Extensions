/// Configuration.cpp

#include "../../Framework.hpp"

namespace Paladin
{
    CConfiguration::CConfiguration( )
    {
        wstrPath = GetDirectory( M_DEPENDENCIES ) + M_WXOR( L"Configurations\\" );

        if ( !PathFileExists( ( wstrPath + M_WXOR( L"global.json" ) ).c_str( ) ) )
        {
            // TODO: Missing Global Configuration File
        }

        std::ifstream fFile( wstrPath + M_WXOR( L"global.json" ) );

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
            LoadConfiguration( string_cast< std::wstring >( jsGlobalConfiguration[ M_XOR( "Default Configuration" ) ].get_ref< nlohmann::json::string_t & >( ) ) );
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
        if ( !PathFileExists( ( wstrPath + wstrConfig + M_WXOR( L".json" ) ).c_str( ) ) )
        {
            // TODO: Missing Configuration File
        }

        std::ifstream fFile( wstrPath + wstrConfig + M_WXOR( L".json" ) );

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
        std::ofstream fFile( wstrPath + wstrConfig + M_WXOR( L".json" ), std::ofstream::trunc );
        if ( !fFile.is_open( ) )
        {
            // TODO: could not open file for writing
        }
        fFile << jsConfiguration.dump( 4 );
        fFile.close( );
    }

    void CConfiguration::DeleteConfiguration( std::wstring wstrConfig )
    {
        if ( string_cast< std::wstring >( jsGlobalConfiguration[ M_XOR( "Default Configuration" ) ].get_ref< nlohmann::json::string_t & >( ) ) != wstrConfig )
        {
            std::ofstream fFile( wstrPath + wstrConfig + M_WXOR( L".json" ), std::ofstream::trunc );
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
}