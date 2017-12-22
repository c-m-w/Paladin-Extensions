#include "../../dllmain.h"

void CFOV::FOV( )
{
	plrLocalPlayer.val.iFOV = 120;
	eng.SetLocalPlayer( );
}

void CFOV::WeaponFOV( )
{}

CFOV fov;
