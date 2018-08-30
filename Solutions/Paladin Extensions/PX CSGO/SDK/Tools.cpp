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
	VMatrix vmMatrix;

	void PX_API OnPaintTraverse( )
	{
		memcpy( &vmMatrix, &pEngineClient->WorldToScreenMatrix( ), sizeof( VMatrix ) );
	}

	CBasePlayer* PX_API GetLocalPlayer( )
	{
		return reinterpret_cast< CBasePlayer* >( pEntityList->GetClientEntity( pEngineClient->GetLocalPlayer( ) ) );
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

	bool PX_API WorldToScreen( const Vector& vecWorld, Vector &vecScreen )
	{
		int iWidth, iHeight;
		pEngineClient->GetScreenSize( iWidth, iHeight );
	// OVERFLOW
		const auto dbTemp = double( vmMatrix[ 3 ][ 0 ] * vecWorld.x + vmMatrix[ 3 ][ 1 ] * vecWorld.y + vmMatrix[ 3 ][ 2 ] * vecWorld.z + vmMatrix[ 3 ][ 3 ] );
	
		if ( dbTemp <= 0.01 ) /// no .f cause we need double for DECIMAL PRECISION
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
		return m_flNextPrimaryAttack( ) <= pGlobalVariables->m_flCurrentTime;
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

	Vector CBasePlayer::GetViewPosition( )
	{
		return m_vecOrigin( ) + m_vecViewOffset( );
	}

	bool CBasePlayer::PositionInSight( Vector& vecPosition, bool bMindSmoke, void* pEntity /*= nullptr*/ )
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

		if ( gtRay.fraction == 1.f )
			return true;
		return gtRay.hit_entity == pEntity;
	}

	CGameTrace& CBasePlayer::TraceRayFromView( )
	{
		Vector vecEnd;
		CTraceFilter tfFilter;
		Ray_t rRay;
		static CGameTrace gtRay;

		TransformAngle( m_angEyeAngles( ), vecEnd );
		vecEnd *= 8192;
		vecEnd += GetViewPosition( );
		tfFilter.pSkip = this;
		rRay.Init( GetViewPosition( ), vecEnd );
		pEngineTrace->TraceRay( rRay, PX_MASK_VISIBLE, &tfFilter, &gtRay );
		return gtRay;
	}

	Vector CBasePlayer::GetHitboxPosition( EHitbox hHitboxID )
	{
		matrix3x4_t mtxBones[ MAXSTUDIOBONES ];

		if ( !SetupBones( mtxBones, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, 0.f ) )
			return Vector( );

		const auto pStudioModel = pModelInfo->GetStudiomodel( GetModel( ) );
		if ( !pStudioModel )
			return Vector( );

		const auto pHitbox = pStudioModel->GetHitboxSet( NULL )->GetHitbox( hHitboxID );
		if ( !pHitbox )
			return Vector( );

		Vector vecMin, vecMax;
		TransformVector( pHitbox->bbmin, mtxBones[ pHitbox->bone ], vecMin );
		TransformVector( pHitbox->bbmax, mtxBones[ pHitbox->bone ], vecMax );
		return ( vecMin + vecMax ) / 2.f;
	}
}
