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
	byte* PX_API ParseResource( int RESOURCE_ID )
	{
		HMODULE hModule = GetModuleHandle( nullptr );
		HRSRC hResource = FindResource( hModule, MAKEINTRESOURCE( RESOURCE_ID ), MAKEINTRESOURCE( RESOURCE_ID ) );
		HGLOBAL hMemory = LoadResource( hModule, hResource );
		DWORD dwSize = SizeofResource( hModule, hResource );
		LPVOID lpAddress = LockResource( hMemory );

		byte *bytes = new byte[ dwSize ];
		memcpy( bytes, lpAddress, dwSize );
		return bytes;
	}

	void PX_API ParseResources( )
	{
		::Resources::bLogoICO = ParseResource( IDI_ICON1 );
	}

	void PX_API Install( )
	{
		
	}

	void PX_API Rollback( )
	{
		
	}

	void PX_API Uninstall( )
	{
		
	}
}
