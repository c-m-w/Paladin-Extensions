/// System Information.cpp

#define PX_USE_NAMESPACES
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
			{ PX_XOR( "cpu" ), string_cast< std::string >( wstrSystemParts[ SYS_CPU ] ) },
			{ PX_XOR( "gpu" ), string_cast< std::string >( wstrSystemParts[ SYS_GPU ] ) },
			{ PX_XOR( "display" ), string_cast< std::string >( wstrSystemParts[ SYS_DISPLAY ] ) },
			{ PX_XOR( "os" ), string_cast< std::string >( wstrSystemParts[ SYS_OS ] ) },
			{ PX_XOR( "board" ), string_cast< std::string >( wstrSystemParts[ SYS_BOARD ] ) },
		};
	}

	std::string PX_API AssembleExtensionInformation( std::string strCipher )
	{
		auto jsFileInformation = nlohmann::json::parse( Decrypt( strCipher ) );

		uLoadDLLSize = jsFileInformation[ PX_XOR( "Functions" ) ][ PX_XOR( "LoadDLL" ) ][ PX_XOR( "Size" ) ].get< int >( );
		bLoadDLL = new byte_t[ uLoadDLLSize + 1 ];
		for ( auto u = 0u; u < uLoadDLLSize; u++ )
			bLoadDLL[ u ] = byte_t( jsFileInformation[ PX_XOR( "Functions" ) ][ PX_XOR( "LoadDLL" ) ][ PX_XOR( "Shellcode" ) ][ u ].get< int >( ) );

		uStubSize = jsFileInformation[ PX_XOR( "Functions" ) ][ PX_XOR( "Stub" ) ][ PX_XOR( "Size" ) ].get< int >( );
		bStub = new byte_t[ uStubSize + 1 ];
		for ( auto u = 0u; u < uStubSize; u++ )
			bStub[ u ] = byte_t( jsFileInformation[ PX_XOR( "Functions" ) ][ PX_XOR( "Stub" ) ][ PX_XOR( "Shellcode" ) ][ u ].get< int >( ) );

		std::array< std::string, PX_EXTENSION_SECTIONS > strFileSections;
		std::string strAssembledFile { };

		for ( int i { }; i < PX_EXTENSION_SECTIONS; i++ )
			strFileSections.at( jsFileInformation[ PX_XOR( "DLL" ) ][ PX_XOR( "Order" ) ][ i ].get< int >( ) ) = Decrypt( jsFileInformation[ PX_XOR( "DLL" ) ][ PX_XOR( "Sections" ) ][ i ].get< std::string >( ) );

		for each ( const auto& strSection in strFileSections )
			strAssembledFile += strSection;

		return strAssembledFile;
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

		const auto dwLastError = GetLastError( );
		SetLastError( 0u );

		auto hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, NULL );
		if ( hSnapshot == INVALID_HANDLE_VALUE )
		{
			PutLastError( );
			CloseHandle( hSnapshot );
			return 0;
		}

		if ( Process32First( hSnapshot, &peTarget ) != TRUE )
		{
			CloseHandle( hSnapshot );
			return 0u;
		}
		do
		{
			if ( wstrExecutableName == peTarget.szExeFile )
				break;
		} while ( Process32Next( hSnapshot, &peTarget ) == TRUE );

		CloseHandle( hSnapshot );

		if ( GetLastError( ) == ERROR_NO_MORE_FILES )
			return 0u;

		SetLastError( dwLastError );

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
			PutLastError( );
			CloseHandle( hSnapshot );
			return INVALID_HANDLE_VALUE;
		}

		if ( Thread32First( hSnapshot, &teThread ) == TRUE )
		{
			do
			{
				if ( teThread.th32OwnerProcessID == dwProcessID )
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

	DWORD WINAPI LoadDLL( _In_ LPVOID lpParameter )
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

	void PX_API WipeMemoryEx( HANDLE hTarget, LPVOID pAddress, std::size_t sSize )
	{
		DWORD dwBuffer;
		std::unique_ptr< byte_t[ ] > pZeroMemoryBuffer( new byte_t[ sSize ]( ) );
		WriteProcessMemory( hTarget, pAddress, pZeroMemoryBuffer.get( ), sSize, nullptr );
		VirtualProtectEx( hTarget, pAddress, sSize, PAGE_NOACCESS, &dwBuffer );
		VirtualFreeEx( hTarget, pAddress, sSize, MEM_DECOMMIT );
	}

	void PX_API WipeMemory( LPVOID pAddress, std::size_t sSize )
	{
		DWORD dwBuffer;
		std::unique_ptr< byte_t[ ] > pZeroMemoryBuffer( new byte_t[ sSize ]( ) );
		memcpy( pAddress, pZeroMemoryBuffer.get( ), sSize );
		VirtualProtect( pAddress, sSize, PAGE_NOACCESS, &dwBuffer );
		VirtualFree( pAddress, sSize, MEM_DECOMMIT );
	}

	bool PX_API LoadRawLibraryEx( const LPVOID& pDLL, const std::wstring& wstrExecutableName, injection_info_t* injInfo )
	{
		HANDLE hTarget { },
			hThread { };
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
				PutLastError( );
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

		// open handle to target process
		const auto dwProcessID = GetProcessID( wstrExecutableName );
		hTarget = OpenProcess( PROCESS_VM_OPERATION | PROCESS_VM_WRITE, FALSE, dwProcessID );
		if ( !hTarget )
		{
			fnCleanup( true );
			return false;
		}

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
			if ( !WriteProcessMemory( hTarget, reinterpret_cast< void* >( ptr_t( pImage ) + pSectionHeader[ w ].VirtualAddress ), reinterpret_cast< void* >( ptr_t( pDLL ) + pSectionHeader[ w ].PointerToRawData ), pSectionHeader[ w ].SizeOfRawData, nullptr ) )
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
			 !WriteProcessMemory( hTarget, reinterpret_cast< void* >( ptr_t( pMemory ) + sizeof( injection_info_t ) ), bLoadDLL, uLoadDLLSize, nullptr ) )
		{
			fnCleanup( true );
			return false;
		}

		CONTEXT ctxThread { CONTEXT_FULL };
		if ( ( hThread = FindProcessThread( dwProcessID ) ) == INVALID_HANDLE_VALUE ||
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

		const auto dwOldEIP = ctxThread.Eip;
		ctxThread.Eip = ptr_t( pStub );

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
						*ptrOperand = dwOldEIP;
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

		SetThreadContext( hThread, &ctxThread );
		ResumeThread( hThread );

		// Wait until the thread resumes it's previous state.
		while ( GetThreadContext( hThread, &ctxThread ) == TRUE && ctxThread.Eip != dwOldEIP )
			Wait( 100ull );

		// Wipe PE headers
		WipeMemoryEx( hTarget, pImage, pDOSHeader->e_lfanew + sizeof pNTHeader + sizeof pSectionHeader * pNTHeader->FileHeader.NumberOfSections );

		// Wipe discardable sections
		for ( WORD w = 0; w < pNTHeader->FileHeader.NumberOfSections; w++ )
			if ( pSectionHeader[ w ].Characteristics & IMAGE_SCN_MEM_DISCARDABLE ) // If the section's characteristics are marked as discardable, wipe them and free the memory, and set it back to its' previous state.
				WipeMemoryEx( hTarget, reinterpret_cast< void* > ( ptr_t( pImage ) + pSectionHeader[ w ].VirtualAddress ), pSectionHeader[ w ].SizeOfRawData );

		// Wipe our CallDLLThread function that we wrote in
		WipeMemoryEx( hTarget, pMemory, PX_PAGE );
		WipeMemoryEx( hTarget, pStub, PX_PAGE );

		fnCleanup( false );
		return true;
	}

	bool PX_API LoadRawLibrary( const LPVOID& pDLL, injection_info_t* injInfo )
	{
		// set up headers & ensure their validity against pre - defined signatures / characteristics
		const auto pDOSHeader = PIMAGE_DOS_HEADER( pDLL );
		const auto pNTHeader = PIMAGE_NT_HEADERS( ptr_t( pDLL ) + pDOSHeader->e_lfanew );
		const auto pSectionHeader = PIMAGE_SECTION_HEADER( pNTHeader + 1 );
		const auto pImage = VirtualAlloc( nullptr, pNTHeader->OptionalHeader.SizeOfImage, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE );

		if ( pDOSHeader->e_magic != IMAGE_DOS_SIGNATURE )
			return false;

		if ( pNTHeader->Signature != IMAGE_NT_SIGNATURE
			 || !( pNTHeader->FileHeader.Characteristics & IMAGE_FILE_DLL ) )
			return false;

		memcpy( pImage, pDLL, pNTHeader->OptionalHeader.SizeOfHeaders );

		for ( WORD w = 0; w < pNTHeader->FileHeader.NumberOfSections; w++ )
			memcpy( reinterpret_cast< void* >( ptr_t( pImage ) + pSectionHeader[ w ].VirtualAddress ),
					reinterpret_cast< void* >( ptr_t( pDLL ) + pSectionHeader[ w ].PointerToRawData ), pSectionHeader[ w ].SizeOfRawData );

		injInfo->pImageBase = pImage;
		injInfo->pNTHeaders = PIMAGE_NT_HEADERS( ptr_t( pImage ) + pDOSHeader->e_lfanew );
		injInfo->pBaseRelocation = PIMAGE_BASE_RELOCATION( ptr_t( pImage ) + pNTHeader->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_BASERELOC ].VirtualAddress );
		injInfo->pImportDescriptor = PIMAGE_IMPORT_DESCRIPTOR( ptr_t( pImage ) + pNTHeader->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_IMPORT ].VirtualAddress );
		injInfo->fnLoadLibraryA = LoadLibraryA;
		injInfo->fnGetProcAddress = GetProcAddress;

		if ( FALSE == LoadDLL( injInfo ) )
			return false;

		// Wipe PE headers
		WipeMemory( pImage, pDOSHeader->e_lfanew + sizeof pNTHeader + sizeof pSectionHeader * pNTHeader->FileHeader.NumberOfSections );

		// Wipe discardable sections
		for ( WORD w = 0; w < pNTHeader->FileHeader.NumberOfSections; w++ )
			if ( pSectionHeader[ w ].Characteristics & IMAGE_SCN_MEM_DISCARDABLE ) // If the section's characteristics are marked as discardable, wipe them and free the memory, and set it back to its' previous state.
				WipeMemory( reinterpret_cast< void* >( ptr_t( pImage ) + pSectionHeader[ w ].VirtualAddress ), pSectionHeader[ w ].SizeOfRawData );

		return true;
	}

	typedef struct
	{
		DWORD	dwProcessID;
		BYTE	bObjectType;
		BYTE	bFlags;
		WORD	wValue;
		PVOID	pAddress;
		DWORD	dwGrantedAccess;
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
				PutLastError( );
				exit( -1 );
			}
		}
	}

	void PX_API Delete( ) noexcept
	{
		std::wstring wstrPath;
		FileRead( PX_APPDATA + PX_XOR( L"data.px" ), wstrPath, false );

		std::function< void( const std::wstring&, bool ) > lmdaDeleteDirectory = [ &lmdaDeleteDirectory ]( const std::wstring& wstrRootDirectory, const bool bDeleteHostDirectory )
		{
			WIN32_FIND_DATA fdInfo;

			auto hFiles = FindFirstFile( ( wstrRootDirectory + L"\\*.*" ).c_str( ), &fdInfo );
			do
			{
				if ( fdInfo.cFileName[ 0 ] != '.' )
				{
					auto wstrFilePath = wstrRootDirectory + L"\\" + fdInfo.cFileName;

					if ( fdInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
					{
						lmdaDeleteDirectory( wstrFilePath, true );
						RemoveDirectory( wstrFilePath.c_str( ) );
					}
					else
					{
						SetFileAttributes( wstrFilePath.c_str( ), FILE_ATTRIBUTE_NORMAL );
						DeleteFile( wstrFilePath.c_str( ) );
					}
				}
			} while ( TRUE == FindNextFile( hFiles, &fdInfo ) );

			bDeleteHostDirectory && RemoveDirectory( wstrRootDirectory.c_str( ) );

			FindClose( hFiles );
		};

		lmdaDeleteDirectory( PX_APPDATA, true );
		lmdaDeleteDirectory( wstrPath.substr( 0, wstrPath.find_last_of( L'\\' ) ), false );

		auto mmtStart = GetMoment( );
		int iTries = 0;
Retry:
		iTries++;
		try
		{

			STARTUPINFO si { };
			PROCESS_INFORMATION pi;
			// waits 3 seconds before creating the process
			CreateProcess( nullptr, &( std::wstring( PX_XOR( L"cmd.exe /C ping 1.1.1.1 -n 1 -w 3000 > Nul & Del /f /q \"" ) ) + wstrPath + L'\"' )[ 0 ],
						   nullptr, nullptr, FALSE, CREATE_NO_WINDOW, nullptr, nullptr, &si, &pi );

			CloseHandle( pi.hThread );
			CloseHandle( pi.hProcess );

			// if we took longer than 3 seconds to close handles (aka breakpoint, someone is stepping through) we retry. after 30 seconds/10 tries, we give up.
			if ( GetMoment( ) - mmtStart > 3000ull && iTries < 10 )
				goto Retry;
		}
		catch ( ... )
		{
		}
		exit( -1 );
	}
}
