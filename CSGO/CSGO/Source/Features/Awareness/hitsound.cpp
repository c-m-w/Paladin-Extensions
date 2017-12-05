#include "../../main.h"

void CHitSound::PlaySoundOnHit() {
	mem.Read(lp_totalHitsOnServer);
	if (lp_totalHitsOnServer.val > totalLastHits) {
		if (cfg.strHitSoundLocation == "\0") {
			Beep(750, 100);
		} else {
			//TODO
		}
		totalLastHits = lp_totalHitsOnServer.val;
	}
}

CHitSound hit;
