#pragma once

class CHitSound {
	total totalPreviousHitsOnServer = 0;
public:
	void PlaySoundOnHit();
};

extern CHitSound hit;
