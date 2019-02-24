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
		return _Log.Log( EPrefix::ERROR, ELocation::HOOKING, ENC( "Unable to fild module of origin for table." ) ), false;

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
		if ( reinterpret_cast< unsigned char * >( std::uintptr_t( pRealReplacement ) + z ) == 0xCC )
			*reinterpret_cast< void ** >( std::uintptr_t( pRealReplacement ) + z ) = pReplacement, bFound = true;

	if ( !bFound )
		return _Log.Log( EPrefix::ERROR, ELocation::WARNING, ENC( "Unable to replace function in stub." ) ), false;
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
	return ( _Importee = image_info_t( hImportee ) ).ValidImage( );
}

bool CImportHook::Detach( )
{
	const auto bReturn = RevertAllPatches( );
	*this = CImportHook( );
	return bReturn;
}

bool CImportHook::PatchImport( HMODULE hExporter, const std::string &strImportName, void *pPatch )
{
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
	for ( auto &_Patch : _Patches )
	{
		for ( auto &__Patch : _Patch.second )
			if ( !PatchAddress( __Patch.pPatchedFunction, __Patch.pOriginal ) )
				return false;

		_Patch.second.clear( );
	}

	return true;
}
