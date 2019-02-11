/// System Utilities.hpp

#pragma once

struct device_info_t
{
	const static inline std::wstring wstrCommand = ENC( L"SELECT * FROM " );

	std::string *pValue;
	const std::wstring wstrDevice, wstrProperty;

	device_info_t( std::string *pValue, const std::wstring &wstrDevice, const std::wstring &wstrProperty = ENC( L"Name" ) );
};

class CSystemInformation
{
private:

	std::vector< device_info_t > vecInformation;

	[ [ nodiscard ] ] static bool GetProcessThreads( DWORD dwProcessID, std::vector< DWORD >& vecOut );
	[ [ nodiscard ] ] static bool GetProcessID( const std::string &strExecutableName, DWORD& dwOut );
	static bool ElevateProcess( HANDLE hProcess = GetCurrentProcess( ) );

public:

	enum ESystemInformation
	{
		SYS_CPU,
		SYS_GPU,
		SYS_DISPLAY,
		SYS_PC,
		SYS_OS,
		SYS_DRIVE,
		SYS_BOARD,
		SYS_MAX
	};

	Utilities::vector2_t GetScreenSize( ); // todo move to system information
	void OpenLink( const std::string& strLink ); // todo move somewhere more fitting

	void AddDeviceToQueue( const device_info_t& _DeviceInfo );
	bool ProcessQueue( );
	static void TerminateProcessByID( DWORD dwProcessID );

	friend class CMemoryManager;
} inline _SystemInformation;

using ESystemInformation = CSystemInformation::ESystemInformation;
