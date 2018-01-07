#include "../../dllmain.h"

void CRecoilControl::RecoilControl( )
{
	if ( plrLocalPlayer.xValue._My_val.ulShotsFired > 1 ) // ignore shot count
	{
		if ( ulOldShotsFired < plrLocalPlayer.xValue._My_val.ulShotsFired )
		{
			angle_t angCurrentAimPunch { }; // = ( plrLocalPlayer.val.angAimPunch - angOldAimPunch ) * 2.f;

			float flSmooth = plrLocalPlayer.xValue._My_val.flNextAttack;
			for ( unsigned short usLoop = unsigned short( plrLocalPlayer.xValue._My_val.flNextAttack * MILLISECONDS_PER_SECOND ); usLoop > 0;
			      usLoop -= unsigned short( eng.GetGlobalVars( ).flIntervalPerTick * MILLISECONDS_PER_SECOND ) )
			{
				eng.SetViewAngle( eng.GetViewAngle( ) - angCurrentAimPunch / flSmooth );
				Wait( usLoop );
			}

			/*angOldAimPunch = plrLocalPlayer.val.angAimPunch;*/
			ulOldShotsFired = plrLocalPlayer.xValue._My_val.ulShotsFired;
		}
	}
	else
	{
		angOldAimPunch = { 0, 0, 0 };
		ulOldShotsFired = 0;
	}
}

CRecoilControl rcs;
