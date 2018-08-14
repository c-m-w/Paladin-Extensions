/// System Information.cpp

#include "../PX Framework.hpp"

namespace PX::sys
{
	std::wstring PX_API RetrieveInfo( const bstr_t& wstrDevice, wcstr_t wstrdeviceProperty = PX_XOR( L"Name" ) )
	{
		if ( CoInitializeEx( nullptr, COINIT_MULTITHREADED ) != S_OK )
			return { };

		auto hResult = CoInitializeSecurity( nullptr, -1, nullptr, nullptr, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE, nullptr, EOAC_NONE, nullptr );
		if ( hResult != S_OK && hResult != RPC_E_TOO_LATE )
			return { };

		IWbemLocator* pLocator;
		if ( CoCreateInstance( CLSID_WbemLocator, nullptr, CLSCTX_INPROC_SERVER, IID_IWbemLocator, reinterpret_cast< LPVOID* >( &pLocator ) ) != S_OK
			 || pLocator == nullptr )
			return { };

		IWbemServices* pServices;
		pLocator->ConnectServer( bstr_t( PX_XOR( L"ROOT\\CIMV2" ) ), nullptr, nullptr, nullptr, 0, nullptr, nullptr, &pServices );
		if ( pServices == nullptr
			 || CoSetProxyBlanket( pServices, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, nullptr, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, nullptr, EOAC_NONE ) != S_OK )
			return { };

		IEnumWbemClassObject* pEnumerator;
		pServices->ExecQuery( bstr_t( PX_XOR( L"WQL" ) ), wstrDevice, WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, nullptr, &pEnumerator );
		if ( pEnumerator == nullptr )
			return { };

		std::wstring wstrInfo;
		while ( pEnumerator )
		{
			IWbemClassObject* pClassObject;
			ULONG uReturn;
			pEnumerator->Next( WBEM_INFINITE, 1, &pClassObject, &uReturn );
			if ( !uReturn )
				break;

			VARIANT vtProp;
			pClassObject->Get( wstrdeviceProperty, 0, &vtProp, nullptr, nullptr );
			wstrInfo += vtProp.bstrVal;

			VariantClear( &vtProp );
			pClassObject->Release( );
		}

		pEnumerator->Release( );
		pServices->Release( );
		pLocator->Release( );
		CoUninitialize( );
		return wstrInfo;
	}

	nlohmann::json PX_API GetSystemInfo( )
	{
		wstrSystemParts[ SYS_CPU ] = RetrieveInfo( PX_XOR( L"SELECT * FROM Win32_Processor" ) );
		wstrSystemParts[ SYS_GPU ] = RetrieveInfo( PX_XOR( L"SELECT * FROM CIM_PCVideoController" ) );
		wstrSystemParts[ SYS_DISPLAY ] = RetrieveInfo( PX_XOR( L"SELECT * FROM Win32_DesktopMonitor" ) );
		wstrSystemParts[ SYS_OS ] = RetrieveInfo( PX_XOR( L"SELECT * FROM CIM_OperatingSystem" ) );
		wstrSystemParts[ SYS_OS ] = wstrSystemParts[ SYS_OS ].substr( 0, wstrSystemParts[ SYS_OS ].find_first_of( '|' ) );
		wstrSystemParts[ SYS_BOARD ] = RetrieveInfo( PX_XOR( L"SELECT * FROM Win32_BaseBoard" ), PX_XOR( L"Product" ) );

		px_assert( !wstrSystemParts[ SYS_CPU ].empty( )
				   && !wstrSystemParts[ SYS_GPU ].empty( )
				   && !wstrSystemParts[ SYS_DISPLAY ].empty( )
				   && !wstrSystemParts[ SYS_OS ].empty( )
				   && !wstrSystemParts[ SYS_BOARD ].empty( ) );

		for each( auto &wstr in wstrSystemParts )
			if ( wstr.length( ) > 100 )
				wstr = wstr.substr( 0, 100 );

		return nlohmann::json
		{
			{ PX_XOR( "cpu"     ), string_cast< std::string >( wstrSystemParts[ SYS_CPU ] ) },
			{ PX_XOR( "gpu"     ), string_cast< std::string >( wstrSystemParts[ SYS_GPU ] ) },
			{ PX_XOR( "display" ), string_cast< std::string >( wstrSystemParts[ SYS_DISPLAY ] ) },
			{ PX_XOR( "os"      ), string_cast< std::string >( wstrSystemParts[ SYS_OS ] ) },
			{ PX_XOR( "board"   ), string_cast< std::string >( wstrSystemParts[ SYS_BOARD ] ) },
		};
	}

	bool PX_API EnsureElevation( HANDLE hProcess /*= GetCurrentProcess( )*/ )
	{
		HANDLE hTokenSelf { };
		TOKEN_ELEVATION teSelf { };
		DWORD dwReturnLength = sizeof( TOKEN_ELEVATION );

		if ( !OpenProcessToken( hProcess, TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES, &hTokenSelf ) || !hTokenSelf
			 || !GetTokenInformation( hTokenSelf, TokenElevation, &teSelf, dwReturnLength, &dwReturnLength ) )
		{
			hTokenSelf && CloseHandle( hTokenSelf );
			return false;
		}

		TOKEN_PRIVILEGES tpSelf;
		tpSelf.PrivilegeCount = 1;
		
		tpSelf.Privileges[ 0 ].Attributes = SE_PRIVILEGE_ENABLED;
		
		if ( !LookupPrivilegeValue( nullptr, SE_DEBUG_NAME, &tpSelf.Privileges[ 0 ].Luid )
			 || !AdjustTokenPrivileges( hTokenSelf, FALSE, &tpSelf, 0, nullptr, nullptr ) )
		{
			hTokenSelf && CloseHandle( hTokenSelf );
			return false;
		}

		if ( !GetTokenInformation( hTokenSelf, TokenElevation, &teSelf, dwReturnLength, &dwReturnLength ) || !teSelf.TokenIsElevated )
		{
			hTokenSelf && CloseHandle( hTokenSelf );
			return false;
		}

		return true;
	}

	DWORD PX_API GetProcessID( const std::wstring& wstrExecutableName )
	{
		PROCESSENTRY32 peTarget { sizeof peTarget };

		const auto errLastError = GetLastError( );
		SetLastError( 0u );

		auto hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, NULL );
		if ( hSnapshot == INVALID_HANDLE_VALUE )
		{
			dbg::PutLastError( );
			CloseHandle( hSnapshot );
			return 0;
		}

		if ( Process32First( hSnapshot, &peTarget ) == TRUE )
		{
			do
			{
				if ( wstrExecutableName == peTarget.szExeFile )
					break;
			} while ( Process32Next( hSnapshot, &peTarget ) == TRUE );

			CloseHandle( hSnapshot );

			if ( GetLastError( ) == ERROR_NO_MORE_FILES )
				return 0u;

			SetLastError( errLastError );
		}
		else
		{
			CloseHandle( hSnapshot );
			return 0u;
		}

		return peTarget.th32ProcessID;
	}

	HANDLE PX_API FindProcessThread( DWORD dwProcessID )
	{
		auto hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPTHREAD, NULL );
		THREADENTRY32 teThread { sizeof teThread };

		const auto errLastError = GetLastError( );
		SetLastError( 0u );

		if ( hSnapshot == INVALID_HANDLE_VALUE )
		{
			dbg::PutLastError( );
			CloseHandle( hSnapshot );
			return INVALID_HANDLE_VALUE;
		}

		if ( Thread32First( hSnapshot, &teThread ) == TRUE )
		{
			do
			{
				if ( teThread.th32OwnerProcessID == dwProcessID && teThread.th32ThreadID != GetCurrentThreadId( ) )
				{
					CloseHandle( hSnapshot );
					return OpenThread( THREAD_GET_CONTEXT | THREAD_SET_CONTEXT | THREAD_SUSPEND_RESUME, FALSE, teThread.th32ThreadID );
				}
			} while ( Thread32Next( hSnapshot, &teThread ) == TRUE );

			if ( GetLastError( ) == ERROR_NO_MORE_FILES )
			{
				CloseHandle( hSnapshot );
				return INVALID_HANDLE_VALUE;
			}

			SetLastError( errLastError );
		}
		CloseHandle( hSnapshot );
		return INVALID_HANDLE_VALUE;
	}

	HMODULE FindModule( const std::wstring& wstrModule, DWORD dwProcessID )
	{
		auto hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcessID );

		if ( hSnapshot == INVALID_HANDLE_VALUE )
			return nullptr;

		MODULEENTRY32 meEntry { sizeof( MODULEENTRY32 ) };
		HMODULE hmSearch = nullptr;

		if ( Module32First( hSnapshot, &meEntry ) )
			do
			{
				if ( wstrModule == meEntry.szModule )
					hmSearch = meEntry.hModule;
			} while ( hmSearch == nullptr && Module32Next( hSnapshot, &meEntry ) );

		CloseHandle( hSnapshot );
		return hmSearch;
	}

	bool PX_API IsProcessOpen( const std::wstring& wstrExecutableName )
	{
		return GetProcessID( wstrExecutableName ) != 0u;
	}

	bool PX_API IsProcessThreadRunning( DWORD dwProcessID )
	{
		const auto hThread = FindProcessThread( dwProcessID );
		const auto bResult = hThread != nullptr;
		if ( bResult )
			CloseHandle( hThread );
		return bResult;
	}

	bool PX_API NecessaryModulesLoaded( DWORD dwProcessID )
	{
		return FindModule( PX_XOR( L"USER32.dll" ), dwProcessID );
	}	

	/// These functions have been converted to shellcode below, so they will function properly in debug mode. They should not be deleted in case we need them.

	/// Resolves imports and calls DLLMain.
	/*
	DWORD WINAPI CallDLLThread( _In_ LPVOID lpParameter )
	{
		auto* injInfo = static_cast< injection_info_t* >( lpParameter );

		// Mark starting address in header
		auto pBaseRelocation = injInfo->pBaseRelocation;
		auto dwHeaderSize = DWORD( LPBYTE( injInfo->pImageBase ) - injInfo->pNTHeaders->OptionalHeader.ImageBase );
		while ( pBaseRelocation->VirtualAddress )
		{
			if ( pBaseRelocation->SizeOfBlock >= sizeof( IMAGE_BASE_RELOCATION ) )
			{
				auto dwNumberOfBlocks = ( pBaseRelocation->SizeOfBlock - sizeof( IMAGE_BASE_RELOCATION ) ) / sizeof( WORD );
				auto pList = PWORD( pBaseRelocation + 1 );

				for ( DWORD d = 0; d < dwNumberOfBlocks; d++ )
					if ( pList[ d ] )
					{
						auto pAddress = PDWORD( LPBYTE( injInfo->pImageBase ) + ( pBaseRelocation->VirtualAddress + ( pList[ d ] & 0xFFF ) ) );
						*pAddress += dwHeaderSize;
					}
			}

			pBaseRelocation = PIMAGE_BASE_RELOCATION( LPBYTE( pBaseRelocation ) + pBaseRelocation->SizeOfBlock );
		}

		// Resolve DLL imports
		auto pImportDescriptor = injInfo->pImportDescriptor;
		for ( ; pImportDescriptor->Characteristics; pImportDescriptor++ )
		{
			auto thkOriginalFirst = PIMAGE_THUNK_DATA( LPBYTE( injInfo->pImageBase ) + pImportDescriptor->OriginalFirstThunk );
			auto thkNewFirst = PIMAGE_THUNK_DATA( LPBYTE( injInfo->pImageBase ) + pImportDescriptor->FirstThunk );

			auto hModule = injInfo->fnLoadLibraryA( LPCSTR( injInfo->pImageBase ) + pImportDescriptor->Name );

			if ( !hModule )
				return FALSE;

			for ( ; thkOriginalFirst->u1.AddressOfData; thkOriginalFirst++, thkNewFirst++ )
			{
				if ( thkOriginalFirst->u1.Ordinal & IMAGE_ORDINAL_FLAG ) // Import by ordinal
				{
					auto dwFunction = DWORD( injInfo->fnGetProcAddress( hModule, LPCSTR( thkOriginalFirst->u1.Ordinal & 0xFFFF ) ) );

					if ( !dwFunction )
						return FALSE;

					thkNewFirst->u1.Function = dwFunction;
				}
				else // Import by name
				{
					auto dwFunction = DWORD( injInfo->fnGetProcAddress( hModule, LPCSTR( PIMAGE_IMPORT_BY_NAME( LPBYTE( injInfo->pImageBase ) + thkOriginalFirst->u1.AddressOfData )->Name ) ) );

					if ( !dwFunction )
						return FALSE;

					thkNewFirst->u1.Function = dwFunction;
				}
			}
		}

		// Call DLLMain
		if ( injInfo->pNTHeaders->OptionalHeader.AddressOfEntryPoint )
		{
			auto fnEntry = reinterpret_cast< BOOL( WINAPI* )( HMODULE, DWORD, PVOID ) > ( LPBYTE( injInfo->pImageBase ) + injInfo->pNTHeaders->OptionalHeader.AddressOfEntryPoint );
			return fnEntry( HMODULE( injInfo->pImageBase ), DLL_PROCESS_ATTACH, nullptr );
		}

		return TRUE;
	}
	*/

	/// Stub to store and restore registers so we don't mess up the stack and cause crashing.
	/*
	__declspec( naked ) void stub( )
	{
		__asm
		{
			pushad
			call start

			start :
			pop ebx
				sub ebx, 0x6
				mov eax, PX_UNITIALIZED_STACK_MEMORY
				mov edx, PX_UNITIALIZED_STACK_MEMORY
				push edx
				call eax

				popad

				push PX_UNITIALIZED_STACK_MEMORY

				ret
		}
	}
	*/

	bool PX_API Inject( const LPVOID& pDLL, HANDLE hTarget, DWORD dwProcessID, injection_info_t* injInfo, DWORD dwThreadID /*= NULL*/ )
	{
		HANDLE hThread { };
		LPVOID pImage { },
			pMemory { },
			pStub { };

		const auto fnCleanup = [ & ]( bool bPrintLastError )
		{
			if ( hTarget )
			{
				if ( pImage )
					VirtualFreeEx( hTarget, pImage, 0, MEM_RELEASE );
				if ( pMemory )
					VirtualFreeEx( hTarget, pMemory, 0, MEM_RELEASE );
				if ( pStub )
					VirtualFreeEx( hTarget, pStub, 0, MEM_RELEASE );
				if ( hThread )
					CloseHandle( hThread );
				CloseHandle( hTarget );
			}

			delete[ ] bLoadDLL;
			delete[ ] bStub;

			if ( bPrintLastError )
				dbg::PutLastError( );
		};

		if ( !EnsureElevation( ) )
			return false;

		// set up headers & ensure their validity against pre-defined signatures/characteristics
		auto pDOSHeader = PIMAGE_DOS_HEADER( pDLL );
		if ( pDOSHeader->e_magic != IMAGE_DOS_SIGNATURE )
			return false;

		auto pNTHeader = PIMAGE_NT_HEADERS( PBYTE( pDLL ) + pDOSHeader->e_lfanew );
		if ( pNTHeader->Signature != IMAGE_NT_SIGNATURE
			 || !( pNTHeader->FileHeader.Characteristics & IMAGE_FILE_DLL ) )
			return false;	

		// allocate memory in & write headers to target process
		pImage = VirtualAllocEx( hTarget, nullptr, pNTHeader->OptionalHeader.SizeOfImage, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE );
		if ( !pImage )
		{
			fnCleanup( true );
			return false;
		}

		if ( !WriteProcessMemory( hTarget, pImage, pDLL, pNTHeader->OptionalHeader.SizeOfHeaders, nullptr ) )
		{
			fnCleanup( true );
			return false;
		}

		auto pSectionHeader = PIMAGE_SECTION_HEADER( pNTHeader + 1 );
		for ( WORD w = 0; w < pNTHeader->FileHeader.NumberOfSections; w++ )
			if ( !WriteProcessMemory( hTarget, PBYTE( pImage ) + pSectionHeader[ w ].VirtualAddress, PBYTE( pDLL ) + pSectionHeader[ w ].PointerToRawData, pSectionHeader[ w ].SizeOfRawData, nullptr ) )
			{
				fnCleanup( true );
				return false;
			}
		// transfer important info to dll
		injInfo->pImageBase = pImage;
		injInfo->pNTHeaders = PIMAGE_NT_HEADERS( PBYTE( pImage ) + pDOSHeader->e_lfanew );
		injInfo->pBaseRelocation = PIMAGE_BASE_RELOCATION( PBYTE( pImage ) + pNTHeader->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_BASERELOC ].VirtualAddress );
		injInfo->pImportDescriptor = PIMAGE_IMPORT_DESCRIPTOR( PBYTE( pImage ) + pNTHeader->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_IMPORT ].VirtualAddress );
		injInfo->fnLoadLibraryA = LoadLibraryA;
		injInfo->fnGetProcAddress = GetProcAddress;

		//// allocate memory in & write data to target process
		pMemory = VirtualAllocEx( hTarget, nullptr, PX_PAGE, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE );
		pStub = VirtualAllocEx( hTarget, nullptr, PX_PAGE, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE );
		if ( !WriteProcessMemory( hTarget, pMemory, injInfo, INJECTION_INFO_SIZE, nullptr ) ||
			 !WriteProcessMemory( hTarget, PVOID( ptr_t( pMemory ) + sizeof( injection_info_t ) ), bLoadDLL, uLoadDLLSize, nullptr ) )
		{
			fnCleanup( true );
			return false;
		}

		CONTEXT ctxThread { CONTEXT_FULL };
		if ( ( hThread = dwThreadID == NULL ? FindProcessThread( dwProcessID ) : OpenThread( THREAD_ALL_ACCESS, false, dwThreadID ) ) == INVALID_HANDLE_VALUE ||
			 SuspendThread( hThread ) == UINT_MAX )
		{
			fnCleanup( true );
			return false;
		}
		
		if ( GetThreadContext( hThread, &ctxThread ) == 0 )
		{
			ResumeThread( hThread );
			fnCleanup( true );
			return false;
		}
		
		for ( auto u = 0u; u < uStubSize - sizeof( ptr_t ); u++ )
		{
			const auto bOperator = bStub[ u ];
			const auto ptrOperand = reinterpret_cast< ptr_t* >( &bStub[ u + 1 ] );
		
			if ( *ptrOperand == PX_UNITIALIZED_STACK_MEMORY )
				switch ( bOperator )
				{
					case PX_MOV_EAX:
						*ptrOperand = ptr_t( ptr_t( pMemory ) + sizeof( injection_info_t ) );
						break;
		
					case PX_MOV_EDX:
						*ptrOperand = ptr_t( pMemory );
						break;
		
					case PX_PUSH:
						*ptrOperand = ctxThread.Eip;
						break;
		
					default:
						break;
				}
		}
		
		if ( !WriteProcessMemory( hTarget, pStub, bStub, uStubSize, nullptr ) )
		{
			ResumeThread( hThread );
			fnCleanup( true );
			return false;
		}
		
		ctxThread.Eip = ptr_t( pStub );
		SetThreadContext( hThread, &ctxThread );
		ResumeThread( hThread );
		
		// Wait until the thread resumes it's previous state.
		while ( GetThreadContext( hThread, &ctxThread ) == TRUE && ctxThread.Eip == ptr_t( pStub ) )
			Wait( 100ull );

		Wait( 10000 );

		auto fnWipeMemory = [ & ]( LPVOID pAddress, unsigned uSize )
		{
			DWORD dwBuffer;
			std::unique_ptr< byte_t[ ] > pZeroMemoryBuffer( new byte_t[ uSize ]( ) );
			WriteProcessMemory( hTarget, pAddress, pZeroMemoryBuffer.get( ), uSize, nullptr );
			VirtualProtectEx( hTarget, pAddress, uSize, PAGE_NOACCESS, &dwBuffer );
			VirtualFreeEx( hTarget, pAddress, uSize, MEM_DECOMMIT );
		};
		
		// Wipe PE headers
		fnWipeMemory( pImage, pDOSHeader->e_lfanew + sizeof pNTHeader + sizeof pSectionHeader * pNTHeader->FileHeader.NumberOfSections );
		
		// Wipe discardable sections
		for ( WORD w = 0; w < pNTHeader->FileHeader.NumberOfSections; w++ )
			if ( pSectionHeader[ w ].Characteristics & IMAGE_SCN_MEM_DISCARDABLE ) // If the section's characteristics are marked as discardable, wipe them and free the memory, and set it back to its' previous state.
				fnWipeMemory( LPVOID( pSectionHeader[ w ].VirtualAddress ), pSectionHeader[ w ].SizeOfRawData );
		
		// Wipe our CallDLLThread function that we wrote in
		fnWipeMemory( PVOID( static_cast< injection_info_t* >( pMemory ) + 1 ), uLoadDLLSize );

		fnCleanup( false );
		return true;
	}

	bool PX_API Inject( const LPVOID& pDLL, DWORD dwProcessID, injection_info_t* injInfo )
	{
		return Inject( pDLL, OpenProcess( PROCESS_ALL_ACCESS, FALSE, dwProcessID ), dwProcessID, injInfo );
	}

	bool PX_API Inject( const LPVOID& pDLL, const std::wstring& wstrExecutableName, injection_info_t* injInfo )
	{
		const auto dwProcessID = GetProcessID( wstrExecutableName );
		return Inject( pDLL, OpenProcess( PROCESS_ALL_ACCESS, FALSE, dwProcessID ), dwProcessID, injInfo );
	}

	typedef struct
	{
		DWORD    dwProcessID;
		BYTE     bObjectType;
		BYTE     bFlags;
		WORD     wValue;
		PVOID    pAddress;
		DWORD    dwGrantedAccess;
	} system_handle_t;

	typedef struct
	{
		ULONG HandleCount;
		system_handle_t Handles[ 1 ];
	} *psystem_handle_information_t;

	HANDLE FindInternalHandle( const DWORD dwTargetProcessID )
	{
		const auto fnQuerySystemInfo = reinterpret_cast< NTSTATUS( NTAPI* )( ULONG, PVOID, ULONG, PULONG ) >
								( GetProcAddress( GetModuleHandle( PX_XOR( L"ntdll.dll" ) ), PX_XOR( "NtQuerySystemInformation" ) ) );
		auto ulHandleInfoSize = 0x10000ul;
		auto pHandleInfo = reinterpret_cast< psystem_handle_information_t >( malloc( ulHandleInfoSize ) );

		NTSTATUS ntsResult;
		constexpr auto ulSystemHandleInfoFlags = 1 << 4;
		while ( ( ntsResult = fnQuerySystemInfo( ulSystemHandleInfoFlags, pHandleInfo, ulHandleInfoSize, nullptr ) ) == STATUS_INFO_LENGTH_MISMATCH )
			pHandleInfo = reinterpret_cast< psystem_handle_information_t >( realloc( pHandleInfo, ulHandleInfoSize *= 2 ) );

		px_assert( NT_SUCCESS( ntsResult ) );

		for ( auto ul = 0ul; ul < pHandleInfo->HandleCount; ul++ )
		{
			if ( pHandleInfo->Handles[ ul ].dwProcessID == GetCurrentProcessId( )
				 && dwTargetProcessID == GetProcessId( reinterpret_cast< HANDLE >( pHandleInfo->Handles[ ul ].wValue ) ) )
				return reinterpret_cast< HANDLE >( pHandleInfo->Handles[ ul ].wValue );
		}
		free( pHandleInfo );
		return nullptr;
	}

	void TerminateProcess( DWORD dwTargetProcessID )
	{
		if ( dwTargetProcessID )
		{
			if ( !EnsureElevation( ) )
				exit( -1 );
			if ( !::TerminateProcess( OpenProcess( PROCESS_TERMINATE, false, dwTargetProcessID ), 0 ) )
			{
				dbg::PutLastError( );
				exit( -1 );
			}
		}
	}

	void PX_API Delete( )
	{

	}
}
