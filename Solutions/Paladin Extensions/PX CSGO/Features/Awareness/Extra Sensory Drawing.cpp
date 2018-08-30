/// Extra Sensory Drawing.cpp

#include "../../PX CSGO.hpp"

using namespace PX::Tools;
using namespace PX::Information;
using namespace Pointers;

namespace PX::Features::Awareness
{
	auto esdConfig = &_Settings._Awareness._ExtraSensoryDrawing;
	auto esdEntityConfig = &esdConfig->_Players[ TEAM ];
	CBasePlayer* pLocalPlayer = nullptr;

	struct
	{
		CBaseEntity* pEntity { };
		bool bTeammate { }, bIsPlayer { };
		int iSettingIndex { };
		Vector vecLocation { };
		EClassID cClass;
		int iState { };
	} info { };

	void PX_API Box( );
	void PX_API Snapline( );

	void PX_API Draw( )
	{
		//vertex_t vtxPoints[]
		//{
		//	vertex_t( 0, 0, 0xffffffff ),
		//	vertex_t( 50, 0, 0xffffffff ),
		//	vertex_t( 50, 50, 0xffffffff ),
		//	vertex_t( 0, 50, 0xffffffff )
		//};
		//
		//Drawing::Polygon( vtxPoints, 4, 2 );
		//
		//Drawing::BoxFilled( 500, 500, 200, 200, 0xffff0000 );

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
			if ( !pEntity || !ValidPlayer( pEntity ) )
				continue;

			info.pEntity = pEntity;
			info.bTeammate = pEntity->m_iTeamNum( ) == iLocalPlayerTeam;
			info.vecLocation = pEntity->m_vecOrigin( );
			info.cClass = pEntity->GetClientNetworkable( )->GetClientClass( )->m_ClassID;

			switch ( info.cClass )
			{
				case ClassID_CCSPlayer:
					info.iSettingIndex = info.bTeammate ? TEAM : ENEMY;
					esdEntityConfig = &esdConfig->_Players[ info.iSettingIndex ];
					info.bIsPlayer = true;
					break;
				// TODO: add rest of options for esp.
				default:
					continue;
			}

			if ( !esdEntityConfig->bEnabled )
				continue;

			info.iState = pEntity->IsDormant( ) ? DORMANT
				: pLocalPlayer->PositionInSight( !info.bIsPlayer ? info.vecLocation : reinterpret_cast< CBasePlayer* >( info.pEntity )->GetHitboxPosition( HITBOX_CHEST ), 
												 esdEntityConfig->bMindSmoke, info.pEntity ) ? VISIBLE : INVISIBLE;
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
			enum
			{
				BOTTOMRIGHT,
				BOTTOMLEFT,
				TOPRIGHT,
				TOPLEFT
			};

			Vector vecPoints[ ] { info.vecLocation, info.vecLocation, info.vecLocation, info.vecLocation };
			Vector vecBuffer[ 4 ];
			std::deque< D3DXVECTOR2 > dqScreenPoints;
			dqScreenPoints.resize( 5 );
			const Vector2D vecRotationPoint { info.vecLocation.x, info.vecLocation.y };
			const auto vecHeadPosition = reinterpret_cast< CBasePlayer* >( info.pEntity )->GetHitboxPosition( HITBOX_HEAD );

			vecPoints[ BOTTOMRIGHT ].y -= 20.f; // Bottom right
			vecPoints[ BOTTOMRIGHT ].z -= 5.f;
			vecPoints[ BOTTOMLEFT ].y += 20.f; // Bottom left
			vecPoints[ BOTTOMLEFT ].z -= 5.f;
			vecPoints[ TOPRIGHT ].y -= 20.f; // Top right
			vecPoints[ TOPRIGHT ].z = vecHeadPosition.z + 10.f;
			vecPoints[ TOPLEFT ].y += 20.f; // Top left
			vecPoints[ TOPLEFT ].z = vecHeadPosition.z + 10.f;

			const auto flRotation = pClientState->viewangles.y - ( pClientState->viewangles.y -
																   CalcAngle( pLocalPlayer->GetViewPosition( ), reinterpret_cast< CBasePlayer* >( info.pEntity )->GetViewPosition( ) ).y );

			for ( auto i = 0; i < 4; i++ )
			{
				vecPoints[ i ].Rotate2D( flRotation, vecRotationPoint );
				if ( !WorldToScreen( vecPoints[ i ], vecBuffer[ i ] ) )
					return;
			}

			dqScreenPoints[ 0 ] = D3DXVECTOR2( vecBuffer[ BOTTOMRIGHT ].x, vecBuffer[ BOTTOMRIGHT ].y );
			dqScreenPoints[ 1 ] = D3DXVECTOR2( vecBuffer[ BOTTOMLEFT ].x, vecBuffer[ BOTTOMLEFT ].y );
			dqScreenPoints[ 2 ] = D3DXVECTOR2( vecBuffer[ TOPLEFT ].x, vecBuffer[ TOPLEFT ].y );
			dqScreenPoints[ 3 ] = D3DXVECTOR2( vecBuffer[ TOPRIGHT ].x, vecBuffer[ TOPRIGHT ].y );
			dqScreenPoints[ 4 ] = D3DXVECTOR2( vecBuffer[ BOTTOMRIGHT ].x, vecBuffer[ BOTTOMRIGHT ].y );

			Drawing::Line( dqScreenPoints, 2, esdEntityConfig->seqBox[ info.iState ].GetCurrentColor( ).GetARGB( ) );
			if ( !esdEntityConfig->bFill )
				return;

			vertex_t vtxFillPoints[ 4 ];
			if ( esdEntityConfig->bHealthBasedFillColor )
			{
				const auto iHealth = reinterpret_cast< CBasePlayer* >( info.pEntity )->m_iHealth( );
				const auto dwTopColor = D3DCOLOR_ARGB( byte_t( iHealth * 1.275f ), 0, 0xFF, 0 );
				const auto dwBottomColor = D3DCOLOR_ARGB( byte_t( iHealth * 5.1f ), 0, 0xFF, 0 );

				vtxFillPoints[ 0 ] = vertex_t( vecBuffer[ TOPLEFT ].x, vecBuffer[ TOPLEFT ].y, dwTopColor );
				vtxFillPoints[ 1 ] = vertex_t( vecBuffer[ TOPRIGHT ].x, vecBuffer[ TOPRIGHT ].y, dwTopColor );
				vtxFillPoints[ 2 ] = vertex_t( vecBuffer[ BOTTOMRIGHT ].x, vecBuffer[ BOTTOMRIGHT ].y, dwBottomColor );
				vtxFillPoints[ 3 ] = vertex_t( vecBuffer[ BOTTOMLEFT ].x, vecBuffer[ BOTTOMLEFT ].y, dwBottomColor );
			}
			else
			{
				const auto dwColor = esdEntityConfig->seqFill[ info.iState ].GetCurrentColor( ).GetARGB( );
				vtxFillPoints[ 0 ] = vertex_t( vecBuffer[ TOPLEFT ].x, vecBuffer[ TOPLEFT ].y, dwColor );
				vtxFillPoints[ 1 ] = vertex_t( vecBuffer[ TOPRIGHT ].x, vecBuffer[ TOPRIGHT ].y, dwColor );
				vtxFillPoints[ 2 ] = vertex_t( vecBuffer[ BOTTOMRIGHT ].x, vecBuffer[ BOTTOMRIGHT ].y, dwColor );
				vtxFillPoints[ 3 ] = vertex_t( vecBuffer[ BOTTOMLEFT ].x, vecBuffer[ BOTTOMLEFT ].y, dwColor );
			}
			Drawing::Polygon( vtxFillPoints, 4, 2 );
		}
	}

	void PX_API Snapline( )
	{

	}
}
