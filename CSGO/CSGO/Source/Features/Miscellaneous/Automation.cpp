#include "../../dllmain.h"

/*if ( FAKE SCROLL )
{
	for ( unsigned short us= rand( ) % 5; i < 7; i++ )
	{
		eng.WaitTicks( rand( ) % 3 + 1 );
		eng.SetJump( FA_TICK );
	}
}
else if ( DIST FROM GROUND < 45 && DIST FROM GROUND > 0 )
{
	if ( !( DIST FROM GROUND % 15 ) )
	{
		eng.SetJump( FA_TICK );
	}
}*/

void CAutomation::AutoJump( )
{
	// TODO fake scroll
	if ( plrLocalPlayer.val.fFlags & FL_ONGROUND )
	{
		eng.SetJump( ACTION_TICK );
	}
	else
	{
		eng.SetJump( ACTION_NONE );
	}
}

void CAutomation::AutoNade( )
{
	// TODO weapon ID for nades
	if ( eng.GetAttack( ) & ACTION_PRESS && plrLocalPlayer.val.fFlags & ~FL_ONGROUND )
	{
		eng.SetAttack( ACTION_NONE );
	}
}

void CAutomation::AutoShoot( )
{
	// TODO weapon ID for pistols, shotguns (not xm), and snipers (not autosnipers)
	if ( plrLocalPlayer.val.flNextAttack - eng.GetGlobalVars( ).flCurrentTime <= 0.f )
	{
		eng.SetAttack( ACTION_TICK );
	}
	else
	{
		eng.SetAttack( ACTION_NONE );
	}
}

CAutomation aut;
