#pragma once
#include "../main.h"

class Engine {
public:
	enum Keystroke {
		RELEASE = 4,
		PRESS = 5,
		SCROLL = 6
	};

	static void Jump(const Keystroke ksType);
	static void Attack(const Keystroke ksType);
	static float GetSensitivity();
	static void SetSensitivity(const float fSensitivity);
};
extern Engine eng;
