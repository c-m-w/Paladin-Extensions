#include "../../main.h"

void CHitSound::PlaySoundOnHit() {
	eng.GetLocalPlayerHitsOnServer();
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
