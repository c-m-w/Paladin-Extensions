#include "../../dllmain.h"

void CHitSound::PlaySoundOnHit( )
{
	if ( plrLocalPlayer.val.totalHitsOnServer > totalOldHitsOnServer )
	{
		totalOldHitsOnServer = plrLocalPlayer.val.totalHitsOnServer;
		if ( cfg.strHitSoundLocation == "\0" )
		{
			Beep( 750, 100 );
		}
		else
		{
			PlaySound( cfg.strHitSoundLocation.c_str( ), nullptr, SND_SYNC );
		}
	}
}

CHitSound hit;
