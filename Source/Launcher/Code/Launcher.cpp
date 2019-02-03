/// Launcher.cpp

#include "Precompile.hpp"

#define WIN_ENTRY
#include "../../Framework/Code/Framework.hpp"

std::unique_ptr< CWindow > pWindow;

void OnLaunch( )
{
	if ( !InitializeFramework( ) )
		return;

	pWindow = std::make_unique< CWindow >( CWindow( XOR( "Launcher" ), { 600.f, 600.f }, GetModuleHandle( nullptr ) ) );
	_Drawing.SetTarget( pWindow.get( ) );
	if ( !_Drawing.Setup( ) )
		return;
}
