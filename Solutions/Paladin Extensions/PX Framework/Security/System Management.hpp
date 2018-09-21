/// System Information.hpp

#pragma once

namespace PX::sys
{
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

	/** \brief Puts system info into info variables. */
	/** \return System information as a JSON object. */
	nlohmann::json PX_API GetSystemInfo( );

	std::string PX_API AssembleExtensionInformation( std::string strCipher );

	/** \brief Used to ensure elevation for a process.\n
	If the process is not elevated, it will attempt to elevate it manually. */
	/** \param hProcess Process to ensure elevation for.\n
	Pass no parameter if you wish to check the current process. */
	/** \return True if the process is elevated. */
	bool PX_API EnsureElevation( HANDLE hProcess = GetCurrentProcess( ) );
	/** \brief Gets process identifier for any running executable */
	/** \param wstrExecutableName Executable name for target process */
	/** \return Process ID */
	DWORD PX_API GetProcessID( const std::wstring& wstrExecutableName );
	HANDLE PX_API FindProcessThread( DWORD dwProcessID );
	HMODULE PX_API FindModuleEx( const std::wstring& wstrModule, DWORD dwProcessID );
	bool PX_API IsProcessOpen( const std::wstring& wstrExecutableName );
	bool PX_API IsProcessThreadRunning( DWORD dwProcessID );
	bool PX_API NecessaryModulesLoaded( DWORD dwProcessID );

	PX_DEF INJECTION_INFO_SIZE = 24u;
	PX_SDK unsigned uLoadDLLSize = 0u;
	PX_SDK unsigned uStubSize = 0u;
	PX_SDK Types::byte_t* bLoadDLL = nullptr;
	PX_SDK Types::byte_t* bStub = nullptr;

	/** \brief Information for manually mapping a DLL into a process. */
	typedef struct
	{
		PVOID pImageBase;
		PIMAGE_NT_HEADERS pNTHeaders;
		PIMAGE_BASE_RELOCATION pBaseRelocation;
		PIMAGE_IMPORT_DESCRIPTOR pImportDescriptor;
		HMODULE ( WINAPI* fnLoadLibraryA )( LPCSTR );
		FARPROC ( WINAPI* fnGetProcAddress )( HMODULE, LPCSTR );
	} injection_info_t;

	void PX_API WipeMemoryEx( HANDLE hTarget, LPVOID pAddress, std::size_t zSize );
	void PX_API WipeMemory( LPVOID pAddress, std::size_t zSize );
	bool PX_API LoadLibraryEx( const std::wstring& wstrExecutableName, const std::wstring& wstrDLLPath );
	/** \brief Manually maps and calls desired DLL into any running executable */
	/** \param pDLL Data for DLL to be mapped */
	/** \param wstrExecutableName Executable name for target process */
	/** \param injInfo Object to store information of injection. */
	/** \return True if successful, false if failed. */
	bool PX_API LoadRawLibraryEx( const LPVOID& pDLL, const std::wstring& wstrExecutableName, injection_info_t* injInfo, HANDLE* hTarget = nullptr, HANDLE* hThread = nullptr );
	/** \brief Manually maps and calls desired DLL into self */
	/** \param pDLL Data for DLL to be mapped */
	/** \param injInfo Object to store information of injection. */
	/** \return True if successful, false if failed. */
	bool PX_API LoadRawLibrary( const LPVOID& pDLL, injection_info_t* injInfo );

	HANDLE PX_API FindInternalHandle( DWORD dwTargetProcessID );

	void PX_API TerminateProcess( DWORD dwTargetProcessID );

	struct SWindowsAPI: PX::Tools::ASingleton< SWindowsAPI >
	{
		// typedefs
		typedef LONG KPRIORITY;

		// structs
		typedef struct _SYSTEM_HANDLE
		{
			ULONG ProcessId;
			BYTE ObjectTypeNumber;
			BYTE Flags;
			USHORT Handle;
			PVOID Object;
			ACCESS_MASK GrantedAccess;
		} SYSTEM_HANDLE, *PSYSTEM_HANDLE;

		typedef struct _SYSTEM_HANDLE_INFORMATION
		{
			ULONG HandleCount;
			SYSTEM_HANDLE Handles[ 1 ];
		} SYSTEM_HANDLE_INFORMATION, *PSYSTEM_HANDLE_INFORMATION;


		typedef struct _SYSTEM_KERNEL_DEBUGGER_INFORMATION
		{
			BOOLEAN DebuggerEnabled;
			BOOLEAN DebuggerNotPresent;
		} SYSTEM_KERNEL_DEBUGGER_INFORMATION, *PSYSTEM_KERNEL_DEBUGGER_INFORMATION;

		typedef struct _LDR_MODULE
		{
			LIST_ENTRY InLoadOrderModuleList, InMemoryOrderModuleList, InInitializationOrderModuleList;
			PVOID BaseAddress, EntryPoint;
			ULONG SizeOfImage;
			UNICODE_STRING FullDllName, BaseDllName;
			ULONG Flags;
			SHORT LoadCount, TlsIndex;
			LIST_ENTRY HashTableEntry;
			ULONG TimeDateStamp;
		} LDR_MODULE, *PLDR_MODULE;

		typedef struct _CLIENT_ID
		{
			HANDLE UniqueProcess, UniqueThread;
		} CLIENT_ID, *PCLIENT_ID;

		typedef struct _THREAD_BASIC_INFORMATION
		{
			NTSTATUS ExitStatus;
			PVOID TebBaseAddress;
			CLIENT_ID ClientId;
			KAFFINITY AffinityMask, Priority, BasePriority;
		} THREAD_BASIC_INFORMATION, *PTHREAD_BASIC_INFORMATION;

		typedef struct _PEB64
		{
			BYTE Reserved1[ 2 ], BeingDebugged, Reserved2[ 1 ];
			PVOID64 Reserved3[ 2 ], Ldr, ProcessParameters;
			BYTE Reserved4[ 104 ];
			PVOID64 Reserved5[ 52 ], PostProcessInitRoutine;
			BYTE Reserved6[ 128 ];
			PVOID64 Reserved7[ 1 ];
			ULONG SessionId;
		} PEB64, *PPEB64;

		typedef struct _PEB_LDR_DATA64
		{
			BYTE Reserved1[ 8 ];
			PVOID64 Reserved2[ 3 ];
			LIST_ENTRY64 InMemoryOrderModuleList;
		} PEB_LDR_DATA64, *PPEB_LDR_DATA64;

		typedef struct _UNICODE_STRING64
		{
			USHORT Length, MaximumLength;
			PVOID64 Buffer;
		} UNICODE_STRING64;

		typedef struct _LDR_DATA_TABLE_ENTRY64
		{
			PVOID64 Reserved1[ 2 ];
			LIST_ENTRY64 InMemoryOrderLinks;
			PVOID64 Reserved2[ 2 ], DllBase, Reserved3[ 2 ];
			UNICODE_STRING64 FullDllName;
			BYTE Reserved4[ 8 ];
			PVOID64 Reserved5[ 3 ];

			union
			{
				ULONG CheckSum;
				PVOID64 Reserved6;
			} DUMMYUNIONNAME;

			ULONG TimeDateStamp;
		} LDR_DATA_TABLE_ENTRY64, *PLDR_DATA_TABLE_ENTRY64;

		// functions
		typedef VOID ( NTAPI LDR_ENUM_CALLBACK )( PLDR_DATA_TABLE_ENTRY, PVOID, BOOLEAN* );
		typedef LDR_ENUM_CALLBACK *PLDR_ENUM_CALLBACK;

		typedef UINT ( WINAPI* fnEnumSystemFirmwareTables )( DWORD, PVOID, DWORD );
		typedef UINT ( WINAPI* fnGetSystemFirmwareTable )( DWORD, DWORD, PVOID, DWORD );
		typedef void ( WINAPI* fnGetNativeSystemInfo )( LPSYSTEM_INFO );
		typedef BOOL ( WINAPI* fnGetProductInfo )( DWORD, DWORD, DWORD, DWORD, PDWORD );
		typedef BOOL ( WINAPI* fnIsWow64Process )( HANDLE, PBOOL );
		typedef NTSTATUS ( NTAPI* fnLdrEnumerateLoadedModules )( BOOLEAN, PLDR_ENUM_CALLBACK, PVOID );
		typedef NTSTATUS ( NTAPI* fnNtClose )( HANDLE );
		typedef NTSTATUS ( NTAPI* fnNtCreateDebugObject )( PHANDLE, ACCESS_MASK, POBJECT_ATTRIBUTES, ULONG );
		typedef NTSTATUS ( NTAPI* fnNtCreateThreadEx )( PHANDLE, ACCESS_MASK, LPVOID, HANDLE, LPTHREAD_START_ROUTINE, LPVOID, BOOL, DWORD, DWORD, DWORD, LPVOID );
		typedef NTSTATUS ( NTAPI* fnNtDelayExecution )( BOOLEAN, PLARGE_INTEGER );
		typedef NTSTATUS ( NTAPI* fnNtQueryInformationThread )( HANDLE, UINT, PVOID, ULONG, PULONG );
		typedef NTSTATUS ( NTAPI* fnNtQueryInformationProcess )(  HANDLE,  UINT, PVOID, ULONG, PULONG );
		typedef NTSTATUS ( NTAPI* fnNtQueryObject )( HANDLE, UINT, PVOID, ULONG, PULONG );
		typedef NTSTATUS ( NTAPI* fnNtQuerySystemInformation )( UINT, PVOID, ULONG, PULONG );
		typedef NTSTATUS ( NTAPI* fnNtSetInformationThread )( HANDLE, UINT, PVOID, ULONG );
		typedef NTSTATUS ( NTAPI* fnNtWow64ReadVirtualMemory64 )( HANDLE, PVOID64, PVOID, ULONGLONG, PULONGLONG );
		typedef NTSTATUS ( NTAPI* fnNtWow64QueryVirtualMemory64 )( HANDLE, PVOID64, DWORD, PMEMORY_BASIC_INFORMATION64, ULONG64, PULONG64 );
		typedef NTSTATUS ( NTAPI* fnNtUnmapViewOfSection )( HANDLE, PVOID );
		typedef NTSTATUS ( NTAPI* fnNtYieldExecution )( );
		typedef NTSTATUS ( WINAPI* fnRtlGetVersion )( RTL_OSVERSIONINFOEXW* );
		typedef DWORD ( WINAPI* fnRtlCreateUserThread )( HANDLE, PSECURITY_DESCRIPTOR, BOOL, ULONG, PULONG, PULONG, LPVOID, LPVOID, HANDLE, LPVOID );

		enum EFuncs
		{
			EnumSystemFirmwareTables,
			GetSystemFirmwareTable,
			GetNativeSystemInfo,
			GetProductInfo,
			IsWow64Process,
			LdrEnumerateLoadedModules,
			NtClose,
			NtCreateDebugObject,
			NtCreateThreadEx,
			NtDelayExecution,
			NtQueryInformationThread,
			NtQueryInformationProcess,
			NtQueryObject,
			NtQuerySystemInformation,
			NtSetInformationThread,
			NtWow64QueryVirtualMemory64,
			NtWow64ReadVirtualMemory64,
			NtUnmapViewOfSection,
			NtYieldExecution,
			RtlGetVersion,
			RtlCreateUserThread,
			FUNC_MAX
		};

		SWindowsAPI( ) PX_NOX;
		void* PX_API GetFunctionPointer( EFuncs enfRequest ) const PX_NOX;
	};
}

#if defined PX_USE_NAMESPACES
using namespace PX::sys;
#endif
