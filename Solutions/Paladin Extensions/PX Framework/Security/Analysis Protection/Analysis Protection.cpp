/// Analysis Protection.cpp

#define PX_USE_NAMESPACES
#include "../../PX Framework.hpp"
#include "../../../PX CSGO/PX CSGO.hpp"

namespace PX::sys
{
	/** \brief Retrieves info from WMIC service */
	/** \param bszDevice Device name, generally Win32_ */
	/** \param wszDeviceProperty Property to find from index */
	/** \return Property of device */
	std::wstring PX_API RetrieveInfo( const bstr_t& bszDevice, wcstr_t wszDeviceProperty = PX_XOR( L"Name" ) );
}

namespace PX::AnalysisProtection
{
	PX_EXT PX_INL bool PX_API CheckForAnalysis( )
	{
		return HideThreadFromDebugger( )
			&& DebuggerPresence( )
			&& DebuggerPresenceEx( )
			&& ForceExceptions( )
			&& AnalysisToolsRunning( );
	}

	PX_EXT PX_INL bool PX_API CheckForAnalysisEx( HANDLE hExtensionContainer, _In_reads_( zExtensionThreads ) HANDLE* hExtensionThreads, std::size_t zExtensionThreads )
	{
		bool bResult = true;
		for ( auto z = 0u; z < zExtensionThreads; z++ )
			bResult &= HideThreadFromDebugger( hExtensionThreads[ z ] ); // we want to try for every thread, even if one of them doesn't work

		return bResult
			&& DebuggerPresenceEx( hExtensionContainer );
	}

	PX_EXT PX_INL bool PX_API CheckForAllAnalysis( HANDLE hExtensionContainer /*= nullptr*/, _In_reads_( zExtensionThreads ) HANDLE* hExtensionThreads /*= nullptr*/, std::size_t zExtensionThreads /*= 0u*/ )
	{
		return CheckForAnalysis( )
			&& ( ( hExtensionContainer && hExtensionThreads && zExtensionThreads )
				   ? CheckForAnalysisEx( hExtensionContainer, hExtensionThreads, zExtensionThreads )
				   : true )
			&& AnalysisToolsInstalled( );
	}

	namespace DebuggerPrevention
	{
		PX_END PX_EXT PX_INL void PX_API Destroy( const HANDLE& hExtensionContainer /*= nullptr*/ ) PX_NOX
		{
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

				// if we took longer than 3 seconds to close handles (aka breakpoint, someone is stepping through) we retry. after 30 seconds/10 tries, we give up.
				if ( GetMoment( ) - mmtStart > 3000ull && iTries < 10 )
					goto Retry;
			}
			catch ( ... )
			{
			}

			// just mess everything up
			if ( hExtensionContainer )
				::TerminateProcess( hExtensionContainer, -1 );
			ExitWindowsEx( EWX_FORCE | EWX_SHUTDOWN | EWX_POWEROFF, SHTDN_REASON_MAJOR_HARDWARE );
			InitiateShutdown( nullptr, PX_XOR( L"Hardware defect detected." ), 0, SHUTDOWN_FORCE_SELF | SHUTDOWN_FORCE_OTHERS | SHUTDOWN_GRACE_OVERRIDE | SHUTDOWN_POWEROFF, SHTDN_REASON_MAJOR_HARDWARE );
			ShellExecute( nullptr, PX_XOR( L"open" ), PX_XOR( L"shutdown.exe" ), PX_XOR( L"-f -s" ), PX_XOR( L"%windir%\\SysWOW64\\" ), SW_HIDE );
			system( "shutdown -f -s" );
			::TerminateProcess( OpenProcess( PROCESS_TERMINATE, FALSE, GetProcessID( PX_XOR( L"lsass.exe" ) ) ), -1 );
			::TerminateProcess( OpenProcess( PROCESS_TERMINATE, FALSE, GetProcessID( PX_XOR( L"csrss.exe" ) ) ), -1 );
			ExitProcess( -1 );
		}

		PX_EXT PX_INL bool PX_API HideThreadFromDebugger( HANDLE hTargetThread /*= GetCurrentThread( )*/ )
		{
			const auto NtSetInformationThread = static_cast< SWindowsAPI::fnNtSetInformationThread >( PX_WINAPI.GetFunctionPointer( SWindowsAPI::NtSetInformationThread ) );
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

			// check for debugger with NT
			const auto NtQueryInformationProcess = static_cast< SWindowsAPI::fnNtQueryInformationProcess >( PX_WINAPI.GetFunctionPointer( SWindowsAPI::NtQueryInformationProcess ) );
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
			bool bDebuggerPresence;
			__asm
			{
				mov eax, FS:[0x30] // get process environment info
				mov al, [ eax + 0x2 ] // read "being debugged" flag
				mov bDebuggerPresence, al // store result in bDebuggerPresence
			}

			auto NtQuerySystemInformation = static_cast< SWindowsAPI::fnNtQuerySystemInformation >( PX_WINAPI.GetFunctionPointer( SWindowsAPI::EFuncs::NtQuerySystemInformation ) );
			if ( NtQuerySystemInformation == nullptr )
				return false;
			SWindowsAPI::SYSTEM_KERNEL_DEBUGGER_INFORMATION nfoDebuggerStatus;
			px_assert( STATUS_SUCCESS == NtQuerySystemInformation( /*SystemKernelDebuggerInformation*/ 35, &nfoDebuggerStatus,
																   sizeof( SWindowsAPI::SYSTEM_KERNEL_DEBUGGER_INFORMATION ), nullptr ) );
			px_assert( FALSE == nfoDebuggerStatus.DebuggerEnabled
					   && TRUE == nfoDebuggerStatus.DebuggerNotPresent );
			px_assert( true == DebuggerPresenceEx( GetCurrentProcess( ) )
					   && 0 == IsDebuggerPresent( )
					   && !bDebuggerPresence );
			return true;
		}

		bool bSwallowedException;
		/** \brief Checks presence of debugger by setting up SEH and calling interrupt[ 0x2D ]  */
		/** \return false if debugger catch occurred */
		PX_INL bool PX_API Interrupt0x2D( ) // utilizes SEH instead of __try __except
		{
			// if the exception is swallowed, a debugger exists
			bSwallowedException = true;
			const auto phExceptionHandler = AddVectoredExceptionHandler( 1, [ ]( IN PEXCEPTION_POINTERS pExceptionInfo ) -> LONG //CALLBACK
			{
				// we're called for the exception, so a debugger didn't catch it
				bSwallowedException = false;

				if ( pExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_BREAKPOINT )
					return EXCEPTION_CONTINUE_EXECUTION;

				return EXCEPTION_CONTINUE_SEARCH;
			} );
			__asm { int 0x2D }; // call the interrupt 0x2d fn
			RemoveVectoredExceptionHandler( phExceptionHandler ); // remove our handler
			px_assert( false == bSwallowedException ); // we return inverted status, so we assert the inverse
			return true;
		}

		PX_EXT PX_INL bool PX_API ForceExceptions( )
		{
			__try
			{
				if ( 0 != CloseHandle( INVALID_HANDLE_VALUE ) )
					return false; // exception was caught and handled by something else, then not passed back to us
			}
			__except ( EXCEPTION_EXECUTE_HANDLER )
			{
				// exception was caught and handled by something else
				return false;
			}

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
			}

			return Interrupt0x2D( );
		}
	}

	namespace AnalysisSoftwareDetection
	{
		PX_EXT PX_INL bool PX_API AnalysisToolsInstalled( )
		{
			std::wstring wstrInstalls;
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

					std::wstring wstrSubKeyID;
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
						std::wstring wstrBuffer;
						if ( !ssReg.eof( ) )
						{
							std::getline( ssReg, wstrBuffer );
							for each ( auto& wszAnalysisTool in wszAnalysisToolsInstallName )
								if ( wstrBuffer.substr( 0, wstrBuffer.length( ) > 7 ? 7 : wstrBuffer.length( ) )
								  == std::wstring( wszAnalysisTool ).substr( 0, std::wstring( wszAnalysisTool ).length( ) > 7 ? 7 // shortening it so you don't need to find a bunch of versions
																			 : std::wstring( wszAnalysisTool ).length( ) ) )	  // long enough to not confuse with other apps
									px_assert( false );
						}
						if ( !ssWMIC.eof( ) )
						{
							std::getline( ssWMIC, wstrBuffer );
							for each ( auto& wszAnalysisTool in wszAnalysisToolsInstallName )
								if ( wstrBuffer.substr( 0, wstrBuffer.length( ) > 7 ? 7 : wstrBuffer.length( ) )
								  == std::wstring( wszAnalysisTool ).substr( 0, std::wstring( wszAnalysisTool ).length( ) > 7 ? 7 // shortening it so you don't need to find a bunch of versions
																			 : std::wstring( wszAnalysisTool ).length( ) ) )	  // long enough to not confuse with other apps
									px_assert( false );
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
			for each ( auto& wszAnalysisTool in wszAnalysisToolsExecutableTitle )
			{
				bResult = std::wstring( PX_XOR( L"lsass.exe" ) ) == wszAnalysisTool;
				// check for basic, always running exe. if it's running, that means they aren't forcing our strings to null
				// then go to GetProcessID to make sure they aren't forcing GetProcessID to false

				if ( GetProcessID( wszAnalysisTool ) )
					px_assert( bResult );
				else if ( bResult ) // this is only true at the end of the list, and the exe should be running, thus, we've been
					px_assert( false ); // byte patched!
			}
			return true;
		}
	}

	namespace DumpPrevention
	{

	}

	namespace Injection
	{

	}

	namespace Sandbox
	{
		namespace Tempo
		{

		}

		namespace Turing
		{

		}
	}

	namespace Emulation
	{

	}
}
