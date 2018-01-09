#include "../../dllmain.h"

void CHitSound::PlaySoundOnHit( )
{
	if ( plrLocalPlayer.xValue._My_val.iHitsOnServer > iOldHitsOnServer )
	{
		iOldHitsOnServer = plrLocalPlayer.xValue._My_val.iHitsOnServer;
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
