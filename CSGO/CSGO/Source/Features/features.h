#pragma once
enum Keystroke {
	RELEASE = 4,
	PRESS = 5,
	SCROLL = 6
};
void Jump(const Keystroke kType);
void Attack(const Keystroke kType);
float GetSensitivity();
void SetSensitivity(const float fSensitivity);