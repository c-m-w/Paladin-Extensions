/// Functionality.cpp

#include "PX Precompiled.hpp"
#include "PX Installer.hpp"

namespace Resources
{
	bstr_t bstrLogoICO;
	bstr_t bstrLogoPNG;
	bstr_t bstrLogoLoading;

	bstr_t bstrCursorArrow;
	bstr_t bstrCursorHand;
	bstr_t bstrCursorIBeam;

	bstr_t bstrFontsEnvy;
	bstr_t bstrFontsFontAwesome;
	bstr_t bstrFontsRoboto;
	bstr_t bstrFontsRobotoBold;
	bstr_t bstrFontsTahoma;
	bstr_t bstrFontsTahomaBold;
	bstr_t bstrFontsCSGO;
	bstr_t bstrFontsCSGO2;

	bstr_t bstrGameIconsCSGO;
	bstr_t bstrGameIconsCSGOSized;
	bstr_t bstrGameIconsPUBG;
	bstr_t bstrGameIconsPUBGSized;
	bstr_t bstrGameIconsRSIX;
	bstr_t bstrGameIconsRSIXSized;

	namespace ExtensionData
	{
		namespace CSGO
		{
			namespace Resources
			{ }

			namespace Configurations
			{ }
		}

		namespace PUBG
		{
			namespace Resources
			{ }

			namespace Configurations
			{ }
		}

		namespace RSIX
		{
			namespace Resources
			{ }

			namespace Configurations
			{ }
		}
	}
}

namespace PX::Functionality
{
	bstr_t PX_API ParseResource( int iResourceID )
	{
		HRSRC hResource = FindResource( PX::hinstWin, MAKEINTRESOURCE( iResourceID ), MAKEINTRESOURCE( iResourceID ) );
		if ( !hResource )
			return { };
		HGLOBAL hMemory = LoadResource( PX::hinstWin, hResource );
		if ( !hMemory )
			return { };
		DWORD dwSize = SizeofResource( PX::hinstWin, hResource );
		LPVOID lpAddress = LockResource( hMemory );

		bstr_t bData;
		bData.resize( dwSize );
		memcpy( &bData[ 0 ], lpAddress, dwSize );
		return bData += '\0'_b;
	}

	void PX_API ParseResources( )
	{
		::Resources::bstrLogoICO = ParseResource( LOGO_ICO );
		::Resources::bstrLogoPNG = ParseResource( LOGO_PNG );
		::Resources::bstrLogoLoading = ParseResource( LOGO_LOADING );

		::Resources::bstrCursorArrow = ParseResource( CUR_ARROW );
		::Resources::bstrCursorHand = ParseResource( CUR_HAND );
		::Resources::bstrCursorIBeam = ParseResource( CUR_IBEAM );

		::Resources::bstrFontsEnvy = ParseResource( FNT_ENVY );
		::Resources::bstrFontsFontAwesome = ParseResource( FONT_FONT_AWESOME );
		::Resources::bstrFontsRoboto = ParseResource( FONT_ROBOT );
		::Resources::bstrFontsRobotoBold = ParseResource( FONT_ROBOTO_BOLD );
		::Resources::bstrFontsTahoma = ParseResource( FNT_TAHOMA );
		::Resources::bstrFontsTahomaBold = ParseResource( FONT_TAHOMA_BOLD );
		::Resources::bstrFontsCSGO = ParseResource( FONT_CSGO );
		::Resources::bstrFontsCSGO2 = ParseResource( FONT_CSGO2 );

		::Resources::bstrGameIconsCSGO = ParseResource( GAME_CSGO );
		::Resources::bstrGameIconsCSGOSized = ParseResource( GAME_CSGO_SIZED );
		::Resources::bstrGameIconsPUBG = ParseResource( GAME_PUBG );
		::Resources::bstrGameIconsPUBGSized = ParseResource( GAME_PUBG_SIZED );
		::Resources::bstrGameIconsRSIX = ParseResource( GAME_RSIX );
		::Resources::bstrGameIconsRSIXSized = ParseResource( GAME_RSIX_SIZED );
	}

	void PX_API Install( )
	{
		if ( !bCancelInstallation )
		{ }
		uProgress = 1u;
		if ( !bCancelInstallation )
		{ }
	}

	void PX_API Rollback( )
	{
		bCancelInstallation = true;
		switch ( uProgress )
		{
			case 1u:
			{ }
			case 2u:
			{ }
			case 3u:
			{ }
			case 4u:
			{ }
			case 5u:
			{ }
			default:
			{
				return;
			}
		}
	}

	void PX_API Uninstall( )
	{ }
}
