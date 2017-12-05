#include "../main.h"

void CEngine::Jump(EKeystroke ksType) {
	ksForceJump.val = ksType;
	mem.Write(ksForceJump);
}

void CEngine::Attack(EKeystroke ksType) {
	ksForceAttack.val = ksType;
	mem.Write(ksForceAttack);
}

float CEngine::GetSensitivity() {
	mem.Read(flSensitivity);
	return flSensitivity.val;
}

void CEngine::SetSensitivity(float flSensitivityNew) {
	flSensitivity.val = flSensitivityNew;
	mem.Write(flSensitivity);
}

CEngine eng;
