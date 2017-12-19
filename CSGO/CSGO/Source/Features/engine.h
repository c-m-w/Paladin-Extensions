#pragma once

class CEngine
{
public:
	// engine - global
	CGlobalVars GetGlobalVars( );
	void SetGlobalVars( CGlobalVars ); // careful! unlimited

	// engine - clientstate
	DWORD GetClientState( );
	ESignOnState GetSignOnState( );
	angle_t GetViewAngle( );
	void SetViewAngle( angle_t ); // sets view angles automatically normalized and clamped

	// client - global
	flag GetAttack( );
	void SetAttack( flag );
	flag GetJump( );
	void SetJump( flag );
	float GetSensitivity( );
	void SetSensitivity( float ); // sets sensitivity limited to 0 and 1000

	// client - entities
	DWORD GetEntityBase( int );

	ETeam GetEntityTeam( int );
	bool GetEntityDormancy( int );
	bool GetEntitySpottedState( int );
	void SetEntitySpottedState( int, bool );
	coordinate_t GetEntityOrigin(int);

	// client - localplayer
	DWORD GetLocalPlayer( );

	ETeam GetTeam( );
	flag GetFlags( );
	EMoveType GetMoveType( );
	angle_t GetAimPunch( );
	int GetFieldOfView( );
	void SetFieldOfView( int ); // sets field of view limited to 0 and 180
	int GetShotsFired( );
	total GetHitsOnServer( );
	float GetFlashMaxAlpha( );
	void SetFlashMaxAlpha( float ); // sets max flash limited to 0 and 255

	handle GetActiveWeaponHandle( );
	int GetActiveWeaponZoomLevel( );
	float GetNextPrimaryAttack( );
	EWeapon GetActiveWeaponIndex( );

	// general
	float GetPixelToAngleYAW( );
	float GetPixelToAnglePITCH( );
	angle_t ClampAngle( angle_t ); // clamps angles to 89, 180, and 50
	angle_t NormalizeAngle( angle_t ); // sets angle to sensitivity, limits delta to 22 degrees
	angle_t VectorToAngle( coordinate_t, coordinate_t );
};

extern CEngine eng;
