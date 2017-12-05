#pragma once

class CEngine {
public:
	void Jump(EKeystroke);
	void Attack(EKeystroke);
	float GetSensitivity();
	void SetSensitivity(float);
};

extern CEngine eng;
