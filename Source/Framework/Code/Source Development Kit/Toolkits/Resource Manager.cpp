/// Resource Manager.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#define USE_DEFINITIONS
#include "../../Framework.hpp"

bool CResourceManager::Initialize( )
{
	std::string strHashCipher { }, strDecrypted { };
	if ( !NET.Request( EAction::GET_RESOURCE_HASH, strHashCipher )
		|| !CRYPTO.Decrypt( strHashCipher, strDecrypted ) )
		return false;

	nlohmann::json jsInformation { };
	try
	{
		jsInformation = nlohmann::json::parse( strDecrypted );
	}
	catch ( nlohmann::json::parse_error & )
	{
		LOG.Log( EPrefix::ERROR, ELocation::RESOURCE_MANAGER, XOR( "Unable to parse text retrieved for hash comparison of resources." ) );
		return false;
	}

	auto bValid = true;

	FS.ChangeWorkingDirectory( CFilesystem::GetAppdataDirectory( ), { CFilesystem::strRelativeResourceDirectory } );
	try
	{
		for ( auto &_File: jsInformation )
		{
			FS.StoreCurrentWorkingDirectory( );

			const auto strFile = _File[ XOR( "Path" ) ].get< std::string >( ).substr( 1 );
			std::string strFileData { };

			FS.ChangeWorkingDirectory( FS.GetWorkingDirectory( ), { FS.GetAbsoluteContainingDirectory( strFile ) } );
			if ( !FS.ReadFile( FS.PathToFile( strFile ), strFileData, true ) )
			{
				bValid = false;
				break;
			}

			if ( _File[ XOR( "Hash" ) ].get< std::string >( ) != CRYPTO.GenerateHash( strFileData ) )
			{
				LOG.Log( EPrefix::WARNING, ELocation::FILESYSTEM, XOR( "Hash of file %s does not match." ), strFile.c_str( ) );
				bValid = false;
				break;
			}
			FS.RestoreWorkingDirectory( );
		}
	}
	catch ( nlohmann::json::type_error & )
	{
		LOG.Log( EPrefix::ERROR, ELocation::FILESYSTEM, XOR( "Error while accessing json object while comparing hashes." ) );
		return false;
	}

	if ( !bValid )
	{
		std::string strResourceCipher { }, strDecryptedResources { };
		if ( !FS.DeleteCurrentDirectory( )
			|| !NET.Request( EAction::GET_RESOURCES, strResourceCipher )
			|| !CRYPTO.Decrypt( strResourceCipher, strDecryptedResources ) )
			return false;

		try
		{
			jsInformation = nlohmann::json::parse( strDecryptedResources );
		}
		catch ( nlohmann::json::parse_error & )
		{
			LOG.Log( EPrefix::ERROR, ELocation::RESOURCE_MANAGER, XOR( "Unable to parse text retrieved for installing resources." ) );
			return false;
		}
		try
		{
			for ( auto &_File: jsInformation )
			{
				FS.StoreCurrentWorkingDirectory( );

				const auto strFile = _File[ XOR( "Path" ) ].get< std::string >( ).substr( 1 ),
					strData = _File[ XOR( "Data" ) ].get< std::string >( );
				std::string strRawData { };

				FS.ChangeWorkingDirectory( FS.GetWorkingDirectory( ), {FS.GetAbsoluteContainingDirectory( strFile ) } );

				if ( strData.empty( ) )
				{
					LOG.Log( EPrefix::ERROR, ELocation::RESOURCE_MANAGER, XOR( "File %s is empty. If you uploaded a config file to the server, please remove it. They are automatically created." ), strFile.c_str( ) );
					FS.RestoreWorkingDirectory( ); 
					return false;
				}

				if ( !CRYPTO.Decode( strData, strRawData ) )
				{
					LOG.Log( EPrefix::ERROR, ELocation::RESOURCE_MANAGER, XOR( "Unable to un-base64 file %s from json." ), strFile.c_str( ) );
					FS.RestoreWorkingDirectory( );
					return false;
				}

				if ( !FS.WriteFile( FS.PathToFile( strFile ), strRawData, true ) )
				{
					FS.RestoreWorkingDirectory( );
					return false;
				}

				FS.RestoreWorkingDirectory( );
			}
		}
		catch ( nlohmann::json::type_error & )
		{
			LOG.Log( EPrefix::ERROR, ELocation::FILESYSTEM, XOR( "Error while accessing json object while installing resources." ) );
			return false;
		}
	}

	return FS.SetPathVisibility( { }, false );
}

void CResourceManager::Uninitialize( )
{ }

std::string& CResourceManager::GetResource( const std::string &strRelativePath )
{
	const auto pSearch = _LoadedResources.find( strRelativePath );
	if ( pSearch != _LoadedResources.end( ) )
		return pSearch->second;

	const auto strPath = FS.GetAbsoluteContainingDirectory( strRelativePath );
	std::string strReturn;

	FS.StoreCurrentWorkingDirectory( );
	FS.ChangeWorkingDirectory( FS.GetAppdataDirectory( ), { FS.strRelativeResourceDirectory, strPath } );
	if ( !FS.ReadFile( CFilesystem::PathToFile( strRelativePath ), strReturn, true ) )
		throw std::runtime_error( XOR( "Unable to obtain resource " ) + strRelativePath );

	FS.RestoreWorkingDirectory( );
	_LoadedResources.insert( std::pair< std::string, std::string >( strRelativePath, strReturn ) );
	return GetResource( strRelativePath );
}
