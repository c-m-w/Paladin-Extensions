/// File Manager.cpp

#include "../PX Framework.hpp"

namespace PX
{
    CFileManager::CFileManager( )
    {
        std::ifstream ifGlobalConfiguration( Tools::GetDirectory( PX_DEPENDENCIES_ESCAPE ) + LR"(\Configurations\global.json)" );
        if ( ifGlobalConfiguration.is_open( ) )
            ifGlobalConfiguration >> jsGlobal;
        else
            throw std::exception( "Failed to open global.json for reading" );

        wszCurrent = &Tools::string_cast< std::wstring >( jsGlobal[ "Default Configuration" ].get_ref< std::string& >( ) )[ 0 ];

        ChangeConfiguration( wszCurrent );
    }

    void PX_API CFileManager::SaveInformation( )
    {
        std::ofstream ofGlobalConfiguration( Tools::GetDirectory( PX_DEPENDENCIES_ESCAPE ) + LR"(\Configurations\global.json)" );
        if ( ofGlobalConfiguration.is_open( ) )
            ofGlobalConfiguration << jsGlobal.dump( 4 );
        else
            throw std::exception( "Failed to open global.json for writing" );

        std::ofstream ofCurrentConfiguration( Tools::GetDirectory( PX_DEPENDENCIES_ESCAPE ) + LR"(\Configurations\global\)" + wszCurrent + L".json)" );
        if ( ofCurrentConfiguration.is_open( ) )
            ofCurrentConfiguration << jsGlobal.dump( 4 );
        else
            throw std::exception( ( std::string( "Failed to open " ) + Tools::string_cast< std::string >( wszCurrent ) + ".json for writing" ).c_str( ) );
    }

    bool PX_API CFileManager::ChangeConfiguration( Tools::wcstr_t wszConfig )
    {
        if ( wszCurrent == wszConfig )
            return true;

        if ( PathFileExistsW( ( Tools::GetDirectory( PX_DEPENDENCIES_ESCAPE ) + LR"(\Configurations\global\)" + wszConfig + L".json)" ).c_str( ) ) )
        {
            std::ifstream ifNewConfiguration( Tools::GetDirectory( PX_DEPENDENCIES_ESCAPE ) + LR"(\Configurations\global\)" + wszConfig + L".json)" );
            if ( ifNewConfiguration.is_open( ) )
            {
                try
                {
                    ifNewConfiguration >> jsGlobal;
                }
                catch ( nlohmann::detail::parse_error& )
                {
                    return false; // Formatting Errors
                }
                catch ( nlohmann::detail::type_error& )
                {
                    return false; // Missing Errors
                }
            }
            else
                throw std::exception( ( std::string( "Failed to open " ) + Tools::string_cast< std::string >( wszConfig ) + ".json for writing" ).c_str( ) );

            wszCurrent = wszConfig;
            return true;
        }
        return false;
    }
}
