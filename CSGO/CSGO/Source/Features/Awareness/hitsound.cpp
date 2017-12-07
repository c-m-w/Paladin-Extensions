#include "../../main.h"

void CHitSound::PlaySoundOnHit() {
	if (eng.GetLocalPlayerHitsOnServer() > totalPreviousHitsOnServer) {
		if (cfg.strHitSoundLocation == "\0") {
			Beep(750, 100);
		} else {
			//TODO
		}
		totalPreviousHitsOnServer = lp_totalHitsOnServer.val;
	}
}

CHitSound hit;
