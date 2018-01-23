#include "../../main.h"

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
	// int iWeaponID = eng.GetEntityBase( ( eng.GetLocalPlayer( ).hActiveWeapon & INDEX_ENTITY_MASK ) - 1 );
	// if ( iWeaponID == SMOKEGRENADE || iWeaponID == HEGRENADE || iWeaponID == FLASHBANG || iWeaponID == MOLOTOV || iWeaponID == INCGRENADE || iWeaponID == DECOY )
	if ( eng.GetAttack( ) & ACTION_PRESS && plrLocalPlayer.xValue.fFlags & ~FL_ONGROUND )
	{
		eng.SetAttack( ACTION_NONE );
	}
}

void CAutomation::AutoShoot( )
{
	// TODO if weapon ID for pistols, shotguns (not xm), and snipers (not autosnipers)
	// int iWeaponID = eng.GetEntityBase( ( eng.GetLocalPlayer( ).hActiveWeapon & INDEX_ENTITY_MASK ) - 1 );
	// if ( iWeaponID == USP_SILENCER || iWeaponID == HKP2000 || iWeaponID == GLOCK || iWeaponID == ELITE || iWeaponID == P250 ||
	//		iWeaponID == FIVESEVEN || iWeaponID == TEC9 || iWeaponID == CZ75A || iWeaponID == DEAGLE || iWeaponID == REVOLVER )
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
