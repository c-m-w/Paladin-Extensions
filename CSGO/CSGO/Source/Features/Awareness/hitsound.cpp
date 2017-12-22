#include "../../dllmain.h"

void CHitSound::PlaySoundOnHit( )
{
	if ( plrLocalPlayer.val.ulHitsOnServer > ulOldHitsOnServer )
	{
		ulOldHitsOnServer = plrLocalPlayer.val.ulHitsOnServer;
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
