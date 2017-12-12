#include "../../dllmain.h"

void CHitSound::PlaySoundOnHit( )
{
	if ( eng.GetHitsOnServer( ) > totalPreviousHitsOnServer )
	{
		totalPreviousHitsOnServer = lp_totalHitsOnServer.val;
		if ( cfg.strHitSoundLocation == "\0" )
		{
			Beep( 750, 100 );
		}
		else
		{
			PlaySound( cfg.strHitSoundLocation.c_str( ), nullptr, SND_SYNC );
		}
	}
	eng.WaitTicks( 1 );
}

CHitSound hit;
