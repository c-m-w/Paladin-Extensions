/// Aim Assist.cpp

#include "PX Precompiled.hpp"
#include "../../PX CSGO.hpp"

using namespace PX;
using namespace Information;
using namespace Pointers;
using namespace Tools;

namespace PX::Features::Combat
{
	auto& _Config = _Settings._Combat._Aim._All;
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
		float flOldForward = 0.f, flOldSide = 0.f, flOldUp = 0.f;
		bool bRestoreAngle = false;
	} _AimContext;
	const decltype( _AimContext ) DEFAULT;

	/** \brief Finds a target to aim at. */
	/** \param pLocalPlayer Pointer to the local player. */
	/** \param pCmd User commands of the local player. */
	/** \return Pointer to player to aim at.\n
				 nullptr is returned if no target was found. */
	player_ptr_t PX_API FindTarget( player_ptr_t pLocalPlayer, CUserCmd* pCmd );
	int PX_API FindHitbox( player_ptr_t pLocalPlayer, player_ptr_t pTarget, CUserCmd* pCmd );
	void PX_API OnNewTarget( player_ptr_t pLocalPlayer, player_ptr_t pTarget, CUserCmd* pCmd );

	void PX_API AimAssist( player_ptr_t pLocalPlayer, CUserCmd* pCmd )
	{
		if ( !pLocalPlayer->IsAlive( ) )
			return;

		const auto hWeapon = pLocalPlayer->m_hActiveWeapon( );
		if ( !hWeapon )
			return;

		const auto pTarget = FindTarget( pLocalPlayer, pCmd );
		if ( nullptr == pTarget
			 || !( pTarget->m_iTeamNum( ) == pLocalPlayer->m_iTeamNum( ) ? _Config.bTeammates : _Config.bEnemies ) )
			return;

		if ( _AimContext.iEntityIndex != pTarget->EntIndex( ) )
			OnNewTarget( pLocalPlayer, pTarget, pCmd );
		if ( _AimContext.iHitbox == -1 )
			return;

		auto qTargetAngle = CalculateAngle( pLocalPlayer, pTarget, _AimContext.iHitbox, pCmd, false );
		ClampAngles( qTargetAngle );
		switch( _Config.iAimType )
		{
			case AIMTYPE_DEFAULT:
			{
				pClientState->viewangles = { qTargetAngle.pitch, qTargetAngle.yaw, qTargetAngle.roll };
			}
			break;

			case AIMTYPE_SMOOTH:
			{
				switch( _Config.iSmoothMode )
				{
					case SMOOTH_LINEAR:
					{
						auto vecTemp = pClientState->viewangles, vecTemp2 = Vector( qTargetAngle.pitch, qTargetAngle.yaw, qTargetAngle.roll );
						if( fabsf( vecTemp.y ) > 90.f && fabsf( vecTemp2.y ) > 90.f )
						{
							if ( vecTemp.y < 0.f )
								vecTemp.y += 360.f;
							if ( vecTemp2.y < 0.f )
								vecTemp2.y += 360.f;
						}

						auto vecNewAngles = pClientState->viewangles - ( vecTemp - vecTemp2 ) / _Config.flSmoothFactor;
						ClampAngles( vecNewAngles );
						pClientState->viewangles = vecNewAngles;
					}

					default:
					{
						return;
					}
				}
			}

			case AIMTYPE_SILENT:
			{
				const auto fnDoSilent = [ & ]( )
				{
					_AimContext.qOldAngles = pCmd->viewangles;
					_AimContext.flOldForward = pCmd->forwardmove;
					_AimContext.flOldSide = pCmd->sidemove;
					_AimContext.flOldUp = pCmd->upmove;
					pCmd->viewangles = qTargetAngle;
					_AimContext.bRestoreAngle = true;
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
				 || !pLocalPlayer->CanSeePlayer( pCurrentEntity, _Config.bMindSmoke.Get( ) ) )
				continue;

			auto flCrosshairDistance = CalculateCrosshairDistance( pLocalPlayer, pCurrentEntity, _Config.iReferenceHitbox, pCmd, _Config.bWorldlyCrosshairDistance.Get( ) );
			if ( flCrosshairDistance > 254.558441227f )
				flCrosshairDistance = fabsf( flCrosshairDistance -= 360.f );
			if ( flCrosshairDistance > _Config.flMaxCrosshairDistance )
				continue;

			switch( _Config.iTargeting )
			{
				case TARGETING_DISTANCE:
				{
					const auto flCurrentDistance = pLocalPlayer->DistanceFromPlayer( pCurrentEntity );
					if( flCurrentDistance < flClosestDistance )
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
					if( pCurrentEntity->m_iHealth(  ) < iLowestHealth )
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

		for( int i = HITBOX_HEAD; i < HITBOX_MAX; i++ )
		{
			if ( !_Config.bHitboxes[ i ] )
				continue;

			const auto flCurrentDistance = CalculateCrosshairDistance( pLocalPlayer, pTarget, i, pCmd, _Config.bWorldlyCrosshairDistance.Get( ) );
			if ( flCurrentDistance > _Config.flMaxCrosshairDistance )
				continue;

			if ( i == _Config.iPriorityHitbox )
				return i;

			if( flCurrentDistance < flClosestHitboxDistance )
			{
				iClosestHitbox = i;
				flClosestHitboxDistance = flCurrentDistance;
			}
		}
		return iClosestHitbox;
	}

	void PX_API OnNewTarget( player_ptr_t pLocalPlayer, player_ptr_t pNewTarget, CUserCmd* pCmd )
	{
		_AimContext = DEFAULT;
		if ( ( _AimContext.iHitbox = FindHitbox( pLocalPlayer, pNewTarget, pCmd ) ) == -1 )
			return;
		_AimContext.pTarget = pNewTarget;
		_AimContext.iEntityIndex = pNewTarget->EntIndex( );
	}
}
