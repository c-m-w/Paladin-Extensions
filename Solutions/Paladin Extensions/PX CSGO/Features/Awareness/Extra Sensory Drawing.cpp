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
		CBaseEntity* pEntity = nullptr;
		bool bTeammate = false, bIsPlayer = false;
		int iSettingIndex = 0;
		Vector vecLocation = Vector( );
		EClassID cClass = CLASSID_MAX;
		int iState = STATE_VISIBLE;
	} info;

	void PX_API Box( );
	void PX_API SnapLine( );
	void PX_API ViewLine( );

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

			info.iState = pEntity->IsDormant( ) ? STATE_DORMANT
				: pLocalPlayer->PositionInSight( !info.bIsPlayer ? info.vecLocation : reinterpret_cast< CBasePlayer* >( info.pEntity )->GetHitboxPosition( HITBOX_CHEST ), 
												 esdEntityConfig->bMindSmoke, info.pEntity ) ? STATE_VISIBLE : STATE_INVISIBLE;
			Box( );
			SnapLine( );
			ViewLine( );
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

			if ( esdEntityConfig->bFill )
			{
				vertex_t vtxFillPoints[ 4 ];
				if ( esdEntityConfig->bHealthBasedFillColor )
				{
					PX_DEF iMaxHealth = 100;
					const auto iHealth = reinterpret_cast< CBasePlayer* >( info.pEntity )->m_iHealth( );
					const auto iLeftSideHeight = vecBuffer[ BOTTOMLEFT ].y - vecBuffer[ TOPLEFT ].y;
					const auto iRightSideHeight = vecBuffer[ BOTTOMRIGHT ].y - vecBuffer[ TOPRIGHT ].y;
					const auto flHealthRatio = float( iHealth ) / float( iMaxHealth );
					const auto iLeftSideDifference = vecBuffer[ BOTTOMLEFT ].x - vecBuffer[ TOPLEFT ].x;
					const auto iRightSideDifference = vecBuffer[ BOTTOMRIGHT ].x - vecBuffer[ TOPRIGHT ].x;
					const auto dwBottom = esdEntityConfig->seqHealthFill[ 1 ][ info.iState ].GetCurrentColor( ).GetARGB( );

					if ( iHealth < iMaxHealth )
					{
						const auto dwTop = esdEntityConfig->seqHealthFill[ 0 ][ info.iState ].GetCurrentColor( ).GetARGB( );
						vtxFillPoints[ 0 ] = vertex_t( vecBuffer[ TOPLEFT ].x, vecBuffer[ TOPLEFT ].y, esdEntityConfig->bSolidHealthFill ? dwTop : 0 );
						vtxFillPoints[ 1 ] = vertex_t( vecBuffer[ TOPRIGHT ].x, vecBuffer[ TOPRIGHT ].y, esdEntityConfig->bSolidHealthFill ? dwTop : 0 );
						vtxFillPoints[ 2 ] = vertex_t( vecBuffer[ TOPRIGHT ].x + iRightSideDifference * ( 1.f - flHealthRatio ), vecBuffer[ TOPRIGHT ].y + ( iRightSideHeight - ( iRightSideHeight * flHealthRatio ) ), dwTop );
						vtxFillPoints[ 3 ] = vertex_t( vecBuffer[ TOPLEFT ].x + iLeftSideDifference * ( 1.f - flHealthRatio ), vecBuffer[ TOPLEFT ].y + ( iLeftSideHeight - ( iLeftSideHeight * flHealthRatio ) ), dwTop );
						Drawing::Polygon( vtxFillPoints, 4, 2 );
					}

					vtxFillPoints[ 0 ] = vertex_t( vecBuffer[ BOTTOMLEFT ].x - iLeftSideDifference * flHealthRatio, vecBuffer[ BOTTOMLEFT ].y - iLeftSideHeight * flHealthRatio, dwBottom );
					vtxFillPoints[ 1 ] = vertex_t( vecBuffer[ BOTTOMRIGHT ].x - iRightSideDifference * flHealthRatio, vecBuffer[ BOTTOMRIGHT ].y - iRightSideHeight * flHealthRatio, dwBottom );
					vtxFillPoints[ 2 ] = vertex_t( vecBuffer[ BOTTOMRIGHT ].x, vecBuffer[ BOTTOMRIGHT ].y, esdEntityConfig->bSolidHealthFill ? dwBottom : 0 );
					vtxFillPoints[ 3 ] = vertex_t( vecBuffer[ BOTTOMLEFT ].x, vecBuffer[ BOTTOMLEFT ].y, esdEntityConfig->bSolidHealthFill ? dwBottom : 0 );
					Drawing::Polygon( vtxFillPoints, 4, 2 );
				}
				else
				{
					const auto dwColor = esdEntityConfig->seqFill[ info.iState ].GetCurrentColor( ).GetARGB( );
					vtxFillPoints[ 0 ] = vertex_t( vecBuffer[ TOPLEFT ].x, vecBuffer[ TOPLEFT ].y, dwColor );
					vtxFillPoints[ 1 ] = vertex_t( vecBuffer[ TOPRIGHT ].x, vecBuffer[ TOPRIGHT ].y, dwColor );
					vtxFillPoints[ 2 ] = vertex_t( vecBuffer[ BOTTOMRIGHT ].x, vecBuffer[ BOTTOMRIGHT ].y, dwColor );
					vtxFillPoints[ 3 ] = vertex_t( vecBuffer[ BOTTOMLEFT ].x, vecBuffer[ BOTTOMLEFT ].y, dwColor );
					Drawing::Polygon( vtxFillPoints, 4, 2 );
				}
			}

			Drawing::Line( dqScreenPoints, 2, esdEntityConfig->seqBox[ info.iState ].GetCurrentColor( ).GetARGB( ) );
		}
	}

	void PX_API SnapLine( )
	{
		if ( !esdEntityConfig->bSnaplines )
			return;

		Vector vecEntity;
		int iWidth, iHeight;
		std::deque< D3DXVECTOR2 > dqScreenPoints;

		if ( !WorldToScreen( info.vecLocation, vecEntity ) )
			return;

		pEngineClient->GetScreenSize( iWidth, iHeight );
		dqScreenPoints.emplace_back( vecEntity.x, vecEntity.y );
		dqScreenPoints.emplace_back( iWidth / 2.f, iHeight );
		Drawing::Line( dqScreenPoints, esdEntityConfig->flSnaplineWidth, esdEntityConfig->seqSnaplines[ info.iState ].GetCurrentColor( ).GetARGB( ) );
	}

	void PX_API ViewLine( )
	{
		if ( !esdEntityConfig->bViewLines )
			return;

		Vector vecEntity, vecEnd;
		std::deque< D3DXVECTOR2 > dqScreenPoints;
		auto& gtRay = reinterpret_cast< CBasePlayer* >( info.pEntity )->TraceRayFromView( );

		WorldToScreen( gtRay.startpos, vecEntity );
		WorldToScreen( gtRay.endpos, vecEnd );
		dqScreenPoints.emplace_back( vecEntity.x, vecEntity.y );
		dqScreenPoints.emplace_back( vecEnd.x, vecEnd.y );
		Drawing::Line( dqScreenPoints, esdEntityConfig->flViewLineWidth, esdEntityConfig->seqViewLines[ info.iState ].GetCurrentColor( ).GetARGB( ) );
	}
}
