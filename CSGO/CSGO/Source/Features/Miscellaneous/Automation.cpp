#include "../../dllmain.h"

void CAutomation::AutoJump() {
	if (eng.GetFlags() & FL_ONGROUND) {
		eng.ForceJump(EKeystroke::SCROLL);
	} else {
		eng.ForceJump(EKeystroke::RELEASE);
	}
	eng.WaitTicks(1);
}

void CAutomation::AutoJumpThrow() {
	if (/*eng.GetActiveWeaponID() == Grenade*/true) {
		// TODO
		if (eng.GetForceAttack() == EKeystroke::PRESS) {
			if (!(eng.GetFlags() & FL_ONGROUND)) {
				eng.ForceAttack(EKeystroke::RELEASE);
			}
		}
	}
}

CAutomation aut;
