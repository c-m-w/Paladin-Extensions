#include "../../dllmain.h"

void CFOV::FOV( )
{
	plrLocalPlayer.xValue.ulDefaultFOV = 120;
	eng.SetLocalPlayer( );
}

void CFOV::WeaponFOV( )
{}

CFOV fov;
