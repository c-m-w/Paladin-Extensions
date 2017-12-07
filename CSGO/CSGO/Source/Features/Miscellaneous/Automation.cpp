#include "../../main.h"

void CAutomation::AutoJump() {
	if (eng.GetForceJump() == EKeystroke::PRESS) {
		eng.ForceJump(EKeystroke::RELEASE);
	}
	if (eng.GetLocalPlayerFlags() & FL_ONGROUND) {
		eng.ForceJump(EKeystroke::SCROLL);
	}
}

CAutomation aut;
