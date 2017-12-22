#include "../../dllmain.h"

void CRecoilControl::RecoilControl( )
{
	if ( plrLocalPlayer.val.iShotsFired > 1 ) // ignore shot count
	{
		if ( iOldShotsFired < plrLocalPlayer.val.iShotsFired )
		{
			angle_t angCurrentAimPunch; // = ( plrLocalPlayer.val.angAimPunch - angOldAimPunch ) * 2.f;

			for ( float flSmooth = plrLocalPlayer.val.flNextAttack; flSmooth > 0; flSmooth -= eng.GetGlobalVars( ).interval_per_tick )
			{
				eng.SetViewAngle( eng.GetViewAngle( ) - angCurrentAimPunch / flSmooth );
				Wait( int( eng.GetGlobalVars( ).interval_per_tick * MILLISECONDS_PER_SECOND ) );
			}

			/*angOldAimPunch = plrLocalPlayer.val.angAimPunch;*/
			iOldShotsFired = plrLocalPlayer.val.iShotsFired;
		}
	}
	else
	{
		angOldAimPunch = { 0, 0, 0 };
		iOldShotsFired = 0;
	}
}

CRecoilControl rcs;
