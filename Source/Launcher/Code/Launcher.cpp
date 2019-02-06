/// Launcher.cpp

#include "Precompile.hpp"

#define WIN_ENTRY
#define USE_NAMESPACES
#define USE_DEFINITIONS
#include "../../Framework/Code/Framework.hpp"

std::unique_ptr< CApplicationWindow > pWindow;

void OnLaunch( )
{
	if ( !SetupFramework( ) )
		return;

	pWindow = std::make_unique< CApplicationWindow >( CApplicationWindow( XOR( "Launcher" ), { 1280.f, 720.f }, GetModuleHandle( nullptr ) ) );
	DRAW.SetTarget( pWindow.get( ) );
	if ( !_Drawing.Setup( ) )
		return;

	InitializeInterface( );
	auto wndCurrent = CWindow( CWindow::DEFAULT_FLAGS, rectangle_t( 0, 0, 720, 600 ), "Paladin Extensions", "CSGO", [ ]( )
	{ }, [ ]( )
	{ } );
	AddWindow( &wndCurrent );

	while ( false && !INPUT.GetKeyState( VK_DELETE ) )
	{
		if ( pWindow->PollInput( ) )
			continue;

		if ( DRAW.BeginFrame( ) )
		{
			DrawWindows( );
			DRAW.EndFrame( );
		}

		Pause( );
	}

	ShutdownFramework( );
}
