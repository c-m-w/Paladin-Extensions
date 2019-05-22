/// SteamX.cpp

#include "Precompile.hpp"

#define ENTRY_SOURCE
#include "SteamX.hpp"

// https://developer.valvesoftware.com/wiki/Command_Line_Options#Steam_.28Windows.29
// -login Username Password
// -applaunch 730
// -shutdown
// -silent

// Computer\HKEY_LOCAL_MACHINE\SOFTWARE\WOW6432Node\Valve\Steam
//     InstallPath key
// Computer\HKEY_LOCAL_MACHINE\SOFTWARE\WOW6432Node\Valve\Steam\NSIS
//     Path key

// todo find where steam guard 2fa session is stored and save it so we can have multiple sessions

void OnLaunch( )
{
	// todo safety and comparison of [0] and [1] to see if at least 1 has a steam path, and if both do, that they are the same

	std::string strSteamPath[ 2 ] { { }, { } };

	{
		HKEY hKey;
		RegOpenKeyEx( HKEY_LOCAL_MACHINE, ENC( R"(SOFTWARE\WOW6432Node\Valve\Steam)" ), 0, KEY_READ, &hKey );

		strSteamPath[ 0 ] = ENC( "InstallPath" );
		strSteamPath[ 0 ].resize( 512 );
		RegQueryValueEx( hKey, strSteamPath[ 0 ].c_str( ), nullptr, nullptr, reinterpret_cast< LPBYTE >( &strSteamPath[ 0 ][ 0 ] ), new DWORD( strSteamPath[ 0 ].size( ) ) );

		strSteamPath[ 0 ] = strSteamPath[ 0 ].c_str( ); // do not remove, we need to free the extra mem of the 512 allocated
		strSteamPath[ 0 ] += ENC( "\\Steam.exe" );
	}

	{
		HKEY hKey;
		RegOpenKeyEx( HKEY_LOCAL_MACHINE, ENC( R"(SOFTWARE\WOW6432Node\Valve\Steam\NSIS)" ), 0, KEY_READ, &hKey );

		strSteamPath[ 1 ] = ENC( "Path" );
		strSteamPath[ 1 ].resize( 512 );
		RegQueryValueEx( hKey, strSteamPath[ 1 ].c_str( ), nullptr, nullptr, reinterpret_cast< LPBYTE >( &strSteamPath[ 1 ][ 0 ] ), new DWORD( strSteamPath[ 1 ].size( ) ) );

		strSteamPath[ 1 ] = strSteamPath[ 1 ].c_str( ); // do not remove, we need to free the extra mem of the 512 allocated
		strSteamPath[ 1 ] += ENC( "\\Steam.exe" );
	}

	MessageBox( nullptr, strSteamPath[ 0 ].c_str( ), "Steam/Install Path", 0 );
	MessageBox( nullptr, strSteamPath[ 1 ].c_str( ), "Steam/NSIS/Path", 0 );
}
