#include "../../dllmain.h"

void CFOV::FOV( )
{
	CPlayer plrNewLocalPlayer = aplrLocalPlayer.xValue;
	plrNewLocalPlayer.ulDefaultFOV = 120;
	eng.SetLocalPlayer( plrNewLocalPlayer );
}

void CFOV::WeaponFOV( )
{}

CFOV fov;
