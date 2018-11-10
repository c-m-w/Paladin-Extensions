/// Features.inl

#pragma once

namespace PX::Features
{
	template< typename _r, typename _t > _r* PX_API GetWeaponConfig( CHandle< Tools::CBaseCombatWeapon > hWeapon, _t _Config )
	{
		const auto iItemDefIndex = hWeapon->m_Item( )->m_iItemDefinitionIndex( );
		const auto fucking_men = hWeapon->GetCSWeaponData( );
		if ( !fucking_men )
			return nullptr;

		const auto pWeaponType = fucking_men->WeaponType;
		return _Config._IndividualWeapons[ iItemDefIndex ].bUseSeparate.Get( ) ? &_Config._IndividualWeapons[ iItemDefIndex ]
			: _Config._WeaponTypes[ pWeaponType ].bUseSeparate.Get( ) ? &_Config._WeaponTypes[ pWeaponType ]
			: &_Config._All;
	}
}
