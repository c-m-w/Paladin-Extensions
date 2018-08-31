/// File Manager.hpp

#pragma once

namespace PX::Files
{
	// INFO: Gets directory with specified directories upward
	// PARAM: Levels to escape
	std::wstring PX_API GetExecutablePath( );
	std::wstring PX_API GetExecutableDirectory( );
	std::wstring PX_API GetExecutableName( );
	std::wstring PX_API GetPXDirectory( );

	namespace Resources
	{
		PX_SDK std::string strLogoICO;
		PX_SDK std::string strLogoPNG;

		PX_SDK std::string strCursorArrow;
		PX_SDK std::string strCursorHand;
		PX_SDK std::string strCursorIBeam;

		PX_SDK std::string strFontsEnvy;
		PX_SDK std::string strFontsFontAwesome;
		PX_SDK std::string strFontsRoboto;
		PX_SDK std::string strFontsRobotoBold;
		PX_SDK std::string strFontsTahoma;
		PX_SDK std::string strFontsTahomaBold;

		PX_SDK std::string strGameIconsCSGO;
		PX_SDK std::string strGameIconsPUBG;
		PX_SDK std::string strGameIconsRSIX;

		PX_SDK std::string strGameIconsCSGOSized;
		PX_SDK std::string strGameIconsPUBGSized;
		PX_SDK std::string strGameIconsRSIXSized;

		// INFO: Verifies vital resources have not been modified, then loads them
		// PARAM: Hash of resources
		bool LoadResources( const std::string& );
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

	bool PX_API FileRead( std::wstring wstrPath, std::wstring& wstrData, bool bRelativePath, bool bBase64 = true );
	bool PX_API FileWrite( std::wstring wstrPath, const std::wstring& wstrData, bool bRelativePath, bool bBase64 = true );
}

#if defined PX_USE_NAMESPACES
using namespace PX::Files;
using namespace PX::Files::Resources;
#endif
