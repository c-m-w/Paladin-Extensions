/// Information.cpp

#include "PX Precompiled.hpp"
#include "../../PX CSGO.hpp"
#include "../../../PX Debug Injector/PX Debug Injector.hpp"

using namespace PX::Tools;
using namespace PX::Information;
using namespace PX::Drawing;
using namespace Pointers;

namespace PX::Features::Awareness
{
	CBasePlayer* pLocalPlayer = nullptr;

	// todo life checks

	enum
	{
		TOPLEFT,
		TOPRIGHT,
		BOTTOMLEFT,
		BOTTOMRIGHT,
		TLRB_MAX,
		BASE = 0,
		SECONDARY,
		FC_MAX
	};

	struct _
	{
		CBaseEntity* p = nullptr;
		bool operator!( ) const
		{
			return p == nullptr;
		}

		_& operator=( const entity_ptr_t p )
		{
			this->p = p; return *this;
		}

		CBaseEntity* operator->( ) const
		{
			return p;
		}
		template< typename _t > _t* operator->( ) const
		{
			return reinterpret_cast< _t* >( p );
		}

		bool Friendly( ) const
		{
			return p->IsPlayer( ) && p->m_iTeamNum( ) == pLocalPlayer->m_iTeamNum( );
		}
		Vector vecBox[ FC_MAX ][ TLRB_MAX ] { { { }, { }, { }, { } }, { { }, { }, { }, { } } };
		bool bBoxVisibility = false;
		EState enumExistence = STATE_MAX;
	} pEntity;

	bool bVariantID = false; // false is ent, true is player.
	void* _cfg;

	// todo
	static void PX_API DrawPlayerBone( )
	{
		auto& cfg = *reinterpret_cast< settings_t::awareness_t::statistics_t::player_t* >( _cfg );
		if ( !cfg.bBone )
			return;
		const auto clrBone = cfg.seqBone[ pEntity.enumExistence ].GetCurrentColor( );
		if ( clrBone.a == 0 )
			return;
		const auto clrBoneOutline = cfg.seqBoneOutline.GetCurrentColor( );

		int buf_[ 5 ][ 4 ] { { HITBOX_HEAD, HITBOX_NECK, HITBOX_UPPER_CHEST, HITBOX_LOWER_CHEST },
			{ HITBOX_UPPER_CHEST, HITBOX_RIGHT_UPPER_ARM, HITBOX_RIGHT_FOREARM, HITBOX_RIGHT_HAND },
			{ HITBOX_UPPER_CHEST, HITBOX_LEFT_UPPER_ARM, HITBOX_LEFT_FOREARM, HITBOX_LEFT_HAND },
			{ HITBOX_LOWER_CHEST, HITBOX_RIGHT_THIGH, HITBOX_RIGHT_CALF, HITBOX_RIGHT_FOOT },
			{ HITBOX_LOWER_CHEST, HITBOX_LEFT_THIGH, HITBOX_LEFT_CALF, HITBOX_LEFT_FOOT } };

		for ( auto &buf__: buf_ )
			for ( int i = 1; i < 4; i++ )
			{
				Vector _buf[ ] = { { }, { } };
				D3DXVECTOR2 buf[ ] = { { }, { } };

				_buf[ 0 ] = player_ptr_t( pEntity.p )->GetHitboxPosition( buf__[ i - 1 ] );
				WorldToScreen( _buf[ 0 ], _buf[ 1 ] );
				buf[ 0 ] = { _buf[ 1 ].x, _buf[ 1 ].y };

				_buf[ 0 ] = player_ptr_t( pEntity.p )->GetHitboxPosition( buf__[ i ] );
				WorldToScreen( _buf[ 0 ], _buf[ 1 ] );
				buf[ 1 ] = { _buf[ 1 ].x, _buf[ 1 ].y };

				Line( buf, 2, cfg.flBoneThickness, clrBone.GetARGB( ) );
				!!cfg.bBoneOutline && clrBoneOutline.a != 0 ? Line( buf, 2, cfg.flBoneThickness, clrBone.GetARGB( ) ) : ( void )0;
			}
	}

	// todo color circle end needs variable for menu
	static void PX_API DrawPlayerOrientation( )
	{
		auto &cfg = *reinterpret_cast< settings_t::awareness_t::statistics_t::player_t* >( _cfg );
		if ( !cfg.bOrientation )
			return;
		auto basdi = cfg.seqOrientation[ pEntity.enumExistence ].GetCurrentColor( );
		if ( basdi.a == 0 )
			return;
		auto buf = player_ptr_t( pEntity.p )->GetHitboxPosition( HITBOX_HEAD );
		const QAngle buff = player_ptr_t( pEntity.p )->m_angEyeAngles( );
		const Vector viewbuff { buff.pitch, buff.yaw, buff.roll };
		Vector viewscreenapsodiaospfjlkosdfg;
		WorldToScreen( player_ptr_t( pEntity.p )->TraceRayFromView( ).endpos, viewscreenapsodiaospfjlkosdfg );

		Vector viewScreenCOnveraskjrt;
		WorldToScreen( buf, viewScreenCOnveraskjrt );
		D3DXVECTOR2 bufff[ ] {
			{ viewscreenapsodiaospfjlkosdfg.x, viewscreenapsodiaospfjlkosdfg.y },
			{ viewScreenCOnveraskjrt.x, viewScreenCOnveraskjrt.y }
		};
		Line( bufff, 2, cfg.flOrientationThickness, basdi.GetARGB( ) );
		Circle( bufff[ 0 ], 3.f, 0, 0xFFFFFFFF, 7 );
		if ( !cfg.bOrientationOutline )
			return;
		auto askldjaskld = cfg.seqOrientationOutline.GetCurrentColor( );
		if ( askldjaskld.a == 0 )
			return;
		Line( bufff, 2, cfg.flOrientationOutlineThickness, askldjaskld.GetARGB( ) );
	}

	// review code for some 2d stuff, it's just cold pasted from cole's original esd
	static void PX_API CalculateBoundingBox( )
	{
		auto& cfg = *reinterpret_cast< settings_t::awareness_t::statistics_t::a_statistics_base* >( _cfg );

		if ( !cfg.bDimesMode ) // 2d
		{
			pEntity.bBoxVisibility = true;
			if ( !cfg.bDisplayMode ) // screen
			{
				// todo wip, will make this bone/hitbox based...
				const auto pCollidable = pEntity->GetCollideable( );
				const auto vecMinimum = pCollidable->OBBMins( );
				const auto vecMaximum = pCollidable->OBBMaxs( );
				const auto mtxTransformation = pEntity->m_rgflCoordinateFrame( );

				Vector vecPoints[ ]
				{
					Vector( vecMinimum.x, vecMinimum.y, vecMinimum.z ),
					Vector( vecMinimum.x, vecMaximum.y, vecMinimum.z ),
					Vector( vecMaximum.x, vecMaximum.y, vecMinimum.z ),
					Vector( vecMaximum.x, vecMinimum.y, vecMinimum.z ),
					Vector( vecMaximum.x, vecMaximum.y, vecMaximum.z ),
					Vector( vecMinimum.x, vecMaximum.y, vecMaximum.z ),
					Vector( vecMinimum.x, vecMinimum.y, vecMaximum.z ),
					Vector( vecMaximum.x, vecMinimum.y, vecMaximum.z )
				}, vecTransformedPoints[ 8 ], vecScreenPoints[ 8 ];

				for ( auto i = 0; i < 8; i++ )
				{
					TransformVector( vecPoints[ i ], mtxTransformation, vecTransformedPoints[ i ] );
					pEntity.bBoxVisibility &= WorldToScreen( vecTransformedPoints[ i ], vecScreenPoints[ i ] );
				}

				auto flTop = vecScreenPoints[ 0 ].y, flRight = vecScreenPoints[ 0 ].x, flBottom = vecScreenPoints[ 0 ].y, flLeft = vecScreenPoints[ 0 ].x;
				for ( const auto& vecScreenPoint : vecScreenPoints )
				{
					if ( flLeft > vecScreenPoint.x )
						flLeft = vecScreenPoint.x;
					if ( flTop < vecScreenPoint.y )
						flTop = vecScreenPoint.y;
					if ( flRight < vecScreenPoint.x )
						flRight = vecScreenPoint.x;
					if ( flBottom > vecScreenPoint.y )
						flBottom = vecScreenPoint.y;
				}

				pEntity.vecBox[ BASE ][ TOPLEFT ] = { flLeft, flBottom, 0.f };
				pEntity.vecBox[ BASE ][ TOPRIGHT ] = { flRight, flBottom, 0.f };
				pEntity.vecBox[ BASE ][ BOTTOMRIGHT ] = { flRight, flTop, 0.f };
				pEntity.vecBox[ BASE ][ BOTTOMLEFT ] = { flLeft, flTop, 0.f };

			//	auto& vecOrigin = pEntity->m_vecOrigin( );
			//	Vector min { }, max { };
			//	pEntity->GetRenderBounds( min, max );
			//	min += vecOrigin;
			//	max += vecOrigin;
			//
			//	WorldToScreen( min, pEntity.vecBox[ BASE ][ BOTTOMLEFT ] );
			//	WorldToScreen( max, pEntity.vecBox[ BASE ][ TOPRIGHT ] );
			//	pEntity.vecBox[ BASE ][ BOTTOMRIGHT ] = { pEntity.vecBox[ BASE ][ TOPRIGHT ].x, pEntity.vecBox[ BASE ][ BOTTOMLEFT ].y, 0.f };
			//	pEntity.vecBox[ BASE ][ TOPLEFT ] = { pEntity.vecBox[ BASE ][ BOTTOMLEFT ].x, pEntity.vecBox[ BASE ][ TOPRIGHT ].y, 0.f };
			}
			else // world
			{
				auto& vecOrigin = pEntity->m_vecOrigin( );
				for each ( auto& vecBox in pEntity.vecBox[ BASE ] )
					vecBox = vecOrigin;
				const Vector2D vecRotationPoint { vecOrigin.x, vecOrigin.y };
				const auto vecViewPosition = vecOrigin + player_ptr_t( pEntity.p )->m_vecViewOffset( );

				pEntity.vecBox[ BASE ][ BOTTOMRIGHT ].y -= 20.f; // Bottom right
				pEntity.vecBox[ BASE ][ BOTTOMRIGHT ].z -= 5.f;
				pEntity.vecBox[ BASE ][ BOTTOMLEFT ].y += 20.f; // Bottom left
				pEntity.vecBox[ BASE ][ BOTTOMLEFT ].z -= 5.f;
				pEntity.vecBox[ BASE ][ TOPRIGHT ].y -= 20.f; // Top right
				pEntity.vecBox[ BASE ][ TOPRIGHT ].z = vecViewPosition.z + 10.f;
				pEntity.vecBox[ BASE ][ TOPLEFT ].y += 20.f; // Top left
				pEntity.vecBox[ BASE ][ TOPLEFT ].z = vecViewPosition.z + 10.f;

				//const auto flRotation = pEntity.p->GetABSAngles( ).yaw;
				//const auto flRotation = pClientState->viewangles.y;
				const auto flRotation = pClientState->viewangles.y - ( pClientState->viewangles.y - CalcAngle( pLocalPlayer->GetViewPosition( ), player_ptr_t( pEntity.p )->GetViewPosition( ) ).y );

				for ( auto i = 0; i < TLRB_MAX; i++ )
				{
					pEntity.vecBox[ BASE ][ i ].Rotate2D( flRotation, vecRotationPoint );
					Vector buf;
					pEntity.bBoxVisibility &= WorldToScreen( pEntity.vecBox[ BASE ][ i ], buf );
					pEntity.vecBox[ BASE ][ i ] = buf;
				}
			}
		}
		else // 3d
		{
			pEntity.bBoxVisibility = false;

			auto& vecOrigin = pEntity->m_vecOrigin( );
			Vector vecPoints[ FC_MAX ][ TLRB_MAX ] { { vecOrigin, vecOrigin, vecOrigin, vecOrigin }, { } };
			const Vector2D vecRotationPoint { vecOrigin.x, vecOrigin.y };

			const auto vecViewPosition = bVariantID ? ( vecOrigin + player_ptr_t( pEntity.p )->m_vecViewOffset( ) ).z : 0.f;

			vecPoints[ BASE ][ TOPLEFT ].x -= 20.f;
			vecPoints[ BASE ][ TOPLEFT ].y += 20.f;
			vecPoints[ BASE ][ TOPLEFT ].z -= 5.f;
			vecPoints[ BASE ][ TOPRIGHT ].x += 20.f;
			vecPoints[ BASE ][ TOPRIGHT ].y += 20.f;
			vecPoints[ BASE ][ TOPRIGHT ].z -= 5.f;
			vecPoints[ BASE ][ BOTTOMLEFT ].x -= 20.f;
			vecPoints[ BASE ][ BOTTOMLEFT ].y -= 20.f;
			vecPoints[ BASE ][ BOTTOMLEFT ].z -= 5.f;
			vecPoints[ BASE ][ BOTTOMRIGHT ].x += 20.f;
			vecPoints[ BASE ][ BOTTOMRIGHT ].y -= 20.f;
			vecPoints[ BASE ][ BOTTOMRIGHT ].z -= 5.f;

			vecPoints[ SECONDARY ][ TOPLEFT ] = vecPoints[ BASE ][ TOPLEFT ];
			vecPoints[ SECONDARY ][ TOPLEFT ].z = vecViewPosition + 10.f;
			vecPoints[ SECONDARY ][ TOPRIGHT ] = vecPoints[ BASE ][ TOPRIGHT ];
			vecPoints[ SECONDARY ][ TOPRIGHT ].z = vecViewPosition + 10.f;
			vecPoints[ SECONDARY ][ BOTTOMLEFT ] = vecPoints[ BASE ][ BOTTOMLEFT ];
			vecPoints[ SECONDARY ][ BOTTOMLEFT ].z = vecViewPosition + 10.f;
			vecPoints[ SECONDARY ][ BOTTOMRIGHT ] = vecPoints[ BASE ][ BOTTOMRIGHT ];
			vecPoints[ SECONDARY ][ BOTTOMRIGHT ].z = vecViewPosition + 10.f;

			const auto flRotation = pEntity->GetABSAngles( ).yaw;

			for ( auto i = 0; i < TLRB_MAX; i++ )
			{
				vecPoints[ BASE ][ i ].Rotate2D( flRotation, vecRotationPoint );
				vecPoints[ SECONDARY ][ i ].Rotate2D( flRotation, vecRotationPoint );
				pEntity.bBoxVisibility |= pLocalPlayer->CanSeePosition( vecPoints[ BASE ][ i ], !!cfg.bSmokeCheck ) || pLocalPlayer->CanSeePosition( vecPoints[ SECONDARY ][ i ], !!cfg.bSmokeCheck );
			}
			memcpy( pEntity.vecBox, vecPoints, sizeof( Vector ) * 8 );
		}
	}

	static void PX_API DrawSnapline( )
	{
		if ( !pEntity.bBoxVisibility )
			return;

		auto& cfg = *reinterpret_cast< settings_t::awareness_t::statistics_t::a_statistics_base* >( _cfg );

		if ( !cfg.bSnapline )
			return;

		color_t clrSnapline;
		if ( bVariantID )
			clrSnapline = reinterpret_cast< settings_t::awareness_t::statistics_t::player_t* >( _cfg )->seqSnapline[ pEntity.enumExistence ].GetCurrentColor( );
		else
			clrSnapline = reinterpret_cast< settings_t::awareness_t::statistics_t::entity_t* >( _cfg )->seqSnapline[ pEntity.enumExistence ].GetCurrentColor( );
		if ( clrSnapline.a == 0 )
			return;

		enum
		{
			ORIGIN,
			DESTINATION,
			ORIGIN_DESTINATION_MAX
		};

		D3DXVECTOR2 vecSnapline[ ORIGIN_DESTINATION_MAX ] { };
		int iDimes[ 2 ];
		pEngineClient->GetScreenSize( iDimes[ 0 ], iDimes[ 1 ] );

		vecSnapline[ ORIGIN ].x = float( iDimes[ 0 ] ) / 2.f;
		vecSnapline[ ORIGIN ].y = !cfg.bSnaplineOrigin ? iDimes[ 1 ] : 0.f;

		if ( !cfg.bSnaplineDestination ) // bottom
		{
			vecSnapline[ DESTINATION ] = { pEntity.vecBox[ BASE ][ BOTTOMLEFT ].x, pEntity.vecBox[ BASE ][ BOTTOMLEFT ].y };
			vecSnapline[ DESTINATION ].x += ( pEntity.vecBox[ BASE ][ BOTTOMRIGHT ].x - pEntity.vecBox[ BASE ][ BOTTOMLEFT ].x ) / 2.f;
			vecSnapline[ DESTINATION ].y += ( pEntity.vecBox[ BASE ][ BOTTOMRIGHT ].y - pEntity.vecBox[ BASE ][ BOTTOMLEFT ].y ) / 2.f;
		}
		else // top
		{
			auto enumIndex = !cfg.bDimesMode ? BASE : SECONDARY;
			vecSnapline[ DESTINATION ] = { pEntity.vecBox[ enumIndex ][ TOPLEFT ].x, pEntity.vecBox[ BASE ][ TOPLEFT ].y };
			vecSnapline[ DESTINATION ].x += ( pEntity.vecBox[ enumIndex ][ TOPRIGHT ].x - pEntity.vecBox[ BASE ][ TOPLEFT ].x ) / 2.f;
			vecSnapline[ DESTINATION ].y += ( pEntity.vecBox[ enumIndex ][ TOPRIGHT ].y - pEntity.vecBox[ BASE ][ TOPLEFT ].y ) / 2.f;
		}

		if ( !!cfg.bSnaplineOutline )
		{
			const auto clrSnaplineOutline = cfg.seqSnaplineOutline.GetCurrentColor( );
			if ( clrSnaplineOutline.a != 0 )
				Line( vecSnapline, ORIGIN_DESTINATION_MAX, cfg.flSnaplineOutlineThickness, clrSnaplineOutline.GetARGB( ) );
		}

		Line( vecSnapline, ORIGIN_DESTINATION_MAX, cfg.flSnaplineThickness, clrSnapline.GetARGB( ) );
	}

	static void PX_API DrawBox( )
	{
		if ( !pEntity.bBoxVisibility )
			return;

		auto& cfg = *reinterpret_cast< settings_t::awareness_t::statistics_t::a_statistics_base* >( _cfg );

		if ( !cfg.bBox )
			return;

		color_t clrBox;
		if ( bVariantID )
			clrBox = reinterpret_cast< settings_t::awareness_t::statistics_t::player_t* >( _cfg )->seqSnapline[ pEntity.enumExistence ].GetCurrentColor( );
		else
			clrBox = reinterpret_cast< settings_t::awareness_t::statistics_t::entity_t* >( _cfg )->seqSnapline[ pEntity.enumExistence ].GetCurrentColor( );

		if ( clrBox.a == 0 )
			return;

		if ( !cfg.bDimesMode ) // 2d
		{
			D3DXVECTOR2 buf[ ] = { { }, { } };
			const auto clrBoxOutline = cfg.seqBoxOutline.GetCurrentColor( );

			buf[ 0 ] = { pEntity.vecBox[ BASE ][ TOPLEFT ].x, pEntity.vecBox[ BASE ][ TOPLEFT ].y };
			buf[ 1 ] = { pEntity.vecBox[ BASE ][ TOPRIGHT ].x, pEntity.vecBox[ BASE ][ TOPRIGHT ].y };
			!!cfg.bBoxOutline && clrBoxOutline.a != 0 ? Line( buf, 2, cfg.flBoxOutlineThickness, clrBoxOutline.GetARGB( ) ) : ( void )0;
			Line( buf, 2, cfg.flBoxThickness, clrBox.GetARGB( ) );
			buf[ 0 ] = { pEntity.vecBox[ BASE ][ TOPRIGHT ].x, pEntity.vecBox[ BASE ][ TOPRIGHT ].y };
			buf[ 1 ] = { pEntity.vecBox[ BASE ][ BOTTOMRIGHT ].x, pEntity.vecBox[ BASE ][ BOTTOMRIGHT ].y };
			!!cfg.bBoxOutline && clrBoxOutline.a != 0 ? Line( buf, 2, cfg.flBoxOutlineThickness, clrBoxOutline.GetARGB( ) ) : ( void )0;
			Line( buf, 2, cfg.flBoxThickness, clrBox.GetARGB( ) );
			buf[ 0 ] = { pEntity.vecBox[ BASE ][ BOTTOMRIGHT ].x, pEntity.vecBox[ BASE ][ BOTTOMRIGHT ].y };
			buf[ 1 ] = { pEntity.vecBox[ BASE ][ BOTTOMLEFT ].x, pEntity.vecBox[ BASE ][ BOTTOMLEFT ].y };
			!!cfg.bBoxOutline && clrBoxOutline.a != 0 ? Line( buf, 2, cfg.flBoxOutlineThickness, clrBoxOutline.GetARGB( ) ) : ( void )0;
			Line( buf, 2, cfg.flBoxThickness, clrBox.GetARGB( ) );
			buf[ 0 ] = { pEntity.vecBox[ BASE ][ BOTTOMLEFT ].x, pEntity.vecBox[ BASE ][ BOTTOMLEFT ].y };
			buf[ 1 ] = { pEntity.vecBox[ BASE ][ TOPLEFT ].x, pEntity.vecBox[ BASE ][ TOPLEFT ].y };
			!!cfg.bBoxOutline && clrBoxOutline.a != 0 ? Line( buf, 2, cfg.flBoxOutlineThickness, clrBoxOutline.GetARGB( ) ) : ( void )0;
			Line( buf, 2, cfg.flBoxThickness, clrBox.GetARGB( ) );
		}
		else // 3d
		{
			Vector _buf[ ] = { { }, { } };
			D3DXVECTOR2 buf[ ] = { { }, { } };
			const auto clrBoxOutline = cfg.seqBoxOutline.GetCurrentColor( );

			if ( !WorldToScreen( pEntity.vecBox[ BASE ][ TOPLEFT ], _buf[ 0 ] ) ) return;
			if ( !WorldToScreen( pEntity.vecBox[ BASE ][ TOPRIGHT ], _buf[ 1 ] ) ) return;
			buf[ 0 ] = { _buf[ 0 ].x, _buf[ 0 ].y };
			buf[ 1 ] = { _buf[ 1 ].x, _buf[ 1 ].y };
			!!cfg.bBoxOutline && clrBoxOutline.a != 0 ? Line( buf, 2, cfg.flBoxThickness, clrBox.GetARGB( ) ) : ( void )0;
			Line( buf, 2, cfg.flBoxThickness, clrBox.GetARGB( ) );
			if ( !WorldToScreen( pEntity.vecBox[ BASE ][ TOPRIGHT ], _buf[ 0 ] ) ) return;
			if ( !WorldToScreen( pEntity.vecBox[ BASE ][ BOTTOMRIGHT ], _buf[ 1 ] ) ) return;
			buf[ 0 ] = { _buf[ 0 ].x, _buf[ 0 ].y };
			buf[ 1 ] = { _buf[ 1 ].x, _buf[ 1 ].y };
			!!cfg.bBoxOutline && clrBoxOutline.a != 0 ? Line( buf, 2, cfg.flBoxThickness, clrBox.GetARGB( ) ) : ( void )0;
			Line( buf, 2, cfg.flBoxThickness, clrBox.GetARGB( ) );
			if ( !WorldToScreen( pEntity.vecBox[ BASE ][ BOTTOMRIGHT ], _buf[ 0 ] ) ) return;
			if ( !WorldToScreen( pEntity.vecBox[ BASE ][ BOTTOMLEFT ], _buf[ 1 ] ) ) return;
			buf[ 0 ] = { _buf[ 0 ].x, _buf[ 0 ].y };
			buf[ 1 ] = { _buf[ 1 ].x, _buf[ 1 ].y };
			!!cfg.bBoxOutline && clrBoxOutline.a != 0 ? Line( buf, 2, cfg.flBoxThickness, clrBox.GetARGB( ) ) : ( void )0;
			Line( buf, 2, cfg.flBoxThickness, clrBox.GetARGB( ) );
			if ( !WorldToScreen( pEntity.vecBox[ BASE ][ BOTTOMLEFT ], _buf[ 0 ] ) ) return;
			if ( !WorldToScreen( pEntity.vecBox[ BASE ][ TOPLEFT ], _buf[ 1 ] ) ) return;
			buf[ 0 ] = { _buf[ 0 ].x, _buf[ 0 ].y };
			buf[ 1 ] = { _buf[ 1 ].x, _buf[ 1 ].y };
			!!cfg.bBoxOutline && clrBoxOutline.a != 0 ? Line( buf, 2, cfg.flBoxThickness, clrBox.GetARGB( ) ) : ( void )0;
			Line( buf, 2, cfg.flBoxThickness, clrBox.GetARGB( ) );

			if ( !WorldToScreen( pEntity.vecBox[ SECONDARY ][ TOPLEFT ], _buf[ 0 ] ) ) return;
			if ( !WorldToScreen( pEntity.vecBox[ SECONDARY ][ TOPRIGHT ], _buf[ 1 ] ) ) return;
			buf[ 0 ] = { _buf[ 0 ].x, _buf[ 0 ].y };
			buf[ 1 ] = { _buf[ 1 ].x, _buf[ 1 ].y };
			!!cfg.bBoxOutline && clrBoxOutline.a != 0 ? Line( buf, 2, cfg.flBoxThickness, clrBox.GetARGB( ) ) : ( void )0;
			Line( buf, 2, cfg.flBoxThickness, clrBox.GetARGB( ) );
			if ( !WorldToScreen( pEntity.vecBox[ SECONDARY ][ TOPRIGHT ], _buf[ 0 ] ) ) return;
			if ( !WorldToScreen( pEntity.vecBox[ SECONDARY ][ BOTTOMRIGHT ], _buf[ 1 ] ) ) return;
			buf[ 0 ] = { _buf[ 0 ].x, _buf[ 0 ].y };
			buf[ 1 ] = { _buf[ 1 ].x, _buf[ 1 ].y };
			!!cfg.bBoxOutline && clrBoxOutline.a != 0 ? Line( buf, 2, cfg.flBoxThickness, clrBox.GetARGB( ) ) : ( void )0;
			Line( buf, 2, cfg.flBoxThickness, clrBox.GetARGB( ) );
			if ( !WorldToScreen( pEntity.vecBox[ SECONDARY ][ BOTTOMRIGHT ], _buf[ 0 ] ) ) return;
			if ( !WorldToScreen( pEntity.vecBox[ SECONDARY ][ BOTTOMLEFT ], _buf[ 1 ] ) ) return;
			buf[ 0 ] = { _buf[ 0 ].x, _buf[ 0 ].y };
			buf[ 1 ] = { _buf[ 1 ].x, _buf[ 1 ].y };
			!!cfg.bBoxOutline && clrBoxOutline.a != 0 ? Line( buf, 2, cfg.flBoxThickness, clrBox.GetARGB( ) ) : ( void )0;
			Line( buf, 2, cfg.flBoxThickness, clrBox.GetARGB( ) );
			if ( !WorldToScreen( pEntity.vecBox[ SECONDARY ][ BOTTOMLEFT ], _buf[ 0 ] ) ) return;
			if ( !WorldToScreen( pEntity.vecBox[ SECONDARY ][ TOPLEFT ], _buf[ 1 ] ) ) return;
			buf[ 0 ] = { _buf[ 0 ].x, _buf[ 0 ].y };
			buf[ 1 ] = { _buf[ 1 ].x, _buf[ 1 ].y };
			!!cfg.bBoxOutline && clrBoxOutline.a != 0 ? Line( buf, 2, cfg.flBoxThickness, clrBox.GetARGB( ) ) : ( void )0;
			Line( buf, 2, cfg.flBoxThickness, clrBox.GetARGB( ) );

			if ( !WorldToScreen( pEntity.vecBox[ BASE ][ TOPLEFT ], _buf[ 0 ] ) ) return;
			if ( !WorldToScreen( pEntity.vecBox[ SECONDARY ][ TOPLEFT ], _buf[ 1 ] ) ) return;
			buf[ 0 ] = { _buf[ 0 ].x, _buf[ 0 ].y };
			buf[ 1 ] = { _buf[ 1 ].x, _buf[ 1 ].y };
			!!cfg.bBoxOutline && clrBoxOutline.a != 0 ? Line( buf, 2, cfg.flBoxThickness, clrBox.GetARGB( ) ) : ( void )0;
			Line( buf, 2, cfg.flBoxThickness, clrBox.GetARGB( ) );
			if ( !WorldToScreen( pEntity.vecBox[ BASE ][ TOPRIGHT ], _buf[ 0 ] ) ) return;
			if ( !WorldToScreen( pEntity.vecBox[ SECONDARY ][ TOPRIGHT ], _buf[ 1 ] ) ) return;
			buf[ 0 ] = { _buf[ 0 ].x, _buf[ 0 ].y };
			buf[ 1 ] = { _buf[ 1 ].x, _buf[ 1 ].y };
			!!cfg.bBoxOutline && clrBoxOutline.a != 0 ? Line( buf, 2, cfg.flBoxThickness, clrBox.GetARGB( ) ) : ( void )0;
			Line( buf, 2, cfg.flBoxThickness, clrBox.GetARGB( ) );
			if ( !WorldToScreen( pEntity.vecBox[ BASE ][ BOTTOMRIGHT ], _buf[ 0 ] ) ) return;
			if ( !WorldToScreen( pEntity.vecBox[ SECONDARY ][ BOTTOMRIGHT ], _buf[ 1 ] ) ) return;
			buf[ 0 ] = { _buf[ 0 ].x, _buf[ 0 ].y };
			buf[ 1 ] = { _buf[ 1 ].x, _buf[ 1 ].y };
			!!cfg.bBoxOutline && clrBoxOutline.a != 0 ? Line( buf, 2, cfg.flBoxThickness, clrBox.GetARGB( ) ) : ( void )0;
			Line( buf, 2, cfg.flBoxThickness, clrBox.GetARGB( ) );
			if ( !WorldToScreen( pEntity.vecBox[ BASE ][ BOTTOMLEFT ], _buf[ 0 ] ) ) return;
			if ( !WorldToScreen( pEntity.vecBox[ SECONDARY ][ BOTTOMLEFT ], _buf[ 1 ] ) ) return;
			buf[ 0 ] = { _buf[ 0 ].x, _buf[ 0 ].y };
			buf[ 1 ] = { _buf[ 1 ].x, _buf[ 1 ].y };
			!!cfg.bBoxOutline && clrBoxOutline.a != 0 ? Line( buf, 2, cfg.flBoxThickness, clrBox.GetARGB( ) ) : ( void )0;
			Line( buf, 2, cfg.flBoxThickness, clrBox.GetARGB( ) );
		}
	}

	// todo
	static void PX_API DrawInformation( )
	{
		if ( !pEntity.bBoxVisibility )
			return;

		auto& cfg = *reinterpret_cast< settings_t::awareness_t::statistics_t::a_statistics_base* >( _cfg );
		if ( !cfg.bInformation )
			return;

		DWORD dwAlignment { };
		switch ( cfg.fAlignment )
		{
			case settings_t::awareness_t::statistics_t::a_statistics_base::LEFT:
			{
			}
			case settings_t::awareness_t::statistics_t::a_statistics_base::RIGHT:
			{
				dwAlignment = DT_LEFT | DT_NOCLIP;
				if ( !!cfg.bIdentifier )
				{
					if ( !cfg.bDimesMode ) // 2d
					{
						if ( !cfg.bDisplayMode ) // screen
						{
							Text( ED3DFont::FNT_TAHOMA, pEntity.vecBox[ BASE ][ TOPRIGHT ].x + 5, pEntity.vecBox[ BASE ][ TOPRIGHT ].y,
								  string_cast< wstr_t >( bVariantID ? player_ptr_t( pEntity.p )->GetPlayerInformation( ).szName : pEntity->GetModel( )->szName ).c_str( ), 
								  cfg.bInformationOutline.Get( ), dwAlignment, 0xFFFFFFFF );
						}
						else // world
						{

						}
					}
					else // 3d
					{

					}
				}
			}
			case settings_t::awareness_t::statistics_t::a_statistics_base::TOP:
			{
				
			}
			case settings_t::awareness_t::statistics_t::a_statistics_base::BOTTOM:
			{
				
			}
			case settings_t::awareness_t::statistics_t::a_statistics_base::SMART:
			{
				
			}
		}
	}

	// todo entities seem to not be working
	void PX_API DrawStatistics( )
	{
		static bool bDeleteOnce = false;
		{
			_Settings._Awareness._Statistics._Players[ SETTING_PLAYER_ENEMY ].bEnabled = true;
			_Settings._Awareness._Statistics._Players[ SETTING_PLAYER_ENEMY ].bInformation = true;
			_Settings._Awareness._Statistics._Players[ SETTING_PLAYER_ENEMY ].bIdentifier = true;
			_Settings._Awareness._Statistics._Players[ SETTING_PLAYER_ENEMY ].fAlignment = settings_t::awareness_t::statistics_t::a_statistics_base::RIGHT;
			_Settings._Awareness._Statistics._Players[ SETTING_PLAYER_ENEMY ].bOrientation = true;
			_Settings._Awareness._Statistics._Players[ SETTING_PLAYER_ENEMY ].bBone = true;
			_Settings._Awareness._Statistics._Players[ SETTING_PLAYER_ENEMY ].bSnapline = true;
			_Settings._Awareness._Statistics._Players[ SETTING_PLAYER_ENEMY ].flBoneThickness = 1.f;
			_Settings._Awareness._Statistics._Players[ SETTING_PLAYER_ENEMY ].flSnaplineThickness = 1.f;

			_Settings._Awareness._Statistics._Players[ SETTING_PLAYER_ENEMY ].bBox = true;
			_Settings._Awareness._Statistics._Players[ SETTING_PLAYER_ENEMY ].bBoxOutline = true;
			_Settings._Awareness._Statistics._Players[ SETTING_PLAYER_ENEMY ].bDimesMode =   false;//GetMoment( ) / 10000000ull % 10 > 6 ? true : false;
			_Settings._Awareness._Statistics._Players[ SETTING_PLAYER_ENEMY ].bDisplayMode = false;//GetMoment( ) / 10000000ull % 10 > 3 ? true : false;
			//bDeleteOnce ? _Settings._Awareness._Statistics._Players[ SETTING_PLAYER_ENEMY ].seqBox[ STATE_VISIBLE ].DeleteColorSequence( 0 ) : ( void )0;
			bDeleteOnce ? _Settings._Awareness._Statistics._Players[ SETTING_PLAYER_ENEMY ].seqBox[ STATE_VISIBLE ].PutNewColorSequence( { 255, 255, 255, 255 }, 1000ull ) : ( void )0;
			_Settings._Awareness._Statistics._Players[ SETTING_PLAYER_ENEMY ].flBoxThickness = 1.f;
		}
		bDeleteOnce = true;

		// check that game is setup properly
		if ( !pEngineClient->IsInGame( ) )
			return;
		pLocalPlayer = GetLocalPlayer( );
		if ( !pLocalPlayer )
			return;

		// check that config for anything is enabled
		{
			auto bContinue = false;
			for each ( auto& _Player in _Settings._Awareness._Statistics._Players )
				if ( !bContinue )
					bContinue |= _Player.bEnabled.Get( );
			for each ( auto& _Entity in _Settings._Awareness._Statistics._Entities )
				if ( !bContinue )
				bContinue |= _Entity.bEnabled.Get( );
			if ( !bContinue )
				return;
		}

		for ( auto i = 0; i < pEntityList->GetMaxEntities( ); i++ )
		{
			pEntity = entity_ptr_t( pEntityList->GetClientEntity( i ) );
			if ( !pEntity )
				continue;

			// check that the config for that ent is enabled
#define buffer_macro( _Sub, enumExist ) _cfg = &_Settings._Awareness._Statistics.##_Sub[ enumExist ]; if ( !_Settings._Awareness._Statistics.##_Sub[ enumExist ].bEnabled  ) continue;
			switch ( pEntity->GetClientClass( )->m_ClassID )
			{
				case ClassID_CCSPlayer:
					bVariantID = true;
					if ( pEntity.Friendly( ) )
					{
						buffer_macro( _Players, SETTING_PLAYER_TEAM );
					}
					else
					{
						buffer_macro( _Players, SETTING_PLAYER_ENEMY );
					}
					break;
				case ClassID_CBaseAnimating: // defuse kit
					bVariantID = false;
					buffer_macro( _Entities, SETTING_ENTITY_DEFUSER );
					break;
				case ClassID_CHEGrenade:
					bVariantID = false;
					buffer_macro( _Entities, SETTING_ENTITY_GRENADE_HE );
					break;
				case ClassID_CFlashbang:
					bVariantID = false;
					buffer_macro( _Entities, SETTING_ENTITY_GRENADE_FLASH );
					break;
				case ClassID_CSmokeGrenade:
					bVariantID = false;
					buffer_macro( _Entities, SETTING_ENTITY_GRENADE_SMOKE );
					break;
				case ClassID_CDecoyGrenade:
					bVariantID = false;
					buffer_macro( _Entities, SETTING_ENTITY_GRENADE_DECOY );
					break;
				case ClassID_CIncendiaryGrenade:
					bVariantID = false;
					buffer_macro( _Entities, SETTING_ENTITY_GRENADE_INCENDIARY );
					break;
				case ClassID_CBaseCSGrenadeProjectile: // projectile flash and he
				{
					bVariantID = false;
					const auto& iModelIndex = reinterpret_cast< CBaseViewModel* >( pEntity.p )->m_nModelIndex( );
					if ( iModelIndex == pModelInfo->GetModelIndex( PX_XOR( "models/Weapons/w_eq_flashbang_dropped.mdl" ) ) )
					{
						buffer_macro( _Entities, SETTING_ENTITY_GRENADE_PROJECTILE_FLASH );
					}
					else if ( iModelIndex == pModelInfo->GetModelIndex( PX_XOR( "models/Weapons/w_eq_fraggrenade_dropped.mdl" ) ) )
					{
						buffer_macro( _Entities, SETTING_ENTITY_GRENADE_PROJECTILE_HE );
					}
					else
						continue; // waduhek
					break;
				}
				case ClassID_CSmokeGrenadeProjectile:
					bVariantID = false;
					buffer_macro( _Entities, SETTING_ENTITY_GRENADE_PROJECTILE_SMOKE );
					break;
				case ClassID_CDecoyProjectile:
					bVariantID = false;
					buffer_macro( _Entities, SETTING_ENTITY_GRENADE_PROJECTILE_DECOY );
					break;
				case ClassID_CMolotovProjectile:
					bVariantID = false;
					buffer_macro( _Entities, SETTING_ENTITY_GRENADE_PROJECTILE_INCENDIARY );
					break;
				case ClassID_CChicken:
					bVariantID = false;
					buffer_macro( _Entities, SETTING_ENTITY_CHICKEN );
					break;
				case ClassID_CC4:
					bVariantID = false;
					buffer_macro( _Entities, SETTING_ENTITY_C4 );
					break;
				case ClassID_CPlantedC4:
					bVariantID = false;
					buffer_macro( _Entities, SETTING_ENTITY_PLANTED_C4 );
					break;
				default: // unaccounted for ent
					continue;
			}

			if ( bVariantID )
			{
				auto& cfg = *reinterpret_cast< settings_t::awareness_t::statistics_t::player_t* >( _cfg );

				if ( player_ptr_t( pEntity.p )->IsDormant( ) )
					pEntity.enumExistence = STATE_DORMANT;
			//	if ( player_ptr_t( pEntity.p )->IsVulnerable( ) )
			//		pEntity.enumExistence = STATE_PLAYER_VULNERABLE;
				else if ( pLocalPlayer->CanSeePlayer( player_ptr_t( pEntity.p ), cfg.bSmokeCheck.Get( ) ) )
					pEntity.enumExistence = STATE_VISIBLE;
			//	else if ( player_ptr_t( pEntity.p )->m_bSpotted( ) )
			//		pEntity.enumExistence = STATE_PLAYER_SPOTTED;
			//	else if ( player_ptr_t( pEntity.p ) is heard )
			//		pEntity.enumExistence = STATE_PLAYER_HEARD;
				else
					pEntity.enumExistence = STATE_INVISIBLE;

				DrawPlayerBone( );
				DrawPlayerOrientation( );
			}
			else
			{
				auto& cfg = *reinterpret_cast< settings_t::awareness_t::statistics_t::entity_t* >( _cfg );

				if ( pLocalPlayer->CanSeePosition( pEntity->m_vecOrigin( ), cfg.bSmokeCheck.Get( ), pEntity.p ) )
					pEntity.enumExistence = STATE_VISIBLE;
				else
					pEntity.enumExistence = STATE_INVISIBLE;
			}

			CalculateBoundingBox( );
			DrawSnapline( );
			DrawBox( );
			DrawInformation( );
		}
	}
}
