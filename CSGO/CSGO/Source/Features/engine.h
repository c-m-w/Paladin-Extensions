#pragma once

class CEngine {
public:
	// engine - global
	CGlobalVars GetGlobalVars();

	// engine - clientstate
	DWORD GetClientState();
	ESignOnState GetClientStateSignOnState();

	// client - global
	EKeystroke GetForceJump();
	void ForceJump(EKeystroke);
	EKeystroke GetForceAttack();
	void ForceAttack(EKeystroke);

	float GetSensitivity();
	void SetSensitivity(float);

	// client - entities
	DWORD GetEntityBase(int);

	ETeam GetEntityTeam(int);
	bool GetEntitySpotted(int);
	void SetEntitySpotted(int, bool);

	// client - localplayer
	DWORD GetLocalPlayer();

	ETeam GetTeam();
	EMoveType GetMoveType();
	frame GetFlags();
	total GetHitsOnServer();
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
	Angle VectorToAngle(Coordinate, Coordinate);
};

extern CEngine eng;
