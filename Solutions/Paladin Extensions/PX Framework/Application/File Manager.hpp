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
		inline const static std::wstring wstrExtension = PX_XOR( L".pxcfg" );
		inline const static std::wstring wstrExtensionFolderNames[ ] { PX_XOR( L"CSGO\\Configurations\\" ), PX_XOR( L"PUBG\\Configurations\\" ), PX_XOR( L"RSIX\\Configurations\\" ) };
		inline const static std::wstring wstrGlobalFileName = PX_XOR( L"global" );
	public:
		constexpr static std::size_t MAX_FILE_NAME_SIZE = 32;

		CConfig( ) = default;

		PX_RET static std::wstring PX_API GetConfigDirectory( int iExtension );
		void PX_API SaveConfiguration( int iExtensionID, Types::wcstr_t wszFileName, void* pConfigStructure, std::size_t zConfigStructureSize );
		bool PX_API LoadDefaultConfiguration( int iExtensionID, void* pConfigStructure, std::size_t zConfigStructureSize );
		void PX_API SetDefaultConfiguration( int iExtensionID, Types::wcstr_t wszFileName );
		bool PX_API LoadConfiguration( int iExtensionID, Types::wcstr_t wszFileName, void* pConfigStructure, std::size_t zConfigStructureSize );
	};

	bool PX_API FileRead( Types::wstr_t wstrPath, Types::wstr_t& wstrData, bool bRelativePath, bool bBase64 = true );
	bool PX_API FileWrite( Types::wstr_t wstrPath, const Types::wstr_t& wstrData, bool bRelativePath, bool bBase64 = true );
}

#if defined PX_USE_NAMESPACES
using namespace PX::Files;
using namespace PX::Files::Resources;
#endif
