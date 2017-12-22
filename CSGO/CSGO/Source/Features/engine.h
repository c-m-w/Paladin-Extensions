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
	FLAG GetAttack( );
	void SetAttack( FLAG );
	FLAG GetJump( );
	void SetJump( FLAG );
	float GetSensitivity( );
	void SetSensitivity( float ); // sets sensitivity limited to 0 and 1000

	// client - entities
	DWORD GetEntityBase( unsigned long );
	CPlayer GetEntity( unsigned long );
	void GetEntities( );
	void SetEntity( unsigned long, CPlayer );

	// client - localplayer
	DWORD GetLocalPlayerBase( );
	CPlayer GetLocalPlayer( );
	void SetLocalPlayer( );

	// general
	float GetPixelToAngleYAW( );
	float GetPixelToAnglePITCH( );
	angle_t ClampAngle( angle_t ); // clamps angles to 89, 180, and 50
	angle_t NormalizeAngle( angle_t ); // sets angle to sensitivity, limits delta to 22 degrees
	angle_t VectorToAngle( coordinate_t, coordinate_t );
};

extern CEngine eng;
