#include "../main.h"

void Engine::Jump(EKeystroke ksType) {
	ksForceJump.val = ksType;
	mem.Write(ksForceJump);
}

void Engine::Attack(EKeystroke ksType) {
	ksForceAttack.val = ksType;
	mem.Write(ksForceAttack);
}

float Engine::GetSensitivity() {
	mem.Read(flSensitivity);
	return flSensitivity.val;
}

void Engine::SetSensitivity(float flSensitivityNew) {
	flSensitivity.val = flSensitivityNew;
	mem.Write(flSensitivity);
}

Engine eng;
