#include "../../dllmain.h"

void CHitSound::PlaySoundOnHit( )
{
	address_t< CPlayer > aplrLocalPlayerCopy = aplrLocalPlayer;
	if ( aplrLocalPlayerCopy.xValue.ulHitsOnServer > ulOldHitsOnServer )
	{
		ulOldHitsOnServer = aplrLocalPlayerCopy.xValue.ulHitsOnServer;
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
