#include "automation.h"

Automation aut;

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
	//alternative auto jump throw based on no key type, only if nade is out TODO
	mem.Read(ksForceAttack);
	if (ksForceAttack == EKeystroke::RELEASE) {
		eng.Attack(EKeystroke::PRESS);
	}
	mem.Read(lp_fFlags);
	if (!(lp_fFlags & FL_ONGROUND)) {
		eng.Attack(EKeystroke::RELEASE);
	} else {
		Wait(1);
	}
}
