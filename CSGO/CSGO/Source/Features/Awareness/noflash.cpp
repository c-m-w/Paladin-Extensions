#include "../../dllmain.h"

void CNoFlash::NoFlash( )
{
	CPlayer plrNewLocalPlayer = plrLocalPlayer._My_val.xValue;
	plrNewLocalPlayer.flFlashMaxAlpha = 0;
	eng.SetLocalPlayer( plrNewLocalPlayer );
}

CNoFlash nof;
