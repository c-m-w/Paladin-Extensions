#pragma once

class CEngine {
public:
	//engine
	DWORD GetClientState();
	ESignOnState GetClientStateSignOnState();

	//client
	EKeystroke GetForceJump();
	void ForceJump(EKeystroke);
	EKeystroke GetForceAttack();
	void ForceAttack(EKeystroke);

	float GetSensitivity();
	void SetSensitivity(float);

	DWORD GetLocalPlayer();

	frame GetLocalPlayerFlags();
	total GetLocalPlayerHitsOnServer();

	handle GetActiveWeapon();
	float GetNextPrimaryAttack();
};

extern CEngine eng;
