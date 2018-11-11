/// Visuals.cpp

#include "PX Precompiled.hpp"
#include "../../PX CSGO.hpp"

using namespace PX;
using namespace Information;
using namespace Pointers;
using namespace Tools;

namespace PX::Features::Miscellaneous
{
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
		Vector vecMiddle { }, vecMiddleWorld { }, vecNewWorld { }, vecScreenMiddle { }, vecScreenNew { };
		vecMiddle = pClientState->viewangles;
		TransformAngle( vecMiddle, vecMiddleWorld );
		vecNewWorld = vecMiddleWorld;
		vecNewWorld += powf( ( hActiveWeapon->GetInaccuracy( ) + hActiveWeapon->GetSpread( ) ) / 3.f, 2.f );
		vecMiddleWorld *= flRange;
		vecNewWorld *= flRange;
		vecNewWorld += vecViewPos;
		vecMiddle += vecViewPos;

		WorldToScreen( vecMiddleWorld, vecScreenMiddle );
		WorldToScreen( vecNewWorld, vecScreenNew );

		auto radius = sqrt( powf( vecScreenNew.x - vecScreenMiddle.x, 2.f ) + powf( vecScreenNew.y - vecScreenMiddle.y, 2.f ) );
		int iWidth, iHeight;
		pEngineClient->GetScreenSize( iWidth, iHeight );
		radius = std::clamp( radius, 0.f, sqrt( powf( iWidth / 2.f, 2.f ) + powf( iHeight / 2.f, 2.f ) ) );

		Drawing::Circle( D3DXVECTOR2( iWidth / 2.f, iHeight / 2.f ), radius, _Settings._Miscellaneous._Visuals.seqSpread[ 0 ].GetCurrentColor( ).GetARGB( ), _Settings._Miscellaneous._Visuals.seqSpread[ 1 ].GetCurrentColor( ).GetARGB( ), int( 2 * D3DX_PI * radius / 4.f ) );

	}
}
