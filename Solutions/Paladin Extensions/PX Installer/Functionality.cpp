/// Functionality.cpp

#include "PX Precompiled.hpp"
#include "PX Installer.hpp"

namespace Resources
{
	byte_t* bLogoICO;
			
	byte_t* bCursorArrow;
	byte_t* bCursorHand;
	byte_t* bCursorIBeam;
			
	byte_t* bFontsEnvy;
	byte_t* bFontsFontAwesome;
	byte_t* bFontsRoboto;
	byte_t* bFontsRobotoBold;
	byte_t* bFontsTahoma;
	byte_t* bFontsTahomaBold;
			
	byte_t* bGameIconsCSGO;
	byte_t* bGameIconsCSGOSized;
	byte_t* bGameIconsPUBG;
	byte_t* bGameIconsPUBGSized;
	byte_t* bGameIconsRSIX;
	byte_t* bGameIconsRSIXSized;

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
	byte* PX_API ParseResource( int iResourceID )
	{
		HRSRC hResource = FindResource( PX::hinstWin, MAKEINTRESOURCE( iResourceID ), MAKEINTRESOURCE( iResourceID ) );
		HGLOBAL hMemory = LoadResource( PX::hinstWin, hResource );
		DWORD dwSize = SizeofResource( PX::hinstWin, hResource );
		LPVOID lpAddress = LockResource( hMemory );

		bstr_t bData;
		bData.resize( dwSize );
		memcpy( &bData[ 0 ], lpAddress, dwSize );
		return bData.c_str( );
	}

	void PX_API ParseResources( )
	{
		::Resources::bLogoICO = ParseResource( IDI_ICON1 );
		PX::UI::vecTextures;
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
