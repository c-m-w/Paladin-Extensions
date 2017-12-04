#pragma once

class HitSound {
	total totalLastHits = 0;
public:
	void PlaySoundOnHit();
};

extern HitSound hit;
