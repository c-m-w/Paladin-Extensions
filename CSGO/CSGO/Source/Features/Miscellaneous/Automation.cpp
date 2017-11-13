#include "../../main.h"

void Automation::AutoJump() {
	mem.Read(mem.ksForceJump);
	if (mem.ksForceJump.val == PRESS) {
		Jump(RELEASE);
	}
	mem.Read(mem.lp_iFlags);
	switch (mem.lp_iFlags.val) {
		case 257:
			Jump(SCROLL);
		case 261:
			Jump(SCROLL);
		case 263:
			Jump(SCROLL);
		default:
			Wait(1);
	}
}
