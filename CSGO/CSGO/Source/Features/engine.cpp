#include "../main.h"

void Jump(const Keystroke kType) {
	mem.ksForceJump = kType;
	mem.Write(mem.ksForceJump);
}

void Attack(const Keystroke kType) {
	mem.ksForceAttack = kType;
	mem.Write(mem.ksForceAttack);
}

float GetSensitivity() {
	mem.Read(mem.fSensitivity);
	return mem.fSensitivity.val;
}

void SetSensitivity(const float fSensitivity) {
	mem.fSensitivity.val = fSensitivity;
	mem.Write(mem.fSensitivity);
}
