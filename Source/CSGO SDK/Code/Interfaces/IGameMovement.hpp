#pragma once

#include "../Math/Vector.hpp"
#include "../Math/QAngle.hpp"
#include "../Types/CBaseHandle.hpp"
#include "IMoveHelper.hpp"

class CBasePlayer;

class CMoveData
{
public:
	bool m_bFirstRunOfFunctions : 1;
	bool m_bGameCodeMovedPlayer : 1;

	EntityHandle_t m_nPlayerHandle;	// edict index on server, client entity handle on client

	int m_nImpulseCommand;	// Impulse command issued.
	QAngle m_vecViewAngles;	// Command view angles (local space)
	QAngle m_vecAbsViewAngles;	// Command view angles (world space)
	int m_nButtons;			// Attack buttons.
	int m_nOldButtons;		// From host_client->oldbuttons;
	float m_flForwardMove;
	float m_flSideMove;
	float m_flUpMove;

	float m_flMaxSpeed;
	float m_flClientMaxSpeed;

	// Variables from the player edict (sv_player) or entvars on the client.
	// These are copied in here before calling and copied out after calling.
	Vector m_vecVelocity;		// edict::velocity		// Current movement direction.
	QAngle m_vecAngles;		// edict::angles
	QAngle m_vecOldAngles;

	// Output only
	float m_outStepHeight;	// how much you climbed this move
	Vector m_outWishVel;		// This is where you tried 
	Vector m_outJumpVel;		// This is your jump velocity

	// Movement constraints	(radius 0 means no constraint)
	Vector m_vecConstraintCenter;
	float m_flConstraintRadius;
	float m_flConstraintWidth;
	float m_flConstraintSpeedFactor;

	void SetAbsOrigin( const Vector &vec );
	const Vector &GetAbsOrigin( ) const;

private:
	Vector m_vecAbsOrigin;		// edict::origin
};

class IGameMovement
{
public:
	virtual ~IGameMovement( void )
	{ }

	virtual void ProcessMovement( void *pPlayer, void *pMove ) = 0;
	virtual void Reset( void ) = 0;
	virtual void StartTrackPredictionErrors( void *pPlayer ) = 0;
	virtual void FinishTrackPredictionErrors( void *pPlayer ) = 0;
	virtual void DiffPrint( char const *fmt, ... ) = 0;
	virtual Vector const &GetPlayerMins( bool ducked ) const = 0;
	virtual Vector const &GetPlayerMaxs( bool ducked ) const = 0;
	virtual Vector const &GetPlayerViewOffset( bool ducked ) const = 0;
	virtual bool IsMovingPlayerStuck( void ) const = 0;
	virtual void *GetMovingPlayer( void ) const = 0;
	virtual void UnblockPusher( void *pPlayer, void *pPusher ) = 0;
	virtual void SetupMovementBounds( CMoveData *pMove ) = 0;
};
