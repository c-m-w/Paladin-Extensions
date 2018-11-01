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

		for ( auto m = pMaterialSystem->FirstMaterial(  ); m != pMaterialSystem->InvalidMaterial(  ); m = pMaterialSystem->NextMaterial( m ) )
		{
			const auto pMaterial = pMaterialSystem->GetMaterial( m );
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
}
