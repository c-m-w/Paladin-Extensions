#include "../../dllmain.h"

void CNoFlash::NoFlash( )
{
	address_t< CPlayer > aplrLocalPlayerCopy = aplrLocalPlayer;
	CPlayer plrNewLocalPlayer = aplrLocalPlayerCopy.xValue;
	plrNewLocalPlayer.flFlashMaxAlpha = 0;
	eng.SetLocalPlayer( plrNewLocalPlayer );
}

CNoFlash nof;
