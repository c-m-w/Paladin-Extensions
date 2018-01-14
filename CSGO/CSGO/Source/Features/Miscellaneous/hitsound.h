#pragma once

class CHitSound
{
	int iOldHitsOnServer { };
public:
	void PlaySoundOnHit( );
};

extern CHitSound hit;
