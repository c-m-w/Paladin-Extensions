/// System Information.hpp

#pragma once

class CSystemInformation
{
private:

	enum
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

	std::string GetDeviceInformation( const bstr_t& bszDevice, const wchar_t *wszDeviceProperty = ENC( L"Name" ) );

public:

	nlohmann::json GetHardware( );
	[ [ nodiscard ] ] static bool GetProcessThreads( DWORD dwProcessID, std::vector< DWORD >& vecOut );
	[ [ nodiscard ] ] static bool GetProcessID( const std::string &strExecutableName, DWORD& dwOut );
	static void TerminateProcessByID( DWORD dwProcessID );
	static bool ElevateProcess( HANDLE hProcess = GetCurrentProcess( ) );
} inline _SystemInformation;
