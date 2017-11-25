#pragma once
#include "../includes.h"

class Engine {
public:
	void Jump(Keystroke ksType);
	void Attack(Keystroke ksType);
	float GetSensitivity();
	void SetSensitivity(float flSensitivity);
};

extern Engine eng;
