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
		CBaseEntity* pEntity;
		bool bTeammate = false, bIsPlayer = false;
		int iSettingIndex = 0;
		Vector vecLocation = Vector( );
		EClassID cClass = CLASSID_MAX;
		int iState = STATE_VISIBLE;
	} info;

	void PX_API Box( );
	void PX_API SnapLine( );
	void PX_API ViewLine( );
	void PX_API Skeleton( );

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

			info.cClass = pEntity->GetClientNetworkable( )->GetClientClass( )->m_ClassID;
			info.bTeammate = pEntity->m_iTeamNum( ) == iLocalPlayerTeam;

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

			info.pEntity = pEntity;
			info.vecLocation = info.pEntity->m_vecOrigin( );

			if ( pEntity->IsDormant( ) )
				info.iState = STATE_DORMANT;
			else if ( pLocalPlayer->PositionInSight( !info.bIsPlayer ? info.vecLocation : reinterpret_cast< CBasePlayer* >( info.pEntity )->GetHitboxPosition( HITBOX_HEAD ),
													 esdEntityConfig->bMindSmoke, info.pEntity )
					  || info.bIsPlayer && ( pLocalPlayer->PositionInSight( reinterpret_cast< CBasePlayer* >( info.pEntity )->GetHitboxPosition( HITBOX_LEFT_FOOT ),
														esdEntityConfig->bMindSmoke, info.pEntity )
					  || pLocalPlayer->PositionInSight( reinterpret_cast< CBasePlayer* >( info.pEntity )->GetHitboxPosition( HITBOX_RIGHT_FOOT ),
														esdEntityConfig->bMindSmoke, info.pEntity ) ) )
				info.iState = STATE_VISIBLE;
			else
				info.iState = STATE_INVISIBLE;

			Box( );
			SnapLine( );
			ViewLine( );
			Skeleton( );
		}
	}

	void PX_API Box( )
	{
		if ( !esdEntityConfig->bBox )
			return;
		const auto clrBox = esdEntityConfig->seqBox[ info.iState ].GetCurrentColor( ),
					clrFill = esdEntityConfig->bHealthBasedFillColor ? color_t( ) : esdEntityConfig->seqFill[ info.iState ].GetCurrentColor( ),
					clrBottom = esdEntityConfig->bHealthBasedFillColor ? esdEntityConfig->seqHealthFill[ 1 ][ info.iState ].GetCurrentColor( ) : color_t( ),
					clrTop = esdEntityConfig->bHealthBasedFillColor ? esdEntityConfig->seqHealthFill[ 0 ][ info.iState ].GetCurrentColor( ) : color_t( );
		if ( clrBox.a == 0 && esdEntityConfig->bHealthBasedFillColor ? clrBottom.a == 0 && clrTop.a == 0 : clrFill.a == 0 )
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
			const Vector2D vecRotationPoint { info.vecLocation.x, info.vecLocation.y };
			const auto vecViewPosition = info.vecLocation + reinterpret_cast< CBasePlayer* >( info.pEntity )->m_vecViewOffset( );

			vecPoints[ BOTTOMRIGHT ].y -= 20.f; // Bottom right
			vecPoints[ BOTTOMRIGHT ].z -= 5.f;
			vecPoints[ BOTTOMLEFT ].y += 20.f; // Bottom left
			vecPoints[ BOTTOMLEFT ].z -= 5.f;
			vecPoints[ TOPRIGHT ].y -= 20.f; // Top right
			vecPoints[ TOPRIGHT ].z = vecViewPosition.z + 10.f;
			vecPoints[ TOPLEFT ].y += 20.f; // Top left
			vecPoints[ TOPLEFT ].z = vecViewPosition.z + 10.f;

			const auto flRotation = pClientState->viewangles.y - ( pClientState->viewangles.y -
																   CalcAngle( pLocalPlayer->GetViewPosition( ), reinterpret_cast< CBasePlayer* >( info.pEntity )->GetViewPosition( ) ).y );

			for ( auto i = 0; i < 4; i++ )
			{
				vecPoints[ i ].Rotate2D( flRotation, vecRotationPoint );
				if ( !WorldToScreen( vecPoints[ i ], vecBuffer[ i ] ) )
					return;
			}

			D3DXVECTOR2 vecScreenPoints[ ]
			{
				D3DXVECTOR2( vecBuffer[ BOTTOMRIGHT ].x, vecBuffer[ BOTTOMRIGHT ].y ),
				D3DXVECTOR2( vecBuffer[ BOTTOMLEFT ].x, vecBuffer[ BOTTOMLEFT ].y ),
				D3DXVECTOR2( vecBuffer[ TOPLEFT ].x, vecBuffer[ TOPLEFT ].y ),
				D3DXVECTOR2( vecBuffer[ TOPRIGHT ].x, vecBuffer[ TOPRIGHT ].y ),
				D3DXVECTOR2( vecBuffer[ BOTTOMRIGHT ].x, vecBuffer[ BOTTOMRIGHT ].y )
			};

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
					const auto flZDifference = ( vecPoints[ TOPLEFT ].z - vecPoints[ BOTTOMLEFT ].z ) * ( float( iHealth ) / float( iMaxHealth ) );
					auto vecMiddleLeft = vecPoints[ BOTTOMLEFT ],
						vecMiddleRight = vecPoints[ BOTTOMRIGHT ];
					vecMiddleLeft.z += flZDifference;
					vecMiddleRight.z += flZDifference;
					Vector vecScreenMiddleLeft, vecScreenMiddleRight;
					const auto dwBottom = clrBottom.GetARGB( );

					WorldToScreen( vecMiddleLeft, vecScreenMiddleLeft );
					WorldToScreen( vecMiddleRight, vecScreenMiddleRight );

					if ( iHealth < iMaxHealth )
					{
						const auto dwTop = clrTop.GetARGB( );
						vtxFillPoints[ 0 ] = vertex_t( vecBuffer[ TOPLEFT ].x, vecBuffer[ TOPLEFT ].y, esdEntityConfig->bSolidHealthFill ? dwTop : 0 );
						vtxFillPoints[ 1 ] = vertex_t( vecBuffer[ TOPRIGHT ].x, vecBuffer[ TOPRIGHT ].y, esdEntityConfig->bSolidHealthFill ? dwTop : 0 );
						vtxFillPoints[ 2 ] = vertex_t( vecScreenMiddleRight.x, vecScreenMiddleRight.y, dwTop );
						vtxFillPoints[ 3 ] = vertex_t( vecScreenMiddleLeft.x, vecScreenMiddleLeft.y, dwTop );
						Drawing::Polygon( vtxFillPoints, 4, 2 );
					}

					vtxFillPoints[ 0 ] = vertex_t( vecScreenMiddleLeft.x, vecScreenMiddleLeft.y, dwBottom );
					vtxFillPoints[ 1 ] = vertex_t( vecScreenMiddleRight.x, vecScreenMiddleRight.y, dwBottom );
					vtxFillPoints[ 2 ] = vertex_t( vecBuffer[ BOTTOMRIGHT ].x, vecBuffer[ BOTTOMRIGHT ].y, esdEntityConfig->bSolidHealthFill ? dwBottom : 0 );
					vtxFillPoints[ 3 ] = vertex_t( vecBuffer[ BOTTOMLEFT ].x, vecBuffer[ BOTTOMLEFT ].y, esdEntityConfig->bSolidHealthFill ? dwBottom : 0 );
					Drawing::Polygon( vtxFillPoints, 4, 2 );
				}
				else
				{
					const auto dwColor = clrFill.GetARGB( );
					vtxFillPoints[ 0 ] = vertex_t( vecBuffer[ TOPLEFT ].x, vecBuffer[ TOPLEFT ].y, dwColor );
					vtxFillPoints[ 1 ] = vertex_t( vecBuffer[ TOPRIGHT ].x, vecBuffer[ TOPRIGHT ].y, dwColor );
					vtxFillPoints[ 2 ] = vertex_t( vecBuffer[ BOTTOMRIGHT ].x, vecBuffer[ BOTTOMRIGHT ].y, dwColor );
					vtxFillPoints[ 3 ] = vertex_t( vecBuffer[ BOTTOMLEFT ].x, vecBuffer[ BOTTOMLEFT ].y, dwColor );
					Drawing::Polygon( vtxFillPoints, 4, 2 );
				}
			}
			Drawing::Line( vecScreenPoints, 5, 2, clrBox.GetARGB( ) );
		}
	}

	void PX_API SnapLine( )
	{
		if ( !esdEntityConfig->bSnaplines )
			return;

		const auto clrSnapLine = esdEntityConfig->seqSnaplines[ info.iState ].GetCurrentColor( );
		if ( clrSnapLine.a == 0 )
			return;

		Vector vecEntity;
		int iWidth, iHeight;
		if ( !WorldToScreen( info.vecLocation, vecEntity ) )
			return;

		pEngineClient->GetScreenSize( iWidth, iHeight );
		const D3DXVECTOR2 vecScreenPoints[ ]
		{
			D3DXVECTOR2( vecEntity.x, vecEntity.y ),
			D3DXVECTOR2( iWidth / 2.f, iHeight )
		};

		Drawing::Line( vecScreenPoints, 2, esdEntityConfig->flSnaplineWidth, clrSnapLine.GetARGB( ) );
	}

	void PX_API ViewLine( )
	{
		if ( !esdEntityConfig->bViewLines )
			return;

		const auto clrViewline = esdEntityConfig->seqViewLines[ info.iState ].GetCurrentColor( );
		if ( clrViewline.a == 0 )
			return;

		Vector vecEntity, vecEnd;
		auto& gtRay = reinterpret_cast< CBasePlayer* >( info.pEntity )->TraceRayFromView( );

		if ( !WorldToScreen( reinterpret_cast< CBasePlayer* >( info.pEntity )->GetHitboxPosition( HITBOX_HEAD ), vecEntity )
			 || !WorldToScreen( gtRay.endpos, vecEnd ) )
			return;

		const D3DXVECTOR2 vecScreenPoints[ ]
		{
			D3DXVECTOR2( vecEntity.x, vecEntity.y ),
			D3DXVECTOR2( vecEnd.x, vecEnd.y )
		};
		const auto dwColor = clrViewline.GetARGB( );
		const auto flBoxSize = esdEntityConfig->flViewLineWidth + 1.5f;

		Drawing::Line( vecScreenPoints, 2, esdEntityConfig->flViewLineWidth, dwColor );

		vertex_t vtxBox[ ]
		{
			vertex_t( vecEnd.x - flBoxSize, vecEnd.y - flBoxSize, dwColor ),
			vertex_t( vecEnd.x + flBoxSize, vecEnd.y - flBoxSize, dwColor ),
			vertex_t( vecEnd.x + flBoxSize, vecEnd.y + flBoxSize, dwColor ),
			vertex_t( vecEnd.x - flBoxSize, vecEnd.y + flBoxSize, dwColor )
		};
		Drawing::Polygon( vtxBox, 4, 2 );
	}

	void PX_API Skeleton( )
	{
		if ( !esdEntityConfig->bSkeleton )
			return;

		const auto clrSkeleton = esdEntityConfig->seqSkeleton[ info.iState ].GetCurrentColor( );
		if ( clrSkeleton.a == 0 )
			return;

		Vector vecHitboxes[ HITBOX_MAX ];
		for ( auto e = int( HITBOX_HEAD ); e < HITBOX_MAX; e++ )
			if ( !WorldToScreen( reinterpret_cast< CBasePlayer* >( info.pEntity )->GetHitboxPosition( EHitbox( e ) ), vecHitboxes[ e ] ) )
				 return;

		const D3DXVECTOR2 vecLegs[ ] // 7
		{
			D3DXVECTOR2( vecHitboxes[ HITBOX_LEFT_FOOT ].x, vecHitboxes[ HITBOX_LEFT_FOOT ].y ),
			D3DXVECTOR2( vecHitboxes[ HITBOX_LEFT_CALF ].x, vecHitboxes[ HITBOX_LEFT_CALF ].y ),
			D3DXVECTOR2( vecHitboxes[ HITBOX_LEFT_THIGH ].x, vecHitboxes[ HITBOX_LEFT_THIGH ].y ),
			D3DXVECTOR2( vecHitboxes[ HITBOX_PELVIS ].x, vecHitboxes[ HITBOX_PELVIS ].y ),
			D3DXVECTOR2( vecHitboxes[ HITBOX_RIGHT_THIGH ].x, vecHitboxes[ HITBOX_RIGHT_THIGH ].y ),
			D3DXVECTOR2( vecHitboxes[ HITBOX_RIGHT_CALF ].x, vecHitboxes[ HITBOX_RIGHT_CALF ].y ),
			D3DXVECTOR2( vecHitboxes[ HITBOX_RIGHT_FOOT ].x, vecHitboxes[ HITBOX_RIGHT_FOOT ].y )
		};

		const D3DXVECTOR2 vecArms[ ] // 7
		{
			D3DXVECTOR2( vecHitboxes[ HITBOX_LEFT_HAND ].x, vecHitboxes[ HITBOX_LEFT_HAND ].y ),
			D3DXVECTOR2( vecHitboxes[ HITBOX_LEFT_FOREARM ].x, vecHitboxes[ HITBOX_LEFT_FOREARM ].y ),
			D3DXVECTOR2( vecHitboxes[ HITBOX_LEFT_UPPER_ARM ].x, vecHitboxes[ HITBOX_LEFT_UPPER_ARM ].y ),
			D3DXVECTOR2( vecHitboxes[ HITBOX_UPPER_CHEST ].x, vecHitboxes[ HITBOX_UPPER_CHEST ].y ),
			D3DXVECTOR2( vecHitboxes[ HITBOX_RIGHT_UPPER_ARM ].x, vecHitboxes[ HITBOX_RIGHT_UPPER_ARM ].y ),
			D3DXVECTOR2( vecHitboxes[ HITBOX_RIGHT_FOREARM ].x, vecHitboxes[ HITBOX_RIGHT_FOREARM ].y ),
			D3DXVECTOR2( vecHitboxes[ HITBOX_RIGHT_HAND ].x, vecHitboxes[ HITBOX_RIGHT_HAND ].y )
		};

		const D3DXVECTOR2 vecTorso[ ] // 5
		{
			D3DXVECTOR2( vecHitboxes[ HITBOX_PELVIS ].x, vecHitboxes[ HITBOX_PELVIS ].y ),
			D3DXVECTOR2( vecHitboxes[ HITBOX_CHEST ].x, vecHitboxes[ HITBOX_CHEST ].y ),
			D3DXVECTOR2( vecHitboxes[ HITBOX_UPPER_CHEST ].x, vecHitboxes[ HITBOX_UPPER_CHEST ].y ),
			D3DXVECTOR2( vecHitboxes[ HITBOX_NECK ].x, vecHitboxes[ HITBOX_NECK ].y ),
			D3DXVECTOR2( vecHitboxes[ HITBOX_HEAD ].x, vecHitboxes[ HITBOX_HEAD ].y )
		};

		const auto dwColor = clrSkeleton.GetARGB( );
		Drawing::Line( vecLegs, 7, esdEntityConfig->flSkeletonWidth, dwColor );
		Drawing::Line( vecArms, 7, esdEntityConfig->flSkeletonWidth, dwColor );
		Drawing::Line( vecTorso, 5, esdEntityConfig->flSkeletonWidth, dwColor );
	}
}
