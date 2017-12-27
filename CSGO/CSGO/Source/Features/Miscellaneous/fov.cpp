#include "../../dllmain.h"

void CFOV::FOV( )
{
	address_t< CPlayer > aplrLocalPlayerCopy = aplrLocalPlayer;
	CPlayer plrNewLocalPlayer = aplrLocalPlayerCopy.xValue;
	plrNewLocalPlayer.ulDefaultFOV = 120;
	eng.SetLocalPlayer( plrNewLocalPlayer );
}

void CFOV::WeaponFOV( )
{}

CFOV fov;
