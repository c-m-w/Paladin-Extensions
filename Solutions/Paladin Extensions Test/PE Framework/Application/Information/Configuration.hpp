/// Configuration.hpp

#pragma once

namespace Paladin
{
    class CConfiguration
    {
        std::wstring wstrPath;

    public:
        CConfiguration( );

        /**
         * \brief json file with global configuration information.
         */
        nlohmann::json jsGlobalConfiguration;
        /**
        * \brief json file with current selected configuration information.
        */
        nlohmann::json jsConfiguration;

        /**
         * \brief Loads configuration of name from parameter in local file directory (Extension '.json' is automatically added)
         */
        void LoadConfiguration( std::wstring );
        /**
        * \brief Saves configuration of name from parameter in local file directory and creates a new one if it does not exist. (Extension '.json' is automatically added)
        */
        void SaveConfiguration( std::wstring ) const;
        /**
        * \brief Deletes configuration of name from parameter in local file directory. (Extension '.json' is automatically added)
        */
        void DeleteConfiguration( std::wstring );
    } static *cfg;
}
