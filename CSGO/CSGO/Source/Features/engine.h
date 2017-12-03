#pragma once

class Engine {
public:
	void Jump(EKeystroke);
	void Attack(EKeystroke);
	float GetSensitivity();
	void SetSensitivity(float);
};

extern Engine eng;
