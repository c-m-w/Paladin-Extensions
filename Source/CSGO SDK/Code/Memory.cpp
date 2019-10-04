/// Memory.cpp

#include "CSGO SDK.hpp"
#include <wingdi.h>
#include <wingdi.h>
#include <wingdi.h>

namespace Memory
{
	nlohmann::json jsMemory { };

	bool GetMemoryValue( std::initializer_list< std::string > initLevels, std::string &strOut )
	{
		auto jsSearch = jsMemory;

		for ( auto &strLevel: initLevels )
			jsSearch = jsSearch[ _Cryptography.GenerateHash( strLevel ) ];

		try
		{
			if ( !_Cryptography.Decrypt( jsSearch.get< std::string >( ), strOut, _Cryptography.strStaticEncryptionKey, _Cryptography.strStaticInitializationVector ) )
				return false;
		}
		catch ( nlohmann::json::type_error &e )
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

	bool FindNetworkedVariables( )
	{
		std::function< networked_variable_table_t( RecvTable *pTable ) > fnParseTable = [ & ]( RecvTable *pTable )
		{
			networked_variable_table_t _Current( pTable->m_pNetTableName );

			for ( auto i = 0; i < pTable->m_nProps; i++ )
			{
				const auto pProp = &pTable->m_pProps[ i ];
				if ( nullptr == pProp
					|| std::isdigit( pProp->m_pVarName[ 0 ] )
					|| !strcmp( pProp->m_pVarName, ENC( "baseclass" ) ) )
					continue;
				if ( pProp->m_RecvType == DPT_DataTable && pProp->m_pDataTable != nullptr )
				{
					_Current.vecChildTables.emplace_back( fnParseTable( pProp->m_pDataTable ) );
					_Current.vecChildTables.back( ).ptrOffset = pProp->m_Offset;
					_Current.vecChildTables.back( ).pProp = pProp;
				}
				else
					_Current.vecChildProps.emplace_back( pProp );
			}

			return _Current;
		};

		for ( auto pClass = pClientBase->GetAllClasses( ); nullptr != pClass; pClass = pClass->m_pNext )
			if ( pClass->m_pRecvTable )
				vecNetworkedVariables.push_back( fnParseTable( pClass->m_pRecvTable ) );

		return !vecNetworkedVariables.empty( );
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
			std::string strModule { }, strSignature { }, strOffset { };

			if ( !GetMemoryValue( { strInterfacePatternIdentifier, std::to_string( i ), strModuleIdentifier }, strModule )
				|| !GetMemoryValue( { strInterfacePatternIdentifier, std::to_string( i ), strSignatureIdentifier }, strSignature )
				|| !GetMemoryValue( { strInterfacePatternIdentifier, std::to_string( i ), strSignatureOffsetIdentifier }, strOffset ) )
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

			if ( !_MemoryManager.AddPattern( _Module, pattern_t( strSignature, &pInterfaces[ i ], ptrOffset ) ) )
				return false;
		}

		for ( int i = SIGNATURE_LINE_GOES_THROUGH_SMOKE; i != SIGNATURE_MAX; i++ )
		{
			std::string strModule { }, strSignature { }, strOffset { };

			if ( !GetMemoryValue( { strPointerPatternIdentifier, std::to_string( i ), strModuleIdentifier }, strModule )
				|| !GetMemoryValue( { strPointerPatternIdentifier, std::to_string( i ), strSignatureIdentifier }, strSignature )
				|| !GetMemoryValue( { strPointerPatternIdentifier, std::to_string( i ), strSignatureOffsetIdentifier }, strOffset ) )
				return false;

			const auto _Module = _Modules[ std::stoi( strModule ) ];
			const auto ptrOffset = std::stoi( strOffset );

			if ( !_MemoryManager.AddPattern( _Module, pattern_t( strSignature, &pPointers[ i ], ptrOffset ) ) )
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

		pGlobalVariables = **reinterpret_cast< CGlobalVarsBase*** >( pInterfaces[ INTERFACE_GLOBAL_VARS ] );
		pClientState = **reinterpret_cast< CClientState*** >( pInterfaces[ INTERFACE_CLIENT_STATE ] );
		pDevice = **reinterpret_cast< IDirect3DDevice9*** >( pInterfaces[ INTERFACE_DEVICE ] );
		pClientBase = reinterpret_cast< IBaseClientDLL* >( pInterfaces[ INTERFACE_CLIENT_BASE ] );
		pClientMode = *reinterpret_cast< IClientMode ** >( pInterfaces[ INTERFACE_CLIENT_MODE ] );
		pGlowObjectManager = *reinterpret_cast< CGlowObjectManager** >( pInterfaces[ INTERFACE_GLOW_OBJECT_MANAGER ] );
		pInputSystem = reinterpret_cast< IInputSystem* >( pInterfaces[ INTERFACE_INPUT_SYSTEM ] );
		pEngineClient = reinterpret_cast< IVEngineClient* >( pInterfaces[ INTERFACE_ENGINE_CLIENT ] );
		pSurface = reinterpret_cast< ISurface* >( pInterfaces[ INTERFACE_SURFACE ] );
		pPanel = reinterpret_cast< IPanel* >( pInterfaces[ INTERFACE_PANEL ] );
		pEntityList = reinterpret_cast< IClientEntityList* >( pInterfaces[ INTERFACE_ENTITY_LIST ] );
		pEngineTrace = reinterpret_cast< IEngineTrace* >( pInterfaces[ INTERFACE_ENGINE_TRACE ] );
		pModelInfo = reinterpret_cast< IVModelInfoClient* >( pInterfaces[ INTERFACE_MODEL_INFO ] );
		pInput = *reinterpret_cast< CInput** >( pInterfaces[ INTERFACE_INPUT ] );
		pModelRender = reinterpret_cast< IVModelRender* >( pInterfaces[ INTERFACE_MODEL_RENDER ] );
		pMaterialSystem = reinterpret_cast< IMaterialSystem* >( pInterfaces[ INTERFACE_MATERIAL_SYSTEM ] );
		pEngineRenderView = reinterpret_cast< IVRenderView* >( pInterfaces[ INTERFACE_ENGINE_RENDER_VIEW ] );
		pConVar = reinterpret_cast< ICvar* >( pInterfaces[ INTERFACE_CONVAR ] );
		pLocalize = reinterpret_cast< ILocalize* >( pInterfaces[ INTERFACE_LOCALIZE ] );
		pEvents = reinterpret_cast< IGameEventManager2* >( pInterfaces[ INTERFACE_EVENTS ] );
		pMoveHelper = **reinterpret_cast< IMoveHelperServer*** >( pInterfaces[ INTERFACE_MOVE_HELPER ] );
		pGameMovement = reinterpret_cast< IGameMovement* >( pInterfaces[ INTERFACE_GAME_MOVEMENT ] );
		pPrediction = reinterpret_cast< IPrediction* >( pInterfaces[ INTERFACE_PREDICTION ] );
		pEngineSound = reinterpret_cast< IEngineSound* >( pInterfaces[ INTERFACE_ENGINE_SOUND ] );
		pRenderBeams = *reinterpret_cast< IViewRenderBeams** >( pInterfaces[ INTERFACE_RENDER_BEAMS ] );
		pFileSystem = reinterpret_cast< IFileSystem* >( pInterfaces[ INTERFACE_FILE_SYSTEM ] );

		return FindNetworkedVariables( );
	}

	unsigned GetFunctionIndex( EFunctions _Function )
	{
		return uFunctionIndices[ _Function ];
	}

	void *GetSignaturePointer( ESignatures _Signature )
	{
		return pPointers[ _Signature ];
	}

	std::uintptr_t FindOffset( networked_variable_table_t &_Table, const char *szVariable )
	{
		for ( auto &pProp: _Table.vecChildProps )
			if ( !strcmp( pProp->m_pVarName, szVariable ) )
				return _Table.ptrOffset + pProp->m_Offset;

		for ( networked_variable_table_t pChild: _Table.vecChildTables )
		{
			auto ptrPropOffset = FindOffset( pChild, szVariable );
			if ( ptrPropOffset != 0 )
				return _Table.ptrOffset + ptrPropOffset;
		}

		for ( auto &pChild: _Table.vecChildTables )
			if ( !strcmp( pChild.pProp->m_pVarName, szVariable ) )
				return _Table.ptrOffset + pChild.ptrOffset;

		return 0u;
	}

	std::uintptr_t FindOffset( const char *szTable, const char *szVariable )
	{
		for each ( auto pTable in vecNetworkedVariables )
			if ( !strcmp( pTable.szName, szTable ) )
			{
				const auto ptrResult = FindOffset( pTable, szVariable );
				if ( 0u != ptrResult )
					return ptrResult;
			}

		return 0u;
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

		for ( auto &_Pattern: vecInterfacePatterns )
		{
			std::string strEncryptedModule { }, strEncryptedSignature { }, strEncryptedOffset { };

			if ( !_Cryptography.Encrypt( std::to_string( _Pattern._Module ), strEncryptedModule, _Cryptography.strStaticEncryptionKey, _Cryptography.strStaticInitializationVector )
				|| !_Cryptography.Encrypt( _Pattern.strPattern, strEncryptedSignature, _Cryptography.strStaticEncryptionKey, _Cryptography.strStaticInitializationVector )
				|| !_Cryptography.Encrypt( std::to_string( _Pattern.ptrOffset ), strEncryptedOffset, _Cryptography.strStaticEncryptionKey, _Cryptography.strStaticInitializationVector ) )
				return { };

			auto &jsPatternInfo = jsData[ _Cryptography.GenerateHash( strInterfacePatternIdentifier ) ][ _Cryptography.GenerateHash( std::to_string( _Pattern._Owner ) ) ];

			jsPatternInfo[ _Cryptography.GenerateHash( strModuleIdentifier ) ] = strEncryptedModule;
			jsPatternInfo[ _Cryptography.GenerateHash( strSignatureIdentifier ) ] = strEncryptedSignature;
			jsPatternInfo[ _Cryptography.GenerateHash( strSignatureOffsetIdentifier ) ] = strEncryptedOffset;
		}

		for ( auto &_Pattern: vecPointerPatterns )
		{
			std::string strEncryptedModule { }, strEncryptedSignature { }, strEncryptedOffset { };

			if ( !_Cryptography.Encrypt( std::to_string( _Pattern._Module ), strEncryptedModule, _Cryptography.strStaticEncryptionKey, _Cryptography.strStaticInitializationVector )
				|| !_Cryptography.Encrypt( _Pattern.strPattern, strEncryptedSignature, _Cryptography.strStaticEncryptionKey, _Cryptography.strStaticInitializationVector )
				|| !_Cryptography.Encrypt( std::to_string( _Pattern.ptrOffset ), strEncryptedOffset, _Cryptography.strStaticEncryptionKey, _Cryptography.strStaticInitializationVector ) )
				return { };

			auto &jsPatternInfo = jsData[ _Cryptography.GenerateHash( strPointerPatternIdentifier ) ][ _Cryptography.GenerateHash( std::to_string( _Pattern._Owner ) ) ];

			jsPatternInfo[ _Cryptography.GenerateHash( strModuleIdentifier ) ] = strEncryptedModule;
			jsPatternInfo[ _Cryptography.GenerateHash( strSignatureIdentifier ) ] = strEncryptedSignature;
			jsPatternInfo[ _Cryptography.GenerateHash( strSignatureOffsetIdentifier ) ] = strEncryptedOffset;
		}

		for ( auto &_Version: vecVersions )
		{
			std::string strEncryptedModule { }, strEncryptedVersion { };

			if ( !_Cryptography.Encrypt( std::to_string( _Version._Module ), strEncryptedModule, _Cryptography.strStaticEncryptionKey, _Cryptography.strStaticInitializationVector )
				|| !_Cryptography.Encrypt( _Version.strVersion, strEncryptedVersion, _Cryptography.strStaticEncryptionKey, _Cryptography.strStaticInitializationVector ) )
				return { };

			jsData[ _Cryptography.GenerateHash( strVersionIdentifier ) ][ _Cryptography.GenerateHash( std::to_string( _Version._Interface ) ) ][ _Cryptography.GenerateHash( strModuleIdentifier ) ] = strEncryptedModule;
			jsData[ _Cryptography.GenerateHash( strVersionIdentifier ) ][ _Cryptography.GenerateHash( std::to_string( _Version._Interface ) ) ][ _Cryptography.GenerateHash( strVersionIdentifier ) ] = strEncryptedVersion;
		}

		for ( auto &_FunctionIndex: vecFunctionIndices )
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
