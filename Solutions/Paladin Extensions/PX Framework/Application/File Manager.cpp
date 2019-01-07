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

	CConfig::CConfig( ): wstrExtension( PX_XOR( L".pxcfg" ) ), wstrExtensionFolderNames { PX_XOR( L"CSGO\\Configurations\\" ), PX_XOR( L"PUBG\\Configurations\\" ), PX_XOR( L"RSIX\\Configurations\\" ) }, wstrGlobalFileName( PX_XOR( L"global" ) )
	{ }

	PX_RET wstr_t PX_API CConfig::GetConfigDirectory( int iExtension )
	{
		static wstr_t wstrConfigDirectory;
		if ( wstrConfigDirectory.empty( ) )
			wstrConfigDirectory = GetPXDirectory( ) + PX_XOR( L"Resources\\Extensions Data\\" );
		return wstrConfigDirectory + wstrExtensionFolderNames[ iExtension ];
	}

	void PX_API CConfig::SaveConfiguration( int iExtensionID, wcstr_t wszFileName, void *pConfigStructure, std::size_t zConfigStructureSize )
	{
		nlohmann::json jsConfiguration;
		jsConfiguration[ PX_XOR( "Size" ) ] = zConfigStructureSize;
		for ( auto u = 0u; u < zConfigStructureSize; u++ )
			jsConfiguration[ PX_XOR( "Bytes" ) ][ u ] = *reinterpret_cast< byte_t* >( ptr_t( pConfigStructure ) + u );
		FileWrite( GetConfigDirectory( iExtensionID ) + wszFileName + wstrExtension, string_cast< wstr_t >( jsConfiguration.dump( 4 ) ), false, true );
	}

	bool PX_API CConfig::LoadDefaultConfiguration( int iExtensionID, void *pConfigStructure, std::size_t zConfigStructureSize )
	{
		wstr_t wstrData;
		if ( !FileRead( GetConfigDirectory( iExtensionID ) + wstrGlobalFileName + wstrExtension, wstrData, false, true ) )
			return false;
		nlohmann::json jsData;
		try
		{
			jsData = nlohmann::json::parse( string_cast< str_t >( wstrData ) );
		}
		catch ( nlohmann::json::parse_error & )
		{
			return false;
		}
#define large_char_t unsigned __int128
		try
		{
			return LoadConfiguration( iExtensionID, string_cast< wstr_t >( jsData[ PX_XOR( "Default Configuration" ) ].get< str_t >( ) ).c_str( ), pConfigStructure, zConfigStructureSize );
		}
		catch ( nlohmann::json::type_error & )
		{
			return false;
		}
	}

	void CConfig::SetDefaultConfiguration( int iExtensionID, wcstr_t wszFileName )
	{
		nlohmann::json jsGlobal;
		jsGlobal[ PX_XOR( "Default Configuration" ) ] = string_cast< str_t >( wstr_t( wszFileName ) );
		FileWrite( GetConfigDirectory( iExtensionID ) + wstrGlobalFileName + wstrExtension, string_cast< wstr_t >( jsGlobal.dump( 4 ) ), false, true );
	}

	bool PX_API CConfig::LoadConfiguration( int iExtensionID, Types::wcstr_t wszFileName, void *pConfigStructure, std::size_t zConfigStructureSize )
	{
		wstr_t wstrData;
		if ( !FileRead( GetConfigDirectory( iExtensionID ) + wszFileName + wstrExtension, wstrData, false, true ) )
			return false;
		const auto strData = string_cast< str_t >( wstrData );
		nlohmann::json jsConfig;

		try
		{
			jsConfig = nlohmann::json::parse( strData );
		}
		catch ( nlohmann::json::parse_error & )
		{
			return false;
		}

		try
		{
			if ( jsConfig[ PX_XOR( "Size" ) ].get< std::size_t >( ) != zConfigStructureSize )
			{ };// config outdated
			for ( auto u = 0u; u < jsConfig[ PX_XOR( "Size" ) ].get< std::size_t >( ); u++ )
				*reinterpret_cast< byte_t* >( ptr_t( pConfigStructure ) + u ) = jsConfig[ PX_XOR( "Bytes" ) ][ u ].get< byte_t >( );
		}
		catch ( nlohmann::json::type_error & )
		{
			return false;
		}
		return true;
	}

	namespace Resources
	{
		// todo: shouldn't have a parameter, should be hash from server
		bool LoadResources( const str_t &strHash )
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

	bool PX_API FileRead( wstr_t wstrPath, wstr_t &wstrData, bool bRelativePath, bool bBase64 /*= true*/ )
	{
		px_assert( !wstrPath.empty( ) );

		std::ifstream fFile( bRelativePath ? GetPXDirectory( ) + wstrPath : wstrPath );

		if ( !fFile.good( ) )
			return false;

		std::stringstream ssReturn { };
		ssReturn << fFile.rdbuf( );
		fFile.close( );
		const auto str = ssReturn.str( );
		if ( str.empty( ) )
			return false;
		wstrData = string_cast< wstr_t >( bBase64 ? Base64< CryptoPP::Base64Decoder >( str ) : ssReturn.str( ) );
		return true;
	}

	bool PX_API FileWrite( wstr_t wstrPath, const wstr_t &wstrData, bool bRelativePath, bool bBase64 /*= true*/ )
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
