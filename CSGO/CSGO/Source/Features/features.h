#pragma once
enum Keystroke {
	RELEASE = 4,
	PRESS = 5,
	SCROLL = 6
};
void Jump(const Keystroke ksType);
void Attack(const Keystroke ksType);
float GetSensitivity();
void SetSensitivity(const float fSensitivity);