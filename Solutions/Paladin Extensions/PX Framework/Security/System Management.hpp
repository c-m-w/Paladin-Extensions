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

	/** \brief Used to ensure elevation for self process\n
		If current process is not elevated, it will attempt to elevate it manually. */
	/** \return True if self process is elevated */
	bool PX_API EnsureElevation( );
	/** \brief Gets process identifier for any running executable */
	/** \param wstrExecutableName Executable name for target process */
	/** \return Process ID */
	DWORD PX_API GetProcessID( const std::wstring& wstrExecutableName );

	/** \brief Manually maps and calls desired DLL into any running executable */
	/** \param pDLL Data for DLL to be mapped */
	/** \param wstrExecutableName Executable name for target process */
	/** \param injInfo Object to store information of injection. */
	/** \return True if successful, false if failed. */
	bool PX_API DLLManualMap( const LPVOID& pDLL, const std::wstring& wstrExecutableName, Types::injection_info_t* injInfo );
}
