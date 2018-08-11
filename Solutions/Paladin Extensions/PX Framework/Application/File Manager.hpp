/// File Manager.hpp

#pragma once

namespace PX::Files
{
	// INFO: Gets directory with specified directories upward
	// PARAM: Levels to escape
	std::wstring PX_API GetDirectory( unsigned = PX_DEPENDENCIES_ESCAPE );

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

		// INFO: Verifies vital resources have not been modified, then loads them
		// PARAM: Hash of resources
		bool LoadResources( const std::string& );
	}

	class CConfig: public ASingleton< CConfig >
	{
	public:
		// INFO: Contains global information generally used for program initialization
		nlohmann::json jsGlobal;
		// INFO: Contains user-defined information generally used for program customization
		nlohmann::json jsCurrent;
		// INFO: Name of current configuration
		wcstr_t wszCurrent = static_cast< wchar_t* >( malloc( 32 ) );

		CConfig( );
		// INFO: Saves json configurations
		void PX_API SaveInformation( );
		// INFO: Changes json configuration to reference desired configuration
		// *return*: false if path does not exist or there was an issue prcoessing the file, true if changed/is same file
		bool PX_API ChangeConfiguration( wcstr_t );
	};

	bool PX_API FileRead( std::wstring wstrPath, std::string& strData, bool bRelativePath, bool bBase64 = true );
	bool PX_API FileWrite( std::wstring wstrPath, const std::wstring& wstrData, bool bRelativePath, bool bBase64 = true );
}
