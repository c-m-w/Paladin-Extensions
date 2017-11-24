#pragma once
#include "../Program/memory.h"

class Engine {
public:
	void Jump(int ksType);
	void Attack(int ksType);
	float GetSensitivity();
	void SetSensitivity(float flSensitivity);
};

extern Engine eng;
