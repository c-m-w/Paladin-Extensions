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
		bool LoadResources( const Types::str_t& );
	}

	class CConfig: public Tools::ASingleton< CConfig >
	{
	public:
		// INFO: Contains global information generally used for program initialization
		nlohmann::json jsGlobal;
		// INFO: Contains user-defined information generally used for program customization
		nlohmann::json jsCurrent;
		// INFO: Name of current configuration
		Types::wcstr_t wszCurrent = static_cast< wchar_t* >( malloc( 32 ) );

		CConfig( );
		// INFO: Saves json configurations
		void PX_API SaveInformation( );
		// INFO: Changes json configuration to reference desired configuration
		// *return*: false if path does not exist or there was an issue prcoessing the file, true if changed/is same file
		bool PX_API ChangeConfiguration( Types::wcstr_t );
	};

	bool PX_API FileRead( Types::wstr_t wstrPath, Types::wstr_t& wstrData, bool bRelativePath, bool bBase64 = true );
	bool PX_API FileWrite( Types::wstr_t wstrPath, const Types::wstr_t& wstrData, bool bRelativePath, bool bBase64 = true );
}

#if defined PX_USE_NAMESPACES
using namespace PX::Files;
using namespace PX::Files::Resources;
#endif
