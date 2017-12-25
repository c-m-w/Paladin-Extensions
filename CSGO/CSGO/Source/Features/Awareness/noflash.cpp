#include "../../dllmain.h"

void CNoFlash::NoFlash( )
{
	CPlayer plrNewLocalPlayer = aplrLocalPlayer.xValue;
	plrNewLocalPlayer.flFlashMaxAlpha = 0;
	eng.SetLocalPlayer( plrNewLocalPlayer );
}

CNoFlash nof;
