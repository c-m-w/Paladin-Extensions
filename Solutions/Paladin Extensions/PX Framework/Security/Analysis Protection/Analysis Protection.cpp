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
	PX_EXT std::wstring PX_API RetrieveInfo( const bstr_t& bszDevice, wcstr_t wszDeviceProperty = PX_XOR( L"Name" ) );
}

namespace PX::AnalysisProtection
{
	namespace DebuggerDetection
	{
		bool DebuggerPresenceEx( HANDLE hTarget )
		{
			// check for debugger with WinAPI
			BOOL bPresent;
			px_assert( 0 != CheckRemoteDebuggerPresent( hTarget, &bPresent ) );
			px_assert( !bPresent );

			// check for debugger with NT
			auto NtQueryInformationProcess = static_cast< SWindowsAPI::fnNtQueryInformationProcess >( PX_WINAPI.GetFunctionPointer( SWindowsAPI::NtQueryInformationProcess ) );
			// port (returns true if being debugged)
			px_assert( STATUS_SUCCESS == NtQueryInformationProcess( hTarget, ProcessDebugPort, &bPresent, sizeof( DWORD ), nullptr )
					   && !bPresent );
			   // objecthandle (returns ProcessDebugPort inverted [false if being debugged])
			px_assert( STATUS_SUCCESS == NtQueryInformationProcess( hTarget, /*ProcessDebugPort*/ 0x1E, &bPresent, sizeof( DWORD ), nullptr )
					   && !bPresent );
			   // flags (returns true if being debugged)
			px_assert( STATUS_SUCCESS == NtQueryInformationProcess( hTarget, /*ProcessDebugFlags*/ 0x1F, &bPresent, sizeof( DWORD ), nullptr )
					   && bPresent );

			return true;
		}

		bool DebuggerPresence( ) // check for debugger using remove functions & WinAPI
		{
			bool bDebuggerPresence;
			__asm
			{
				mov eax, FS:[ 0x30 ] // get process environment info
				mov al, [ eax + 2h ] // read "being debugged" flag
				mov bDebuggerPresence, al // store result in bDebuggerPresence
			}

			auto ZwQuerySystemInformation = static_cast< SWindowsAPI::fnZwQuerySystemInformation >( PX_WINAPI.GetFunctionPointer( SWindowsAPI::EFuncs::ZwQuerySystemInformation ) );
			if ( ZwQuerySystemInformation != nullptr )
			{
				SWindowsAPI::SYSTEM_KERNEL_DEBUGGER_INFORMATION nfoDebuggerStatus;
				px_assert( STATUS_SUCCESS == ZwQuerySystemInformation( SYSTEM_INFORMATION_CLASS( /*SystemKernelDebuggerInformation*/ 35 ),
																	   &nfoDebuggerStatus, sizeof( SWindowsAPI::SYSTEM_KERNEL_DEBUGGER_INFORMATION ), nullptr ) );
				px_assert( FALSE == nfoDebuggerStatus.DebuggerEnabled
						&& TRUE == nfoDebuggerStatus.DebuggerNotPresent );
			}
			px_assert( true == DebuggerPresenceEx( GetCurrentProcess( ) )
					&& 0 == IsDebuggerPresent( )
					&& !bDebuggerPresence );
			return true;
		}

		bool bSwallowedException;
		bool Interrupt0x2D( ) // utilizes SEH instead of __try __except
		{
			// if the exception is swallowed, a debugger exists
			bSwallowedException = true;
			const auto phExceptionHandler = AddVectoredExceptionHandler( 1, [ ]( PEXCEPTION_POINTERS pExceptionInfo ) -> LONG //CALLBACK
			{
				// we're called for the exception, so a debugger didn't catch it
				bSwallowedException = false;

				if ( pExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_BREAKPOINT )
					return EXCEPTION_CONTINUE_EXECUTION;

				return EXCEPTION_CONTINUE_SEARCH;
			} );
			__asm { int 0x2D }; // call the interrupt 0x2d fn
			RemoveVectoredExceptionHandler( phExceptionHandler );
			px_assert( false == bSwallowedException ); // we return inverted status, so we assert the inverse
			return true;
		}

		bool ForceExceptions( )
		{
			__try
			{
				if ( 0 != CloseHandle( INVALID_HANDLE_VALUE ) )
					return false;
			}
			__except ( EXCEPTION_EXECUTE_HANDLER )
			{
				// exception was caught and handled by something else
				return false;
			}

			auto NtClose = static_cast< SWindowsAPI::fnNtClose >( PX_WINAPI.GetFunctionPointer( SWindowsAPI::NtClose ) );
			__try
			{
				if ( STATUS_INVALID_HANDLE != NtClose( INVALID_HANDLE_VALUE ) )
					return false;
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
		bool AnalysisToolsInstalled( )
		{
			std::wstring wstrInstalls;
			{
				wcstr_t wszRegPath = PX_XOR( L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall" );
				HKEY hkeyUninstall;
				px_assert( RegOpenKeyEx( HKEY_LOCAL_MACHINE, wszRegPath, 0, KEY_READ, &hkeyUninstall ) == ERROR_SUCCESS );

				do
				{
					static auto u = 0u;
					wchar_t wchAppKeyID[ 1024 ];
					DWORD dwBuffer = sizeof wchAppKeyID;
					if ( RegEnumKeyEx( hkeyUninstall, u++, wchAppKeyID, &dwBuffer, nullptr, nullptr, nullptr, nullptr ) != ERROR_SUCCESS )
						break;

					std::wstring wstrSubKeyID;
					wstrSubKeyID = wstrSubKeyID + wszRegPath + L'\\' + wchAppKeyID;
					HKEY hkeyApp;
					px_assert( RegOpenKeyEx( HKEY_LOCAL_MACHINE, wstrSubKeyID.c_str( ), 0, KEY_READ, &hkeyApp ) == ERROR_SUCCESS );

					wchar_t wchDisplay[ 1024 ];
					dwBuffer = sizeof wchDisplay;
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
								if ( wstrBuffer.substr( 0, 7 ) == std::wstring( wszAnalysisTool ).substr( 0, 7 ) )
									px_assert( false );
						}
						if ( !ssWMIC.eof( ) )
						{
							std::getline( ssWMIC, wstrBuffer );
							for each ( auto& wszAnalysisTool in wszAnalysisToolsInstallName )
								if ( wstrBuffer.substr( 0, 7 ) == std::wstring( wszAnalysisTool ).substr( 0, 7 ) )
									px_assert( false );
						}
					}
					while ( !ssReg.eof( ) || !ssWMIC.eof( ) );
				}
			}
			return true;
		}

		bool AnalysisToolsRunning( )
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
				// then go to GetProcessID to make sure they arent forcing GetProcessID to false

				if ( GetProcessID( wszAnalysisTool ) )
					px_assert( bResult );
				else if ( bResult ) // this is only true at the end of the list, and the exe should be running, thus, we've been
					px_assert( false ); // byte patched!
			}
			return true;
		}
	}

	namespace Dump
	{

	}

	namespace Injection
	{

	}

	namespace Sandbox
	{
		namespace Timely
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
