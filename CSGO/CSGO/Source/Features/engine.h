#pragma once

class CEngine {
public:
	// general
	void WaitTicks(int);
	Angle ClampAngle(Angle);
	Angle WorldToScreen(Coordinate, Coordinate);

	//engine
	CGlobalVars GetGlobalVars();

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
	float GetFlashMaxAlpha();
	void SetFlashMaxAlpha(float);

	handle GetActiveWeapon();
	int GetActiveWeaponID();
	DWORD GetActiveWeaponEntity();
	float GetNextPrimaryAttack();
};

extern CEngine eng;
