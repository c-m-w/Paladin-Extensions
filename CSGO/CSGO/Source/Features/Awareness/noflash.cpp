#include "../../dllmain.h"

void CNoFlash::NoFlash( )
{
	eng.SetFlashMaxAlpha( 0 );
	eng.WaitTicks( 1 );
}

CNoFlash nof;
