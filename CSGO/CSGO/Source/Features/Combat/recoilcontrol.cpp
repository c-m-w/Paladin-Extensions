#include "../../dllmain.h"

void CRecoilControl::RecoilControl( )
{
	if ( eng.GetShotsFired( ) > 1 ) // ignore shot count
	{
		if ( iOldShotsFired < eng.GetShotsFired( ) )
		{
			angle_t angCurrentAimPunch = ( eng.GetAimPunch( ) - angOldAimPunch ) * 2.f;

			for ( float flSmooth = eng.GetNextPrimaryAttack( ); flSmooth > 0; flSmooth -= eng.GetGlobalVars( ).interval_per_tick )
			{
				eng.SetViewAngle( eng.GetViewAngle( ) - angCurrentAimPunch / flSmooth );
				Wait( eng.GetGlobalVars( ).interval_per_tick * MILLISECONDS_PER_SECOND );
			}

			angOldAimPunch = eng.GetAimPunch( );
			iOldShotsFired = eng.GetShotsFired( );
		}
	}
	else
	{
		angOldAimPunch = { 0, 0, 0 };
		iOldShotsFired = 0;
	}
}

CRecoilControl rcs;
