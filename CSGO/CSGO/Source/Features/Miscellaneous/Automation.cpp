#include "../../main.h"

void Automation::AutoJump() {
	mem.Read(ksForceJump);
	if (ksForceJump == EKeystroke::PRESS) {
		eng.Jump(EKeystroke::RELEASE);
	}
	mem.Read(lp_fFlags);
	if (lp_fFlags & FL_ONGROUND) {
		eng.Jump(EKeystroke::SCROLL);
	} else {
		Wait(1);
	}
}

void Automation::AutoJumpthrow() {
}

Automation aut;