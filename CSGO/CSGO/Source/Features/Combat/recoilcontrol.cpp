#include "../../dllmain.h"

void CRecoilControl::RecoilControl( )
{
	if ( eng.GetShotsFired( ) > 1 ) // ignore shot count
	{
		if ( eng.GetNextPrimaryAttack( ) <= 0.f )
		{
			angle_t angCurrentAimPunch = eng.GetAimPunch( ) - angOldAimPunch;
			angCurrentAimPunch *= 2.f; // rcs factor

			while ( eng.GetNextPrimaryAttack( ) <= 0.f )
			{
				Wait( 1 );
			}

			int iStartingShotsFired = eng.GetShotsFired( );
			int iNextPrimaryAttack = int( eng.GetNextPrimaryAttack( ) * MILLISECONDS_PER_SECOND );

			while ( iNextPrimaryAttack > 0 && !( eng.GetAttack( ) & FA_DEFAULT ) && iStartingShotsFired == eng.GetShotsFired( ) && eng.GetNextPrimaryAttack( ) > 0.f )
			{
				eng.SetViewAngle( eng.GetViewAngle( ) - angCurrentAimPunch / float( iNextPrimaryAttack ) );
				Wait( iNextPrimaryAttack );
				iNextPrimaryAttack--;
			}

			angOldAimPunch = eng.GetAimPunch( );
		}
	}
	else
	{
		angOldAimPunch = { 0, 0, 0 };
	}
}

CRecoilControl rcs;
