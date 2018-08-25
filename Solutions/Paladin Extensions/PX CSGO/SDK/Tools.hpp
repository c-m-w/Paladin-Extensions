/// Tools.hpp

#pragma once

using namespace PX::Information::NetworkedVariableManager;
using namespace PX::Types;

namespace PX::Tools
{
	class CBasePlayer;

	bool PX_API LineGoesThroughSmoke( Vector vecStartPos, Vector vecEndPos );
	CBasePlayer* PX_API GetLocalPlayer( );

	class CEconomyItemView
	{
	public:
		PX_NETVAR_REFERENCE( int32_t, m_bInitialized, "DT_BaseAttributableItem", "m_bInitialized" );
		PX_NETVAR_REFERENCE( int16_t, m_iItemDefinitionIndex, "DT_BaseAttributableItem", "m_iItemDefinitionIndex" );
		PX_NETVAR_REFERENCE( int32_t, m_iEntityLevel, "DT_BaseAttributableItem", "m_iEntityLevel" );
		PX_NETVAR_REFERENCE( int32_t, m_iAccountID, "DT_BaseAttributableItem", "m_iAccountID" );
		PX_NETVAR_REFERENCE( int32_t, m_iItemIDLow, "DT_BaseAttributableItem", "m_iItemIDLow" );
		PX_NETVAR_REFERENCE( int32_t, m_iItemIDHigh, "DT_BaseAttributableItem", "m_iItemIDHigh" );
		PX_NETVAR_REFERENCE( int32_t, m_iEntityQuality, "DT_BaseAttributableItem", "m_iEntityQuality" );
	};

	class CBaseEntity: public IClientEntity
	{
	public:
		PX_NETVAR_REFERENCE( int32_t, m_nModelIndex, "DT_BaseEntity", "m_nModelIndex" );
		PX_NETVAR_REFERENCE( int32_t, m_iTeamNum, "DT_BaseEntity", "m_iTeamNum" );
		PX_NETVAR_REFERENCE( Vector, m_vecOrigin, "DT_BaseEntity", "m_vecOrigin" );
		PX_NETVAR_REFERENCE( bool, m_bShouldGlow, "DT_DynamicProp", "m_bShouldGlow" );
		PX_NETVAR_REFERENCE( CHandle< CBasePlayer >, m_hOwnerEntity, "DT_BaseEntity", "m_hOwnerEntity" );
		PX_NETVAR_REFERENCE( float, m_flSimulationTime, "DT_BaseEntity", "m_flSimulationTime" );
		PX_NETVAR_REFERENCE_OFFSET( matrix3x4_t, m_rgflCoordinateFrame, "DT_BaseEntity", "m_CollisionGroup", -int( 0x30 ) );

		bool IsPlayer( );
		bool IsWeapon( );
		bool IsPlantedC4( );
		bool IsDefuseKit( );
		float GetBombTimer( );
		float GetDefuseTimer( );
	};

	class CBaseAttributableItem: public CBaseEntity
	{
	public:
		PX_NETVAR_REFERENCE( uint64_t, m_OriginalOwnerXuid, "DT_BaseAttributableItem", "m_OriginalOwnerXuidLow" );
		PX_NETVAR_REFERENCE( int32_t, m_OriginalOwnerXuidLow, "DT_BaseAttributableItem", "m_OriginalOwnerXuidLow" );
		PX_NETVAR_REFERENCE( int32_t, m_OriginalOwnerXuidHigh, "DT_BaseAttributableItem", "m_OriginalOwnerXuidHigh" );
		PX_NETVAR_REFERENCE( int32_t, m_nFallbackStatTrak, "DT_BaseAttributableItem", "m_nFallbackStatTrak" );
		PX_NETVAR_REFERENCE( int32_t, m_nFallbackPaintKit, "DT_BaseAttributableItem", "m_nFallbackPaintKit" );
		PX_NETVAR_REFERENCE( int32_t, m_nFallbackSeed, "DT_BaseAttributableItem", "m_nFallbackSeed" );
		PX_NETVAR_REFERENCE( float_t, m_flFallbackWear, "DT_BaseAttributableItem", "m_flFallbackWear" );

		CEconomyItemView* m_Item( );
	};

	class CBaseCombatWeapon: public CBaseAttributableItem
	{
	public:
		PX_NETVAR_REFERENCE( float_t, m_flNextPrimaryAttack, "DT_BaseCombatWeapon", "m_flNextPrimaryAttack" );
		PX_NETVAR_REFERENCE( float_t, m_flNextSecondaryAttack, "DT_BaseCombatWeapon", "m_flNextSecondaryAttack" );
		PX_NETVAR_REFERENCE( int32_t, m_iClip1, "DT_BaseCombatWeapon", "m_iClip1" );
		PX_NETVAR_REFERENCE( int32_t, m_iClip2, "DT_BaseCombatWeapon", "m_iClip2" );
		PX_NETVAR_REFERENCE( float_t, m_flRecoilIndex, "DT_WeaponCSBase", "m_flRecoilIndex" );

		CCSWeaponInfo* GetCSWeaponData( );
		bool HasBullets( );
		bool CanFire( );
		bool IsGrenade( );
		bool IsKnife( );
		bool IsReloading( );
		bool IsRifle( );
		bool IsPistol( );
		bool IsSniper( );
		float GetInaccuracy( );
		float GetSpread( );
		void UpdateAccuracyPenalty( );
	};

	class CBaseViewModel: public CBaseEntity
	{
	public:
		PX_NETVAR_REFERENCE( int32_t, m_nModelIndex, "DT_BaseViewModel", "m_nModelIndex" );
		PX_NETVAR_REFERENCE( int32_t, m_nViewModelIndex, "DT_BaseViewModel", "m_nViewModelIndex" );
		PX_NETVAR_REFERENCE( CHandle<CBaseCombatWeapon>, m_hWeapon, "DT_BaseViewModel", "m_hWeapon" );
		PX_NETVAR_REFERENCE( CHandle<CBasePlayer>, m_hOwner, "DT_BaseViewModel", "m_hOwner" );
	};

	class CBasePlayer: public CBaseEntity
	{
	public:
		PX_NETVAR_REFERENCE( bool, m_bHasDefuser, "DT_CSPlayer", "m_bHasDefuser" );
		PX_NETVAR_REFERENCE( bool, m_bGunGameImmunity, "DT_CSPlayer", "m_bGunGameImmunity" );
		PX_NETVAR_REFERENCE( int32_t, m_iShotsFired, "DT_CSPlayer", "m_iShotsFired" );
		PX_NETVAR_REFERENCE( QAngle, m_angEyeAngles, "DT_CSPlayer", "m_angEyeAngles[0]" );
		PX_NETVAR_REFERENCE( int, m_ArmorValue, "DT_CSPlayer", "m_ArmorValue" );
		PX_NETVAR_REFERENCE( bool, m_bHasHelmet, "DT_CSPlayer", "m_bHasHelmet" );
		PX_NETVAR_REFERENCE( bool, m_bIsScoped, "DT_CSPlayer", "m_bIsScoped" );;
		PX_NETVAR_REFERENCE( float, m_flLowerBodyYawTarget, "DT_CSPlayer", "m_flLowerBodyYawTarget" );
		PX_NETVAR_REFERENCE( float, m_flFlashDuration, "DT_CSPlayer", "m_flFlashDuration" );
		PX_NETVAR_REFERENCE( float, m_flFlashMaxAlpha, "DT_CSPlayer", "m_flFlashMaxAlpha" );
		PX_NETVAR_REFERENCE( int, m_totalHitsOnServer, "DT_CSPlayer", "m_totalHitsOnServer" );
		PX_NETVAR_REFERENCE( int32_t, m_iHealth, "DT_BasePlayer", "m_iHealth" );
		PX_NETVAR_REFERENCE( int32_t, m_lifeState, "DT_BasePlayer", "m_lifeState" );
		PX_NETVAR_REFERENCE( int32_t, m_fFlags, "DT_BasePlayer", "m_fFlags" );
		PX_NETVAR_REFERENCE( int32_t, m_nTickBase, "DT_BasePlayer", "m_nTickBase" );
		PX_NETVAR_REFERENCE( Vector, m_vecViewOffset, "DT_BasePlayer", "m_vecViewOffset[0]" );
		PX_NETVAR_REFERENCE( QAngle, m_viewPunchAngle, "DT_BasePlayer", "m_viewPunchAngle" );
		PX_NETVAR_REFERENCE( QAngle, m_aimPunchAngle, "DT_BasePlayer", "m_aimPunchAngle" );
		PX_NETVAR_REFERENCE( CHandle<CBaseViewModel>, m_hViewModel, "DT_BasePlayer", "m_hViewModel[0]" );
		PX_NETVAR_REFERENCE( Vector, m_vecVelocity, "DT_BasePlayer", "m_vecVelocity[0]" );
		PX_NETVAR_REFERENCE( float, m_flMaxspeed, "DT_BasePlayer", "m_flMaxspeed" );
		PX_NETVAR_REFERENCE( CHandle<CBasePlayer>, m_hObserverTarget, "DT_BasePlayer", "m_hObserverTarget" );
		PX_NETVAR_REFERENCE( int, m_iObserverMode, "DT_BasePlayer", "m_iObserverMode" );
		PX_NETVAR_REFERENCE( CHandle<CBaseCombatWeapon>, m_hActiveWeapon, "DT_BaseCombatCharacter", "m_hActiveWeapon" );
		PX_NETVAR_POINTER( CHandle<CBaseCombatWeapon>, m_hMyWeapons, "DT_BaseCombatCharacter", "m_hMyWeapons" );
		PX_NETVAR_POINTER( CHandle<CBaseAttributableItem>, m_hMyWearables, "DT_BaseCombatCharacter", "m_hMyWearables" );
	};

	class CPlantedC4
	{
	public:
		PX_NETVAR_REFERENCE( bool, m_bBombTicking, "DT_PlantedC4", "m_bBombTicking" );
		PX_NETVAR_REFERENCE( bool, m_bBombDefused, "DT_PlantedC4", "m_bBombDefused" );
		PX_NETVAR_REFERENCE( float, m_flC4Blow, "DT_PlantedC4", "m_flC4Blow" );
		PX_NETVAR_REFERENCE( float, m_flTimerLength, "DT_PlantedC4", "m_flTimerLength" );
		PX_NETVAR_REFERENCE( float, m_flDefuseLength, "DT_PlantedC4", "m_flDefuseLength" );
		PX_NETVAR_REFERENCE( float, m_flDefuseCountDown, "DT_PlantedC4", "m_flDefuseCountDown" );
		PX_NETVAR_REFERENCE( CHandle< CBasePlayer >, m_hBombDefuser, "DT_PlantedC4", "m_hBombDefuser" );
	};
}
