/// Extra Sensory Drawing.cpp

#include "../../PX CSGO.hpp"

using namespace PX::Tools;
using namespace PX::Information;
using namespace Pointers;

namespace PX::Features::Awareness
{
	auto esdConfig = &sSettings.awareness.extra_sensory_drawing;
	auto esdEntityConfig = &esdConfig->players[ TEAM ];
	CBasePlayer* pLocalPlayer = nullptr;

	struct
	{
		CBaseEntity* pEntity { };
		bool bTeammate { }, bIsPlayer { };
		int iSettingIndex { };
		Vector vecLocation { };
		int iState { };
	} info;

	void PX_API Box( );
	void PX_API Snapline( );

	void PX_API Draw( )
	{
		if ( !pEngineClient->IsInGame( ) )
			return;
		pLocalPlayer = GetLocalPlayer( );
		if ( !pLocalPlayer )
			return;
		const auto iLocalPlayerIndex = pLocalPlayer->EntIndex( );
		const auto iLocalPlayerTeam = pLocalPlayer->m_iTeamNum( );

		for ( auto i = 0; i < pEntityList->GetMaxEntities( ); i++ )
		{
			if ( i == iLocalPlayerIndex )
				continue;

			const auto pEntity = reinterpret_cast< CBaseEntity* >( pEntityList->GetClientEntity( i ) );
			if ( !pEntity )
				continue;

			info.pEntity = pEntity;
			info.bTeammate = pEntity->m_iTeamNum( ) == iLocalPlayerTeam;
			info.vecLocation = pEntity->m_vecOrigin( );

			switch ( pEntity->GetClientNetworkable( )->GetClientClass( )->m_ClassID )
			{
				case ClassID_CCSPlayer:
					info.iSettingIndex = info.bTeammate ? TEAM : ENEMY;
					esdEntityConfig = &esdConfig->players[ info.iSettingIndex ];
					info.bIsPlayer = true;
					break;
				/// TODO: add rest of options for esp.
				default:
					continue;
			}

			if ( !esdEntityConfig->bEnabled )
				continue;

			info.iState = pEntity->IsDormant( ) ? DORMANT
				: pLocalPlayer->PositionInSight( info.vecLocation, esdEntityConfig->bMindSmoke ) ? VISIBLE : INVISIBLE;
			Box( );
			Snapline( );
		}
	}

	void PX_API Box( )
	{
		if ( !esdEntityConfig->bBox )
			return;

		if( esdEntityConfig->bThreeDimensional ) // 3d box
		{
			
		}
		else // 2d box
		{
			Vector vecPoints[ ] { info.vecLocation, info.vecLocation, info.vecLocation, info.vecLocation };
			Vector vecBuffer[ 4 ];
			std::deque< D3DXVECTOR2 > dqScreenPoints;
			dqScreenPoints.resize( 5 );
			Vector2D vecRotationPoint { info.vecLocation.x, info.vecLocation.y };
			const auto vecHeadPosition = reinterpret_cast< CBasePlayer* >( info.pEntity )->GetHitboxPosition( HITBOX_HEAD );

			vecPoints[ 0 ].y -= 20.f; // Bottom right
			vecPoints[ 0 ].z -= 5.f;
			vecPoints[ 1 ].y += 20.f; // Bottom left
			vecPoints[ 1 ].z -= 5.f;

			vecPoints[ 2 ].y -= 20.f; // Top right
			vecPoints[ 2 ].z = vecHeadPosition.z;
			vecPoints[ 3 ].y += 20.f; // Top left
			vecPoints[ 3 ].z = vecHeadPosition.z;

			const auto flRotation = pClientState->viewangles.y - ( pClientState->viewangles.y - 
																   CalcAngle( pLocalPlayer->GetViewPosition( ), reinterpret_cast< CBasePlayer* >( info.pEntity )->GetViewPosition( ) ).y );
			for ( auto i = 0; i < 4; i++ )
			{
				vecPoints[ i ].Rotate2D( flRotation, vecRotationPoint );
				WorldToScreen( vecPoints[ i ], vecBuffer[i] );
			}

			dqScreenPoints[ 0 ] = D3DXVECTOR2( vecBuffer[ 0 ].x, vecBuffer[ 0 ].y );
			dqScreenPoints[ 1 ] = D3DXVECTOR2( vecBuffer[ 1 ].x, vecBuffer[ 1 ].y );
			dqScreenPoints[ 2 ] = D3DXVECTOR2( vecBuffer[ 3 ].x, vecBuffer[ 3 ].y );
			dqScreenPoints[ 3 ] = D3DXVECTOR2( vecBuffer[ 2 ].x, vecBuffer[ 2 ].y );
			dqScreenPoints[ 4 ] = D3DXVECTOR2( vecBuffer[ 0 ].x, vecBuffer[ 0 ].y );

			Drawing::Line( dqScreenPoints, 2, esdEntityConfig->seqBox[ info.iState ].GetCurrentColor( ).GetHex( ) );
		}
	}

	void PX_API Snapline( )
	{

	}
}
