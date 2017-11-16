#pragma once
#include "../main.h"

class Engine {
public:
	void Jump(int ksType);
	void Attack(int ksType);
	float GetSensitivity();
	void SetSensitivity(float fSensitivity);
};

extern Engine eng;
