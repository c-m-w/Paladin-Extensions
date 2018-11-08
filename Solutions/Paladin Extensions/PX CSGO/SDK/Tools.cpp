/// Tools.cpp

#include "PX Precompiled.hpp"
#include "../PX CSGO.hpp"

using namespace PX::Information;
using namespace PX::Types;
using namespace Memory;
using namespace VirtualTableIndicies;
using namespace Modules;
using namespace Pointers;

namespace PX::Tools
{
	VMatrix vmMatrix;

	void PX_API OnPaintTraverse( )
	{
		memcpy( &vmMatrix, &pEngineClient->WorldToScreenMatrix( ), sizeof( VMatrix ) );
	}

	CBasePlayer* PX_API GetLocalPlayer( )
	{
		return reinterpret_cast< CBasePlayer* >( pEntityList->GetClientEntity( pEngineClient->GetLocalPlayer( ) ) );
	}

	CUserCmd* PX_API GetUserCmd( int iSequenceNumber )
	{
		return &pInput->m_pCommands[ iSequenceNumber % MULTIPLAYER_BACKUP ];
	}

	CVerifiedUserCmd* PX_API GetVerifiedUserCmd( int iSequenceNumber )
	{
		return &pInput->m_pVerifiedCommands[ iSequenceNumber % MULTIPLAYER_BACKUP ];
	}

	CRC32_t GetCmdHash( CUserCmd* pCmd )
	{
		CRC32_t crcHash;

		CRC32_Init( &crcHash );
		CRC32_ProcessBuffer( &crcHash, &pCmd->command_number, sizeof( pCmd->command_number ) );
		CRC32_ProcessBuffer( &crcHash, &pCmd->tick_count, sizeof( pCmd->tick_count ) );
		CRC32_ProcessBuffer( &crcHash, &pCmd->viewangles, sizeof( pCmd->viewangles ) );
		CRC32_ProcessBuffer( &crcHash, &pCmd->aimdirection, sizeof( pCmd->aimdirection ) );
		CRC32_ProcessBuffer( &crcHash, &pCmd->forwardmove, sizeof( pCmd->forwardmove ) );
		CRC32_ProcessBuffer( &crcHash, &pCmd->sidemove, sizeof( pCmd->sidemove ) );
		CRC32_ProcessBuffer( &crcHash, &pCmd->upmove, sizeof( pCmd->upmove ) );
		CRC32_ProcessBuffer( &crcHash, &pCmd->buttons, sizeof( pCmd->buttons ) );
		CRC32_ProcessBuffer( &crcHash, &pCmd->impulse, sizeof( pCmd->impulse ) );
		CRC32_ProcessBuffer( &crcHash, &pCmd->weaponselect, sizeof( pCmd->weaponselect ) );
		CRC32_ProcessBuffer( &crcHash, &pCmd->weaponsubtype, sizeof( pCmd->weaponsubtype ) );
		CRC32_ProcessBuffer( &crcHash, &pCmd->random_seed, sizeof( pCmd->random_seed ) );
		CRC32_ProcessBuffer( &crcHash, &pCmd->mousedx, sizeof( pCmd->mousedx ) );
		CRC32_ProcessBuffer( &crcHash, &pCmd->mousedy, sizeof( pCmd->mousedy ) );
		CRC32_Final( &crcHash );

		return crcHash;
	}

	bool PX_API ValidPlayer( void* pEntity )
	{
		if ( !pEntity )
			return false;

		const auto pPlayer = reinterpret_cast< CBasePlayer* >( pEntity );
		return pPlayer->IsPlayer( ) && pPlayer->IsAlive( );
	}

	bool PX_API LineGoesThroughSmoke( Vector vecStartPos, Vector vecEndPos )
	{
		static auto ptrLineGoesThroughSmoke = mClient.FindPattern( jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Signatures" ) ][ PX_XOR( "Line Goes Through Smoke" ) ].get< str_t >( ) )
			+ jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Offsets" ) ][ PX_XOR( "Line Goes Through Smoke" ) ].get< int >( );
		return reinterpret_cast< bool( __cdecl* )( Vector, Vector ) >( ptrLineGoesThroughSmoke )( vecStartPos, vecEndPos );
	}

	void PX_API SetClantag( cstr_t szTag )
	{
		static auto ptrSetClantag = mEngine.FindPattern( jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Signatures" ) ][ PX_XOR( "Set Clantag" ) ].get< str_t >( ) )
			+ jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Offsets" ) ][ PX_XOR( "Set Clantag" ) ].get< int >( );
		reinterpret_cast< int( __fastcall* )( const char*, const char* ) >( ptrSetClantag )( szTag, szTag );
	}

	void PX_API RevealRanks( )
	{
		static auto ptrRevealRanks = mClient.FindPattern( jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Signatures" ) ][ PX_XOR( "Reveal Ranks" ) ].get< str_t >( ) )
			+ jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Offsets" ) ][ PX_XOR( "Reveal Ranks" ) ].get< int >( );
		static int iBuffer[ ] { 0, 0, 0 };
		reinterpret_cast< char( __cdecl* )( int* ) >( ptrRevealRanks )( iBuffer );
	}

	void PX_API ClampAngles( QAngle& qAngles )
	{
		//if ( isnan( qAngles.pitch ) || isnan( qAngles.yaw ) || isnan( qAngles.roll )
		//	 || isinf( qAngles.pitch ) || isinf( qAngles.yaw ) || isinf( qAngles.roll ) )
		//	return ( void )( qAngles.pitch = 0.f, qAngles.yaw = 0.f, qAngles.roll = 0.f );
		//
		//qAngles.pitch = std::clamp( qAngles.pitch, PX_MIN_PITCH, PX_MAX_PITCH );
		//
		//if ( qAngles.yaw < PX_MIN_YAW || qAngles.yaw > PX_MAX_YAW )
		//	qAngles.yaw += -qAngles.yaw / fabs( qAngles.yaw ) * floorf( qAngles.yaw / ( PX_REVOLUTION / 2.f ) ) * PX_REVOLUTION;
		//if ( qAngles.yaw < PX_MIN_YAW || qAngles.yaw > PX_MAX_YAW )
		//	qAngles.yaw = 0.f;
		//
		//qAngles.roll = std::clamp( qAngles.roll, PX_MIN_ROLL, PX_MAX_ROLL );
	}

	void PX_API ClampAngles( Vector& vecAngles )
	{
		//if ( isnan( vecAngles.x ) || isnan( vecAngles.y ) || isnan( vecAngles.z )
		//	 || isinf( vecAngles.x ) || isinf( vecAngles.y ) || isinf( vecAngles.z ) )
		//	return ( void )( vecAngles.x = 0.f, vecAngles.y = 0.f, vecAngles.z = 0.f );
		//
		//vecAngles.x = std::clamp( vecAngles.x, PX_MIN_PITCH, PX_MAX_PITCH );
		//
		//if ( vecAngles.y < PX_MIN_YAW || vecAngles.y > PX_MAX_YAW )
		//	vecAngles.y += -vecAngles.y / fabs( vecAngles.y ) * floorf( vecAngles.y / ( PX_REVOLUTION / 2.f ) ) * PX_REVOLUTION;
		//if ( vecAngles.y < PX_MIN_YAW || vecAngles.y > PX_MAX_YAW )
		//	vecAngles.y = 0.f;
		//
		//vecAngles.z = std::clamp( vecAngles.z, PX_MIN_ROLL, PX_MAX_ROLL );
	}

	bool PX_API WorldToScreen( const Vector& vecWorld, Vector &vecScreen )
	{
		int iWidth, iHeight;
		pEngineClient->GetScreenSize( iWidth, iHeight );
		// note OVERFLOW. cast first operand to 8byte var, then do operations on it.
		const auto dbTemp = double( vmMatrix[ 3 ][ 0 ] * vecWorld.x + vmMatrix[ 3 ][ 1 ] * vecWorld.y + vmMatrix[ 3 ][ 2 ] * vecWorld.z + vmMatrix[ 3 ][ 3 ] );

		if ( dbTemp <= 0.01 )
			return false;

		const auto flTemp = float( dbTemp );
		const auto flInverseTemp = 1.f / flTemp;
		vecScreen.x = vmMatrix[ 0 ][ 0 ] * vecWorld.x + vmMatrix[ 0 ][ 1 ] * vecWorld.y + vmMatrix[ 0 ][ 2 ] * vecWorld.z + vmMatrix[ 0 ][ 3 ];
		vecScreen.y = vmMatrix[ 1 ][ 0 ] * vecWorld.x + vmMatrix[ 1 ][ 1 ] * vecWorld.y + vmMatrix[ 1 ][ 2 ] * vecWorld.z + vmMatrix[ 1 ][ 3 ];
		vecScreen = { iWidth / 2.f + 0.5f * ( vecScreen.x * flInverseTemp ) * iWidth + 0.5f, iHeight / 2.f - 0.5f * ( vecScreen.y * flInverseTemp ) * iHeight + 0.5f, 0.f };
		return true;
	}

	void PX_API TransformVector( Vector vecInput, matrix3x4_t mtxInput, Vector& vecOutput )
	{
		vecOutput[ 0 ] = vecInput.Dot( mtxInput[ 0 ] ) + mtxInput[ 0 ][ 3 ];
		vecOutput[ 1 ] = vecInput.Dot( mtxInput[ 1 ] ) + mtxInput[ 1 ][ 3 ];
		vecOutput[ 2 ] = vecInput.Dot( mtxInput[ 2 ] ) + mtxInput[ 2 ][ 3 ];
	}

	void PX_API TransformAngle( const QAngle& qAngles, Vector& vecForward )
	{
		float flSin, flSin2, flCos, flCos2;

		DirectX::XMScalarSinCos( &flSin, &flCos, D3DXToRadian( qAngles[ 0 ] ) );
		DirectX::XMScalarSinCos( &flSin2, &flCos2, D3DXToRadian( qAngles[ 1 ] ) );

		vecForward.x = flCos * flCos2;
		vecForward.y = flCos * flSin2;
		vecForward.z = -flSin;
	}

	void PX_API TransformAngle( const Vector& vecAngles, Vector& vecForward )
	{
		QAngle qBuffer;
		qBuffer[ 0 ] = vecAngles.x;
		qBuffer[ 1 ] = vecAngles.y;
		return TransformAngle( qBuffer, vecForward );
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

	RECT CalculateRenderBounds( Vector* vecScreenPoints )
	{
		if ( !vecScreenPoints )
			return RECT( );

		auto flLeft = vecScreenPoints[ 0 ].x;
		auto flTop = vecScreenPoints[ 0 ].y;
		auto flRight = vecScreenPoints[ 0 ].x;
		auto flBottom = vecScreenPoints[ 0 ].y;

		for ( auto i = 1; i < 8; i++ )
		{
			if ( flLeft > vecScreenPoints[ i ].x )
				flLeft = vecScreenPoints[ i ].x;
			if ( flTop < vecScreenPoints[ i ].y )
				flTop = vecScreenPoints[ i ].y;
			if ( flRight < vecScreenPoints[ i ].x )
				flRight = vecScreenPoints[ i ].x;
			if ( flBottom > vecScreenPoints[ i ].y )
				flBottom = vecScreenPoints[ i ].y;
		}
		return RECT { int( flLeft ), int( flTop ), int( flRight ), int( flBottom ) };
	}

	RECT CalculateRenderBounds( CBaseEntity* pEntity )
	{
		const auto pPoints = pEntity->BoundingBox( );
		const auto recReturn = CalculateRenderBounds( pPoints );
		delete[ ] pPoints;
		return recReturn;
	}

	float PX_API CalculateVectorDistance( const Vector& vecPositionOne, const Vector& vecPositionTwo )
	{
		const auto vecNew = vecPositionOne - vecPositionTwo;
		return sqrt( pow( vecNew.z, 2.0 ) + pow( vecNew.x, 2.0 ) + pow( vecNew.y, 2.0 ) );
	}

	QAngle PX_API CalculateAngle( CBasePlayer* pLocalPlayer, CBasePlayer* pPlayer, int iHitbox, CUserCmd* pCmd, bool bAccountForRecoil, float flRecoilPrecision /*= 0.f*/ )
	{
		QAngle qReturn;
		const auto vecRelativePosition = pPlayer->GetHitboxPosition( iHitbox ) - pLocalPlayer->GetViewPosition( );
		const auto fl2DDistance = sqrt( pow( vecRelativePosition.x, 2.f ) + pow( vecRelativePosition.y, 2.f ) );

		qReturn.pitch = atan2( vecRelativePosition.z, fl2DDistance ) * -180.f / D3DX_PI;
		qReturn.yaw = atan2( vecRelativePosition.y, vecRelativePosition.x ) * 180.f / D3DX_PI;
		qReturn.roll = pCmd->viewangles.roll;
		if ( bAccountForRecoil )
			qReturn += pLocalPlayer->m_aimPunchAngle( ) * 2.f * ( flRecoilPrecision / 100.f );
		return qReturn;
	}

	float PX_API CalculateCrosshairDistance( CBasePlayer* pLocalPlayer, CBasePlayer* pPlayer, int iHitbox, CUserCmd* pCmd, bool bWorldlyDistance )
	{
		auto qNonGayAngles = pCmd->viewangles;
		if ( qNonGayAngles.yaw < 0.f )
			qNonGayAngles.yaw += 360.f;

		const auto qNewAngles = qNonGayAngles - CalculateAngle( pLocalPlayer, pPlayer, iHitbox, pCmd, false );
		if ( bWorldlyDistance )
			return sin( atan2( qNewAngles.yaw, qNewAngles.pitch ) ) * CalculateVectorDistance( pLocalPlayer->GetViewPosition( ), pPlayer->GetHitboxPosition( iHitbox ) );
		const auto flDistance = sqrt( pow( qNewAngles.yaw, 2.f ) + pow( qNewAngles.pitch, 2.f ) );
		return flDistance > 254.558441227f ? fabs( flDistance - 360.f ) : flDistance;
	}

	bool CBaseEntity::IsPlayer( )
	{
		return reinterpret_cast< bool( __thiscall* )( CBaseEntity* ) >( ( *reinterpret_cast< void*** >( this ) )[ uIsPlayer ] )( this );
	}

	bool CBaseEntity::IsWeapon( )
	{
		return reinterpret_cast< bool( __thiscall* )( CBaseEntity* ) >( ( *reinterpret_cast< void*** >( this ) )[ uIsWeapon ] )( this );
	}

	void CBaseEntity::SetABSOrigin( Vector& vecOrigin )
	{
		static auto ptrSetABSOrigin = mClient.FindPattern( jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Signatures" ) ][ PX_XOR( "Set ABS Origin" ) ].get< str_t >( ) )
			+ jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Offsets" ) ][ PX_XOR( "Set ABS Origin" ) ].get< int >( );
		return reinterpret_cast< void( __thiscall* )( CBaseEntity*, Vector& ) >( ptrSetABSOrigin )( this, vecOrigin );
	}

	bool CBaseEntity::IsPlantedC4( )
	{
		return GetClientClass( )->m_ClassID == ClassID_CPlantedC4;
	}

	bool CBaseEntity::IsDefuseKit( )
	{
		return GetClientClass( )->m_ClassID == ClassID_CBaseAnimating;
	}

	bool CBaseEntity::IsGrenade( )
	{
		const auto iClassID = GetClientClass( )->m_ClassID;
		return iClassID == ClassID_CMolotovGrenade
			|| iClassID == ClassID_CIncendiaryGrenade
			|| iClassID == ClassID_CDecoyGrenade
			|| iClassID == ClassID_CHEGrenade
			|| iClassID == ClassID_CFlashbang
			|| iClassID == ClassID_CSmokeGrenade;
	}

	float CBaseEntity::GetBombTimer( )
	{
		const auto flTimer = *reinterpret_cast< float* >( this + Offsets::ptrBombTimer ) - pGlobalVariables->m_flCurrentTime;
		return flTimer > 0.f ? flTimer : 0.f;
	}

	float CBaseEntity::GetDefuseTimer( )
	{
		const auto flTimer = *reinterpret_cast< float* >( this + Offsets::ptrDefuseTimer ) - pGlobalVariables->m_flCurrentTime;
		return flTimer > 0.f ? flTimer : 0.f;
	}

	Vector* CBaseEntity::BoundingBox( )
	{
		const auto pCollideable = GetCollideable( );
		if ( !pCollideable )
			return nullptr;

		const auto vecMin = pCollideable->OBBMins( );
		const auto vecMax = pCollideable->OBBMaxs( );
		const auto& mtxCoordinateFrame = m_rgflCoordinateFrame( );

		Vector points[ ] = {
			Vector( vecMin.x, vecMin.y, vecMin.z ),
			Vector( vecMin.x, vecMax.y, vecMin.z ),
			Vector( vecMax.x, vecMax.y, vecMin.z ),
			Vector( vecMax.x, vecMin.y, vecMin.z ),
			Vector( vecMax.x, vecMax.y, vecMax.z ),
			Vector( vecMin.x, vecMax.y, vecMax.z ),
			Vector( vecMin.x, vecMin.y, vecMax.z ),
			Vector( vecMax.x, vecMin.y, vecMax.z )
		};

		Vector vecTransformedPoints[ 8 ];
		for ( auto i = 0; i < 8; i++ )
			TransformVector( points[ i ], mtxCoordinateFrame, vecTransformedPoints[ i ] );

		const auto vecScreenPoints = new Vector[ 8 ];
		for ( auto i = 0; i < 8; i++ )
			if ( !WorldToScreen( vecTransformedPoints[ i ], vecScreenPoints[ i ] ) )
			{
				delete[ ] vecScreenPoints;
				return nullptr;
			}
		return vecScreenPoints;
	}

	CEconomyItemView* CBaseAttributableItem::m_Item( )
	{
		return reinterpret_cast< CEconomyItemView* >( this );
	}

	CCSWeaponInfo* CBaseCombatWeapon::GetCSWeaponData( )
	{
		static auto ptrGetCSWeaponData = mClient.FindPattern( jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Signatures" ) ][ PX_XOR( "Get CS Weapon Data" ) ].get< str_t >( ) )
			+ jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Offsets" ) ][ PX_XOR( "Get CS Weapon Data" ) ].get< int >( );
		return reinterpret_cast< CCSWeaponInfo*( __thiscall* )( CBaseCombatWeapon* ) >( ptrGetCSWeaponData )( this );
	}

	bool CBaseCombatWeapon::HasBullets( )
	{
		return !IsReloading( ) && m_iClip1( ) > 0;
	}

	bool CBaseCombatWeapon::CanFire( )
	{
		return HasBullets( ) && m_flNextPrimaryAttack( ) <= pGlobalVariables->m_flCurrentTime;
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
		static auto ptrIsReloading = *reinterpret_cast< ptr_t* >( mClient.FindPattern( jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Signatures" ) ][ PX_XOR( "Is Reloading" ) ].get< str_t >( ) )
			+ jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Offsets" ) ][ PX_XOR( "Is Reloading" ) ].get< int >( ) );
		return *reinterpret_cast< bool* >( ptr_t( this ) + ptrIsReloading );
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

	bool CBasePlayer::IsLocalPlayer( )
	{
		return EntIndex( ) == pEngineClient->GetLocalPlayer( );
	}

	Vector CBasePlayer::GetViewPosition( )
	{
		return m_vecOrigin( ) + m_vecViewOffset( );
	}

	player_info_t CBasePlayer::GetPlayerInformation( )
	{
		player_info_t piPlayer;
		pEngineClient->GetPlayerInfo( EntIndex( ), &piPlayer );
		return piPlayer;
	}

	bool CBasePlayer::CanSeePosition( Vector vecPosition, bool bMindSmoke, void* pEntity /*= nullptr*/ )
	{
		const auto vecStart = GetViewPosition( );
		if ( bMindSmoke && LineGoesThroughSmoke( vecStart, vecPosition ) )
			return false;

		CTraceFilter tfFilter;
		Ray_t rRay;
		CGameTrace gtRay;

		tfFilter.pSkip = this;
		rRay.Init( vecStart, vecPosition );
		pEngineTrace->TraceRay( rRay, PX_MASK_VISIBLE, &tfFilter, &gtRay );

		return gtRay.fraction == 1.f || gtRay.hit_entity == pEntity;
	}

	inline struct player_sight_t
	{
		int iTick = 0;
		bool bVisible = false;
		player_sight_t( bool _bVisible ): iTick( pGlobalVariables->m_iTickCount ), bVisible( _bVisible )
		{ }
		player_sight_t( ) = default;
	} _PlayerSight[ 64 ][ 64 ];

	bool CBasePlayer::CanSeePlayer( CBasePlayer* pPlayer, bool bMindSmoke )
	{
		const auto iPlayerIndex = EntIndex( ), iTargetIndex = pPlayer->EntIndex( );
		if ( _PlayerSight[ iPlayerIndex ][ iTargetIndex ].iTick == pGlobalVariables->m_iTickCount )
			return _PlayerSight[ iPlayerIndex ][ iTargetIndex ].bVisible;
		return ( _PlayerSight[ iPlayerIndex ][ iTargetIndex ] = player_sight_t( CanSeePosition( pPlayer->GetHitboxPosition( HITBOX_HEAD ), bMindSmoke, pPlayer )
																				|| CanSeePosition( pPlayer->GetHitboxPosition( HITBOX_LEFT_FOOT ), bMindSmoke, pPlayer )
																				|| CanSeePosition( pPlayer->GetHitboxPosition( HITBOX_RIGHT_FOOT ), bMindSmoke, pPlayer ) ) ).bVisible;
	}

	CGameTrace& CBasePlayer::TraceRayFromView( )
	{
		Vector vecEnd;
		CTraceFilter tfFilter;
		Ray_t rRay;
		static CGameTrace gtRay;

		TransformAngle( m_angEyeAngles( ), vecEnd );
		vecEnd *= 8192.f;
		vecEnd += GetViewPosition( );
		tfFilter.pSkip = this;
		rRay.Init( GetViewPosition( ), vecEnd );
		pEngineTrace->TraceRay( rRay, PX_MASK_VISIBLE, &tfFilter, &gtRay );
		return gtRay;
	}

	struct player_model_t
	{
		int iTickCount = -1;
		matrix3x4_t mtxBones[ MAXSTUDIOBONES ] { };
		studiohdr_t* pStudioModel = nullptr;
		mstudiohitboxset_t* pHitboxSet = nullptr;
	} _PlayerModels[ 64 ];

	Vector CBasePlayer::GetHitboxPosition( int hHitboxID )
	{
		auto& pmPlayer = _PlayerModels[ EntIndex( ) ];

		if ( pGlobalVariables->m_iTickCount != pmPlayer.iTickCount
			 || !pmPlayer.pStudioModel || !pmPlayer.pHitboxSet )
		{
			if ( !SetupBones( pmPlayer.mtxBones, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, 0.f )
				 || nullptr == ( pmPlayer.pStudioModel = pModelInfo->GetStudiomodel( GetModel( ) ) )
				 || nullptr == ( pmPlayer.pHitboxSet = pmPlayer.pStudioModel->GetHitboxSet( NULL ) ) )
				return Vector( );
			pmPlayer.iTickCount = pGlobalVariables->m_iTickCount;
		}

		const auto pHitbox = pmPlayer.pHitboxSet->GetHitbox( hHitboxID );
		if ( !pHitbox )
			return Vector( );

		Vector vecMin, vecMax;
		TransformVector( pHitbox->bbmin, pmPlayer.mtxBones[ pHitbox->bone ], vecMin );
		TransformVector( pHitbox->bbmax, pmPlayer.mtxBones[ pHitbox->bone ], vecMax );
		return ( vecMin + vecMax ) / 2.f;
	}

	bool CBasePlayer::IsVulnerable( )
	{
		const auto& hActiveWeapon = m_hActiveWeapon( );
		const auto iWeaponType = hActiveWeapon->GetCSWeaponData( )->WeaponType;
		return m_flFlashDuration( ) // cant see
			|| !hActiveWeapon
			&& ( !hActiveWeapon->HasBullets( ) // cant fire
				 || iWeaponType == ITEM_NONE // no weapon (tpose)
				 || iWeaponType > ITEM_WEAPON_SSG08 // useless weapon/nade
				 && iWeaponType < ITEM_WEAPON_M4A1S // useless weapon/nade
				 || iWeaponType > ITEM_WEAPON_TACTICALAWARENESSGRENADE ); // knife model/gloves/other
	}

	float CBasePlayer::DistanceFromPlayer( CBasePlayer* pPlayer )
	{
		return CalculateVectorDistance( m_vecOrigin( ), pPlayer->m_vecOrigin( ) );
	}
}
