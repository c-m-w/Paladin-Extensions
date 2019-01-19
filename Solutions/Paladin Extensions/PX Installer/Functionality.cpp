/// Functionality.cpp

#include "PX Precompiled.hpp"
#include "PX Installer.hpp"

namespace Resources
{
	bstr_t bstrLauncherEXE;

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
		::Resources::bstrLauncherEXE = ParseResource( EXE_LAUNCHER );

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

		::Resources::bstrGameIconsCSGO = ParseResource( GAME_CSGO );
		::Resources::bstrGameIconsCSGOSized = ParseResource( GAME_CSGO_SIZED );
		::Resources::bstrGameIconsPUBG = ParseResource( GAME_PUBG );
		::Resources::bstrGameIconsPUBGSized = ParseResource( GAME_PUBG_SIZED );
		::Resources::bstrGameIconsRSIX = ParseResource( GAME_RSIX );
		::Resources::bstrGameIconsRSIXSized = ParseResource( GAME_RSIX_SIZED );
		::Resources::bstrGameIconsRSIX = ParseResource( GAME_RUST );
		::Resources::bstrGameIconsRSIXSized = ParseResource( GAME_RUST_SIZED );
	}

	void PX_API Install( )
	{
		auto fnCreateFile = [ ]( auto szPath, auto bstrData )
		{
			std::ofstream ofsFile( strInstallDirectory + szPath, std::ios::out | std::ios::binary | std::ios::trunc );
			ofsFile << bstrData.c_str( );
			ofsFile.close( );
		};

		{
			if ( bCancelInstallation ) return;
				// write to file Launcher.exe
			fnCreateFile( PX_XOR( "\\PX Launcher.exe" ), ::Resources::bstrLauncherEXE );
			uProgress = 1u;
		}
		{
			if ( bCancelInstallation ) return;
				// write to file all logos
			fnCreateFile( PX_XOR( "\\PX Logo.ico" ), ::Resources::bstrLogoICO );
			fnCreateFile( PX_XOR( "\\PX Logo.png" ), ::Resources::bstrLogoPNG );
			fnCreateFile( PX_XOR( "\\PX Loading.png" ), ::Resources::bstrLogoLoading );
			uProgress = 2u;
		}
		{
			if ( bCancelInstallation ) return;
				// write to file all cursor
			fnCreateFile( PX_XOR( "\\Cursor\\Arrow.png" ), ::Resources::bstrCursorArrow );
			fnCreateFile( PX_XOR( "\\Cursor\\Hand.png" ), ::Resources::bstrCursorHand );
			fnCreateFile( PX_XOR( "\\Cursor\\I Beam.png" ), ::Resources::bstrCursorIBeam );
			uProgress = 3u;
		}
		{
			if ( bCancelInstallation ) return;
				// write to file all fonts
			fnCreateFile( PX_XOR( "\\Fonts\\csgo_icons.ttf" ), ::Resources::bstrCursorArrow );
			fnCreateFile( PX_XOR( "\\Fonts\\Envy.ttf" ), ::Resources::bstrCursorHand );
			fnCreateFile( PX_XOR( "\\Fonts\\FontAwesome.ttf" ), ::Resources::bstrCursorIBeam );
			fnCreateFile( PX_XOR( "\\Fonts\\Roboto.ttf" ), ::Resources::bstrCursorArrow );
			fnCreateFile( PX_XOR( "\\Fonts\\RobotoBold.ttf" ), ::Resources::bstrCursorHand );
			fnCreateFile( PX_XOR( "\\Fonts\\Tahoma.ttf" ), ::Resources::bstrCursorIBeam );
			fnCreateFile( PX_XOR( "\\Fonts\\TahomaBold.ttf" ), ::Resources::bstrCursorArrow );
			uProgress = 4u;
		}
		{
			if ( bCancelInstallation ) return;
				// write to file all game icons
			fnCreateFile( PX_XOR( "\\Game Icons\\CSGO.png" ), ::Resources::bstrCursorArrow );
			fnCreateFile( PX_XOR( "\\Game Icons\\PUBG.png" ), ::Resources::bstrCursorHand );
			fnCreateFile( PX_XOR( "\\Game Icons\\RSIX.png" ), ::Resources::bstrCursorIBeam );
			fnCreateFile( PX_XOR( "\\Game Icons\\RUST.png" ), ::Resources::bstrCursorIBeam );
			fnCreateFile( PX_XOR( "\\Game Icons\\CSGO Sized.png" ), ::Resources::bstrCursorArrow );
			fnCreateFile( PX_XOR( "\\Game Icons\\PUBG Sized.png" ), ::Resources::bstrCursorHand );
			fnCreateFile( PX_XOR( "\\Game Icons\\RSIX Sized.png" ), ::Resources::bstrCursorIBeam );
			fnCreateFile( PX_XOR( "\\Game Icons\\RUST Sized.png" ), ::Resources::bstrCursorIBeam );
			uProgress = 5u;
		}
		{
			if ( bCancelInstallation ) return;
			// write to file configs based on bExtensionAccess[ PX_EXTENSIONS_... ]
			Wait< std::chrono::seconds >( 2 );
			uProgress = 6u;
		}
	}

	// https://stackoverflow.com/questions/734717/how-to-delete-a-folder-in-c
	int DeleteDirectory( const std::string &refcstrRootDirectory,
						 bool              bDeleteSubdirectories = true )
	{
		bool            bSubdirectory = false;       // Flag, indicating whether
													 // subdirectories have been found
		HANDLE          hFile;                       // Handle to directory
		std::string     strFilePath;                 // Filepath
		std::string     strPattern;                  // Pattern
		WIN32_FIND_DATAA FileInformation;             // File information


		strPattern = refcstrRootDirectory + "\\*.*";
		hFile = ::FindFirstFileA( strPattern.c_str( ), &FileInformation );
		if ( hFile != INVALID_HANDLE_VALUE )
		{
			do
			{
				if ( FileInformation.cFileName[ 0 ] != '.' )
				{
					strFilePath.erase( );
					strFilePath = refcstrRootDirectory + "\\" + FileInformation.cFileName;

					if ( FileInformation.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
					{
						if ( bDeleteSubdirectories )
						{
						  // Delete subdirectory
							int iRC = DeleteDirectory( strFilePath, bDeleteSubdirectories );
							if ( iRC )
								return iRC;
						}
						else
							bSubdirectory = true;
					}
					else
					{
					  // Set file attributes
						if ( ::SetFileAttributesA( strFilePath.c_str( ),
												  FILE_ATTRIBUTE_NORMAL ) == FALSE )
							return ::GetLastError( );

						  // Delete file
						if ( ::DeleteFileA( strFilePath.c_str( ) ) == FALSE )
							return ::GetLastError( );
					}
				}
			} while ( ::FindNextFileA( hFile, &FileInformation ) == TRUE );

			// Close handle
			::FindClose( hFile );

			DWORD dwError = ::GetLastError( );
			if ( dwError != ERROR_NO_MORE_FILES )
				return dwError;
			else
			{
				if ( !bSubdirectory )
				{
				  // Set directory attributes
					if ( ::SetFileAttributesA( refcstrRootDirectory.c_str( ),
											  FILE_ATTRIBUTE_NORMAL ) == FALSE )
						return ::GetLastError( );

					  // Delete directory
					if ( ::RemoveDirectoryA( refcstrRootDirectory.c_str( ) ) == FALSE )
						return ::GetLastError( );
				}
			}
		}

		return 0;
	}

	void PX_API Rollback( )
	{
		//bCancelInstallation = true;
		if ( strInstallDirectory.empty( ) )
			return;
		if ( DeleteDirectory( strInstallDirectory ) || DeleteDirectory( string_cast< std::string >( PX_APPDATA.substr( 0, PX_APPDATA.length( ) - 1 ) ) ) )
			Popup( EMBType::FATAL_ERROR, PX_XOR( L"Failed to rollback installation. Contact support for help in rollback." ) );
		//switch ( uProgress )
		//{
		//	case 6u:
		//	{
		//		// delete configs
		//	}
		//	case 5u:
		//	case 4u:
		//	case 3u:
		//	case 2u:
		//	{
		//		// delete resources
		//	}
		//	case 1u:
		//	{
		//		// delete exe
		//	}
		//	default: ;
		//}
	}

	void PX_API Uninstall( )
	{
		if ( strInstallDirectory.empty( ) )
			return;
		if ( DeleteDirectory( strInstallDirectory ) || DeleteDirectory( string_cast< std::string >( PX_APPDATA.substr( 0, PX_APPDATA.length( ) - 1 ) ) ) )
			Popup( EMBType::FATAL_ERROR, PX_XOR( L"Failed to uninstall. Contact support for help in uninstallation." ) );
		// delete Paladin Extensions data from appdata/PX/data.px
		// delete appdata/PX folder
	}
}
