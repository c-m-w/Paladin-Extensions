#pragma once

class CHitSound {
	total totalLastHits = 0;
public:
	void PlaySoundOnHit();
};

extern CHitSound hit;
