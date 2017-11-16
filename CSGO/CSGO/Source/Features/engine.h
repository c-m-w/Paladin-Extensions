#pragma once
#include "../main.h"

class Engine {
public:
	void Jump(Keystroke ksType);
	void Attack(Keystroke ksType);
	float GetSensitivity();
	void SetSensitivity(float fSensitivity);
};

extern Engine eng;
