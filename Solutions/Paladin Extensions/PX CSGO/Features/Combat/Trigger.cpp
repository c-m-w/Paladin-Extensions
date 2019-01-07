/// Trigger.cpp

#include "PX Precompiled.hpp"
#include "../../PX CSGO.hpp"

using namespace PX;
using namespace Information;
using namespace Pointers;
using namespace Tools;

namespace PX::Features::Combat
{
	float PX_API CalculateHitchance( player_ptr_t pLocalPlayer, player_ptr_t pTarget, int iHitgroup, CBaseCombatWeapon *pWeapon, CUserCmd *pCmd, int iRays );

	void PX_API Trigger( player_ptr_t pLocalPlayer, CUserCmd *pCmd )
	{
		if ( pCmd->buttons & IN_ATTACK || _Settings._Miscellaneous._Other.bAutomaticFire.Get( ) )
			return;

		const auto hActiveWeapon = pLocalPlayer->m_hActiveWeapon( ).Get( );
		if ( hActiveWeapon == nullptr
			|| !hActiveWeapon->CanFire( ) )
			return;

		const auto pWeaponData = hActiveWeapon->GetCSWeaponData( );
		if ( !pWeaponData )
			return;

		trigger_config_t *_Config;
		PX_GET_WEAPON_CONFIG( hActiveWeapon, _Config, _Settings._Combat._Trigger );

		if ( !_Config->bEnemies.Get( ) && !_Config->bTeammates.Get( ) ) // dont bother tracing a ray if we wont shoot anyway
			return;

		const auto vecStart = pLocalPlayer->GetViewPosition( );
		Vector vecEnd;
		CTraceFilter tfFilter;
		Ray_t rRay;
		CGameTrace gtRay;

		TransformAngle( pCmd->viewangles, vecEnd );
		vecEnd *= pWeaponData->flRange;
		vecEnd += vecStart;
		tfFilter.pSkip = pLocalPlayer;
		rRay.Init( vecStart, vecEnd );
		pEngineTrace->TraceRay( rRay, PX_MASK_VISIBLE, &tfFilter, &gtRay );

		if ( !_Config->bHitGroups[ gtRay.hitgroup ].Get( ) )
			return;
		if ( gtRay.hit_entity == nullptr
			|| !player_ptr_t( gtRay.hit_entity )->IsPlayer( )
			|| player_ptr_t( gtRay.hit_entity )->m_bGunGameImmunity( )
			|| !( player_ptr_t( gtRay.hit_entity )->m_iTeamNum( ) == pLocalPlayer->m_iTeamNum( ) ? _Config->bTeammates.Get( ) : _Config->bEnemies.Get( ) )
			|| _Config->bMindSmoke.Get( ) && LineGoesThroughSmoke( vecStart, gtRay.endpos ) )
			return;
		if ( _Config->flHitChance != 0.f && CalculateHitchance( pLocalPlayer, player_ptr_t( gtRay.hit_entity ), gtRay.hitgroup, hActiveWeapon, pCmd, _Config->iRays ) < _Config->flHitChance )
			return;

		pCmd->buttons |= IN_ATTACK;
	}

	float PX_API CalculateHitchance( player_ptr_t pLocalPlayer, player_ptr_t pTarget, int iHitgroup, CBaseCombatWeapon *pWeapon, CUserCmd *pCmd, int iRays )
	{
		const auto vecViewPosition = pLocalPlayer->GetViewPosition( );
		Vector vecForward;
		TransformAngle( pCmd->viewangles, vecForward );
		auto iHits = 0;
		for ( auto i = 0; i < iRays; i++ )
		{
			const auto flSpread = ( pWeapon->GetInaccuracy( ) + pWeapon->GetSpread( ) ) / 2.f;
			const auto vecRandom = vecViewPosition + pWeapon->GetCSWeaponData( )->flRange * ( Vector( GenerateRandomNumber( -flSpread, flSpread ), GenerateRandomNumber( -flSpread, flSpread ), GenerateRandomNumber( -flSpread, flSpread ) ) + vecForward );
			CTraceFilter tfFilter;
			Ray_t rRay;
			CGameTrace gtRay;

			tfFilter.pSkip = pLocalPlayer;
			rRay.Init( vecViewPosition, vecRandom );
			pEngineTrace->TraceRay( rRay, PX_MASK_VISIBLE, &tfFilter, &gtRay );

			if ( gtRay.hit_entity == pTarget
				&& gtRay.hitgroup == iHitgroup )
				iHits++;
		}
		return float( iHits ) / float( iRays );
	}
}
