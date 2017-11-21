#include "automation.h"
Automation aut;
void Automation::AutoJump() {
	mem.Read(ksForceJump);
	if (ksForceJump == Keystroke::SCROLL) {
		eng.Jump(int(Keystroke::SCROLL));
	}
	mem.Read(lp_fFlags);
	if (lp_fFlags.val & FL_ONGROUND) {
		eng.Jump(int(Keystroke::SCROLL));
	} else {
		Wait(1);
	}
}
