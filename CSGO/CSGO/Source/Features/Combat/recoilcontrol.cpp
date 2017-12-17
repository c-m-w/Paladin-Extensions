#include "../../dllmain.h"

void CRecoilControl::RecoilControl( )
{
	if ( eng.GetShotsFired( ) > 1 ) // ignore shot count
	{
		if ( iOldShotsFired < eng.GetShotsFired( ) )
		{
			angle_t angCurrentAimPunch = eng.GetAimPunch( ) - angOldAimPunch;
			angCurrentAimPunch *= 2.f; // rcs factor

			int iNextPrimaryAttack = int( eng.GetNextPrimaryAttack( ) * MILLISECONDS_PER_SECOND / 10 );

			while ( iNextPrimaryAttack > 0 )
			{
				eng.SetViewAngle( eng.GetViewAngle( ) - angCurrentAimPunch / float( iNextPrimaryAttack ) );
				Wait( iNextPrimaryAttack * 10 );
				iNextPrimaryAttack--;
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
