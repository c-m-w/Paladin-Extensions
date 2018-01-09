#include "../../dllmain.h"

void CRecoilControl::RecoilControl( )
{
	if ( plrLocalPlayer.xValue._My_val.uiShotsFired > 1 ) // ignore shot count
	{
		if ( uiOldShotsFired < plrLocalPlayer.xValue._My_val.uiShotsFired )
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
			uiOldShotsFired = plrLocalPlayer.xValue._My_val.uiShotsFired;
		}
	}
	else
	{
		angOldAimPunch = { 0, 0, 0 };
		uiOldShotsFired = 0;
	}
}

CRecoilControl rcs;
