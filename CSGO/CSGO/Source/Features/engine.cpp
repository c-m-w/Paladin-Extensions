#include "../main.h"

void Engine::Jump(EKeystroke ksType) {
	ksForceJump = ksType;
	mem.Write(ksForceJump);
}

void Engine::Attack(EKeystroke ksType) {
	ksForceAttack = ksType;
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

Engine eng;
