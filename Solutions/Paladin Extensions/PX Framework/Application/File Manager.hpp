/// File Manager.hpp

#pragma once

namespace PX
{
    class CFileManager: public Tools::SSingleton< CFileManager >
    {
    public:
        // INFO: Contains global information generally used for program initialization
        nlohmann::json jsGlobal;
        // INFO: Contains user-defined information generally used for program customization
        nlohmann::json jsCurrent;
        // INFO: Name of current configuration
        Tools::wcstr_t wszCurrent = static_cast< wchar_t* >( malloc( 32 ) );

        CFileManager( );
        // INFO: Saves json configurations
        void PX_API SaveInformation( );
        // INFO: Changes json configuration to reference desired configuration
        // *return*: false if path does not exist or there was an issue prcoessing the file, true if changed/is same file
        bool PX_API ChangeConfiguration( Tools::wcstr_t );
    };
}
