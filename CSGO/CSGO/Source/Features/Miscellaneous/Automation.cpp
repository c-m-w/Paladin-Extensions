#include "../../main.h"

void CAutomation::AutoJump() {
	eng.ForceJump(EKeystroke::RELEASE);
	eng.WaitTicks(1);
	if (eng.GetLocalPlayerFlags() & FL_ONGROUND) {
		eng.ForceJump(EKeystroke::SCROLL);
	}
}

CAutomation aut;
