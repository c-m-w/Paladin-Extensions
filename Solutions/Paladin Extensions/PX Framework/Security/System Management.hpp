/// System Information.hpp

#pragma once

namespace PX::sys
{
	enum
	{
		SYS_CPU, SYS_GPU, SYS_DISPLAY, SYS_OS, SYS_BOARD, SYS_MAX
	};

	PX_SDK std::wstring wstrSystemParts[ SYS_MAX ];
	PX_SDK std::wstring wstrInstallUSBName;
	PX_SDK std::deque< std::wstring > dqApps;

	/** \brief Puts system info into info variables. */
	void PX_API GetSystemInfo( );

	/** \brief Used to ensure elevation for a process.\n
		If the process is not elevated, it will attempt to elevate it manually. */
	/** \param hProcess Process to ensure elevation for.\n
				Leave it as nullptr if you wish to check the current process. */
	/** \return True if the process is elevated. */
	bool PX_API EnsureElevation( HANDLE hProcess = nullptr );
	/** \brief Gets process identifier for any running executable */
	/** \param wstrExecutableName Executable name for target process */
	/** \return Process ID */
	DWORD PX_API GetProcessID( const std::wstring& wstrExecutableName );

	/** \brief Information for manually mapping a DLL into a process. */
	struct injection_info_t
	{
		PVOID pImageBase;
		PIMAGE_NT_HEADERS pNTHeaders;
		PIMAGE_BASE_RELOCATION pBaseRelocation;
		PIMAGE_IMPORT_DESCRIPTOR pImportDescriptor;
		HMODULE( WINAPI* fnLoadLibraryA )( LPCSTR );
		FARPROC( WINAPI* fnGetProcAddress )( HMODULE, LPCSTR );
	};
	/** \brief Manually maps and calls desired DLL into any running executable */
	/** \param pDLL Data for DLL to be mapped */
	/** \param wstrExecutableName Executable name for target process */
	/** \param injInfo Object to store information of injection. */
	/** \return True if successful, false if failed. */
	bool PX_API DLLManualMap( const LPVOID& pDLL, const std::wstring& wstrExecutableName, injection_info_t* injInfo );
}
