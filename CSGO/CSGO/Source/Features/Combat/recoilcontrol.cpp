#include "../../dllmain.h"

void CRecoilControl::RecoilControl( )
{
	if ( eng.GetShotsFired( ) > 1 ) // ignore shot count
	{
		if ( eng.GetNextPrimaryAttack( ) <= 0.f )
		{
			eng.WaitTicks( 1 );

			angle_t angCurrentAimPunch = eng.GetAimPunch( ) - angOldAimPunch;
			angCurrentAimPunch *= 2.f; // rcs factor

			// smoothness factor = 25
			for ( float flNextPrimaryAttack = eng.GetNextPrimaryAttack( ); flNextPrimaryAttack > 0.f; flNextPrimaryAttack = eng.GetNextPrimaryAttack( ) )
			{
				eng.SetViewAngle( eng.GetViewAngle( ) - angCurrentAimPunch / 25.f );
				Wait( int( flNextPrimaryAttack / .025f ) );
			}

			angOldAimPunch = eng.GetAimPunch( );
		}
	}
	else
	{
		angOldAimPunch = { 0, 0, 0 };
	}
	eng.WaitTicks( 1 );
}

CRecoilControl rcs;
