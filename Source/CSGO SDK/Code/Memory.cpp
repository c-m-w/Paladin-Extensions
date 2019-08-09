/// Memory.cpp

#include "CSGO SDK.hpp"
#include <wingdi.h>
#include <wingdi.h>
#include <wingdi.h>

namespace Memory
{
	nlohmann::json jsMemory { };

	bool GetMemoryValue( std::initializer_list< std::string > initLevels, std::string& strOut )
	{
		auto jsSearch = jsMemory;

		for ( auto& strLevel : initLevels )	
			jsSearch = jsSearch[ _Cryptography.GenerateHash( strLevel ) ];

		try
		{
			if ( !_Cryptography.Decrypt( jsSearch.get< std::string >( ), strOut, _Cryptography.strStaticEncryptionKey, _Cryptography.strStaticInitializationVector ) )
				return false;
		}
		catch( nlohmann::json::type_error& e )
		{
			return false;
		}

		return true;
	}

	module_info_t::operator HMODULE( ) const
	{
		return _Module;
	}

	bool module_info_t::Valid( )
	{
		if ( !_Module )
			return false;

		if ( _CreateInterface == nullptr )
		{
			std::string strCreateInterface { };

			if ( !GetMemoryValue( { strCreateInterfaceIdentifier }, strCreateInterface ) )
				return false;

			_CreateInterface = decltype( _CreateInterface )( GetProcAddress( _Module, strCreateInterface.c_str( ) ) );
		}

		return true;
	}

	bool InitializeMemory( )
	{
#if defined _DEBUG

		jsMemory = nlohmann::json::parse( CreateDataFile( ) );

#else

		std::string strData { };

		if ( !_Authentication.RequestLibraryData( CAuthentication::CSGOX, strData ) )
			return false;

		try
		{
			jsMemory = nlohmann::json::parse( strData );
		}
		catch( nlohmann::json::parse_error& e )
		{
			_Log.Log( EPrefix::ERROR, ELocation::APPLICATION, ENC( "Unable to parse library data file." ) );
			return false;
		}

#endif

		for ( int i = MODULE_ENGINE; i != MODULE_MAX; i++ )
		{
			std::string strModule { };

			if ( !GetMemoryValue( { strModuleIdentifier, std::to_string( i ) }, strModule ) )
				return false;

			_Modules[ i ]._Module = GetModuleHandle( strModule.c_str( ) );

			if ( !_Modules[ i ].Valid( ) )
				return false;
		}

		for ( int i = INTERFACE_GLOBAL_VARS; i != INTERFACE_MAX; i++ )
		{
			if ( i == INTERFACE_CLIENT_MODE )
				continue;

			std::string strModule { }, strSignature { }, strOffset { };

			if ( !GetMemoryValue( { strPatternIdentifier, std::to_string( i ), strModuleIdentifier }, strModule )
				 || !GetMemoryValue( { strPatternIdentifier, std::to_string( i ), strSignatureIdentifier }, strSignature )
				 || !GetMemoryValue( { strPatternIdentifier, std::to_string( i ), strSignatureOffsetIdentifier }, strOffset ) )
			{
				std::string strVersion { };

				if ( !GetMemoryValue( { strVersionIdentifier, std::to_string( i ), strModuleIdentifier }, strModule )
					 || !GetMemoryValue( { strVersionIdentifier, std::to_string( i ), strVersionIdentifier }, strVersion ) )
					return false;

				if ( !_Modules[ std::stoi( strModule ) ]( strVersion.c_str( ), &pInterfaces[ i ] ) )
					return false;

				continue;
			}

			const auto _Module = _Modules[ std::stoi( strModule ) ];
			const auto ptrOffset = std::stoi( strOffset );

			if ( !_MemoryManager.AddPattern( _Module, pattern_t( strSignature, reinterpret_cast< unsigned* >( &pInterfaces[ i ] ), ptrOffset ) ) )
				return false;
		}

		for ( int i = SIGNATURE_LINE_GOES_THROUGH_SMOKE; i != SIGNATURE_MAX; i++ )
		{
			std::string strModule { }, strSignature { }, strOffset { };

			const auto _Module = _Modules[ std::stoi( strModule ) ];
			const auto ptrOffset = std::stoi( strOffset );

			if ( !_MemoryManager.AddPattern( _Module, pattern_t( strSignature, reinterpret_cast< unsigned* >( &pPointers[ i ] ), ptrOffset ) ) )
				return false;
		}

		for ( int i = FUNCTION_BEGIN_SCENE; i != FUNCTION_MAX; i++ )
		{
			std::string strFunctionIndex { };

			if ( !GetMemoryValue( { strFunctionIndexIdentifier, std::to_string( i ) }, strFunctionIndex ) )
				return false;

			uFunctionIndices[ i ] = std::stoul( strFunctionIndex );
		}
		
		if ( !_MemoryManager.FindPatterns( ) )
			return false;

		pGlobalVariables = **reinterpret_cast< CGlobalVarsBase * ** >( pGlobalVariables );
		pClientState = **reinterpret_cast< CClientState * ** >( pClientState );
		pDevice = **reinterpret_cast< IDirect3DDevice9 * ** >( pDevice );
		pGlowObjectManager = *reinterpret_cast< CGlowObjectManager * * >( pGlowObjectManager );
		pInput = *reinterpret_cast< CInput * * >( pInput );
		pMoveHelper = **reinterpret_cast< IMoveHelperServer * ** >( pMoveHelper );
		pRenderBeams = *reinterpret_cast< IViewRenderBeams * * >( pRenderBeams );
		pClientMode = **reinterpret_cast< IClientMode * ** >( ( *reinterpret_cast< std::uintptr_t * * >( pClientBase ) )[ 10 ] + 5 );

		return true;
	}

	unsigned GetFunctionIndex( EFunctions _Function )
	{
		return uFunctionIndices[ _Function ];
	}

	void * GetSignaturePointer( ESignatures _Signature )
	{
		return pPointers[ _Signature ];
	}

#if defined _DEBUG

	std::string CreateDataFile( )
	{
		nlohmann::json jsData { };
		std::string strEncryptedCreateInterface { };

		if ( !_Cryptography.Encrypt( strCreateInterface, strEncryptedCreateInterface, _Cryptography.strStaticEncryptionKey, _Cryptography.strStaticInitializationVector ) )
			return { };

		jsData[ _Cryptography.GenerateHash( strCreateInterfaceIdentifier ) ] = strEncryptedCreateInterface;

		for ( int i = MODULE_ENGINE; i != MODULE_MAX; i++ )
		{
			std::string strEncryptedModuleName { };

			if ( !_Cryptography.Encrypt( strModules[ i ], strEncryptedModuleName, _Cryptography.strStaticEncryptionKey, _Cryptography.strStaticInitializationVector ) )
				return { };

			jsData[ _Cryptography.GenerateHash( strModuleIdentifier ) ][ _Cryptography.GenerateHash( std::to_string( i ) ) ] = strEncryptedModuleName;
		}

		for ( auto& _Pattern : vecInterfacePatterns )
		{
			std::string strEncryptedModule { }, strEncryptedSignature { }, strEncryptedOffset { };

			if ( !_Cryptography.Encrypt( std::to_string( _Pattern._Module ), strEncryptedModule, _Cryptography.strStaticEncryptionKey, _Cryptography.strStaticInitializationVector )
				 || !_Cryptography.Encrypt( _Pattern.strPattern, strEncryptedSignature, _Cryptography.strStaticEncryptionKey, _Cryptography.strStaticInitializationVector )
				 || !_Cryptography.Encrypt( std::to_string( _Pattern.ptrOffset ), strEncryptedOffset, _Cryptography.strStaticEncryptionKey, _Cryptography.strStaticInitializationVector ) )
				return { };

			auto& jsPatternInfo = jsData[ _Cryptography.GenerateHash( strPatternIdentifier ) ][ _Cryptography.GenerateHash( std::to_string( _Pattern._Owner ) ) ];

			jsPatternInfo[ _Cryptography.GenerateHash( strModuleIdentifier ) ] = strEncryptedModule;
			jsPatternInfo[ _Cryptography.GenerateHash( strSignatureIdentifier ) ] = strEncryptedSignature;
			jsPatternInfo[ _Cryptography.GenerateHash( strSignatureOffsetIdentifier ) ] = strEncryptedOffset;
		}

		for ( auto& _Pattern : vecPointerPatterns )
		{
			std::string strEncryptedModule { }, strEncryptedSignature { }, strEncryptedOffset { };

			if ( !_Cryptography.Encrypt( std::to_string( _Pattern._Module ), strEncryptedModule, _Cryptography.strStaticEncryptionKey, _Cryptography.strStaticInitializationVector )
				 || !_Cryptography.Encrypt( _Pattern.strPattern, strEncryptedSignature, _Cryptography.strStaticEncryptionKey, _Cryptography.strStaticInitializationVector )
				 || !_Cryptography.Encrypt( std::to_string( _Pattern.ptrOffset ), strEncryptedOffset, _Cryptography.strStaticEncryptionKey, _Cryptography.strStaticInitializationVector ) )
				return { };

			auto& jsPatternInfo = jsData[ _Cryptography.GenerateHash( strPatternIdentifier ) ][ _Cryptography.GenerateHash( std::to_string( _Pattern._Owner ) ) ];

			jsPatternInfo[ _Cryptography.GenerateHash( strModuleIdentifier ) ] = strEncryptedModule;
			jsPatternInfo[ _Cryptography.GenerateHash( strSignatureIdentifier ) ] = strEncryptedSignature;
			jsPatternInfo[ _Cryptography.GenerateHash( strSignatureOffsetIdentifier ) ] = strEncryptedOffset;
		}

		for ( auto& _Version : vecVersions )
		{
			std::string strEncryptedModule { }, strEncryptedVersion { };

			if ( !_Cryptography.Encrypt( std::to_string( _Version._Module ), strEncryptedModule, _Cryptography.strStaticEncryptionKey, _Cryptography.strStaticInitializationVector )
				 || !_Cryptography.Encrypt( _Version.strVersion, strEncryptedVersion, _Cryptography.strStaticEncryptionKey, _Cryptography.strStaticInitializationVector ) )
				return { };

			jsData[ _Cryptography.GenerateHash( strVersionIdentifier ) ][ _Cryptography.GenerateHash( std::to_string( _Version._Interface ) ) ][ _Cryptography.GenerateHash( strModuleIdentifier ) ] = strEncryptedModule;
			jsData[ _Cryptography.GenerateHash( strVersionIdentifier ) ][ _Cryptography.GenerateHash( std::to_string( _Version._Interface ) ) ][ _Cryptography.GenerateHash( strVersionIdentifier ) ] = strEncryptedVersion;
		}

		for ( auto& _FunctionIndex : vecFunctionIndices )
		{
			std::string strEncryptedIndex { };

			if ( !_Cryptography.Encrypt( std::to_string( _FunctionIndex.second ), strEncryptedIndex, _Cryptography.strStaticEncryptionKey, _Cryptography.strStaticInitializationVector ) )
				return { };

			jsData[ _Cryptography.GenerateHash( strFunctionIndexIdentifier ) ][ _Cryptography.GenerateHash( std::to_string( _FunctionIndex.first ) ) ] = strEncryptedIndex;
		}

		return jsData.dump( 4 );
	}

#endif
}
