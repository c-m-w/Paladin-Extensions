/// SteamX.cpp

#include "Precompile.hpp"

#define ENTRY_SOURCE
#include "SteamX.hpp"

//	Note:																				\
	https://developer.valvesoftware.com/wiki/Command_Line_Options#Steam_.28Windows.29	\
	-login Username Password															\
	-applaunch 730																		\
	-shutdown																			\
	-silent																				\

//	Note:																				\
	Computer\HKEY_LOCAL_MACHINE\SOFTWARE\WOW6432Node\Valve\Steam						\
		InstallPath key																	\
	Computer\HKEY_LOCAL_MACHINE\SOFTWARE\WOW6432Node\Valve\Steam\NSIS					\
		Path key																		\

// Todo: find where steam guard 2fa session is stored and save it so we can have multiple sessions
// Todo: possibly get logins from the server? this way nothing is stored client side and is safe in case they get a RAT
// Todo: safety of winapi funcs and comparison of [0] and [1] to see if at least 1 has a steam path, and if both do, that they are the same
// Todo: actually check that the exe's are there and at least probably a real size/a sig identifying it as steam is in there, this way we can make sure there is no app trying to steal steam accounts (i.e. RAT)

std::string GetSteamExecutablePath( bool bAllowExceptions = true )
{
	std::string strSteamInstallPath, strSteamNSISPath;

	{
		HKEY hKey;
		RegOpenKeyEx( HKEY_LOCAL_MACHINE, ENC( R"(SOFTWARE\WOW6432Node\Valve\Steam)" ), 0, KEY_READ, &hKey );

		strSteamInstallPath = ENC( "InstallPath" );
		strSteamInstallPath.resize( 512 );
		RegQueryValueEx( hKey, strSteamInstallPath.c_str( ), nullptr, nullptr, reinterpret_cast< LPBYTE >( &strSteamInstallPath[ 0 ] ), new DWORD( strSteamInstallPath.size( ) ) );

		strSteamInstallPath = strSteamInstallPath.c_str( ); // do not remove, we need to free the extra mem of the 512 allocated
		strSteamInstallPath += ENC( "\\Steam.exe" );
	}

	if ( !bAllowExceptions )
		return strSteamInstallPath;
	{
		HKEY hKey;
		RegOpenKeyEx( HKEY_LOCAL_MACHINE, ENC( R"(SOFTWARE\WOW6432Node\Valve\Steam\NSIS)" ), 0, KEY_READ, &hKey );

		strSteamNSISPath = ENC( "Path" );
		strSteamNSISPath.resize( 512 );
		RegQueryValueEx( hKey, strSteamNSISPath.c_str( ), nullptr, nullptr, reinterpret_cast< LPBYTE >( &strSteamNSISPath[ 0 ] ), new DWORD( strSteamNSISPath.size( ) ) );

		strSteamNSISPath = strSteamNSISPath.c_str( ); // do not remove, we need to free the extra mem of the 512 allocated
		strSteamNSISPath += ENC( "\\Steam.exe" );
	}

	if ( strSteamInstallPath == strSteamNSISPath )
		return strSteamInstallPath;
	throw std::runtime_error( ENC( "Installation directory mismatch" ) );
}

void OnLaunch( )
{
	std::string strArguments[ ] { ENC( "-shutdown" ), ENC( "-login gaben@valvesoftware.com moolyftw" ) };
	auto strBuffer = GetSteamExecutablePath( false );
	int a[ ] { strBuffer.size( ) + 1, 0 };
	const char *strSteamPath = new char[ a[ 0 ] ];
	for ( int i = 0; i < a[ 0 ]; i++ ) // this cancer code is brought to you buy C++ automatic string copy destruction.
		const_cast< char* >( strSteamPath )[ i ] = strBuffer[ i ];
	a[ 1 ] = std::string( strSteamPath ).find_last_of( "\\" ) + 1;
	const char *strSteamDirectory = new char[ a[ 1 ] ];
	for ( int i = 0; i < a[ 1 ]; i++ )
		const_cast< char* >( strSteamDirectory )[ i ] = strSteamPath[ i ];
	const_cast< char* >( strSteamDirectory )[ a[ 1 ] ] = 0;

	STARTUPINFO si { sizeof( STARTUPINFO ) };
	PROCESS_INFORMATION pi { };
	if ( 0 == CreateProcess( strSteamPath, &strArguments[ 0 ][ 1 ], nullptr, nullptr, FALSE, 0u, nullptr, strSteamDirectory, &si, &pi ) )
		MessageBox( 0, std::to_string( GetLastError( ) ).c_str( ), 0, 0 );
	CloseHandle( pi.hProcess );
	CloseHandle( pi.hThread );

	try
	{
		delete[ ] strSteamDirectory;
		delete[ ] strSteamPath;
	}
	catch ( ... )
	{ }
}
