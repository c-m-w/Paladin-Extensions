#include "../../dllmain.h"

void CNoFlash::NoFlash( )
{
	plrLocalPlayer.val.flFlashMaxAlpha = 0;
	eng.SetLocalPlayer( );
}

CNoFlash nof;
