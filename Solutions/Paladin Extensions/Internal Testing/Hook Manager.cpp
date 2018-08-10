/// Hook Manager.cpp

#include "Internal Testing.hpp"

namespace PX::Tools
{
	std::size_t PX_API EstimateTableLength( ptr_t* pVirtualTable )
	{
		auto uReturn = 0u;
		MEMORY_BASIC_INFORMATION mbiTable { };
		for ( ; VirtualQuery( reinterpret_cast<LPCVOID>( pVirtualTable[ uReturn ] ), &mbiTable, sizeof mbiTable ) &&
			  mbiTable.BaseAddress != nullptr &&
			  mbiTable.Type != NULL &&
			  mbiTable.Protect & ( PAGE_EXECUTE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY ) &&
			  !( mbiTable.Protect & ( PAGE_GUARD | PAGE_NOACCESS ) ); uReturn++ ) { }
		return uReturn;
	}

	ptr_t FindFreeMemory( HMODULE hLocation, std::size_t sMinimumSize )
	{
		const auto ptrModuleEnd = reinterpret_cast< ptr_t  >( hLocation ) + reinterpret_cast< PIMAGE_NT_HEADERS > ( reinterpret_cast< std::uint8_t* >( hLocation ) + reinterpret_cast< PIMAGE_DOS_HEADER > ( hLocation )->e_lfanew )->OptionalHeader.SizeOfImage;
		
		for( auto ptrAddress = ptrModuleEnd; ptrAddress > ptr_t( hLocation ); ptrAddress -= sizeof( ptr_t ) )
		{
			MEMORY_BASIC_INFORMATION mbiPage;
			if ( VirtualQuery( reinterpret_cast< LPCVOID >( ptrAddress ), &mbiPage, sizeof mbiPage ) == NULL ||
				 mbiPage.AllocationBase == nullptr ||
				 mbiPage.BaseAddress == nullptr ||
				 !( mbiPage.State & MEM_COMMIT ) ||
				 mbiPage.Protect & ( PAGE_GUARD | PAGE_NOACCESS ) ||
				 !( mbiPage.Protect & ( PAGE_EXECUTE_READWRITE | PAGE_READWRITE ) ) ||
				 mbiPage.RegionSize < sMinimumSize )
				continue;

			auto bMemoryInUse = false;
			auto uPageCount = 0u;
			while( uPageCount < sMinimumSize && !bMemoryInUse )
			{
				uPageCount += sizeof( ptr_t );
				if ( *reinterpret_cast< ptr_t* >( ptrAddress + uPageCount ) )
					bMemoryInUse = true;
			}

			if ( !bMemoryInUse && uPageCount >= sMinimumSize )
				return ptrAddress;
		}
		return 0u;
	}

	hook_t::hook_t( void* pVirtualTable, const wchar_t* wszAllocationModule ):
		dwOldProtection( 0u ), sTableLength( 0u ), sTableSize( 0u ), pClassBase( pVirtualTable ), pOldTable( nullptr ), pNewTable( nullptr ), hAllocationModule( HMODULE( ) ), bSetNewTable( false )
	{
		// Ensure that we are hooking a valid virtual table and that the length is valid( there are proper permissions to read and write to it ).
		// Set the address of pOldTable to the address of the first virtual function.
		if ( !px_assert( pClassBase != nullptr ) || 
			!px_assert( ( sTableLength = EstimateTableLength( pOldTable = reinterpret_cast< ptr_t** >( pClassBase )[ 0 ] ) ) > 0 ) )
			return;

		// Get the size of the table in bytes.
		sTableSize = sTableLength * sizeof( ptr_t );
		// Ensure that the module that has been entered is valid and find free memory inside of that module to point the class base to.
		if ( !px_assert( ( hAllocationModule = GetModuleHandle( wszAllocationModule ) ) != nullptr ) ||
			 !px_assert( ( pNewTable = reinterpret_cast< ptr_t* >( FindFreeMemory( hAllocationModule, sTableSize + sizeof( ptr_t ) ) ) ) != nullptr ) )
			return;

		// Copy the addresses of the old table to the new table so the functions can still be accessed as normal.
		memcpy( pNewTable, pOldTable, sTableSize );

		// Set the permissions of the memory we found so that it is readable and writable, and store the old protection.
		// This is also used just to ensure that we have permission to modify the memory.
		if ( !px_assert( VirtualProtect( pClassBase, sTableSize, PAGE_READWRITE, &dwOldProtection ) ) )
		{
			Cleanup( );
			return;
		}

		// Set the address of the class base to the new table.
		reinterpret_cast< ptr_t** >( pClassBase )[ 0 ] = &pNewTable[ 0 ];
		bSetNewTable = true;
	}

	hook_t::~hook_t( )
	{
		Cleanup( );
	}

	void hook_t::UnhookIndex( unsigned uIndex )
	{
		if ( uIndex >= 0 && uIndex < sTableLength )
			pNewTable[ uIndex ] = pOldTable[ uIndex ];
	}

	void hook_t::ResetTable( )
	{
		memcpy( pNewTable, pOldTable, sTableSize );
	}

	void hook_t::Cleanup( )
	{
		// Reset the virtual function address array first, before we set the memory to 0 in case that function is called between and causes a crash.
		if ( bSetNewTable )
			reinterpret_cast< ptr_t** >( pClassBase )[ 0 ] = &pOldTable[ 0 ];

		memset( pNewTable, 0, sTableSize );
		DWORD dwBuffer;
		VirtualProtect( pClassBase, sTableSize, dwOldProtection, &dwBuffer );
	}
}
