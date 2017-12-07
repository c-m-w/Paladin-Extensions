#include "../../main.h"

void CAutomation::AutoJump() {
	eng.ForceJump(EKeystroke::RELEASE);
	if (eng.GetLocalPlayerFlags() & FL_ONGROUND) {
		eng.ForceJump(EKeystroke::SCROLL);
	}
}

CAutomation aut;
