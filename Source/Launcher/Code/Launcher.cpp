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
			auto txtTest = text_t( ICON_FA_BOMB, CDrawing::FA, 48, 0, 0 );
			auto txtTest1 = text_t( "iraq #1", CDrawing::ENVY, 48, 0, 0 );
			auto txtTest2 = text_t( ICON_FA_BAND_AID, CDrawing::FA, 48, 0, 0 );
			txtTest.Initialize( color_t( { 0, 0, 0, 255 } ), CDrawing::ICON );
			txtTest1.Initialize( color_t( { 0, 0, 0, 255 } ), CDrawing::NONE );
			txtTest2.Initialize( color_t( { 0, 0, 0, 255 } ), CDrawing::ICON );
			DRAW.DrawPolygon( DRAW.Rectangle( rectangle_t( 0.f, 0.f, 600.f, 600.f ), color_t( 0xFFFFFFFF ) ).GetBuffer( ), true );
			txtTest.Draw( location_t( 20.f, 10.f ) );
			txtTest1.Draw( location_t( 120, 80 ) );
			txtTest2.Draw( location_t( 80, 32 ) );
			DRAW.EndFrame( );
		}

		Pause( );
	}

	ShutdownFramework( );
}
