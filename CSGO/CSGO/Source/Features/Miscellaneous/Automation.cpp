#include "automation.h"

void Automation::AutoJump() {
	mem.Read(ksForceJump);
	if (ksForceJump == PRESS) {
		eng.Jump(RELEASE);
	}
	mem.Read(lp_fFlags);
	if (lp_fFlags.val & FL_ONGROUND) {
		eng.Jump(SCROLL);
	} else {
		Wait(1);
	}
}

Automation aut;
