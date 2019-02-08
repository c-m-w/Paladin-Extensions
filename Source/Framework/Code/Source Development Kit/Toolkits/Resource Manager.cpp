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
		_Log.Log( EPrefix::ERROR, ELocation::RESOURCE_MANAGER, XOR( "Unable to parse text retrieved for hash comparison of resources." ) );
		return false;
	}

	auto bValid = true;

	_Filesystem.ChangeWorkingDirectory( CFilesystem::GetAppdataDirectory( ), { CFilesystem::strRelativeResourceDirectory } );
	try
	{
		for ( auto &_File: jsInformation )
		{
			_Filesystem.StoreCurrentWorkingDirectory( );

			const auto strFile = _File[ XOR( "Path" ) ].get< std::string >( ).substr( 1 );
			std::string strFileData { };

			_Filesystem.ChangeWorkingDirectory( _Filesystem.GetWorkingDirectory( ), { _Filesystem.GetAbsoluteContainingDirectory( strFile ) } );
			if ( !_Filesystem.ReadFile( _Filesystem.PathToFile( strFile ), strFileData, true ) )
			{
				bValid = false;
				break;
			}

			if ( _File[ XOR( "Hash" ) ].get< std::string >( ) != _Cryptography.GenerateHash( strFileData ) )
			{
				_Log.Log( EPrefix::WARNING, ELocation::FILESYSTEM, XOR( "Hash of file %s does not match." ), strFile.c_str( ) );
				bValid = false;
				break;
			}
			_Filesystem.RestoreWorkingDirectory( );
		}
	}
	catch ( nlohmann::json::type_error & )
	{
		_Log.Log( EPrefix::ERROR, ELocation::FILESYSTEM, XOR( "Error while accessing json object while comparing hashes." ) );
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
			_Log.Log( EPrefix::ERROR, ELocation::RESOURCE_MANAGER, XOR( "Unable to parse text retrieved for installing resources." ) );
			return false;
		}
		try
		{
			for ( auto &_File: jsInformation )
			{
				_Filesystem.StoreCurrentWorkingDirectory( );

				const auto strFile = _File[ XOR( "Path" ) ].get< std::string >( ).substr( 1 ),
					strData = _File[ XOR( "Data" ) ].get< std::string >( );
				std::string strRawData { };

				_Filesystem.ChangeWorkingDirectory( _Filesystem.GetWorkingDirectory( ), {_Filesystem.GetAbsoluteContainingDirectory( strFile ) } );

				if ( strData.empty( ) )
				{
					_Log.Log( EPrefix::ERROR, ELocation::RESOURCE_MANAGER, XOR( "File %s is empty. If you uploaded a config file to the server, please remove it. They are automatically created." ), strFile.c_str( ) );
					_Filesystem.RestoreWorkingDirectory( ); 
					return false;
				}

				if ( !_Cryptography.Decode( strData, strRawData ) )
				{
					_Log.Log( EPrefix::ERROR, ELocation::RESOURCE_MANAGER, XOR( "Unable to un-base64 file %s from json." ), strFile.c_str( ) );
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
		catch ( nlohmann::json::type_error & )
		{
			_Log.Log( EPrefix::ERROR, ELocation::FILESYSTEM, XOR( "Error while accessing json object while installing resources." ) );
			return false;
		}
	}

	return _Filesystem.SetPathVisibility( { }, false );
}

void CResourceManager::Uninitialize( )
{ }
