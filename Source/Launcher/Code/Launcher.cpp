/// Launcher.cpp

#include "Precompile.hpp"

#define WIN_ENTRY
#define USE_NAMESPACES
#define USE_DEFINITIONS
#include "../../Framework/Code/Framework.hpp"

std::unique_ptr< CWindow > pWindow;

void OnLaunch( )
{
	if ( !SetupFramework( ) )
		return;

	pWindow = std::make_unique< CWindow >( CWindow( XOR( "Launcher" ), { 600.f, 600.f }, GetModuleHandle( nullptr ) ) );
	DRAW.SetTarget( pWindow.get( ) );
	if ( !_Drawing.Setup( ) )
		return;

	while( !INPUT.GetKeyState( VK_DELETE ) )
	{
		if ( pWindow->PollInput( ) )
			continue;

		if( DRAW.BeginFrame( ) )
		{
			auto txtTest = text_t( "test", CDrawing::ROBOTO, 14, 0, 0 );
			txtTest.Initialize( color_t( 0xFFFFFFFF ), CDrawing::NONE );
			txtTest.Draw( location_t( 20.f, 10.f ) );
			DRAW.DrawPolygon( DRAW.Rectangle( rectangle_t( 50.f, 50.f, 10.f, 90.f ), color_t( 0xFFFFFFFF ) ).GetBuffer( ), true );
			DRAW.EndFrame( );
		}

		Pause( );
	}

	ShutdownFramework( );
}
