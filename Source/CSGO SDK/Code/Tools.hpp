/// Tools.hpp

#pragma once

// SDK functions
struct bezier_order_t;

inline IHandleEntity *CBaseHandle::Get( ) const
{
	return pEntityList->GetClientEntityFromHandle( *this );
}

namespace Utilities
{
	class CBasePlayer;
	class CBaseEntity;

	void OnPaintTraverse( );
	CBasePlayer *GetLocalPlayer( );
	CUserCmd *GetUserCmd( int iSequenceNumber );
	CVerifiedUserCmd *GetVerifiedUserCmd( int iSequenceNumber );
	CUserCmd &GetLastUserCmd( );
	CRC32_t GetCmdHash( CUserCmd *pCmd );
	bool ValidPlayer( void *pEntity );
	void RepairBoneRendering( );
	void BeginPrediction( CUserCmd* pCmd );
	void EndPrediction();

	// CVars
	float GetRecoilScale( );

	// Game fucntions
	bool LineGoesThroughSmoke( Vector vecStartPos, Vector vecEndPos );
	void SetClantag( const char *szTag );
	void RevealRanks( );
	/*
		template< typename _t > _t *FindHudElement( const char *szName )
		{
			static auto pHudInterface = *reinterpret_cast< void** >( Information::Modules::mClient.FindPattern( Information::jsMemoryInformation[ ENC( "Patterns" ) ][ ENC( "Signatures" ) ][ ENC( "Hud Interface" ) ].get< str_t >( ) )
				+ Information::jsMemoryInformation[ ENC( "Patterns" ) ][ ENC( "Offsets" ) ][ ENC( "Hud Interface" ) ].get< int >( ) );
			static auto ptrFindHudElement = uintptr_t( Information::Modules::mClient.FindPattern( Information::jsMemoryInformation[ ENC( "Patterns" ) ][ ENC( "Signatures" ) ][ ENC( "Find Hud Element" ) ].get< str_t >( ) )
												  + Information::jsMemoryInformation[ ENC( "Patterns" ) ][ ENC( "Offsets" ) ][ ENC( "Find Hud Element" ) ].get< int >( ) );
			return reinterpret_cast< _t* >( reinterpret_cast< void*( __thiscall*)( void *, Types::cstr_t ) >( ptrFindHudElement )( pHudInterface, szName ) );
		}*/

	// Math
	void ClampAngles( QAngle &qAngles );
	void ClampAngles( Vector &vecAngles );
	void HumanizeAngles( QAngle &qAngles, PX::Tools::CBasePlayer *pLocalPlayer );
	void HumanizeAngles( Vector &vecAngles, PX::Tools::CBasePlayer *pLocalPlayer );
	bool WorldToScreen( const Vector &vecWorld, Vector &vecScreen );
	bool AngleToScreen( const Vector &vecAngle, const Vector &vecOrigin, Vector &vecScreen );
	void TransformVector( Vector vecInput, matrix3x4_t mtxInput, Vector &vecOutput );
	void TransformAngle( const QAngle &qAngles, Vector &vecForward );
	void TransformAngle( const Vector &vecAngles, Vector &vecForward );
	Vector2D CalcAngle( Vector vecPosOne, Vector vecPosTwo );
	float GetAngleDistance( Vector vecCurrentAngles, Vector vecPosOne, Vector vecPosTwo );
	RECT CalculateRenderBounds( Vector *vecScreenPoints );
	RECT CalculateRenderBounds( CBaseEntity *pEntity );
	float CalculateVectorDistance( const Vector &vecPositionOne, const Vector &vecPositionTwo );
	QAngle CalculateAngle( const Vector &vecFirst, const Vector &vecSecond );
	QAngle CalculateAngle( CBasePlayer *pLocalPlayer, CBasePlayer *pPlayer, int iHitbox, CUserCmd *pCmd, Vector *vecOverCompensation );
	float CalculateCrosshairDistance( CBasePlayer *pLocalPlayer, CBasePlayer *pPlayer, int iHitbox, CUserCmd *pCmd, bool bWorldlyDistance );

	std::vector< Vector > GetBezierPoints( Vector vecStart, Vector vecEnd, bezier_order_t *pOrders, std::size_t zOrders );
	Vector GetBezierPoint( std::vector< Vector > vecPoints, float flRatio );

	class CEconomyItemView
	{
	public:
		NETVAR_REFERENCE( int32_t, m_bInitialized, ENC( "DT_BaseAttributableItem" ), ENC( "m_bInitialized" ) );
		NETVAR_REFERENCE( int16_t, m_iItemDefinitionIndex, ENC( "DT_BaseAttributableItem" ), ENC( "m_iItemDefinitionIndex" ) );
		NETVAR_REFERENCE( int32_t, m_iEntityLevel, ENC( "DT_BaseAttributableItem" ), ENC( "m_iEntityLevel" ) );
		NETVAR_REFERENCE( int32_t, m_iAccountID, ENC( "DT_BaseAttributableItem" ), ENC( "m_iAccountID" ) );
		NETVAR_REFERENCE( int32_t, m_iItemIDLow, ENC( "DT_BaseAttributableItem" ), ENC( "m_iItemIDLow" ) );
		NETVAR_REFERENCE( int32_t, m_iItemIDHigh, ENC( "DT_BaseAttributableItem" ), ENC( "m_iItemIDHigh" ) );
		NETVAR_REFERENCE( int32_t, m_iEntityQuality, ENC( "DT_BaseAttributableItem" ), ENC( "m_iEntityQuality" ) );

		CUtlVector< IRefCounted* > *m_CustomMaterials( )
		{
			return reinterpret_cast< CUtlVector< IRefCounted* >* >( uintptr_t( this ) + 0x14 );
		}

		CUtlVector< IRefCounted* > *m_VisualsDataProcessors( )
		{
			//static const auto ptrOffset = *reinterpret_cast< uintptr_t* >( Information::Modules::mClient.FindPattern( Information::jsMemoryInformation[ ENC( "Patterns" ) ][ ENC( "Signatures" ) ][ ENC( "m_VisualsDataProcessors" ) ].get< str_t >( ) )
			//							 + Information::jsMemoryInformation[ ENC( "Patterns" ) ][ ENC( "Offsets" ) ][ ENC( "m_VisualsDataProcessors" ) ].get< int >( ) );
			//return reinterpret_cast< CUtlVector<IRefCounted*>* >( uintptr_t( this ) + ptrOffset );
			return reinterpret_cast< CUtlVector< IRefCounted* >* >( uintptr_t( this ) + 0x0220 );
		}
	};

	class CEnvTonemapController: public IClientEntity
	{
	public:

		NETVAR_REFERENCE( bool, m_bUseCustomAutoExposureMin, ENC( "DT_EnvTonemapController" ), ENC( "m_bUseCustomAutoExposureMin" ) );
		NETVAR_REFERENCE( bool, m_bUseCustomAutoExposureMax, ENC( "DT_EnvTonemapController" ), ENC( "m_bUseCustomAutoExposureMax" ) );
		NETVAR_REFERENCE( float, m_flCustomAutoExposureMin, ENC( "DT_EnvTonemapController" ), ENC( "m_flCustomAutoExposureMin" ) );
		NETVAR_REFERENCE( float, m_flCustomAutoExposureMax, ENC( "DT_EnvTonemapController" ), ENC( "m_flCustomAutoExposureMax" ) );
	};

	class CBaseEntity: public IClientEntity
	{
	public:
		NETVAR_REFERENCE( int32_t, m_iTeamNum, ENC( "DT_BaseEntity" ), ENC( "m_iTeamNum" ) );
		NETVAR_REFERENCE( Vector, m_vecOrigin, ENC( "DT_BaseEntity" ), ENC( "m_vecOrigin" ) );
		NETVAR_REFERENCE( bool, m_bShouldGlow, ENC( "DT_DynamicProp" ), ENC( "m_bShouldGlow" ) );
		NETVAR_REFERENCE( CBasePlayer*, m_hOwnerEntity, ENC( "DT_BaseEntity" ), ENC( "m_hOwnerEntity" ) );
		NETVAR_REFERENCE( float, m_flSimulationTime, ENC( "DT_BaseEntity" ), ENC( "m_flSimulationTime" ) );
		NETVAR_REFERENCE_OFFSET( matrix3x4_t, m_rgflCoordinateFrame, ENC( "DT_BaseEntity" ), ENC( "m_CollisionGroup" ), -int( 0x30 ) );
		NETVAR_REFERENCE_OFFSET( int32_t, GetIndex, ENC( "CBaseEntity" ), ENC( "m_bIsAutoaimTarget" ), 0x4 );
		NETVAR_REFERENCE( int32_t, movetype, ENC( "DT_BaseEntity" ), ENC( "movetype" ) );

		bool IsPlayer( );
		bool IsWeapon( );
		bool IsPlantedC4( );
		bool IsDefuseKit( );
		bool IsGrenade( );
		float GetBombTimer( );
		float GetDefuseTimer( );
		Vector *BoundingBox( );
		void SetABSOrigin( Vector &vecOrigin );
	};

	class CBaseAttributableItem: public CBaseEntity
	{
	public:
		NETVAR_REFERENCE( uint64_t, m_OriginalOwnerXuid, ENC( "DT_BaseAttributableItem" ), ENC( "m_OriginalOwnerXuidLow" ) );
		NETVAR_REFERENCE( int32_t, m_OriginalOwnerXuidLow, ENC( "DT_BaseAttributableItem" ), ENC( "m_OriginalOwnerXuidLow" ) );
		NETVAR_REFERENCE( int32_t, m_OriginalOwnerXuidHigh, ENC( "DT_BaseAttributableItem" ), ENC( "m_OriginalOwnerXuidHigh" ) );
		NETVAR_REFERENCE( int32_t, m_nFallbackStatTrak, ENC( "DT_BaseAttributableItem" ), ENC( "m_nFallbackStatTrak" ) );
		NETVAR_REFERENCE( int32_t, m_nFallbackPaintKit, ENC( "DT_BaseAttributableItem" ), ENC( "m_nFallbackPaintKit" ) );
		NETVAR_REFERENCE( int32_t, m_nFallbackSeed, ENC( "DT_BaseAttributableItem" ), ENC( "m_nFallbackSeed" ) );
		NETVAR_REFERENCE( float_t, m_flFallbackWear, ENC( "DT_BaseAttributableItem" ), ENC( "m_flFallbackWear" ) );
		NETVAR_REFERENCE( char*, m_szCustomName, ENC( "DT_BaseAttributableItem" ), ENC( "m_szCustomName" ) );

		CEconomyItemView *m_Item( );
	};

	class CBaseCombatWeapon: public CBaseAttributableItem
	{
	public:
		NETVAR_REFERENCE( float_t, m_flNextPrimaryAttack, ENC( "DT_BaseCombatWeapon" ), ENC( "m_flNextPrimaryAttack" ) );
		NETVAR_REFERENCE( float_t, m_flNextSecondaryAttack, ENC( "DT_BaseCombatWeapon" ), ENC( "m_flNextSecondaryAttack" ) );
		NETVAR_REFERENCE( int32_t, m_iClip1, ENC( "DT_BaseCombatWeapon" ), ENC( "m_iClip1" ) );
		NETVAR_REFERENCE( int32_t, m_iClip2, ENC( "DT_BaseCombatWeapon" ), ENC( "m_iClip2" ) );
		NETVAR_REFERENCE( float_t, m_flRecoilIndex, ENC( "DT_WeaponCSBase" ), ENC( "m_flRecoilIndex" ) );/*

		CUtlVector< IRefCounted* > *m_CustomMaterials( )
		{
			static const auto ptrOffset = uintptr_t( *reinterpret_cast< uintptr_t* >( Information::Modules::mClient.FindPattern( Information::jsMemoryInformation[ ENC( "Patterns" ) ][ ENC( "Signatures" ) ][ ENC( "m_CustomMaterials" ) ].get< std::string >( ) )
													+ Information::jsMemoryInformation[ ENC( "Patterns" ) ][ ENC( "Offsets" ) ][ ENC( "m_CustomMaterials" ) ].get< int >( ) ) ) - 12;
			return reinterpret_cast< CUtlVector< IRefCounted* >* >( uintptr_t( this ) + ptrOffset );
		}

		bool &m_bCustomMaterialInitialized( )
		{
			static const auto ptrOffset = *reinterpret_cast< uintptr_t* >( Information::Modules::mClient.FindPattern( Information::jsMemoryInformation[ ENC( "Patterns" ) ][ ENC( "Signatures" ) ][ ENC( "m_bCustomMaterialInitialized" ) ].get< std::string >( ) )
				+ Information::jsMemoryInformation[ ENC( "Patterns" ) ][ ENC( "Offsets" ) ][ ENC( "m_bCustomMaterialInitialized" ) ].get< int >( ) );
			return *reinterpret_cast< bool* >( uintptr_t( this ) + ptrOffset );
		}
*/
		CCSWeaponInfo *GetCSWeaponData( );
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
		float GetNextShotTime( );
	};

	class CBaseViewModel: public CBaseEntity
	{
	public:
		NETVAR_REFERENCE( int32_t, m_nModelIndex, ENC( "DT_BaseViewModel" ), ENC( "m_nModelIndex" ) );
		NETVAR_REFERENCE( int32_t, m_nWorldModelIndex, ENC( "DT_BaseViewModel" ), ENC( "m_nWorldModelIndex" ) );
		NETVAR_REFERENCE( int32_t, m_nViewModelIndex, ENC( "DT_BaseViewModel" ), ENC( "m_nViewModelIndex" ) );
		NETVAR_REFERENCE( CHandle<CBaseCombatWeapon>, m_hWeapon, ENC( "DT_BaseViewModel" ), ENC( "m_hWeapon" ) );
		NETVAR_REFERENCE( CHandle<CBasePlayer>, m_hOwner, ENC( "DT_BaseViewModel" ), ENC( "m_hOwner" ) );
	};

	class CBasePlayer: public CBaseEntity
	{
	public:
		NETVAR_REFERENCE( bool, m_bHasDefuser, ENC( "DT_CSPlayer" ), ENC( "m_bHasDefuser" ) );
		NETVAR_REFERENCE( bool, m_bGunGameImmunity, ENC( "DT_CSPlayer" ), ENC( "m_bGunGameImmunity" ) );
		NETVAR_REFERENCE( int32_t, m_iShotsFired, ENC( "DT_CSPlayer" ), ENC( "m_iShotsFired" ) );
		NETVAR_REFERENCE( QAngle, m_angEyeAngles, ENC( "DT_CSPlayer" ), ENC( "m_angEyeAngles[0]" ) );
		NETVAR_REFERENCE( int, m_ArmorValue, ENC( "DT_CSPlayer" ), ENC( "m_ArmorValue" ) );
		NETVAR_REFERENCE( bool, m_bHasHelmet, ENC( "DT_CSPlayer" ), ENC( "m_bHasHelmet" ) );
		NETVAR_REFERENCE( bool, m_bIsScoped, ENC( "DT_CSPlayer" ), ENC( "m_bIsScoped" ) );;
		NETVAR_REFERENCE( float, m_flLowerBodyYawTarget, ENC( "DT_CSPlayer" ), ENC( "m_flLowerBodyYawTarget" ) );
		NETVAR_REFERENCE( float, m_flFlashDuration, ENC( "DT_CSPlayer" ), ENC( "m_flFlashDuration" ) );
		NETVAR_REFERENCE( float, m_flFlashMaxAlpha, ENC( "DT_CSPlayer" ), ENC( "m_flFlashMaxAlpha" ) );
		NETVAR_REFERENCE( int, m_totalHitsOnServer, ENC( "DT_CSPlayer" ), ENC( "m_totalHitsOnServer" ) );
		NETVAR_REFERENCE( int32_t, m_iHealth, ENC( "DT_BasePlayer" ), ENC( "m_iHealth" ) );
		NETVAR_REFERENCE( int32_t, m_lifeState, ENC( "DT_BasePlayer" ), ENC( "m_lifeState" ) );
		NETVAR_REFERENCE( int32_t, m_fFlags, ENC( "DT_BasePlayer" ), ENC( "m_fFlags" ) );
		NETVAR_REFERENCE( int32_t, m_nTickBase, ENC( "DT_BasePlayer" ), ENC( "m_nTickBase" ) );
		NETVAR_REFERENCE( Vector, m_vecViewOffset, ENC( "DT_BasePlayer" ), ENC( "m_vecViewOffset[0]" ) );
		NETVAR_REFERENCE( QAngle, m_viewPunchAngle, ENC( "DT_BasePlayer" ), ENC( "m_viewPunchAngle" ) );
		NETVAR_REFERENCE( QAngle, m_aimPunchAngle, ENC( "DT_BasePlayer" ), ENC( "m_aimPunchAngle" ) );
		NETVAR_REFERENCE( CHandle<CBaseViewModel>, m_hViewModel, ENC( "DT_BasePlayer" ), ENC( "m_hViewModel[0]" ) );
		NETVAR_REFERENCE( Vector, m_vecVelocity, ENC( "DT_BasePlayer" ), ENC( "m_vecVelocity[0]" ) );
		NETVAR_REFERENCE( float, m_flMaxspeed, ENC( "DT_BasePlayer" ), ENC( "m_flMaxspeed" ) );
		NETVAR_REFERENCE( CHandle<CBasePlayer>, m_hObserverTarget, ENC( "DT_BasePlayer" ), ENC( "m_hObserverTarget" ) );
		NETVAR_REFERENCE( int, m_iObserverMode, ENC( "DT_BasePlayer" ), ENC( "m_iObserverMode" ) );
		NETVAR_REFERENCE( CHandle< CBaseCombatWeapon >, m_hActiveWeapon, ENC( "DT_BaseCombatCharacter" ), ENC( "m_hActiveWeapon" ) );
		NETVAR_POINTER( CHandle< CBaseCombatWeapon >, m_hMyWeapons, ENC( "DT_BaseCombatCharacter" ), ENC( "m_hMyWeapons" ) );
		NETVAR_POINTER( CHandle<CBaseAttributableItem>, m_hMyWearables, ENC( "DT_BaseCombatCharacter" ), ENC( "m_hMyWearables" ) );
		NETVAR_POINTER( bool, m_bSpotted, ENC( "DT_CSPlayerResource" ), ENC( "m_bSpotted" ) );
		NETVAR_REFERENCE_OFFSET( CUserCmd*, m_pCurrentCommand, ENC( "DT_BasePlayer" ), ENC( "m_hConstraintEntity" ), -int( 0xC ) );
		int m_iTickBase( );

		bool IsAlive( );
		bool IsLocalPlayer( );
		Vector GetViewPosition( );
		player_info_t GetPlayerInformation( );
		bool CanSeePosition( Vector vecPosition, bool bMindSmoke, void *pEntity = nullptr );
		bool CanSeePlayer( CBasePlayer *pPlayer, bool bMindSmoke );
		CGameTrace &TraceRayFromAngle( const QAngle &qAngle );
		CGameTrace &TraceRayFromView( CUserCmd *pCmd = nullptr );
		Vector GetHitboxPosition( int hHitboxID );
		bool IsVulnerable( );
		float DistanceFromPlayer( CBasePlayer *pPlayer );
	};

	class CPlantedC4
	{
	public:
		NETVAR_REFERENCE( bool, m_bBombTicking, ENC( "DT_PlantedC4" ), ENC( "m_bBombTicking" ) );
		NETVAR_REFERENCE( bool, m_bBombDefused, ENC( "DT_PlantedC4" ), ENC( "m_bBombDefused" ) );
		NETVAR_REFERENCE( float, m_flC4Blow, ENC( "DT_PlantedC4" ), ENC( "m_flC4Blow" ) );
		NETVAR_REFERENCE( float, m_flTimerLength, ENC( "DT_PlantedC4" ), ENC( "m_flTimerLength" ) );
		NETVAR_REFERENCE( float, m_flDefuseLength, ENC( "DT_PlantedC4" ), ENC( "m_flDefuseLength" ) );
		NETVAR_REFERENCE( float, m_flDefuseCountDown, ENC( "DT_PlantedC4" ), ENC( "m_flDefuseCountDown" ) );
		NETVAR_REFERENCE( CHandle< CBasePlayer >, m_hBombDefuser, ENC( "DT_PlantedC4" ), ENC( "m_hBombDefuser" ) );
	};
}

#include "Valve/Attributes.hpp"
#include "Valve/C_EconItemView.h"
#include "Valve/CEconItem.hpp"
#include "Valve/CSharedObjectTypeCache.hpp"
#include "Valve/CPlayerInventory.hpp"
