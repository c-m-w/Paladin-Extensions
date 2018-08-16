/// Tools.cpp

#include "../PX Framework.hpp"

using namespace PX::Files;

namespace PX::Tools
{
	PX_SDK std::vector< HMODULE > vecModules;

	bool PX_API FindModules( )
	{
		constexpr auto sMaxModules = 1024u;
		DWORD dwMemoryNeeded;

		vecModules.resize( sMaxModules );
		if ( EnumProcessModules( GetCurrentProcess( ), &vecModules[ 0 ], sMaxModules * sizeof( HMODULE ), &dwMemoryNeeded ) == FALSE )
			return false;
		vecModules.erase( vecModules.begin( ) + dwMemoryNeeded / sizeof( HMODULE ), vecModules.end( ) );
		return true;
	}

	std::size_t PX_API EstimateTableLength( ptr_t* pVirtualTable )
	{
		auto uReturn = 0u;
		MEMORY_BASIC_INFORMATION mbiTable { };
		for ( ; VirtualQuery( reinterpret_cast<LPCVOID>( pVirtualTable[ uReturn ] ), &mbiTable, sizeof mbiTable ) &&
			  mbiTable.BaseAddress != nullptr &&
			  mbiTable.Type != NULL &&
			  mbiTable.Protect & ( PAGE_EXECUTE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY ) &&
			  !( mbiTable.Protect & ( PAGE_GUARD | PAGE_NOACCESS ) ); uReturn++ )
		{
		}
		return uReturn;
	}

	ptr_t PX_API GetModuleEnd( HMODULE hm )
	{
		return reinterpret_cast< ptr_t  >( hm ) + reinterpret_cast< PIMAGE_NT_HEADERS > ( reinterpret_cast< std::uint8_t* >( hm ) + reinterpret_cast< PIMAGE_DOS_HEADER > ( hm )->e_lfanew )->OptionalHeader.SizeOfImage;
	}

	ptr_t FindFreeMemory( HMODULE hLocation, std::size_t sMinimumSize )
	{
		const auto ptrModuleEnd = GetModuleEnd( hLocation );

		for ( auto ptrAddress = ptrModuleEnd; ptrAddress > ptr_t( hLocation ); ptrAddress -= sizeof( ptr_t ) )
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
			while ( uPageCount < sMinimumSize && !bMemoryInUse )
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

	HMODULE PX_API GetAddressOriginModule( ptr_t ptrAddress )
	{
		if ( vecModules.empty( ) )
			px_assert( FindModules( ) );

		for ( const auto& hm : vecModules )
			if ( ptrAddress > ptr_t( hm ) && ptrAddress < GetModuleEnd( hm ) )
				return hm;

		return nullptr;
	}

	CHook::CHook( void* pVirtualTable ):
		dwOldProtection( 0u ), sTableLength( 0u ), sTableSize( 0u ), pClassBase( pVirtualTable ), pOldTable( nullptr ), pNewTable( nullptr ), hAllocationModule( HMODULE( ) ), bSetNewTable( false )
	{
		// Ensure that we are hooking a valid virtual table and that the length is valid( there are proper permissions to read and write to it ).
		// Set the address of pOldTable to the address of the first virtual function.
		if ( pClassBase == nullptr ||
			( sTableLength = EstimateTableLength( pOldTable = reinterpret_cast< ptr_t** >( pClassBase )[ 0 ] ) ) <= 0 )
			return;

		// Get the size of the table in bytes.
		sTableSize = sTableLength * sizeof( ptr_t );
		// Ensure that the module that has been entered is valid and find free memory inside of that module to point the class base to.
		if ( ( hAllocationModule = GetAddressOriginModule( ptr_t( *reinterpret_cast< void** >( pOldTable ) ) ) ) == nullptr ||
			( pNewTable = reinterpret_cast< ptr_t* >( FindFreeMemory( hAllocationModule, sTableSize + sizeof( ptr_t ) ) ) ) == nullptr )
			return;

		// Copy the addresses of the old table to the new table so the functions can still be accessed as normal.
		memcpy( pNewTable, pOldTable, sTableSize );

		// Set the permissions of the memory we found so that it is readable and writable, and store the old protection.
		// This is also used just to ensure that we have permission to modify the memory.
		if ( !VirtualProtect( pClassBase, sTableSize, PAGE_READWRITE, &dwOldProtection ) )
		{
			Cleanup( );
			return;
		}

		// Set the address of the class base to the new table.
		reinterpret_cast< ptr_t** >( pClassBase )[ 0 ] = &pNewTable[ 0 ];
		bSetNewTable = true;
	}

	CHook::~CHook( )
	{
		Cleanup( );
	}

	bool CHook::Succeeded( )
	{
		return bSetNewTable;
	}

	void CHook::UnhookIndex( unsigned uIndex )
	{
		if ( uIndex >= 0 && uIndex < sTableLength )
			pNewTable[ uIndex ] = pOldTable[ uIndex ];
	}

	void CHook::ResetTable( )
	{
		memcpy( pNewTable, pOldTable, sTableSize );
	}

	void CHook::Cleanup( )
	{
		// Reset the virtual function address array first, before we set the memory to 0 in case that function is called between and causes a crash.
		if ( bSetNewTable )
			reinterpret_cast< ptr_t** >( pClassBase )[ 0 ] = &pOldTable[ 0 ];

		memset( pNewTable, NULL, sTableSize );
		DWORD dwBuffer;
		VirtualProtect( pClassBase, sTableSize, dwOldProtection, &dwBuffer );
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void PX_API OpenLink( cstr_t szLink )
	{
		ShellExecute( nullptr, PX_XOR( L"open" ), Tools::string_cast< std::wstring >( std::string( szLink ) ).c_str( ), nullptr, nullptr, SW_SHOWNORMAL );
	}

	std::string PX_API TimeToDate( moment_t mmtTime )
	{
		if ( mmtTime == 0ull )
			return PX_XOR( "Never" );

		static char szBuffer[ 32 ];
		time_t tmBuffer = mmtTime;

		time( &tmBuffer );
		const auto tmTime = localtime( &tmBuffer );

		const char* szDaySuffix;

		switch ( tmTime->tm_mday % 10 )
		{
			default:
				if ( tmTime->tm_mday / 10 == 1 || tmTime->tm_mday % 10 > 3 )
				{
					szDaySuffix = PX_XOR( "th" );
					break;
				}
			case 1:
				szDaySuffix = PX_XOR( "st" );
				break;
			case 2:
				szDaySuffix = PX_XOR( "nd" );
				break;
			case 3:
				szDaySuffix = PX_XOR( "rd" );
				break;
		}

		px_assert( szDaySuffix );

		strftime( szBuffer, 80, ( std::string( PX_XOR( "%B %e" ) ) + szDaySuffix + PX_XOR( ", 20%g" ) ).c_str( ), tmTime );
		return szBuffer;
	}

	std::string PX_API FormatShellcode( byte_t* bByteArray, unsigned uSize )
	{
		std::string strFormatted { };
		for ( auto u = 0u; u < uSize; u++ )
		{
			strFormatted += PX_XOR( R"(\x)" );
			strFormatted.resize( strFormatted.size( ) + 2 ); // +2 because max length of a byte in digits is 2.
			sprintf( &strFormatted[ 0 ], "%s%02X", strFormatted.c_str( ), bByteArray[ u ] );
		}
		return strFormatted;
	}

	unsigned* GetScreenDimensions( )
	{
		static unsigned uScreenDimensions[ 2 ];
		uScreenDimensions[ 0 ] = GetSystemMetrics( SM_CXSCREEN );
		uScreenDimensions[ 1 ] = GetSystemMetrics( SM_CYSCREEN );
		return uScreenDimensions;
	}
}
