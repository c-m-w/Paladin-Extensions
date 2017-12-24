#include "main.h"

Engine *eng = nullptr;

void Engine::Jump(int kType) 
{
	Addresses::ksForceJump.val = kType;
	mem->Write(Addresses::ksForceJump);
}

void Engine::Attack(int kType)
{
	Addresses::ksForceAttack.val = kType;
	mem->Write(Addresses::ksForceAttack);
}

float Engine::GetSensitivity() 
{
	mem->Read(Addresses::flSensitivity);
	return Addresses::flSensitivity.val;
}

void Engine::SetSensitivity(float flSensitivityNew) 
{
	Addresses::flSensitivity.val = flSensitivityNew;
	mem->Write(Addresses::flSensitivity);
}
