/// Extra Sensory Drawing.cpp

#include "PX Precompiled.hpp"
#include "../../PX CSGO.hpp"

using namespace PX::Tools;
using namespace PX::Information;
using namespace PX::Drawing;
using namespace Pointers;

namespace PX::Features::Awareness
{
	auto esdConfig = &_Settings._Awareness._ExtraSensoryDrawing;
	auto esdEntityConfig = &esdConfig->_Players[ TEAM ];
	CBasePlayer* pLocalPlayer = nullptr;
	PX_DEF iMaxHealth = 100;

	enum
	{
		BOTTOMRIGHT,
		BOTTOMLEFT,
		TOPRIGHT,
		TOPLEFT
	};

	struct
	{
		CBaseEntity* pEntity;
		bool bTeammate = false, bIsPlayer = false;
		int iSettingIndex = 0;
		Vector vecLocation = Vector( );
		EClassID cClass = CLASSID_MAX;
		int iState = STATE_VISIBLE;
		int iHealth = 0;
		Vector vecBoundingBoxCorners[ 4 ] { };
		Vector vecWorldBoundingBoxCorners[ 4 ] { };
		bool bBoxInSight = true;
	} info;

	void PX_API CalculateBoundingBox( );
	void PX_API Box( );
	void PX_API SnapLine( );
	void PX_API ViewLine( );
	void PX_API Skeleton( );
	void PX_API Information( );

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
					info.iHealth = reinterpret_cast< CBasePlayer* >( pEntity )->m_iHealth( );
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

			CalculateBoundingBox( );
			Box( );
			SnapLine( );
			ViewLine( );
			Skeleton( );
			Information( );
		}
	}

	PX_EXT PX_INL void PX_API CalculateBoundingBox( )
	{
		Vector vecPoints[ ] { info.vecLocation, info.vecLocation, info.vecLocation, info.vecLocation };
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
		info.bBoxInSight = true;
		for ( auto i = 0; i < 4; i++ )
		{
			vecPoints[ i ].Rotate2D( flRotation, vecRotationPoint );
			if ( !WorldToScreen( vecPoints[ i ], info.vecBoundingBoxCorners[ i ] ) )
				info.bBoxInSight = false;
		}
		memcpy( info.vecWorldBoundingBoxCorners, vecPoints, sizeof( Vector ) * 4 );
	}

	PX_EXT PX_INL void PX_API Box( )
	{
		if ( esdEntityConfig->iBoxMode == BOX_NONE || !info.bBoxInSight )
			return;
		const auto clrBox = esdEntityConfig->seqBox[ info.iState ].GetCurrentColor( ),
					clrFill = esdEntityConfig->bHealthBasedFillColor ? color_t( ) : esdEntityConfig->seqFill[ info.iState ].GetCurrentColor( ),
					clrBottom = esdEntityConfig->bHealthBasedFillColor ? esdEntityConfig->seqHealthFill[ 0 ][ info.iState ].GetCurrentColor( ) : color_t( ),
					clrTop = esdEntityConfig->bHealthBasedFillColor ? esdEntityConfig->seqHealthFill[ 1 ][ info.iState ].GetCurrentColor( ) : color_t( );
		if ( clrBox.a == 0 && esdEntityConfig->bHealthBasedFillColor ? clrBottom.a == 0 && clrTop.a == 0 : clrFill.a == 0 )
			return;

		if ( esdEntityConfig->bThreeDimensional ) // 3d box
		{
			
		}
		else // 2d box
		{
			const D3DXVECTOR2 vecScreenPoints[ ]
			{
				D3DXVECTOR2( info.vecBoundingBoxCorners[ BOTTOMRIGHT ].x, info.vecBoundingBoxCorners[ BOTTOMRIGHT ].y ),
				D3DXVECTOR2( info.vecBoundingBoxCorners[ BOTTOMLEFT ].x, info.vecBoundingBoxCorners[ BOTTOMLEFT ].y ),
				D3DXVECTOR2( info.vecBoundingBoxCorners[ TOPLEFT ].x, info.vecBoundingBoxCorners[ TOPLEFT ].y ),
				D3DXVECTOR2( info.vecBoundingBoxCorners[ TOPRIGHT ].x, info.vecBoundingBoxCorners[ TOPRIGHT ].y ),
				D3DXVECTOR2( info.vecBoundingBoxCorners[ BOTTOMRIGHT ].x, info.vecBoundingBoxCorners[ BOTTOMRIGHT ].y )
			};

			if ( esdEntityConfig->bFill )
			{
				vertex_t vtxFillPoints[ 4 ];
				if ( esdEntityConfig->bHealthBasedFillColor )
				{
					const auto flZDifference = ( info.vecWorldBoundingBoxCorners[ TOPLEFT ].z - info.vecWorldBoundingBoxCorners[ BOTTOMLEFT ].z ) * ( float( info.iHealth ) / float( iMaxHealth ) );
					auto vecMiddleLeft = info.vecWorldBoundingBoxCorners[ BOTTOMLEFT ],
						vecMiddleRight = info.vecWorldBoundingBoxCorners[ BOTTOMRIGHT ];
					vecMiddleLeft.z += flZDifference;
					vecMiddleRight.z += flZDifference;
					Vector vecScreenMiddleLeft, vecScreenMiddleRight;
					const auto dwBottom = clrBottom.GetARGB( );

					WorldToScreen( vecMiddleLeft, vecScreenMiddleLeft );
					WorldToScreen( vecMiddleRight, vecScreenMiddleRight );

					if ( info.iHealth < iMaxHealth )
					{
						const auto dwTop = clrTop.GetARGB( );
						vtxFillPoints[ 0 ] = vertex_t( info.vecBoundingBoxCorners[ TOPLEFT ].x, info.vecBoundingBoxCorners[ TOPLEFT ].y, esdEntityConfig->bSolidHealthFill ? dwTop : 0 );
						vtxFillPoints[ 1 ] = vertex_t( info.vecBoundingBoxCorners[ TOPRIGHT ].x, info.vecBoundingBoxCorners[ TOPRIGHT ].y, esdEntityConfig->bSolidHealthFill ? dwTop : 0 );
						vtxFillPoints[ 2 ] = vertex_t( vecScreenMiddleRight.x, vecScreenMiddleRight.y, dwTop );
						vtxFillPoints[ 3 ] = vertex_t( vecScreenMiddleLeft.x, vecScreenMiddleLeft.y, dwTop );
						Drawing::Polygon( vtxFillPoints, 4, 2 );
					}

					vtxFillPoints[ 0 ] = vertex_t( vecScreenMiddleLeft.x, vecScreenMiddleLeft.y, dwBottom );
					vtxFillPoints[ 1 ] = vertex_t( vecScreenMiddleRight.x, vecScreenMiddleRight.y, dwBottom );
					vtxFillPoints[ 2 ] = vertex_t( info.vecBoundingBoxCorners[ BOTTOMRIGHT ].x, info.vecBoundingBoxCorners[ BOTTOMRIGHT ].y, esdEntityConfig->bSolidHealthFill ? dwBottom : 0 );
					vtxFillPoints[ 3 ] = vertex_t( info.vecBoundingBoxCorners[ BOTTOMLEFT ].x, info.vecBoundingBoxCorners[ BOTTOMLEFT ].y, esdEntityConfig->bSolidHealthFill ? dwBottom : 0 );
					Drawing::Polygon( vtxFillPoints, 4, 2 );
				}
				else
				{
					const auto dwColor = clrFill.GetARGB( );
					vtxFillPoints[ 0 ] = vertex_t( info.vecBoundingBoxCorners[ TOPLEFT ].x, info.vecBoundingBoxCorners[ TOPLEFT ].y, dwColor );
					vtxFillPoints[ 1 ] = vertex_t( info.vecBoundingBoxCorners[ TOPRIGHT ].x, info.vecBoundingBoxCorners[ TOPRIGHT ].y, dwColor );
					vtxFillPoints[ 2 ] = vertex_t( info.vecBoundingBoxCorners[ BOTTOMRIGHT ].x, info.vecBoundingBoxCorners[ BOTTOMRIGHT ].y, dwColor );
					vtxFillPoints[ 3 ] = vertex_t( info.vecBoundingBoxCorners[ BOTTOMLEFT ].x, info.vecBoundingBoxCorners[ BOTTOMLEFT ].y, dwColor );
					Drawing::Polygon( vtxFillPoints, 4, 2 );
				}
			}
			Line( vecScreenPoints, 5, 2, clrBox.GetARGB( ) );
		}
	}

	PX_EXT PX_INL void PX_API SnapLine( )
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

		Line( vecScreenPoints, 2, esdEntityConfig->flSnaplineWidth, clrSnapLine.GetARGB( ) );
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

		Line( vecScreenPoints, 2, esdEntityConfig->flViewLineWidth, dwColor );

		vertex_t vtxBox[ ]
		{
			vertex_t( vecEnd.x - flBoxSize, vecEnd.y - flBoxSize, dwColor ),
			vertex_t( vecEnd.x + flBoxSize, vecEnd.y - flBoxSize, dwColor ),
			vertex_t( vecEnd.x + flBoxSize, vecEnd.y + flBoxSize, dwColor ),
			vertex_t( vecEnd.x - flBoxSize, vecEnd.y + flBoxSize, dwColor )
		};
		Polygon( vtxBox, 4, 2 );
	}

	PX_EXT PX_INL void PX_API Skeleton( )
	{
		constexpr bool bUsedBone[ HITBOX_MAX ]
		{
			true,
			true,
			true,
			false,
			false,
			true,
			true,
			true,
			true,
			true,
			true,
			true,
			true,
			true,
			true,
			true,
			true,
			true,
			true
		};

		if ( !esdEntityConfig->bSkeleton )
			return;

		const auto clrSkeleton = esdEntityConfig->seqSkeleton[ info.iState ].GetCurrentColor( );
		if ( clrSkeleton.a == 0 )
			return;

		Vector vecHitboxes[ HITBOX_MAX ];
		for ( auto e = int( HITBOX_HEAD ); e < HITBOX_MAX; e++ )
			if ( bUsedBone[ e ] && !WorldToScreen( reinterpret_cast< CBasePlayer* >( info.pEntity )->GetHitboxPosition( EHitbox( e ) ), vecHitboxes[ e ] ) )
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
		Line( vecLegs, 7, esdEntityConfig->flSkeletonWidth, dwColor );
		Line( vecArms, 7, esdEntityConfig->flSkeletonWidth, dwColor );
		Line( vecTorso, 5, esdEntityConfig->flSkeletonWidth, dwColor );
	}

	PX_EXT PX_INL void PX_API Information( )
	{
		if ( !esdEntityConfig->bShowInformation || !info.bBoxInSight )
			return;
		const auto clrInformation = esdEntityConfig->seqInformation[ info.iState ].GetCurrentColor( );
		if ( clrInformation.a == 0 )
			return;
		const auto clrOutline = esdEntityConfig->bInformationOutline ? esdEntityConfig->seqInformationOutline[ info.iState ].GetCurrentColor( ) : color_t( );
		const auto bDoOutline = esdEntityConfig->bInformationOutline && clrOutline.a != 0;
		const auto dwOutline = bDoOutline ? clrOutline.GetARGB( ) : 0;
		const auto dwColor = clrInformation.GetARGB( );
		Vector vecInformationStart;
		DWORD dwAlignment { };
		auto flPadding = 3.f;
		auto flTextHeight = 16.f;
		auto bSmartAlign = false;

		switch ( esdEntityConfig->iInformationAlignment )
		{
			case ALIGNMENT_LEFT:
			{
				vecInformationStart = info.vecBoundingBoxCorners[ TOPLEFT ];
				vecInformationStart.x -= flPadding;
				dwAlignment = DT_RIGHT | DT_NOCLIP;
			}
			break;

			case ALIGNMENT_TOP:
			{
				vecInformationStart = ( info.vecBoundingBoxCorners[ TOPLEFT ] + info.vecBoundingBoxCorners[ TOPRIGHT ] ) / 2.f;
				dwAlignment = DT_CENTER | DT_NOCLIP;
				flPadding *= -1.f;
				flTextHeight *= -1.f; // go backwards.
				vecInformationStart.y += flPadding + flTextHeight;
			}
			break;

			case ALIGNMENT_RIGHT:
			{
				vecInformationStart = info.vecBoundingBoxCorners[ TOPRIGHT ];
				vecInformationStart.x += flPadding;
				dwAlignment = DT_LEFT | DT_NOCLIP;
			}
			break;

			case ALIGNMENT_BOTTOM:
			{
				vecInformationStart = ( info.vecBoundingBoxCorners[ BOTTOMLEFT ] + info.vecBoundingBoxCorners[ BOTTOMRIGHT ] ) / 2.f;
				dwAlignment = DT_CENTER | DT_NOCLIP;
			}
			break;

			default:
			{
				bSmartAlign = true;
			}
				break;

		}

		if ( esdEntityConfig->bShowHealth )
		{
			if ( esdEntityConfig->bHealthBar )
			{
				const auto clrBottom = esdEntityConfig->seqHealthBar[ 0 ][ info.iState ].GetCurrentColor( );
				const auto clrTop = esdEntityConfig->seqHealthBar[ 1 ][ info.iState ].GetCurrentColor( );

				if ( clrBottom.a != 0 && clrTop.a != 0 )
				{
					constexpr auto flHealthbarWidth = -5.f;
					const auto dwBottom = clrBottom.GetARGB( );
					const auto dwTop = clrTop.GetARGB( );
					vertex_t vtxTop[ 4 ], vtxBottom[ 4 ];
					Vector vecBar[ 4 ];
					const auto flHealthRatio = float( info.iHealth ) / float( iMaxHealth );
					auto fl = 23.f;

					Vector vecPoints[ ] { info.vecLocation, info.vecLocation, info.vecLocation, info.vecLocation };
					const Vector2D vecRotationPoint { info.vecLocation.x, info.vecLocation.y };
					const auto vecViewOffset = reinterpret_cast< CBasePlayer* >( info.pEntity )->m_vecViewOffset( );
					const auto flRotation = pClientState->viewangles.y - ( pClientState->viewangles.y -
																		   CalcAngle( pLocalPlayer->GetViewPosition( ), reinterpret_cast< CBasePlayer* >( info.pEntity )->GetViewPosition( ) ).y );
					auto fl2 = 13.f + vecViewOffset.z;
					vertex_t vtxOutline[ 4 ];

					switch ( esdEntityConfig->iInformationAlignment )
					{
						case ALIGNMENT_RIGHT:
						{
							fl = -28.f;
						}
						case ALIGNMENT_LEFT:
						{
							vecPoints[ BOTTOMRIGHT ].y += fl; // Bottom right
							vecPoints[ BOTTOMRIGHT ].z -= 5.f;
							vecPoints[ BOTTOMLEFT ].y += fl - flHealthbarWidth; // Bottom left
							vecPoints[ BOTTOMLEFT ].z -= 5.f;
							vecPoints[ TOPRIGHT ].y += fl; // Top right
							vecPoints[ TOPRIGHT ].z = info.vecLocation.z + vecViewOffset.z + 10.f;
							vecPoints[ TOPLEFT ].y += fl - flHealthbarWidth; // Top left
							vecPoints[ TOPLEFT ].z = info.vecLocation.z + vecViewOffset.z + 10.f;

							for ( auto i = 0; i < 4; i++ )
							{
								vecPoints[ i ].Rotate2D( flRotation, vecRotationPoint );
								WorldToScreen( vecPoints[ i ], vecBar[ i ] );
							}

							if ( flHealthRatio != 1.f )
							{
								const auto flZDifference = ( vecPoints[ TOPLEFT ].z - vecPoints[ BOTTOMLEFT ].z ) * flHealthRatio;
								auto vecMiddleLeft = vecPoints[ BOTTOMLEFT ],
									vecMiddleRight = vecPoints[ BOTTOMRIGHT ];
								vecMiddleLeft.z += flZDifference;
								vecMiddleRight.z += flZDifference;

								Vector vecScreenMiddleLeft, vecScreenMiddleRight;
								WorldToScreen( vecMiddleLeft, vecScreenMiddleLeft );
								WorldToScreen( vecMiddleRight, vecScreenMiddleRight );

								vtxTop[ 0 ] = vertex_t( vecBar[ TOPLEFT ].x, vecBar[ TOPLEFT ].y, dwTop );
								vtxTop[ 1 ] = vertex_t( vecBar[ TOPRIGHT ].x, vecBar[ TOPRIGHT ].y, dwTop );
								vtxTop[ 2 ] = vertex_t( vecScreenMiddleRight.x, vecScreenMiddleRight.y, dwTop );
								vtxTop[ 3 ] = vertex_t( vecScreenMiddleLeft.x, vecScreenMiddleLeft.y, dwTop );

								vtxBottom[ 0 ] = vertex_t( vecScreenMiddleLeft.x, vecScreenMiddleLeft.y, dwBottom );
								vtxBottom[ 1 ] = vertex_t( vecScreenMiddleRight.x, vecScreenMiddleRight.y, dwBottom );
								vtxBottom[ 2 ] = vertex_t( vecBar[ BOTTOMRIGHT ].x, vecBar[ BOTTOMRIGHT ].y, dwBottom );
								vtxBottom[ 3 ] = vertex_t( vecBar[ BOTTOMLEFT ].x, vecBar[ BOTTOMLEFT ].y, dwBottom );

								if ( bDoOutline )
								{
									const auto uSize = sizeof( vertex_t ) * 2u;
									memcpy( vtxOutline, vtxTop, uSize );
									memcpy( &vtxOutline[ 2 ], &vtxBottom[ 2 ], uSize );
								}
							}
							else if ( bDoOutline )
							{
								vtxOutline[ 0 ] = vertex_t( vecBar[ TOPLEFT ].x, vecBar[ TOPLEFT ].y, 0 );
								vtxOutline[ 1 ] = vertex_t( vecBar[ TOPRIGHT ].x, vecBar[ TOPRIGHT ].y, 0 );
								vtxOutline[ 2 ] = vertex_t( vecBar[ BOTTOMRIGHT ].x, vecBar[ BOTTOMRIGHT ].y, 0 );
								vtxOutline[ 3 ] = vertex_t( vecBar[ BOTTOMLEFT ].x, vecBar[ BOTTOMLEFT ].y, 0 );
							}

							if ( esdEntityConfig->iInformationAlignment == ALIGNMENT_LEFT )
							{
								vecInformationStart = vecBar[ TOPLEFT ];
								vecInformationStart.x -= flPadding;
							}
							else
							{
								vecInformationStart = vecBar[ TOPRIGHT ];
								vecInformationStart.x += flPadding;
							}
						}
						break;

						case ALIGNMENT_BOTTOM:
						{
							fl2 = -8.f + flHealthbarWidth;
						}
						case ALIGNMENT_TOP:
						{
							vecPoints[ BOTTOMRIGHT ].y -= 20.f; // Bottom right
							vecPoints[ BOTTOMRIGHT ].z += fl2;
							vecPoints[ BOTTOMLEFT ].y += 20.f; // Bottom left
							vecPoints[ BOTTOMLEFT ].z += fl2;
							vecPoints[ TOPRIGHT ].y -= 20.f; // Top right
							vecPoints[ TOPRIGHT ].z += fl2 - flHealthbarWidth;
							vecPoints[ TOPLEFT ].y += 20.f; // Top left
							vecPoints[ TOPLEFT ].z += fl2 - flHealthbarWidth;

							if ( flHealthRatio != 1.f )
							{
								const auto flYDifference = ( vecPoints[ TOPLEFT ].y - vecPoints[ TOPRIGHT ].y ) * ( 1.f - flHealthRatio );
								auto vecMiddleTop = vecPoints[ TOPLEFT ],
									vecMiddleBottom = vecPoints[ BOTTOMLEFT ];
								vecMiddleTop.y -= flYDifference;
								vecMiddleBottom.y -= flYDifference;

								for ( auto i = 0; i < 4; i++ )
								{
									vecPoints[ i ].Rotate2D( flRotation, vecRotationPoint );
									WorldToScreen( vecPoints[ i ], vecBar[ i ] );
								}

								vecMiddleTop.Rotate2D( flRotation, vecRotationPoint );
								vecMiddleBottom.Rotate2D( flRotation, vecRotationPoint );
								Vector vecScreenMiddleTop, vecScreenMiddleBottom;
								WorldToScreen( vecMiddleTop, vecScreenMiddleTop );
								WorldToScreen( vecMiddleBottom, vecScreenMiddleBottom );

								vtxTop[ 0 ] = vertex_t( vecBar[ TOPLEFT ].x, vecBar[ TOPLEFT ].y, dwTop );
								vtxTop[ 1 ] = vertex_t( vecScreenMiddleTop.x, vecScreenMiddleTop.y, dwTop );
								vtxTop[ 2 ] = vertex_t( vecScreenMiddleBottom.x, vecScreenMiddleBottom.y, dwTop );
								vtxTop[ 3 ] = vertex_t( vecBar[ BOTTOMLEFT ].x, vecBar[ BOTTOMLEFT ].y, dwTop );

								vtxBottom[ 0 ] = vertex_t( vecScreenMiddleTop.x, vecScreenMiddleTop.y, dwBottom );
								vtxBottom[ 1 ] = vertex_t( vecBar[ TOPRIGHT ].x, vecBar[ TOPRIGHT ].y, dwBottom );
								vtxBottom[ 2 ] = vertex_t( vecBar[ BOTTOMRIGHT ].x, vecBar[ BOTTOMRIGHT ].y, dwBottom );
								vtxBottom[ 3 ] = vertex_t( vecScreenMiddleBottom.x, vecScreenMiddleBottom.y, dwBottom );
							}
							else
								for ( auto i = 0; i < 4; i++ )
								{
									vecPoints[ i ].Rotate2D( flRotation, vecRotationPoint );
									WorldToScreen( vecPoints[ i ], vecBar[ i ] );
								}

							if ( esdEntityConfig->iInformationAlignment == ALIGNMENT_BOTTOM )
							{
								vecInformationStart.x = ( vecBar[ BOTTOMRIGHT ].x + vecBar[ BOTTOMLEFT ].x ) / 2.f;
								vecInformationStart.y = ( vecBar[ BOTTOMRIGHT].y + vecBar[ BOTTOMLEFT ].y ) / 2.f + flPadding;
							}
							else
							{
								vecInformationStart.x = ( vecBar[ TOPRIGHT ].x + vecBar[ TOPLEFT ].x ) / 2.f;
								vecInformationStart.y = ( vecBar[ TOPRIGHT ].y + vecBar[ TOPLEFT ].y ) / 2.f + flTextHeight;
							}

							if ( bDoOutline )
								for ( auto i = 0; i < 4; i++ )
								{
									vtxOutline[ 0 ].flVectors[ 0 ] = vecBar[ TOPLEFT ].x;
									vtxOutline[ 0 ].flVectors[ 1 ] = vecBar[ TOPLEFT ].y;
									vtxOutline[ 1 ].flVectors[ 0 ] = vecBar[ TOPRIGHT ].x;
									vtxOutline[ 1 ].flVectors[ 1 ] = vecBar[ TOPRIGHT ].y;
									vtxOutline[ 2 ].flVectors[ 0 ] = vecBar[ BOTTOMRIGHT ].x;
									vtxOutline[ 2 ].flVectors[ 1 ] = vecBar[ BOTTOMRIGHT ].y;
									vtxOutline[ 3 ].flVectors[ 0 ] = vecBar[ BOTTOMLEFT ].x;
									vtxOutline[ 3 ].flVectors[ 1 ] = vecBar[ BOTTOMLEFT ].y;
								}
						}
					}
					if ( bDoOutline )
					{
						vtxOutline[ 0 ].flVectors[ 0 ] -= 1.f;
						vtxOutline[ 0 ].flVectors[ 1 ] -= 1.f;
						vtxOutline[ 1 ].flVectors[ 0 ] += 1.f;
						vtxOutline[ 1 ].flVectors[ 1 ] -= 1.f;
						vtxOutline[ 2 ].flVectors[ 0 ] += 1.f;
						vtxOutline[ 2 ].flVectors[ 1 ] += 1.f;
						vtxOutline[ 3 ].flVectors[ 0 ] -= 1.f;
						vtxOutline[ 3 ].flVectors[ 1 ] += 1.f;
						vtxOutline[ 0 ].dwColor = vtxOutline[ 1 ].dwColor = vtxOutline[ 2 ].dwColor = vtxOutline[ 3 ].dwColor = dwOutline;
						Polygon( vtxOutline, 4, 2 );
					}
					if( flHealthRatio != 1.f )
						Polygon( vtxTop, 4, 2 );
					else
					{
						vtxBottom[ 0 ] = vertex_t( vecBar[ TOPLEFT ].x, vecBar[ TOPLEFT ].y, dwBottom );
						vtxBottom[ 1 ] = vertex_t( vecBar[ TOPRIGHT ].x, vecBar[ TOPRIGHT ].y, dwBottom );
						vtxBottom[ 2 ] = vertex_t( vecBar[ BOTTOMRIGHT ].x, vecBar[ BOTTOMRIGHT ].y, dwBottom );
						vtxBottom[ 3 ] = vertex_t( vecBar[ BOTTOMLEFT ].x, vecBar[ BOTTOMLEFT ].y, dwBottom );
					}
					Polygon( vtxBottom, 4, 2 );
				}
			}
			else
			{
				Text( ED3DFont::FONT_TAHOMA, vecInformationStart.x, vecInformationStart.y, ( std::to_wstring( info.iHealth ) + PX_XOR( L" HP" ) ).c_str( ), bDoOutline, dwAlignment, dwColor, dwOutline );
				vecInformationStart.y += flTextHeight + flPadding;
			}
		}

		if( esdEntityConfig->bShowName )
		{
			constexpr auto zPlayerNameMaxLength = std::size_t( 128u );
			wchar_t wszName[ zPlayerNameMaxLength ];

			if ( info.bIsPlayer )
				wcscpy( wszName, string_cast< std::wstring >( std::string( reinterpret_cast< CBasePlayer* >( info.pEntity )->GetPlayerInformation( ).szName ) ).c_str( ) );
			else
				return;
			Text( ED3DFont::FONT_TAHOMA, vecInformationStart.x, vecInformationStart.y, wszName, bDoOutline, dwAlignment, dwColor, dwOutline );
			vecInformationStart.y += 16.f + flPadding;
		}

		if ( esdEntityConfig->bShowRank )
		{

		}

		if ( esdEntityConfig->bShowWeapon )
		{

		}
	}
}
