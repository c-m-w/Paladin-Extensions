#include "../../dllmain.h"

void CRecoilControl::RecoilControl( )
{
	address_t< CPlayer > aplrLocalPlayerCopy = plrLocalPlayer;
	if ( aplrLocalPlayerCopy.xValue.ulShotsFired > 1 ) // ignore shot count
	{
		if ( ulOldShotsFired < aplrLocalPlayerCopy.xValue.ulShotsFired )
		{
			angle_t angCurrentAimPunch { }; // = ( plrLocalPlayer.val.angAimPunch - angOldAimPunch ) * 2.f;

			float flSmooth = aplrLocalPlayerCopy.xValue.flNextAttack;
			for ( unsigned short usLoop = unsigned short( aplrLocalPlayerCopy.xValue.flNextAttack * MILLISECONDS_PER_SECOND ); usLoop > 0;
			      usLoop -= unsigned short( eng.GetGlobalVars( ).flIntervalPerTick * MILLISECONDS_PER_SECOND ) )
			{
				eng.SetViewAngle( eng.GetViewAngle( ) - angCurrentAimPunch / flSmooth );
				Wait( usLoop );
			}

			/*angOldAimPunch = plrLocalPlayer.val.angAimPunch;*/
			ulOldShotsFired = aplrLocalPlayerCopy.xValue.ulShotsFired;
		}
	}
	else
	{
		angOldAimPunch = { 0, 0, 0 };
		ulOldShotsFired = 0;
	}
}

CRecoilControl rcs;
