/// Visuals.cpp

#include "PX Precompiled.hpp"
#include "../../PX CSGO.hpp"

using namespace PX;
using namespace Information;
using namespace Pointers;
using namespace Tools;

namespace PX::Features::Miscellaneous
{
	struct hitmarker_t
	{
		Vector vecPosition;
		float flStartTime;
		bool bEnemy;

		hitmarker_t( ) = default;
		hitmarker_t( const Vector& _vecPosition, bool _bEnemy ): vecPosition( _vecPosition ), flStartTime( pGlobalVariables->m_flCurrentTime ), bEnemy( _bEnemy ) { }
		~hitmarker_t( ) = default;

		byte_t GetAlpha( ) const
		{
			if ( pGlobalVariables->m_flCurrentTime < flStartTime + _Settings._Miscellaneous._Visuals.flHitmarkerFadeTime )
				return UCHAR_MAX;

			return UCHAR_MAX / ( _Settings._Miscellaneous._Visuals.flHitmarkerLifetime - _Settings._Miscellaneous._Visuals.flHitmarkerFadeTime )
				* ( flStartTime + _Settings._Miscellaneous._Visuals.flHitmarkerFadeTime - pGlobalVariables->m_flCurrentTime );
		}

		bool Over( ) const
		{
			return flStartTime + _Settings._Miscellaneous._Visuals.flHitmarkerLifetime < pGlobalVariables->m_flCurrentTime;
		}

		bool GetScreenPosition( Vector& vecScreen ) const
		{
			return WorldToScreen( vecPosition, vecScreen );
		}

		bool IsEnemy( ) const
		{
			return bEnemy;
		}
	};
	std::vector< hitmarker_t > vecHitmarkers { };

	void PX_API DarkenWorld( )
	{
		static auto bModifiedMaterials = false;
		char szOldSky[ MAX_PATH ];
		static auto pSkyModel = pConVar->FindVar( PX_XOR( "sv_skyname" ) );
		static auto pDrawSpecificStaticProp = pConVar->FindVar( PX_XOR( "r_DrawSpecificStaticProp" ) );
		if ( pSkyModel->m_nFlags & FCVAR_CHEAT )
			pSkyModel->m_nFlags &= ~FCVAR_CHEAT;
		pDrawSpecificStaticProp->SetValue( 1 );
		if ( bModifiedMaterials == _Settings._Miscellaneous._Visuals.bDarkenWorld.Get( ) )
			return;

		float flColorModifier;
		char szNewSky[ MAX_PATH ];

		if( bModifiedMaterials )
		{
			strcpy( szNewSky, const_cast< const char* >( szOldSky ) );
			flColorModifier = 1.f;
		}
		else
		{
			strcpy( szOldSky, pSkyModel->GetString( ) );
			strcpy( szNewSky, PX_XOR( "sky_csgo_night02" ) );
			flColorModifier = 0.15f;
		}

		bModifiedMaterials = !bModifiedMaterials;
		const static auto pInvalidMaterial = reinterpret_cast< MaterialHandle_t( __thiscall* )( IMaterialSystem* ) >( ( *reinterpret_cast< void*** >( pMaterialSystem ) )[ 88 ] )( pMaterialSystem );

		for ( auto m = reinterpret_cast< MaterialHandle_t( __thiscall* )( IMaterialSystem* ) >( ( *reinterpret_cast< void*** >( pMaterialSystem ) )[ 86 ] )( pMaterialSystem );
			  m != pInvalidMaterial; 
			  m = reinterpret_cast< MaterialHandle_t( __thiscall* )( IMaterialSystem*, MaterialHandle_t ) >( ( *reinterpret_cast< void*** >( pMaterialSystem ) )[ 87 ] )( pMaterialSystem, m ) )
		{
			const auto pMaterial = reinterpret_cast< IMaterial*( __thiscall* )( IMaterialSystem*, MaterialHandle_t ) >( ( *reinterpret_cast< void*** >( pMaterialSystem ) )[ 89 ] )( pMaterialSystem, m );
			if ( pMaterial == nullptr
				 || pMaterial->IsErrorMaterial( ) )
				continue;
			std::cout << pMaterial->GetTextureGroupName( ) << std::endl;
			if( strstr( pMaterial->GetTextureGroupName(  ), PX_XOR( "World" ) ) != nullptr
				|| strstr( pMaterial->GetTextureGroupName(  ), PX_XOR( "StaticProp" ) ) != nullptr )
			{
				pSkyModel->SetValue( szNewSky );
				pMaterial->ColorModulate( flColorModifier, flColorModifier, flColorModifier );
				if ( bModifiedMaterials )
					pMaterial->SetMaterialVarFlag( MATERIAL_VAR_TRANSLUCENT, false );
			}
		}
	}

	void PX_API DrawAimbotFOV( )
	{
		if ( !_Settings._Miscellaneous._Visuals.bDrawAimFOV )
			return;

		const auto pLocalPlayer = GetLocalPlayer( );
		if ( !pLocalPlayer
			 || !pLocalPlayer->IsAlive( ) )
			return;

		const auto hActiveWeapon = pLocalPlayer->m_hActiveWeapon( );
		if ( !hActiveWeapon )
			return;

		const auto def_index = hActiveWeapon->m_Item( )->m_iItemDefinitionIndex( ); 
		const auto wep_type = hActiveWeapon->GetCSWeaponData( )->WeaponType; 
		auto pConfig = _Settings._Combat._Aim._IndividualWeapons[ def_index ].bUseSeparate.Get( ) ? &_Settings._Combat._Aim._IndividualWeapons[ def_index ] : _Settings._Combat._Aim._WeaponTypes[ wep_type ].bUseSeparate.Get( ) ? &_Settings._Combat._Aim._WeaponTypes[ wep_type ] : &_Settings._Combat._Aim._All;;

		const auto vecViewPos = pLocalPlayer->GetViewPosition( );
		Vector vecMiddle { }, vecNew { }, vecScreenMiddle { }, vecScreenNew { };
		vecMiddle = pClientState->viewangles;
		vecNew = pClientState->viewangles;
		vecNew.y += pConfig->flMaxCrosshairDistance;

		AngleToScreen( vecMiddle, vecViewPos, vecScreenMiddle );
		AngleToScreen( vecNew, vecViewPos, vecScreenNew );
		auto radius = fabs( vecScreenNew.x - vecScreenMiddle.x );
		int iWidth, iHeight;
		pEngineClient->GetScreenSize( iWidth, iHeight );
		radius = std::clamp( radius, 0.f, sqrt( powf( iWidth / 2.f, 2.f ) + powf( iHeight / 2.f, 2.f ) ) );

		Drawing::Circle( D3DXVECTOR2( iWidth / 2.f, iHeight / 2.f ), radius, _Settings._Miscellaneous._Visuals.seqAimFOV[0].GetCurrentColor(  ).GetARGB(  ), _Settings._Miscellaneous._Visuals.seqAimFOV[ 1 ].GetCurrentColor( ).GetARGB( ), int( 2 * D3DX_PI * radius / 4.f ) );
	}

	void PX_API VisualizeSpread( )
	{
		if ( !_Settings._Miscellaneous._Visuals.bVisualizeSpread )
			return;

		const auto pLocalPlayer = GetLocalPlayer( );
		if ( !pLocalPlayer
			 || !pLocalPlayer->IsAlive( ) )
			return;

		const auto hActiveWeapon = pLocalPlayer->m_hActiveWeapon( );
		if ( !hActiveWeapon )
			return;

		const auto vecViewPos = pLocalPlayer->GetViewPosition( );
		const auto flRange = hActiveWeapon->GetCSWeaponData( )->flRange;
		const auto qRecoil = pLocalPlayer->m_aimPunchAngle( );
		Vector vecMiddle { }, vecRecoil { }, vecMiddleWorld { }, vecRecoilWorld { }, vecNewWorld { }, vecScreenMiddle { }, vecScreenRecoil { }, vecScreenNew { };
		vecMiddle = pClientState->viewangles;
		vecRecoil = vecMiddle + Vector( qRecoil.pitch, qRecoil.yaw, qRecoil.roll );
		TransformAngle( vecMiddle, vecMiddleWorld );
		TransformAngle( vecRecoil, vecRecoilWorld );

		vecNewWorld = vecMiddleWorld;
		vecNewWorld += hActiveWeapon->GetInaccuracy( ) + hActiveWeapon->GetSpread( );
		vecRecoilWorld *= flRange;
		vecMiddleWorld *= flRange;
		vecNewWorld *= flRange;
		vecNewWorld += vecViewPos;
		vecMiddleWorld += vecViewPos;
		vecRecoilWorld += vecViewPos;

		WorldToScreen( vecMiddleWorld, vecScreenMiddle );
		WorldToScreen( vecNewWorld, vecScreenNew );
		WorldToScreen( vecRecoilWorld, vecScreenRecoil );

		const auto vecRecoilDifference = vecScreenMiddle - vecScreenRecoil;
		auto radius = sqrt( powf( vecScreenNew.x - vecScreenMiddle.x, 2.f ) + powf( vecScreenNew.y - vecScreenMiddle.y, 2.f ) );
		int iWidth, iHeight;
		pEngineClient->GetScreenSize( iWidth, iHeight );
		radius = std::clamp( radius, 0.f, sqrt( powf( iWidth / 2.f, 2.f ) + powf( iHeight / 2.f, 2.f ) ) );

		Drawing::Circle( D3DXVECTOR2( iWidth / 2.f - vecRecoilDifference.x, iHeight / 2.f - vecRecoilDifference.y ), radius, _Settings._Miscellaneous._Visuals.seqSpread[ 0 ].GetCurrentColor( ).GetARGB( ), _Settings._Miscellaneous._Visuals.seqSpread[ 1 ].GetCurrentColor( ).GetARGB( ), int( 2 * D3DX_PI * radius / 4.f ) );
	}

	void PX_API ModifyRenderFOV( CViewSetup* pViewSetup )
	{
		if ( !_Settings._Miscellaneous._Visuals.bModifyFOV )
			return;

		const auto pLocalPlayer = GetLocalPlayer( );
		if ( pLocalPlayer == nullptr
			 || pLocalPlayer->m_bIsScoped( ) )
			return;

		pViewSetup->fov = _Settings._Miscellaneous._Visuals.flRenderFOV;
	}

	void PX_API ModifyViewmodelFOV( float* pFOV )
	{
		if ( !_Settings._Miscellaneous._Visuals.bModifyFOV )
			return;

		*pFOV = _Settings._Miscellaneous._Visuals.flViewmodelFOV;
	}

	void PX_API BulletBeam( IGameEvent* pEvent )
	{
		if ( !_Settings._Miscellaneous._Visuals.bBulletBeams )
			return;

		const auto pLocalPlayer = GetLocalPlayer( );
		if ( pLocalPlayer == nullptr
			 || pLocalPlayer->EntIndex( ) != pEngineClient->GetPlayerForUserID( pEvent->GetInt( PX_XOR( "userid" ) ) ) )
			return;

		auto& gtRay = pLocalPlayer->TraceRayFromView( &GetLastUserCmd( ) );
		const auto bHitPlayer = gtRay.hit_entity != nullptr
			&& entity_ptr_t( gtRay.hit_entity )->IsPlayer( );
		const auto clrBeam = _Settings._Miscellaneous._Visuals.seqBulletBeams[ bHitPlayer ].GetCurrentColor( );
		BeamInfo_t biBeam { };

		biBeam.m_nType = TE_BEAMPOINTS;
		biBeam.m_pszModelName = PX_XOR( "sprites/physbeam.vmt" );
		biBeam.m_nModelIndex = -1; // will be set by CreateBeamPoints if its -1
		biBeam.m_flHaloScale = 0.0f;
		biBeam.m_flLife = 10.f;
		biBeam.m_flWidth = 5.f;
		biBeam.m_flEndWidth = 2.0f;
		biBeam.m_flFadeLength = 5.f;
		biBeam.m_flAmplitude = 2.0f;
		biBeam.m_flBrightness = 255.f;
		biBeam.m_flSpeed = 0.2f;
		biBeam.m_nStartFrame = 0;
		biBeam.m_flFrameRate = 0.f;
		biBeam.m_flRed = clrBeam.rfl * 255.f;
		biBeam.m_flGreen = clrBeam.gfl * 255.f;
		biBeam.m_flBlue = clrBeam.bfl * 255.f;
		biBeam.m_nSegments = 2;
		biBeam.m_bRenderable = true;
		biBeam.m_nFlags = 0;
		biBeam.m_vecStart = gtRay.startpos;
		biBeam.m_vecEnd = gtRay.endpos;
		const auto pBeam = pRenderBeams->CreateBeamPoints( biBeam );
		if ( pBeam != nullptr )
			pRenderBeams->DrawBeam( pBeam );
	}

	void PX_API CreateHitmarker( IGameEvent* pEvent )
	{
		if ( !_Settings._Miscellaneous._Visuals.bHitmarkers )
			return;

		const auto pLocalPlayer = GetLocalPlayer( );
		if ( pLocalPlayer == nullptr
			 || pLocalPlayer->EntIndex( ) != pEngineClient->GetPlayerForUserID( pEvent->GetInt( PX_XOR( "userid" ) ) ) )
			return;

		const auto vecImpact = Vector( pEvent->GetFloat( PX_XOR( "x" ) ), pEvent->GetFloat( PX_XOR( "y" ) ), pEvent->GetFloat( PX_XOR( "z" ) ) );
		auto& gtRay = pLocalPlayer->TraceRayFromAngle( CalculateAngle( pLocalPlayer->GetViewPosition( ), vecImpact ) );
		if ( !gtRay.DidHit( )
			 || !gtRay.hit_entity
			 || !player_ptr_t( gtRay.hit_entity )->IsPlayer( ) )
			return;

		vecHitmarkers.emplace_back( gtRay.endpos, player_ptr_t( gtRay.hit_entity )->m_iTeamNum( ) != pLocalPlayer->m_iTeamNum( ) );
	}

	void PX_API DrawHitmarkers( )
	{
		for( auto z = 0u; z < vecHitmarkers.size( ); z++ )
		{
			const auto& hitmarker = vecHitmarkers[ z ];
			if( hitmarker.Over( ) )
			{
				vecHitmarkers.erase( vecHitmarkers.begin( ) + z );
				continue;
			}
			Vector vecScreen { };
			if ( !hitmarker.GetScreenPosition( vecScreen ) )
				continue;

			D3DXVECTOR2 vecPoints[ 2 ][ 2 ]
			{
				{
					D3DXVECTOR2( vecScreen.x - 5.f, vecScreen.y - 5.f ),
					D3DXVECTOR2( vecScreen.x + 5.f, vecScreen.y + 5.f )
				},
				{
					D3DXVECTOR2( vecScreen.x + 5.f, vecScreen.y - 5.f ),
					D3DXVECTOR2( vecScreen.x - 5.f, vecScreen.y + 5.f )
				}
			};

			const auto clrCurrent = _Settings._Miscellaneous._Visuals.seqHitmarkers[ hitmarker.IsEnemy( ) ].GetCurrentColor( );
			const auto flTemp = ( _Settings._Miscellaneous._Visuals.bHitmarkerFade.Get( ) ? hitmarker.GetAlpha( ) : clrCurrent.a ) / 255.f;
			const auto dwColor = D3DCOLOR_ARGB( byte_t( flTemp * 255.f ), byte_t( clrCurrent.r * flTemp ), byte_t( clrCurrent.g * flTemp ), byte_t( clrCurrent.b * flTemp ) );

			Drawing::Line( vecPoints[ 0 ], 2, 2.f,dwColor );
			Drawing::Line( vecPoints[ 1 ], 2, 2.f,dwColor );
		}
	}

	void PX_API MinimizeFlash( )
	{
		//switch
		// Clamp: if flash is greater than FLASH_CLAMP, set to FLASH_CLAMP (0.f -> 1.f or 0 -> 255 or 0% to 100%)
		// Scale: scale flash alpha by FLASH_MINIMIZE_FACTOR (0% -> 100%)
		// Clarity: if flash is less than 255, scale flash alpha by FLASH_MINIMIZE_FACTOR (0% -> 100%)
	}

	void PX_API SmokeWireframe( )
	{
		// https://www.unknowncheats.me/forum/2021077-post20.html
		// https://www.unknowncheats.me/forum/2022778-post23.html
	}

	void PX_API ScopeWireframe( )
	{
		// disable drawing scope
		// draw scope lines all the way across screen
		// draw two circles, one at the outer blur, where the black alpha just hits 255
		//					 one at the inner blur, where the black alpha just hits 0
		// https://i.imgur.com/XlQRTPU.jpg concept art
	}

	void PX_API MaximizeRadarVisibility( )
	{
		// just set all the players bSpotted
	}
}
