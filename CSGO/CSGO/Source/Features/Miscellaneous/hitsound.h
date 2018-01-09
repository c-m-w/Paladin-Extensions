#pragma once

class CHitSound
{
	int iOldHitsOnServer = 0;
public:
	void PlaySoundOnHit( );
};

extern CHitSound hit;
