#include "../../dllmain.h"

void CHitSound::PlaySoundOnHit( )
{
	if ( aplrLocalPlayer.xValue.ulHitsOnServer > ulOldHitsOnServer )
	{
		ulOldHitsOnServer = aplrLocalPlayer.xValue.ulHitsOnServer;
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
