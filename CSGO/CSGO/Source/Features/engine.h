#pragma once

class CEngine {
public:
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
	int GetFieldOfView();
	void SetFieldOfView(int);

	handle GetActiveWeaponHandle();
	DWORD GetActiveWeaponEntity();
	float GetNextPrimaryAttack();

	// general
	void WaitTicks(int);
	Angle ClampAngle(Angle);
	Angle WorldToScreen(Coordinate, Coordinate);
};

extern CEngine eng;
