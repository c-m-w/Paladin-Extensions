#include "main.hpp"

using namespace Paladin;

void OnAttach( )
{
	if ( !inject.GetElevationState( ) )
		return;

	Utilities::CaptureInterfaces( );

	Utilities::HookAll( );
}

void OnDetach( )
{
	Utilities::UnhookAll( );
}
