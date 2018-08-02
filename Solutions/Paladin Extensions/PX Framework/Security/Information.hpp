/// Information.hpp

#pragma once

namespace PX
{
	namespace Info
	{

	std::wstring RetrieveInfo( bstr_t wstrDevice, Types::wcstr_t wstrdeviceProperty = L"Name" );
	std::wstring* GetSystemInfo();

	}
}
