#include "../../dllmain.h"

void CAirstuck::AirStuck( )
{
	if ( eng.GetAttack( ) != ( ACTION_DEFAULT | ACTION_PRESS ) )
	{
		CGlobalVars gvMaxTickCount = eng.GetGlobalVars( );
		gvMaxTickCount.uiTickCount = INT_MAX;
		eng.SetGlobalVars( gvMaxTickCount );
	}
}

CAirstuck air;
