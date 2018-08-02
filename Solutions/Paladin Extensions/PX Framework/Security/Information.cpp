/// Information.cpp

#include "../PX Framework.hpp"

namespace PX
{
	namespace Info
	{

		std::wstring RetrieveInfo(bstr_t wstrDevice, Types::wcstr_t wstrdeviceProperty)
		{
			std::wstring deviceInfo;

			//Start of setup
			HRESULT hResult = CoInitializeEx(0, COINIT_MULTITHREADED);

			hResult = CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_DEFAULT,
				RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);

			IWbemLocator *pLoc = NULL;
			hResult = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLoc);

			IWbemServices *pSvc = NULL;
			hResult = pLoc->ConnectServer(bstr_t(L"ROOT\\CIMV2"), NULL, NULL, 0, NULL, 0, 0, &pSvc);

			hResult = CoSetProxyBlanket(pSvc, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, RPC_C_AUTHN_LEVEL_CALL,
				RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);

			IEnumWbemClassObject *pEnumerator = NULL;
			hResult = pSvc->ExecQuery(bstr_t(L"WQL"), wstrDevice,
				WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator);
			//End of not understanding what's going on

			IWbemClassObject *pclsObj;
			ULONG uReturn = 0;
			while (pEnumerator)
			{
				hResult = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
				if (uReturn == 0)
					break;
				VARIANT vtProp;

				hResult = pclsObj->Get(wstrdeviceProperty, 0, &vtProp, 0, 0);

				deviceInfo = vtProp.bstrVal;

				VariantClear(&vtProp);
				pclsObj->Release();
			}
			pEnumerator->Release();
			pSvc->Release();
			pLoc->Release();
			CoUninitialize();

			return deviceInfo;
		}

		std::wstring * GetSystemInfo()
		{
			enum {cpu, gpu, monitor, os, motherboard, usb, apps, max};
			std::wstring systemInfo[max];

			systemInfo[cpu] = RetrieveInfo(L"SELECT * FROM Win32_Processor");
			systemInfo[gpu] = RetrieveInfo(L"SELECT * FROM CIM_PCVideoController");
			systemInfo[monitor] = RetrieveInfo(L"SELECT * FROM Win32_DesktopMonitor");
			systemInfo[os] = RetrieveInfo(L"SELECT * FROM CIM_OperatingSystem");
			systemInfo[motherboard] = RetrieveInfo(L"SELECT * FROM Win32_BaseBoard", L"Product");
			//systemInfo[apps] = RetrieveInfo(L"SELECT * FROM CIM_Product");
			//systemInfo[usb] = RetrieveInfo(L"SELECT * FROM CIM_LogicalDisk", L"Model"); //Retrieve usbs

			return systemInfo;

		}

	}
}
