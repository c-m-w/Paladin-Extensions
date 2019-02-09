/// System Information.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#define USE_DEFINITIONS
#include "../../Framework.hpp"

std::string CSystemInformation::GetDeviceInformation( const bstr_t &bszDevice, const wchar_t *wszDeviceProperty /*= ENC( L"Name" )*/ )
{ // todo https://docs.microsoft.com/en-us/windows/desktop/api/oleauto/nf-oleauto-geterrorinfo for logging
	{
		const auto hrReturn = CoInitialize( nullptr );
		if ( hrReturn != S_OK && hrReturn != S_FALSE )
			return _Log.Log( EPrefix::ERROR, ELocation::SYSTEM_INFORMATION,
							 ENC( "Couldn't initialize COM library for device information retrieval. Error %i." ), hrReturn ), std::string( );
	}

	{
		const auto hrReturn = CoInitializeSecurity( nullptr, -1, nullptr, nullptr, RPC_C_AUTHN_LEVEL_DEFAULT,
													RPC_C_IMP_LEVEL_IMPERSONATE, nullptr, EOAC_NONE, nullptr );
		if ( hrReturn != S_OK && hrReturn != RPC_E_TOO_LATE )
			return CoUninitialize( ), _Log.Log( EPrefix::ERROR, ELocation::SYSTEM_INFORMATION,
												ENC( "Couldn't set security for device information retrieval. Error %i." ), hrReturn ), std::string( );
	}

	IWbemLocator *pLocator;
	{
		const auto hrReturn = CoCreateInstance( CLSID_WbemLocator, nullptr, CLSCTX_INPROC_SERVER,
												IID_IWbemLocator, reinterpret_cast< LPVOID* >( &pLocator ) );
		if ( hrReturn != S_OK || pLocator == nullptr )
			return CoUninitialize( ), _Log.Log( EPrefix::ERROR, ELocation::SYSTEM_INFORMATION,
												ENC( "Couldn't create locator object for device information retrieval. Error %i." ), hrReturn ), std::string( );
	}

	IWbemServices *pServices;
	{
		auto hrReturn = pLocator->ConnectServer( bstr_t( ENCW( L"ROOT\\CIMV2" ) ), nullptr, nullptr, nullptr,
												 0, nullptr, nullptr, &pServices );
		if ( hrReturn != S_OK || pServices == nullptr )
			return pLocator->Release( ), CoUninitialize( ),
					_Log.Log( EPrefix::ERROR, ELocation::SYSTEM_INFORMATION,
							  ENC( "Couldn't connect DCOM to WMI for device information retrieval. Error %i." ), hrReturn ), std::string( );

		hrReturn = CoSetProxyBlanket( pServices, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, nullptr, RPC_C_AUTHN_LEVEL_CALL,
									  RPC_C_IMP_LEVEL_IMPERSONATE, nullptr, EOAC_NONE );
		if ( hrReturn != S_OK )
			return pServices->Release( ), pLocator->Release( ), CoUninitialize( ),
					_Log.Log( EPrefix::ERROR, ELocation::SYSTEM_INFORMATION,
							  ENC( "Couldn't set authentication information on proxy for device information retrieval. Error %i." ), hrReturn ), std::string( );
	}

	IEnumWbemClassObject *pEnumerator;
	{
		const auto hrReturn = pServices->ExecQuery( bstr_t( ENCW( L"WQL" ) ), bszDevice,
													WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, nullptr, &pEnumerator );
		if ( hrReturn != S_OK || pEnumerator == nullptr )
			return pServices->Release( ), pLocator->Release( ), CoUninitialize( ),
					_Log.Log( EPrefix::ERROR, ELocation::SYSTEM_INFORMATION,
							  ENC( "Couldn't set authentication information on proxy for device information retrieval. Error %i." ), hrReturn ), std::string( );
	}

	std::string strInfo;
	while ( pEnumerator )
	{
		IWbemClassObject *pClassObject;
		ULONG uReturn;
		auto hrReturn = pEnumerator->Next( WBEM_INFINITE, 1, &pClassObject, &uReturn );
		if ( hrReturn != S_OK )
			return pEnumerator->Release( ), pServices->Release( ), pLocator->Release( ), CoUninitialize( ),
					_Log.Log( EPrefix::ERROR, ELocation::SYSTEM_INFORMATION,
							  ENC( "Couldn't iterate through device information. Error %i." ), hrReturn ), std::string( );
		if ( uReturn == 0 )
			break;

		VARIANT vtProp;
		hrReturn = pClassObject->Get( wszDeviceProperty, 0, &vtProp, nullptr, nullptr );
		if ( hrReturn != S_OK )
			return pClassObject->Release( ), pEnumerator->Release( ), pServices->Release( ), pLocator->Release( ), CoUninitialize( ),
					_Log.Log( EPrefix::ERROR, ELocation::SYSTEM_INFORMATION,
							  ENC( "Couldn't iterate through device information. Error %i." ), hrReturn ), std::string( );
		strInfo += string_cast< std::string >( vtProp.bstrVal ) + '\n';

		hrReturn = VariantClear( &vtProp );
		if ( hrReturn != S_OK )
			return pClassObject->Release( ), pEnumerator->Release( ), pServices->Release( ), pLocator->Release( ), CoUninitialize( ),
					_Log.Log( EPrefix::ERROR, ELocation::SYSTEM_INFORMATION,
							  ENC( "Couldn't clear device information prop. Error %i." ), hrReturn ), std::string( );
		pClassObject->Release( );
	}

	pEnumerator->Release( );
	pServices->Release( );
	pLocator->Release( );
	CoUninitialize( );

	if ( strInfo.empty( ) )
		return _Log.Log( EPrefix::ERROR, ELocation::SYSTEM_INFORMATION, ENC( "Couldn't get device information." ) ), std::string( );

	return strInfo.substr( 0, strInfo.length( ) - 1 ); // remove last newline character
}

nlohmann::json CSystemInformation::GetHardware( )
{
	std::string strHardware[ SYS_MAX ];
	strHardware[ SYS_CPU ] = GetDeviceInformation( ENCW( L"SELECT * FROM Win32_Processor" ) );
	strHardware[ SYS_GPU ] = GetDeviceInformation( ENCW( L"SELECT * FROM CIM_PCVideoController" ) );
	strHardware[ SYS_DISPLAY ] = GetDeviceInformation( ENCW( L"SELECT * FROM Win32_DesktopMonitor" ) );
	strHardware[ SYS_PC ] = GetDeviceInformation( ENCW( L"SELECT * FROM CIM_OperatingSystem" ), ENCW( L"CSName" ) );
	strHardware[ SYS_OS ] = GetDeviceInformation( ENCW( L"SELECT * FROM CIM_OperatingSystem" ), ENCW( L"Caption" ) );
	strHardware[ SYS_DRIVE ] = GetDeviceInformation( ENCW( L"SELECT * FROM Win32_DiskDrive" ), ENCW( L"SerialNumber" ) );
	strHardware[ SYS_BOARD ] = GetDeviceInformation( ENCW( L"SELECT * FROM Win32_BaseBoard" ), ENCW( L"Product" ) );

	if ( strHardware[ SYS_CPU ].empty( )
		|| strHardware[ SYS_GPU ].empty( )
		|| strHardware[ SYS_DISPLAY ].empty( )
		|| strHardware[ SYS_PC ].empty( )
		|| strHardware[ SYS_OS ].empty( )
		|| strHardware[ SYS_DRIVE ].empty( )
		|| strHardware[ SYS_BOARD ].empty( ) )
		throw ( _Log.Log( EPrefix::ERROR, ELocation::SYSTEM_INFORMATION,
						  ENC( "Couldn't get hardware." ) ), std::runtime_error( ENC( "Cannot run properly on modified Windows OS." ) ) );

	for each ( auto &wstr in strHardware )
		if ( wstr.length( ) > 100 )
			wstr = wstr.substr( 0, 100 );

	return nlohmann::json
	{
		{ ENC( "cpu" ), strHardware[ SYS_CPU ] },
		{ ENC( "gpu" ), strHardware[ SYS_GPU ] },
		{ ENC( "display" ), strHardware[ SYS_DISPLAY ] },
		{ ENC( "pc" ), strHardware[ SYS_PC ] },
		{ ENC( "os" ), strHardware[ SYS_OS ] },
		{ ENC( "drive" ), strHardware[ SYS_DRIVE ] },
		{ ENC( "board" ), strHardware[ SYS_BOARD ] }
	};
}
