/// System Information.hpp

#pragma once

namespace PX
{
	namespace sys
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

		bool PX_API EnsureElevation( );
		DWORD PX_API GetProcessID( const std::wstring& wstrExecutableName );

		struct SInjectionInfo
		{
			PVOID pImageBase;
			PIMAGE_NT_HEADERS pNTHeaders;
			PIMAGE_BASE_RELOCATION pBaseRelocation;
			PIMAGE_IMPORT_DESCRIPTOR pImportDescriptor;
			HMODULE( WINAPI* fnLoadLibraryA )( LPCSTR );
			FARPROC( WINAPI* fnGetProcAddress )( HMODULE, LPCSTR );
		};
		bool PX_API Inject( LPVOID pDLL, const std::wstring& wstrExecutableName, SInjectionInfo* injInfo );
	}
}
