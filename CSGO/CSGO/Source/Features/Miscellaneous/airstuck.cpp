#include "../../dllmain.h"

void CAirstuck::AirStuck( )
{
	if ( eng.GetAttack( ) != ( FA_DEFAULT | FA_PRESS ) )
	{
		CGlobalVars gvMaxTickCount = eng.GetGlobalVars( );
		gvMaxTickCount.tickcount = INT_MAX;
		eng.SetGlobalVars( gvMaxTickCount );
	}
}

CAirstuck air;
