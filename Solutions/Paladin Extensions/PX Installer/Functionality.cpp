/// Functionality.cpp

#include "PX Precompiled.hpp"
#include "PX Installer.hpp"

namespace Resources
{
	bstr_t bLogoICO;
	bstr_t bLogoPNG;
	bstr_t bLogoLoading;
	
	bstr_t bCursorArrow;
	bstr_t bCursorHand;
	bstr_t bCursorIBeam;
	
	bstr_t bFontsEnvy;
	bstr_t bFontsFontAwesome;
	bstr_t bFontsRoboto;
	bstr_t bFontsRobotoBold;
	bstr_t bFontsTahoma;
	bstr_t bFontsTahomaBold;
	
	bstr_t bGameIconsCSGO;
	bstr_t bGameIconsCSGOSized;
	bstr_t bGameIconsPUBG;
	bstr_t bGameIconsPUBGSized;
	bstr_t bGameIconsRSIX;
	bstr_t bGameIconsRSIXSized;

	namespace ExtensionData
	{
		namespace CSGO
		{
			namespace Resources
			{
				
			}

			namespace Configurations
			{
				
			}
		}

		namespace PUBG
		{
			namespace Resources
			{

			}

			namespace Configurations
			{

			}
		}

		namespace RSIX
		{
			namespace Resources
			{

			}

			namespace Configurations
			{

			}
		}
	}
}

namespace PX::Functionality
{
	bstr_t PX_API ParseResource( int iResourceID )
	{
		HRSRC hResource = FindResource( PX::hinstWin, MAKEINTRESOURCE( iResourceID ), MAKEINTRESOURCE( iResourceID ) );
		HGLOBAL hMemory = LoadResource( PX::hinstWin, hResource );
		DWORD dwSize = SizeofResource( PX::hinstWin, hResource );
		LPVOID lpAddress = LockResource( hMemory );

		bstr_t bData;
		bData.resize( dwSize );
		memcpy( &bData[ 0 ], lpAddress, dwSize );
		return bData += '\0'_b;
	}

	void PX_API ParseResources( )
	{
		::Resources::bLogoICO = ParseResource( LOGO_ICO );
		::Resources::bLogoPNG = ParseResource( LOGO_PNG );
		::Resources::bLogoLoading = ParseResource( LOGO_LOADING );

		::Resources::bCursorArrow = ParseResource( CUR_ARROW );
		::Resources::bCursorHand = ParseResource( CUR_HAND );
		::Resources::bCursorIBeam = ParseResource( CUR_IBEAM );

		/*::Resources::bFontsEnvy = ParseResource( );
		::Resources::bFontsFontAwesome = ParseResource( );
		::Resources::bFontsRoboto = ParseResource( );
		::Resources::bFontsRobotoBold = ParseResource( );
		::Resources::bFontsTahoma = ParseResource( );
		::Resources::bFontsTahomaBold = ParseResource( );

		::Resources::bGameIconsCSGO = ParseResource( );
		::Resources::bGameIconsCSGOSized = ParseResource( );
		::Resources::bGameIconsPUBG = ParseResource( );
		::Resources::bGameIconsPUBGSized = ParseResource( );
		::Resources::bGameIconsRSIX = ParseResource( );
		::Resources::bGameIconsRSIXSized = ParseResource( );*/
	}

	void PX_API Install( )
	{
		if ( !bCancelInstallation )
		{
			
		}
		uProgress = 1u;
		if ( !bCancelInstallation )
		{
			
		}
	}

	void PX_API Rollback( )
	{
		bCancelInstallation = true;
		switch ( uProgress )
		{
			case 1u:
			{
				
			}
			case 2u:
			{
				
			}
			case 3u:
			{
				
			}
			case 4u:
			{
				
			}
			case 5u:
			{
				
			}
			default: 
			{
				return;
			}
		}
	}

	void PX_API Uninstall( )
	{
		
	}
}
