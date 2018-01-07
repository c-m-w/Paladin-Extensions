#include "../../dllmain.h"

void CHitSound::PlaySoundOnHit( )
{
	if ( plrLocalPlayer.xValue._My_val.ulHitsOnServer > ulOldHitsOnServer )
	{
		ulOldHitsOnServer = plrLocalPlayer.xValue._My_val.ulHitsOnServer;
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
