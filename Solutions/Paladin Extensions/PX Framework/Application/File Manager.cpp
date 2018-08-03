/// File Manager.cpp

#include "../PX Framework.hpp"

namespace PX::Files
{
	std::wstring PX_API GetDirectory( unsigned uEscapeLevels )
	{
		auto wszBuffer = static_cast< wchar_t* >( malloc( MAX_PATH ) );
		GetModuleFileName( nullptr, wszBuffer, MAX_PATH );
		std::wstring wstrDirectory = wszBuffer;

		for ( unsigned i = 0u; i <= uEscapeLevels; i++ )
			wstrDirectory = wstrDirectory.substr( 0, wstrDirectory.find_last_of( L'\\' ) );

		return wstrDirectory;
	}

	namespace Resources
	{
		bool LoadResources( const std::string& strHash )
		{
			std::wstring wstrPath = GetDirectory( PX_DEPENDENCIES_ESCAPE ) + LR"(\Resources\)";

			bool bFilesExist = std::filesystem::exists( ( wstrPath + LR"(Paladin Logo.ico)" ).c_str( ) )
					& std::filesystem::exists( ( wstrPath + LR"(Paladin Logo.png)" ).c_str( ) )

					& std::filesystem::exists( ( wstrPath + LR"(Cursor\Arrow.cur)" ).c_str( ) )
					& std::filesystem::exists( ( wstrPath + LR"(Cursor\Hand.cur)" ).c_str( ) )
					& std::filesystem::exists( ( wstrPath + LR"(Cursor\I Beam.cur)" ).c_str( ) )

					& std::filesystem::exists( ( wstrPath + LR"(Fonts\Envy.ttf)" ).c_str( ) )
					& std::filesystem::exists( ( wstrPath + LR"(Fonts\Font Awesome.ttf)" ).c_str( ) )
					& std::filesystem::exists( ( wstrPath + LR"(Fonts\Roboto.ttf)" ).c_str( ) )
					& std::filesystem::exists( ( wstrPath + LR"(Fonts\Roboto Bold.ttf)" ).c_str( ) )
					& std::filesystem::exists( ( wstrPath + LR"(Fonts\Tahoma.ttf)" ).c_str( ) )
					& std::filesystem::exists( ( wstrPath + LR"(Fonts\Tahoma Bold.ttf)" ).c_str( ) )

					& std::filesystem::exists( ( wstrPath + LR"(Game Icons\CSGO.png)" ).c_str( ) )
					& std::filesystem::exists( ( wstrPath + LR"(Game Icons\PUBG.png)" ).c_str( ) );

			if ( !bFilesExist )
				return false;

			const auto fnGetFileData = [ ]( Types::wcstr_t szPathToFile )
			{
				auto pResource = _wfopen( szPathToFile, L"r" );
				dbg::Ensure( pResource );

				fseek( pResource, 0, SEEK_END );
				const auto lSize = ftell( pResource );
				rewind( pResource );

				std::string strData;
				strData.resize( lSize );
				fread( &strData[ 0 ], 1, lSize, pResource );

				fclose( pResource );
				return strData;
			};

			strLogoICO = fnGetFileData( ( wstrPath + LR"(Paladin Logo.ico)" ).c_str( ) );
			strLogoPNG = fnGetFileData( ( wstrPath + LR"(Paladin Logo.png)" ).c_str( ) );

			strCursorArrow = fnGetFileData( ( wstrPath + LR"(Cursor\Arrow.cur)" ).c_str( ) );
			strCursorHand = fnGetFileData( ( wstrPath + LR"(Cursor\Hand.cur)" ).c_str( ) );
			strCursorIBeam = fnGetFileData( ( wstrPath + LR"(Cursor\I Beam.cur)" ).c_str( ) );

			strFontsEnvy = fnGetFileData( ( wstrPath + LR"(Fonts\Envy.ttf)" ).c_str( ) );
			strFontsFontAwesome = fnGetFileData( ( wstrPath + LR"(Fonts\Font Awesome.ttf)" ).c_str( ) );
			strFontsRoboto = fnGetFileData( ( wstrPath + LR"(Fonts\Font Awesome.ttf)" ).c_str( ) );
			strFontsRobotoBold = fnGetFileData( ( wstrPath + LR"(Fonts\Roboto Bold.ttf)" ).c_str( ) );
			strFontsTahoma = fnGetFileData( ( wstrPath + LR"(Fonts\Tahoma.ttf)" ).c_str( ) );
			strFontsTahomaBold = fnGetFileData( ( wstrPath + LR"(Fonts\Tahoma Bold.ttf)" ).c_str( ) );

			strGameIconsCSGO = fnGetFileData( ( wstrPath + LR"(Game Icons\CSGO.png)" ).c_str( ) );
			strGameIconsPUBG = fnGetFileData( ( wstrPath + LR"(Game Icons\PUBG.png)" ).c_str( ) );

			auto strResourcesHash = Cryptography::GenerateHash( strLogoICO )
					+ Cryptography::GenerateHash( strLogoPNG )

					+ Cryptography::GenerateHash( strCursorArrow )
					+ Cryptography::GenerateHash( strCursorHand )
					+ Cryptography::GenerateHash( strCursorIBeam )

					+ Cryptography::GenerateHash( strFontsEnvy )
					+ Cryptography::GenerateHash( strFontsFontAwesome )
					+ Cryptography::GenerateHash( strFontsRoboto )
					+ Cryptography::GenerateHash( strFontsRobotoBold )
					+ Cryptography::GenerateHash( strFontsTahoma )
					+ Cryptography::GenerateHash( strFontsTahomaBold )

					+ Cryptography::GenerateHash( strGameIconsCSGO )
					+ Cryptography::GenerateHash( strGameIconsPUBG );

			return strHash == strResourcesHash;
		}
	}

	CConfig::CConfig( )
	{
		std::ifstream ifGlobalConfiguration( GetDirectory( PX_DEPENDENCIES_ESCAPE ) + PX_XOR( LR"(\Configurations\global.pxcfg)" ) );
		if ( ifGlobalConfiguration.good( ) )
		{
			std::stringstream ssBuffer;
			ssBuffer << ifGlobalConfiguration.rdbuf( );
			jsGlobal = nlohmann::json::parse( Cryptography::Base64< CryptoPP::Base64Decoder >( ssBuffer.str( ) ) );
		}
		else
			throw std::exception( PX_XOR( "Failed to open global.pxcfg for reading" ) );

		wszCurrent = &Tools::string_cast< std::wstring >( jsGlobal[ PX_XOR( "Default Configuration" ) ].get_ref< std::string& >( ) )[ 0 ];

		ChangeConfiguration( wszCurrent );
	}

	void PX_API CConfig::SaveInformation( )
	{
		std::ofstream ofGlobalConfiguration( GetDirectory( PX_DEPENDENCIES_ESCAPE ) + PX_XOR( LR"(\Configurations\global.pxcfg)" ) );
		if ( ofGlobalConfiguration.good( ) )
			ofGlobalConfiguration << Cryptography::Base64< CryptoPP::Base64Encoder >( jsGlobal.dump( 4 ) );
		else
			throw std::exception( PX_XOR( "Failed to open global.pxcfg for writing" ) );

		std::ofstream ofCurrentConfiguration( GetDirectory( PX_DEPENDENCIES_ESCAPE ) + PX_XOR( LR"(\Configurations\)" ) + wszCurrent + PX_XOR( L".pxcfg" ) );
		if ( ofCurrentConfiguration.good( ) )
			ofCurrentConfiguration << Cryptography::Base64< CryptoPP::Base64Encoder >( jsCurrent.dump( 4 ) );
		else
			throw std::exception( ( std::string( PX_XOR( "Failed to open " ) ) + Tools::string_cast< std::string >( wszCurrent ) + PX_XOR( ".pxcfg for writing" ) ).c_str( ) );
	}

	bool PX_API CConfig::ChangeConfiguration( Types::wcstr_t wszConfig )
	{
		if ( wszCurrent == wszConfig )
			return true;

		if ( std::filesystem::exists( ( GetDirectory( PX_DEPENDENCIES_ESCAPE ) + PX_XOR( LR"(\Configurations\)" ) + wszConfig + PX_XOR( L".pxcfg" ) ).c_str( ) ) )
		{
			std::ifstream ifNewConfiguration( GetDirectory( PX_DEPENDENCIES_ESCAPE ) + PX_XOR( LR"(\Configurations\)" ) + wszConfig + PX_XOR( L".pxcfg" ) );
			if ( ifNewConfiguration.good( ) )
			{
				try
				{
					std::stringstream ssBuffer;
					ssBuffer << ifNewConfiguration.rdbuf( );
					jsCurrent = nlohmann::json::parse( Cryptography::Base64< CryptoPP::Base64Decoder >( ssBuffer.str( ) ) );
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
				throw std::exception( ( std::string( PX_XOR( "Failed to open " ) ) + Tools::string_cast< std::string >( wszConfig ) + PX_XOR( ".pxcfg for writing" ) ).c_str( ) );

			wszCurrent = wszConfig;
			return true;
		}
		return false;
	}
}
