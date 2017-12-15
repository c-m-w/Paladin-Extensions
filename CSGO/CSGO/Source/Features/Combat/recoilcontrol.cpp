#include "../../dllmain.h"

void CRecoilControl::RecoilControl( )
{
	if ( eng.GetShotsFired( ) > 1 ) // ignore shot count
	{
		if ( eng.GetNextPrimaryAttack( ) <= 0.f )
		{
			while ( eng.GetNextPrimaryAttack( ) <= 0.f )
			{
				Wait( 1 );
			}
			angle_t angCurrentAimPunch = eng.GetAimPunch( ) - angOldAimPunch;
			angCurrentAimPunch *= 2.f; // rcs factor

			int iStartingShotsFired = eng.GetShotsFired( );
			for ( int iNextPrimaryAttack = int( eng.GetNextPrimaryAttack( ) / eng.GetGlobalVars( ).interval_per_tick + 0.5f); iNextPrimaryAttack > 0; iNextPrimaryAttack-- )
			{
				eng.SetViewAngle( eng.GetViewAngle( ) - angCurrentAimPunch );
				eng.WaitTicks( 1 );
				if ( eng.GetAttack( ) & ( FA_DEFAULT | FA_PRESS ) || iStartingShotsFired != eng.GetShotsFired( ) )
				{
					break;
				}
			}

			angOldAimPunch = eng.GetAimPunch( );
		}
	}
	else
	{
		angOldAimPunch = { 0, 0, 0 };
	}
}

CRecoilControl rcs;
