#include "../../main.h"

void Automation::AutoJump() {
	mem.Read(mem.ksForceJump);
	if (mem.ksForceJump.val == eng.PRESS) {
		eng.Jump(eng.RELEASE);
	}
	mem.Read(mem.lp_iFlags);
	switch (mem.lp_iFlags.val) {
		case 257:
			eng.Jump(eng.SCROLL);
		case 261:
			eng.Jump(eng.SCROLL);
		case 263:
			eng.Jump(eng.SCROLL);
		default:
			gbl.Wait(1);
	}
}
