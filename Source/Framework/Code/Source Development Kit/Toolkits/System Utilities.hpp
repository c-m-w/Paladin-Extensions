/// System Utilities.hpp

#pragma once

/** \brief Information of device from system */
struct device_info_t
{
	const static inline std::wstring wstrCommand = ENC( L"SELECT * FROM " );

	/** \brief Device information */
	std::string *pValue;
	const std::wstring wstrDevice, wstrProperty;

	/** \brief Initializes structure */
	/** \param pValue Value to assign */
	/** \param wstrDevice Device to retrieve information of */
	/** \param wstrProperty Property to retrieve information of device of */
	device_info_t( std::string *pValue, const std::wstring &wstrDevice, const std::wstring &wstrProperty = ENC( L"Name" ) );
};

/** \brief Structure to retrieve information about the system */
class CSystemInformation
{
private:

	using thread_list_t = std::vector< std::pair< DWORD, DWORD > >;

	std::vector< device_info_t > vecInformation;

	/** \brief Retrieves threads of a specified process */
	/** \param dwProcessID Process identifier to retrieve threads of */
	/** \param _Out Thread list */
	/** \return Success of thread retrieval */
	[ [ nodiscard ] ] static bool GetProcessThreads( DWORD dwProcessID, thread_list_t& _Out );
	/** \brief Retrieves process identifier */
	/** \param strExecutableName Executable to search snapshot for */
	/** \param dwOut Process ID */
	/** \return Success of process identifier retrieval */
	[ [ nodiscard ] ] static bool GetProcessID( const std::string &strExecutableName, DWORD& dwOut );
	static bool GetExecutableByProcessID( DWORD dwProcessID, std::string &strOut );
	/** \brief Elevates a process to administrator if not already */
	/** \param hProcess Process to elevate */
	/** \return Status of process elevation */
	static bool ElevateProcess( HANDLE hProcess = GetCurrentProcess( ) );

public:

	/** \brief Order of system hardware information retrieved by queue process */
	enum ESystemInformation
	{
		SYS_CPU,
		SYS_GPU,
		SYS_DISPLAY,
		SYS_PC,
		SYS_OS,
		SYS_DRIVE,
		SYS_BOARD,
		SYS_HASH,
		SYS_MAX
	};

	// todo clean up this crap
	enum ESystemBuild
	{
		BUILD_UNKNOWN,									// XP, Vista, 7, 8, 8.1, or Server
		BUILD_INITIAL_1507 = 10240,						// Initial 10 Build
		BUILD_REDSTONE_NOVEMBER_1511 = 10586,			// Redstone November Build
		BUILD_REDSTONE_ANNIVERSARY_1607 = 14393,		// Redstone Anniversary Build
		BUILD_REDSTONE_CREATORS_1703 = 15063,			// Redstone Creators Build
		BUILD_REDSTONE_CREATORS_FALL_1709 = 16299,		// Redstone Creators Update 1 Build
		BUILD_REDSTONE_CREATORS_APRIL_1803 = 17134,		// Redstone Creators Update 2 Build
		BUILD_REDSTONE_CREATORS_OCTOBER_1809 = 17763,	// Redstone Creators Update 3 Build
		BUILD_PREVIEW = 18334,							// Codename 19H1/Preview Build
	};

	enum ESystemVersion
	{
		W_UNKNOWN,							// Unknown W version
		WSERVER,							// Initial Server
		WXP,								// Initial XP
		WXP1,								// XP Service Pack 1
		WXP2,								// XP Service Pack 2
		WXP3,								// XP Service Pack 3
		WVISTA,								// Initial Vista
		WVISTA1,							// Vista Service Pack 1
		WVISTA2,							// Vista Service Pack 2
		W7,									// Initial 7
		W71,								// 7 Service Pack 1
		W8,									// Initial 8
		W81,								// 8.1
		W10_INITIAL_1507,					// Initial Release
		W10_REDSTONE_NOVEMBER_1511,			// Redstone November Release
		W10_REDSTONE_ANNIVERSARY_1607,		// Redstone Anniversary Release
		W10_REDSTONE_CREATORS_1703,			// Redstone Creators Release
		W10_REDSTONE_CREATORS_FALL_1709,	// Redstone Creators Update 1 Release
		W10_REDSTONE_CREATORS_APRIL_1803,	// Redstone Creators Update 2 Release
		W10_REDSTONE_CREATORS_OCTOBER_1809,	// Redstone Creators Update 3 Release
		W10_19H1_1903,						// Codename 19H1 Release
		W10_PREVIEW							// Preview version of W10
	};

	/** \brief Gets the operating system version */
	/** \return Version found */
	ESystemVersion GetOperatingSystemVersion( );

	/** \brief Queries screen size of main display */
	/** \return Screen size */
	Utilities::vector2_t GetScreenSize( );
	/** \brief Opens link with main browser */
	/** \param strLink Link to pass to browser */
	void OpenLink( const std::string& strLink );
	/** \brief Gets the data currently stored in clipboard */
	/** \param strOut Clipboard data */
	/** \return Success of retrieval */
	bool GetClipboardData( std::string& strOut );
	/** \brief Sets the data in clipboard */
	/** \param strIn Clipboard data */
	/** \return Success of assignment */
	bool SetClipboardData( const std::string& strIn );

	/** \brief Adds device to queue to process for query of device information */
	/** \param _DeviceInfo Device to add */
	void AddDeviceToQueue( const device_info_t& _DeviceInfo );
	/** \brief Processes queue of devices to retrieve information for */
	/** \return Success of queue process */
	bool ProcessQueue( );
	bool GetProgramList( std::string &strOut );
	[ [ nodiscard ] ] std::string GetHardwareHash( );
	/** \brief Terminates a process */
	/** \param dwProcessID Identifer of process to terminate */
	static void TerminateProcessByID( DWORD dwProcessID );
	static bool GetProcesses( std::vector< std::string > &vecOut );
	static bool GetProgramList( std::vector< std::string > &vecOut );
	static std::vector< HWND > GetOpenWindows( );
	static std::vector< HWND > GetCurrentProcessWindows( );
	static std::vector< std::string > GetOpenWindowNames( );

	friend class CMemoryManager;
} inline _SystemInformation;

using ESystemInformation = CSystemInformation::ESystemInformation;
using ESystemBuild = CSystemInformation::ESystemBuild;
using ESystemVersion = CSystemInformation::ESystemVersion;
