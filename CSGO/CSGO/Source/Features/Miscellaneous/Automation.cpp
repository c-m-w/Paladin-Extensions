#include "../../dllmain.h"

void CAutomation::AutoJump() {
	if (eng.GetFlags() & FL_ONGROUND) {
		eng.ForceJump(KS_TICK);
	} else {
		eng.ForceJump(~KS_TOGGLE);
	}
	eng.WaitTicks(1);
}

void CAutomation::AutoJumpThrow() {
	if (/*eng.GetActiveWeaponID() == Grenade*/true) {
		// TODO
		if (eng.GetForceAttack() & KS_TOGGLE) {
			if (eng.GetFlags() ^ FL_ONGROUND) {
				eng.ForceAttack(!KS_TOGGLE);
			}
		}
	}
}

CAutomation aut;
