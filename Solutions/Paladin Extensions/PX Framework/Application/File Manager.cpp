/// File Manager.cpp

#include "PX Precompiled.hpp"
#define PX_USE_NAMESPACES
#include "../PX Framework.hpp"

namespace PX::Files
{
	wstr_t GetExecutablePath( )
	{
		wstr_t wstrDirectory;
		wstrDirectory.resize( MAX_PATH );
		GetModuleFileName( nullptr, &wstrDirectory[ 0 ], MAX_PATH );

		return wstrDirectory;
	}

	wstr_t PX_API GetExecutableDirectory( )
	{
		wstr_t wstrDirectory;
		wstrDirectory.resize( MAX_PATH );
		GetModuleFileName( nullptr, &wstrDirectory[ 0 ], MAX_PATH );

		wstrDirectory = wstrDirectory.substr( 0, wstrDirectory.find_last_of( L'\\' ) );

		return wstrDirectory + L'\\';
	}

	wstr_t PX_API GetExecutableName( )
	{
		wstr_t wstrDirectory;
		wstrDirectory.resize( MAX_PATH );
		GetModuleFileName( nullptr, &wstrDirectory[ 0 ], MAX_PATH );

		return wstrDirectory.substr( wstrDirectory.find_last_of( L'\\' ) + 1, wstrDirectory.length( ) );
	}

	wstr_t GetPXDirectory( )
	{
		static wstr_t wstrInstallDirectory;
		if ( wstrInstallDirectory.empty( ) )
		{
			if ( !FileRead( PX_APPDATA + PX_XOR( L"data.px" ), wstrInstallDirectory, false ) )
				return { };
			for ( auto u = 0u; u <= PX_DEPENDENCIES_ESCAPE; u++ )
				wstrInstallDirectory = wstrInstallDirectory.substr( 0, wstrInstallDirectory.find_last_of( L'\\' ) );
			wstrInstallDirectory += L'\\';
		}

		return wstrInstallDirectory;
	}

	namespace Resources
	{
		// todo: shouldn't have a parameter, should be hash from server
		bool LoadResources( const str_t& strHash )
		{
			wstr_t wstrPath = GetPXDirectory( ) + PX_XOR( LR"(Resources\)" );

			bool bFilesExist = std::filesystem::exists( ( wstrPath + PX_XOR( LR"(PX Logo.ico)" ) ).c_str( ) )

				&& std::filesystem::exists( ( wstrPath + PX_XOR( LR"(Cursor\Arrow.png)" ) ).c_str( ) )
				&& std::filesystem::exists( ( wstrPath + PX_XOR( LR"(Cursor\Hand.png)" ) ).c_str( ) )
				&& std::filesystem::exists( ( wstrPath + PX_XOR( LR"(Cursor\I Beam.png)" ) ).c_str( ) )

				//& std::filesystem::exists( ( wstrPath + PX_XOR( LR"(Fonts\Envy.ttf)" ) ).c_str( ) )
				//& std::filesystem::exists( ( wstrPath + PX_XOR( LR"(Fonts\Font Awesome.ttf)" ) ).c_str( ) )
				//& std::filesystem::exists( ( wstrPath + PX_XOR( LR"(Fonts\Roboto.ttf)" ) ).c_str( ) )
				//& std::filesystem::exists( ( wstrPath + PX_XOR( LR"(Fonts\Roboto Bold.ttf)" ) ).c_str( ) )
				//& std::filesystem::exists( ( wstrPath + PX_XOR( LR"(Fonts\Tahoma.ttf)" ) ).c_str( ) )
				//& std::filesystem::exists( ( wstrPath + PX_XOR( LR"(Fonts\Tahoma Bold.ttf)" ) ).c_str( ) )

				&& std::filesystem::exists( ( wstrPath + PX_XOR( LR"(Game Icons\CSGO.png)" ) ).c_str( ) )
				&& std::filesystem::exists( ( wstrPath + PX_XOR( LR"(Game Icons\PUBG.png)" ) ).c_str( ) )
				&& std::filesystem::exists( ( wstrPath + PX_XOR( LR"(Game Icons\RSIX.png)" ) ).c_str( ) )

				&& std::filesystem::exists( ( wstrPath + PX_XOR( LR"(Game Icons\CSGO Sized.png)" ) ).c_str( ) )
				&& std::filesystem::exists( ( wstrPath + PX_XOR( LR"(Game Icons\PUBG Sized.png)" ) ).c_str( ) )
				&& std::filesystem::exists( ( wstrPath + PX_XOR( LR"(Game Icons\RSIX Sized.png)" ) ).c_str( ) );

			if ( !bFilesExist )
				return false;

			const auto fnGetFileData = [ ]( wcstr_t szPathToFile ) -> str_t
			{
				auto pResource = _wfopen( szPathToFile, PX_XOR( L"r" ) );
				px_assert( pResource );

				fseek( pResource, 0, SEEK_END );
				const auto lSize = ftell( pResource );
				rewind( pResource );

				str_t strData;
				strData.resize( lSize );
				fread( &strData[ 0 ], 1, lSize, pResource );

				fclose( pResource );
				return strData;
			};

			strLogoICO = fnGetFileData( ( wstrPath + PX_XOR( LR"(PX Logo.ico)" ) ).c_str( ) );

			strCursorArrow = fnGetFileData( ( wstrPath + PX_XOR( LR"(Cursor\Arrow.png)" ) ).c_str( ) );
			strCursorHand = fnGetFileData( ( wstrPath + PX_XOR( LR"(Cursor\Hand.png)" ) ).c_str( ) );
			strCursorIBeam = fnGetFileData( ( wstrPath + PX_XOR( LR"(Cursor\I Beam.png)" ) ).c_str( ) );

			//strFontsEnvy = fnGetFileData( ( wstrPath + PX_XOR( LR"(Fonts\Envy.ttf)" ) ).c_str( ) );
			//strFontsFontAwesome = fnGetFileData( ( wstrPath + PX_XOR( LR"(Fonts\Font Awesome.ttf)" ) ).c_str( ) );
			//strFontsRoboto = fnGetFileData( ( wstrPath + PX_XOR( LR"(Fonts\Roboto.ttf)" ) ).c_str( ) );
			//strFontsRobotoBold = fnGetFileData( ( wstrPath + PX_XOR( LR"(Fonts\Roboto Bold.ttf)" ) ).c_str( ) );
			//strFontsTahoma = fnGetFileData( ( wstrPath + PX_XOR( LR"(Fonts\Tahoma.ttf)" ) ).c_str( ) );
			//strFontsTahomaBold = fnGetFileData( ( wstrPath + PX_XOR( LR"(Fonts\Tahoma Bold.ttf)" ) ).c_str( ) );

			strGameIconsCSGO = fnGetFileData( ( wstrPath + PX_XOR( LR"(Game Icons\CSGO.png)" ) ).c_str( ) );
			strGameIconsPUBG = fnGetFileData( ( wstrPath + PX_XOR( LR"(Game Icons\PUBG.png)" ) ).c_str( ) );
			strGameIconsRSIX = fnGetFileData( ( wstrPath + PX_XOR( LR"(Game Icons\RSIX.png)" ) ).c_str( ) );

			strGameIconsPUBGSized = fnGetFileData( ( wstrPath + PX_XOR( LR"(Game Icons\CSGO Sized.png)" ) ).c_str( ) );
			strGameIconsCSGOSized = fnGetFileData( ( wstrPath + PX_XOR( LR"(Game Icons\PUBG Sized.png)" ) ).c_str( ) );
			strGameIconsPUBGSized = fnGetFileData( ( wstrPath + PX_XOR( LR"(Game Icons\RSIX Sized.png)" ) ).c_str( ) );

			auto strResourcesHash = GenerateHash( strLogoICO )

				+ GenerateHash( strCursorArrow )
				+ GenerateHash( strCursorHand )
				+ GenerateHash( strCursorIBeam )

				//+ GenerateHash( strFontsEnvy )
				//+ GenerateHash( strFontsFontAwesome )
				//+ GenerateHash( strFontsRoboto )
				//+ GenerateHash( strFontsRobotoBold )
				//+ GenerateHash( strFontsTahoma )
				//+ GenerateHash( strFontsTahomaBold )

				+ GenerateHash( strGameIconsCSGO )
				+ GenerateHash( strGameIconsPUBG )
				+ GenerateHash( strGameIconsRSIX )
			
				+ GenerateHash( strGameIconsCSGOSized )
				+ GenerateHash( strGameIconsPUBGSized )
				+ GenerateHash( strGameIconsRSIXSized );

			return true;
			//return strHash == strResourcesHash;
		}
	}

	CConfig::CConfig( )
	{
		std::ifstream ifGlobalConfiguration( GetPXDirectory( ) + PX_XOR( LR"(Configurations\global.px)" ) );
		px_assert( ifGlobalConfiguration.good( ) );
		std::stringstream ssBuffer;
		ssBuffer << ifGlobalConfiguration.rdbuf( );
		jsGlobal = nlohmann::json::parse( Base64< CryptoPP::Base64Decoder >( ssBuffer.str( ) ) );

		wszCurrent = &string_cast< wstr_t >( jsGlobal[ PX_XOR( "Default Configuration" ) ].get_ref< str_t& >( ) )[ 0 ];

		ChangeConfiguration( wszCurrent );
	}

	void PX_API CConfig::SaveInformation( )
	{
		std::ofstream ofGlobalConfiguration( GetPXDirectory( ) + PX_XOR( LR"(Configurations\global.px)" ) );
		px_assert( ofGlobalConfiguration.good( ) );
		ofGlobalConfiguration << Base64< CryptoPP::Base64Encoder >( jsGlobal.dump( 4 ) );

		std::ofstream ofCurrentConfiguration( GetPXDirectory( ) + PX_XOR( LR"(Configurations\)" ) + wszCurrent + PX_XOR( L".px" ) );
		px_assert( ofCurrentConfiguration.good( ) );
		ofCurrentConfiguration << Base64< CryptoPP::Base64Encoder >( jsCurrent.dump( 4 ) );
	}

	bool PX_API CConfig::ChangeConfiguration( wcstr_t wszConfig )
	{
		if ( wszCurrent == wszConfig )
			return true;

		if ( std::filesystem::exists( ( GetPXDirectory( ) + PX_XOR( LR"(Configurations\)" ) + wszConfig + PX_XOR( L".px" ) ).c_str( ) ) )
		{
			std::ifstream ifNewConfiguration( GetPXDirectory( ) + PX_XOR( LR"(Configurations\)" ) + wszConfig + PX_XOR( L".px" ) );
			px_assert( ifNewConfiguration.good( ) );
				try
				{
					std::stringstream ssBuffer;
					ssBuffer << ifNewConfiguration.rdbuf( );
					jsCurrent = nlohmann::json::parse( Base64< CryptoPP::Base64Decoder >( ssBuffer.str( ) ) );
				}
				catch ( nlohmann::detail::parse_error& )
				{
					return false; // Formatting Errors
				}
				catch ( nlohmann::detail::type_error& )
				{
					return false; // Missing Errors
				}

			wszCurrent = wszConfig;
			return true;
		}
		return false;
	}

	bool PX_API FileRead( wstr_t wstrPath, wstr_t& wstrData, bool bRelativePath, bool bBase64 /*= true*/ )
	{
		px_assert( !wstrPath.empty( ) );

		std::ifstream fFile( bRelativePath ? GetPXDirectory( ) + wstrPath : wstrPath );

		if ( !fFile.good( ) )
			return false;

		std::stringstream ssReturn { };
		ssReturn << fFile.rdbuf( );
		wstrData = string_cast< wstr_t >( bBase64 ? Base64< CryptoPP::Base64Decoder >( ssReturn.str( ) ) : ssReturn.str( ) );
		return true;
	}

	bool PX_API FileWrite( wstr_t wstrPath, const wstr_t& wstrData, bool bRelativePath, bool bBase64 /*= true*/ )
	{
		if ( wstrPath.empty( ) || wstrData.empty( ) )
			return false;

		if ( 0 == PathFileExists( wstrPath.substr( 0, wstrPath.find_last_of( L'\\' ) ).c_str( ) ) )
			if ( 0 == CreateDirectory( wstrPath.substr( 0, wstrPath.find_last_of( L'\\' ) ).c_str( ), nullptr ) )
				return false;

		std::ofstream fFile( bRelativePath ? GetPXDirectory( ) + wstrPath : wstrPath, std::ofstream::out | std::ofstream::trunc );
		const auto strBuffer = string_cast< str_t >( wstrData );

		if ( bBase64 )
			fFile << Base64< CryptoPP::Base64Encoder >( strBuffer ).c_str( );
		else
			fFile << strBuffer.c_str( );
		return true;
	}
}
