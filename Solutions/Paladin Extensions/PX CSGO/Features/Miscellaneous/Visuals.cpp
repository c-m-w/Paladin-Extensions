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
		if ( pSkyModel->m_nFlags & FCVAR_CHEAT )
			pSkyModel->m_nFlags &= ~FCVAR_CHEAT;
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
		Vector vecMiddle { }, vecNew { }, vecWorldMiddle { }, vecWorldNew { }, vecScreenMiddle { }, vecScreenNew { };
		vecMiddle = pClientState->viewangles;
		vecNew = pClientState->viewangles;
		vecNew.y += pConfig->flMaxCrosshairDistance;

		TransformAngle( vecMiddle, vecWorldMiddle );
		TransformAngle( vecNew, vecWorldNew );

		vecWorldMiddle *= 8192.f;
		vecWorldNew *= 8192.f;
		vecWorldMiddle += vecViewPos;
		vecWorldNew += vecViewPos;
		WorldToScreen( vecWorldMiddle, vecScreenMiddle );
		WorldToScreen( vecWorldNew, vecScreenNew );
		const auto radius = fabs( vecScreenNew.x - vecScreenMiddle.x );
		int iWidth, iHeight;
		pEngineClient->GetScreenSize( iWidth, iHeight );

		Drawing::Circle( D3DXVECTOR2( iWidth / 2.f, iHeight / 2.f ), radius, 0x80000000, 0x80505050, 36 );
	}
}
