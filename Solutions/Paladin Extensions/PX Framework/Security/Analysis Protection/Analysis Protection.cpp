/// Analysis Protection.cpp

#define PX_USE_NAMESPACES
#include "../../PX Framework.hpp"

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
	namespace Debug
	{
		bool RemoteDebuggerPresence( HANDLE hTarget /*= GetCurrentProcess( )*/ )
		{
			BOOL bPresent;
			px_assert( 0 != CheckRemoteDebuggerPresent( hTarget, &bPresent ) );
			return FALSE != bPresent;
		}
	}

	namespace Analysis
	{
		bool AnalysisToolsInstalled( )
		{
			wchar_t wchDisplay[ 1024 ];
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

					wchar_t wchSubKeyID[ dwBuffer ];
					wsprintf( wchSubKeyID, L"%s\\%s", wszRegPath, wchAppKeyID );
					HKEY hkeyApp;
					px_assert( RegOpenKeyEx( HKEY_LOCAL_MACHINE, wchSubKeyID, 0, KEY_READ, &hkeyApp ) == ERROR_SUCCESS );

					dwBuffer = sizeof wchDisplay;
					DWORD dwType = KEY_ALL_ACCESS;
					px_assert( RegQueryValueEx( hkeyApp, PX_XOR( L"DisplayName" ), nullptr, &dwType, reinterpret_cast< BYTE* >( wchDisplay ), &dwBuffer ) == ERROR_SUCCESS );
					wprintf( L"%s\n", wchDisplay );

					RegCloseKey( hkeyApp );
				} while ( true );
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
					std::wstringstream ssReg( wchDisplay ), ssWMIC( RetrieveInfo( PX_XOR( L"SELECT * FROM Win32_Product" ) ) );
					do
					{
						std::wstring wstrBuffer;
						if ( !ssReg.eof )
						{
							std::getline( ssReg, wstrBuffer );
							for each ( auto& wszAnalysisTool in wszAnalysisToolsInstallName )
								if ( wstrBuffer.substr( 0, 7 ) == std::wstring( wszAnalysisTool ).substr( 0, 7 ) )
									return true;
						}
						if ( !ssWMIC.eof )
						{
							std::getline( ssWMIC, wstrBuffer );
							for each ( auto& wszAnalysisTool in wszAnalysisToolsInstallName )
								if ( wstrBuffer.substr( 0, 7 ) == std::wstring( wszAnalysisTool ).substr( 0, 7 ) )
									return true;
						}
					} while ( !ssReg.eof( ) || !ssWMIC.eof( ) );
				}
			}
			return false;
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
			bool bResult = true;
			for each ( auto& wszAnalysisTool in wszAnalysisToolsExecutableTitle )
				if ( std::wstring( PX_XOR( L"lsass.exe" ) ) == wszAnalysisTool )
				{
					bResult = false;
					goto Ensure;
				}
				else Ensure: if ( GetProcessID( wszAnalysisTool ) )
					return bResult;
			return false; // bytepatched
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

	bool CheckAll( )
	{
		
	}
}
