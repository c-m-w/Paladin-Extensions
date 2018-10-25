/// Tools.cpp

#include "PX Precompiled.hpp"
#define PX_USE_NAMESPACES
#include "../PX Framework.hpp"

namespace PX::Tools
{
	PX_SDK std::vector< HMODULE > vecModules;

	bool PX_API FindModules( )
	{
		constexpr auto sMaxModules = 1024u;
		DWORD dwMemoryNeeded;

		vecModules.resize( sMaxModules );
		if ( 0 == EnumProcessModules( GetCurrentProcess( ), &vecModules[ 0 ], sMaxModules * sizeof( HMODULE ), &dwMemoryNeeded ) )
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

	ptr_t PX_API GetModuleEnd( HMODULE hModule )
	{
		return reinterpret_cast< ptr_t >( hModule ) + reinterpret_cast< PIMAGE_NT_HEADERS > ( reinterpret_cast< byte_t* >( hModule ) + reinterpret_cast< PIMAGE_DOS_HEADER > ( hModule )->e_lfanew )->OptionalHeader.SizeOfImage;
	}

	ptr_t FindFreeMemory( HMODULE hLocation, std::size_t zMinimumSize )
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
				 mbiPage.RegionSize < zMinimumSize )
				continue;

			auto bMemoryInUse = false;
			auto uPageCount = 0u;
			while ( uPageCount < zMinimumSize && !bMemoryInUse )
			{
				uPageCount += sizeof( ptr_t );
				if ( *reinterpret_cast< ptr_t* >( ptrAddress + uPageCount ) )
					bMemoryInUse = true;
			}

			if ( !bMemoryInUse && uPageCount >= zMinimumSize )
				return ptrAddress;
		}
		return 0u;
	}

	HMODULE PX_API FindAddressOrigin( ptr_t ptrAddress )
	{
		if ( vecModules.empty( ) )
			px_assert( FindModules( ) );

		for ( const auto& hm : vecModules )
			if ( ptrAddress > ptr_t( hm ) && ptrAddress < GetModuleEnd( hm ) )
				return hm;

		return nullptr;
	}

	CStandardHook::CStandardHook( void* pVirtualTable ): dwOldProtection( 0u ), zTableLength( 0u ), zTableSize( 0u ), pClassBase( pVirtualTable ),
		pOldTable( nullptr ), pNewTable( nullptr ), hAllocationModule( HMODULE( ) ), bSetNewTable( false )
	{
		// Ensure that we are hooking a valid virtual table and that the length is valid( there are proper permissions to read and write to it ).
		// Set the address of pOldTable to the address of the first virtual function.
		if ( pClassBase == nullptr ||
			( zTableLength = EstimateTableLength( pOldTable = *reinterpret_cast< ptr_t** >( pClassBase ) ) ) <= 0 )
			return;

		// Get the size of the table in bytes.
		zTableSize = zTableLength * sizeof( ptr_t );
		// Ensure that the module that has been entered is valid and find free memory inside of that module to point the class base to.
		if ( ( hAllocationModule = FindAddressOrigin( ptr_t( *reinterpret_cast< void** >( pOldTable ) ) ) ) == nullptr
#if defined _DEBUG
			  || ( pNewTable = new ptr_t[ zTableLength + 1 ] ) == nullptr )
#else
			  || ( pNewTable = reinterpret_cast< ptr_t* >( FindFreeMemory( hAllocationModule, zTableSize + sizeof( ptr_t ) ) ) ) == nullptr )
#endif
			return;

		// Copy the addresses of the old table to the new table so the functions can still be accessed as normal.
		memcpy( pNewTable, pOldTable, zTableSize );

		// Set the permissions of the memory we found so that it is readable and writable, and store the old protection.
		// This is also used just to ensure that we have permission to modify the memory.
		if ( !VirtualProtect( pClassBase, zTableSize, PAGE_READWRITE, &dwOldProtection ) )
		{
			Cleanup( );
			return;
		}

		// Set the address of the class base to the new table.
		*reinterpret_cast< ptr_t** >( pClassBase ) = pNewTable;
		bSetNewTable = true;
	}

	CStandardHook::~CStandardHook( )
	{
		Cleanup( );
	}

	bool CStandardHook::Succeeded( )
	{
		return bSetNewTable;
	}

	bool CStandardHook::HookIndex( unsigned uIndex, void* pNewFunction )
	{
		if ( uIndex >= 0 && uIndex <= zTableLength )
		{
			pNewTable[ uIndex ] = ptr_t( pNewFunction );
			return true;
		}
		return false;
	}

	void CStandardHook::UnhookIndex( unsigned uIndex )
	{
		if ( uIndex >= 0 && uIndex < zTableLength )
			pNewTable[ uIndex ] = pOldTable[ uIndex ];
	}

	void CStandardHook::ResetTable( )
	{
		memcpy( pNewTable, pOldTable, zTableSize );
	}

	void CStandardHook::Cleanup( )
	{
		// Reset the virtual function address array first, before we set the memory to 0 in case that function is called between and causes a crash.
		if ( bSetNewTable )
		{
			*reinterpret_cast< ptr_t** >( pClassBase ) = pOldTable;
#if defined _DEBUG
			delete[ ] pNewTable;
#endif
			bSetNewTable = false;
		}
	}

	CTrampolineHook::CTrampolineHook( void* pTable )
	{
		if ( !( bInitialized = nullptr != pTable
				&& nullptr != ( pNewTable = *reinterpret_cast< ptr_t** >( pTable ) )
				&& 0 < ( sTable = EstimateTableLength( pNewTable ) )
				&& nullptr != ( hTableOrigin = FindAddressOrigin( ptr_t( *reinterpret_cast< void** >( pNewTable ) ) ) ) ) )
			return;
		pOldTable = new uintptr_t[ sTable ];
		memcpy( pOldTable, pNewTable, sTable * sizeof( uintptr_t ) );
	}

	CTrampolineHook::~CTrampolineHook( )
	{
		UnhookAll( );
	}

	void CTrampolineHook::Setup( void* pTable )
	{
		*this = CTrampolineHook( pTable );
	}

	bool CTrampolineHook::Succeeded( )
	{
		return bInitialized;
	}

	bool CTrampolineHook::SetProtection( )
	{
		return bSetProtection = bInitialized
								  && TRUE == VirtualProtect( pNewTable, sTable * sizeof( uintptr_t ), PAGE_READWRITE, &dwTableProtection );
	}

	bool CTrampolineHook::HookIndex( unsigned uIndex, void* pAddress )
	{
		if ( !bSetProtection )
			return false;
		vecStubs.emplace_back( stub_t( ) );
		auto& stub = vecStubs.back( );
		stub.ptrAddress = FindFreeMemory( hTableOrigin, stub_t::STUB_SIZE );

		if ( FALSE == VirtualProtect( reinterpret_cast< void* >( stub.ptrAddress ), stub_t::STUB_SIZE, PAGE_EXECUTE_READWRITE, &stub.dwProtect ) )
			return false;
		memcpy( reinterpret_cast< void* >( stub.ptrAddress ), stub_t::STUB, stub_t::STUB_SIZE );
		*reinterpret_cast< uintptr_t* >( stub.ptrAddress + 1 ) = uintptr_t( pAddress );
		pNewTable[ uIndex ] = stub.ptrAddress;
		return true;
	}

	bool CTrampolineHook::ResetProtection( )
	{
		DWORD dwBuffer;
		return bSetProtection = TRUE == VirtualProtect( pNewTable, sTable * sizeof( uintptr_t ), dwTableProtection, &dwBuffer );
	}

	void CTrampolineHook::UnhookAll( )
	{
		DWORD dwBuffer;

		SetProtection( );
		memcpy( pNewTable, pOldTable, sTable * sizeof( uintptr_t ) );
		ResetProtection( );

		delete[ ] pOldTable;
		for ( auto& stub : vecStubs )
		{
			memset( reinterpret_cast< void* >( stub.ptrAddress ), 0, stub_t::STUB_SIZE );
			VirtualProtect( reinterpret_cast< void* >( stub.ptrAddress ), stub_t::STUB_SIZE, stub.dwProtect, &dwBuffer );
		}
	}

	bool Popup( EMBType popType, const wchar_t *wszMessage, const bool bDelete )
	{
		switch ( popType )
		{
			case EMBType::FATAL_ERROR:
				MessageBox( nullptr, wszMessage, PX_XOR( L"Paladin Extensions: Fatal Error" ), UINT( popType ) );
				break;
			case EMBType::RETRY_ERROR:
				if ( !bDelete )
					return MessageBox( nullptr, wszMessage, PX_XOR( L"Paladin Extensions: Error" ), UINT( popType ) ) == IDRETRY;
				Destroy( );
			case EMBType::QUERY:
				if ( !bDelete )
					return MessageBox( nullptr, wszMessage, PX_XOR( L"Paladin Extensions: Query" ), UINT( popType ) ) == IDYES;
				Destroy( );
			case EMBType::WARNING:
				MessageBox( nullptr, wszMessage, PX_XOR( L"Paladin Extensions: Warning" ), UINT( popType ) );
				break;
			case EMBType::INFO:
				if ( !bDelete )
					return MessageBox( nullptr, wszMessage, PX_XOR( L"Paladin Extensions: Information" ), UINT( popType ) );
				Destroy( );
			default:
				MessageBox( nullptr, wszMessage, PX_XOR( L"Paladin Extensions" ), UINT( popType ) );
				break;
		}
		bDelete ? Destroy( ) : ExitProcess( UINT_MAX );
	}

	void PX_API OpenLink( cstr_t szLink )
	{
		ShellExecute( nullptr, PX_XOR( L"open" ), Tools::string_cast< wstr_t >( str_t( szLink ) ).c_str( ), nullptr, nullptr, SW_SHOWNORMAL );
	}

	str_t PX_API TimeToDate( moment_t mmtTime )
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

		px_assert( strlen( szDaySuffix ) > 0 ); // if you get an exception thrown here, it's likely because the date is 0th

		// TODO: writing 80 bytes to szBuffer, but it's only 32...
		strftime( szBuffer, 80, ( str_t( PX_XOR( "%B %e" ) ) + szDaySuffix + PX_XOR( ", 20%g" ) ).c_str( ), tmTime );
		return szBuffer;
	}

	str_t PX_API FormatShellcode( byte_t* bByteArray, unsigned uSize )
	{
		str_t strFormatted { };
		for ( auto u = 0u; u < uSize; u++ )
		{
			strFormatted += PX_XOR( R"(\x)" );
			strFormatted.resize( strFormatted.size( ) + 2 ); // +2 because max length of a byte in digits is 2.
			sprintf( &strFormatted[ 0 ], "%s%02X", strFormatted.c_str( ), bByteArray[ u ] );
		}
		return strFormatted;
	}

	moment_t PX_API GetMoment( )
	{
		// WinAPI resolution is only in tenths of a microsecond
		return std::chrono::duration_cast< std::chrono::nanoseconds >( std::chrono::system_clock::now( ).time_since_epoch( ) ).count( ) / 100;
	}

	PX_EXT PX_INL void PX_API Pause( const moment_t mmtPauseLength /*= 1ull*/ ) // only accept time in milliseconds as that's all we can guarantee
	{
		if ( 0 == mmtPauseLength )
			return;

		static const auto NtDelayExecution = static_cast< SWindowsAPI::fnNtDelayExecution >( PX_WINAPI.GetFunctionPointer( SWindowsAPI::NtDelayExecution ) );
		if ( nullptr == NtDelayExecution ) // their system must be really messed up if it can't find delay execution
			return Sleep( DWORD( mmtPauseLength ) );

		const auto mmtEndTarget = GetMoment( ) + mmtPauseLength * 10000ull - 5000ull; // 10,000 is milliseconds to 100 nanoseconds conversion

		LARGE_INTEGER liDelayInterval;
		liDelayInterval.QuadPart = -1ll;

		while ( GetMoment( ) < mmtEndTarget )
			NtDelayExecution( FALSE, &liDelayInterval );
	}

	unsigned* GetScreenDimensions( )
	{
		static unsigned uScreenDimensions[ 2 ];
		uScreenDimensions[ 0 ] = GetSystemMetrics( SM_CXSCREEN );
		uScreenDimensions[ 1 ] = GetSystemMetrics( SM_CYSCREEN );
		return uScreenDimensions;
	}
}
