#pragma once
#include "../main.h"
using namespace Addresses;
class Engine {
public:
	void Jump(Keystroke ksType);
	void Attack(Keystroke ksType);
	float GetSensitivity();
	void SetSensitivity(float fSensitivity);
};

extern Engine eng;
