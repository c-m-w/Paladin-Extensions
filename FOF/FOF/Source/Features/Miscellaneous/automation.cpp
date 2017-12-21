#include "../../dllmain.h"

/*if ( FAKE SCROLL )
{
	for ( int i = rand( ) % 5; i < 7; i++ )
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
	if ( eng.GetFlags( ) & FL_ONGROUND )
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
			if ( eng.GetFlags( ) & !FL_ONGROUND )
			{
				eng.SetAttack( !FA_PRESS );
			}
		}
	}
}

void CAutomation::AutoShoot( )
{
	// TODO weapon ID for pistols, shotguns (not xm), and snipers (not autosnipers)
	if ( eng.GetNextPrimaryAttack( ) <= 0.f )
	{
		eng.SetAttack( FA_TICK );
	}
	else
	{
		eng.SetAttack( !FA_PRESS );
	}
}

CAutomation aut;
