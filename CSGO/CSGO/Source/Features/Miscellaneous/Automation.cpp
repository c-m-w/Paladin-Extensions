#include "automation.h"

void Automation::AutoJump() {
	mem.Read(ksForceJump);
	if (ksForceJump == PRESS) {
		eng.Jump(RELEASE);
	}
	mem.Read(lp_uiFlags);
	switch (lp_uiFlags.val) {
		case 257:
		case 261:
		case 263:
			eng.Jump(SCROLL);
		default:
			Wait(1);
	}
}

Automation aut;
