/// System Utilities.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#define USE_DEFINITIONS
#include "../../Framework.hpp"

device_info_t::device_info_t( std::string *pValue, const std::wstring &wstrDevice, const std::wstring &wstrProperty ): pValue( pValue ), wstrDevice( wstrDevice ), wstrProperty( wstrProperty )
{ }

void CSystemInformation::AddDeviceToQueue( const device_info_t &_DeviceInfo )
{
	vecInformation.emplace_back( _DeviceInfo );
}

bool CSystemInformation::ProcessQueue( )
{ // todo https://docs.microsoft.com/en-us/windows/desktop/api/oleauto/nf-oleauto-geterrorinfo for logging
	{
		const auto hrReturn = CoInitialize( nullptr );
		if ( hrReturn != S_OK && hrReturn != S_FALSE )
			return _Log.Log( EPrefix::ERROR, ELocation::SYSTEM_UTILITIES,
							 ENC( "Couldn't initialize COM library for device information retrieval. Error %i." ), hrReturn ), false;
	}

	{
		const auto hrReturn = CoInitializeSecurity( nullptr, -1, nullptr, nullptr, RPC_C_AUTHN_LEVEL_DEFAULT,
													RPC_C_IMP_LEVEL_IMPERSONATE, nullptr, EOAC_NONE, nullptr );
		if ( hrReturn != S_OK && hrReturn != RPC_E_TOO_LATE )
			return CoUninitialize( ), _Log.Log( EPrefix::ERROR, ELocation::SYSTEM_UTILITIES,
												ENC( "Couldn't set security for device information retrieval. Error %i." ), hrReturn ), false;
	}

	IWbemLocator *pLocator = nullptr;
	{
		const auto hrReturn = CoCreateInstance( CLSID_WbemLocator, nullptr, CLSCTX_INPROC_SERVER,
												IID_IWbemLocator, reinterpret_cast< LPVOID* >( &pLocator ) );
		if ( hrReturn != S_OK || pLocator == nullptr )
			return CoUninitialize( ), _Log.Log( EPrefix::ERROR, ELocation::SYSTEM_UTILITIES,
												ENC( "Couldn't create locator object for device information retrieval. Error %i." ), hrReturn ), false;
	}

	IWbemServices *pServices = nullptr;
	{
		auto hrReturn = pLocator->ConnectServer( bstr_t( ENC( L"ROOT\\CIMV2" ) ), nullptr, nullptr, nullptr,
												 0, nullptr, nullptr, &pServices );
		if ( hrReturn != S_OK || pServices == nullptr )
			return pLocator->Release( ), CoUninitialize( ),
					_Log.Log( EPrefix::ERROR, ELocation::SYSTEM_UTILITIES,
							  ENC( "Couldn't connect DCOM to WMI for device information retrieval. Error %i." ), hrReturn ), false;

		hrReturn = CoSetProxyBlanket( pServices, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, nullptr, RPC_C_AUTHN_LEVEL_CALL,
									  RPC_C_IMP_LEVEL_IMPERSONATE, nullptr, EOAC_NONE );
		if ( hrReturn != S_OK )
			return pServices->Release( ), pLocator->Release( ), CoUninitialize( ),
					_Log.Log( EPrefix::ERROR, ELocation::SYSTEM_UTILITIES,
							  ENC( "Couldn't set authentication information on proxy for device information retrieval. Error %i." ), hrReturn ), false;
	}

	for ( auto& _DeviceInformation : vecInformation )
	{
		_DeviceInformation.pValue->clear( );

		IEnumWbemClassObject *pEnumerator = nullptr;
		{
			const auto hrReturn = pServices->ExecQuery( bstr_t( ENC( L"WQL" ) ), bstr_t( ( device_info_t::wstrCommand + _DeviceInformation.wstrDevice ).c_str( ) ),
														WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, nullptr, &pEnumerator );
			if ( hrReturn != S_OK || pEnumerator == nullptr )
				return pServices->Release( ), pLocator->Release( ), CoUninitialize( ),
				_Log.Log( EPrefix::ERROR, ELocation::SYSTEM_UTILITIES,
						  ENC( "Couldn't set authentication information on proxy for device information retrieval. Error %i." ), hrReturn ), false;
		}

		while ( pEnumerator )
		{
			IWbemClassObject *pClassObject = nullptr;
			ULONG uReturn;
			auto hrReturn = pEnumerator->Next( WBEM_INFINITE, 1, &pClassObject, &uReturn );
			if ( uReturn == 0 )
				break;

			if ( hrReturn != S_OK )
			{
				pEnumerator->Release( ),
					_Log.Log( EPrefix::ERROR, ELocation::SYSTEM_UTILITIES,
							  ENC( "Couldn't iterate through device information. Error %i." ), hrReturn );
				break;
			}

			VARIANT vtProp { };
			hrReturn = pClassObject->Get( _DeviceInformation.wstrProperty.c_str( ), 0, &vtProp, nullptr, nullptr );
			if ( hrReturn != S_OK )
			{
				pClassObject->Release( ), pEnumerator->Release( ),
					_Log.Log( EPrefix::ERROR, ELocation::SYSTEM_UTILITIES,
							  ENC( "Couldn't iterate through device information. Error %i." ), hrReturn );
				break;
			}
			if ( vtProp.bstrVal == nullptr || reinterpret_cast< std::uintptr_t >( vtProp.bstrVal ) == 0x5 )
			{
				pClassObject->Release( ),
					_Log.Log( EPrefix::WARNING, ELocation::SYSTEM_UTILITIES,
							  ENC( "Prop didn't exist." ), hrReturn );
				continue;
			}

			if ( !_DeviceInformation.pValue->empty( ) )
				*_DeviceInformation.pValue += '\n';

			*_DeviceInformation.pValue += string_cast< std::string >( std::wstring( vtProp.bstrVal ) );

			hrReturn = VariantClear( &vtProp );
			if ( hrReturn != S_OK )
			{
				pClassObject->Release( ), pEnumerator->Release( ),
					_Log.Log( EPrefix::ERROR, ELocation::SYSTEM_UTILITIES,
							  ENC( "Couldn't clear device information prop. Error %i." ), hrReturn );
				break;
			}
			pClassObject->Release( );
		}

		if ( _DeviceInformation.pValue->empty( ) )
			_Log.Log( EPrefix::ERROR, ELocation::SYSTEM_UTILITIES, ENC( "Unable to get device information. Device: %s. Property: %s." ),
					  string_cast< std::string >( _DeviceInformation.wstrDevice ).c_str( ), string_cast< std::string >( _DeviceInformation.wstrProperty ).c_str( ) );

		pEnumerator->Release( );
	}
	pServices->Release( ); // todo probably should check the returns of release and uninits
	pLocator->Release( );
	CoUninitialize( );

	vecInformation.clear( );
	return true;
}

bool CSystemInformation::GetProgramList( std::string &strOut )
{
	AddDeviceToQueue( device_info_t( &strOut, ENC( L"Win32_Product" ), ENC( L"Name" ) ) );
	return ProcessQueue( );
}

std::string CSystemInformation::GetHardwareHash( )
{
	std::string strReturn;

	strReturn.resize( VMProtectGetCurrentHWID( nullptr, NULL ) );
	VMProtectGetCurrentHWID( &strReturn[ 0 ], strReturn.size( ) );
	return CRYPTO.GenerateHash( strReturn );
}

bool CSystemInformation::GetProcessThreads( DWORD dwProcessID, thread_list_t& _Out )
{
	if ( dwProcessID == 0
		 || dwProcessID == UINT_MAX )
		return _Log.Log( EPrefix::ERROR, ELocation::SYSTEM_UTILITIES, ENC( "Invalid process ID passed to GetProcessThreads( )." ) ), false;

	const auto hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPTHREAD, NULL );
	_Out.clear( );

	if ( hSnapshot == INVALID_HANDLE_VALUE
		 || hSnapshot == nullptr )
		return _Log.Log( EPrefix::ERROR, ELocation::SYSTEM_UTILITIES, ENC( "Unable to get system threads." ) ), false;

	auto bReturn = true;
	THREADENTRY32 _CurrentThread { sizeof( THREADENTRY32 ) };

	if ( Thread32First( hSnapshot, &_CurrentThread ) != TRUE )
	{
		_Log.Log( EPrefix::ERROR, ELocation::SYSTEM_UTILITIES, ENC( "Unable to get information of first thread." ) );
		bReturn = false;
	}
	else
		do
		{
			if ( _CurrentThread.th32OwnerProcessID == dwProcessID )
				_Out.emplace_back( std::pair< DWORD, DWORD >( _CurrentThread.th32ThreadID, _CurrentThread.tpBasePri ) );

		} while ( Thread32Next( hSnapshot, &_CurrentThread ) == TRUE );

	if ( CloseHandle( hSnapshot ) == FALSE )
		_Log.Log( EPrefix::WARNING, ELocation::SYSTEM_UTILITIES, ENC( "Unable to close process thread snapshot properly." ) );

	return bReturn && !_Out.empty( );
}

bool CSystemInformation::GetProcessID( const std::string &strExecutableName, DWORD& dwOut )
{
	const auto hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, NULL );
	dwOut = 0;

	if ( hSnapshot == INVALID_HANDLE_VALUE
		 || hSnapshot == nullptr )
		return _Log.Log( EPrefix::ERROR, ELocation::SYSTEM_UTILITIES, ENC( "Unable to get processes." ) ), false;

	auto bReturn = true;
	PROCESSENTRY32 _CurrentProcess { sizeof( PROCESSENTRY32 ) };
	if ( Process32First( hSnapshot, &_CurrentProcess ) != TRUE )
	{
		_Log.Log( EPrefix::ERROR, ELocation::SYSTEM_UTILITIES, ENC( "Unable to find first process." ) );
		bReturn = false;
	}
	else
		do
		{
			if ( _CurrentProcess.szExeFile == strExecutableName )
				dwOut = _CurrentProcess.th32ProcessID;
		} while ( Process32Next( hSnapshot, &_CurrentProcess ) == TRUE
				  && dwOut == 0 );

	if ( CloseHandle( hSnapshot ) == FALSE )
		_Log.Log( EPrefix::WARNING, ELocation::SYSTEM_UTILITIES, ENC( "Unable to close process thread snapshot properly." ) );

	return bReturn && dwOut != NULL;
}

bool CSystemInformation::GetExecutableByProcessID( DWORD dwProcessID, std::string &strOut )
{
	const auto hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, NULL );
	strOut.clear( );

	if ( hSnapshot == INVALID_HANDLE_VALUE
		 || hSnapshot == nullptr )
		return _Log.Log( EPrefix::ERROR, ELocation::SYSTEM_UTILITIES, ENC( "Unable to get processes." ) ), false;

	auto bReturn = true;
	PROCESSENTRY32 _CurrentProcess { sizeof( PROCESSENTRY32 ) };
	if ( Process32First( hSnapshot, &_CurrentProcess ) != TRUE )
	{
		_Log.Log( EPrefix::ERROR, ELocation::SYSTEM_UTILITIES, ENC( "Unable to find first process." ) );
		bReturn = false;
	}
	else
		do
		{
			if ( _CurrentProcess.th32ProcessID == dwProcessID )
				strOut = _CurrentProcess.szExeFile;

		} while ( Process32Next( hSnapshot, &_CurrentProcess ) == TRUE
				  && strOut.empty( ) );

	if ( CloseHandle( hSnapshot ) == FALSE )
		_Log.Log( EPrefix::WARNING, ELocation::SYSTEM_UTILITIES, ENC( "Unable to close process thread snapshot properly." ) );

	return bReturn && !strOut.empty( );
}

void CSystemInformation::TerminateProcessByID( DWORD dwProcessID )
{
	
}

bool CSystemInformation::GetProcesses( std::vector< std::string > &vecOut )
{
	const auto hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, NULL );

	if ( hSnapshot == INVALID_HANDLE_VALUE
		 || hSnapshot == nullptr )
		return _Log.Log( EPrefix::ERROR, ELocation::SYSTEM_UTILITIES, ENC( "Unable to get processes." ) ), false;

	auto bReturn = true;
	PROCESSENTRY32 _CurrentProcess { sizeof( PROCESSENTRY32 ) };
	if ( Process32First( hSnapshot, &_CurrentProcess ) != TRUE )
	{
		_Log.Log( EPrefix::ERROR, ELocation::SYSTEM_UTILITIES, ENC( "Unable to find first process." ) );
		bReturn = false;
	}
	else
		do
		{
			vecOut.emplace_back( _CurrentProcess.szExeFile );
		} while ( Process32Next( hSnapshot, &_CurrentProcess ) == TRUE );

	if ( CloseHandle( hSnapshot ) == FALSE )
		_Log.Log( EPrefix::WARNING, ELocation::SYSTEM_UTILITIES, ENC( "Unable to close process process snapshot properly." ) );

	return bReturn && !vecOut.empty( );
}

bool CSystemInformation::GetProgramList( std::vector< std::string > &vecOut )
{
	return false;
}

bool CSystemInformation::GetExecutablePath( const std::string &strExecutableName, std::string &strOut )
{
	DWORD dwProcessID;
	if ( !GetProcessID( strExecutableName, dwProcessID ) )
		return false;

	const auto hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, dwProcessID );

	if ( hSnapshot == INVALID_HANDLE_VALUE
		 || hSnapshot == nullptr )
		return _Log.Log( EPrefix::ERROR, ELocation::SYSTEM_UTILITIES, ENC( "Unable to get modules." ) ), false;

	strOut.clear( );
	auto bReturn = true;
	MODULEENTRY32 _Module { sizeof( MODULEENTRY32 ) };
	if ( Module32First( hSnapshot, &_Module ) != TRUE )
	{
		_Log.Log( EPrefix::ERROR, ELocation::SYSTEM_UTILITIES, ENC( "Unable to find first module." ) );
		bReturn = false;
	}
	else
		do
		{
			if ( _Module.szModule == strExecutableName )
				strOut = FS.PathToDirectory( _Module.szExePath );
		} while ( Module32Next( hSnapshot, &_Module ) == TRUE && strOut.empty( ) );

	if ( CloseHandle( hSnapshot ) == FALSE )
		_Log.Log( EPrefix::WARNING, ELocation::SYSTEM_UTILITIES, ENC( "Unable to close process module snapshot properly." ) );

	return bReturn && !strOut.empty( );
}

BOOL CALLBACK EnumWindowsProc(
	_In_		 HWND hwnd,
	_In_		 LPARAM lParam
)
{
	const auto lStyle = GetWindowLong( hwnd, GWL_STYLE );
	if ( ( lStyle & WS_VISIBLE ) > 0 )
		reinterpret_cast< std::vector< HWND >* >( lParam )->emplace_back( hwnd );

	return true;
}

std::vector< HWND > CSystemInformation::GetOpenWindows( )
{
	std::vector< HWND > vecWindows { };

	EnumWindows( EnumWindowsProc, reinterpret_cast< LPARAM >( &vecWindows ) );
	return vecWindows;
}

std::vector< HWND > CSystemInformation::GetCurrentProcessWindows( )
{
	auto vecReturn = GetOpenWindows( );

	for ( auto u = 0u; u < vecReturn.size( ); u++ )
	{
		DWORD dwProcessID;
		GetWindowThreadProcessId( vecReturn[ u ], &dwProcessID );

		if ( dwProcessID != GetCurrentProcessId( ) )
			vecReturn.erase( vecReturn.begin( ) + u ), u--;
	}

	return vecReturn;
}

std::vector< std::string > CSystemInformation::GetOpenWindowNames( )
{
	const auto vecWindows = GetOpenWindows( );
	std::vector< std::string > vecReturn;

	for ( auto &hwWindow: vecWindows )
	{
		std::string strWindow;

		strWindow.resize( MAX_PATH );
		const auto zSize = GetWindowText( hwWindow, &strWindow[ 0 ], MAX_PATH );
		if ( zSize != 0 )
		{
			strWindow.resize( zSize );
			DWORD dwProcessID;
			GetWindowThreadProcessId( hwWindow, &dwProcessID );
			std::string strProcess;
			if ( GetExecutableByProcessID( dwProcessID, strProcess ) )
				vecReturn.emplace_back( strProcess + ENC( " - " ) + strWindow.c_str( ) );
		}
	}

	return vecReturn;
}

bool CSystemInformation::GetModules( DWORD dwProcessID, std::vector< HMODULE > &vecOut )
{
	const auto hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, dwProcessID );

	vecOut.clear( );
	if ( hSnapshot == INVALID_HANDLE_VALUE
		 || hSnapshot == nullptr )
		return _Log.Log( EPrefix::ERROR, ELocation::SYSTEM_UTILITIES, ENC( "Unable to get modules." ) ), false;

	auto bReturn = true;
	MODULEENTRY32 _Module { sizeof( MODULEENTRY32 ) };
	if ( Module32First( hSnapshot, &_Module ) != TRUE )
	{
		_Log.Log( EPrefix::ERROR, ELocation::SYSTEM_UTILITIES, ENC( "Unable to find first module." ) );
		bReturn = false;
	}
	else
		do
		{
			vecOut.emplace_back( _Module.hModule );
		} while ( Module32Next( hSnapshot, &_Module ) == TRUE );

	if ( CloseHandle( hSnapshot ) == FALSE )
		_Log.Log( EPrefix::WARNING, ELocation::SYSTEM_UTILITIES, ENC( "Unable to close process module snapshot properly." ) );

	return bReturn && !vecOut.empty( );
}

bool CSystemInformation::ElevateProcess( HANDLE hProcess /*= GetCurrentProcess( )*/ )
{
	HANDLE hTokenSelf { };
	TOKEN_ELEVATION teSelf { };
	DWORD dwReturnLength;

	if ( FALSE == OpenProcessToken( hProcess, TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES, &hTokenSelf )
		 || !hTokenSelf
		 || FALSE == GetTokenInformation( hTokenSelf, TokenElevation, &teSelf, sizeof( TOKEN_ELEVATION ), &dwReturnLength ) )
		return hTokenSelf && CloseHandle( hTokenSelf ), false;

	TOKEN_PRIVILEGES tpNewDebug { };
	TOKEN_PRIVILEGES tpNewShutdown { };

	tpNewDebug.PrivilegeCount = 1;
	tpNewShutdown.PrivilegeCount = 1;

	tpNewDebug.Privileges[ 0 ].Attributes = SE_PRIVILEGE_ENABLED;
	tpNewShutdown.Privileges[ 0 ].Attributes = SE_PRIVILEGE_ENABLED;

	if ( FALSE == LookupPrivilegeValue( nullptr, SE_DEBUG_NAME, &tpNewDebug.Privileges[ 0 ].Luid )
		 || FALSE == LookupPrivilegeValue( nullptr, SE_SHUTDOWN_NAME, &tpNewShutdown.Privileges[ 0 ].Luid )
		 || FALSE == AdjustTokenPrivileges( hTokenSelf, FALSE, &tpNewDebug, 0, nullptr, nullptr )
		 || FALSE == AdjustTokenPrivileges( hTokenSelf, FALSE, &tpNewShutdown, 0, nullptr, nullptr ) )
		return hTokenSelf&& CloseHandle( hTokenSelf ), false;

	if ( FALSE == GetTokenInformation( hTokenSelf, TokenElevation, &teSelf, sizeof( TOKEN_ELEVATION ), &dwReturnLength )
		 || FALSE == teSelf.TokenIsElevated )
		return hTokenSelf && CloseHandle( hTokenSelf ), false;

	return true;
}

CSystemInformation::ESystemVersion CSystemInformation::GetOperatingSystemVersion( )
{
	static ESystemVersion enumResult = W_UNKNOWN;
	if ( enumResult != W_UNKNOWN )
		return enumResult;

	if ( !IsWindows8OrGreater( ) )
		throw std::runtime_error( ENC( "This program cannot run on your version of Windows." ) );

	RTL_OSVERSIONINFOW _OperatingSystemVersionInformation = { };
	if ( RtlGetVersion( &_OperatingSystemVersionInformation ) != STATUS_SUCCESS )
		throw std::runtime_error( ENC( "This program cannot run on a corrupted operating system." ) );

	if ( _OperatingSystemVersionInformation.dwBuildNumber >= BUILD_PREVIEW )
		return enumResult = W10_PREVIEW;

	if ( _OperatingSystemVersionInformation.dwBuildNumber >= BUILD_REDSTONE_CREATORS_OCTOBER_1809 )
		return enumResult = W10_REDSTONE_CREATORS_OCTOBER_1809;

	if ( _OperatingSystemVersionInformation.dwBuildNumber >= BUILD_REDSTONE_CREATORS_APRIL_1803 )
		return enumResult = W10_REDSTONE_CREATORS_APRIL_1803;

	if ( _OperatingSystemVersionInformation.dwBuildNumber >= BUILD_REDSTONE_CREATORS_FALL_1709 )
		return enumResult = W10_REDSTONE_CREATORS_FALL_1709;

	if ( _OperatingSystemVersionInformation.dwBuildNumber >= BUILD_REDSTONE_CREATORS_1703 )
		return enumResult = W10_REDSTONE_CREATORS_1703;

	if ( _OperatingSystemVersionInformation.dwBuildNumber >= BUILD_REDSTONE_ANNIVERSARY_1607 )
		return enumResult = W10_REDSTONE_ANNIVERSARY_1607;

	if ( _OperatingSystemVersionInformation.dwBuildNumber >= BUILD_REDSTONE_NOVEMBER_1511 )
		return enumResult = W10_REDSTONE_NOVEMBER_1511;

	if ( _OperatingSystemVersionInformation.dwBuildNumber >= BUILD_INITIAL_1507 )
		return enumResult = W10_INITIAL_1507;

	throw std::runtime_error( ENC( "This program cannot run on your version of Windows." ) );
}

vector2_t CSystemInformation::GetScreenSize( )
{
	const auto hwDesktop = GetDesktopWindow( );
	RECT recDesktop { };

	GetWindowRect( hwDesktop, &recDesktop );
	return { float( recDesktop.right - recDesktop.left ), float( recDesktop.bottom - recDesktop.top ) };
}

void CSystemInformation::OpenLink( const std::string & strLink )
{
	ShellExecute( nullptr, ENC( "open" ), strLink.c_str( ), nullptr, nullptr, SW_SHOWNORMAL );
}

bool CSystemInformation::GetClipboardData( std::string &strOut )
{
	if ( OpenClipboard( nullptr ) == 0 )
		return _Log.Log( EPrefix::ERROR, ELocation::SYSTEM_UTILITIES, ENC( "Failed to open clipboard for copying." ) ), false;

	const auto hClipboard =	::GetClipboardData( CF_TEXT );
	if ( hClipboard == nullptr )
	{
		_Log.Log( EPrefix::ERROR, ELocation::SYSTEM_UTILITIES, ENC( "Failed to get global memory for clipboard data." ) );
		if ( CloseClipboard( ) == 0 )
			_Log.Log( EPrefix::ERROR, ELocation::SYSTEM_UTILITIES, ENC( "Failed to close clipboard after error." ) );
		return false;
	}

	strOut = static_cast< char* >( hClipboard );

	if ( CloseClipboard( ) == 0 )
		_Log.Log( EPrefix::WARNING, ELocation::SYSTEM_UTILITIES, ENC( "Failed to close clipboard after error." ) );
	return true;
}

bool CSystemInformation::SetClipboardData( const std::string& strIn )
{
	if ( OpenClipboard( nullptr ) == 0 )
		return _Log.Log( EPrefix::ERROR, ELocation::SYSTEM_UTILITIES, ENC( "Failed to open clipboard for copying." ) ), false;

	if ( EmptyClipboard( ) == 0 )
	{
		_Log.Log( EPrefix::ERROR, ELocation::SYSTEM_UTILITIES, ENC( "Failed to empty clipboard for copying." ) );
		if ( CloseClipboard( ) == 0 )
			_Log.Log( EPrefix::ERROR, ELocation::SYSTEM_UTILITIES, ENC( "Failed to close clipboard after error." ) );
		return false;
	}

	const auto hClipboard = GlobalAlloc( GMEM_FIXED, strIn.length( ) + 1 );
	if ( hClipboard == nullptr )
	{
		_Log.Log( EPrefix::ERROR, ELocation::SYSTEM_UTILITIES, ENC( "Failed to create global memory for clipboard data." ) );
		if ( CloseClipboard( ) == 0 )
			_Log.Log( EPrefix::ERROR, ELocation::SYSTEM_UTILITIES, ENC( "Failed to close clipboard after error." ) );
		return false;
	}

	if ( strcpy_s( static_cast< char* >( hClipboard ), strIn.length( ) + 1, strIn.c_str( ) ) != 0 )
	{
		_Log.Log( EPrefix::ERROR, ELocation::SYSTEM_UTILITIES, ENC( "Failed to copy desired clipboard data to global clipboard memory." ) );
		if ( GlobalFree( hClipboard ) != nullptr )
			_Log.Log( EPrefix::ERROR, ELocation::SYSTEM_UTILITIES, ENC( "Failed to free global memory for clipboard data." ) );
		if ( CloseClipboard( ) == 0 )
			_Log.Log( EPrefix::ERROR, ELocation::SYSTEM_UTILITIES, ENC( "Failed to close clipboard after error." ) );
		return false;
	}

	if ( ::SetClipboardData( CF_TEXT, hClipboard ) == nullptr )
	{
		_Log.Log( EPrefix::ERROR, ELocation::SYSTEM_UTILITIES, ENC( "Failed to set clipboard data." ) );
		if ( GlobalFree( hClipboard ) != nullptr )
			_Log.Log( EPrefix::ERROR, ELocation::SYSTEM_UTILITIES, ENC( "Failed to free global memory for clipboard data." ) );
		if ( CloseClipboard( ) != 0 )
			_Log.Log( EPrefix::ERROR, ELocation::SYSTEM_UTILITIES, ENC( "Failed to close clipboard after error." ) );
		return false;
	}

	if ( CloseClipboard( ) == 0 )
		_Log.Log( EPrefix::WARNING, ELocation::SYSTEM_UTILITIES, ENC( "Failed to close clipboard after error." ) );
	return true;
}
