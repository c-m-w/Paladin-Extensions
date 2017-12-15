#include "../../dllmain.h"

void CRecoilControl::RecoilControl( )
{
	if ( eng.GetShotsFired( ) > 1 ) // ignore shot count
	{
		if ( eng.GetNextPrimaryAttack( ) <= 0.f )
		{
			eng.WaitTicks( 1 );

			angle_t angCurrentAimPunch = eng.GetAimPunch( ) - angOldAimPunch;
			angCurrentAimPunch *= 2.f; // rcs factor
			
			for ( int iNextPrimaryAttack = eng.GetNextPrimaryAttack( ) * eng.GetGlobalVars( ).interval_per_tick; iNextPrimaryAttack > 0; iNextPrimaryAttack-- )
			{
				eng.SetViewAngle( eng.GetViewAngle( ) - angCurrentAimPunch / iNextPrimaryAttack );
				eng.WaitTicks( 1 );
			}

			angOldAimPunch = eng.GetAimPunch( );
		}
	}
	else
	{
		angOldAimPunch = { 0, 0, 0 };
	}
	eng.WaitTicks( 1 );
}

CRecoilControl rcs;
