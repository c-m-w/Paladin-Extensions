#include "../../dllmain.h"

void CHitSound::PlaySoundOnHit( )
{
	address_t< CPlayer > plrLocalPlayerCopy = plrLocalPlayer;
	if ( plrLocalPlayerCopy.xValue.ulHitsOnServer > ulOldHitsOnServer )
	{
		ulOldHitsOnServer = plrLocalPlayerCopy.xValue.ulHitsOnServer;
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
