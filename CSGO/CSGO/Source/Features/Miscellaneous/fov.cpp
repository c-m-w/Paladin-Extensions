#include "../../dllmain.h"

void CFOV::FOV( )
{
	if ( !eng.GetActiveWeaponZoomLevel( ) )
	{
		eng.SetFieldOfView( 120 );
	}
	else
	{
		eng.SetFieldOfView( 90 );
	}
}

void CFOV::WeaponFOV( )
{}

CFOV fov;
