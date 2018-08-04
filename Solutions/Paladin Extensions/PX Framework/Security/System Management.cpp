/// System Information.cpp

#include "../PX Framework.hpp"

namespace PX::sys
{
	std::wstring PX_API RetrieveInfo( const bstr_t& wstrDevice, Types::wcstr_t wstrdeviceProperty = L"Name" )
	{
		if ( CoInitializeEx( nullptr, COINIT_MULTITHREADED ) != S_OK
			 || CoInitializeSecurity( nullptr, -1, nullptr, nullptr, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE, nullptr, EOAC_NONE, nullptr ) != S_OK )
			return { };

		IWbemLocator* pLocator;
		if ( CoCreateInstance( CLSID_WbemLocator, nullptr, CLSCTX_INPROC_SERVER, IID_IWbemLocator, reinterpret_cast< LPVOID* >( &pLocator ) ) != S_OK
			 || pLocator == nullptr )
			return { };

		IWbemServices* pServices;
		pLocator->ConnectServer( bstr_t( L"ROOT\\CIMV2" ), nullptr, nullptr, nullptr, 0, nullptr, nullptr, &pServices );
		if ( pServices == nullptr
			 || CoSetProxyBlanket( pServices, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, nullptr, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, nullptr, EOAC_NONE ) != S_OK )
			return { };

		IEnumWbemClassObject* pEnumerator;
		pServices->ExecQuery( bstr_t( L"WQL" ), wstrDevice, WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, nullptr, &pEnumerator );
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

	void PX_API GetSystemInfo( )
	{
		wstrSystemParts[ SYS_CPU ] = RetrieveInfo( L"SELECT * FROM Win32_Processor" );
		wstrSystemParts[ SYS_GPU ] = RetrieveInfo( L"SELECT * FROM CIM_PCVideoController" );
		wstrSystemParts[ SYS_DISPLAY ] = RetrieveInfo( L"SELECT * FROM Win32_DesktopMonitor" );
		wstrSystemParts[ SYS_OS ] = RetrieveInfo( L"SELECT * FROM CIM_OperatingSystem" );
		wstrSystemParts[ SYS_BOARD ] = RetrieveInfo( L"SELECT * FROM Win32_BaseBoard", L"Product" );

		dbg::Ensure( !wstrSystemParts[ SYS_CPU ].empty( )
					 && !wstrSystemParts[ SYS_GPU ].empty( )
					 && !wstrSystemParts[ SYS_DISPLAY ].empty( )
					 && !wstrSystemParts[ SYS_OS ].empty( )
					 && !wstrSystemParts[ SYS_BOARD ].empty( ) );

		wstrInstallUSBName = RetrieveInfo( L"SELECT * FROM CIM_LogicalDisk", L"Model" ); // TODO @Skel get the install usb name/model, then store it in this variable
		dbg::Ensure( !wstrInstallUSBName.empty( ) );

		std::wstring wstrBuffer = RetrieveInfo( L"SELECT * FROM CIM_LogicalDisk", L"Model" );
		dbg::Ensure( !wstrBuffer.empty( ) );

		while ( !wstrBuffer.substr( wstrBuffer.find_first_of( L'\n' ), wstrBuffer.size( ) ).empty( ) )
		{
			dqApps.emplace_back( wstrBuffer.substr( 0, wstrBuffer.find_first_of( L'\n' ) ) );
			wstrBuffer = wstrBuffer.substr( wstrBuffer.find_first_of( L'\n' ), wstrBuffer.size( ) );
		}
	}

	bool PX_API EnsureElevation( )
	{
		HANDLE hTokenSelf;
		TOKEN_ELEVATION teSelf { };
		DWORD dwReturnLength = sizeof( TOKEN_ELEVATION );

		if ( !OpenProcessToken( GetCurrentProcess( ), TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES, &hTokenSelf )
			 && !GetTokenInformation( hTokenSelf, TokenElevation, &teSelf, dwReturnLength, &dwReturnLength ) )
		{
			CloseHandle( hTokenSelf );
			return false;
		}

		if ( !teSelf.TokenIsElevated )
		{
			TOKEN_PRIVILEGES tpSelf;
			tpSelf.PrivilegeCount = 1;

			tpSelf.Privileges[ 0 ].Attributes = SE_PRIVILEGE_ENABLED;

			tpSelf.Privileges[ 0 ].Luid.LowPart = 20;
			tpSelf.Privileges[ 0 ].Luid.HighPart = 0;

			AdjustTokenPrivileges( hTokenSelf, FALSE, &tpSelf, 0, nullptr, nullptr );
		}

		if ( !GetTokenInformation( hTokenSelf, TokenElevation, &teSelf, dwReturnLength, &dwReturnLength ) || !teSelf.TokenIsElevated )
		{
			CloseHandle( hTokenSelf );
			return false;
		}

		return true;
	}

	DWORD PX_API GetProcessID( const std::wstring& wstrExecutableName )
	{
		PROCESSENTRY32 peTarget;
		peTarget.dwSize = sizeof( PROCESSENTRY32 );

		auto hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, NULL );
		if ( !dbg::Ensure( hSnapshot != INVALID_HANDLE_VALUE ) )
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

			if ( !dbg::Ensure( GetLastError( ) != ERROR_NO_MORE_FILES ) )
			{
				CloseHandle( hSnapshot );
				return 0;
			}
		}
		else
		{
			CloseHandle( hSnapshot );
			return 0;
		}

		return peTarget.th32ProcessID;
	}

	DWORD WINAPI CallDLLThreadEnd( )
	{
		return 0;
	}

	DWORD WINAPI CallDLLThread( _In_ LPVOID lpParameter )
	{
		auto* injInfo = static_cast< SInjectionInfo* >( lpParameter );

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

	bool PX_API DLLManualMap( LPVOID pDLL, const std::wstring& wstrExecutableName, SInjectionInfo* injInfo )
	{
		if ( !dbg::Ensure( EnsureElevation( ) ) )
			return false;

		// set up headers & ensure their validity against pre-defined signatures/characteristics
		auto pDOSHeader = PIMAGE_DOS_HEADER( pDLL );
		if ( !dbg::Ensure( pDOSHeader->e_magic == IMAGE_DOS_SIGNATURE ) )
			return false;

		auto pNTHeader = PIMAGE_NT_HEADERS( PBYTE( pDLL ) + pDOSHeader->e_lfanew );
		if ( !dbg::Ensure( pNTHeader->Signature == IMAGE_NT_SIGNATURE )
			 || !dbg::Ensure( pNTHeader->FileHeader.Characteristics & IMAGE_FILE_DLL ) )
			return false;

		// open handle to target process
		auto hTarget = OpenProcess( PROCESS_ALL_ACCESS, FALSE, GetProcessID( wstrExecutableName ) );
		if ( !dbg::Ensure( hTarget ) )
		{
			dbg::PutLastError( );
			CloseHandle( hTarget );
			return false;
		}

		// allocate memory in & write headers to target process
		auto pImage = VirtualAllocEx( hTarget, nullptr, pNTHeader->OptionalHeader.SizeOfImage, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE );
		if ( !dbg::Ensure( pImage ) )
		{
			dbg::PutLastError( );
			CloseHandle( hTarget );
			return false;
		}

		if ( !dbg::Ensure( WriteProcessMemory( hTarget, pImage, pDLL, pNTHeader->OptionalHeader.SizeOfHeaders, nullptr ) ) )
		{
			dbg::PutLastError( );
			VirtualFreeEx( hTarget, pImage, 0, MEM_RELEASE );
			CloseHandle( hTarget );
			return false;
		}

		auto pSectionHeader = PIMAGE_SECTION_HEADER( pNTHeader + 1 );
		for ( WORD w = 0; w < pNTHeader->FileHeader.NumberOfSections; w++ )
		{
			if ( !dbg::Ensure( WriteProcessMemory( hTarget, PBYTE( pImage ) + pSectionHeader[ w ].VirtualAddress, PBYTE( pDLL ) + pSectionHeader[ w ].PointerToRawData, pSectionHeader[ w ].SizeOfRawData, nullptr ) ) )
			{
				dbg::PutLastError( );
				VirtualFreeEx( hTarget, pImage, 0, MEM_RELEASE );
				CloseHandle( hTarget );
				return false;
			}
		}

		// allocate memory in & write data to target process
		auto pMemory = VirtualAllocEx( hTarget, nullptr, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE );
		if ( !dbg::Ensure( pMemory ) )
		{
			dbg::PutLastError( );
			VirtualFreeEx( hTarget, pImage, 0, MEM_RELEASE );
			CloseHandle( hTarget );
			return false;
		}

		// transfer important info to dll
		injInfo->pImageBase = pImage;
		injInfo->pNTHeaders = PIMAGE_NT_HEADERS( PBYTE( pImage ) + pDOSHeader->e_lfanew );
		injInfo->pBaseRelocation = PIMAGE_BASE_RELOCATION( PBYTE( pImage ) + pNTHeader->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_BASERELOC ].VirtualAddress );
		injInfo->pImportDescriptor = PIMAGE_IMPORT_DESCRIPTOR( PBYTE( pImage ) + pNTHeader->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_IMPORT ].VirtualAddress );
		injInfo->fnLoadLibraryA = LoadLibraryA;
		injInfo->fnGetProcAddress = GetProcAddress;

		if ( !dbg::Ensure( WriteProcessMemory( hTarget, pMemory, injInfo, sizeof( SInjectionInfo ), nullptr ) ) )
		{
			dbg::PutLastError( );
			VirtualFreeEx( hTarget, pImage, 0, MEM_RELEASE );
			VirtualFreeEx( hTarget, pMemory, 0, MEM_RELEASE );
			CloseHandle( hTarget );
			return false;
		}

		WriteProcessMemory( hTarget, PVOID( static_cast< SInjectionInfo* >( pMemory ) + 1 ), CallDLLThread, DWORD( CallDLLThreadEnd ) - DWORD( CallDLLThread ), nullptr );
		auto hThread = CreateRemoteThread( hTarget, nullptr, 0, LPTHREAD_START_ROUTINE( static_cast< SInjectionInfo* >( pMemory ) + 1 ), pMemory, 0, nullptr );
		if ( !dbg::Ensure( hThread ) )
		{
			dbg::PutLastError( );
			VirtualFreeEx( hTarget, pImage, 0, MEM_RELEASE );
			VirtualFreeEx( hTarget, pMemory, 0, MEM_RELEASE );
			CloseHandle( hTarget );
			return false;
		}
		dbg::PutLastError( );
		if ( !dbg::Ensure( WaitForSingleObject( hThread, INFINITE ) != WAIT_FAILED ) )
		{
			dbg::PutLastError( );
			VirtualFreeEx( hTarget, pMemory, 0, MEM_RELEASE );
			VirtualFreeEx( hTarget, pImage, 0, MEM_RELEASE );
			CloseHandle( hThread );
			CloseHandle( hTarget );
			return false;
		}

		DWORD dwExitCode;
		if ( !dbg::Ensure( GetExitCodeThread( hThread, &dwExitCode ) ) )
		{
			dbg::PutLastError( );
			VirtualFreeEx( hTarget, pMemory, 0, MEM_RELEASE );
			VirtualFreeEx( hTarget, pImage, 0, MEM_RELEASE );
			CloseHandle( hThread );
			CloseHandle( hTarget );
			return false;
		}

		if ( !dbg::Ensure( dwExitCode ) )
		{
			VirtualFreeEx( hTarget, pMemory, 0, MEM_RELEASE );
			VirtualFreeEx( hTarget, pImage, 0, MEM_RELEASE );
			CloseHandle( hThread );
			CloseHandle( hTarget );
			return false;
		}

		CloseHandle( hThread );
		VirtualFreeEx( hTarget, pMemory, 0, MEM_RELEASE );
		CloseHandle( hTarget );

		return true;
	}
}
