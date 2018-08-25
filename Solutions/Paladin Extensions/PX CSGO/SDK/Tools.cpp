/// Tools.cpp

#include "../PX CSGO.hpp"

using namespace PX::Information;
using namespace PX::Types;
using namespace Memory;
using namespace VirtualTableIndicies;
using namespace Modules;
using namespace Pointers;

namespace PX::Tools
{
	bool PX_API LineGoesThroughSmoke( Vector vecStartPos, Vector vecEndPos )
	{
		static auto ptrLineGoesThroughSmoke = mClient.FindPattern( jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Signatures" ) ][ PX_XOR( "Line Goes Through Smoke" ) ].get< std::string >( ) )
			+ jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Offsets" ) ][ PX_XOR( "Line Goes Through Smoke" ) ].get< int >( );
		return reinterpret_cast< bool( __cdecl* )( Vector, Vector ) >( ptrLineGoesThroughSmoke )( vecStartPos, vecEndPos );
	}

	CBasePlayer* PX_API GetLocalPlayer( )
	{
		return reinterpret_cast< CBasePlayer* >( pEntityList->GetClientEntity( pEngineClient->GetLocalPlayer( ) ) );
	}

	bool CBaseEntity::IsPlayer( )
	{
		return reinterpret_cast< bool( __thiscall* )( CBaseEntity* ) >( ( *reinterpret_cast< void*** >( this ) )[ uIsPlayer ] )( this );
	}

	bool CBaseEntity::IsWeapon( )
	{
		return reinterpret_cast< bool( __thiscall* )( CBaseEntity* ) >( ( *reinterpret_cast< void*** >( this ) )[ uIsWeapon ] )( this );
	}

	bool CBaseEntity::IsPlantedC4( )
	{
		return GetClientClass( )->m_ClassID == ClassID_CPlantedC4;
	}

	bool CBaseEntity::IsDefuseKit( )
	{
		return GetClientClass( )->m_ClassID == ClassID_CBaseAnimating;
	}

	float CBaseEntity::GetBombTimer( )
	{
		const auto flTimer = *reinterpret_cast< float* >( this + Offsets::ptrBombTimer ) - pGlobalVariables->curtime;
		return flTimer > 0.f ? flTimer : 0.f;
	}

	float CBaseEntity::GetDefuseTimer( )
	{
		const auto flTimer = *reinterpret_cast< float* >( this + Offsets::ptrDefuseTimer ) - pGlobalVariables->curtime;
		return flTimer > 0.f ? flTimer : 0.f;
	}

	CEconomyItemView* CBaseAttributableItem::m_Item( )
	{
		return reinterpret_cast< CEconomyItemView* >( this );
	}

	CCSWeaponInfo* CBaseCombatWeapon::GetCSWeaponData( )
	{
		static auto ptrGetCSWeaponData = mClient.FindPattern( jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Signatures" ) ][ PX_XOR( "Get CS Weapon Data" ) ].get< std::string >( ) )
			+ jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Offsets" ) ][ PX_XOR( "Get CS Weapon Data" ) ].get< int >( );
		return reinterpret_cast< CCSWeaponInfo*( __thiscall* )( CBaseCombatWeapon* ) >( ptrGetCSWeaponData )( this );
	}

	bool CBaseCombatWeapon::HasBullets( )
	{
		return !IsReloading( ) && m_iClip1( ) > 0;
	}

	bool CBaseCombatWeapon::CanFire( )
	{
		if ( !HasBullets( ) )
			return false;
		return m_flNextPrimaryAttack( ) <= pGlobalVariables->curtime;
	}

	bool CBaseCombatWeapon::IsGrenade( )
	{
		return GetCSWeaponData( )->WeaponType == WEAPONTYPE_GRENADE;
	}

	bool CBaseCombatWeapon::IsKnife( )
	{
		return GetCSWeaponData( )->WeaponType == WEAPONTYPE_KNIFE;
	}

	bool CBaseCombatWeapon::IsRifle( )
	{
		switch ( GetCSWeaponData( )->WeaponType )
		{
			case WEAPONTYPE_RIFLE:
			case WEAPONTYPE_SHOTGUN:
			case WEAPONTYPE_SUBMACHINEGUN:
			case WEAPONTYPE_MACHINEGUN:
				return true;
			default:
				return false;
		}
	}

	bool CBaseCombatWeapon::IsPistol( )
	{
		return GetCSWeaponData( )->WeaponType == WEAPONTYPE_PISTOL;
	}

	bool CBaseCombatWeapon::IsSniper( )
	{
		return GetCSWeaponData( )->WeaponType == WEAPONTYPE_SNIPER_RIFLE;
	}

	bool CBaseCombatWeapon::IsReloading( )
	{
		static auto ptrIsReloading = mClient.FindPattern( jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Signatures" ) ][ PX_XOR( "Is Reloading" ) ].get< std::string >( ) )
			+ jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Offsets" ) ][ PX_XOR( "Is Reloading" ) ].get< int >( );
		return *reinterpret_cast< bool* >( this + ptrIsReloading );
	}

	float CBaseCombatWeapon::GetInaccuracy( )
	{
		return reinterpret_cast< float( __thiscall* )( CBaseCombatWeapon* ) >( ( *reinterpret_cast< void*** >( this ) )[ uGetInaccuracy ] )( this );
	}

	float CBaseCombatWeapon::GetSpread( )
	{
		return reinterpret_cast< float( __thiscall* )( CBaseCombatWeapon* ) >( ( *reinterpret_cast< void*** >( this ) )[ uGetSpread ] )( this );
	}

	void CBaseCombatWeapon::UpdateAccuracyPenalty( )
	{
		return reinterpret_cast< void( __thiscall* )( CBaseCombatWeapon* ) >( ( *reinterpret_cast< void*** >( this ) )[ uUpdateAccuracyPenalty ] )( this );
	}
}
