/// System Information.cpp

#define PX_USE_NAMESPACES
#include "../PX Framework.hpp"
#include "../../PX Debug Injector/PX Debug Injector.hpp"

namespace PX::sys
{
	/** \brief Retrieves info from WMIC service */
	/** \param bszDevice Device name, generally Win32_ */
	/** \param wszDeviceProperty Property to find from index */
	/** \return Property of device */
	std::wstring PX_API RetrieveInfo( const bstr_t& bszDevice, wcstr_t wszDeviceProperty = PX_XOR( L"Name" ) )
	{
		{
			const auto hrReturn = CoInitialize( nullptr );
			if ( hrReturn != S_OK && hrReturn != S_FALSE )
				return PX_XOR( L"-1" );
		}

		{
			auto hResult = CoInitializeSecurity( nullptr, -1, nullptr, nullptr, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE, nullptr, EOAC_NONE, nullptr );
			if ( hResult != S_OK && hResult != RPC_E_TOO_LATE )
				return PX_XOR( L"0" );
		}

		IWbemLocator* pLocator;
		if ( CoCreateInstance( CLSID_WbemLocator, nullptr, CLSCTX_INPROC_SERVER, IID_IWbemLocator, reinterpret_cast< LPVOID* >( &pLocator ) ) != S_OK
			 || pLocator == nullptr )
			return PX_XOR( L"1" );

		IWbemServices* pServices;
		pLocator->ConnectServer( bstr_t( PX_XOR( L"ROOT\\CIMV2" ) ), nullptr, nullptr, nullptr, 0, nullptr, nullptr, &pServices );
		if ( pServices == nullptr
			 || CoSetProxyBlanket( pServices, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, nullptr, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, nullptr, EOAC_NONE ) != S_OK )
			return PX_XOR( L"2" );

		IEnumWbemClassObject* pEnumerator;
		pServices->ExecQuery( bstr_t( PX_XOR( L"WQL" ) ), bszDevice, WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, nullptr, &pEnumerator );
		if ( pEnumerator == nullptr )
			return PX_XOR( L"3" );

		std::wstring wstrInfo;
		while ( pEnumerator )
		{
			IWbemClassObject* pClassObject;
			ULONG uReturn;
			pEnumerator->Next( WBEM_INFINITE, 1, &pClassObject, &uReturn );
			if ( !uReturn )
				break;

			VARIANT vtProp;
			pClassObject->Get( wszDeviceProperty, 0, &vtProp, nullptr, nullptr );
			wstrInfo += std::wstring( vtProp.bstrVal ) + L'\n';

			VariantClear( &vtProp );
			pClassObject->Release( );
		}

		pEnumerator->Release( );
		pServices->Release( );
		pLocator->Release( );
		CoUninitialize( );

		return wstrInfo.substr( 0, wstrInfo.size( ) - 1 ); // remove last newline character
	}

	nlohmann::json PX_API GetSystemInfo( )
	{
		std::wstring wstrSystemParts[ SYS_MAX ];
		wstrSystemParts[ SYS_CPU ] = RetrieveInfo( PX_XOR( L"SELECT * FROM Win32_Processor" ) );
		wstrSystemParts[ SYS_GPU ] = RetrieveInfo( PX_XOR( L"SELECT * FROM CIM_PCVideoController" ) );
		wstrSystemParts[ SYS_DISPLAY ] = RetrieveInfo( PX_XOR( L"SELECT * FROM Win32_DesktopMonitor" ) );
		wstrSystemParts[ SYS_PC ] = RetrieveInfo( PX_XOR( L"SELECT * FROM CIM_OperatingSystem" ), PX_XOR( L"CSName" ) );
		wstrSystemParts[ SYS_OS ] = RetrieveInfo( PX_XOR( L"SELECT * FROM CIM_OperatingSystem" ), PX_XOR( L"Caption" ) );
		wstrSystemParts[ SYS_DRIVE ] = RetrieveInfo( PX_XOR( L"SELECT * FROM Win32_DiskDrive" ), PX_XOR( L"SerialNumber" ) );
		wstrSystemParts[ SYS_BOARD ] = RetrieveInfo( PX_XOR( L"SELECT * FROM Win32_BaseBoard" ), PX_XOR( L"Product" ) );

		px_assert( !wstrSystemParts[ SYS_CPU ].empty( )
				   && !wstrSystemParts[ SYS_GPU ].empty( )
				   && !wstrSystemParts[ SYS_DISPLAY ].empty( )
				   && !wstrSystemParts[ SYS_PC ].empty( )
				   && !wstrSystemParts[ SYS_OS ].empty( )
				   && !wstrSystemParts[ SYS_DRIVE ].empty( )
				   && !wstrSystemParts[ SYS_BOARD ].empty( ) );

		for each( auto &wstr in wstrSystemParts )
			if ( wstr.length( ) > 100 )
				wstr = wstr.substr( 0, 100 );

		return nlohmann::json
		{
			{ PX_XOR( "cpu" ), string_cast< std::string >( wstrSystemParts[ SYS_CPU ] ) },
			{ PX_XOR( "gpu" ), string_cast< std::string >( wstrSystemParts[ SYS_GPU ] ) },
			{ PX_XOR( "display" ), string_cast< std::string >( wstrSystemParts[ SYS_DISPLAY ] ) },
			{ PX_XOR( "pc" ), string_cast< std::string >( wstrSystemParts[ SYS_PC ] ) },
			{ PX_XOR( "os" ), string_cast< std::string >( wstrSystemParts[ SYS_OS ] ) },
			{ PX_XOR( "drive" ), string_cast< std::string >( wstrSystemParts[ SYS_DRIVE ] ) },
			{ PX_XOR( "board" ), string_cast< std::string >( wstrSystemParts[ SYS_BOARD ] ) }
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
		DWORD dwReturnLength;

		if ( 0 == OpenProcessToken( hProcess, TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES, &hTokenSelf )
		  || !hTokenSelf
		  || 0 == GetTokenInformation( hTokenSelf, TokenElevation, &teSelf, sizeof( TOKEN_ELEVATION ), &dwReturnLength ) )
		{
			hTokenSelf && CloseHandle( hTokenSelf );
			return false;
		}

		TOKEN_PRIVILEGES tpNewDebug { };
		TOKEN_PRIVILEGES tpNewShutdown { };

		tpNewDebug.PrivilegeCount = 1;
		tpNewShutdown.PrivilegeCount = 1;

		tpNewDebug.Privileges[ 0 ].Attributes = SE_PRIVILEGE_ENABLED;
		tpNewShutdown.Privileges[ 0 ].Attributes = SE_PRIVILEGE_ENABLED;

		if ( 0 == LookupPrivilegeValue( nullptr, SE_DEBUG_NAME, &tpNewDebug.Privileges[ 0 ].Luid )
		  || 0 == LookupPrivilegeValue( nullptr, SE_SHUTDOWN_NAME, &tpNewShutdown.Privileges[ 0 ].Luid )
		  || 0 == AdjustTokenPrivileges( hTokenSelf, FALSE, &tpNewDebug, 0, nullptr, nullptr )
		  || 0 == AdjustTokenPrivileges( hTokenSelf, FALSE, &tpNewShutdown, 0, nullptr, nullptr ) )
		{
			hTokenSelf && CloseHandle( hTokenSelf );
			return false;
		}

		// todo check for tpNewDebug & tpNewShutdown being set properly token info
		if ( 0 == GetTokenInformation( hTokenSelf, TokenElevation, &teSelf, sizeof( TOKEN_ELEVATION ), &dwReturnLength )
		  || 0 == teSelf.TokenIsElevated )
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
		if ( hSnapshot == nullptr || hSnapshot == INVALID_HANDLE_VALUE )
		{
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
		}
		while ( Process32Next( hSnapshot, &peTarget ) == TRUE );

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

		const auto dwLastError = GetLastError( );
		SetLastError( 0u );

		if ( hSnapshot == nullptr || hSnapshot == INVALID_HANDLE_VALUE )
		{
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
			}
			while ( Thread32Next( hSnapshot, &teThread ) == TRUE );

			if ( GetLastError( ) == ERROR_NO_MORE_FILES )
			{
				CloseHandle( hSnapshot );
				return INVALID_HANDLE_VALUE;
			}

			SetLastError( dwLastError );
		}
		CloseHandle( hSnapshot );
		return INVALID_HANDLE_VALUE;
	}

	HMODULE FindModuleEx( const std::wstring& wstrModule, DWORD dwProcessID )
	{
		const auto hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcessID );

		if ( hSnapshot == INVALID_HANDLE_VALUE )
			return nullptr;

		MODULEENTRY32 meEntry { sizeof( MODULEENTRY32 ) };
		HMODULE hmSearch = nullptr;

		if ( Module32First( hSnapshot, &meEntry ) )
			do
			{
				if ( wstrModule == meEntry.szModule )
					hmSearch = meEntry.hModule;
			}
			while ( hmSearch == nullptr && Module32Next( hSnapshot, &meEntry ) );

		CloseHandle( hSnapshot );
		return hmSearch;
	}

	bool PX_API IsProcessOpen( const std::wstring& wstrExecutableName )
	{
		return GetProcessID( wstrExecutableName ) != 0u;
	}

	bool PX_API IsProcessThreadRunning( const DWORD dwProcessID )
	{
		const auto hThread = FindProcessThread( dwProcessID );
		const auto bResult = hThread != nullptr;
		if ( bResult )
			CloseHandle( hThread );
		return bResult;
	}

	bool PX_API NecessaryModulesLoaded( const DWORD dwProcessID )
	{
		return FindModuleEx( PX_XOR( L"USER32.dll" ), dwProcessID );
	}

	// These functions have been converted to shellcode below, so they will function properly in debug mode. They should not be deleted in case we need them.

	// Resolves imports and calls DLLMain.
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

	// Stub to store and restore registers so we don't mess up the stack and cause crashing.
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

	void PX_API WipeMemoryEx( HANDLE hTarget, LPVOID pAddress, std::size_t zSize )
	{
		DWORD dwBuffer;
		std::unique_ptr< byte_t[ ] > pZeroMemoryBuffer( new byte_t[ zSize ]( ) );
		WriteProcessMemory( hTarget, pAddress, pZeroMemoryBuffer.get( ), zSize, nullptr );
		VirtualProtectEx( hTarget, pAddress, zSize, PAGE_NOACCESS, &dwBuffer );
		VirtualFreeEx( hTarget, pAddress, zSize, MEM_DECOMMIT ); // todo should we be calling this with MEM_RELEASE? this might cause address space leaks
	}

	void PX_API WipeMemory( LPVOID pAddress, std::size_t zSize )
	{
		DWORD dwBuffer;
		std::unique_ptr< byte_t[ ] > pZeroMemoryBuffer( new byte_t[ zSize ]( ) );
		memcpy( pAddress, pZeroMemoryBuffer.get( ), zSize );
		VirtualProtect( pAddress, zSize, PAGE_NOACCESS, &dwBuffer );
		VirtualFree( pAddress, zSize, MEM_DECOMMIT );
	}

	bool PX_API LoadLibraryEx( const std::wstring& wstrExecutableName, const std::wstring& wstrDLLPath )
	{
		if ( !EnsureElevation( ) )
			return false;

		HANDLE hTarget = nullptr;
		LPVOID pPath = nullptr;
		HANDLE hThread = nullptr;

		const auto fnCleanup = [ & ]( )
		{
			if ( pPath )
				WipeMemoryEx( hTarget, pPath, PX_PAGE );
			if ( hTarget )
				CloseHandle( hTarget );
			if ( hThread )
				CloseHandle( hThread );
		};

		/* men */
		if ( nullptr == ( hTarget = OpenProcess( PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, FALSE, GetProcessID( wstrExecutableName ) ) )
			 || nullptr == ( pPath = VirtualAllocEx( hTarget, nullptr, PX_PAGE, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE ) )
			 || 0 == WriteProcessMemory( hTarget, pPath, &wstrDLLPath[ 0 ], wstrDLLPath.length( ) * sizeof( wchar_t ), nullptr )
			 || nullptr == ( hThread = CreateRemoteThread( hTarget, nullptr, NULL, LPTHREAD_START_ROUTINE( LoadLibrary ), pPath, NULL, nullptr ) )
			 || WaitForSingleObject( hThread, INFINITE ) == WAIT_TIMEOUT )
		{
			fnCleanup( );
			return false;
		}

		fnCleanup( );
		return true;
	}

	bool PX_API LoadRawLibraryEx( const LPVOID& pDLL, const std::wstring& wstrExecutableName, injection_info_t* injInfo, HANDLE* hTarget /*= nullptr*/, HANDLE* hThread /*= nullptr*/ )
	{
		LPVOID pImage { },
			pMemory { },
			pStub { };

		bool bKeepTargetHandle = true, bKeepThreadHandle = true;
		if ( hTarget == nullptr )
		{
			// it isn't reclaimed because if it's called with a value, then the caller wants to have access to the handle after the function returns
			// ReSharper disable once CppNonReclaimedResourceAcquisition
			hTarget = new HANDLE( nullptr );
			bKeepTargetHandle = false;
		}
		if ( hThread == nullptr )
		{
			// ReSharper disable once CppNonReclaimedResourceAcquisition
			hThread = new HANDLE( nullptr );
			bKeepThreadHandle = false;
		}

		const auto fnCleanup = [ & ]( )
		{
			if ( *hTarget )
			{
				if ( pImage )
					VirtualFreeEx( *hTarget, pImage, 0, MEM_RELEASE );
				if ( pMemory )
					VirtualFreeEx( *hTarget, pMemory, 0, MEM_RELEASE );
				if ( pStub )
					VirtualFreeEx( *hTarget, pStub, 0, MEM_RELEASE );
				if ( !bKeepThreadHandle && *hThread )
				{
					CloseHandle( *hThread );
					delete hThread;
				}
				if ( !bKeepTargetHandle )
				{
					CloseHandle( *hTarget );
					delete hTarget;
				}
			}

			delete[ ] bLoadDLL;
			delete[ ] bStub;
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
		if ( !*hTarget )
			*hTarget = OpenProcess( PROCESS_VM_OPERATION | PROCESS_VM_WRITE, FALSE, dwProcessID );
		if ( !*hTarget )
		{
			fnCleanup( );
			return false;
		}

		// allocate memory in & write headers to target process
		pImage = VirtualAllocEx( *hTarget, nullptr, pNTHeader->OptionalHeader.SizeOfImage, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE );
		if ( !pImage )
		{
			fnCleanup( );
			return false;
		}

		if ( !WriteProcessMemory( *hTarget, pImage, pDLL, pNTHeader->OptionalHeader.SizeOfHeaders, nullptr ) )
		{
			fnCleanup( );
			return false;
		}

		auto pSectionHeader = PIMAGE_SECTION_HEADER( pNTHeader + 1 );
		for ( WORD w = 0; w < pNTHeader->FileHeader.NumberOfSections; w++ )
			if ( !WriteProcessMemory( *hTarget, reinterpret_cast< void* >( ptr_t( pImage ) + pSectionHeader[ w ].VirtualAddress ), reinterpret_cast< void* >( ptr_t( pDLL ) + pSectionHeader[ w ].PointerToRawData ), pSectionHeader[ w ].SizeOfRawData, nullptr ) )
			{
				fnCleanup( );
				return false;
			}
		// transfer important info to dll
		injInfo->pImageBase = pImage;
		injInfo->pNTHeaders = PIMAGE_NT_HEADERS( PBYTE( pImage ) + pDOSHeader->e_lfanew );
		injInfo->pBaseRelocation = PIMAGE_BASE_RELOCATION( PBYTE( pImage ) + pNTHeader->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_BASERELOC ].VirtualAddress );
		injInfo->pImportDescriptor = PIMAGE_IMPORT_DESCRIPTOR( PBYTE( pImage ) + pNTHeader->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_IMPORT ].VirtualAddress );
		injInfo->fnLoadLibraryA = LoadLibraryA;
		injInfo->fnGetProcAddress = GetProcAddress;

		// allocate memory in & write data to target process
		pMemory = VirtualAllocEx( *hTarget, nullptr, PX_PAGE, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE );
		if ( !pMemory ||
			 !WriteProcessMemory( *hTarget, pMemory, injInfo, INJECTION_INFO_SIZE, nullptr ) ||
			 !WriteProcessMemory( *hTarget, reinterpret_cast< void* >( ptr_t( pMemory ) + sizeof( injection_info_t ) ), bLoadDLL, uLoadDLLSize, nullptr ) )
		{
			fnCleanup( );
			return false;
		}

		//const auto hCreatedThread = CreateRemoteThread( hTarget, nullptr, NULL, LPTHREAD_START_ROUTINE( ptr_t( pMemory ) + sizeof( injection_info_t ) ), pMemory, NULL, nullptr );
		//WaitForSingleObject( hCreatedThread, INFINITE );

		CONTEXT ctxThread { CONTEXT_FULL };
		if ( ( *hThread ? *hThread : *hThread = FindProcessThread( dwProcessID ) ) == INVALID_HANDLE_VALUE
		  || SuspendThread( *hThread ) == UINT_MAX )
		{
			fnCleanup( );
			return false;
		}

		if ( GetThreadContext( *hThread, &ctxThread ) == 0 )
		{
			ResumeThread( *hThread );
			fnCleanup( );
			return false;
		}

		const auto dwOldEIP = ctxThread.Eip;
		pStub = VirtualAllocEx( *hTarget, nullptr, PX_PAGE, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE );
		if ( !pStub )
		{
			fnCleanup( );
			return false;
		}
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

		if ( !WriteProcessMemory( *hTarget, pStub, bStub, uStubSize, nullptr ) )
		{
			ResumeThread( *hThread );
			fnCleanup( );
			return false;
		}

		SetThreadContext( *hThread, &ctxThread );
		ResumeThread( *hThread );

		// Wait until the thread resumes it's previous state.
		while ( GetThreadContext( *hThread, &ctxThread ) == TRUE && ctxThread.Eip != dwOldEIP )
			Pause( 100ull );

		// Wipe PE headers
		WipeMemoryEx( *hTarget, pImage, pDOSHeader->e_lfanew + sizeof pNTHeader + sizeof pSectionHeader * pNTHeader->FileHeader.NumberOfSections );

		// Wipe discardable sections
		for ( WORD w = 0; w < pNTHeader->FileHeader.NumberOfSections; w++ )
			if ( pSectionHeader[ w ].Characteristics & IMAGE_SCN_MEM_DISCARDABLE ) // If the section's characteristics are marked as discardable, wipe them and free the memory, and set it back to its' previous state.
				WipeMemoryEx( *hTarget, reinterpret_cast< void* > ( ptr_t( pImage ) + pSectionHeader[ w ].VirtualAddress ), pSectionHeader[ w ].SizeOfRawData );

		// Wipe our CallDLLThread function that we wrote in
		WipeMemoryEx( *hTarget, pMemory, PX_PAGE );
		WipeMemoryEx( *hTarget, pStub, PX_PAGE );

		fnCleanup( );
		return true;
	}

	bool PX_API LoadRawLibrary( const LPVOID& pDLL, injection_info_t* injInfo )
	{
		// set up headers & ensure their validity against pre - defined signatures / characteristics
		const auto pDOSHeader = PIMAGE_DOS_HEADER( pDLL );
		const auto pNTHeader = PIMAGE_NT_HEADERS( ptr_t( pDLL ) + pDOSHeader->e_lfanew );
		const auto pSectionHeader = PIMAGE_SECTION_HEADER( pNTHeader + 1 );
		const auto pImage = VirtualAlloc( nullptr, pNTHeader->OptionalHeader.SizeOfImage, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE );
		if ( !pImage )
			return false;

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

	HANDLE FindInternalHandle( const DWORD dwTargetProcessID )
	{
		const auto fnQuerySystemInfo = reinterpret_cast< NTSTATUS( NTAPI* )( ULONG, PVOID, ULONG, PULONG ) >
			( GetProcAddress( GetModuleHandle( PX_XOR( L"ntdll.dll" ) ), PX_XOR( "NtQuerySystemInformation" ) ) );
		auto ulHandleInfoSize = 0x10000ul;
		auto pHandleInfo = reinterpret_cast< SWindowsAPI::PSYSTEM_HANDLE_INFORMATION >( malloc( ulHandleInfoSize ) );
		px_assert( pHandleInfo );

		NTSTATUS ntsResult;
		constexpr auto ulSystemHandleInfoFlags = 1 << 4;
		while ( ( ntsResult = fnQuerySystemInfo( ulSystemHandleInfoFlags, pHandleInfo, ulHandleInfoSize, nullptr ) ) == STATUS_INFO_LENGTH_MISMATCH )
			pHandleInfo = reinterpret_cast< SWindowsAPI::PSYSTEM_HANDLE_INFORMATION >( realloc( pHandleInfo, ulHandleInfoSize *= 2 ) );

		px_assert( NT_SUCCESS( ntsResult ) );

		for ( auto ul = 0ul; ul < pHandleInfo->HandleCount; ul++ )
		{
			if ( pHandleInfo->Handles[ ul ].ProcessId == GetCurrentProcessId( )
				 && dwTargetProcessID == GetProcessId( reinterpret_cast< HANDLE >( pHandleInfo->Handles[ ul ].Handle ) ) )
				return reinterpret_cast< HANDLE >( pHandleInfo->Handles[ ul ].Handle );
		}
		free( pHandleInfo );
		return nullptr;
	}

	void TerminateProcess( DWORD dwTargetProcessID )
	{
		if ( dwTargetProcessID )
			if ( !EnsureElevation( ) || !::TerminateProcess( OpenProcess( PROCESS_TERMINATE, false, dwTargetProcessID ), 0 ) )
				ExitProcess( -1 );
	}

	struct
	{
		SWindowsAPI::EFuncs efnID;
		const wchar_t* wszLibrary;
		const char* szFunctionSymbolName;
		bool bAvailable = false;
		void* pPointer;
	} fndAPIFunctionsData[ SWindowsAPI::FUNC_MAX ]
	{
		/* Function Identifier								Library						Exported Symbol Name					*/
		{ SWindowsAPI::EFuncs::EnumSystemFirmwareTables,	PX_XOR( L"kernel32.dll" ),	PX_XOR( "EnumSystemFirmwareTables" )	},
		{ SWindowsAPI::EFuncs::GetSystemFirmwareTable,		PX_XOR( L"kernel32.dll" ),	PX_XOR( "GetSystemFirmwareTable" )		},
		{ SWindowsAPI::EFuncs::GetNativeSystemInfo,			PX_XOR( L"kernel32.dll" ),	PX_XOR( "GetNativeSystemInfo" )			},
		{ SWindowsAPI::EFuncs::GetProductInfo,				PX_XOR( L"kernel32.dll" ),	PX_XOR( "GetProductInfo" )				},
		{ SWindowsAPI::EFuncs::IsWow64Process,				PX_XOR( L"kernel32.dll" ),	PX_XOR( "IsWow64Process" )				},
		{ SWindowsAPI::EFuncs::LdrEnumerateLoadedModules,	PX_XOR( L"ntdll.dll" ),		PX_XOR( "LdrEnumerateLoadedModules" )	},
		{ SWindowsAPI::EFuncs::NtClose,						PX_XOR( L"ntdll.dll" ),		PX_XOR( "NtClose" )						},
		{ SWindowsAPI::EFuncs::NtCreateDebugObject,			PX_XOR( L"ntdll.dll" ),		PX_XOR( "NtCreateDebugObject" )			},
		{ SWindowsAPI::EFuncs::NtCreateThreadEx,			PX_XOR( L"ntdll.dll" ),		PX_XOR( "NtCreateThreadEx" )			},
		{ SWindowsAPI::EFuncs::NtDelayExecution,			PX_XOR( L"ntdll.dll" ),		PX_XOR( "NtDelayExecution" )			},
		{ SWindowsAPI::EFuncs::NtQueryInformationThread,	PX_XOR( L"ntdll.dll" ),		PX_XOR( "NtQueryInformationThread" )	},
		{ SWindowsAPI::EFuncs::NtQueryInformationProcess,	PX_XOR( L"ntdll.dll" ),		PX_XOR( "NtQueryInformationProcess" )	},
		{ SWindowsAPI::EFuncs::NtQueryObject,				PX_XOR( L"ntdll.dll" ),		PX_XOR( "NtQueryObject" )				},
		{ SWindowsAPI::EFuncs::NtQuerySystemInformation,	PX_XOR( L"ntdll.dll" ),		PX_XOR( "NtQuerySystemInformation" )	},
		{ SWindowsAPI::EFuncs::NtSetInformationThread,		PX_XOR( L"ntdll.dll" ),		PX_XOR( "NtSetInformationThread" )		},
		{ SWindowsAPI::EFuncs::NtWow64QueryVirtualMemory64,	PX_XOR( L"ntdll.dll" ),		PX_XOR( "NtWow64QueryVirtualMemory64" ) },
		{ SWindowsAPI::EFuncs::NtWow64ReadVirtualMemory64,	PX_XOR( L"ntdll.dll" ),		PX_XOR( "NtWow64ReadVirtualMemory64" )	},
		{ SWindowsAPI::EFuncs::NtUnmapViewOfSection,		PX_XOR( L"ntdll.dll" ),		PX_XOR( "NtUnmapViewOfSection" )		},
		{ SWindowsAPI::EFuncs::NtYieldExecution,			PX_XOR( L"ntdll.dll" ),		PX_XOR( "NtYieldExecution" )			},
		{ SWindowsAPI::EFuncs::RtlGetVersion,				PX_XOR( L"ntdll.dll" ),		PX_XOR( "RtlGetVersion" )				},
		{ SWindowsAPI::EFuncs::RtlCreateUserThread,			PX_XOR( L"ntdll.dll" ),		PX_XOR( "RtlCreateUserThread" )			}
	};

	SWindowsAPI::SWindowsAPI( ) PX_NOX
	{
		for each ( auto& fndAPIFunctionData in fndAPIFunctionsData )
		{
			// cant load the library means OS is messed up bad
			const auto hLibrary = LoadLibrary( fndAPIFunctionData.wszLibrary );
			if ( nullptr == hLibrary )
				continue;

			// cant get the address means the function isn't there
			fndAPIFunctionData.pPointer = GetProcAddress( hLibrary, fndAPIFunctionData.szFunctionSymbolName );
			if ( nullptr == fndAPIFunctionData.pPointer )
				continue;

			fndAPIFunctionData.bAvailable = true;
		}
	}

	void* PX_API SWindowsAPI::GetFunctionPointer( EFuncs enfRequest ) const PX_NOX
	{
		for each ( auto& fndAPIFunctionData in fndAPIFunctionsData )
			if ( fndAPIFunctionData.efnID == enfRequest )
				return fndAPIFunctionData.bAvailable ? fndAPIFunctionData.pPointer : nullptr;
		return nullptr; // somehow the EFunc passed wasn't in our enum...
	}
}
