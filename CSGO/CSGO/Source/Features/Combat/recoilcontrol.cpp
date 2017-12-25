#include "../../dllmain.h"

void CRecoilControl::RecoilControl( )
{
	if ( aplrLocalPlayer.xValue.ulShotsFired > 1 ) // ignore shot count
	{
		if ( ulOldShotsFired < aplrLocalPlayer.xValue.ulShotsFired )
		{
			angle_t angCurrentAimPunch { }; // = ( plrLocalPlayer.val.angAimPunch - angOldAimPunch ) * 2.f;

			float flSmooth = aplrLocalPlayer.xValue.flNextAttack;
			for ( unsigned short sLoop = unsigned short( aplrLocalPlayer.xValue.flNextAttack * MILLISECONDS_PER_SECOND ); sLoop > 0;
			      sLoop -= unsigned short( eng.GetGlobalVars( ).flIntervalPerTick * MILLISECONDS_PER_SECOND ) )
			{
				eng.SetViewAngle( eng.GetViewAngle( ) - angCurrentAimPunch / flSmooth );
				Wait( sLoop );
			}

			/*angOldAimPunch = plrLocalPlayer.val.angAimPunch;*/
			ulOldShotsFired = aplrLocalPlayer.xValue.ulShotsFired;
		}
	}
	else
	{
		angOldAimPunch = { 0, 0, 0 };
		ulOldShotsFired = 0;
	}
}

CRecoilControl rcs;
