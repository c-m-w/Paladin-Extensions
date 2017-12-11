#pragma once

class CEngine {
public:
	// engine - global
	GlobalVars GetGlobalVars();

	// engine - clientstate
	DWORD GetClientState();
	ESignOnState GetSignOnState();
	angle GetViewAngle();
	void SetViewAngle(angle);

	// client - global
	frame GetForceAttack();
	void ForceAttack(frame);
	frame GetForceJump();
	void ForceJump(frame);
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
	angle GetAimPunch();
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
	angle ClampAngle(angle);
	angle NormalizeAngle(angle);
	angle VectorToAngle(coordinate, coordinate);
};

extern CEngine eng;
