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
	/** \return System information as a JSON object. */
	nlohmann::json PX_API GetSystemInfo( );

	/** \brief Used to ensure elevation for a process.\n
		If the process is not elevated, it will attempt to elevate it manually. */
	/** \param hProcess Process to ensure elevation for.\n
				Leave it as nullptr if you wish to check the current process. */
	/** \return True if the process is elevated. */
	bool PX_API EnsureElevation( HANDLE hProcess = GetCurrentProcess( ) );
	/** \brief Gets process identifier for any running executable */
	/** \param wstrExecutableName Executable name for target process */
	/** \return Process ID */
	DWORD PX_API GetProcessID( const std::wstring& wstrExecutableName );
	HANDLE PX_API FindProcessThread( DWORD dwProcessID );
	HMODULE PX_API FindModule( const std::wstring& wstrModule, DWORD dwProcessID );
	bool PX_API IsProcessOpen( const std::wstring& wstrExecutableName );
	bool PX_API IsProcessThreadRunning( DWORD dwProcessID );
	bool PX_API NecessaryModulesLoaded( DWORD dwProcessID );

	PX_DEF INJECTION_INFO_SIZE = 24u;
	PX_SDK unsigned uLoadDLLSize = 0u;
	PX_SDK unsigned uStubSize = 0u;
	PX_SDK byte_t* bLoadDLL = nullptr;
	PX_SDK byte_t* bStub = nullptr;

	/** \brief Information for manually mapping a DLL into a process. */
	typedef struct
	{
		PVOID pImageBase;
		PIMAGE_NT_HEADERS pNTHeaders;
		PIMAGE_BASE_RELOCATION pBaseRelocation;
		PIMAGE_IMPORT_DESCRIPTOR pImportDescriptor;
		HMODULE( WINAPI* fnLoadLibraryA )( LPCSTR );
		FARPROC( WINAPI* fnGetProcAddress )( HMODULE, LPCSTR );
	} injection_info_t;

	bool PX_API Inject( const LPVOID& pDLL, HANDLE hTarget, DWORD dwProcessID, injection_info_t* injInfo, DWORD dwThreadID = NULL );
	bool PX_API Inject( const LPVOID& pDLL, DWORD dwProcessID, injection_info_t* injInfo );
	bool PX_API Inject( const LPVOID& pDLL, const std::wstring& wstrExecutableName, injection_info_t* injInfo );

	HANDLE PX_API FindInternalHandle( DWORD dwTargetProcessID );

	void PX_API TerminateProcess( DWORD dwTargetProcessID );
	void PX_API Delete( );
}
