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
		float flBezierRatio = 0.f;
		bool bResetBezierOrigin = true;
		Vector vecBezierOrigin { }, vecBezierEnd { };
	} _AimContext;
	const decltype( _AimContext ) DEFAULT;

	struct
	{
		std::atomic< std::pair< vertex_t, vertex_t >* > pLines = nullptr;
		std::atomic< std::size_t > zLines = 0u;

		std::atomic< vertex_t* > pPoints = nullptr;
		std::atomic< std::size_t > zPoints = 0u;
	} _AimPath;

	/** \brief Finds a target to aim at. */
	/** \param pLocalPlayer Pointer to the local player. */
	/** \param pCmd User commands of the local player. */
	/** \return Pointer to player to aim at.\n
				 nullptr is returned if no target was found. */
	player_ptr_t PX_API FindTarget( player_ptr_t pLocalPlayer, CUserCmd* pCmd );
	int PX_API FindHitbox( player_ptr_t pLocalPlayer, player_ptr_t pTarget, CUserCmd* pCmd );
	bool PX_API ValidateTarget( player_ptr_t pLocalPlayer, player_ptr_t pTarget, CUserCmd* pCmd );
	void PX_API ResetContext( );
	void PX_API OnNewTarget( player_ptr_t pLocalPlayer, player_ptr_t pTarget, CUserCmd* pCmd );

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

		player_ptr_t pTarget = nullptr;
		if ( _Config.bStaticTarget.Get( ) )
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
					if ( _Config.bValidateTarget.Get( ) && !bReleasedKey )
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

		pLast = &( pTarget->m_iTeamNum( ) == pLocalPlayer->m_iTeamNum( ) ? _Config.bTeammates.Get( ) : _Config.bEnemies.Get( ) );
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
				const auto vecViewAngles = pClientState->viewangles;
				auto vecTemp = vecViewAngles, vecTemp2 = Vector( qTargetAngle.pitch, qTargetAngle.yaw, qTargetAngle.roll );
				if ( fabsf( vecTemp.y ) > 90.f && fabsf( vecTemp2.y ) > 90.f )
				{
					if ( vecTemp.y < 0.f )
						vecTemp.y += 360.f;
					if ( vecTemp2.y < 0.f )
						vecTemp2.y += 360.f;
				}
				auto vecRelativeSmoothedAngles = vecViewAngles - ( vecTemp - vecTemp2 ) / _Config.flSmoothFactor;
				Vector vecNewAngles;

				switch( _Config.iSmoothMode )
				{
					case SMOOTH_LINEAR:
					{
						ClampAngles( vecRelativeSmoothedAngles );
						pClientState->viewangles = vecRelativeSmoothedAngles;
					}
					break;

					case SMOOTH_PARABOLIC:
					{
						vecNewAngles.x = vecRelativeSmoothedAngles.x;
						const auto flTemp = ( vecTemp2.y - vecTemp.y ) / pow( vecTemp2.x - vecNewAngles.x, 2.f );
						vecNewAngles.y = flTemp * pow( vecNewAngles.x - vecTemp.x, 2.f ) + vecTemp.y;
						vecNewAngles.z = vecViewAngles.z;
						ClampAngles( vecNewAngles );
						pClientState->viewangles = vecNewAngles;
					}
					break;

					case SMOOTH_RADICAL:
					{
						vecNewAngles.x = vecRelativeSmoothedAngles.x;
						const auto flTemp = ( vecTemp2.y - vecTemp.y ) / cbrtf( vecTemp2.x - vecNewAngles.x );
						vecNewAngles.y = flTemp * cbrtf( vecNewAngles.x - vecTemp.x ) + vecTemp.y;
						vecNewAngles.z = vecViewAngles.z;
						ClampAngles( vecNewAngles );
						pClientState->viewangles = vecNewAngles;
					}
					break;

					case SMOOTH_SINUSOIDAL:
					{
						vecNewAngles.x = vecRelativeSmoothedAngles.x;
						const auto fl = D3DX_PI / 2.f / ( vecNewAngles.x - vecTemp2.x );
						const auto flTemp = ( vecTemp2.y - vecTemp.y ) / sinf( fl * ( vecTemp2.x - vecNewAngles.x ) );
						vecNewAngles.y = flTemp * sinf( fl * ( vecNewAngles.x - vecTemp.x ) ) + vecTemp.y;
						vecNewAngles.z = vecViewAngles.z;
						ClampAngles( vecNewAngles );
						pClientState->viewangles = vecNewAngles;
					}
					break;

					case SMOOTH_BEZIER:
					{
						std::vector< std::pair< vertex_t, vertex_t > > vecLines;
						std::vector< vertex_t > vecDots;

						const auto fnDrawDot = [ & ]( Vector vecAngle, DWORD dwColor )
						{
							Vector vecPos, vecScreen;
							TransformAngle( vecAngle, vecPos );
							vecPos *= 8192.f;
							vecPos += pLocalPlayer->GetViewPosition( );
							if ( !WorldToScreen( vecPos, vecScreen ) )
								return;
							vecDots.emplace_back( vertex_t( vecScreen.x, vecScreen.y, dwColor ) );
						};

						const auto fnDrawLine = [ & ]( Vector vecStartAngle, Vector vecEndAngle, DWORD dwColor )
						{
							Vector vecPosOne, vecScreenOne;
							TransformAngle( vecStartAngle, vecPosOne );
							vecPosOne *= 8192.f;
							vecPosOne += pLocalPlayer->GetViewPosition( );
							if ( !WorldToScreen( vecPosOne, vecScreenOne ) )
								return;

							Vector vecPosTwo, vecScreenTwo;
							TransformAngle( vecEndAngle, vecPosTwo );
							vecPosTwo *= 8192.f;
							vecPosTwo += pLocalPlayer->GetViewPosition( );
							if ( !WorldToScreen( vecPosTwo, vecScreenTwo ) )
								return;

							vecLines.emplace_back( vertex_t( vecScreenOne.x, vecScreenOne.y, dwColor ), vertex_t( vecScreenTwo.x, vecScreenTwo.y, dwColor ) );
						};

						Vector vecLinePoints[ 2 ];
						const auto vecEndDifference = _AimContext.vecBezierEnd - vecTemp2;
						if ( _AimContext.flBezierRatio > 0.5f && sqrt( powf( vecEndDifference.x, 2.f ) + powf( vecEndDifference.y, 2.f ) ) > 1.f )
							_AimContext.bResetBezierOrigin = true;
						if ( _AimContext.bResetBezierOrigin )
						{
							_AimContext.vecBezierOrigin = vecTemp;
							_AimContext.vecBezierEnd = vecTemp2;
							_AimContext.flBezierRatio = 0.f;
							_AimContext.bResetBezierOrigin = false;
						}
						vecTemp = _AimContext.vecBezierOrigin;

						const auto vecDifference = vecTemp - vecTemp2;
						if ( _AimContext.flBezierRatio < 1.f )
							_AimContext.flBezierRatio += fabsf( _Config.flSmoothFactor - 51.f ) / 50.f;
						if ( _AimContext.flBezierRatio > 1.f )
							_AimContext.flBezierRatio = 1.f;

						fnDrawDot( vecTemp, 0xFF000000 );
						fnDrawDot( vecTemp2, 0xFFFF0000 );

						fnDrawLine( vecTemp, vecTemp2, 0xFFFF0000 );
						const auto flAngle = atan2( vecDifference.x, vecDifference.y );
						const auto vecBisection = vecTemp - vecDifference * _Config.flBisectionPoint;
						fnDrawDot( vecBisection, 0xFF909000 );
						auto vecIntersection = vecBisection;
						vecIntersection.y -= sin( flAngle ) * _Config.flBezierDistance;
						vecIntersection.x += cos( flAngle ) * _Config.flBezierDistance;
						vecLinePoints[ 0 ] = vecTemp - ( vecTemp - vecIntersection ) * _AimContext.flBezierRatio;
						vecLinePoints[ 1 ] = vecIntersection - ( vecIntersection - vecTemp2 ) * _AimContext.flBezierRatio;
						vecNewAngles = vecLinePoints[ 0 ] - ( vecLinePoints[ 0 ] - vecLinePoints[ 1 ] ) * _AimContext.flBezierRatio;
						fnDrawLine( vecTemp, vecIntersection, 0xFFFFFFFF );
						fnDrawLine( vecIntersection, vecTemp2, 0xFFFFFFFF );
						fnDrawLine( vecLinePoints[ 0 ], vecLinePoints[ 1 ], 0xFF0000FF );
						fnDrawDot( vecIntersection, 0xFF00FF00 );
						fnDrawDot( vecNewAngles, 0xFFFFFFFF );
						ClampAngles( vecNewAngles );
						pClientState->viewangles = vecNewAngles;

						const auto pNewDots = new vertex_t[ vecDots.size( ) ];
						const auto pNewLines = new std::pair< vertex_t, vertex_t >[ vecLines.size( ) ];
						memcpy( pNewLines, &vecLines[ 0 ], vecLines.size( ) * sizeof( std::pair< vertex_t, vertex_t > ) );
						memcpy( pNewDots, &vecDots[ 0 ], vecDots.size( ) * sizeof( vertex_t ) );

						const auto pOldDots = _AimPath.pPoints.load( );
						_AimPath.pPoints = pNewDots;
						delete[ ] pOldDots;

						const auto pOldLines = _AimPath.pLines.load( );
						_AimPath.pLines = pNewLines;
						delete[ ] pOldLines;

						_AimPath.zPoints = vecDots.size( );
						_AimPath.zLines = vecLines.size( );
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

	void PX_API DrawAimPath( )
	{
		const auto pLines = _AimPath.pLines.load( );
		const auto pDots = _AimPath.pPoints.load( );
		D3DXVECTOR2 vecCurrent[ 2 ] { };

		for ( auto z = 0u; z < _AimPath.zLines.load( ); z++ )
		{
			vecCurrent[ 0 ] = D3DXVECTOR2( pLines[ z ].first._Vectors.x, pLines[ z ].first._Vectors.y );
			vecCurrent[ 1 ] = D3DXVECTOR2( pLines[ z ].second._Vectors.x, pLines[ z ].second._Vectors.y );

			Drawing::Line( vecCurrent, 2, 3.f, pLines[ z ].first.dwColor );
		}

		for ( auto z = 0u; z < _AimPath.zPoints.load( ); z++ )
			Drawing::Circle( D3DXVECTOR2( pDots[ z ]._Vectors.x, pDots[ z ]._Vectors.y ), 3.f, pDots[ z ].dwColor, pDots[ z ].dwColor, 8 );
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

			const auto flCrosshairDistance = CalculateCrosshairDistance( pLocalPlayer, pCurrentEntity, _Config.iReferenceHitbox, pCmd, _Config.bWorldlyCrosshairDistance.Get( ) );
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

	bool PX_API ValidateTarget( player_ptr_t pLocalPlayer, player_ptr_t pTarget, CUserCmd* pCmd )
	{
		if ( _AimContext.iHitbox != -1 )
			if ( CalculateCrosshairDistance( pLocalPlayer, pTarget, _AimContext.iHitbox, pCmd, _Config.bWorldlyCrosshairDistance.Get( ) ) )
				return true;
		return -1 != ( _AimContext.iHitbox = FindHitbox( pLocalPlayer, pTarget, pCmd ) );
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
	}
}
