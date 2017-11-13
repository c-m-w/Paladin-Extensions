#include "../main.h"

void Automation::AutoJump() {
	mem.Read(mem.iForceJump);
	switch (mem.iForceJump.val) {
		case 5:
		case 6:
			mem.iForceJump = 4;
			mem.Write(mem.iForceJump);
		default:
			Wait(1);
	}
	/*
	if (mem.iForceJump.val == 5 || mem.iForceJump.val == 6) 
	{
		mem.iForceJump = 4;
		mem.Write(mem.iForceJump);
	}
	*/
	mem.Read(mem.lp_iFlags);
	switch (mem.lp_iFlags.val) {
		case 257:
		case 261:
		case 263:
			mem.iForceJump = 6;
			mem.Write(mem.iForceJump);
		default:
			Wait(1);
	}
	/*
	if (mem.lp_iFlags.val == 257 || mem.lp_iFlags.val == 261 || mem.lp_iFlags.val == 263) {
		mem.iForceJump = 6;
		mem.Write(mem.iForceJump);
	}
	*/
}
