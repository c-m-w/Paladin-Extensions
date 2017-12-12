#include "../../dllmain.h"

void CFOV::FOV( )
{
	eng.SetFieldOfView( 120 );
	eng.WaitTicks( 1 );
}

void CFOV::WeaponFOV( )
{
	eng.WaitTicks( 1 );
}

CFOV fov;
