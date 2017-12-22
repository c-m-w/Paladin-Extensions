#include "../../dllmain.h"

void CRecoilControl::RecoilControl( )
{
	if ( plrLocalPlayer.val.ulShotsFired > 1 ) // ignore shot count
	{
		if ( ulOldShotsFired < plrLocalPlayer.val.ulShotsFired )
		{
			angle_t angCurrentAimPunch; // = ( plrLocalPlayer.val.angAimPunch - angOldAimPunch ) * 2.f;

			for ( float flSmooth = plrLocalPlayer.val.flNextAttack; flSmooth > 0; flSmooth -= eng.GetGlobalVars( ).interval_per_tick )
			{
				eng.SetViewAngle( eng.GetViewAngle( ) - angCurrentAimPunch / flSmooth );
				Wait( long( eng.GetGlobalVars( ).interval_per_tick * MILLISECONDS_PER_SECOND ) );
			}

			/*angOldAimPunch = plrLocalPlayer.val.angAimPunch;*/
			ulOldShotsFired = plrLocalPlayer.val.ulShotsFired;
		}
	}
	else
	{
		angOldAimPunch = { 0, 0, 0 };
		ulOldShotsFired = 0;
	}
}

CRecoilControl rcs;
