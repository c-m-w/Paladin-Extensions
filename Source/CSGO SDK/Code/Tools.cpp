/// Tools.cpp

#include "../../Framework/Precompile.hpp"
#include "../../Framework/Code/Framework.hpp"
#include "CSGO SDK.hpp"

namespace Utilities
{
	VMatrix vmMatrix;
	CUserCmd cmdLast;

	void OnPaintTraverse( )
	{
		memcpy( &vmMatrix, &pEngineClient->WorldToScreenMatrix( ), sizeof( VMatrix ) );
	}

	CBasePlayer * GetLocalPlayer( )
	{
		return reinterpret_cast< CBasePlayer* >( pEntityList->GetClientEntity( pEngineClient->GetLocalPlayer( ) ) );
	}

	CUserCmd * GetUserCmd( int iSequenceNumber )
	{
		return &( cmdLast = pInput->m_pCommands[ iSequenceNumber % MULTIPLAYER_BACKUP ] );
	}

	CVerifiedUserCmd * GetVerifiedUserCmd( int iSequenceNumber )
	{
		return &pInput->m_pVerifiedCommands[ iSequenceNumber % MULTIPLAYER_BACKUP ];
	}

	CUserCmd & GetLastUserCmd( )
	{
		return cmdLast;
	}

	CRC32_t GetCmdHash( CUserCmd *pCmd )
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

	bool ValidPlayer( void *pEntity )
	{
		if ( !pEntity )
			return false;

		const auto pPlayer = reinterpret_cast< CBasePlayer* >( pEntity );
		return pPlayer->IsPlayer( ) && pPlayer->IsAlive( );
	}

	void RepairBoneRendering( )
	{
		const auto iLocalPlayerIndex = pEngineClient->GetLocalPlayer( );

		for ( auto i = 1; i < pGlobalVariables->m_iMaxClients; i++ )
		{
			if ( i == iLocalPlayerIndex )
				continue;

			const auto pEntity = pEntityList->GetClientEntity( i );
			if ( pEntity == nullptr )
				continue;

			*reinterpret_cast< int* >( uintptr_t( pEntity ) + 0xA30 ) = pGlobalVariables->m_iFrameCount;
			*reinterpret_cast< int* >( uintptr_t( pEntity ) + 0xA28 ) = 0;
		}
	}

	float GetRecoilScale( )
	{
		static auto pRecoilFactor = pConVar->FindVar( ENC( "weapon_recoil_scale" ) );
		return pRecoilFactor != nullptr ? pRecoilFactor->GetFloat( ) : 2.f;
	}

	bool LineGoesThroughSmoke( Vector vecStartPos, Vector vecEndPos )
	{
		return reinterpret_cast< bool( __cdecl*)( Vector, Vector ) >( pPointers[ SIGNATURE_LINE_GOES_THROUGH_SMOKE ] )( vecStartPos, vecEndPos );
		return false;
	}
	
	void SetClantag( const char *szTag )
	{
		reinterpret_cast< int( __fastcall*)( const char *, const char * ) >( pPointers[ SIGNATURE_SET_CLAN_TAG ] )( szTag, szTag );
	}
	
	void RevealRanks( )
	{
		static int iBuffer[ ] { 0, 0, 0 };
		reinterpret_cast< char( __cdecl*)( int * ) >( pPointers[ SIGNATURE_REVEAL_RANKS ] )( iBuffer );
	}

	void ClampAngles( QAngle &qAngles )
	{
		// test for input validity
		if ( isnan( qAngles.pitch ) || isnan( qAngles.yaw ) || isnan( qAngles.roll )
			|| isinf( qAngles.pitch ) || isinf( qAngles.yaw ) || isinf( qAngles.roll ) )
			return ( void )( qAngles.pitch = 0.f, qAngles.yaw = 0.f, qAngles.roll = 0.f );

		qAngles.pitch = std::clamp( qAngles.pitch, MIN_PITCH, MAX_PITCH );

		// orient horizontal axis into valid ranges
		qAngles.yaw -= copysign( floorf( ( fabsf( qAngles.yaw ) + REVOLUTION / 2.f ) / REVOLUTION ) * REVOLUTION, qAngles.yaw );

		qAngles.roll = std::clamp( qAngles.roll, MIN_ROLL, MAX_ROLL );
	}

	void ClampAngles( Vector &vecAngles )
	{
		// test for input validity
		if ( isnan( vecAngles.x ) || isnan( vecAngles.y ) || isnan( vecAngles.z )
			|| isinf( vecAngles.x ) || isinf( vecAngles.y ) || isinf( vecAngles.z ) )
			return ( void )( vecAngles.x = 0.f, vecAngles.y = 0.f, vecAngles.z = 0.f );

		vecAngles.x = std::clamp( vecAngles.x, MIN_PITCH, MAX_PITCH );

		// orient horizontal axis into valid ranges
		vecAngles.y -= copysign( floorf( ( fabsf( vecAngles.y ) + REVOLUTION / 2.f ) / REVOLUTION ) * REVOLUTION, vecAngles.y );

		vecAngles.z = std::clamp( vecAngles.z, MIN_ROLL, MAX_ROLL );
	}

	void HumanizeAngles( QAngle &qAngles, CBasePlayer* pLocalPlayer )
	{
		// test for input validity
		if ( isnan( qAngles.pitch ) || isnan( qAngles.yaw ) || isnan( qAngles.roll )
			|| isinf( qAngles.pitch ) || isinf( qAngles.yaw ) || isinf( qAngles.roll ) )
			return ( void )( qAngles.pitch = 0.f, qAngles.yaw = 0.f, qAngles.roll = 0.f );

		// assure delta is max sensitivity, 10000
		const auto angView = QAngle( pClientState->viewangles.x, pClientState->viewangles.y, 0.f );
		auto angDelta = qAngles - angView;
		ClampAngles( angDelta );
		angDelta.roll = 0.f;
		const auto flDelta = sqrtf( powf( angDelta.pitch, 2.f ) + powf( angDelta.yaw, 2.f ) );

		if ( flDelta > MAX_ANGLE_DELTA )
			angDelta *= MAX_ANGLE_DELTA / flDelta;

		// assure delta is divisible by current sensitivity
		static auto sensitivity = pConVar->FindVar( ENC( "sensitivity" ) );
		static auto m_pitch = pConVar->FindVar( ENC( "m_pitch" ) );
		static auto m_yaw = pConVar->FindVar( ENC( "m_yaw" ) );
		static auto zoom_sensitivity_ratio_mouse = pConVar->FindVar( ENC( "zoom_sensitivity_ratio_mouse" ) );
		int iWindowsSensitivity;
		const auto flWindowsSensitivity = SystemParametersInfo( SPI_GETMOUSESPEED, 0, &iWindowsSensitivity, false ) ? float( iWindowsSensitivity ) / 10.f : 1.f;
		const auto flStepUnscaled = sensitivity->GetFloat( ) * flWindowsSensitivity * ( pLocalPlayer->m_bIsScoped( ) ? zoom_sensitivity_ratio_mouse->GetFloat( ) : 1.f );
		const auto flStepPitch = m_pitch->GetFloat( ) * flStepUnscaled;
		const auto flStepYaw = m_yaw->GetFloat( ) * flStepUnscaled;

		angDelta.pitch = flStepPitch * roundf( angDelta.pitch / flStepPitch );
		angDelta.yaw = flStepYaw * roundf( angDelta.yaw / flStepYaw );

		// assign and exit
		return ( void )( qAngles = angView + angDelta, qAngles.roll = pClientState->viewangles.z );
	}

	void HumanizeAngles( Vector &vecAngles, CBasePlayer* pLocalPlayer )
	{
		if ( isnan( vecAngles.x ) || isnan( vecAngles.y ) || isnan( vecAngles.z )
			|| isinf( vecAngles.x ) || isinf( vecAngles.y ) || isinf( vecAngles.z ) )
			return ( void )( vecAngles.x = 0.f, vecAngles.y = 0.f, vecAngles.z = 0.f );

		// test for input validity
		if ( isnan( vecAngles.x ) || isnan( vecAngles.y ) || isnan( vecAngles.z )
			|| isinf( vecAngles.x ) || isinf( vecAngles.y ) || isinf( vecAngles.z ) )
			return ( void )( vecAngles.x = 0.f, vecAngles.y = 0.f, vecAngles.z = 0.f );

		// assure delta is max sensitivity, 10000
		auto vecView = pClientState->viewangles;
		auto vecDelta = vecAngles - vecView;
		vecDelta.z = 0.f;
		auto flDelta = sqrtf( powf( vecDelta.x, 2.f ) * powf( vecDelta.y, 2.f ) );

		if ( flDelta > MAX_ANGLE_DELTA )
			vecDelta *= MAX_ANGLE_DELTA / flDelta;

		// assure delta is divisible by current sensitivity
		static auto sensitivity = pConVar->FindVar( ENC( "sensitivity" ) );
		static auto m_pitch = pConVar->FindVar( ENC( "m_pitch" ) );
		static auto m_yaw = pConVar->FindVar( ENC( "m_yaw" ) );
		static auto zoom_sensitivity_ratio_mouse = pConVar->FindVar( ENC( "zoom_sensitivity_ratio_mouse" ) );
		int iWindowsSensitivity;
		const auto flWindowsSensitivity = SystemParametersInfo( SPI_GETMOUSESPEED, 0, &iWindowsSensitivity, false ) != 0 ? float( iWindowsSensitivity ) / 20.f : 1.f;
		const auto flStepUnscaled = sensitivity->GetFloat( ) * flWindowsSensitivity * pLocalPlayer->m_bIsScoped( ) ? zoom_sensitivity_ratio_mouse->GetFloat( ) : 1.f;
		const auto flStepPitch = m_pitch->GetFloat( ) * flStepUnscaled;
		const auto flStepYaw = m_yaw->GetFloat( ) * flStepUnscaled;

		vecDelta.x = flStepPitch * floorf( vecDelta.x / flStepPitch );
		vecDelta.y = flStepYaw * floorf( vecDelta.y / flStepYaw );

		// assign and exit
		return ( void )( vecAngles = vecView + vecDelta, vecAngles.z = pClientState->viewangles.z );
	}

	bool WorldToScreen( const Vector &vecWorld, Vector &vecScreen )
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

	bool AngleToScreen( const Vector &vecAngle, const Vector &vecOrigin, Vector &vecScreen )
	{
		Vector vecWorld;
		TransformAngle( vecAngle, vecWorld );
		vecWorld *= 8192.f;
		vecWorld += vecOrigin;
		return WorldToScreen( vecWorld, vecScreen );
	}

	void TransformVector( Vector vecInput, matrix3x4_t mtxInput, Vector &vecOutput )
	{
		vecOutput[ 0 ] = vecInput.Dot( mtxInput[ 0 ] ) + mtxInput[ 0 ][ 3 ];
		vecOutput[ 1 ] = vecInput.Dot( mtxInput[ 1 ] ) + mtxInput[ 1 ][ 3 ];
		vecOutput[ 2 ] = vecInput.Dot( mtxInput[ 2 ] ) + mtxInput[ 2 ][ 3 ];
	}

	void TransformAngle( const QAngle &qAngles, Vector &vecForward )
	{
		float flSin, flSin2, flCos, flCos2;

		DirectX::XMScalarSinCos( &flSin, &flCos, D3DXToRadian( qAngles[ 0 ] ) );
		DirectX::XMScalarSinCos( &flSin2, &flCos2, D3DXToRadian( qAngles[ 1 ] ) );

		vecForward.x = flCos * flCos2;
		vecForward.y = flCos * flSin2;
		vecForward.z = -flSin;
	}

	void TransformAngle( const Vector &vecAngles, Vector &vecForward )
	{
		QAngle qBuffer;
		qBuffer[ 0 ] = vecAngles.x;
		qBuffer[ 1 ] = vecAngles.y;
		return TransformAngle( qBuffer, vecForward );
	}

	Vector2D CalcAngle( Vector vecPosOne, Vector vecPosTwo )
	{
		vecPosTwo.x -= vecPosOne.x;
		vecPosTwo.y -= vecPosOne.y;
		const auto flZDifference = vecPosOne.z - vecPosTwo.z;
		const auto flDistance = sqrt( vecPosTwo.x * vecPosTwo.x + vecPosTwo.y * vecPosTwo.y );

		Vector2D vecAimAngles {
			D3DXToDegree( atan2( flZDifference, flDistance ) ),
			D3DXToDegree( atan2( vecPosTwo.y, vecPosTwo.x ) )
		};

		vecAimAngles.Normalize( );
		return vecAimAngles;
	}

	float GetAngleDistance( Vector vecCurrentAngles, Vector vecPosOne, Vector vecPosTwo )
	{
		const auto vecAngles = CalcAngle( vecPosOne, vecPosTwo );
		Vector2D vecRelativeAngles { vecCurrentAngles.x - vecAngles.x, vecCurrentAngles.y - vecAngles.y };
		vecRelativeAngles.Normalize( );
		return sqrt( ( vecRelativeAngles.x * vecRelativeAngles.x ) + ( vecRelativeAngles.y * vecRelativeAngles.y ) );
	}

	RECT CalculateRenderBounds( Vector *vecScreenPoints )
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

	RECT CalculateRenderBounds( CBaseEntity *pEntity )
	{
		const auto pPoints = pEntity->BoundingBox( );
		const auto recReturn = CalculateRenderBounds( pPoints );
		delete[ ] pPoints;
		return recReturn;
	}

	float CalculateVectorDistance( const Vector &vecPositionOne, const Vector &vecPositionTwo )
	{
		const auto vecNew = vecPositionOne - vecPositionTwo;
		return sqrt( pow( vecNew.z, 2.0 ) + pow( vecNew.x, 2.0 ) + pow( vecNew.y, 2.0 ) );
	}

	QAngle CalculateAngle( const Vector &vecFirst, const Vector &vecSecond )
	{
		const auto vecRelative = vecSecond - vecFirst;
		const auto fl2DDistance = sqrt( pow( vecRelative.x, 2.f ) + pow( vecRelative.y, 2.f ) );
		QAngle qReturn;

		qReturn.pitch = atan2( vecRelative.z, fl2DDistance ) * -180.f / D3DX_PI;
		qReturn.yaw = atan2( vecRelative.y, vecRelative.x ) * 180.f / D3DX_PI;
		qReturn.roll = 0.f;
		return qReturn;
	}

	QAngle CalculateAngle( CBasePlayer *pLocalPlayer, CBasePlayer *pPlayer, int iHitbox, CUserCmd *pCmd, Vector *vecOverCompensation )
	{
		QAngle qReturn;
		auto vecHitboxPosition = pPlayer->GetHitboxPosition( iHitbox );
		if ( vecOverCompensation != nullptr )
			vecHitboxPosition += *vecOverCompensation;
		return CalculateAngle( pLocalPlayer->GetViewPosition( ), vecHitboxPosition );
	}

	float CalculateCrosshairDistance( CBasePlayer *pLocalPlayer, CBasePlayer *pPlayer, int iHitbox, CUserCmd *pCmd, bool bWorldlyDistance )
	{
		const auto qNewAngles = pCmd->viewangles + pLocalPlayer->m_aimPunchAngle( ) * GetRecoilScale( ) - CalculateAngle( pLocalPlayer, pPlayer, iHitbox, pCmd, nullptr );
		if ( bWorldlyDistance )
			return sin( atan2( qNewAngles.yaw, qNewAngles.pitch ) ) * CalculateVectorDistance( pLocalPlayer->GetViewPosition( ), pPlayer->GetHitboxPosition( iHitbox ) );
		const auto flDistance = sqrt( pow( qNewAngles.yaw, 2.f ) + pow( qNewAngles.pitch, 2.f ) );
		return flDistance > 254.558441227f ? fabs( flDistance - 360.f ) : flDistance;
	}

	//std::vector< Vector > GetBezierPoints( Vector vecStart, Vector vecEnd, bezier_order_t *pOrders, std::size_t zOrders )
	//{
	//	const auto vecPoints = GetBezierPoints( D3DXVECTOR2( vecStart.x, vecStart.y ), D3DXVECTOR2( vecEnd.x, vecEnd.y ), pOrders, zOrders );
	//	std::vector< Vector > vecReturn;
	//	for ( const auto &point: vecPoints )
	//		vecReturn.emplace_back( Vector( point.x, point.y, 0.f ) );
	//	return vecReturn;
	//}
	//
	//Vector GetBezierPoint( std::vector< Vector > vecPoints, float flRatio )
	//{
	//	std::vector< D3DXVECTOR2 > vecNewPoints;
	//	for ( const auto &point: vecPoints )
	//		vecNewPoints.emplace_back( D3DXVECTOR2( point.x, point.y ) );
	//	const auto vecPoint = GetBezierPoint( vecNewPoints, flRatio );
	//	return Vector( vecPoint.x, vecPoint.y, 0.f );
	//}

	bool CBaseEntity::IsPlayer( )
	{
		return reinterpret_cast< bool( __thiscall*)( CBaseEntity * ) >( ( *reinterpret_cast< void*** >( this ) )[ GetFunctionIndex( FUNCTION_IS_PLAYER ) ] )( this );
	}

	bool CBaseEntity::IsWeapon( )
	{
		return reinterpret_cast< bool( __thiscall*)( CBaseEntity * ) >( ( *reinterpret_cast< void*** >( this ) )[ GetFunctionIndex( FUNCTION_IS_WEAPON ) ] )( this );
	}

	void CBaseEntity::SetABSOrigin( Vector &vecOrigin )
	{
		return reinterpret_cast< void( __thiscall*)( CBaseEntity *, Vector & ) >( pPointers[ SIGNATURE_SET_ABS_ORIGIN ] )( this, vecOrigin );
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

	//float CBaseEntity::GetBombTimer( )
	//{
	//	const auto flTimer = *reinterpret_cast< float* >( this + Offsets::ptrBombTimer ) - pGlobalVariables->m_flCurrentTime;
	//	return flTimer > 0.f ? flTimer : 0.f;
	//}
	//
	//float CBaseEntity::GetDefuseTimer( )
	//{
	//	const auto flTimer = *reinterpret_cast< float* >( this + Offsets::ptrDefuseTimer ) - pGlobalVariables->m_flCurrentTime;
	//	return flTimer > 0.f ? flTimer : 0.f;
	//}

	Vector *CBaseEntity::BoundingBox( )
	{
		const auto pCollideable = GetCollideable( );
		if ( !pCollideable )
			return nullptr;

		const auto vecMin = pCollideable->OBBMins( );
		const auto vecMax = pCollideable->OBBMaxs( );
		const auto &mtxCoordinateFrame = m_rgflCoordinateFrame( );

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

	CEconomyItemView *CBaseAttributableItem::m_Item( )
	{
		return reinterpret_cast< CEconomyItemView* >( this );
	}

	CCSWeaponInfo *CBaseCombatWeapon::GetCSWeaponData( )
	{
		return reinterpret_cast< CCSWeaponInfo*( __thiscall*)( CBaseCombatWeapon * ) >( pPointers[ SIGNATURE_GET_WEAPON_DATA ] )( this );
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
		return *reinterpret_cast< bool* >( std::uintptr_t( this ) + *reinterpret_cast< std::uintptr_t* >( pPointers[ SIGNATURE_IS_RELOADING ] ) );
	}

	float CBaseCombatWeapon::GetInaccuracy( )
	{
		return reinterpret_cast< float( __thiscall*)( CBaseCombatWeapon * ) >( ( *reinterpret_cast< void*** >( this ) )[ GetFunctionIndex( FUNCTION_GET_INACCURACY ) ] )( this );
	}

	float CBaseCombatWeapon::GetSpread( )
	{
		return reinterpret_cast< float( __thiscall*)( CBaseCombatWeapon * ) >( ( *reinterpret_cast< void*** >( this ) )[ GetFunctionIndex( FUNCTION_GET_SPREAD ) ] )( this );
	}

	void CBaseCombatWeapon::UpdateAccuracyPenalty( )
	{
		return reinterpret_cast< void( __thiscall*)( CBaseCombatWeapon * ) >( ( *reinterpret_cast< void*** >( this ) )[ GetFunctionIndex( FUNCTION_UPDATE_ACCURACY_PENALTY ) ] )( this );
	}

	float CBaseCombatWeapon::GetNextShotTime( )
	{
		return m_flNextPrimaryAttack( ) - pGlobalVariables->m_flCurrentTime;
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
		Vector vecReturn { };
		return *( *reinterpret_cast< Vector*( __thiscall*** )( void*, Vector* ) >( this ) )[ GetFunctionIndex( FUNCTION_GET_VIEW_POSITION ) ]( this, &vecReturn );
	}

	player_info_t CBasePlayer::GetPlayerInformation( )
	{
		player_info_t piPlayer;
		pEngineClient->GetPlayerInfo( EntIndex( ), &piPlayer );
		return piPlayer;
	}

	bool CBasePlayer::CanSeePosition( Vector vecPosition, bool bMindSmoke, void *pEntity /*= nullptr*/ )
	{
		const auto vecStart = GetViewPosition( );
		if ( bMindSmoke && LineGoesThroughSmoke( vecStart, vecPosition ) )
			return false;

		CTraceFilter tfFilter;
		Ray_t rRay;
		CGameTrace gtRay;

		tfFilter.pSkip = this;
		rRay.Init( vecStart, vecPosition );
		pEngineTrace->TraceRay( rRay, MASK_VISIBLE, &tfFilter, &gtRay );

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

	bool CBasePlayer::CanSeePlayer( CBasePlayer *pPlayer, bool bMindSmoke )
	{
		const auto iPlayerIndex = EntIndex( ), iTargetIndex = pPlayer->EntIndex( );
		if ( _PlayerSight[ iPlayerIndex ][ iTargetIndex ].iTick == pGlobalVariables->m_iTickCount )
			return _PlayerSight[ iPlayerIndex ][ iTargetIndex ].bVisible;
		return ( _PlayerSight[ iPlayerIndex ][ iTargetIndex ] = player_sight_t( CanSeePosition( pPlayer->GetHitboxPosition( HITBOX_HEAD ), bMindSmoke, pPlayer )
																			   || CanSeePosition( pPlayer->GetHitboxPosition( HITBOX_LEFT_FOOT ), bMindSmoke, pPlayer )
																			   || CanSeePosition( pPlayer->GetHitboxPosition( HITBOX_RIGHT_FOOT ), bMindSmoke, pPlayer ) ) ).bVisible;
	}

	CGameTrace &CBasePlayer::TraceRayFromAngle( const QAngle &qAngle )
	{
		Vector vecEnd;
		CTraceFilter tfFilter;
		Ray_t rRay;
		static CGameTrace gtRay;

		TransformAngle( qAngle, vecEnd );
		vecEnd *= 8192.f;
		vecEnd += GetViewPosition( );
		tfFilter.pSkip = this;
		rRay.Init( GetViewPosition( ), vecEnd );
		pEngineTrace->TraceRay( rRay, MASK_SHOT | CONTENTS_GRATE, &tfFilter, &gtRay );
		return gtRay;
	}

	CGameTrace &CBasePlayer::TraceRayFromView( CUserCmd *pCmd /*= nullptr*/ )
	{
		return TraceRayFromAngle( pCmd == nullptr ? m_angEyeAngles( ) : pCmd->viewangles );
	}

	struct player_model_t
	{
		int iTickCount = -1;
		matrix3x4_t mtxBones[ MAXSTUDIOBONES ] { };
		studiohdr_t *pStudioModel = nullptr;
		mstudiohitboxset_t *pHitboxSet = nullptr;
	} _PlayerModels[ 64 ];

	Vector CBasePlayer::GetHitboxPosition( int hHitboxID )
	{
		auto &pmPlayer = _PlayerModels[ EntIndex( ) ];

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
		const auto &hActiveWeapon = m_hActiveWeapon( );
		const auto iWeaponType = hActiveWeapon->GetCSWeaponData( )->WeaponType;
		return m_flFlashDuration( ) // cant see
				|| !hActiveWeapon
				&& ( !hActiveWeapon->HasBullets( ) // cant fire
					|| iWeaponType == ITEM_NONE // no weapon (tpose)
					|| iWeaponType > ITEM_WEAPON_SSG08 // useless weapon/nade
					&& iWeaponType < ITEM_WEAPON_M4A1S // useless weapon/nade
					|| iWeaponType > ITEM_WEAPON_TACTICALAWARENESSGRENADE ); // knife model/gloves/other
	}

	float CBasePlayer::DistanceFromPlayer( CBasePlayer *pPlayer )
	{
		return CalculateVectorDistance( m_vecOrigin( ), pPlayer->m_vecOrigin( ) );
	}
}
