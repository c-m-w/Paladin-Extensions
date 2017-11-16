#include "automation.h"

void Automation::AutoJump() {
	mem.Read(ksForceJump);
	if (ksForceJump == PRESS) {
		eng.Jump(RELEASE);
	}
	mem.Read(lp_uiFlags);
	if (lp_uiFlags.val & FLAG_ON_GROUND) {
		eng.Jump(SCROLL);
	} else {
		Wait(1);
	}
}

Automation aut;
