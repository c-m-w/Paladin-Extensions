#include "../../dllmain.h"

void CFOV::FOV( )
{
	CPlayer plrNewLocalPlayer = plrLocalPlayer._My_val.xValue;
	plrNewLocalPlayer.ulDefaultFOV = 120;
	eng.SetLocalPlayer( plrNewLocalPlayer );
}

void CFOV::WeaponFOV( )
{}

CFOV fov;
