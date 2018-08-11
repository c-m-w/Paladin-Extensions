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
				if ( teThread.th32OwnerProcessID == dwProcessID )
				{
					CloseHandle( hSnapshot );
					return OpenThread( THREAD_GET_CONTEXT | THREAD_SET_CONTEXT, FALSE, teThread.th32ThreadID );
				}
			} while ( Thread32Next( hSnapshot, &teThread ) == TRUE );

			if ( GetLastError( ) == ERROR_NO_MORE_FILES )
			{
				CloseHandle( hSnapshot );
				return INVALID_HANDLE_VALUE;
			}
		}
		CloseHandle( hSnapshot );
		return INVALID_HANDLE_VALUE;
	}

	/// ALLIGN ALL SIZES TO A PAGE (4 bytes)
	constexpr byte_t bCallDLLThread[ ] { "\x55\x8B\xEC\x51\x53\x56\x57\x8B\x7D\x08\x8B\x47\x04\x8B\x57\x08\x8B\x1F\x2B\x58\x34\x83\x3A\x00\x74\x3E\x66\x0F\x1F\x44\x00\x00\x8B\x42\x04\x83\xF8\x08\x72\x29\x8D\x70\xF8\xB9\x00\x00\x00\x00\xD1\xEE\x74\x1D\x0F\xB7\x44\x4A\x08\x66\x85\xC0\x74\x0B\x25\xFF\x0F\x00\x00\x03\x02\x03\x07\x01\x18\x41\x3B\xCE\x72\xE6\x8B\x42\x04\x03\xD0\x83\x3A\x00\x75\xC8\x8B\x57\x0C\x89\x55\x08\x8B\x02\x85\xC0\x74\x5F\x8B\x0F\x8B\x5A\x10\x03\xD9\x8D\x34\x01\x8B\x42\x0C\x03\xC1\x50\x8B\x47\x10\xFF\xD0\x8B\xD0\x89\x55\xFC\x85\xD2\x74\x5F\x8B\x0E\x85\xC9\x74\x2C\x2B\xDE\x85\xC9\x79\x05\x0F\xB7\xC1\xEB\x07\x8B\x07\x83\xC0\x02\x03\xC1\x50\x8B\x47\x14\x52\xFF\xD0\x85\xC0\x74\x3C\x8B\x55\xFC\x89\x04\x33\x83\xC6\x04\x8B\x0E\x85\xC9\x75\xD8\x8B\x55\x08\x83\xC2\x14\x89\x55\x08\x8B\x02\x85\xC0\x75\xA1\x8B\x47\x04\x8B\x48\x28\x85\xC9\x74\x1F\x8B\x07\x6A\x00\x6A\x01\x50\x03\xC1\xFF\xD0\x5F\x5E\x5B\x8B\xE5\x5D\xC2\x04\x00\x5F\x5E\x33\xC0\x5B\x8B\xE5\x5D\xC2\x04\x00\x5F\x5E\xB8\x01\x00\x00\x00\x5B\x8B\xE5\x5D\xC2\x04\x00\xCC\xCC\xCC\xCC\xCC\xCC\x55\x8B\xEC\x6A\xFF\x68\x0B\x47\xA9\x00\x64\xA1\x00\x00\x00\x00\x50\xB8\x50\x11\x00\x00\xE8\x85\xD9\x00\x00\xA1\x84\xD0\xA9\x00\x33\xC5\x89\x45\xF0\x56\x57\x50\x8D\x45\xF4\x64\xA3\x00\x00\x00\x00\x89\x95\xD0\xEE\xFF\xFF\x8B\xF1\x89\xB5\x34\xF1\xFF\xFF\x8B\x45\x08\x0F\x57\xC0\x0F\x11\x85\x24\xF1\xFF\xFF\x89\x85\xCC\xEE\xFF\xFF\x0F\x11\x85\x24\xF1\xFF\xFF\xE8\xB2\xFD\xFF\xFF\x84\xC0\x0F\x84\x83\x05\x00\x00\x8B\x0E\xBA\x4D\x5A\x00\x00\xA1\xD4\xEA\xA9\x00\x40\x89\x8D\xC4\xEE\xFF\xFF\xA3\xD4\xEA\xA9\x00\x66\x39\x11\x74\x06\x50\xE9\x66\x05\x00\x00\x8B\x71\x3C\x40\x03\xF1\xA3\xD4\xEA\xA9\x00\x89\xB5\xC8\xEE\xFF\xFF\x81\x3E\x50\x45\x00\x00\x74\x06\x50\xE9\x47\x05\x00\x00\x0F\xB7\x4E\x16\x40\x81\xE1\x00\x20\x00\x00\xA3\xD4\xEA\xA9\x00\xE8\xA3\x06\x00\x00\x84\xC0\x0F\x84\x50\x01\x00\x00\x6A\x00\x6A\x02\xC7\x85\xD8\xEE\xFF\xFF\x2C\x02\x00\x00\xFF\x15\x18\x60\xA9\x00\x8B\xF8\x89\xBD\xB0\xEE\xFF\xFF\x83\xFF\xFF\x0F\x84\xFF\x04\x00\x00\xFF\x05\xD4\xEA\xA9\x00\x8D\x85\xD8\xEE\xFF\xFF\x50\x57\xFF\x15\x28\x60\xA9\x00\x83\xF8\x01\x0F\x85\xDE\x00\x00\x00\x8B\xB5\xD0\xEE\xFF\xFF\x8D\x7E\x04\x8D\x8D\xFC\xEE\xFF\xFF\x8D\x51\x02\x0F\x1F\x80\x00\x00\x00\x00\x66\x8B\x01\x83\xC1\x02\x66\x85\xC0\x75\xF5\x2B\xCA\xD1\xF9\x83\x7E\x18\x08\x72\x03\x8B\x7E\x04\x8B\x56\x14\x3B\xD1\x75\x42\x8D\x85\xFC\xEE\xFF\xFF\x89\x85\xB4\xEE\xFF\xFF\x85\xD2\x74\x51\x0F\xB7\x0F\x0F\xB7\xB5\xFC\xEE\xFF\xFF\x66\x3B\xCE\x7C\x1D\x2B\xF8\x66\x3B\xCE\x7F\x16\x83\xFA\x01\x74\x36\x0F\xB7\x4C\x38\x02\x83\xC0\x02\x4A\x0F\xB7\x30\x66\x3B\xCE\x7D\xE8\x8B\xB5\xD0\xEE\xFF\xFF\x8D\x85\xD8\xEE\xFF\xFF\x50\xFF\xB5\xB0\xEE\xFF\xFF\xFF\x15\x20\x60\xA9\x00\x8D\x7E\x04\x83\xF8\x01\x0F\x84\x70\xFF\xFF\xFF\xFF\x15\xAC\x60\xA9\x00\x83\xF8\x12\x75\x26\xFF\x35\xD4\xEA\xA9\x00\x8D\x8D\xA4\xEE\xFF\xFF\x68\xC8\x92\xA9\x00\xE8\x5F\xD7\xFF\xFF\x68\x0C\xB1\xA9\x00\x8D\x85\xA4\xEE\xFF\xFF\xE9\x39\x04\x00\x00\xFF\x05\xD4\xEA\xA9\x00\x8B\x85\xE0\xEE\xFF\xFF\x8B\xB5\xC8\xEE\xFF\xFF\xEB\x09\x57\xFF\x15\x2C\x60\xA9\x00\x33\xC0\x50\x6A\x00\x68\xFF\xFF\x1F\x00\xFF\x15\x14\x60\xA9\x00\x8B\xF8\x8B\xCF\xE8\x9B\x05\x00\x00\x84\xC0\x75\x29\x51\x8D\x8D\x24\xF1\xFF\xFF\xE8\x0B\x04\x00\x00\x32\xC0\x8B\x4D\xF4\x64\x89\x0D\x00\x00\x00\x00\x59\x5F\x5E\x8B\x4D\xF0\x33\xCD\xE8\xD2\xB4\x00\x00\x8B\xE5\x5D\xC3\x6A\x40\x68\x00\x30\x00\x00\xFF\x76\x50\x6A\x00\x57\xFF\x15\x38\x60\xA9\x00\x8B\xC8\x89\x85\xD0\xEE\xFF\xFF\xE8\x4E\x05\x00\x00\x84\xC0\x74\xB3\x8B\x85\x34\xF1\xFF\xFF\x6A\x00\xFF\x76\x54\xFF\x30\xFF\xB5\xD0\xEE\xFF\xFF\x57\xFF\x15\xBC\x60\xA9\x00\x8B\xC8\xE8\xE9\x04\x00\x00\x84\xC0\x74\x8E\x8B\x85\xC8\xEE\xFF\xFF\x8D\x8E\xF8\x00\x00\x00\x33\xD2\x33\xF6\x66\x3B\x50\x06\x73\x4E\x8B\x95\x34\xF1\xFF\xFF\x0F\xB7\xC6\x6A\x00\x8D\x04\x80\xFF\x74\xC1\x10\x8D\x0C\xC1\x8B\x41\x14\x03\x02\x50\x8B\x41\x0C\x03\x85\xD0\xEE\xFF\xFF\x50\x57\xFF\x15\xBC\x60\xA9\x00\x8B\xC8\xE8\x9C\x04\x00\x00\x84\xC0\x0F\x84\x3D\xFF\xFF\xFF\x8B\x85\xC8\xEE\xFF\xFF\x46\x8D\x88\xF8\x00\x00\x00\x66\x3B\x70\x06\x72\xB2\x6A\x40\x68\x00\x30\x00\x00\x68\x00\x10\x00\x00\x6A\x00\x57\xFF\x15\x38\x60\xA9\x00\x8B\xF0\x8B\xCE\x89\xB5\x34\xF1\xFF\xFF\xE8\x9D\x04\x00\x00\x84\xC0\x0F\x84\xFE\xFE\xFF\xFF\x8B\x8D\xCC\xEE\xFF\xFF\x8B\x95\xD0\xEE\xFF\xFF\x8B\x85\xC4\xEE\xFF\xFF\x8B\xB5\xCC\xEE\xFF\xFF\x89\x11\x6A\x00\x8B\x40\x3C\x03\xC2\x89\x41\x04\x8B\x8D\xC8\xEE\xFF\xFF\x6A\x18\x8B\x81\xA0\x00\x00\x00\x03\xC2\x89\x46\x08\x8B\x81\x80\x00\x00\x00\x8B\xCE\x8B\xB5\x34\xF1\xFF\xFF\x03\xC2\x51\x56\x8B\x35\xBC\x60\xA9\x00\x89\x41\x0C\xA1\x24\x60\xA9\x00\x89\x41\x10\xA1\x34\x60\xA9\x00\x57\x89\x41\x14\xFF\xD6\x8B\xC8\xE8\xE9\x03\x00\x00\x84\xC0\x0F\x84\x8A\xFE\xFF\xFF\x8B\x85\x34\xF1\xFF\xFF\x6A\x00\x68\xB5\x0E\x00\x00\x83\xC0\x18\x68\x70\x5E\xA8\x00\x50\x57\x89\x85\xCC\xEE\xFF\xFF\xFF\xD6\x8B\xC8\xE8\xBB\x03\x00\x00\x84\xC0\x0F\x84\x5C\xFE\xFF\xFF\x68\xB6\x0E\x00\x00\x8D\x85\x38\xF1\xFF\xFF\x6A\x00\x50\xE8\x8B\xDE\x00\x00\x83\xC4\x0C\x8D\x85\x38\xF1\xFF\xFF\x6A\x00\x68\xB5\x0E\x00\x00\x50\xFF\xB5\xCC\xEE\xFF\xFF\x57\xFF\x15\x3C\x60\xA9\x00\x8D\x8D\x04\xF1\xFF\xFF\xE8\x27\xDD\xFF\xFF\xC7\x45\xFC\x00\x00\x00\x00\x33\xF6\x6A\x02\x68\x08\x9E\xA9\x00\x8D\x8D\x04\xF1\xFF\xFF\xE8\xCC\xF0\xFF\xFF\x8B\x85\x18\xF1\xFF\xFF\x8D\x48\x02\x3B\xC8\x77\x20\x83\xBD\x1C\xF1\xFF\xFF\x10\x8D\x85\x08\xF1\xFF\xFF\x89\x8D\x18\xF1\xFF\xFF\x0F\x43\x85\x08\xF1\xFF\xFF\xC6\x04\x08\x00\xEB\x10\x2B\xC8\x6A\x00\x51\x8D\x8D\x04\xF1\xFF\xFF\xE8\xFF\xEE\xFF\xFF\x83\xBD\x1C\xF1\xFF\xFF\x10\x8D\x8D\x08\xF1\xFF\xFF\x0F\xB6\x84\x35\x38\xF1\xFF\xFF\x0F\x43\x8D\x08\xF1\xFF\xFF\x50\x51\x68\x0C\x9E\xA9\x00\x6A\x00\x8D\x8D\x04\xF1\xFF\xFF\xE8\x8F\x02\x00\x00\x50\xE8\x59\xF9\xFF\xFF\x46\x83\xC4\x10\x81\xFE\xB6\x0E\x00\x00\x0F\x8C\x6B\xFF\xFF\xFF\xCC\x00\x6A\x00\xFF\xB5\x34\xF1\xFF\xFF\xC7\x85\x20\xF1\xFF\xFF\x00\x00\x00\x00\xFF\xB5\xCC\xEE\xFF\xFF\x6A\x00\x6A\x00\x57\xFF\x15\x40\x60\xA9\x00\x8B\xF0\x8B\xCE\xE8\xEB\x02\x00\x00\x84\xC0\x0F\x84\xF8\x00\x00\x00\x6A\xFF\x56\xFF\x15\x10\x60\xA9\x00\x83\xF8\xFF\x0F\x95\xC1\xE8\x6F\xF7\xFF\xFF\x84\xC0\x0F\x84\xDC\x00\x00\x00\x8D\x85\x20\xF1\xFF\xFF\x50\x56\xFF\x15\x1C\x60\xA9\x00\x8B\xC8\xE8\x72\x02\x00\x00\x84\xC0\x0F\x84\xBF\x00\x00\x00\x83\xBD\x20\xF1\xFF\xFF\x00\x75\x26\xFF\x35\xF4\xFA\xA9\x00\x8D\x8D\x28\xF1\xFF\xFF\x68\xC8\x92\xA9\x00\xE8\x0B\xD4\xFF\xFF\x68\x0C\xB1\xA9\x00\x8D\x85\x28\xF1\xFF\xFF\xE9\xE5\x00\x00\x00\x8B\x85\xC4\xEE\xFF\xFF\xCC\x05\xF4\xFA\xA9\x00\x89\xBD\x34\xF1\xFF\xFF\x8B\xBD\xC8\xEE\xFF\xFF\x8B\x40\x3C\x0F\xB7\x4F\x06\x8D\x04\x88\x83\xC0\x04\x8D\x8D\x34\xF1\xFF\xFF\x50\xFF\xB5\xD0\xEE\xFF\xFF\xE8\x14\x01\x00\x00\x33\xC0\x33\xF6\x66\x3B\x47\x06\x73\x3A\x8D\x8F\xF8\x00\x00\x00\x0F\x1F\x40\x00\x0F\xB7\xC6\x8D\x04\x80\xF7\x44\xC1\x24\x00\x00\x00\x02\x74\x19\xFF\x74\xC1\x10\xFF\x74\xC1\x0C\x8D\x8D\x34\xF1\xFF\xFF\xE8\xDD\x00\x00\x00\x8D\x8F\xF8\x00\x00\x00\x46\x66\x3B\x77\x06\x72\xD0\x51\x8D\x8D\x24\xF1\xFF\xFF\xE8\x74\x00\x00\x00\xC6\x85\xD7\xEE\xFF\xFF\x01\xEB\x13\x51\x8D\x8D\x24\xF1\xFF\xFF\xE8\x5F\x00\x00\x00\xC6\x85\xD7\xEE\xFF\xFF\x00\x8D\x8D\x04\xF1\xFF\xFF\xE8\x6D\xEB\xFF\xFF\x8D\x8D\x04\xF1\xFF\xFF\xE8\x22\xF3\xFF\xFF\x8A\x85\xD7\xEE\xFF\xFF\xE9\x2E\xFC\xFF\xFF\xFF\x35\xD4\xEA\xA9\x00\x68\xC8\x92\xA9\x00\x8D\x8D\xB8\xEE\xFF\xFF\xE8\x21\xD3\xFF\xFF\x68\x0C\xB1\xA9\x00\x8D\x85\xB8\xEE\xFF\xFF\x50\xE8\x41\xDC\x00\x00\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\x56\x8B\xF1\x8B\x06\x85\xC0\x74\x35\x8B\x4E\x04\x85\xC9\x74\x0F\x68\x00\x80\x00\x00\x6A\x00\x51\x50\xFF\x15\x44\x60\xA9\x00\x8B\x46\x08\x85\xC0\x74\x10\x68\x00\x80\x00\x00\x6A\x00\x50\xFF\x36\xFF\x15\x44\x60\xA9\x00\xFF\x36\xFF\x15\x2C\x60\xA9\x00\x8B\x46\x0C\x5E\x85\xC0\x74\x07\x50\xFF\x15\x2C\x60\xA9\x00\xC2\x04\x00\x55\x8B\xEC\x83\xEC\x0C\xA1\x84\xD0\xA9\x00\x33\xC5\x89\x45\xFC\x8B\x45\x08\x53\x56\x57\x8B\x7D\x0C\x8B\xD9\x57\x89\x45\xF4\xE8\xDC\xB9\x00\x00\x8B\xF0\x83\xC4\x04\x85\xF6\x74\x0E\x57\x6A\x00\x56\xE8\xA5\xDB\x00\x00\x83\xC4\x0C\xEB\x02\x33\xF6\x6A\x00\x57\x56\xFF\x75\xF4\xFF\x33\xFF\x15\xBC\x60\xA9\x00\x8D\x45\xF8\x50\x6A\x01\x57\xFF\x75\xF4\xFF\x33\xFF\x15\x30\x60\xA9\x00\x68\x00\x40\x00\x00\x57\xFF\x75\xF4\xFF\x33\xFF\x15\x44\x60\xA9\x00\x85\xF6\x74\x09\x56\xE8\x67\xB9\x00\x00\x83\xC4\x04\x8B\x4D\xFC\x5F\x5E\x33\xCD\x5B\xE8\x07\xB0\x00\x00\x8B\xE5\x5D\xC2\x08\x00\xCC\x55\x8B\xEC\x56\x8B\xF1\x57\x8B\x7D\x08\x3B\x7E\x14\x76\x34\x68\x6E\x0C\x00\x00\x68\x28\x8C\xA9\x00\x68\x14\x9E\xA9\x00\xFF\x15\x0C\x61\xA9\x00\x6A\x00\x68\x6E\x0C\x00\x00\x68\x28\x8C\xA9\x00\x68\x90\x9E\xA9\x00\x68\x50\x9E\xA9\x00\xFF\x15\xA4\x61\xA9\x00\x83\xC4\x20\x83\x7E\x18\x10\x72\x0B\x8B\x46\x04\x03\xC7\x5F\x5E\x5D\xC2\x04\x00\x8D\x47\x04\x5F\x03\xC6\x5E\x5D\xC2\x04\x00\xCC\x55\x8B\xEC\x83\xEC\x0C\x85\xC9\x74\x0C\xFF\x05\xFC\xFA\xA9\x00\xB0\x01\x8B\xE5\x5D\xC3\xFF\x35\xFC\xFA\xA9\x00\x8D\x4D\xF4\x68\xC8\x92\xA9\x00\xE8\x97\xD1\xFF\xFF\x68\x0C\xB1\xA9\x00\x8D\x45\xF4\x50\xE8\xBA\xDA\x00\x00\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\x55\x8B\xEC\x83\xEC\x0C\x85\xC9\x74\x0C\xFF\x05\xF8\xFA\xA9\x00\xB0\x01\x8B\xE5\x5D\xC3\xFF\x35\xF8\xFA\xA9\x00\x8D\x4D\xF4\x68\xC8\x92\xA9\x00\xE8\x57\xD1\xFF\xFF\x68\x0C\xB1\xA9\x00\x8D\x45\xF4\x50\xE8\x7A\xDA\x00\x00\xCC\xFF\x25\x14\x61\xA9\x00\xCC\xCC\x55\x8B\xEC\x51\x89\x4D\xFC\x8B\x45\xFC\x8B\x4D\x08\x89\x08\x8B\x55\xFC\x8B\x45\x0C\x89\x42\x04\x8B\x45\xFC\x8B\xE5\x5D\xC2\x08\x00\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\x55\x8B\xEC\x6A\xFF\x68\xC0\x48\xA9\x00\x64\xA1\x00\x00\x00\x00\x50\x83\xEC\x18\x56\xA1\x84\xD0\xA9\x00\x33\xC5\x50\x8D\x45\xF4\x64\xA3\x00\x00\x00\x00\x89\x4D\xEC\x8B\x45\xEC\x8B\x48\x04\x8B\x55\xEC\x8B\x72\x04\x8B\x01\x8B\x48\x08\x89\x4D\xE8\x8B\x4D\xE8\xFF\x15\x48\x62\xA9\x00\x8B\xCE\xFF\x55\xE8\x89\x45\xE0\x8B\x55\xE0\x89\x55\xF0\x83\x7D\xF0\x00\x74\x20\x6A\x01\x8B\x45\xF0\x8B\x08\x8B\x11\x89\x55\xE4\x8B\x4D\xE4\xFF\x15\x48\x62\xA9\x00\x8B\x4D\xF0\xFF\x55\xE4\x89\x45\xDC\xEB\x07\xC7\x45\xDC\x00\x00\x00\x00\x8B\x4D\xF4\x64\x89\x0D\x00\x00\x00\x00\x59\x5E\x8B\xE5\x5D\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\x55\x8B\xEC\x83\xEC\x14\x89\x4D\xEC\x83\x3D\xA0\xD3\xA9\x00\x00\x74\x3D\xA1\xA0\xD3\xA9\x00\x89\x45\xFC\x8B\x4D\xFC\x8B\x11\x89\x15\xA0\xD3\xA9\x00\x8B\x45\xFC\x89\x45\xF4\x8B\x4D\xF4\x89\x4D\xF8\x83\x7D\xF8\x00\x74\x0F\x6A\x01\x8B\x4D\xF8\xE8\x8F\x00\x00\x00\x89\x45\xF0\xEB\x07\xC7\x45\xF0\x00\x00\x00\x00\xEB\xBA\x8B\xE5\x5D\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\x55\x8B\xEC\x83\xEC\x08\x83\x7D\x08\x00\x76\x08\x8B\x45\x08\x89\x45\xFC\xEB\x07\xC7\x45\xFC\x01\x00\x00\x00\x6A\x22\x68\x40\x64\xA9\x00\x6A\x02\x8B\x4D\xFC\x51\xFF\x15\xBC\x61\xA9\x00\x83\xC4\x10\x89\x45\xF8\x83\x7D\xF8\x00\x75\x05\xE8\x89\xFE\xFF\xFF\x8B\x45\xF8\x8B\xE5\x5D\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\x55\x8B\xEC\x6A\x02\x8B\x45\x08\x50\xFF\x15\xB8\x61\xA9\x00\x83\xC4\x08\x5D\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\x55\x8B\xEC\x51\x89\x4D\xFC\x8B\x4D\xFC\xE8\x81\xFE\xFF\xFF\x8B\x45\x08\x83\xE0\x01\x74\x24\x8B\x4D\x08\x83\xE1\x04\x75\x0E\x8B\x55\xFC\x52\xE8\xB8\xFF\xFF\xFF\x83\xC4\x04\xEB\x0E\x6A\x08\x8B\x45\xFC\x50\xE8\xF8\xD3\xFF\xFF\x83\xC4\x08\x8B\x45\xFC\x8B\xE5\x5D\xC2\x04\x00\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\x55\x8B\xEC\x6A\xFF\x68\xEB\x48\xA9\x00\x64\xA1\x00\x00\x00\x00\x50\x83\xEC\x0C\xA1\x84\xD0\xA9\x00\x33\xC5\x50\x8D\x45\xF4\x64\xA3\x00\x00\x00\x00\x6A\x08\xE8\x14\xFF\xFF\xFF\x83\xC4\x04\x89\x45\xF0\xC7\x45\xFC\x00\x00\x00\x00\x83\x7D\xF0\x00\x74\x18\x8B\x45\x08\x50\x8B\x0D\xA0\xD3\xA9\x00\x51\x8B\x4D\xF0\xE8\xBE\xFD\xFF\xFF\x89\x45\xEC\xEB\x07\xC7\x45\xEC\x00\x00\x00\x00\x8B\x55\xEC\x89\x55\xE8\xC7\x45\xFC\xFF\xFF\xFF\xFF\x8B\x45\xE8\xA3\xA0\xD3\xA9\x00\x8B\x4D\xF4\x64\x89\x0D\x00\x00\x00\x00\x59\x8B\xE5\x5D\xC3\xFF\x25\xE8\x60\xA9\x00\xFF\x25\xE4\x60\xA9\x00\xFF\x25\xE0\x60\xA9\x00\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\x55\x8B\xEC\x51\x89\x4D\xFC\x8B\x45\xFC\x8B\xE5\x5D\xC2\x04\x00\x55\x8B\xEC\x8B\x45\x08\x8B\x4D\x0C\xD3\xC8\x5D\xC3\xCC\xCC\xCC\x56\x8B\xF1\x0F\x57\xC0\x8D\x46\x04\x50\xC7\x06\x28\x6D\xA9\x00\x66\x0F\xD6\x00\x8B\x44\x24\x0C\x83\xC0\x04\x50\xE8\x82\xD7\x00\x00\x83\xC4\x08\xC7\x06\x40\x6D\xA9\x00\x8B\xC6\x5E\xC2\x04\x00\x0F\x57\xC0\x8B\xC1\x66\x0F\xD6\x41\x04\xC7\x41\x04\x48\x6D\xA9\x00\xC7\x01\x40\x6D\xA9\x00\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\x8D\x41\x04\xC7\x01\x28\x6D\xA9\x00\x50\xE8\x3E\xD7\x00\x00\x59\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\x56\x8B\xF1\x8D\x46\x04\xC7\x06\x28\x6D\xA9\x00\x50\xE8\x1B\xD7\x00\x00\x83\xC4\x04\xF6\x44\x24\x08\x01\x74\x0B\x6A\x0C\x56\xE8\x2C\xB5\x00\x00\x83\xC4\x08\x8B\xC6\x5E\xC2\x04\x00\xCC\xCC\xCC\x57\x56\x8B\x44\x24\x0C\x8B\x7C\x24\x10\x8D\x04\x88\x8D\x3C\x8F\x8D\x14\x8A\xF7\xD9\xF7\xC1\x02\x00\x00\x00\x74\x05\x83\xE9\x02\xEB\x17\xE3\x32\x8B\x34\x88\x13\x34\x8F\x89\x34\x8A\x8B\x74\x88\x04\x13\x74\x8F\x04\x89\x74\x8A\x04\x8B\x74\x88\x08\x13\x74\x8F\x08\x89\x74\x8A\x08\x8B\x74\x88\x0C\x13\x74\x8F\x0C\x89\x74\x8A\x0C\x8D\x49\x04\xEB\xCC\xB8\x00\x00\x00\x00\x0F\x92\xC0\x5E\x5F\xC2\x08\x00\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\x57\x56\x8B\x44\x24\x0C\x8B\x7C\x24\x10\x8D\x04\x88\x8D\x3C\x8F\x8D\x14\x8A\xF7\xD9\xF7\xC1\x02\x00\x00\x00\x74\x05\x83\xE9\x02\xEB\x17\xE3\x32\x8B\x34\x88\x1B\x34\x8F\x89\x34\x8A\x8B\x74\x88\x04\x1B\x74\x8F\x04\x89\x74\x8A\x04\x8B\x74\x88\x08\x1B\x74\x8F\x08\x89\x74\x8A\x08\x8B\x74\x88\x0C\x1B\x74\x8F\x0C\x89\x74\x8A\x0C\x8D\x49\x04\xEB\xCC\xB8\x00\x00\x00\x00\x0F\x92\xC0\x5E\x5F\xC2\x08\x00\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\x53\x8B\x5C\x24\x10\x55\x8B\x6C\x24\x10\x56\x57\x8B\x45\x00\xF7\x23\x8B\xCA\x8B\x54\x24\x14\x89\x02\x8B\x45\x00\xF7\x63\x04\x8B\xF0\x8B\xFA\x8B\x45\x04\x03\xF1\x83\xD7\x00\xF7\x23\x03\xC6\x8B\xCA\x8B\x74\x24\x14\x83\xD1\x00\x89\x46\x04\x8B\x45\x04\xF7\x63\x04\x03\xC1\x83\xD2\x00\x03\xC7\x5F\x83\xD2\x00\x89\x46\x08\x89\x56\x0C\x5E\x5D\x5B\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\x53\x55\x8B\x6C\x24\x14\x56\x8B\x74\x24\x14\x57\x8B\x06\xF7\x65\x00\x8B\xCA\x8B\x54\x24\x14\x89\x02\x8B\x06\xF7\x65\x04\x8B\xF0\x8B\xFA\x03\xF1\x8B\x4C\x24\x18\x83\xD7\x00\x33\xDB\x8B\x41\x04\xF7\x65\x00\x03\xC6\x13\xD3\x03\xFA\x8B\x54\x24\x14\x13\xDB\x89\x42\x04\x8B\x01\xF7\x65\x08\x8B\xF0\x8B\x41\x04\x03\xF7\x8B\x7C\x24\x1C\x83\xD2\x00\x33\xED\x03\xDA\x13\xED\xF7\x67\x04\x8B\xC8\x03\xCE\x8B\x74\x24\x18\x83\xD2\x00\x03\xDA\x8B\x46\x08\x83\xD5\x00\xF7\x27\x03\xC1\x8B\x4C\x24\x14\x83\xD2\x00\x03\xDA\x89\x41\x08\x8B\xCE\x83\xD5\x00\x8B\x01\xF7\x67\x0C\x8B\xF0\x8B\x41\x04\x03\xF3\x8B\x5C\x24\x1C\x83\xD2\x00\x33\xFF\x03\xEA\x13\xFF\xF7\x63\x08\x8B\xC8\x03\xCE\x8B\x74\x24\x18\x83\xD2\x00\x03\xEA\x8B\x46\x08\x83\xD7\x00\xF7\x63\x04\x8B\xF0\x03\xF1\x8B\x4C\x24\x18\x83\xD2\x00\x03\xEA\x8B\x41\x0C\x83\xD7\x00\xF7\x23\x03\xC6\x83\xD2\x00\x03\xEA\x8B\x54\x24\x14\x83\xD7\x00\x89\x42\x0C\x8B\x41\x04\xF7\x63\x0C\x8B\xF0\x8B\x41\x08\x03\xF5\x8B\x6C\x24\x1C\x83\xD2\x00\x33\xDB\x03\xFA\x13\xDB\xF7\x65\x08\x8B\xC8\x03\xCE\x8B\x74\x24\x18\x83\xD2\x00\x03\xFA\x8B\x46\x0C\x83\xD3\x00\xF7\x65\x04\x03\xC1\x8B\x4C\x24\x14\x83\xD2\x00\x03\xFA\x89\x41\x10\x8B\xCE\x83\xD3\x00\x8B\x41\x08\xF7\x65\x0C\x8B\xF0\x8B\x41\x0C\x03\xF7\x83\xD2\x00\x33\xFF\x03\xDA\x13\xFF\xF7\x65\x08\x03\xC6\x8B\xCA\x8B\x54\x24\x14\x00" };
	PX_DEF CALL_DLL_THREAD_SIZE = 3768;
	byte_t bStub[ ] { "\x60\xE8\x00\x00\x00\x00\x5B\x83\xEB\x06\xB8\xCC\xCC\xCC\xCC\xBA\xCC\xCC\xCC\xCC\x52\xFF\xD0\x61\x68\xCC\xCC\xCC\xCC\xC3" };
	PX_DEF STUB_SIZE = 30u;
	PX_DEF INJECTION_INFO_SIZE = 24u;

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

	bool PX_API Inject( const LPVOID& pDLL, const std::wstring& wstrExecutableName, injection_info_t* injInfo )
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

		// open handle to target process
		const auto dwProcessID = GetProcessID( wstrExecutableName );
		hTarget = OpenProcess( PROCESS_ALL_ACCESS, FALSE, dwProcessID );
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
		pMemory = VirtualAllocEx( hTarget, nullptr, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE );
		pStub = VirtualAllocEx( hTarget, nullptr, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE );
		if ( !WriteProcessMemory( hTarget, pMemory, injInfo, INJECTION_INFO_SIZE, nullptr ) ||
			 !WriteProcessMemory( hTarget, PVOID( ptr_t( pMemory ) + sizeof( injection_info_t ) ), bCallDLLThread, CALL_DLL_THREAD_SIZE, nullptr ) )
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

		for ( auto u = 0u; u < STUB_SIZE - sizeof( ptr_t ); u++ )
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

		if ( !WriteProcessMemory( hTarget, pStub, bStub, STUB_SIZE, nullptr ) )
		{
			ResumeThread( hThread );
			fnCleanup( true );
			return false;
		}

		ctxThread.Eip = ptr_t( pStub );
		SetThreadContext( hThread, &ctxThread );
		ResumeThread( hThread );

		// Wait ~5 seconds for the thread to run and do it's job and get out of our function before we wipe it.
		Wait< std::chrono::seconds>( 5ull );

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
		fnWipeMemory( PVOID( static_cast< injection_info_t* >( pMemory ) + 1 ), CALL_DLL_THREAD_SIZE );

		fnCleanup( false );
		return true;
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

	void PX_API Delete( )
	{

	}
}
