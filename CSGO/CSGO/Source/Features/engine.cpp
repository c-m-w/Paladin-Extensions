#include "engine.h"

void Engine::Jump(const Keystroke kType) {
	mem.ksForceJump = kType;
	mem.Write(mem.ksForceJump);
}

void Engine::Attack(const Keystroke kType) {
	mem.ksForceAttack = kType;
	mem.Write(mem.ksForceAttack);
}

float Engine::GetSensitivity() {
	mem.Read(mem.fSensitivity);
	return mem.fSensitivity.val;
}

void Engine::SetSensitivity(const float fSensitivity) {
	mem.fSensitivity = fSensitivity;
	mem.Write(mem.fSensitivity);
}
