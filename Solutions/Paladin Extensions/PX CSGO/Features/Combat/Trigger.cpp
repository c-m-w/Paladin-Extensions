/// Trigger.cpp

#include "PX Precompiled.hpp"
#include "../../PX CSGO.hpp"

using namespace PX;
using namespace Information;
using namespace Pointers;
using namespace Tools;

namespace PX::Features::Combat
{
	void PX_API Trigger( player_ptr_t pLocalPlayer, CUserCmd* pCmd )
	{
		const auto hActiveWeapon = pLocalPlayer->m_hActiveWeapon( ).Get( );
		if ( hActiveWeapon == nullptr
			 || !hActiveWeapon->CanFire( ) )
			return;
		const auto iItemDefinitionIndex = hActiveWeapon->m_Item( )->m_iItemDefinitionIndex( );
		const auto pWeaponData = hActiveWeapon->GetCSWeaponData( );
		if ( !pWeaponData )
			return;

		const auto iWeaponType = pWeaponData->WeaponType;

		auto& _Config = _Settings._Combat._Trigger._IndividualWeapons[ iItemDefinitionIndex ].bUseSeparate.Get( ) ? _Settings._Combat._Trigger._IndividualWeapons[ iItemDefinitionIndex ]
			: _Settings._Combat._Trigger._WeaponTypes[ iWeaponType ].bUseSeparate.Get( ) ? _Settings._Combat._Trigger._WeaponTypes[ iWeaponType ]
			: _Settings._Combat._Trigger._All;

		if ( !_Config.bEnemies.Get( ) && !_Config.bTeammates.Get( ) ) // dont bother tracing a ray if we wont shoot anyway
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

		if ( !_Config.bHitGroups[ gtRay.hitgroup ].Get( ) )
			return;
		if ( gtRay.hit_entity == nullptr
			 || !player_ptr_t( gtRay.hit_entity )->IsPlayer( )
			 || !( player_ptr_t( gtRay.hit_entity )->m_iTeamNum( ) == pLocalPlayer->m_iTeamNum( ) ? _Config.bTeammates.Get( ) : _Config.bEnemies.Get( ) )
			 || _Config.bMindSmoke.Get( ) && LineGoesThroughSmoke( vecStart, gtRay.endpos ) )
			 return;

		pCmd->buttons |= IN_ATTACK;
	}
}
