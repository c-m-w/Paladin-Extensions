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
	eng.WaitTicks( 1 );
}

void CFOV::WeaponFOV( )
{
	eng.WaitTicks( 1 );
}

CFOV fov;
