/// PX Installer.cpp

#include "PX Precompiled.hpp"

#define PX_ENTRY_AS_WIN
#define PX_INSTANCE_ID L"Installer"
#include <Jeremia-h/Entry Manager.hpp>

#include "PX Installer.hpp"

const wstr_t wstrApplicationExecutableNames[ ] { { }, PX_XOR( L"Steam.exe" ), PX_XOR( L"csgo.exe" ), PX_XOR( L"pubg.exe" ), PX_XOR( L"rsix.exe" ) };
bool bExtensionAccess[ PX_EXTENSION_MAX ];
bool bTerminating = false;

void PX_API MonitorDetectionVectors( )
{
#if defined NDEBUG
	DWORD dwBuffer;
	while ( !bTerminating )
	{
		for each ( auto wstrExecutable in wstrApplicationExecutableNames )
		{
			if ( !CheckForAnalysis( ) )
				Destroy( );
			else if ( !wstrExecutable.empty( ) && ( dwBuffer = GetProcessID( wstrExecutable ) ) )
				TerminateProcess( dwBuffer );
		}
		Pause( 1500ull );
	}
#endif
}

void PX_API UI::Manager::SetLayout( )
{
	
}

void PX_API DrawWindow( )
{
	unsigned uDimensions[ 2 ] { 720, 435 };
	InitializeRenderTarget( uDimensions, PX_XOR( L"Paladin Extensions" ) );
	InitializeUI( PX_XOR( "Manager" ) );

	DEVMODE pDevMode { };
	EnumDisplaySettings( nullptr, ENUM_CURRENT_SETTINGS, &pDevMode );
	while ( !bTerminating )
	{
		const auto mmtStart = GetMoment( );
		if ( !UI::Manager::Render( ) )
			break;

		// todo vsync 1000ull / pDevMode.dmDisplayFrequency - ( GetMoment( ) - mmtStart )
		Pause( 1ull ); // Refresh the application at the speed of the monitor's refresh rate.
	}
}

void PX_API OnLaunch( )
{
	if ( !EnsureElevation( ) )
		Popup( EMBType::FATAL_ERROR, PX_XOR( L"You must run the program as administrator." ) );

	if ( !FileWrite( PX_APPDATA + PX_XOR( L"data.px" ), GetExecutableDirectory( ), false ) )
		return;

	std::thread tDraw( DrawWindow );
	tDraw.detach( );

	// review MAKE SURE TO UNCOMMENT THIS BEFORE RELEASING
#if defined _NDEBUG
	if ( !CheckForAllAnalysis( ) )
		Request( PX_XOR( "https://www.paladin.rip/ban.php" ), { } ),
		Destroy( );
	std::thread( [ ]( )
	{
		if ( !CheckForAllAnalysis( ) )
			Request( PX_XOR( "https://www.paladin.rip/ban.php" ), { } ),
			Destroy( );

		while ( !CheckForAnalysis( ) )
			Pause( 1 );
		Request( PX_XOR( "https://www.paladin.rip/ban.php" ), { } );
		Destroy( );
	} ).detach( );

	std::thread tMonitorDetectionVectors( MonitorDetectionVectors );
	tMonitorDetectionVectors.detach( );
#endif

	Login( bExtensionAccess );
}
