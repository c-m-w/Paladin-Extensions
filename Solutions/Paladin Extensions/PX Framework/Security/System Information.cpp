/// System Information.cpp

#include "../PX Framework.hpp"

namespace PX
{
	namespace SYS
	{
		std::wstring RetrieveInfo( const bstr_t& wstrDevice, Types::wcstr_t wstrdeviceProperty = L"Name" )
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

		void GetSystemInfo( )
		{
			wstrSystemParts[ SYS_CPU ] = RetrieveInfo( L"SELECT * FROM Win32_Processor" );
			wstrSystemParts[ SYS_GPU ] = RetrieveInfo( L"SELECT * FROM CIM_PCVideoController" );
			wstrSystemParts[ SYS_DISPLAY ] = RetrieveInfo( L"SELECT * FROM Win32_DesktopMonitor" );
			wstrSystemParts[ SYS_OS ] = RetrieveInfo( L"SELECT * FROM CIM_OperatingSystem" );
			wstrSystemParts[ SYS_BOARD ] = RetrieveInfo( L"SELECT * FROM Win32_BaseBoard", L"Product" );

			dbg::Assert( !wstrSystemParts[ SYS_CPU ].empty( )
				 && !wstrSystemParts[ SYS_GPU ].empty( )
				 && !wstrSystemParts[ SYS_DISPLAY ].empty( )
				 && !wstrSystemParts[ SYS_OS ].empty( )
				 && !wstrSystemParts[ SYS_BOARD ].empty( ) );

			wstrInstallUSBName = RetrieveInfo( L"SELECT * FROM CIM_LogicalDisk", L"Model" ); // TODO @Skel get the install usb name/model, then store it in this variable
			dbg::Assert( !wstrInstallUSBName.empty( ) );

			std::wstring wstrBuffer = RetrieveInfo( L"SELECT * FROM CIM_LogicalDisk", L"Model" );
			dbg::Assert( !wstrBuffer.empty( ) );

			while ( !wstrBuffer.substr( wstrBuffer.find_first_of( L'\n' ), wstrBuffer.size( ) ).empty( ) )
			{
				dqApps.emplace_back( wstrBuffer.substr( 0, wstrBuffer.find_first_of( L'\n' ) ) );
				wstrBuffer = wstrBuffer.substr( wstrBuffer.find_first_of( L'\n' ), wstrBuffer.size( ) );
			}
		}
	}
}
