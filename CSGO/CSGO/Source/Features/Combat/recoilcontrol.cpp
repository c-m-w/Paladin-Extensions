#include "../../dllmain.h"

void CRecoilControl::RecoilControl( )
{
	if ( plrLocalPlayer.xValue.iShotsFired > 1 ) // ignore shot count
	{
		if ( iOldShotsFired < plrLocalPlayer.xValue.iShotsFired )
		{
			angle_t angCurrentAimPunch { }; // = ( plrLocalPlayer.val.angAimPunch - angOldAimPunch ) * 2.f;

			float flSmooth = plrLocalPlayer.xValue.flNextAttack;
			for ( unsigned short usLoop = unsigned short( plrLocalPlayer.xValue.flNextAttack * MILLISECONDS_PER_SECOND ); usLoop > 0;
			      usLoop -= unsigned short( eng.GetGlobalVars( ).flIntervalPerTick * MILLISECONDS_PER_SECOND ) )
			{
				eng.SetViewAngle( eng.GetViewAngle( ) - angCurrentAimPunch / flSmooth );
				Wait( usLoop );
			}

			/*angOldAimPunch = plrLocalPlayer.val.angAimPunch;*/
			iOldShotsFired = plrLocalPlayer.xValue.iShotsFired;
		}
	}
	else
	{
		angOldAimPunch = { 0, 0, 0 };
		iOldShotsFired = 0;
	}
}

CRecoilControl rcs;
