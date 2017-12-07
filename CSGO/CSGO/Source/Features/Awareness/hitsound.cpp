#include "../../main.h"

void CHitSound::PlaySoundOnHit() {
	if (eng.GetLocalPlayerHitsOnServer() > totalLastHits) {
		if (cfg.strHitSoundLocation == "\0") {
			Beep(750, 100);
		} else {
			//TODO
		}
		totalLastHits = lp_totalHitsOnServer.val;
	}
}

CHitSound hit;
