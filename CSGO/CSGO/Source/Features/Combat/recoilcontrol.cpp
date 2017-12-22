#include "../../dllmain.h"

void CRecoilControl::RecoilControl( )
{
	if ( plrLocalPlayer.val.ulShotsFired > 1 ) // ignore shot count
	{
		if ( ulOldShotsFired < plrLocalPlayer.val.ulShotsFired )
		{
			angle_t angCurrentAimPunch{}; // = ( plrLocalPlayer.val.angAimPunch - angOldAimPunch ) * 2.f;

			float flSmooth = plrLocalPlayer.val.flNextAttack;
			for ( short sLoop = plrLocalPlayer.val.flNextAttack* MILLISECONDS_PER_SECOND; sLoop > 0;
				  sLoop -= eng.GetGlobalVars( ).flIntervalPerTick * MILLISECONDS_PER_SECOND )
			{
				eng.SetViewAngle( eng.GetViewAngle( ) - angCurrentAimPunch / flSmooth );
				Wait( sLoop );
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
