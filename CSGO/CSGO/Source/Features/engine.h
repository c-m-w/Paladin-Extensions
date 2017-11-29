#pragma once
#include "../includes.h"
#include "../Program/memory.h"

class Engine {
public:
	void Jump(EKeystroke ksType);
	void Attack(EKeystroke ksType);
	float GetSensitivity();
	void SetSensitivity(float flSensitivity);
};

extern Engine eng;
