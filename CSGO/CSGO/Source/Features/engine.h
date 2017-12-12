#pragma once

class CEngine
{
public:
	// engine - global
	CGlobalVars GetGlobalVars( );

	// engine - clientstate
	DWORD GetClientState( );
	ESignOnState GetSignOnState( );
	angle_t GetViewAngle( );
	void SetViewAngle( angle_t );

	// client - global
	flag GetAttack( );
	void SetAttack( flag );
	flag GetJump( );
	void SetJump( flag );
	float GetSensitivity( );
	void SetSensitivity( float );

	// client - entities
	DWORD GetEntityBase( int );

	ETeam GetEntityTeam( int );
	bool GetEntitySpotted( int );
	void SetEntitySpotted( int, bool );

	// client - localplayer
	DWORD GetLocalPlayer( );

	ETeam GetTeam( );
	flag GetFlags( );
	EMoveType GetMoveType( );
	angle_t GetAimPunch( );
	int GetFieldOfView( );
	void SetFieldOfView( int );
	total GetHitsOnServer( );
	float GetFlashMaxAlpha( );
	void SetFlashMaxAlpha( float );

	handle GetActiveWeaponHandle( );
	DWORD GetActiveWeaponEntity( );
	EWeapon GetActiveWeaponIndex( );
	float GetNextPrimaryAttack( );

	// general
	void WaitTicks( int );
	float GetPixelToAngleYAW( );
	float GetPixelToAnglePITCH( );
	angle_t ClampAngle( angle_t );
	angle_t NormalizeAngle( angle_t );
	angle_t VectorToAngle( coordinate_t, coordinate_t );
};

extern CEngine eng;
