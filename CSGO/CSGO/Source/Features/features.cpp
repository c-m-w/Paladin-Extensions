#include "../main.h"

void Jump(const Keystroke kType) {
	mem.uiForceJump = kType;
	mem.Write(mem.uiForceJump);
}

void Attack(const Keystroke kType) {
	mem.uiForceAttack = kType;
	mem.Write(mem.uiForceAttack);
}

float GetSensitivity() {
	mem.Read(mem.fSensitivity);
	return mem.fSensitivity.val;
}

void SetSensitivity(const float fSensitivity) {
	mem.fSensitivity.val = fSensitivity;
	mem.Write(mem.fSensitivity);
}