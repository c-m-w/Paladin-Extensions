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
	pCurrentTable = reinterpret_cast< void ** >( MEM.FindFreeMemory( hOrigin, zSize, PAGE_READWRITE ) );
	if ( pCurrentTable == nullptr )
		return _Log.Log( EPrefix::ERROR, ELocation::HOOKING, ENC( "Failed to find free memory for table." ) ), false;

	memcpy( pTableAddress, pCurrentTable, zSize );
	*reinterpret_cast< void ** >( pInterface ) = pCurrentTable;
	return bAttached = true;
}

void CVirtualTableHook::Detach( )
{
	if ( bAttached )
	{
		*reinterpret_cast< void ** >( pInterface ) = pOldTable;
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
