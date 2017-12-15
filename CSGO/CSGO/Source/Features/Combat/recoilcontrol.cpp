#include "../../dllmain.h"

void CRecoilControl::RecoilControl( )
{
	if ( eng.GetShotsFired( ) > 1 ) // ignore shot count
	{
		printf( "\nShots Fired: %i", eng.GetShotsFired( ) );
		printf( "\nTime to next shot: %f", eng.GetNextPrimaryAttack( ) );
		if ( eng.GetNextPrimaryAttack( ) <= 0.f )
		{
			eng.WaitTicks( 1 );
			Wait( 1 );
			printf( "\nTime to next shot: %f", eng.GetNextPrimaryAttack( ) );

			angle_t angCurrentAimPunch = eng.GetAimPunch( ) - angOldAimPunch;
			angCurrentAimPunch *= 2.f; // rcs factor

			for ( int iNextPrimaryAttack = eng.GetNextPrimaryAttack( ) * eng.GetGlobalVars( ).interval_per_tick; iNextPrimaryAttack > 0; iNextPrimaryAttack-- )
			{
				printf( "\nRCS TickStep: %i", iNextPrimaryAttack );
				eng.SetViewAngle( eng.GetViewAngle( ) - ( angCurrentAimPunch / ( float )iNextPrimaryAttack ) );
				eng.WaitTicks( 1 );
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
