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
		eng.SetJump( FA_TICK );
	}
	else
	{
		eng.SetJump( !FA_PRESS );
	}
}

void CAutomation::AutoNade( )
{
	// TODO weapon ID for nades
	if ( true )
	{
		if ( eng.GetAttack( ) & FA_PRESS )
		{
			if ( plrLocalPlayer.val.fFlags & !FL_ONGROUND )
			{
				eng.SetAttack( !FA_PRESS );
			}
		}
	}
}

void CAutomation::AutoShoot( )
{
	// TODO weapon ID for pistols, shotguns (not xm), and snipers (not autosnipers)
	if ( ( plrLocalPlayer.val.flNextAttack - eng.GetGlobalVars( ).curtime ) <= 0.f )
	{
		eng.SetAttack( FA_TICK );
	}
	else
	{
		eng.SetAttack( !FA_PRESS );
	}
}

CAutomation aut;
