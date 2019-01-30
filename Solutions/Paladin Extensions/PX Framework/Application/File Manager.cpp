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

	std::vector< Types::str_t > GetFilesInDirectory( const Types::str_t& strFolder, const Types::str_t& strExtension )
	{
		const auto strDirectory = string_cast< std::string >( GetPXDirectory( ) ) + strFolder;
		std::vector< Types::str_t > vecFiles;
		
		for ( auto& file : std::filesystem::directory_iterator( strDirectory.c_str( ) ) )
			if ( file.is_regular_file( )
				 && ( strExtension.empty( ) || file.path( ).string( ).find( strExtension ) != std::string::npos ) )
			{
				vecFiles.emplace_back( file.path( ).string( ).substr( file.path( ).string( ).find_last_of( '\\' ) + 1 ) );
				if ( !strExtension.empty( ) )
					vecFiles.back() = vecFiles.back( ).substr( 0, vecFiles.back( ).length( ) - strExtension.length( ) );
			}

		return vecFiles;
	}

	void CConfig::LoadGlobalConfig( )
	{
		if ( bLoadedGlobalConfig )
			return;

		std::wstring wstrData { };
		if ( !Files::FileRead( GetConfigDirectory( ) + wstrGlobalFileName, wstrData, false, false ) )
		{
			SaveGlobalConfiguration( );
			return LoadGlobalConfig( );
		}

		try
		{
			auto jsData = nlohmann::json::parse( string_cast< std::string >( wstrData ) );

			global.kMenuKey = jsData[ "Menu Key" ].get< int >( );
			global.bSimplifyMenu = jsData[ "Simplify Menu" ].get< bool >( );
			global.bNotifyUponInjection = jsData[ "Notify Upon Injection" ].get< bool >( );
			global.bNotifyUponConfigurationChange = jsData[ "Notify Upon Configuration Change" ].get< bool >( );
			global.bDisplayTooltips = jsData[ "Display Tooltips" ].get< bool >( );
			global.bDisplayWatermark = jsData[ "Display Watermark" ].get< bool >( );
			bLoadedGlobalConfig = true;
			if ( jsData[ "Default Configuration" ].get< std::string >( ).empty( )
				 || jsData[ "Default Configuration" ].get< std::string >( )[ 0 ] == 0 )
			{
				global.strDefaultConfiguration = PX_XOR( "none" );
				SaveGlobalConfiguration( );
			}
			else
				global.strDefaultConfiguration = jsData[ "Default Configuration" ].get< std::string >( );
		}
		catch( nlohmann::json::parse_error& )
		{
			SaveGlobalConfiguration( );
			return LoadGlobalConfig( );
		}
		catch( nlohmann::json::type_error& )
		{
			SaveGlobalConfiguration( );
			return LoadGlobalConfig( );
		}
	}

	void CConfig::CreateDefaultConfig( )
	{
		SaveConfiguration( string_cast< std::wstring >( GetDefaultConfiguration( ) ).c_str( ) );
	}

	CConfig::CConfig( ): wstrExtension( PX_XOR( L".pxcfg" ) ), wstrExtensionFolderNames { PX_XOR( L"CSGO\\Configurations\\" ), PX_XOR( L"PUBG\\Configurations\\" ), PX_XOR( L"RSIX\\Configurations\\" ) }, wstrConfigsFolder( PX_XOR( L"Resources\\Extensions Data\\") ), wstrGlobalFileName( PX_XOR( L"global.json" ) )
	{ }

	void CConfig::SetMenuKey( const Types::key_t kNewKey )
	{
		if( global.kMenuKey != kNewKey )
		{
			global.kMenuKey = kNewKey;
			SaveGlobalConfiguration( );
		}
	}

	void CConfig::SetDefaultConfiguration( const Types::str_t& strNewDefaultConfiguration )
	{
		if ( global.strDefaultConfiguration != strNewDefaultConfiguration )
		{
			global.strDefaultConfiguration = strNewDefaultConfiguration;
			SaveGlobalConfiguration( );
		}
	}

	Types::key_t CConfig::GetMenuKey( )
	{
		LoadGlobalConfig( );
		return global.kMenuKey;
	}

	const Types::str_t& CConfig::GetDefaultConfiguration( )
	{
		LoadGlobalConfig( );
		return global.strDefaultConfiguration;
	}

	void CConfig::SetContext( void* pStructure, std::size_t zConfigStructure, int iExtensionID )
	{
		pConfig = pStructure;
		zConfig = zConfigStructure;
		iExtension = iExtensionID;

		LoadGlobalConfig( );
		LoadDefaultConfiguration( );
	}

	PX_RET wstr_t PX_API CConfig::GetConfigDirectory( )
	{
		static wstr_t wstrConfigDirectory;
		if ( wstrConfigDirectory.empty( ) )
			wstrConfigDirectory = GetPXDirectory( ) + wstrConfigsFolder;

		return wstrConfigDirectory + wstrExtensionFolderNames[ iExtension ];
	}

	std::vector< Types::str_t > CConfig::GetConfigs( )
	{
		const auto vecConfigs = GetFilesInDirectory( string_cast< std::string >( wstrConfigsFolder + wstrExtensionFolderNames[ iExtension ] ), string_cast< decltype( std::string { } ) > ( wstrExtension ) );
		if ( vecConfigs.empty( ) )
		{
			CreateDefaultConfig( );
			return GetConfigs( );
		}

		return vecConfigs;
	}

	void CConfig::SaveGlobalConfiguration( )
	{
		Files::FileWrite( GetConfigDirectory( ) + wstrGlobalFileName, string_cast< std::wstring >(
			nlohmann::json
			{
				{ "Menu Key", global.kMenuKey },
				{ "Default Configuration", global.strDefaultConfiguration },
				{ "Simplify Menu", global.bSimplifyMenu },
				{ "Notify Upon Injection", global.bNotifyUponInjection },
				{ "Notify Upon Configuration Change", global.bNotifyUponConfigurationChange },
				{ "Display Tooltips", global.bDisplayTooltips },
				{ "Display Watermark", global.bDisplayWatermark },
			}.dump( 4 ) ), false, false );
	}

	void PX_API CConfig::SaveConfiguration( wcstr_t wszFileName )
	{
		std::string strConfig { };

		strConfig.resize( zConfig + 1 );
		const auto pBytes = &strConfig[ 0 ];
		for( auto u = 0u; u < zConfig; u++ )
			pBytes[ u ] = *reinterpret_cast< byte_t* >( ptr_t( pConfig ) + u );

		FileWrite( GetConfigDirectory( ) + wszFileName + wstrExtension, string_cast< wstr_t >( strConfig ), false, false );
	}

	bool PX_API CConfig::LoadDefaultConfiguration( )
	{
		if ( !LoadConfiguration( string_cast< std::wstring >( global.strDefaultConfiguration ).c_str( ) ) )
			SaveConfiguration( string_cast< std::wstring >( global.strDefaultConfiguration ).c_str( ) );

		return true;
	}

	//oid CConfig::SetDefaultConfiguration( int iExtensionID, wcstr_t wszFileName )
	//
	//	nlohmann::json jsGlobal;
	//	jsGlobal[ PX_XOR( "Default Configuration" ) ] = string_cast< str_t >( wstr_t( wszFileName ) );
	//	FileWrite( GetConfigDirectory( iExtensionID ) + wstrGlobalFileName + wstrExtension, string_cast< wstr_t >( jsGlobal.dump( 4 ) ), false, true );
	//

	bool PX_API CConfig::LoadConfiguration( Types::wcstr_t wszFileName )
	{
		wstr_t wstrData;
		if ( !FileRead( GetConfigDirectory( ) + wszFileName + wstrExtension, wstrData, false, false ) )
			return false;

		const auto strData = string_cast< str_t >( wstrData );
		if ( strData.length( ) != zConfig + 1 )
		{
			RemoveConfiguration( wszFileName );
			return false;
		}

		const auto pData = &strData[ 0 ];
		for ( auto u = 0u; u < zConfig; u++ )
			*reinterpret_cast< byte_t* >( ptr_t( pConfig ) + u ) = pData[ u ];

		return true;
	}

	void CConfig::RemoveConfiguration( Types::wcstr_t wszFileName )
	{
		DeleteFile( ( GetPXDirectory( ) + wstrExtensionFolderNames[ iExtension ] + wszFileName + wstrExtension ).c_str( ) );
		if ( wszFileName == string_cast< std::wstring >( global.strDefaultConfiguration ) )
			SaveConfiguration( wszFileName );
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

		const auto pFile = _wfopen( wstrPath.c_str( ), PX_XOR( L"rb" ) );
		if ( pFile == nullptr )
			return false;

		fseek( pFile, 0, SEEK_END );
		const auto sSize = ftell( pFile );
		rewind( pFile );
		std::string strBuffer {  };
		strBuffer.resize( sSize );
		fread( &strBuffer[ 0 ], sizeof( char ), sSize, pFile );
		fclose( pFile );

		if( strBuffer.empty( ) )
		{
			DeleteFile( wstrPath.c_str( ) );
			return false;
		}

		wstrData = string_cast< wstr_t >( bBase64 ? Base64< CryptoPP::Base64Decoder >( strBuffer ) : strBuffer );
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
		const auto strBuffer = bBase64 ? Base64< CryptoPP::Base64Encoder >( string_cast< str_t >( wstrData ) ).c_str( ) : string_cast< str_t >( wstrData );

		const auto pFile = _wfopen( wstrPath.c_str( ), PX_XOR( L"wb" ) );
		if ( pFile == nullptr )
			return false;

		fwrite( &strBuffer[ 0 ], sizeof( char ), strBuffer.length( ), pFile );
		fclose( pFile );
		return true;
	}
}
