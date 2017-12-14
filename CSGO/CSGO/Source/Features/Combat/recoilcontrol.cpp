#include "../../dllmain.h"

void CRecoilControl::RecoilControl( )
{
	if ( eng.GetShotsFired( ) > 1 && eng.GetNextPrimaryAttack( ) <= 0.f )
	{
		angle_t aCurrentAimPunch = eng.GetAimPunch( ) - aOldAimPunch;
		aCurrentAimPunch *= 2.f;
		eng.SetViewAngle( eng.GetViewAngle( ) - aCurrentAimPunch );
		aOldAimPunch = eng.GetAimPunch( );
	}
	else if ( eng.GetShotsFired( ) == 1 )
	{
		aOldAimPunch = { 0, 0, 0 };
	}
	eng.WaitTicks( 1 );
}

CRecoilControl rcs;
