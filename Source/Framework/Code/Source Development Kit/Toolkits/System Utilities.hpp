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
		SYS_MAX
	};

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
	/** \brief Terminates a process */
	/** \param dwProcessID Identifer of process to terminate */
	static void TerminateProcessByID( DWORD dwProcessID );

	friend class CMemoryManager;
} inline _SystemInformation;

using ESystemInformation = CSystemInformation::ESystemInformation;
