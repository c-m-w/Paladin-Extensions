/// Tools.hpp

#pragma once

using namespace PX::Information::NetworkedVariableManager;
using namespace PX::Types;

namespace PX::Tools
{
	class CBasePlayer;
	class CBaseEntity;

	CBasePlayer* PX_API GetLocalPlayer( );
	bool PX_API ValidPlayer( void* pEntity );

	// Game fucntions
	bool PX_API LineGoesThroughSmoke( Vector vecStartPos, Vector vecEndPos );
	void PX_API SetClantag( cstr_t szTag );
	void PX_API RevealRanks( );

	// Math
	void PX_API ClampAngles( QAngle& qAngles );
	bool PX_API WorldToScreen( Vector vecWorld, Vector& vecScreen );
	void PX_API TransformVector( Vector vecInput, matrix3x4_t mtxInput, Vector &vecOutput );
	Vector2D PX_API CalcAngle( Vector vecPosOne, Vector vecPosTwo );
	float PX_API GetAngleDistance( Vector vecCurrentAngles, Vector vecPosOne, Vector vecPosTwo );
	RECT PX_API CalculateRenderBounds( Vector* vecScreenPoints );
	RECT PX_API CalculateRenderBounds( CBaseEntity* pEntity );

	class CEconomyItemView
	{
	public:
		PX_NETVAR_REFERENCE( int32_t, m_bInitialized,PX_XOR( "DT_BaseAttributableItem" ), PX_XOR( "m_bInitialized" ) );
		PX_NETVAR_REFERENCE( int16_t, m_iItemDefinitionIndex,PX_XOR( "DT_BaseAttributableItem" ), PX_XOR( "m_iItemDefinitionIndex" ) );
		PX_NETVAR_REFERENCE( int32_t, m_iEntityLevel,PX_XOR( "DT_BaseAttributableItem" ), PX_XOR( "m_iEntityLevel" ) );
		PX_NETVAR_REFERENCE( int32_t, m_iAccountID,PX_XOR( "DT_BaseAttributableItem" ), PX_XOR( "m_iAccountID" ) );
		PX_NETVAR_REFERENCE( int32_t, m_iItemIDLow,PX_XOR( "DT_BaseAttributableItem" ), PX_XOR( "m_iItemIDLow" ) );
		PX_NETVAR_REFERENCE( int32_t, m_iItemIDHigh,PX_XOR( "DT_BaseAttributableItem" ), PX_XOR( "m_iItemIDHigh" ) );
		PX_NETVAR_REFERENCE( int32_t, m_iEntityQuality,PX_XOR( "DT_BaseAttributableItem" ), PX_XOR( "m_iEntityQuality" ) );
	};

	class CBaseEntity: public IClientEntity
	{
	public:
		PX_NETVAR_REFERENCE( int32_t, m_nModelIndex,PX_XOR( "DT_BaseEntity" ), PX_XOR( "m_nModelIndex" ) );
		PX_NETVAR_REFERENCE( int32_t, m_iTeamNum,PX_XOR( "DT_BaseEntity" ), PX_XOR( "m_iTeamNum" ) );
		PX_NETVAR_REFERENCE( Vector, m_vecOrigin,PX_XOR( "DT_BaseEntity" ), PX_XOR( "m_vecOrigin" ) );
		PX_NETVAR_REFERENCE( bool, m_bShouldGlow,PX_XOR( "DT_DynamicProp" ), PX_XOR( "m_bShouldGlow" ) );
		PX_NETVAR_REFERENCE( CHandle< CBasePlayer >, m_hOwnerEntity,PX_XOR( "DT_BaseEntity" ), PX_XOR( "m_hOwnerEntity" ) );
		PX_NETVAR_REFERENCE( float, m_flSimulationTime,PX_XOR( "DT_BaseEntity" ), PX_XOR( "m_flSimulationTime" ) );
		PX_NETVAR_REFERENCE_OFFSET( matrix3x4_t, m_rgflCoordinateFrame,PX_XOR( "DT_BaseEntity" ), PX_XOR( "m_CollisionGroup" ),  -int( 0x30 ) );

		bool IsPlayer( );
		bool IsWeapon( );
		bool IsPlantedC4( );
		bool IsDefuseKit( );
		float GetBombTimer( );
		float GetDefuseTimer( );
		Vector* BoundingBox( );
	};

	class CBaseAttributableItem: public CBaseEntity
	{
	public:
		PX_NETVAR_REFERENCE( uint64_t, m_OriginalOwnerXuid,PX_XOR( "DT_BaseAttributableItem" ), PX_XOR( "m_OriginalOwnerXuidLow" ) );
		PX_NETVAR_REFERENCE( int32_t, m_OriginalOwnerXuidLow,PX_XOR( "DT_BaseAttributableItem" ), PX_XOR( "m_OriginalOwnerXuidLow" ) );
		PX_NETVAR_REFERENCE( int32_t, m_OriginalOwnerXuidHigh,PX_XOR( "DT_BaseAttributableItem" ), PX_XOR( "m_OriginalOwnerXuidHigh" ) );
		PX_NETVAR_REFERENCE( int32_t, m_nFallbackStatTrak,PX_XOR( "DT_BaseAttributableItem" ), PX_XOR( "m_nFallbackStatTrak" ) );
		PX_NETVAR_REFERENCE( int32_t, m_nFallbackPaintKit,PX_XOR( "DT_BaseAttributableItem" ), PX_XOR( "m_nFallbackPaintKit" ) );
		PX_NETVAR_REFERENCE( int32_t, m_nFallbackSeed,PX_XOR( "DT_BaseAttributableItem" ), PX_XOR( "m_nFallbackSeed" ) );
		PX_NETVAR_REFERENCE( float_t, m_flFallbackWear,PX_XOR( "DT_BaseAttributableItem" ), PX_XOR( "m_flFallbackWear" ) );

		CEconomyItemView* m_Item( );
	};

	class CBaseCombatWeapon: public CBaseAttributableItem
	{
	public:
		PX_NETVAR_REFERENCE( float_t, m_flNextPrimaryAttack,PX_XOR( "DT_BaseCombatWeapon" ), PX_XOR( "m_flNextPrimaryAttack" ) );
		PX_NETVAR_REFERENCE( float_t, m_flNextSecondaryAttack,PX_XOR( "DT_BaseCombatWeapon" ), PX_XOR( "m_flNextSecondaryAttack" ) );
		PX_NETVAR_REFERENCE( int32_t, m_iClip1,PX_XOR( "DT_BaseCombatWeapon" ), PX_XOR( "m_iClip1" ) );
		PX_NETVAR_REFERENCE( int32_t, m_iClip2,PX_XOR( "DT_BaseCombatWeapon" ), PX_XOR( "m_iClip2" ) );
		PX_NETVAR_REFERENCE( float_t, m_flRecoilIndex,PX_XOR( "DT_WeaponCSBase" ), PX_XOR( "m_flRecoilIndex" ) );

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
		PX_NETVAR_REFERENCE( int32_t, m_nModelIndex,PX_XOR( "DT_BaseViewModel" ), PX_XOR( "m_nModelIndex" ) );
		PX_NETVAR_REFERENCE( int32_t, m_nViewModelIndex,PX_XOR( "DT_BaseViewModel" ), PX_XOR( "m_nViewModelIndex" ) );
		PX_NETVAR_REFERENCE( CHandle<CBaseCombatWeapon>, m_hWeapon,PX_XOR( "DT_BaseViewModel" ), PX_XOR( "m_hWeapon" ) );
		PX_NETVAR_REFERENCE( CHandle<CBasePlayer>, m_hOwner,PX_XOR( "DT_BaseViewModel" ), PX_XOR( "m_hOwner" ) );
	};

	class CBasePlayer: public CBaseEntity
	{
	public:
		PX_NETVAR_REFERENCE( bool, m_bHasDefuser,PX_XOR( "DT_CSPlayer" ), PX_XOR( "m_bHasDefuser" ) );
		PX_NETVAR_REFERENCE( bool, m_bGunGameImmunity,PX_XOR( "DT_CSPlayer" ), PX_XOR( "m_bGunGameImmunity" ) );
		PX_NETVAR_REFERENCE( int32_t, m_iShotsFired,PX_XOR( "DT_CSPlayer" ), PX_XOR( "m_iShotsFired" ) );
		PX_NETVAR_REFERENCE( QAngle, m_angEyeAngles,PX_XOR( "DT_CSPlayer" ), PX_XOR( "m_angEyeAngles[0]" ) );
		PX_NETVAR_REFERENCE( int, m_ArmorValue,PX_XOR( "DT_CSPlayer" ), PX_XOR( "m_ArmorValue" ) );
		PX_NETVAR_REFERENCE( bool, m_bHasHelmet,PX_XOR( "DT_CSPlayer" ), PX_XOR( "m_bHasHelmet" ) );
		PX_NETVAR_REFERENCE( bool, m_bIsScoped,PX_XOR( "DT_CSPlayer" ), PX_XOR( "m_bIsScoped" ) );;
		PX_NETVAR_REFERENCE( float, m_flLowerBodyYawTarget,PX_XOR( "DT_CSPlayer" ), PX_XOR( "m_flLowerBodyYawTarget" ) );
		PX_NETVAR_REFERENCE( float, m_flFlashDuration,PX_XOR( "DT_CSPlayer" ), PX_XOR( "m_flFlashDuration" ) );
		PX_NETVAR_REFERENCE( float, m_flFlashMaxAlpha,PX_XOR( "DT_CSPlayer" ), PX_XOR( "m_flFlashMaxAlpha" ) );
		PX_NETVAR_REFERENCE( int, m_totalHitsOnServer,PX_XOR( "DT_CSPlayer" ), PX_XOR( "m_totalHitsOnServer" ) );
		PX_NETVAR_REFERENCE( int32_t, m_iHealth,PX_XOR( "DT_BasePlayer" ), PX_XOR( "m_iHealth" ) );
		PX_NETVAR_REFERENCE( int32_t, m_lifeState,PX_XOR( "DT_BasePlayer" ), PX_XOR( "m_lifeState" ) );
		PX_NETVAR_REFERENCE( int32_t, m_fFlags,PX_XOR( "DT_BasePlayer" ), PX_XOR( "m_fFlags" ) );
		PX_NETVAR_REFERENCE( int32_t, m_nTickBase,PX_XOR( "DT_BasePlayer" ), PX_XOR( "m_nTickBase" ) );
		PX_NETVAR_REFERENCE( Vector, m_vecViewOffset,PX_XOR( "DT_BasePlayer" ), PX_XOR( "m_vecViewOffset[0]" ) );
		PX_NETVAR_REFERENCE( QAngle, m_viewPunchAngle,PX_XOR( "DT_BasePlayer" ), PX_XOR( "m_viewPunchAngle" ) );
		PX_NETVAR_REFERENCE( QAngle, m_aimPunchAngle,PX_XOR( "DT_BasePlayer" ), PX_XOR( "m_aimPunchAngle" ) );
		PX_NETVAR_REFERENCE( CHandle<CBaseViewModel>, m_hViewModel,PX_XOR( "DT_BasePlayer" ), PX_XOR( "m_hViewModel[0]" ) );
		PX_NETVAR_REFERENCE( Vector, m_vecVelocity,PX_XOR( "DT_BasePlayer" ), PX_XOR( "m_vecVelocity[0]" ) );
		PX_NETVAR_REFERENCE( float, m_flMaxspeed,PX_XOR( "DT_BasePlayer" ), PX_XOR( "m_flMaxspeed" ) );
		PX_NETVAR_REFERENCE( CHandle<CBasePlayer>, m_hObserverTarget,PX_XOR( "DT_BasePlayer" ), PX_XOR( "m_hObserverTarget" ) );
		PX_NETVAR_REFERENCE( int, m_iObserverMode,PX_XOR( "DT_BasePlayer" ), PX_XOR( "m_iObserverMode" ) );
		PX_NETVAR_REFERENCE( CHandle<CBaseCombatWeapon>, m_hActiveWeapon,PX_XOR( "DT_BaseCombatCharacter" ), PX_XOR( "m_hActiveWeapon" ) );
		PX_NETVAR_POINTER( CHandle<CBaseCombatWeapon>, m_hMyWeapons,PX_XOR( "DT_BaseCombatCharacter" ), PX_XOR( "m_hMyWeapons" ) );
		PX_NETVAR_POINTER( CHandle<CBaseAttributableItem>, m_hMyWearables,PX_XOR( "DT_BaseCombatCharacter" ), PX_XOR( "m_hMyWearables" ) );

		bool IsAlive( );
		Vector GetViewPosition( );
		bool PositionInSight( Vector& vecPosition, bool bMindSmoke, void* pEntity = nullptr );
		Vector GetHitboxPosition( EHitbox hHitboxID );
	};

	class CPlantedC4
	{
	public:
		PX_NETVAR_REFERENCE( bool, m_bBombTicking,PX_XOR( "DT_PlantedC4" ), PX_XOR( "m_bBombTicking" ) );
		PX_NETVAR_REFERENCE( bool, m_bBombDefused,PX_XOR( "DT_PlantedC4" ), PX_XOR( "m_bBombDefused" ) );
		PX_NETVAR_REFERENCE( float, m_flC4Blow,PX_XOR( "DT_PlantedC4" ), PX_XOR( "m_flC4Blow" ) );
		PX_NETVAR_REFERENCE( float, m_flTimerLength,PX_XOR( "DT_PlantedC4" ), PX_XOR( "m_flTimerLength" ) );
		PX_NETVAR_REFERENCE( float, m_flDefuseLength,PX_XOR( "DT_PlantedC4" ), PX_XOR( "m_flDefuseLength" ) );
		PX_NETVAR_REFERENCE( float, m_flDefuseCountDown,PX_XOR( "DT_PlantedC4" ), PX_XOR( "m_flDefuseCountDown" ) );
		PX_NETVAR_REFERENCE( CHandle< CBasePlayer >, m_hBombDefuser,PX_XOR( "DT_PlantedC4" ), PX_XOR( "m_hBombDefuser" ) );
	};
}
