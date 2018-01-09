#include "../../dllmain.h"

void CHitSound::PlaySoundOnHit( )
{
	if ( plrLocalPlayer.xValue._My_val.uiHitsOnServer > uiOldHitsOnServer )
	{
		uiOldHitsOnServer = plrLocalPlayer.xValue._My_val.uiHitsOnServer;
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
