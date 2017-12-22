#pragma once

class CHitSound
{
	unsigned int totalOldHitsOnServer = 0;
public:
	void PlaySoundOnHit( );
};

extern CHitSound hit;
