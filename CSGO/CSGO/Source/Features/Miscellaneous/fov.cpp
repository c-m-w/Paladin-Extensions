#include "../../dllmain.h"

void CFOV::FOV( )
{
	plrLocalPlayer.val.ulDefaultFOV = 120;
	eng.SetLocalPlayer( );
}

void CFOV::WeaponFOV( )
{}

CFOV fov;
