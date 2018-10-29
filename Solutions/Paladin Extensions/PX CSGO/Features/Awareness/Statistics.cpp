/// Information.cpp

#include "PX Precompiled.hpp"
#include "../../PX CSGO.hpp"

using namespace PX::Tools;
using namespace PX::Information;
using namespace PX::Drawing;
using namespace Pointers;

namespace PX::Features::Awareness
{
	CBasePlayer* pLocalPlayer = nullptr;

	enum
	{
		TOPLEFT,
		TOPRIGHT,
		BOTTOMLEFT,
		BOTTOMRIGHT,
		TLRB_MAX
	};

	struct _
	{
		CBaseEntity* p = nullptr;
		bool operator!( ) const
		{
			return p == nullptr;
		}

		_& operator=( entity_ptr_t p )
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
		Vector vecBox[ TLRB_MAX ] { { }, { }, { }, { } };
		bool bBoxVisibility = false;
		EState enumExistence = STATE_MAX;
	} pEntity;

	bool bVariantID = false; // false is ent, true is player.
	std::variant< settings_t::awareness_t::statistics_t::a_statistics_base, settings_t::awareness_t::statistics_t::player_t, settings_t::awareness_t::statistics_t::entity_t > _cfg;

	static void PX_API DrawPlayerBone( )
	{

	}

	static void PX_API DrawPlayerOrientation( )
	{

	}

	// review code, it's just cold pasted from cole's original esd
	static void PX_API CalculateBoundingBox( )
	{
		pEntity.bBoxVisibility = true;
		if ( !std::get< settings_t::awareness_t::statistics_t::a_statistics_base >( _cfg ).bDisplayMode )
		{
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
				if ( !WorldToScreen( vecTransformedPoints[ i ], vecScreenPoints[ i ] ) )
					pEntity.bBoxVisibility = false;
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

			pEntity.vecBox[ TOPLEFT ] = { flLeft, flBottom, 0.f };
			pEntity.vecBox[ TOPRIGHT ] = { flRight, flBottom, 0.f };
			pEntity.vecBox[ BOTTOMRIGHT ] = { flRight, flTop, 0.f };
			pEntity.vecBox[ BOTTOMLEFT ] = { flLeft, flTop, 0.f };
		}
		else
		{
			auto& vecOrigin = pEntity->m_vecOrigin( );
			Vector vecPoints[ ] { vecOrigin, vecOrigin, vecOrigin, vecOrigin };
			const Vector2D vecRotationPoint { vecOrigin.x, vecOrigin.y };
			const auto vecViewPosition = vecOrigin + player_ptr_t( pEntity.p )->m_vecViewOffset( );

			vecPoints[ BOTTOMRIGHT ].y -= 20.f; // Bottom right
			vecPoints[ BOTTOMRIGHT ].z -= 5.f;
			vecPoints[ BOTTOMLEFT ].y += 20.f; // Bottom left
			vecPoints[ BOTTOMLEFT ].z -= 5.f;
			vecPoints[ TOPRIGHT ].y -= 20.f; // Top right
			vecPoints[ TOPRIGHT ].z = vecViewPosition.z + 10.f;
			vecPoints[ TOPLEFT ].y += 20.f; // Top left
			vecPoints[ TOPLEFT ].z = vecViewPosition.z + 10.f;

			const auto flRotation = pClientState->viewangles.y;// -( pClientState->viewangles.y - \
																   CalcAngle( pLocalPlayer->GetViewPosition( ), player_ptr_t( pEntity.p )->GetViewPosition( ) ).y );

			for ( auto i = 0; i < TLRB_MAX; i++ )
			{
				vecPoints[ i ].Rotate2D( flRotation, vecRotationPoint );
				if ( !WorldToScreen( vecPoints[ i ], pEntity.vecBox[ i ] ) )
					pEntity.bBoxVisibility = false;
			}
			memcpy( pEntity.vecBox, vecPoints, sizeof( Vector ) * 4 );
		}
	}

	static void PX_API DrawSnapline( )
	{
		auto& cfg = std::get< settings_t::awareness_t::statistics_t::a_statistics_base >( _cfg );

		if ( !cfg.bSnapline )
			return;

		const auto clrSnapline = bVariantID ? std::get< settings_t::awareness_t::statistics_t::player_t>( _cfg ).seqSnapline[ pEntity.enumExistence ].GetCurrentColor( ) : std::get< settings_t::awareness_t::statistics_t::entity_t>( _cfg ).seqSnapline[ pEntity.enumExistence ].GetCurrentColor( );
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

		vecSnapline[ DESTINATION ].x = float( iDimes[ 0 ] ) / 2.f;
		if ( !cfg.bSnaplineOrigin ) // bottom
		{
			vecSnapline[ DESTINATION ].y = iDimes[ 1 ];
		}
		else // top
		{
			vecSnapline[ DESTINATION ].y = 0.f;
		}

		if ( !cfg.bSnaplineDestination ) // bottom
		{
			vecSnapline[ DESTINATION ] = { pEntity.vecBox[ BOTTOMLEFT ].x, pEntity.vecBox[ BOTTOMLEFT ].y };
			vecSnapline[ DESTINATION ].x += pEntity.vecBox[ BOTTOMRIGHT ].x - pEntity.vecBox[ BOTTOMLEFT ].x;
			vecSnapline[ DESTINATION ].y += pEntity.vecBox[ BOTTOMRIGHT ].y - pEntity.vecBox[ BOTTOMLEFT ].y;
		}
		else // top
		{
			vecSnapline[ DESTINATION ] = { pEntity.vecBox[ TOPLEFT ].x, pEntity.vecBox[ TOPLEFT ].y };
			vecSnapline[ DESTINATION ].x += pEntity.vecBox[ TOPRIGHT ].x - pEntity.vecBox[ TOPLEFT ].x;
			vecSnapline[ DESTINATION ].y += pEntity.vecBox[ TOPRIGHT ].y - pEntity.vecBox[ TOPLEFT ].y;
		}

		Line( vecSnapline, ORIGIN_DESTINATION_MAX, cfg.flSnaplineThickness, clrSnapline.GetARGB( ) );
		
		if ( !cfg.bSnaplineOutline )
			return;

		const auto clrSnaplineOutline = bVariantID ? std::get< settings_t::awareness_t::statistics_t::player_t>( _cfg ).seqSnaplineOutline.GetCurrentColor( ) : std::get< settings_t::awareness_t::statistics_t::entity_t>( _cfg ).seqSnaplineOutline.GetCurrentColor( );
		if ( clrSnaplineOutline.a == 0 )
			return;

		Line( vecSnapline, ORIGIN_DESTINATION_MAX, cfg.flSnaplineOutlineThickness, clrSnaplineOutline.GetARGB( ) );
	}

	static void PX_API DrawBox( )
	{

	}

	static void PX_API DrawInformation( )
	{
		
	}

	void PX_API DrawStatistics( )
	{
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
				bContinue |= _Player.bEnabled.Get( );
			for each ( auto& _Entity in _Settings._Awareness._Statistics._Entities )
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
			switch ( pEntity->GetClientClass( )->m_ClassID )
			{
				case ClassID_CCSPlayer:
					bVariantID = true;
					if ( pEntity.Friendly( ) )
					{
						if ( !std::get< settings_t::awareness_t::statistics_t::player_t >( _cfg = _Settings._Awareness._Statistics._Players[ SETTING_PLAYER_TEAM ] ).bEnabled )
							continue;
					}
					else if ( !std::get< settings_t::awareness_t::statistics_t::player_t >( _cfg = _Settings._Awareness._Statistics._Players[ SETTING_PLAYER_ENEMY ] ).bEnabled )
						continue;
					break;
				case ClassID_CBaseAnimating: // defuse kit
					if ( !std::get< settings_t::awareness_t::statistics_t::entity_t >( _cfg = _Settings._Awareness._Statistics._Entities[ SETTING_ENTITY_DEFUSER ] ).bEnabled )
						continue;
					break;
				case ClassID_CHEGrenade:
					if ( !std::get< settings_t::awareness_t::statistics_t::entity_t >( _cfg = _Settings._Awareness._Statistics._Entities[ SETTING_ENTITY_GRENADE_HE ] ).bEnabled )
						continue;
					break;
				case ClassID_CFlashbang:
					if ( !std::get< settings_t::awareness_t::statistics_t::entity_t >( _cfg = _Settings._Awareness._Statistics._Entities[ SETTING_ENTITY_GRENADE_FLASH ] ).bEnabled )
						continue;
					break;
				case ClassID_CSmokeGrenade:
					if ( !std::get< settings_t::awareness_t::statistics_t::entity_t >( _cfg = _Settings._Awareness._Statistics._Entities[ SETTING_ENTITY_GRENADE_SMOKE ] ).bEnabled )
						continue;
					break;
				case ClassID_CDecoyGrenade:
					if ( !std::get< settings_t::awareness_t::statistics_t::entity_t >( _cfg = _Settings._Awareness._Statistics._Entities[ SETTING_ENTITY_GRENADE_DECOY ] ).bEnabled )
						continue;
					break;
				case ClassID_CIncendiaryGrenade:
					if ( !std::get< settings_t::awareness_t::statistics_t::entity_t >( _cfg = _Settings._Awareness._Statistics._Entities[ SETTING_ENTITY_GRENADE_INCENDIARY ] ).bEnabled )
						continue;
					break;
				case ClassID_CBaseCSGrenadeProjectile: // projectile flash and he
				{
					const auto& iModelIndex = reinterpret_cast< CBaseViewModel* >( pEntity.p )->m_nModelIndex( );
					if ( iModelIndex == pModelInfo->GetModelIndex( PX_XOR( "models/Weapons/w_eq_flashbang_dropped.mdl" ) )
						 && !std::get< settings_t::awareness_t::statistics_t::entity_t >( _cfg = _Settings._Awareness._Statistics._Entities[ SETTING_ENTITY_GRENADE_PROJECTILE_FLASH ] ).bEnabled )
						continue;
					else if ( iModelIndex == pModelInfo->GetModelIndex( PX_XOR( "models/Weapons/w_eq_fraggrenade_dropped.mdl" ) )
							  && !std::get< settings_t::awareness_t::statistics_t::entity_t >( _cfg = _Settings._Awareness._Statistics._Entities[ SETTING_ENTITY_GRENADE_PROJECTILE_FLASH ] ).bEnabled )
						continue;
					break;
				}
				case ClassID_CSmokeGrenadeProjectile:
					if ( !std::get< settings_t::awareness_t::statistics_t::entity_t >( _cfg = _Settings._Awareness._Statistics._Entities[ SETTING_ENTITY_GRENADE_PROJECTILE_SMOKE ] ).bEnabled )
						continue;
					break;
				case ClassID_CDecoyProjectile:
					if ( !std::get< settings_t::awareness_t::statistics_t::entity_t >( _cfg = _Settings._Awareness._Statistics._Entities[ SETTING_ENTITY_GRENADE_PROJECTILE_DECOY ] ).bEnabled )
						continue;
					break;
				case ClassID_CMolotovProjectile:
					if ( !std::get< settings_t::awareness_t::statistics_t::entity_t >( _cfg = _Settings._Awareness._Statistics._Entities[ SETTING_ENTITY_GRENADE_PROJECTILE_INCENDIARY ] ).bEnabled )
						continue;
					break;
				case ClassID_CChicken:
					if ( !std::get< settings_t::awareness_t::statistics_t::entity_t >( _cfg = _Settings._Awareness._Statistics._Entities[ SETTING_ENTITY_CHICKEN ] ).bEnabled )
						continue;
					break;
				case ClassID_CC4:
					if ( !std::get< settings_t::awareness_t::statistics_t::entity_t >( _cfg = _Settings._Awareness._Statistics._Entities[ SETTING_ENTITY_C4 ] ).bEnabled )
						continue;
					break;
				case ClassID_CPlantedC4:
					if ( !std::get< settings_t::awareness_t::statistics_t::entity_t >( _cfg = _Settings._Awareness._Statistics._Entities[ SETTING_ENTITY_PLANTED_C4 ] ).bEnabled )
						continue;
					break;
				default: // unaccounted for ent
					continue;
			}

			if ( bVariantID )
			{
				auto& cfg = std::get< settings_t::awareness_t::statistics_t::player_t >( _cfg );

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
				auto& cfg = std::get< settings_t::awareness_t::statistics_t::entity_t >( _cfg );

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
