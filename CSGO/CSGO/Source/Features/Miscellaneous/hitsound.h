#pragma once

class CHitSound
{
	unsigned int uiOldHitsOnServer = 0;
public:
	void PlaySoundOnHit( );
};

extern CHitSound hit;
