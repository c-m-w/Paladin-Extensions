/// System Information.hpp

#pragma once

class CSystemInformation
{
	std::string GetDeviceInformation( const bstr_t& bszDevice, const wchar_t *wszDeviceProperty = ENCW( L"Name" ) );

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
public:
	nlohmann::json GetHardware( );
	static DWORD GetProcessID( const std::string& strExecutableName );
	static void TerminateProcessByID( DWORD dwProcessID );
	static bool ElevateProcess( HANDLE hProcess = GetCurrentProcess( ) );
} inline _SystemInformation;
