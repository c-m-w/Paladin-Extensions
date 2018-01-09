#include "../../dllmain.h"

void CFOV::FOV( )
{
	CPlayer plrNewLocalPlayer = plrLocalPlayer.xValue;
	plrNewLocalPlayer.iDefaultFOV = 120;
	eng.SetLocalPlayer( plrNewLocalPlayer );
}

void CFOV::WeaponFOV( )
{ }

CFOV fov;
