#include "../../dllmain.h"

void CFOV::FOV( )
{
	CPlayer plrNewLocalPlayer = plrLocalPlayer.xValue;
	plrNewLocalPlayer.uiDefaultFOV = 120;
	eng.SetLocalPlayer( plrNewLocalPlayer );
}

void CFOV::WeaponFOV( )
{}

CFOV fov;
