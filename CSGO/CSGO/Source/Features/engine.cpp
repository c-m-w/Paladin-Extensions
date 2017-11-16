#include "engine.h"

Engine eng;

void Engine::Jump(int kType) {
	ksForceJump = kType;
	mem.Write(ksForceJump);
}

void Engine::Attack(int kType) {
	ksForceAttack = kType;
	mem.Write(ksForceAttack);
}

float Engine::GetSensitivity() {
	mem.Read(fSensitivity);
	return fSensitivity.val;
}

void Engine::SetSensitivity(float fSensitivityNew) {
	fSensitivity = fSensitivityNew;
	mem.Write(fSensitivity);
}
