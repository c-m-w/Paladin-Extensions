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

	void PX_API SetClantag( cstr_t szTag )
	{
		static auto ptrSetClantag = mEngine.FindPattern( jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Signatures" ) ][ PX_XOR( "Set Clantag" ) ].get< std::string >( ) )
			+ jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Offsets" ) ][ PX_XOR( "Set Clantag" ) ].get< int >( );
		reinterpret_cast< int( __fastcall* )( const char*, const char* ) >( ptrSetClantag )( szTag, szTag );
	}

	void PX_API RevealRanks( )
	{
		static auto ptrRevealRanks = mClient.FindPattern( jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Signatures" ) ][ PX_XOR( "Reveal Ranks" ) ].get< std::string >( ) )
			+ jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Offsets" ) ][ PX_XOR( "Reveal Ranks" ) ].get< int >( );
		static int iBuffer[ ] { 0, 0, 0 };
		reinterpret_cast< char( __cdecl* )( int* ) >( ptrRevealRanks )( iBuffer );
	}

	CBasePlayer* PX_API GetLocalPlayer( )
	{
		return reinterpret_cast< CBasePlayer* >( pEntityList->GetClientEntity( pEngineClient->GetLocalPlayer( ) ) );
	}

	void PX_API ClampAngles( QAngle& qAngles )
	{
		while ( qAngles.yaw >= 180.f )
			qAngles.yaw -= 180.f;
		while ( qAngles.yaw <= -180.f )
			qAngles.yaw += 180.f;

		while ( qAngles.pitch >= 90.f )
			qAngles.pitch -= 90.f;
		while ( qAngles.pitch <= -90.f )
			qAngles.pitch += 90.f;
	}

	bool PX_API WorldToScreen( const Vector vecWorld, Vector &vecScreen )
	{
		int iWidth, iHeight;
		pEngineClient->GetScreenSize( iWidth, iHeight );
		auto vmMatrix = pEngineClient->WorldToScreenMatrix( );

		const auto flTemp = vmMatrix[ 3 ][ 0 ] * vecWorld.x + vmMatrix[ 3 ][ 1 ] * vecWorld.y + vmMatrix[ 3 ][ 2 ] * vecWorld.z + vmMatrix[ 3 ][ 3 ];

		if ( flTemp <= 0.01f )
			return false;

		const auto flInverseTemp = 1.f / flTemp;
		vecScreen.x = vmMatrix[ 0 ][ 0 ] * vecWorld.x + vmMatrix[ 0 ][ 1 ] * vecWorld.y + vmMatrix[ 0 ][ 2 ] * vecWorld.z + vmMatrix[ 0 ][ 3 ];
		vecScreen.y = vmMatrix[ 1 ][ 0 ] * vecWorld.x + vmMatrix[ 1 ][ 1 ] * vecWorld.y + vmMatrix[ 1 ][ 2 ] * vecWorld.z + vmMatrix[ 1 ][ 3 ];
		vecScreen = { iWidth / 2.f + 0.5f * ( vecScreen.x * flInverseTemp ) * iWidth + 0.5f, iHeight / 2.f - 0.5f * ( vecScreen.y * flInverseTemp ) * iHeight + 0.5f, 0.f };
		return true;
	}

	Vector2D PX_API CalcAngle( Vector vecPosOne, Vector vecPosTwo )
	{
		vecPosTwo.x -= vecPosOne.x;
		vecPosTwo.y -= vecPosOne.y;
		const auto flZDifference = vecPosOne.z - vecPosTwo.z;
		const auto flDistance = sqrt( vecPosTwo.x * vecPosTwo.x + vecPosTwo.y * vecPosTwo.y );

		Vector2D vecAimAngles { D3DXToDegree( atan2( flZDifference, flDistance ) ),
			D3DXToDegree( atan2( vecPosTwo.y, vecPosTwo.x ) ) };

		vecAimAngles.Normalize( );
		return vecAimAngles;
	}

	float PX_API GetAngleDistance( Vector vecCurrentAngles, Vector vecPosOne, Vector vecPosTwo )
	{
		const auto vecAngles = CalcAngle( vecPosOne, vecPosTwo );
		Vector2D vecRelativeAngles { vecCurrentAngles.x - vecAngles.x, vecCurrentAngles.y - vecAngles.y };
		vecRelativeAngles.Normalize( );
		return sqrt( ( vecRelativeAngles.x * vecRelativeAngles.x ) + ( vecRelativeAngles.y * vecRelativeAngles.y ) );
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

	bool CBasePlayer::IsAlive( )
	{
		return m_lifeState( ) == LIFE_ALIVE;
	}
}
