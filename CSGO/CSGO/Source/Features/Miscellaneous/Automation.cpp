#include "../../main.h"

void CAutomation::AutoJump() {
	eng.ForceJump(EKeystroke::RELEASE);
	eng.WaitTicks(1);
	if (eng.GetLocalPlayerFlags() & FL_ONGROUND) {
		eng.ForceJump(EKeystroke::SCROLL);
	}
}

void CAutomation::AutoJumpThrow() {
	if (/*eng.GetActiveWeaponID() == Grenade*/true) {
		if (eng.GetForceAttack() == EKeystroke::PRESS) {
			if (!(eng.GetLocalPlayerFlags() & FL_ONGROUND)) {
				eng.ForceAttack(EKeystroke::RELEASE);
			}
		}
	}
}

CAutomation aut;
