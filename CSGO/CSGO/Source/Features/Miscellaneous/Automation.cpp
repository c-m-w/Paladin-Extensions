#include "../../main.h"

void CAutomation::AutoJump() {
	mem.Read(ksForceJump);
	if (ksForceJump.val == EKeystroke::PRESS) {
		eng.Jump(EKeystroke::RELEASE);
	}
	mem.Read(lp_fFlags);
	if (lp_fFlags.val & FL_ONGROUND) {
		eng.Jump(EKeystroke::SCROLL);
	}
}

CAutomation aut;
