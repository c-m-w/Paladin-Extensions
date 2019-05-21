/// CBasePlayer Extended.cpp

#include "CSGO SDK.hpp"

Vector EXTENDED_SDK_CLASS( CCSPlayer )::GetViewPosition( )
{
	return GetAbsOrigin( ) + m_vecViewOffset; // sure hope this is the right function lol
}

bool EXTENDED_SDK_CLASS( CCSPlayer )::IsVulnerable( )
{
	const auto pActiveWeapon = GetActiveWeapon( );
	const auto enumWeaponType = pActiveWeapon != nullptr ? GetActiveWeapon( )->GetWeaponID( ) : WEAPON_NONE;
	return m_flFlashDuration // REVIEW: is this based on curtime/a global var? // cant see
		|| !pActiveWeapon
		&& ( !pActiveWeapon->HasAmmo( ) // REVIEW: maybe HasAnyAmmo( )? // cant fire
			 || enumWeaponType == WEAPON_NONE // no weapon (tpose)
//			 || enumWeaponType > WEAPON_SSG08 // useless weapon/nade
//			 && enumWeaponType < WEAPON_M4A1S // useless weapon/nade
//			 || enumWeaponType > WEAPON_TACTICALAWARENESSGRENADE
			 ); // knife model/gloves/other
}
