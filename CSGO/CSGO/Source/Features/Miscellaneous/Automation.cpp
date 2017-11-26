#include "automation.h"

Automation aut;

void Automation::AutoJump() {
	mem.Read(ksForceJump);
	if (ksForceJump == Keystroke::PRESS) {
		eng.Jump(Keystroke::RELEASE);
	}
	mem.Read(lp_fFlags);
	if (lp_fFlags & FL_ONGROUND) {
		eng.Jump(Keystroke::SCROLL);
	} else {
		Wait(1);
	}
}

void Automation::AutoJumpthrow() {
	//alternative auto jump throw based on no key type, only if nade is out TODO
	mem.Read(ksForceAttack);
	if (ksForceAttack == Keystroke::RELEASE) {
		eng.Attack(Keystroke::PRESS);
	}
	mem.Read(lp_fFlags);
	if (!(lp_fFlags & FL_ONGROUND)) {
		eng.Attack(Keystroke::RELEASE);
	} else {
		Wait(1);
	}
}
