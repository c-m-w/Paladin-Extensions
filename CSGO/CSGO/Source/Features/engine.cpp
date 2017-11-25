#include "engine.h"

Engine eng;

void Engine::Jump(Keystroke kType) {
	ksForceJump = kType;
	mem.Write(ksForceJump);
}

void Engine::Attack(Keystroke kType) {
	ksForceAttack = kType;
	mem.Write(ksForceAttack);
}

float Engine::GetSensitivity() {
	mem.Read(flSensitivity);
	return flSensitivity.val;
}

void Engine::SetSensitivity(float flSensitivityNew) {
	flSensitivity = flSensitivityNew;
	mem.Write(flSensitivity);
}
