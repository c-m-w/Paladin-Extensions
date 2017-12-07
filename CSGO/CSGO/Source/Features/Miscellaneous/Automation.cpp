#include "../../main.h"

void CAutomation::AutoJump() {
	eng.GetForceJump();
	if (ksForceJump.val == EKeystroke::PRESS) {
		eng.ForceJump(EKeystroke::RELEASE);
	}
	eng.GetLocalPlayerFlags();
	if (lp_fFlags.val & FL_ONGROUND) {
		eng.ForceJump(EKeystroke::SCROLL);
	}
}

CAutomation aut;
