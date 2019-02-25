/// Hooking.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#define USE_DEFINITIONS
#include "../../Framework.hpp"

std::size_t CVirtualTableHook::GetTableSize( void **pTable )
{
	std::size_t zReturn = 0;

	while ( pTable != nullptr
			&& MEM.IsExecutableCode( pTable[ zReturn ] ) )
		zReturn++;

	return zReturn;
}

bool CVirtualTableHook::Attach( void *pAttachable )
{
	if ( !MEM.EnsureShellcodeValidity( ) )
		return false;

	pInterface = pAttachable;

	if ( pInterface == nullptr )
		return _Log.Log( EPrefix::ERROR, ELocation::HOOKING, ENC( "Invalid interface passed to Attach." ) ), false;

	pTableAddress = *reinterpret_cast< void *** >( pInterface );
	if ( pTableAddress == nullptr )
		return _Log.Log( EPrefix::ERROR, ELocation::HOOKING, ENC( "Invalid interface passed to Attach." ) ), false;

	hOrigin = MEM.GetOrigin( pTableAddress );
	if ( hOrigin == nullptr )
		return _Log.Log( EPrefix::ERROR, ELocation::HOOKING, ENC( "Unable to find module of origin for table." ) ), false;

	zLength = GetTableSize( pTableAddress );
	if ( zLength == 0 )
		return _Log.Log( EPrefix::ERROR, ELocation::HOOKING, ENC( "Invalid interface passed to Attach." ) ), false;

	zSize = zLength * sizeof( void * );
#if defined _DEBUG
	pCurrentTable = new void*[ zLength ];
#else
	pCurrentTable = reinterpret_cast< void ** >( MEM.FindFreeMemory( hOrigin, zSize, PAGE_READWRITE ) );
#endif
	if ( pCurrentTable == nullptr )
		return _Log.Log( EPrefix::ERROR, ELocation::HOOKING, ENC( "Failed to find free memory for table." ) ), false;

	for ( auto z = 0u; z < zLength; z++ )
		pCurrentTable[ z ] = pTableAddress[ z ];

	*reinterpret_cast< void ** >( pInterface ) = pCurrentTable;
	return bAttached = true;
}

void CVirtualTableHook::Detach( )
{
	if ( bAttached )
	{
		*reinterpret_cast< void ** >( pInterface ) = pOldTable;
#if !defined _DEBUG
		for ( auto z = 0u; z < zLength; z++ )
			if ( pOldTable[ z ] != pCurrentTable[ z ] )
				memset( pCurrentTable[ z ], 0, zTrampolineStub );
#endif
		memset( pCurrentTable, 0, zSize );
		*this = CVirtualTableHook( );
	}

	bAttached = false;
}

bool CVirtualTableHook::Replace( std::size_t zIndex, void *pReplacement )
{
	if ( zIndex > zLength )
		return _Log.Log( EPrefix::WARNING, ELocation::HOOKING, ENC( "Invalid index for replacing a function." ) ), false;

	if ( pReplacement == nullptr )
		return _Log.Log( EPrefix::WARNING, ELocation::HOOKING, ENC( "Invalid function address to replace with." ) ), false;

#if defined _DEBUG
	const auto pRealReplacement = pReplacement;
#else
	const auto pRealReplacement = MEM.FindFreeMemory( hOrigin, zTrampolineStub, PAGE_EXECUTE_READWRITE, pLastStubLocation );
	auto bFound = false;

	pLastStubLocation = reinterpret_cast< void * >( std::uintptr_t( pRealReplacement ) + zTrampolineStub );
	memcpy( pRealReplacement, bTrampolineStub, zTrampolineStub );
	for ( auto z = 0u; z < zTrampolineStub && !bFound; z++ )
		if ( *reinterpret_cast< unsigned char * >( std::uintptr_t( pRealReplacement ) + z ) == 0xCC )
			*reinterpret_cast< void ** >( std::uintptr_t( pRealReplacement ) + z ) = pReplacement, bFound = true;

	if ( !bFound )
		return _Log.Log( EPrefix::ERROR, ELocation::HOOKING, ENC( "Unable to replace function in stub." ) ), false;
#endif

	return pCurrentTable[ zIndex ] = pRealReplacement, true;
}

bool CVirtualTableHook::Replace( void *pReplacee, void *pReplacement )
{
	if ( pReplacement == nullptr )
		return _Log.Log( EPrefix::WARNING, ELocation::HOOKING, ENC( "Invalid function address to replace with." ) ), false;

	for ( auto z = 0u; z < zLength; z++ )
		if ( pTableAddress[ z ] == pReplacee )
			return Replace( z, pReplacement );

	return false;
}

void *CVirtualTableHook::GetOriginalFunction( std::size_t zIndex )
{
	if ( zIndex > zLength )
		return _Log.Log( EPrefix::WARNING, ELocation::HOOKING, ENC( "Invalid index for replacing a function." ) ), nullptr;

	return pTableAddress[ zIndex ];
}

bool CImportHook::PatchAddress( void **pAddress, void *pValue )
{
	DWORD dwOld;
	if ( VirtualProtect( pAddress, sizeof( void * ), PAGE_READWRITE, &dwOld ) == FALSE )
		return LOG( ERROR, HOOKING, "Unable to virtual protect address for writing." ), false;

	*pAddress = pValue;
	return VirtualProtect( pAddress, sizeof( IMAGE_THUNK_DATA ), dwOld, &dwOld ) != FALSE;
}

bool CImportHook::Attach( HMODULE hImportee )
{
	return bAttached = ( _Importee = image_info_t( hImportee ) ).ValidImage( );
}

bool CImportHook::Detach( )
{
	auto bReturn = true;

	if ( bAttached )
	{
		bReturn &= RevertAllPatches( );
		*this = CImportHook( );
	}

	bAttached = false;
	return bReturn;
}

bool CImportHook::PatchImport( HMODULE hExporter, const std::string &strImportName, void *pPatch )
{
	if ( !bAttached )
		return LOG( WARNING, HOOKING, "Attempting to patch import without attaching to a module beforehand." ), false;

	auto _Origin = image_info_t( hExporter );

	if ( !_Origin.ValidImage( )
		 || !_Importee.ValidImage( ) )
		return LOG( WARNING, HOOKING, "Invalid image(s) passed to PatchImport." ), false;

	const auto pImportData = _Importee.FindImport( hExporter, strImportName );
	if ( pImportData == nullptr )
		return LOG( WARNING, HOOKING, "Unable to find import data of import %s.", strImportName.c_str( ) ), false;

	auto pSearch = _Patches.find( hExporter );
	if ( pSearch == _Patches.end( ) )
		_Patches.insert( { hExporter, { } } ), pSearch = _Patches.find( hExporter );

	pSearch->second.emplace_back( patched_import_t { strImportName, reinterpret_cast< void ** >( &pImportData->u1.Function ), reinterpret_cast< void * >( pImportData->u1.Function ) } );
	return PatchAddress( reinterpret_cast< void ** >( &pImportData->u1.Function ), pPatch );
}

void *CImportHook::GetOriginalImport( HMODULE hExporter, const std::string &strImportName )
{
	if ( !bAttached )
		return LOG( WARNING, HOOKING, "Attempting to get original import without attaching to a module beforehand." ), nullptr;

	const auto pSearch = _Patches.find( hExporter );
	if ( pSearch == _Patches.end( ) )
		return nullptr;

	for ( auto &_Patch : pSearch->second )
		if ( _Patch.strImport == strImportName )
			return _Patch.pOriginal;

	return nullptr;
}

bool CImportHook::RevertPatch( HMODULE hExporter, const std::string &strImportName )
{
	if ( !bAttached )
		return LOG( WARNING, HOOKING, "Attempting to revert patch without attaching to a module beforehand." ), nullptr;

	const auto pSearch = _Patches.find( hExporter );
	if ( pSearch == _Patches.end( ) )
		return false;

	for ( auto u = 0u; u < pSearch->second.size( ); u++ )
		if ( pSearch->second[ u ].strImport == strImportName )
		{
			if ( !PatchAddress( pSearch->second[ u ].pPatchedFunction, pSearch->second[ u ].pOriginal ) )
				return false;

			return pSearch->second.erase( pSearch->second.begin( ) + u ), true;
		}

	return false;
}

bool CImportHook::RevertAllPatches( )
{
	if ( !bAttached )
		return LOG( WARNING, HOOKING, "Attempting to revert all patches without attaching to a module beforehand." ), nullptr;

	for ( auto &_Patch : _Patches )
	{
		for ( auto &__Patch : _Patch.second )
			if ( !PatchAddress( __Patch.pPatchedFunction, __Patch.pOriginal ) )
				return false;

		_Patch.second.clear( );
	}

	return true;
}

DWORD ExceptionHandler( EXCEPTION_POINTERS *pRecord )
{
	switch( pRecord->ExceptionRecord->ExceptionCode )
	{
		case STATUS_GUARD_PAGE_VIOLATION:
		{
			for ( auto &_Hook : CExceptionHook::vecHooks )
				if ( std::uintptr_t( _Hook.first ) == pRecord->ContextRecord->Eip )
				{
					pRecord->ContextRecord->Eip = std::uintptr_t( _Hook.second );
					break;
				}

			return pRecord->ContextRecord->EFlags |= CExceptionHook::STEP_OVER, EXCEPTION_CONTINUE_EXECUTION;
		}

		case STATUS_SINGLE_STEP:
		{
			DWORD dwBuffer;
			if ( VirtualProtect( reinterpret_cast< void * >( pRecord->ContextRecord->Eip ), 1, CExceptionHook::PROTECTION, &dwBuffer ) == FALSE )
				LOG( ERROR, HOOKING, "Unable to re-guard page." );

			return EXCEPTION_CONTINUE_EXECUTION;
		}

		default:
			return EXCEPTION_CONTINUE_SEARCH;
	}
}

bool CExceptionHook::AddHandler( )
{
	if ( pHandlerHandle != nullptr )
		return true;

	if ( ( pHandlerHandle = AddVectoredExceptionHandler( 1, PVECTORED_EXCEPTION_HANDLER( ExceptionHandler ) ) ) == nullptr )
		return LOG( ERROR, HOOKING, "Unable to add exception handler." ), false;

	return true;
}

bool CExceptionHook::RemoveHandler( )
{
	if ( pHandlerHandle == nullptr )
		return true;

	if ( RemoveVectoredExceptionHandler( pHandlerHandle ) == FALSE )
		LOG( ERROR, HOOKING, "Unable to remove exception handler." );
	else
		pHandlerHandle = nullptr;

	return pHandlerHandle == nullptr;
}

bool CExceptionHook::Attach( void *pFunction, void *pCallback )
{
	if ( !AddHandler( ) )
		return false;

	for ( auto &_Hook : vecHooks )
		if ( _Hook.first == pFunction )
			return false;

	if ( VirtualProtect( pFunction, 1, PROTECTION, &dwOldProtection ) == FALSE )
		return LOG( ERROR, HOOKING, "Unable to protect function with PAGE_GUARD." ), false;

	pProtectedArea = pFunction;
	vecHooks.emplace_back( std::pair< void *, void * >( pProtectedArea, pCallback ) );
	return true;
}

bool CExceptionHook::Detach( )
{
	if ( VirtualProtect( pProtectedArea, 1, dwOldProtection, &dwOldProtection ) == FALSE )
		return LOG( ERROR, HOOKING, "Unable to restore page protection." ), false;

	for ( auto u = 0u; u < vecHooks.size( ); u++ )
		if ( vecHooks[ u ].second == pHook )
			return vecHooks.erase( vecHooks.begin( ) + u ), *this = CExceptionHook( ), true;

	return false;
}

void *__stdcall FindHook( void *pFunction )
{
	const auto pSearch = CPatchHook::_PatchedFunctions.find( reinterpret_cast< void * >( std::uintptr_t( pFunction ) - CPatchHook::CALL_SIZE ) );
	if ( pSearch == CPatchHook::_PatchedFunctions.end( ) )
		return nullptr;

	return pSearch->second;
}

void __declspec( naked ) HookProxy( )
{
	__asm
	{
		call	FindHook
		cmp		eax, 0
		jnz		JumpToHook
		ret		// mega crash

		JumpToHook:

			jmp		eax
	}
}

bool CPatchHook::Patch( void *pFunction, void *pHook )
{
	if ( bPatched )
		return true;

	const auto pRelative = reinterpret_cast< void * >( std::uintptr_t( HookProxy ) - ( std::uintptr_t( pFunction ) + CALL_SIZE ) );
	DWORD dwOld;

	if ( VirtualProtect( pFunction, CALL_SIZE, PAGE_EXECUTE_READWRITE, &dwOld ) == FALSE )
		return LOG( ERROR, HOOKING, "Unable to protect function to patch." ), false;

	vecOldBytes.resize( CALL_SIZE );
	memcpy( &vecOldBytes[ 0 ], pFunction, CALL_SIZE );
	*reinterpret_cast< unsigned char* >( pFunction ) = CALL_OPCODE;
	*reinterpret_cast< void ** >( std::uintptr_t( pFunction ) + sizeof( unsigned char ) ) = pRelative;

	bPatched = VirtualProtect( pFunction, CALL_SIZE, dwOld, &dwOld ) != FALSE;
	if ( bPatched )
		_PatchedFunctions.insert( { pFunction, pHook } );

	pPatchedData = pFunction;
	return bPatched;
}

bool CPatchHook::Unpatch( )
{
	if ( !bPatched )
		return true;

	DWORD dwOld;

	if ( VirtualProtect( pPatchedData, CALL_SIZE, PAGE_EXECUTE_READWRITE, &dwOld ) == FALSE )
		return LOG( ERROR, HOOKING, "Unable to protect function to patch." ), false;

	memcpy( pPatchedData, &vecOldBytes[ 0 ], CALL_SIZE );
	return ( bPatched = !( VirtualProtect( pPatchedData, CALL_SIZE, dwOld, &dwOld ) != FALSE ) ) == false;
}
