#include "../../dllmain.h"

void CAutomation::AutoJump( )
{
	// TODO fake scroll
	if ( plrLocalPlayer.xValue.fFlags & FL_ONGROUND )
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
	if ( eng.GetAttack( ) & ACTION_PRESS && plrLocalPlayer.xValue.fFlags & ~FL_ONGROUND )
	{
		eng.SetAttack( ACTION_NONE );
	}
}

void CAutomation::AutoShoot( )
{
	// TODO if weapon ID for pistols, shotguns (not xm), and snipers (not autosnipers)
	if ( plrLocalPlayer.xValue.flNextAttack - eng.GetGlobalVars( ).flCurrentTime <= 0.f )
	{
		eng.SetAttack( ACTION_TICK );
	}
	else
	{
		eng.SetAttack( ACTION_NONE );
	}
}

CAutomation aut;
