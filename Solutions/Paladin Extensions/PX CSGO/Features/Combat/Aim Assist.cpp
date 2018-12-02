/// Aim Assist.cpp

#include "PX Precompiled.hpp"
#include "../../PX CSGO.hpp"

using namespace PX;
using namespace Information;
using namespace Pointers;
using namespace Tools;

namespace PX::Features::Combat
{
	auto _Config = &_Settings._Combat._Aim._All;
	auto _RecoilControlConfig = &_Settings._Combat._RecoilCompensation._All;
	/** \brief Holds information about the target. */
	struct
	{
		/** \brief Entity index of the target.\n
					More definite than the target's address. */
		int iEntityIndex = -1;
		/** \brief Target's address. */
		player_ptr_t pTarget = nullptr;
		/** \brief Hitbox to aim at.\n
					Decided when a new target is first selected. */
		int iHitbox = 0;
		/** \brief The amount to aim each time AimAssist is called.\n
					Used for slow aim with a constant factor.\n
					Value is calculated when the target is first selected. */
		QAngle qOldAngles { };
		QAngle qTargetAngle { };
		Vector vecStartPos { }, vecAimVelocity { }, vecAimAcceleration { }, vecTargetAngle { }, vecCurrentAngle { }, vecAimAngle { };
		float flOldForward = 0.f, flOldSide = 0.f, flOldUp = 0.f;
		bool bRestoreAngle = false;
		float flBezierAcceleration = 0.f, flBezierVelocity = 0.f, flBezierRatio = 0.f;
		bool bResetBezierOrigin = true;
		Vector vecOverCompensation { };
	} _AimContext;
	const decltype( _AimContext ) DEFAULT;

	/** \brief Finds a target to aim at. */
	/** \param pLocalPlayer Pointer to the local player. */
	/** \param pCmd User commands of the local player. */
	/** \return Pointer to player to aim at.\n
				 nullptr is returned if no target was found. */
	player_ptr_t PX_API FindTarget( player_ptr_t pLocalPlayer, CUserCmd* pCmd );
	int PX_API FindHitbox( player_ptr_t pLocalPlayer, player_ptr_t pTarget, CUserCmd* pCmd );
	bool PX_API ValidateTarget( player_ptr_t pLocalPlayer, player_ptr_t pTarget, CUserCmd* pCmd );
	void PX_API ResetAimPosition( player_ptr_t pLocalPlayer, CUserCmd* pCmd );
	void PX_API ResetContext( );
	void PX_API OnNewTarget( player_ptr_t pLocalPlayer, player_ptr_t pTarget, CUserCmd* pCmd );

	void PX_API CorrectMovement( QAngle qOldAngles, CUserCmd* pCmd, float flOldForward, float flOldSide )
	{
		float flDelta;
		float f1;
		float f2;

		if ( qOldAngles.yaw < 0.f )
			f1 = 360.f + qOldAngles.yaw;
		else
			f1 = qOldAngles.yaw;

		if ( pCmd->viewangles.yaw < 0.0f )
			f2 = 360.f + pCmd->viewangles.yaw;
		else
			f2 = pCmd->viewangles.yaw;

		if ( f2 < f1 )
			flDelta = fabsf( f2 - f1 );
		else
			flDelta = 360.f - fabsf( f1 - f2 );

		flDelta = 360.f - flDelta;

		pCmd->forwardmove = cos( D3DXToRadian( flDelta ) ) * flOldForward + cos( D3DXToRadian( flDelta + 90.f ) ) * flOldSide;
		pCmd->sidemove = sin( D3DXToRadian( flDelta ) ) * flOldForward + sin( D3DXToRadian( flDelta + 90.f ) ) * flOldSide;
	}

	void PX_API AimAssist( player_ptr_t pLocalPlayer, CUserCmd* pCmd )
	{
		static bool* pLast = nullptr;
		static auto bReleasedKey = true;

		if ( !pLocalPlayer->IsAlive( ) )
			return ResetContext( );

		const auto hWeapon = pLocalPlayer->m_hActiveWeapon( );
		if ( !hWeapon )
			return ResetContext( );
		if ( pLast != nullptr && !*pLast )
			bReleasedKey = true;

		//PX_GET_WEAPON_CONFIG( hWeapon, _Config, _Settings._Combat._Aim );
		//_RecoilControlConfig = _Settings._Combat._RecoilCompensation._IndividualWeapons[ def_index ].bUseSeparate.Get( ) ? &_Settings._Combat._RecoilCompensation._IndividualWeapons[ def_index ] : _Settings._Combat._RecoilCompensation._WeaponTypes[ wep_type ].bUseSeparate.Get( ) ? &_Settings._Combat._RecoilCompensation._WeaponTypes[ wep_type ] : &_Settings._Combat._RecoilCompensation._All;;

		player_ptr_t pTarget = nullptr;
		if ( _Config->bStaticTarget.Get( ) )
		{
			if ( _AimContext.iEntityIndex != -1 )
			{
				pTarget = player_ptr_t( pEntityList->GetClientEntity( _AimContext.iEntityIndex ) );
				if ( !pTarget->IsAlive( ) )
				{
					_AimContext.iEntityIndex = -1;
					return;
				}

				if ( !ValidateTarget( pLocalPlayer, pTarget, pCmd ) )
				{
					if ( _Config->bValidateTarget.Get( ) && !bReleasedKey )
						return;
				}
				else if ( bReleasedKey )
					pTarget = FindTarget( pLocalPlayer, pCmd );
			}
			else if ( bReleasedKey )
				pTarget = FindTarget( pLocalPlayer, pCmd );
			else
				return;
		}
		else
			pTarget = FindTarget( pLocalPlayer, pCmd );

		if ( nullptr == pTarget )
			return ResetContext( );

		pLast = &( pTarget->m_iTeamNum( ) == pLocalPlayer->m_iTeamNum( ) ? _Config->bTeammates.Get( ) : _Config->bEnemies.Get( ) );
		if ( !*pLast )
		{
			bReleasedKey = true;
			return ResetContext( );
		}
		bReleasedKey = false;

		if ( _AimContext.iEntityIndex != pTarget->EntIndex( ) )
			OnNewTarget( pLocalPlayer, pTarget, pCmd );
		if ( _AimContext.iHitbox == -1 )
			return ResetContext( );

		auto qTargetAngle = CalculateAngle( pLocalPlayer, pTarget, _AimContext.iHitbox, pCmd, &_AimContext.vecOverCompensation );
		ClampAngles( qTargetAngle );
		ResetAimPosition( pLocalPlayer, pCmd );
		switch ( _Config->iAimType )
		{
			case AIMTYPE_DEFAULT:
			{
				pClientState->viewangles = { qTargetAngle.pitch, qTargetAngle.yaw, pClientState->viewangles.z };
			}
			break;

			case AIMTYPE_SMOOTH:
			{
				//auto vecRelativeSmoothedAngles = _AimContext.vecCurrentAngle - ( _AimContext.vecCurrentAngle - _AimContext.vecTargetAngle ) / _Config->flSmoothFactor;
				Vector vecNewAngles;

				switch ( _Config->iSmoothMode )
				{
					case SMOOTH_LINEAR:
					{
						ClampAngles( _AimContext.vecAimAngle );
						pClientState->viewangles = _AimContext.vecAimAngle;
					}
					break;

					case SMOOTH_PARABOLIC:
					{
						const auto flTemp = ( _AimContext.vecStartPos.x - _AimContext.vecTargetAngle.x ) / powf( _AimContext.vecStartPos.y - _AimContext.vecTargetAngle.y, 2.f );
						vecNewAngles.y = _AimContext.vecAimAngle.y;
						vecNewAngles.x = flTemp * powf( vecNewAngles.y - _AimContext.vecTargetAngle.y, 2.f ) + _AimContext.vecTargetAngle.x;
						vecNewAngles.z = _AimContext.vecAimAngle.z;
						ClampAngles( vecNewAngles );
						pClientState->viewangles = vecNewAngles;
					}
					break;

					case SMOOTH_RADICAL:
					{
						const auto flTemp = ( _AimContext.vecStartPos.x - _AimContext.vecTargetAngle.x ) / cbrtf( _AimContext.vecStartPos.y - _AimContext.vecTargetAngle.y );
						vecNewAngles.y = _AimContext.vecAimAngle.y;
						vecNewAngles.x = flTemp * cbrtf( _AimContext.vecAimAngle.y - _AimContext.vecTargetAngle.y ) + _AimContext.vecTargetAngle.x;
						vecNewAngles.z = _AimContext.vecAimAngle.z;
						ClampAngles( vecNewAngles );
						pClientState->viewangles = vecNewAngles;
					}
					break;

					case SMOOTH_SINUSOIDAL:
					{
						const auto flMultiplier = D3DX_PI / 2.f / ( vecNewAngles.x - _AimContext.vecTargetAngle.x );
						const auto flTemp = ( _AimContext.vecTargetAngle.y - _AimContext.vecCurrentAngle.y ) / sinf( flMultiplier * ( _AimContext.vecTargetAngle.x - vecNewAngles.x ) );
						vecNewAngles.x = _AimContext.vecAimAngle.x;
						vecNewAngles.y = flTemp * sinf( flMultiplier * ( vecNewAngles.x - _AimContext.vecCurrentAngle.x ) ) + _AimContext.vecCurrentAngle.y;
						vecNewAngles.z = _AimContext.vecCurrentAngle.z;
						ClampAngles( vecNewAngles );
						pClientState->viewangles = vecNewAngles;
					}
					break;

					case SMOOTH_BEZIER:
					{
						const auto vecBezierPoints = GetBezierPoints( _AimContext.vecStartPos, _AimContext.vecTargetAngle, _Config->_BezierOrders, _Config->iCurrentOrders + 1 );
						const auto vecPoint = GetBezierPoint( vecBezierPoints, _AimContext.flBezierRatio );
						
						vecNewAngles = vecPoint;
						vecNewAngles.z = _AimContext.vecTargetAngle.z;
						ClampAngles( vecNewAngles );
						pClientState->viewangles = vecNewAngles;
					}
					break;

					default:
					{
						return;
					}
				}
			}
			break;

			case AIMTYPE_SILENT:
			{
				const auto fnDoSilent = [ & ]( )
				{
					_AimContext.qOldAngles = pCmd->viewangles;
					_AimContext.flOldForward = pCmd->forwardmove;
					_AimContext.flOldSide = pCmd->sidemove;
					_AimContext.flOldUp = pCmd->upmove;
					pCmd->viewangles = { qTargetAngle.pitch, qTargetAngle.yaw, pCmd->viewangles.roll };
					_AimContext.bRestoreAngle = true;
					CorrectMovement( _AimContext.qOldAngles, pCmd, _AimContext.flOldForward, _AimContext.flOldSide );
				};

				const auto fnRestore = [ & ]( )
				{
					pCmd->viewangles = _AimContext.qOldAngles;
					pCmd->forwardmove = _AimContext.flOldForward;
					pCmd->sidemove = _AimContext.flOldSide;
					pCmd->upmove = _AimContext.flOldUp;
					_AimContext.bRestoreAngle = false;
				};

				if ( _AimContext.bRestoreAngle )
					fnRestore( ); // restore angle
				else if ( hWeapon->CanFire( ) ) // if we should restore and can fire
				{
					if ( pCmd->buttons & IN_ATTACK ) // if were already attacking, attack
						fnDoSilent( );
					else
					{
						fnDoSilent( );							// set viewangles and see if triggerbot will shoot,
						Trigger( pLocalPlayer, pCmd );			// if it doesn't, restore the angles.
						if ( !( pCmd->buttons & IN_ATTACK ) )
							fnRestore( );
					}
				}
			}
			break;

			default:
			{
				return;
			}
		}
	}

	player_ptr_t PX_API FindTarget( player_ptr_t pLocalPlayer, CUserCmd* pCmd )
	{
		auto flClosestDistance = FLT_MAX;
		auto iLowestHealth = INT_MAX;
		player_ptr_t pEntity = nullptr;

		for ( auto i = 0; i < pGlobalVariables->m_iMaxClients; i++ )
		{
			const auto pCurrentEntity = player_ptr_t( pEntityList->GetClientEntity( i ) );
			if ( pCurrentEntity == nullptr
				 || pCurrentEntity == pLocalPlayer
				 || !pCurrentEntity->IsPlayer( )
				 || !pCurrentEntity->IsAlive( )
				 || pCurrentEntity->m_bGunGameImmunity( )
				 || !pLocalPlayer->CanSeePlayer( pCurrentEntity, _Config->bMindSmoke.Get( ) ) )
				continue;

			const auto flCrosshairDistance = CalculateCrosshairDistance( pLocalPlayer, pCurrentEntity, _Config->iReferenceHitbox, pCmd, _Config->bWorldlyCrosshairDistance.Get( ) );
			if ( flCrosshairDistance > _Config->flMaxCrosshairDistance )
				continue;

			switch ( _Config->iTargeting )
			{
				case TARGETING_DISTANCE:
				{
					const auto flCurrentDistance = pLocalPlayer->DistanceFromPlayer( pCurrentEntity );
					if ( flCurrentDistance < flClosestDistance )
					{
						flClosestDistance = flCurrentDistance;
						pEntity = pCurrentEntity;
					}
				}
				break;

				case TARGETING_CROSSHAIR_DISTANCE:
				{
					if ( flCrosshairDistance < flClosestDistance )
					{
						flClosestDistance = flCrosshairDistance;
						pEntity = pCurrentEntity;
					}
				}
				break;

				case TARGETING_LOWEST_HEALTH:
				{
					if ( pCurrentEntity->m_iHealth( ) < iLowestHealth )
					{
						iLowestHealth = pCurrentEntity->m_iHealth( );
						pEntity = pCurrentEntity;
					}
				}
				break;

				default:
				{
					return pEntity;
				}
			}
		}
		return pEntity;
	}

	int PX_API FindHitbox( player_ptr_t pLocalPlayer, player_ptr_t pTarget, CUserCmd* pCmd )
	{
		auto flClosestHitboxDistance = FLT_MAX;
		auto iClosestHitbox = -1;

		for ( int i = HITBOX_HEAD; i < HITBOX_MAX; i++ )
		{
			if ( !_Config->bHitboxes[ i ] )
				continue;

			const auto flCurrentDistance = CalculateCrosshairDistance( pLocalPlayer, pTarget, i, pCmd, _Config->bWorldlyCrosshairDistance.Get( ) );
			if ( flCurrentDistance > _Config->flMaxCrosshairDistance )
				continue;

			if ( i == _Config->iPriorityHitbox )
				return i;

			if ( flCurrentDistance < flClosestHitboxDistance )
			{
				iClosestHitbox = i;
				flClosestHitboxDistance = flCurrentDistance;
			}
		}
		return iClosestHitbox;
	}

	bool PX_API ValidateTarget( player_ptr_t pLocalPlayer, player_ptr_t pTarget, CUserCmd* pCmd )
	{
		if ( _AimContext.iHitbox != -1 )
			if ( CalculateCrosshairDistance( pLocalPlayer, pTarget, _AimContext.iHitbox, pCmd, _Config->bWorldlyCrosshairDistance.Get( ) ) )
				return true;
		return -1 != ( _AimContext.iHitbox = FindHitbox( pLocalPlayer, pTarget, pCmd ) );
	}

	void PX_API ResetAimPosition( player_ptr_t pLocalPlayer, CUserCmd* pCmd )
	{
		constexpr auto fnGetAcceleration = [ ]( float flFirst, float flSecond, float flVelocity, float flTime, float flFactor )
		{
			const auto flDistance = flFirst - flSecond;
			if ( flDistance == 0.f )
				return 0.f;

			const auto flFinalVelocity = flVelocity * ( 1.f + flFactor );
			const auto flAcceleration = ( powf( flFinalVelocity, 2.f ) - powf( flVelocity, 2.f ) ) / ( 2.f * flDistance );
			return flAcceleration;
		};

		_AimContext.vecCurrentAngle = pClientState->viewangles;
		_AimContext.vecTargetAngle = Vector( _AimContext.qTargetAngle.pitch, _AimContext.qTargetAngle.yaw, _AimContext.qTargetAngle.roll );

		auto& gtRay = pLocalPlayer->TraceRayFromAngle( _AimContext.qTargetAngle );
		if ( gtRay.hit_entity != nullptr
			 && gtRay.hit_entity->EntIndex( ) == _AimContext.iEntityIndex
			 && gtRay.hitbox == _AimContext.iHitbox )
		{
			if ( _AimContext.vecAimAngle != _AimContext.vecTargetAngle )
			{
				_AimContext.vecAimVelocity += _AimContext.vecAimAcceleration * pGlobalVariables->m_flIntervalPerTick;

				if ( ( _AimContext.vecAimAngle - _AimContext.vecTargetAngle ).Absolute( ) <= ( _AimContext.vecAimVelocity * pGlobalVariables->m_flIntervalPerTick ).Absolute( ) )
				{
					_AimContext.vecAimAngle = _AimContext.vecTargetAngle;
					_AimContext.vecAimAcceleration.Zero( );
					_AimContext.vecAimVelocity.Zero( );
				}
				else
					_AimContext.vecAimAngle -= _AimContext.vecAimVelocity * pGlobalVariables->m_flIntervalPerTick;
			}

			if( _AimContext.flBezierRatio != 1.f )
			{
				_AimContext.flBezierVelocity += _AimContext.flBezierAcceleration * pGlobalVariables->m_flIntervalPerTick;

				if ( _AimContext.flBezierRatio + _AimContext.flBezierVelocity * pGlobalVariables->m_flIntervalPerTick >= 1.f )
				{
					_AimContext.flBezierRatio = 1.f;
					_AimContext.flBezierVelocity = _AimContext.flBezierAcceleration = 0.f;
				}
				else
					_AimContext.flBezierRatio += _AimContext.flBezierVelocity * pGlobalVariables->m_flIntervalPerTick;
			}

			return;
		}

		_AimContext.vecStartPos = _AimContext.vecCurrentAngle;
		_AimContext.qTargetAngle = CalculateAngle( pLocalPlayer, _AimContext.pTarget, _AimContext.iHitbox, pCmd, &_AimContext.vecOverCompensation );
		ClampAngles( _AimContext.qTargetAngle );
		_AimContext.vecTargetAngle = Vector( _AimContext.qTargetAngle.pitch, _AimContext.qTargetAngle.yaw, _AimContext.qTargetAngle.roll );

		_AimContext.vecAimVelocity = ( _AimContext.vecCurrentAngle - _AimContext.vecTargetAngle ) / _Config->flAimTime;
		_AimContext.flBezierVelocity = powf( _Config->flAimTime, -1.f );
		_AimContext.vecAimAcceleration = Vector( fnGetAcceleration( _AimContext.vecStartPos.x, _AimContext.vecTargetAngle.x, _AimContext.vecAimVelocity.x, _Config->flAimTime, _Config->flAimAcceleration ),
												 fnGetAcceleration( _AimContext.vecStartPos.y, _AimContext.vecTargetAngle.y, _AimContext.vecAimVelocity.y, _Config->flAimTime, _Config->flAimAcceleration ),
												 fnGetAcceleration( _AimContext.vecStartPos.z, _AimContext.vecTargetAngle.z, _AimContext.vecAimVelocity.z, _Config->flAimTime, _Config->flAimAcceleration ) );
		_AimContext.flBezierAcceleration = fnGetAcceleration( 1.f, 0.f, _AimContext.flBezierVelocity, _Config->flAimTime, _Config->flAimAcceleration );
		_AimContext.vecAimAngle = _AimContext.vecCurrentAngle;
	}

	void PX_API ResetContext( )
	{
		_AimContext = DEFAULT;
	}

	void PX_API OnNewTarget( player_ptr_t pLocalPlayer, player_ptr_t pNewTarget, CUserCmd* pCmd )
	{
		ResetContext( );
		if ( ( _AimContext.iHitbox = FindHitbox( pLocalPlayer, pNewTarget, pCmd ) ) == -1 )
			return;
		_AimContext.pTarget = pNewTarget;
		_AimContext.iEntityIndex = pNewTarget->EntIndex( );
		_AimContext.vecOverCompensation.x = GenerateRandomNumber( -_Config->flOverCompensation, _Config->flOverCompensation, int( pGlobalVariables->m_flRealTime * 100.f ) );
		_AimContext.vecOverCompensation.y = GenerateRandomNumber( -_Config->flOverCompensation, _Config->flOverCompensation, int( pGlobalVariables->m_flRealTime * 100.f ) );
		_AimContext.vecOverCompensation.z = GenerateRandomNumber( -_Config->flOverCompensation, _Config->flOverCompensation, int( pGlobalVariables->m_flRealTime * 100.f ) );
	}
}