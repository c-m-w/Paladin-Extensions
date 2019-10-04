/// Resource Manager.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#define USE_DEFINITIONS
#include "../../Framework.hpp"

bool CResourceManager::Initialize( )
{
	std::string strHashCipher { }, strDecrypted { };
	if ( !_Connection.Request( EAction::GET_RESOURCE_HASH, strHashCipher )
		|| !CRYPTO.Decrypt( strHashCipher, strDecrypted ) )
		return false;

	nlohmann::json jsInformation { };
	try
	{
		jsInformation = nlohmann::json::parse( strDecrypted );
	}
	catch ( nlohmann::json::parse_error & )
	{
		_Log.Log( EPrefix::ERROR, ELocation::RESOURCE_MANAGER, ENC( "Unable to parse text retrieved for hash comparison of resources." ) );
		return false;
	}

	auto bValid = true;

	_Filesystem.ChangeWorkingDirectory( CFilesystem::GetAppdataDirectory( ), { CFilesystem::strRelativeResourceDirectory } );
	try
	{
		for ( auto &_File: jsInformation )
		{
			_Filesystem.StoreCurrentWorkingDirectory( );

			const auto strFile = _File[ ENC( "Path" ) ].get< std::string >( );
			std::string strFileData { };

			_Filesystem.ChangeWorkingDirectory( _Filesystem.GetWorkingDirectory( ), { _Filesystem.GetAbsoluteContainingDirectory( strFile ) } );
			if ( !_Filesystem.ReadFile( _Filesystem.PathToFile( strFile ), strFileData, true ) )
			{
				_Filesystem.RestoreWorkingDirectory( );
				bValid = false;
				break;
			}

			if ( _File[ ENC( "Hash" ) ].get< std::string >( ) != _Cryptography.GenerateHash( strFileData ) )
			{
				_Filesystem.RestoreWorkingDirectory( );
				_Log.Log( EPrefix::WARNING, ELocation::RESOURCE_MANAGER, ENC( "Hash of file %s does not match." ), strFile.c_str( ) );
				bValid = false;
				break;
			}
			_Filesystem.RestoreWorkingDirectory( );
		}
	}
	catch ( nlohmann::json::type_error &e )
	{
		_Log.Log( EPrefix::ERROR, ELocation::RESOURCE_MANAGER, ENC( "Error while accessing json object while comparing hashes. Message: %s." ), e.what( ) );
		return false;
	}

	if ( !bValid )
	{
		std::string strResourceCipher { }, strDecryptedResources { };
		if ( !_Filesystem.DeleteCurrentDirectory( )
			|| !_Connection.Request( EAction::GET_RESOURCES, strResourceCipher )
			|| !CRYPTO.Decrypt( strResourceCipher, strDecryptedResources ) )
			return false;

		try
		{
			jsInformation = nlohmann::json::parse( strDecryptedResources );
		}
		catch ( nlohmann::json::parse_error & )
		{
			_Log.Log( EPrefix::ERROR, ELocation::RESOURCE_MANAGER, ENC( "Unable to parse text retrieved for installing resources." ) );
			return false;
		}
		try
		{
			for ( auto &_File: jsInformation )
			{
				_Filesystem.StoreCurrentWorkingDirectory( );

				const auto strFile = _File[ ENC( "Path" ) ].get< std::string >( ),
						   strData = _File[ ENC( "Data" ) ].get< std::string >( );
				std::string strRawData { };

				_Filesystem.ChangeWorkingDirectory( _Filesystem.GetWorkingDirectory( ), { _Filesystem.GetAbsoluteContainingDirectory( strFile ) } );

				if ( strData.empty( ) )
				{
					_Log.Log( EPrefix::ERROR, ELocation::RESOURCE_MANAGER, ENC( "File %s is empty. If you uploaded a config file to the server, please remove it. They are automatically created." ), strFile.c_str( ) );
					_Filesystem.RestoreWorkingDirectory( );
					return false;
				}

				if ( !_Cryptography.Decode( strData, strRawData ) )
				{
					_Log.Log( EPrefix::ERROR, ELocation::RESOURCE_MANAGER, ENC( "Unable to un-base64 file %s from json." ), strFile.c_str( ) );
					_Filesystem.RestoreWorkingDirectory( );
					return false;
				}

				if ( !_Filesystem.WriteFile( _Filesystem.PathToFile( strFile ), strRawData, true ) )
				{
					_Filesystem.RestoreWorkingDirectory( );
					return false;
				}

				_Filesystem.RestoreWorkingDirectory( );
			}
		}
		catch ( nlohmann::json::type_error &e )
		{
			_Log.Log( EPrefix::ERROR, ELocation::FILESYSTEM, ENC( "Error while accessing json object while installing resources. Message: %s." ), e.what( ) );
			return false;
		}
	}

	return _Filesystem.SetPathVisibility( { }, false );
}

void CResourceManager::Uninitialize( )
{ }

std::string &CResourceManager::GetResource( const std::string &strRelativePath )
{
	const auto pSearch = _LoadedResources.find( strRelativePath );
	if ( pSearch != _LoadedResources.end( ) )
		return pSearch->second;

	const auto strPath = _Filesystem.GetAbsoluteContainingDirectory( strRelativePath );
	std::string strReturn;

	_Filesystem.StoreCurrentWorkingDirectory( );
	_Filesystem.ChangeWorkingDirectory( _Filesystem.GetAppdataDirectory( ), { _Filesystem.strRelativeResourceDirectory, strPath } );
	if ( !_Filesystem.ReadFile( CFilesystem::PathToFile( strRelativePath ), strReturn, true ) )
		throw std::runtime_error( ENC( "Unable to obtain resource " ) + strRelativePath );

	_Filesystem.RestoreWorkingDirectory( );
	_LoadedResources.insert( std::pair< std::string, std::string >( strRelativePath, strReturn ) );
	return GetResource( strRelativePath );
}

bool CResourceManager::ResourceExists( const std::string &strRelativePath )
{
	return !GetResource( strRelativePath ).empty( );
}

CResourceManager _ResourceManager;
