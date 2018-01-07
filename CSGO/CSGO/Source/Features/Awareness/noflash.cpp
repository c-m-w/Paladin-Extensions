#include "../../dllmain.h"

void CNoFlash::NoFlash( )
{
	CPlayer plrNewLocalPlayer = plrLocalPlayer.xValue;
	plrNewLocalPlayer.flFlashMaxAlpha = 0;
	eng.SetLocalPlayer( plrNewLocalPlayer );
}

CNoFlash nof;
