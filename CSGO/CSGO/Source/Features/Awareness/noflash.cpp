#include "../../dllmain.h"

void CNoFlash::NoFlash( )
{
	address_t< CPlayer > aplrLocalPlayerCopy = plrLocalPlayer;
	CPlayer plrNewLocalPlayer = aplrLocalPlayerCopy.xValue;
	plrNewLocalPlayer.flFlashMaxAlpha = 0;
	eng.SetLocalPlayer( plrNewLocalPlayer );
}

CNoFlash nof;
