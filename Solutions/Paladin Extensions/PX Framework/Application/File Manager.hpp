/// File Manager.hpp

#pragma once

namespace PX::Files
{
	// INFO: Gets directory with specified directories upward
	// PARAM: Levels to escape
	Types::wstr_t PX_API GetExecutablePath( );
	Types::wstr_t PX_API GetExecutableDirectory( );
	Types::wstr_t PX_API GetExecutableName( );
	Types::wstr_t PX_API GetPXDirectory( );
	std::vector< Types::str_t > PX_API GetFilesInDirectory( const Types::str_t& strFolder, const Types::str_t& strExtension = { } );

	namespace Resources
	{
		PX_SDK Types::str_t strLogoICO;

		PX_SDK Types::str_t strCursorArrow;
		PX_SDK Types::str_t strCursorHand;
		PX_SDK Types::str_t strCursorIBeam;

		PX_SDK Types::str_t strFontsEnvy;
		PX_SDK Types::str_t strFontsFontAwesome;
		PX_SDK Types::str_t strFontsRoboto;
		PX_SDK Types::str_t strFontsRobotoBold;
		PX_SDK Types::str_t strFontsTahoma;
		PX_SDK Types::str_t strFontsTahomaBold;

		PX_SDK Types::str_t strGameIconsCSGO;
		PX_SDK Types::str_t strGameIconsPUBG;
		PX_SDK Types::str_t strGameIconsRSIX;

		PX_SDK Types::str_t strGameIconsCSGOSized;
		PX_SDK Types::str_t strGameIconsPUBGSized;
		PX_SDK Types::str_t strGameIconsRSIXSized;

		// INFO: Verifies vital resources have not been modified, then loads them
		// PARAM: Hash of resources
		bool LoadResources( const Types::str_t & );
	}

	class CConfig: public Tools::ASingleton< CConfig >
	{
		const Types::wstr_t wstrExtension;
		const Types::wstr_t wstrExtensionFolderNames[ 3 ];
		const Types::wstr_t wstrGlobalFileName;
		bool bLoadedGlobalConfig = false;
		void* pConfig = nullptr;
		std::size_t zConfig = 0u;
		int iExtension = 0;

		struct global_config_t
		{
			Types::key_t kMenuKey = VK_HOME;
			Types::str_t strDefaultConfiguration = PX_XOR( "none" );
			bool bSimplifyMenu = false;
			bool bNotifyUponInjection = false;
			bool bNotifyUponConfigurationChange = false;
			bool bDisplayTooltips = false;
			bool bDisplayWatermark = false;
		} global;

		void PX_API LoadGlobalConfig( );
		void PX_API CreateDefaultConfig( );

	public:
		constexpr static std::size_t MAX_FILE_NAME_SIZE = 32;

		CConfig( );

		void PX_API SetMenuKey( const Types::key_t kNewKey );
		void PX_API SetDefaultConfiguration( const Types::str_t& strNewDefaultConfiguration );
		Types::key_t PX_API GetMenuKey( );
		const Types::str_t& PX_API GetDefaultConfiguration( );

		void PX_API SetContext( void* pStructure, std::size_t zConfigStructure, int iExtensionID );
		PX_RET Types::wstr_t PX_API GetConfigDirectory( );
		PX_RET std::vector< Types::str_t > GetConfigs( );
		void PX_API SaveGlobalConfiguration( );
		void PX_API SaveConfiguration( Types::wcstr_t wszFileName );
		bool PX_API LoadDefaultConfiguration( );
		bool PX_API LoadConfiguration( Types::wcstr_t wszFileName );
		void PX_API RemoveConfiguration( Types::wcstr_t wszFileName );
	};

	bool PX_API FileRead( Types::wstr_t wstrPath, Types::wstr_t &wstrData, bool bRelativePath, bool bBase64 = true );
	bool PX_API FileWrite( Types::wstr_t wstrPath, const Types::wstr_t &wstrData, bool bRelativePath, bool bBase64 = true );
}

#if defined PX_USE_NAMESPACES
using namespace PX::Files;
using namespace PX::Files::Resources;
#endif
