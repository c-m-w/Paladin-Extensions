/// File Manager.cpp

#include "../PX Framework.hpp"

namespace PX
{
	CFileManager::CFileManager( )
	{
		std::ifstream ifGlobalConfiguration( Tools::GetDirectory( PX_DEPENDENCIES_ESCAPE ) + PX_XOR( LR"(\Configurations\global.pxcfg)" ) );
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

	void PX_API CFileManager::SaveInformation( )
	{
		std::ofstream ofGlobalConfiguration( Tools::GetDirectory( PX_DEPENDENCIES_ESCAPE ) + PX_XOR( LR"(\Configurations\global.pxcfg)" ) );
		if ( ofGlobalConfiguration.good( ) )
			ofGlobalConfiguration << Cryptography::Base64< CryptoPP::Base64Encoder >( jsGlobal.dump( 4 ) );
		else
			throw std::exception( PX_XOR( "Failed to open global.pxcfg for writing" ) );

		std::ofstream ofCurrentConfiguration( Tools::GetDirectory( PX_DEPENDENCIES_ESCAPE ) + PX_XOR( LR"(\Configurations\)" ) + wszCurrent + PX_XOR( L".pxcfg" ) );
		if ( ofCurrentConfiguration.good( ) )
			ofCurrentConfiguration << Cryptography::Base64< CryptoPP::Base64Encoder >( jsCurrent.dump( 4 ) );
		else
			throw std::exception( ( std::string( PX_XOR( "Failed to open " ) ) + Tools::string_cast< std::string >( wszCurrent ) + PX_XOR( ".pxcfg for writing" ) ).c_str( ) );
	}

	bool PX_API CFileManager::ChangeConfiguration( Tools::wcstr_t wszConfig )
	{
		if ( wszCurrent == wszConfig )
			return true;

		if ( PathFileExists( ( Tools::GetDirectory( PX_DEPENDENCIES_ESCAPE ) + PX_XOR( LR"(\Configurations\)" ) + wszConfig + PX_XOR( L".pxcfg" ) ).c_str( ) ) )
		{
			std::ifstream ifNewConfiguration( Tools::GetDirectory( PX_DEPENDENCIES_ESCAPE ) + PX_XOR( LR"(\Configurations\)" ) + wszConfig + PX_XOR( L".pxcfg" ) );
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
