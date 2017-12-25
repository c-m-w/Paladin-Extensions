#include "../../dllmain.h"

void CHitSound::PlaySoundOnHit( )
{
	if ( plrLocalPlayer.xValue.ulHitsOnServer > ulOldHitsOnServer )
	{
		ulOldHitsOnServer = plrLocalPlayer.xValue.ulHitsOnServer;
		if ( !cfg.strHitSoundLocation.c_str( ) )
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
