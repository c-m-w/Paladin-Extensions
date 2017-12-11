#pragma once

class CEngine {
public:
	// engine - global
	CGlobalVars GetGlobalVars();

	// engine - clientstate
	DWORD GetClientState();
	ESignOnState GetSignOnState();
	Angle GetViewAngle();
	void SetViewAngle(Angle);

	// client - global
	EKeystroke GetForceAttack();
	void ForceAttack(EKeystroke);
	EKeystroke GetForceJump();
	void ForceJump(EKeystroke);
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
	frame GetFlags();
	EMoveType GetMoveType();
	Angle GetAimPunch();
	int GetFieldOfView();
	void SetFieldOfView(int);
	total GetHitsOnServer();
	float GetFlashMaxAlpha();
	void SetFlashMaxAlpha(float);

	handle GetActiveWeaponHandle();
	DWORD GetActiveWeaponEntity();
	float GetNextPrimaryAttack();

	// general
	void WaitTicks(int);
	Angle ClampAngle(Angle);
	Angle NormalizeAngle(Angle);
	Angle VectorToAngle(Coordinate, Coordinate);
};

extern CEngine eng;
