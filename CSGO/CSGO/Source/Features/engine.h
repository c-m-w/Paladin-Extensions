#pragma once

class CEngine {
public:
	//engine
	CGlobalVars GetGlobalVars();
	float GetCurTime();
	int GetMaxClients();
	int GetTickCount();
	float GetIntervalPerTick();

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

	// general
	void WaitTick();
	void WaitUntilNextTick();
};

extern CEngine eng;
