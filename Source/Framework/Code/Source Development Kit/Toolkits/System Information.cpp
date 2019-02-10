/// System Information.cpp

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
			return _Log.Log( EPrefix::ERROR, ELocation::SYSTEM_INFORMATION,
							 ENC( "Couldn't initialize COM library for device information retrieval. Error %i." ), hrReturn ), false;
	}

	{
		const auto hrReturn = CoInitializeSecurity( nullptr, -1, nullptr, nullptr, RPC_C_AUTHN_LEVEL_DEFAULT,
													RPC_C_IMP_LEVEL_IMPERSONATE, nullptr, EOAC_NONE, nullptr );
		if ( hrReturn != S_OK && hrReturn != RPC_E_TOO_LATE )
			return CoUninitialize( ), _Log.Log( EPrefix::ERROR, ELocation::SYSTEM_INFORMATION,
												ENC( "Couldn't set security for device information retrieval. Error %i." ), hrReturn ), false;
	}

	IWbemLocator *pLocator = nullptr;
	{
		const auto hrReturn = CoCreateInstance( CLSID_WbemLocator, nullptr, CLSCTX_INPROC_SERVER,
												IID_IWbemLocator, reinterpret_cast< LPVOID* >( &pLocator ) );
		if ( hrReturn != S_OK || pLocator == nullptr )
			return CoUninitialize( ), _Log.Log( EPrefix::ERROR, ELocation::SYSTEM_INFORMATION,
												ENC( "Couldn't create locator object for device information retrieval. Error %i." ), hrReturn ), false;
	}

	IWbemServices *pServices = nullptr;
	{
		auto hrReturn = pLocator->ConnectServer( bstr_t( ENC( L"ROOT\\CIMV2" ) ), nullptr, nullptr, nullptr,
												 0, nullptr, nullptr, &pServices );
		if ( hrReturn != S_OK || pServices == nullptr )
			return pLocator->Release( ), CoUninitialize( ),
					_Log.Log( EPrefix::ERROR, ELocation::SYSTEM_INFORMATION,
							  ENC( "Couldn't connect DCOM to WMI for device information retrieval. Error %i." ), hrReturn ), false;

		hrReturn = CoSetProxyBlanket( pServices, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, nullptr, RPC_C_AUTHN_LEVEL_CALL,
									  RPC_C_IMP_LEVEL_IMPERSONATE, nullptr, EOAC_NONE );
		if ( hrReturn != S_OK )
			return pServices->Release( ), pLocator->Release( ), CoUninitialize( ),
					_Log.Log( EPrefix::ERROR, ELocation::SYSTEM_INFORMATION,
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
				_Log.Log( EPrefix::ERROR, ELocation::SYSTEM_INFORMATION,
						  ENC( "Couldn't set authentication information on proxy for device information retrieval. Error %i." ), hrReturn ), false;
		}

		while ( pEnumerator )
		{
			IWbemClassObject *pClassObject = nullptr;
			ULONG uReturn;
			auto hrReturn = pEnumerator->Next( WBEM_INFINITE, 1, &pClassObject, &uReturn );
			if ( hrReturn != S_OK )
			{
				pEnumerator->Release( ), pServices->Release( ), pLocator->Release( ), CoUninitialize( ),
					_Log.Log( EPrefix::ERROR, ELocation::SYSTEM_INFORMATION,
							  ENC( "Couldn't iterate through device information. Error %i." ), hrReturn );
				break;
			}
			if ( uReturn == 0 )
				break;

			VARIANT vtProp;
			hrReturn = pClassObject->Get( _DeviceInformation.wstrProperty.c_str( ), 0, &vtProp, nullptr, nullptr );
			if ( hrReturn != S_OK )
			{
				pClassObject->Release( ), pEnumerator->Release( ), pServices->Release( ), pLocator->Release( ), CoUninitialize( ),
					_Log.Log( EPrefix::ERROR, ELocation::SYSTEM_INFORMATION,
							  ENC( "Couldn't iterate through device information. Error %i." ), hrReturn );
				break;
			}
			*_DeviceInformation.pValue += string_cast< std::string >( vtProp.bstrVal ) + '\n';

			hrReturn = VariantClear( &vtProp );
			if ( hrReturn != S_OK )
			{
				pClassObject->Release( ), pEnumerator->Release( ), pServices->Release( ), pLocator->Release( ), CoUninitialize( ),
					_Log.Log( EPrefix::ERROR, ELocation::SYSTEM_INFORMATION,
							  ENC( "Couldn't clear device information prop. Error %i." ), hrReturn );
				break;
			}
			pClassObject->Release( );
		}

		if ( _DeviceInformation.pValue->empty( ) )
			_Log.Log( EPrefix::ERROR, ELocation::SYSTEM_INFORMATION, ENC( "Unable to get device information. Device: %s. Property: %s." ),
					  string_cast< std::string >( _DeviceInformation.wstrDevice ).c_str( ), string_cast< std::string >( _DeviceInformation.wstrProperty ).c_str( ) );

		pEnumerator->Release( );
	}
	pServices->Release( );
	pLocator->Release( );
	CoUninitialize( );

	vecInformation.clear( );
	return true;
}

bool CSystemInformation::GetProcessThreads( DWORD dwProcessID, std::vector< DWORD >& vecOut )
{
	if ( dwProcessID == 0
		 || dwProcessID == UINT_MAX )
	{
		_Log.Log( EPrefix::ERROR, ELocation::SYSTEM_INFORMATION, ENC( "Invalid process ID passed to GetProcessThreads( )." ) );
		return { };
	}

	const auto hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPTHREAD, NULL );
	vecOut.clear( );

	if ( hSnapshot == INVALID_HANDLE_VALUE
		 || hSnapshot == nullptr )
		return _Log.Log( EPrefix::WARNING, ELocation::SYSTEM_INFORMATION, ENC( "Unable to get system threads." ) ), false;

	auto bReturn = true;
	THREADENTRY32 _CurrentThread { sizeof( THREADENTRY32 ) };

	if ( Thread32First( hSnapshot, &_CurrentThread ) != TRUE )
	{
		_Log.Log( EPrefix::ERROR, ELocation::SYSTEM_INFORMATION, ENC( "Unable to get information of first thread." ) );
		bReturn = false;
	}
	else
		do
		{
			if ( _CurrentThread.th32OwnerProcessID == dwProcessID )
				vecOut.emplace_back( _CurrentThread.th32ThreadID );

		} while ( Thread32Next( hSnapshot, &_CurrentThread ) == TRUE );

	if ( CloseHandle( hSnapshot ) == FALSE )
		_Log.Log( EPrefix::WARNING, ELocation::SYSTEM_INFORMATION, ENC( "Unable to close process thread snapshot properly." ) );

	return bReturn && !vecOut.empty( );
}

bool CSystemInformation::GetProcessID( const std::string &strExecutableName, DWORD& dwOut )
{
	const auto hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, NULL );
	dwOut = 0;

	if ( hSnapshot == INVALID_HANDLE_VALUE
		 || hSnapshot == nullptr )
	{
		_Log.Log( EPrefix::WARNING, ELocation::SYSTEM_INFORMATION, ENC( "Unable to get processes." ) );
		return false;
	}

	auto bReturn = true;
	PROCESSENTRY32 _CurrentProcess { sizeof( PROCESSENTRY32 ) };
	if ( Process32First( hSnapshot, &_CurrentProcess ) != TRUE )
	{
		_Log.Log( EPrefix::ERROR, ELocation::SYSTEM_INFORMATION, ENC( "Unable to find first process." ) );
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
		_Log.Log( EPrefix::WARNING, ELocation::SYSTEM_INFORMATION, ENC( "Unable to close process thread snapshot properly." ) );

	return bReturn && dwOut != NULL;
}

void CSystemInformation::TerminateProcessByID( DWORD dwProcessID )
{
	
}

bool CSystemInformation::ElevateProcess( HANDLE hProcess )
{
	return false;
}
