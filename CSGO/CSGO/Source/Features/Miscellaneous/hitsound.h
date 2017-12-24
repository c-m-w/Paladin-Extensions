#pragma once

class CHitSound
{
	unsigned long ulOldHitsOnServer = 0;
public:
	void PlaySoundOnHit( );
};

extern CHitSound hit;
