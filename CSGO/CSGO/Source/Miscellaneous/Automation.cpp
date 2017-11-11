#include "Automation.h"

void Automation::AutoJump() {
	mem.Read(mem.iForceJump);
	if (mem.iForceJump.val == 5 || mem.iForceJump.val == 6) {
		mem.iForceJump = 4;
		mem.Write(mem.iForceJump);
	}
	mem.Read(mem.lp_iFlags);
	if (mem.lp_iFlags.val == 257 || mem.lp_iFlags.val == 261 || mem.lp_iFlags.val == 263) {
		mem.iForceJump = 6;
		mem.Write(mem.iForceJump);
	}
}
