#include "../../dllmain.h"

void CAutomation::AutoJump( )
{
	// TODO fake scroll
	address_t< CPlayer > aplrLocalPlayerCopy = aplrLocalPlayer;
	if ( aplrLocalPlayerCopy.xValue.fFlags & FL_ONGROUND )
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
	address_t< CPlayer > aplrLocalPlayerCopy = aplrLocalPlayer;
	if ( eng.GetAttack( ) & ACTION_PRESS && aplrLocalPlayerCopy.xValue.fFlags & ~FL_ONGROUND )
	{
		eng.SetAttack( ACTION_NONE );
	}
}

void CAutomation::AutoShoot( )
{
	// TODO if weapon ID for pistols, shotguns (not xm), and snipers (not autosnipers)
	address_t< CPlayer > aplrLocalPlayerCopy = aplrLocalPlayer;
	if ( aplrLocalPlayerCopy.xValue.flNextAttack - eng.GetGlobalVars( ).flCurrentTime <= 0.f )
	{
		eng.SetAttack( ACTION_TICK );
	}
	else
	{
		eng.SetAttack( ACTION_NONE );
	}
}

CAutomation aut;
