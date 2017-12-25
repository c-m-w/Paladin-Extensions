#include "../../dllmain.h"

void CNoFlash::NoFlash( )
{
	plrLocalPlayer.xValue.flFlashMaxAlpha = 0;
	eng.SetLocalPlayer( );
}

CNoFlash nof;
