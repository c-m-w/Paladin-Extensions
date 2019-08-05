/// Tools.hpp

#pragma once

// SDK functions
struct bezier_order_t;

namespace PX::Information::NetworkedVariableManager
{
	// todo
	int FindOffset( const char *bob, const char *boob )
	{
		return 0;
	}
}


inline IHandleEntity *CBaseHandle::Get( ) const
{
	return Interfaces::pEntityList->GetClientEntityFromHandle( *this );
}

namespace PX::Tools
{
	class CBasePlayer;
	class CBaseEntity;

	void OnPaintTraverse( );
	CBasePlayer * GetLocalPlayer( );
	CUserCmd * GetUserCmd( int iSequenceNumber );
	CVerifiedUserCmd * GetVerifiedUserCmd( int iSequenceNumber );
	CUserCmd & GetLastUserCmd( );
	CRC32_t GetCmdHash( CUserCmd *pCmd );
	bool ValidPlayer( void *pEntity );
	void RepairBoneRendering( );

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
		PX_NETVAR_REFERENCE( int32_t, m_bInitialized,ENC( "DT_BaseAttributableItem" ), ENC( "m_bInitialized" ) );
		PX_NETVAR_REFERENCE( int16_t, m_iItemDefinitionIndex,ENC( "DT_BaseAttributableItem" ), ENC( "m_iItemDefinitionIndex" ) );
		PX_NETVAR_REFERENCE( int32_t, m_iEntityLevel,ENC( "DT_BaseAttributableItem" ), ENC( "m_iEntityLevel" ) );
		PX_NETVAR_REFERENCE( int32_t, m_iAccountID,ENC( "DT_BaseAttributableItem" ), ENC( "m_iAccountID" ) );
		PX_NETVAR_REFERENCE( int32_t, m_iItemIDLow,ENC( "DT_BaseAttributableItem" ), ENC( "m_iItemIDLow" ) );
		PX_NETVAR_REFERENCE( int32_t, m_iItemIDHigh,ENC( "DT_BaseAttributableItem" ), ENC( "m_iItemIDHigh" ) );
		PX_NETVAR_REFERENCE( int32_t, m_iEntityQuality,ENC( "DT_BaseAttributableItem" ), ENC( "m_iEntityQuality" ) );

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

		PX_NETVAR_REFERENCE( bool, m_bUseCustomAutoExposureMin, ENC( "DT_EnvTonemapController" ), ENC( "m_bUseCustomAutoExposureMin" ) );
		PX_NETVAR_REFERENCE( bool, m_bUseCustomAutoExposureMax, ENC( "DT_EnvTonemapController" ), ENC( "m_bUseCustomAutoExposureMax" ) );
		PX_NETVAR_REFERENCE( float, m_flCustomAutoExposureMin, ENC( "DT_EnvTonemapController" ), ENC( "m_flCustomAutoExposureMin" ) );
		PX_NETVAR_REFERENCE( float, m_flCustomAutoExposureMax, ENC( "DT_EnvTonemapController" ), ENC( "m_flCustomAutoExposureMax" ) );
	};

	class CBaseEntity: public IClientEntity
	{
	public:
		PX_NETVAR_REFERENCE( int32_t, m_iTeamNum,ENC( "DT_BaseEntity" ), ENC( "m_iTeamNum" ) );
		PX_NETVAR_REFERENCE( Vector, m_vecOrigin,ENC( "DT_BaseEntity" ), ENC( "m_vecOrigin" ) );
		PX_NETVAR_REFERENCE( bool, m_bShouldGlow,ENC( "DT_DynamicProp" ), ENC( "m_bShouldGlow" ) );
		PX_NETVAR_REFERENCE( CBasePlayer*, m_hOwnerEntity,ENC( "DT_BaseEntity" ), ENC( "m_hOwnerEntity" ) );
		PX_NETVAR_REFERENCE( float, m_flSimulationTime,ENC( "DT_BaseEntity" ), ENC( "m_flSimulationTime" ) );
		PX_NETVAR_REFERENCE_OFFSET( matrix3x4_t, m_rgflCoordinateFrame, ENC( "DT_BaseEntity" ), ENC( "m_CollisionGroup" ), -int( 0x30 ) );
		PX_NETVAR_REFERENCE_OFFSET( int32_t, GetIndex, ENC( "CBaseEntity" ), ENC( "m_bIsAutoaimTarget" ), 0x4 );
		PX_NETVAR_REFERENCE( int32_t, movetype, ENC( "DT_BaseEntity" ), ENC( "movetype" ) );

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
		PX_NETVAR_REFERENCE( uint64_t, m_OriginalOwnerXuid,ENC( "DT_BaseAttributableItem" ), ENC( "m_OriginalOwnerXuidLow" ) );
		PX_NETVAR_REFERENCE( int32_t, m_OriginalOwnerXuidLow,ENC( "DT_BaseAttributableItem" ), ENC( "m_OriginalOwnerXuidLow" ) );
		PX_NETVAR_REFERENCE( int32_t, m_OriginalOwnerXuidHigh,ENC( "DT_BaseAttributableItem" ), ENC( "m_OriginalOwnerXuidHigh" ) );
		PX_NETVAR_REFERENCE( int32_t, m_nFallbackStatTrak,ENC( "DT_BaseAttributableItem" ), ENC( "m_nFallbackStatTrak" ) );
		PX_NETVAR_REFERENCE( int32_t, m_nFallbackPaintKit,ENC( "DT_BaseAttributableItem" ), ENC( "m_nFallbackPaintKit" ) );
		PX_NETVAR_REFERENCE( int32_t, m_nFallbackSeed,ENC( "DT_BaseAttributableItem" ), ENC( "m_nFallbackSeed" ) );
		PX_NETVAR_REFERENCE( float_t, m_flFallbackWear,ENC( "DT_BaseAttributableItem" ), ENC( "m_flFallbackWear" ) );
		PX_NETVAR_REFERENCE( char*, m_szCustomName, ENC( "DT_BaseAttributableItem" ), ENC( "m_szCustomName" ) );

		CEconomyItemView *m_Item( );
	};

	class CBaseCombatWeapon: public CBaseAttributableItem
	{
	public:
		PX_NETVAR_REFERENCE( float_t, m_flNextPrimaryAttack,ENC( "DT_BaseCombatWeapon" ), ENC( "m_flNextPrimaryAttack" ) );
		PX_NETVAR_REFERENCE( float_t, m_flNextSecondaryAttack,ENC( "DT_BaseCombatWeapon" ), ENC( "m_flNextSecondaryAttack" ) );
		PX_NETVAR_REFERENCE( int32_t, m_iClip1,ENC( "DT_BaseCombatWeapon" ), ENC( "m_iClip1" ) );
		PX_NETVAR_REFERENCE( int32_t, m_iClip2,ENC( "DT_BaseCombatWeapon" ), ENC( "m_iClip2" ) );
		PX_NETVAR_REFERENCE( float_t, m_flRecoilIndex,ENC( "DT_WeaponCSBase" ), ENC( "m_flRecoilIndex" ) );/*

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
		PX_NETVAR_REFERENCE( int32_t, m_nModelIndex, ENC( "DT_BaseViewModel" ), ENC( "m_nModelIndex" ) );
		PX_NETVAR_REFERENCE( int32_t, m_nWorldModelIndex, ENC( "DT_BaseViewModel" ), ENC( "m_nWorldModelIndex" ) );
		PX_NETVAR_REFERENCE( int32_t, m_nViewModelIndex,ENC( "DT_BaseViewModel" ), ENC( "m_nViewModelIndex" ) );
		PX_NETVAR_REFERENCE( CHandle<CBaseCombatWeapon>, m_hWeapon,ENC( "DT_BaseViewModel" ), ENC( "m_hWeapon" ) );
		PX_NETVAR_REFERENCE( CHandle<CBasePlayer>, m_hOwner,ENC( "DT_BaseViewModel" ), ENC( "m_hOwner" ) );
	};

	class CBasePlayer: public CBaseEntity
	{
	public:
		PX_NETVAR_REFERENCE( bool, m_bHasDefuser,ENC( "DT_CSPlayer" ), ENC( "m_bHasDefuser" ) );
		PX_NETVAR_REFERENCE( bool, m_bGunGameImmunity,ENC( "DT_CSPlayer" ), ENC( "m_bGunGameImmunity" ) );
		PX_NETVAR_REFERENCE( int32_t, m_iShotsFired,ENC( "DT_CSPlayer" ), ENC( "m_iShotsFired" ) );
		PX_NETVAR_REFERENCE( QAngle, m_angEyeAngles,ENC( "DT_CSPlayer" ), ENC( "m_angEyeAngles[0]" ) );
		PX_NETVAR_REFERENCE( int, m_ArmorValue,ENC( "DT_CSPlayer" ), ENC( "m_ArmorValue" ) );
		PX_NETVAR_REFERENCE( bool, m_bHasHelmet,ENC( "DT_CSPlayer" ), ENC( "m_bHasHelmet" ) );
		PX_NETVAR_REFERENCE( bool, m_bIsScoped,ENC( "DT_CSPlayer" ), ENC( "m_bIsScoped" ) );;
		PX_NETVAR_REFERENCE( float, m_flLowerBodyYawTarget,ENC( "DT_CSPlayer" ), ENC( "m_flLowerBodyYawTarget" ) );
		PX_NETVAR_REFERENCE( float, m_flFlashDuration,ENC( "DT_CSPlayer" ), ENC( "m_flFlashDuration" ) );
		PX_NETVAR_REFERENCE( float, m_flFlashMaxAlpha,ENC( "DT_CSPlayer" ), ENC( "m_flFlashMaxAlpha" ) );
		PX_NETVAR_REFERENCE( int, m_totalHitsOnServer,ENC( "DT_CSPlayer" ), ENC( "m_totalHitsOnServer" ) );
		PX_NETVAR_REFERENCE( int32_t, m_iHealth,ENC( "DT_BasePlayer" ), ENC( "m_iHealth" ) );
		PX_NETVAR_REFERENCE( int32_t, m_lifeState,ENC( "DT_BasePlayer" ), ENC( "m_lifeState" ) );
		PX_NETVAR_REFERENCE( int32_t, m_fFlags,ENC( "DT_BasePlayer" ), ENC( "m_fFlags" ) );
		PX_NETVAR_REFERENCE( int32_t, m_nTickBase,ENC( "DT_BasePlayer" ), ENC( "m_nTickBase" ) );
		PX_NETVAR_REFERENCE( Vector, m_vecViewOffset,ENC( "DT_BasePlayer" ), ENC( "m_vecViewOffset[0]" ) );
		PX_NETVAR_REFERENCE( QAngle, m_viewPunchAngle,ENC( "DT_BasePlayer" ), ENC( "m_viewPunchAngle" ) );
		PX_NETVAR_REFERENCE( QAngle, m_aimPunchAngle,ENC( "DT_BasePlayer" ), ENC( "m_aimPunchAngle" ) );
		PX_NETVAR_REFERENCE( CHandle<CBaseViewModel>, m_hViewModel,ENC( "DT_BasePlayer" ), ENC( "m_hViewModel[0]" ) );
		PX_NETVAR_REFERENCE( Vector, m_vecVelocity,ENC( "DT_BasePlayer" ), ENC( "m_vecVelocity[0]" ) );
		PX_NETVAR_REFERENCE( float, m_flMaxspeed,ENC( "DT_BasePlayer" ), ENC( "m_flMaxspeed" ) );
		PX_NETVAR_REFERENCE( CHandle<CBasePlayer>, m_hObserverTarget,ENC( "DT_BasePlayer" ), ENC( "m_hObserverTarget" ) );
		PX_NETVAR_REFERENCE( int, m_iObserverMode,ENC( "DT_BasePlayer" ), ENC( "m_iObserverMode" ) );
		PX_NETVAR_REFERENCE( CHandle< CBaseCombatWeapon >, m_hActiveWeapon,ENC( "DT_BaseCombatCharacter" ), ENC( "m_hActiveWeapon" ) );
		PX_NETVAR_POINTER( CHandle< CBaseCombatWeapon >, m_hMyWeapons,ENC( "DT_BaseCombatCharacter" ), ENC( "m_hMyWeapons" ) );
		PX_NETVAR_POINTER( CHandle<CBaseAttributableItem>, m_hMyWearables, ENC( "DT_BaseCombatCharacter" ), ENC( "m_hMyWearables" ) );
		PX_NETVAR_POINTER( bool, m_bSpotted, ENC( "DT_CSPlayerResource" ), ENC( "m_bSpotted" ) );
		PX_NETVAR_REFERENCE_OFFSET( CUserCmd*, m_pCurrentCommand, ENC( "DT_BasePlayer" ), ENC( "m_hConstraintEntity" ), -int( 0xC ) );

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
		PX_NETVAR_REFERENCE( bool, m_bBombTicking,ENC( "DT_PlantedC4" ), ENC( "m_bBombTicking" ) );
		PX_NETVAR_REFERENCE( bool, m_bBombDefused,ENC( "DT_PlantedC4" ), ENC( "m_bBombDefused" ) );
		PX_NETVAR_REFERENCE( float, m_flC4Blow,ENC( "DT_PlantedC4" ), ENC( "m_flC4Blow" ) );
		PX_NETVAR_REFERENCE( float, m_flTimerLength,ENC( "DT_PlantedC4" ), ENC( "m_flTimerLength" ) );
		PX_NETVAR_REFERENCE( float, m_flDefuseLength,ENC( "DT_PlantedC4" ), ENC( "m_flDefuseLength" ) );
		PX_NETVAR_REFERENCE( float, m_flDefuseCountDown,ENC( "DT_PlantedC4" ), ENC( "m_flDefuseCountDown" ) );
		PX_NETVAR_REFERENCE( CHandle< CBasePlayer >, m_hBombDefuser,ENC( "DT_PlantedC4" ), ENC( "m_hBombDefuser" ) );
	};
}
