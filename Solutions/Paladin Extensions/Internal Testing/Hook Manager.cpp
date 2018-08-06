/// Hook Manager.cpp

#include "Internal Testing.hpp"
#include "../../../../../../../../Program Files (x86)/Windows Kits/10/Include/10.0.14393.0/um/processthreadsapi.h"

namespace PX::Tools
{
	std::size_t PX_API EstimateTableLength( Types::ptr_t* pVirtualTable )
	{
		auto uReturn = 0u;
		MEMORY_BASIC_INFORMATION mbiTable { };
		for ( ; VirtualQuery( reinterpret_cast<LPCVOID>( pVirtualTable[ uReturn ] ), &mbiTable, sizeof mbiTable )
			  && ( mbiTable.Protect == PAGE_EXECUTE_READ || mbiTable.Protect == PAGE_EXECUTE_READWRITE ); uReturn++ ) { }
		return uReturn;
	}

	Types::ptr_t FindFreeMemory( HMODULE hLocation, std::size_t sMinimumSize )
	{
		auto fnValidateMemory = [ = ]( Types::ptr_t ptrAddress )
		{
			MEMORY_BASIC_INFORMATION mbiPage;
			return VirtualQuery( reinterpret_cast< LPCVOID >( ptrAddress ), &mbiPage, sizeof mbiPage ) &&
				mbiPage.AllocationBase != nullptr &&
				mbiPage.BaseAddress != nullptr &&
				mbiPage.State & MEM_COMMIT &&
				!( mbiPage.Protect & ( PAGE_GUARD | PAGE_NOACCESS ) ) &&
				mbiPage.Protect & ( PAGE_EXECUTE_READWRITE | PAGE_READWRITE ) &&
				mbiPage.RegionSize >= sMinimumSize;
		};

		const auto ptrModuleEnd = reinterpret_cast< Types::ptr_t  >( hLocation ) + reinterpret_cast< PIMAGE_NT_HEADERS > ( reinterpret_cast< std::uint8_t* >( hLocation ) + reinterpret_cast< PIMAGE_DOS_HEADER > ( hLocation )->e_lfanew )->OptionalHeader.SizeOfImage - sizeof( Types::ptr_t );
		int iSize = ptrModuleEnd - Types::ptr_t( hLocation );

		for( auto ptrAddress = ptrModuleEnd; ptrAddress > Types::ptr_t( hLocation ); ptrAddress -= sizeof( Types::ptr_t ) )
		{
			if ( !fnValidateMemory( ptrAddress ) )
				continue;

			auto bEmptyMemory = true;
			auto uPageCount = 0u;
			while( uPageCount < sMinimumSize && bEmptyMemory )
			{
				uPageCount += sizeof( Types::ptr_t );
				if ( *reinterpret_cast< Types::ptr_t* >( ptrAddress + uPageCount ) )
					bEmptyMemory = false;
			}

			if ( bEmptyMemory && uPageCount >= sMinimumSize )
				return ptrAddress;
		}

		return 0u;
	}

	hook_t::hook_t( void* pVirtualTable, const wchar_t* wszAllocationModule ):
		dwOldProtection( 0u ), sTableLength( 0u ), sTableSize( 0u ), pClassBase( pVirtualTable ), pOldTable( nullptr ), pNewTable( nullptr ), hAllocationModule( HMODULE( ) ), bSetNewTable( false )
	{
		if ( !dbg::Assert( pClassBase != nullptr ) )
			return;

		if ( !dbg::Assert( ( sTableLength = EstimateTableLength( pOldTable = *reinterpret_cast< Types::ptr_t** >( pClassBase ) ) ) > 0 ) )
			return;

		sTableSize = sTableLength * sizeof( Types::ptr_t );
		if ( !dbg::Assert( ( hAllocationModule = GetModuleHandle( wszAllocationModule ) ) != nullptr ) ||
			 !dbg::Assert( ( pNewTable = reinterpret_cast< Types::ptr_t* >( FindFreeMemory( hAllocationModule, sTableSize + sizeof( Types::ptr_t ) ) ) ) != nullptr ) )
			return;

		memcpy( pNewTable, pOldTable, sTableSize );

		if ( !dbg::Assert( VirtualProtect( pClassBase, sTableSize, PAGE_READWRITE, &dwOldProtection ) ) )
		{
			Cleanup( );
			return;
		}

		*reinterpret_cast< Types::ptr_t** >( pClassBase ) = &pNewTable[ 0 ];
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

	void hook_t::Cleanup( )
	{
		memset( pNewTable, 0, sTableSize );
		DWORD dwBuffer;
		VirtualProtect( pClassBase, sTableSize, dwOldProtection, &dwBuffer );

		if ( bSetNewTable )
			*reinterpret_cast< Types::ptr_t** >( pClassBase ) = &pOldTable[ 0 ];
	}
}
