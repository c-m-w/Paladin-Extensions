/// File Manager.cpp

#define PX_USE_NAMESPACES
#include "../PX Framework.hpp"

namespace PX::Files
{
	std::wstring GetExecutablePath( )
	{
		std::wstring wstrDirectory;
		wstrDirectory.resize( MAX_PATH );
		GetModuleFileName( nullptr, &wstrDirectory[ 0 ], MAX_PATH );

		return wstrDirectory;
	}

	std::wstring PX_API GetExecutableDirectory( unsigned uEscapeLevels )
	{
		std::wstring wstrDirectory;
		wstrDirectory.resize( MAX_PATH );
		GetModuleFileName( nullptr, &wstrDirectory[ 0 ], MAX_PATH );

		for ( unsigned i = 0u; i <= uEscapeLevels; i++ )
			wstrDirectory = wstrDirectory.substr( 0, wstrDirectory.find_last_of( L'\\' ) );

		return wstrDirectory + L'\\';
	}

	std::wstring PX_API GetExecutableName( )
	{
		std::wstring wstrDirectory;
		wstrDirectory.resize( MAX_PATH );
		GetModuleFileName( nullptr, &wstrDirectory[ 0 ], MAX_PATH );

		return wstrDirectory.substr( wstrDirectory.find_last_of( L'\\' ) + 1, wstrDirectory.length( ) );
	}

	namespace Resources
	{
		bool LoadResources( const std::string& strHash )
		{
			std::wstring wstrPath = GetExecutableDirectory( PX_DEPENDENCIES_ESCAPE ) + PX_XOR( LR"(Resources\)" );

			bool bFilesExist = std::filesystem::exists( ( wstrPath + PX_XOR( LR"(Paladin Logo.ico)" ) ).c_str( ) )
				& std::filesystem::exists( ( wstrPath + PX_XOR( LR"(Paladin Logo.png)" ) ).c_str( ) )

				& std::filesystem::exists( ( wstrPath + PX_XOR( LR"(Cursor\Arrow.cur)" ) ).c_str( ) )
				& std::filesystem::exists( ( wstrPath + PX_XOR( LR"(Cursor\Hand.cur)" ) ).c_str( ) )
				& std::filesystem::exists( ( wstrPath + PX_XOR( LR"(Cursor\I Beam.cur)" ) ).c_str( ) )

				& std::filesystem::exists( ( wstrPath + PX_XOR( LR"(Fonts\Envy.ttf)" ) ).c_str( ) )
				& std::filesystem::exists( ( wstrPath + PX_XOR( LR"(Fonts\Font Awesome.ttf)" ) ).c_str( ) )
				& std::filesystem::exists( ( wstrPath + PX_XOR( LR"(Fonts\Roboto.ttf)" ) ).c_str( ) )
				& std::filesystem::exists( ( wstrPath + PX_XOR( LR"(Fonts\Roboto Bold.ttf)" ) ).c_str( ) )
				& std::filesystem::exists( ( wstrPath + PX_XOR( LR"(Fonts\Tahoma.ttf)" ) ).c_str( ) )
				& std::filesystem::exists( ( wstrPath + PX_XOR( LR"(Fonts\Tahoma Bold.ttf)" ) ).c_str( ) )

				& std::filesystem::exists( ( wstrPath + PX_XOR( LR"(Game Icons\CSGO.png)" ) ).c_str( ) )
				& std::filesystem::exists( ( wstrPath + PX_XOR( LR"(Game Icons\PUBG.png)" ) ).c_str( ) );

			if ( !bFilesExist )
				return false;

			const auto fnGetFileData = [ ]( wcstr_t szPathToFile )
			{
				auto pResource = _wfopen( szPathToFile, PX_XOR( L"r" ) );
				px_assert( pResource );

				fseek( pResource, 0, SEEK_END );
				const auto lSize = ftell( pResource );
				rewind( pResource );

				std::string strData;
				strData.resize( lSize );
				fread( &strData[ 0 ], 1, lSize, pResource );

				fclose( pResource );
				return strData;
			};

			strLogoICO = fnGetFileData( ( wstrPath + PX_XOR( LR"(Paladin Logo.ico)" ) ).c_str( ) );
			strLogoPNG = fnGetFileData( ( wstrPath + PX_XOR( LR"(Paladin Logo.png)" ) ).c_str( ) );

			strCursorArrow = fnGetFileData( ( wstrPath + PX_XOR( LR"(Cursor\Arrow.cur)" ) ).c_str( ) );
			strCursorHand = fnGetFileData( ( wstrPath + PX_XOR( LR"(Cursor\Hand.cur)" ) ).c_str( ) );
			strCursorIBeam = fnGetFileData( ( wstrPath + PX_XOR( LR"(Cursor\I Beam.cur)" ) ).c_str( ) );

			strFontsEnvy = fnGetFileData( ( wstrPath + PX_XOR( LR"(Fonts\Envy.ttf)" ) ).c_str( ) );
			strFontsFontAwesome = fnGetFileData( ( wstrPath + PX_XOR( LR"(Fonts\Font Awesome.ttf)" ) ).c_str( ) );
			strFontsRoboto = fnGetFileData( ( wstrPath + PX_XOR( LR"(Fonts\Font Awesome.ttf)" ) ).c_str( ) );
			strFontsRobotoBold = fnGetFileData( ( wstrPath + PX_XOR( LR"(Fonts\Roboto Bold.ttf)" ) ).c_str( ) );
			strFontsTahoma = fnGetFileData( ( wstrPath + PX_XOR( LR"(Fonts\Tahoma.ttf)" ) ).c_str( ) );
			strFontsTahomaBold = fnGetFileData( ( wstrPath + PX_XOR( LR"(Fonts\Tahoma Bold.ttf)" ) ).c_str( ) );

			strGameIconsCSGO = fnGetFileData( ( wstrPath + PX_XOR( LR"(Game Icons\CSGO.png)" ) ).c_str( ) );
			strGameIconsPUBG = fnGetFileData( ( wstrPath + PX_XOR( LR"(Game Icons\PUBG.png)" ) ).c_str( ) );

			auto strResourcesHash = GenerateHash( strLogoICO )
				+ GenerateHash( strLogoPNG )

				+ GenerateHash( strCursorArrow )
				+ GenerateHash( strCursorHand )
				+ GenerateHash( strCursorIBeam )

				+ GenerateHash( strFontsEnvy )
				+ GenerateHash( strFontsFontAwesome )
				+ GenerateHash( strFontsRoboto )
				+ GenerateHash( strFontsRobotoBold )
				+ GenerateHash( strFontsTahoma )
				+ GenerateHash( strFontsTahomaBold )

				+ GenerateHash( strGameIconsCSGO )
				+ GenerateHash( strGameIconsPUBG );

			return strHash == strResourcesHash;
		}
	}

	CConfig::CConfig( )
	{
		std::ifstream ifGlobalConfiguration( GetExecutableDirectory( PX_DEPENDENCIES_ESCAPE ) + PX_XOR( LR"(\Configurations\global.px)" ) );
		if ( ifGlobalConfiguration.good( ) )
		{
			std::stringstream ssBuffer;
			ssBuffer << ifGlobalConfiguration.rdbuf( );
			jsGlobal = nlohmann::json::parse( Base64< CryptoPP::Base64Decoder >( ssBuffer.str( ) ) );
		}
		else
			throw std::exception( PX_XOR( "Failed to open global.px for reading" ) );

		wszCurrent = &string_cast< std::wstring >( jsGlobal[ PX_XOR( "Default Configuration" ) ].get_ref< std::string& >( ) )[ 0 ];

		ChangeConfiguration( wszCurrent );
	}

	void PX_API CConfig::SaveInformation( )
	{
		std::ofstream ofGlobalConfiguration( GetExecutableDirectory( PX_DEPENDENCIES_ESCAPE ) + PX_XOR( LR"(\Configurations\global.px)" ) );
		if ( ofGlobalConfiguration.good( ) )
			ofGlobalConfiguration << Base64< CryptoPP::Base64Encoder >( jsGlobal.dump( 4 ) );
		else
			throw std::exception( PX_XOR( "Failed to open global.px for writing" ) );

		std::ofstream ofCurrentConfiguration( GetExecutableDirectory( PX_DEPENDENCIES_ESCAPE ) + PX_XOR( LR"(\Configurations\)" ) + wszCurrent + PX_XOR( L".px" ) );
		if ( ofCurrentConfiguration.good( ) )
			ofCurrentConfiguration << Base64< CryptoPP::Base64Encoder >( jsCurrent.dump( 4 ) );
		else
			throw std::exception( ( std::string( PX_XOR( "Failed to open " ) ) + string_cast< std::string >( wszCurrent ) + PX_XOR( ".px for writing" ) ).c_str( ) );
	}

	bool PX_API CConfig::ChangeConfiguration( wcstr_t wszConfig )
	{
		if ( wszCurrent == wszConfig )
			return true;

		if ( std::filesystem::exists( ( GetExecutableDirectory( PX_DEPENDENCIES_ESCAPE ) + PX_XOR( LR"(\Configurations\)" ) + wszConfig + PX_XOR( L".px" ) ).c_str( ) ) )
		{
			std::ifstream ifNewConfiguration( GetExecutableDirectory( PX_DEPENDENCIES_ESCAPE ) + PX_XOR( LR"(\Configurations\)" ) + wszConfig + PX_XOR( L".px" ) );
			if ( ifNewConfiguration.good( ) )
			{
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
			}
			else
				throw std::exception( ( std::string( PX_XOR( "Failed to open " ) ) + string_cast< std::string >( wszConfig ) + PX_XOR( ".px for writing" ) ).c_str( ) );

			wszCurrent = wszConfig;
			return true;
		}
		return false;
	}

	bool PX_API FileRead( std::wstring wstrPath, std::wstring& wstrData, bool bRelativePath, bool bBase64 /*= true*/ )
	{
		px_assert( !wstrPath.empty( ) );

		std::ifstream fFile( bRelativePath ? GetExecutableDirectory( PX_DEPENDENCIES_ESCAPE ) + wstrPath : wstrPath );

		if ( !fFile.good( ) )
			return false;

		std::stringstream ssReturn { };
		ssReturn << fFile.rdbuf( );
		wstrData = string_cast< std::wstring >( bBase64 ? Base64< CryptoPP::Base64Decoder >( ssReturn.str( ) ) : ssReturn.str( ) );
		return true;
	}

	bool PX_API FileWrite( std::wstring wstrPath, const std::wstring& wstrData, bool bRelativePath, bool bBase64 /*= true*/ )
	{
		if ( wstrPath.empty( ) || wstrData.empty( ) )
			return false;

		if ( FALSE == PathFileExists( wstrPath.substr( 0, wstrPath.find_last_of( L'\\' ) ).c_str( ) ) )
			if ( FALSE == CreateDirectory( wstrPath.substr( 0, wstrPath.find_last_of( L'\\' ) ).c_str( ), nullptr ) )
				return false;

		std::ofstream fFile( bRelativePath ? GetExecutableDirectory( PX_DEPENDENCIES_ESCAPE ) + wstrPath : wstrPath, std::ofstream::out | std::ofstream::trunc );

		fFile.write( bBase64
					 ? Base64< CryptoPP::Base64Encoder >( string_cast< std::string >( wstrData ) ).c_str( )
					 : string_cast< std::string >( wstrData ).c_str( ), wstrData.length( ) );
		return true;
	}
}
