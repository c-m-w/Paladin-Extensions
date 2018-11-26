/// Tools.hpp

#pragma once

using namespace PX::Information::NetworkedVariableManager;
using namespace PX::Types;
using namespace PX::Information::Pointers;

// SDK functions

inline IHandleEntity* CBaseHandle::Get( ) const
{
	return PX::Information::Pointers::pEntityList->GetClientEntityFromHandle( *this );
}

namespace PX::Tools
{
	class CBasePlayer;
	class CBaseEntity;

	void PX_API OnPaintTraverse( );
	CBasePlayer* PX_API GetLocalPlayer( );
	CUserCmd* PX_API GetUserCmd( int iSequenceNumber );
	CVerifiedUserCmd* PX_API GetVerifiedUserCmd( int iSequenceNumber );
	CUserCmd& PX_API GetLastUserCmd( );
	CRC32_t PX_API GetCmdHash( CUserCmd* pCmd );
	bool PX_API ValidPlayer( void* pEntity );
	void PX_API RepairBoneRendering( );

	// CVars
	float PX_API GetRecoilScale( );

	// Game fucntions
	bool PX_API LineGoesThroughSmoke( Vector vecStartPos, Vector vecEndPos );
	void PX_API SetClantag( cstr_t szTag );
	void PX_API RevealRanks( );
	template< typename _t > _t* FindHudElement( Types::cstr_t szName )
	{
		static auto pHudInterface = *reinterpret_cast<void**>( Information::Modules::mClient.FindPattern( Information::jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Signatures" ) ][ PX_XOR( "Hud Interface" ) ].get< str_t >( ) )
										   + Information::jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Offsets" ) ][ PX_XOR( "Hud Interface" ) ].get< int >( ) );
		static auto ptrFindHudElement = ptr_t( Information::Modules::mClient.FindPattern( Information::jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Signatures" ) ][ PX_XOR( "Find Hud Element" ) ].get< str_t >( ) )
			+ Information::jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Offsets" ) ][ PX_XOR( "Find Hud Element" ) ].get< int >( ) );
		return reinterpret_cast< _t* >( reinterpret_cast< void*( __thiscall* )( void*, Types::cstr_t ) >( ptrFindHudElement )( pHudInterface, szName ) );
	}

	// Math
	void PX_API ClampAngles( QAngle& qAngles );
	void PX_API ClampAngles( Vector& vecAngles );
	void PX_API HumanizeAngles( QAngle& qAngles, PX::Tools::CBasePlayer* pLocalPlayer );
	void PX_API HumanizeAngles( Vector& vecAngles, PX::Tools::CBasePlayer* pLocalPlayer );
	bool PX_API WorldToScreen( const Vector& vecWorld, Vector &vecScreen );
	bool PX_API AngleToScreen( const Vector& vecAngle, const Vector& vecOrigin, Vector& vecScreen );
	void PX_API TransformVector( Vector vecInput, matrix3x4_t mtxInput, Vector &vecOutput );
	void PX_API TransformAngle( const QAngle &qAngles, Vector& vecForward );
	void PX_API TransformAngle( const Vector &vecAngles, Vector& vecForward );
	Vector2D PX_API CalcAngle( Vector vecPosOne, Vector vecPosTwo );
	float PX_API GetAngleDistance( Vector vecCurrentAngles, Vector vecPosOne, Vector vecPosTwo );
	RECT PX_API CalculateRenderBounds( Vector* vecScreenPoints );
	RECT PX_API CalculateRenderBounds( CBaseEntity* pEntity );
	float PX_API CalculateVectorDistance( const Vector& vecPositionOne, const Vector& vecPositionTwo );
	QAngle PX_API CalculateAngle( const Vector& vecFirst, const Vector& vecSecond );
	QAngle PX_API CalculateAngle( CBasePlayer* pLocalPlayer, CBasePlayer* pPlayer, int iHitbox, CUserCmd* pCmd, Vector* vecOverCompensation );
	float PX_API CalculateCrosshairDistance( CBasePlayer* pLocalPlayer, CBasePlayer* pPlayer, int iHitbox, CUserCmd* pCmd, bool bWorldlyDistance );

	std::vector< Vector > PX_API GetBezierPoints( Vector vecStart, Vector vecEnd, bezier_order_t* pOrders, std::size_t zOrders );
	Vector PX_API GetBezierPoint( std::vector< Vector > vecPoints, float flRatio );

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
		CUtlVector< IRefCounted* >* m_CustomMaterials()
		{
			return reinterpret_cast< CUtlVector<IRefCounted*>* >( ptr_t( this ) + 0x14 );
		}

		CUtlVector<IRefCounted*>* m_VisualsDataProcessors()
		{
			//static const auto ptrOffset = *reinterpret_cast< ptr_t* >( Information::Modules::mClient.FindPattern( Information::jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Signatures" ) ][ PX_XOR( "m_VisualsDataProcessors" ) ].get< str_t >( ) )
			//							 + Information::jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Offsets" ) ][ PX_XOR( "m_VisualsDataProcessors" ) ].get< int >( ) );
			//return reinterpret_cast< CUtlVector<IRefCounted*>* >( ptr_t( this ) + ptrOffset );
			return reinterpret_cast< CUtlVector< IRefCounted* >* >( ptr_t( this ) + 0x0220 );
		}
	};

	class CBaseEntity: public IClientEntity
	{
	public:
		PX_NETVAR_REFERENCE( int32_t, m_iTeamNum,PX_XOR( "DT_BaseEntity" ), PX_XOR( "m_iTeamNum" ) );
		PX_NETVAR_REFERENCE( Vector, m_vecOrigin,PX_XOR( "DT_BaseEntity" ), PX_XOR( "m_vecOrigin" ) );
		PX_NETVAR_REFERENCE( bool, m_bShouldGlow,PX_XOR( "DT_DynamicProp" ), PX_XOR( "m_bShouldGlow" ) );
		PX_NETVAR_REFERENCE( CBasePlayer*, m_hOwnerEntity,PX_XOR( "DT_BaseEntity" ), PX_XOR( "m_hOwnerEntity" ) );
		PX_NETVAR_REFERENCE( float, m_flSimulationTime,PX_XOR( "DT_BaseEntity" ), PX_XOR( "m_flSimulationTime" ) );
		PX_NETVAR_REFERENCE_OFFSET( matrix3x4_t, m_rgflCoordinateFrame, PX_XOR( "DT_BaseEntity" ), PX_XOR( "m_CollisionGroup" ),  -int( 0x30 ) );
		PX_NETVAR_REFERENCE_OFFSET( int32_t, GetIndex, PX_XOR( "CBaseEntity" ), PX_XOR( "m_bIsAutoaimTarget" ), 0x4 );
		PX_NETVAR_REFERENCE( int32_t, movetype, PX_XOR( "DT_BaseEntity" ), PX_XOR( "movetype" ) );

		bool IsPlayer( );
		bool IsWeapon( );
		bool IsPlantedC4( );
		bool IsDefuseKit( );
		bool IsGrenade( );
		float GetBombTimer( );
		float GetDefuseTimer( );
		Vector* BoundingBox( );
		void SetABSOrigin( Vector& vecOrigin );
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
		PX_NETVAR_REFERENCE( char*, m_szCustomName, PX_XOR( "DT_BaseAttributableItem" ), PX_XOR( "m_szCustomName" ) );

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
		CUtlVector< IRefCounted* >* m_CustomMaterials( )
		{
			static const auto ptrOffset = ptr_t( *reinterpret_cast< ptr_t* >( Information::Modules::mClient.FindPattern( Information::jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Signatures" ) ][ PX_XOR( "m_CustomMaterials" ) ].get< str_t >( ) )
																 + Information::jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Offsets" ) ][ PX_XOR( "m_CustomMaterials" ) ].get< int >( ) ) ) - 12;
			return reinterpret_cast< CUtlVector< IRefCounted* >* >( ptr_t( this ) + ptrOffset );
		}

		bool& m_bCustomMaterialInitialized( )
		{
			static const auto ptrOffset = *reinterpret_cast< ptr_t* >( Information::Modules::mClient.FindPattern( Information::jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Signatures" ) ][ PX_XOR( "m_bCustomMaterialInitialized" ) ].get< str_t >( ) )
																 + Information::jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Offsets" ) ][ PX_XOR( "m_bCustomMaterialInitialized" ) ].get< int >( ) );
			return *reinterpret_cast< bool* >( ptr_t( this ) + ptrOffset );
		}

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
		float GetNextShotTime( );
	};

	class CBaseViewModel: public CBaseEntity
	{
	public:
		PX_NETVAR_REFERENCE( int32_t, m_nModelIndex, PX_XOR( "DT_BaseViewModel" ), PX_XOR( "m_nModelIndex" ) );
		PX_NETVAR_REFERENCE( int32_t, m_nWorldModelIndex, PX_XOR( "DT_BaseViewModel" ), PX_XOR( "m_nWorldModelIndex" ) );
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
		PX_NETVAR_REFERENCE( CHandle< CBaseCombatWeapon >, m_hActiveWeapon,PX_XOR( "DT_BaseCombatCharacter" ), PX_XOR( "m_hActiveWeapon" ) );
		PX_NETVAR_POINTER( CHandle< CBaseCombatWeapon >, m_hMyWeapons,PX_XOR( "DT_BaseCombatCharacter" ), PX_XOR( "m_hMyWeapons" ) );
		PX_NETVAR_POINTER( CHandle<CBaseAttributableItem>, m_hMyWearables, PX_XOR( "DT_BaseCombatCharacter" ), PX_XOR( "m_hMyWearables" ) );
		PX_NETVAR_POINTER( bool, m_bSpotted, PX_XOR( "DT_CSPlayerResource" ), PX_XOR( "m_bSpotted" ) );
		PX_NETVAR_REFERENCE_OFFSET( CUserCmd*, m_pCurrentCommand, PX_XOR( "DT_BasePlayer" ), PX_XOR( "m_hConstraintEntity" ), -int( 0xC ) );

		bool IsAlive( );
		bool IsLocalPlayer( );
		Vector GetViewPosition( );
		player_info_t GetPlayerInformation( );
		bool CanSeePosition( Vector vecPosition, bool bMindSmoke, void* pEntity = nullptr );
		bool CanSeePlayer( CBasePlayer* pPlayer, bool bMindSmoke );
		CGameTrace& TraceRayFromAngle( const QAngle& qAngle );
		CGameTrace& TraceRayFromView( CUserCmd* pCmd = nullptr );
		Vector GetHitboxPosition( int hHitboxID );
		bool IsVulnerable( );
		float DistanceFromPlayer( CBasePlayer* pPlayer );
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
