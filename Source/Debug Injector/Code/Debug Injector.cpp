/// Debug Injector.cpp

#include "Precompile.hpp"

#define WIN_ENTRY
#define ENTRY_SOURCE
#define USE_NAMESPACES
#define USE_DEFINITIONS
#include "../../Framework/Code/Framework.hpp"

#define CURRENT_PROCESS ( CSGO )

enum
{
	CSGO,
	PUBG,
	RSIX,
	RUST,
	MAX
};

std::pair< std::string, std::string > _ProcessInfo[ MAX ]
{
	{ "csgo.exe", "CSGOX.dll" },
	{ { }, { } },
	{ { }, { } },
	{ { }, { } }
};

void OnLaunch( )
{
	if ( !SetupFramework( ) )
		return;

	if ( !_MemoryManager.SetProcess( "csgo.exe", PROCESS_ALL_ACCESS ) )
		MessageBox( 0, "mm.sp", 0, 0 );
	else if ( !_MemoryManager.LoadLibraryEx( R"(D:\Jeremiah\Documents\Paladin-Extensions\Source\Debug\CSGOX.dll)", false ) )
		MessageBox( 0, "mm.lle", 0, 0 );
}

void OnLaunch2( )
{
	if ( !SetupFramework( ) )
		return;

	std::string strVMP { };
	FS.ChangeWorkingDirectory( FS.GetExecutableDirectory( ) );
	if ( !FS.ReadFile( "VMProtectSDK32.dll", strVMP, false ) )
		return;

	std::string strExecutablePath { };
	if ( !SI.GetExecutablePath( _ProcessInfo[ CURRENT_PROCESS ].first, strExecutablePath ) )
		return;

	FS.ChangeWorkingDirectory( strExecutablePath );
	if ( !FS.WriteFile( "VMProtectSDK32.dll", strVMP, false ) )
		return;

	FS.ChangeWorkingDirectory( FS.GetExecutableDirectory( ) );
	if ( !MEM.SetProcess( _ProcessInfo[ CURRENT_PROCESS ].first, PROCESS_ALL_ACCESS ) )
		return;

	MEM.LoadLibraryEx( FS.FileToPath( _ProcessInfo[ CURRENT_PROCESS ].second ), false );
	//MEM.CloseProcess( );
}
