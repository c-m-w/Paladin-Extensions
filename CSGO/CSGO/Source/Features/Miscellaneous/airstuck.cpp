#include "../../dllmain.h"

void CAirstuck::AirStuck( )
{
	if ( eng.GetAttack( ) != ( KS_DEFAULT | KS_PRESS ) )
	{
		CGlobalVars gvMaxTickCount = eng.GetGlobalVars( );
		gvMaxTickCount.tickcount = INT_MAX;
		eng.SetGlobalVars( gvMaxTickCount );
	}
}

CAirstuck air;
