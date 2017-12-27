#include "../../dllmain.h"

void CRecoilControl::RecoilControl( )
{
	address_t< CPlayer > aplrLocalPlayerCopy = aplrLocalPlayer;
	if ( aplrLocalPlayerCopy.xValue.ulShotsFired > 1 ) // ignore shot count
	{
		if ( ulOldShotsFired < aplrLocalPlayerCopy.xValue.ulShotsFired )
		{
			angle_t angCurrentAimPunch { }; // = ( plrLocalPlayer.val.angAimPunch - angOldAimPunch ) * 2.f;

			float flSmooth = aplrLocalPlayerCopy.xValue.flNextAttack;
			for ( unsigned short sLoop = unsigned short( aplrLocalPlayerCopy.xValue.flNextAttack * MILLISECONDS_PER_SECOND ); sLoop > 0;
			      sLoop -= unsigned short( eng.GetGlobalVars( ).flIntervalPerTick * MILLISECONDS_PER_SECOND ) )
			{
				eng.SetViewAngle( eng.GetViewAngle( ) - angCurrentAimPunch / flSmooth );
				Wait( sLoop );
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
