/// Materials.cpp

#include "PX Precompiled.hpp"
#include "../../PX CSGO.hpp"
#include <cstdio>

using namespace PX;
using namespace Information;
using namespace Pointers;
using namespace Tools;

namespace PX::Features::Awareness
{
	enum
	{
		MATERIAL_DEFAULT,
		MATERIAL_IGNOREZ,
		MATERIAL_FLAT,
		MATERIAL_FLAT_IGNOREZ,
		MATERIAL_MAX
	};

	struct material_t
	{
		std::string wstrData, wstrFileName;
		IMaterial* pMaterial;
		material_t( std::string w, std::string f ): wstrData( w ), wstrFileName( f ), pMaterial( nullptr ) { }
	};

	material_t matMaterials[ MATERIAL_MAX ]
	{
		material_t( PX_XOR( 
R"#("VertexLitGeneric"
{
  "$basetexture" "vgui/white_additive"
  "$ignorez"      "0"
  "$envmap"       ""
  "$nofog"        "1"
  "$model"        "1"
  "$nocull"       "0"
  "$selfillum"    "1"
  "$halflambert"  "1"
  "$znearer"      "0"
  "$flat"         "1"
}
)#" ), PX_XOR( "default" ) ),

		material_t( PX_XOR(
R"#("VertexLitGeneric"
{
  "$basetexture" "vgui/white_additive"
  "$ignorez"      "1"
  "$envmap"       ""
  "$nofog"        "1"
  "$model"        "1"
  "$nocull"       "0"
  "$selfillum"    "1"
  "$halflambert"  "1"
  "$znearer"      "0"
  "$flat"         "1"
}
)#" ), PX_XOR( "ignorez" ) ),

		material_t( PX_XOR(
R"#("UnlitGeneric"
{
  "$basetexture" "vgui/white_additive"
  "$ignorez"      "0"
  "$envmap"       ""
  "$nofog"        "1"
  "$model"        "1"
  "$nocull"       "0"
  "$selfillum"    "1"
  "$halflambert"  "1"
  "$znearer"      "0"
  "$flat"         "1"
}
)#" ), PX_XOR( "flat" ) ),

		material_t( PX_XOR(
R"#("UnlitGeneric"
{
  "$basetexture" "vgui/white_additive"
  "$ignorez"      "1"
  "$envmap"       ""
  "$nofog"        "1"
  "$model"        "1"
  "$nocull"       "0"
  "$selfillum"    "1"
  "$halflambert"  "1"
  "$znearer"      "0"
  "$flat"         "1"
}
)#" ), PX_XOR( "flat_ignorez" ) )
	};

	bool PX_API CreateMaterials( )
	{
		for ( auto& material : matMaterials )
		{
			std::ofstream( PX_XOR( "csgo\\materials\\" ) + material.wstrFileName + PX_XOR( ".vmt" ) ) << material.wstrData;
			if ( ( material.pMaterial = pMaterialSystem->FindMaterial( string_cast< str_t >( material.wstrFileName ).c_str( ), TEXTURE_GROUP_MODEL ) ) == nullptr )
				return false;
		}
		return true;
	}

	void PX_API RemoveMaterials( )
	{
		for ( auto& material : matMaterials )
			std::remove( ( PX_XOR( "csgo\\materials\\" ) + material.wstrFileName + PX_XOR( ".vmt" ) ).c_str( ) );
	}

	bool PX_API SetMaterial( player_ptr_t pLocalPlayer, IMatRenderContext* pContext, const DrawModelState_t& _State, const ModelRenderInfo_t& _Info, matrix3x4_t* pMatrix, draw_model_execute_t fnDrawModelExecute, entity_ptr_t pEntity, int iSettingIndex );

	bool PX_API OverrideMaterial( player_ptr_t pLocalPlayer, IMatRenderContext* pContext, const DrawModelState_t& _State, const ModelRenderInfo_t& _Info, matrix3x4_t* pMatrix, void* fnDrawModelExecute )
	{
		return false;
		if ( strstr( _Info.pModel->szName, PX_XOR( "arms" ) ) != nullptr
			 || strstr( _Info.pModel->szName, PX_XOR( "sleeve" ) ) != nullptr )
			return SetMaterial( pLocalPlayer, pContext, _State, _Info, pMatrix, draw_model_execute_t( fnDrawModelExecute ), nullptr, SETTING_MATERIALS_SELF );
		return false;

		//const auto pEntity = _Info.pRenderable->GetIClientUnknown( )->GetBaseEntity( );
		//if ( pEntity == nullptr )
		//	return false;
		//auto iSettingIndex = 0;
		//
		//switch ( pEntity->GetClientClass( )->m_ClassID )
		//{
		//	case ClassID_CCSPlayer:
		//	{
		//		if ( !player_ptr_t( pEntity )->IsAlive( ) )
		//			return false;
		//		if ( player_ptr_t( pEntity )->m_iTeamNum( ) != pLocalPlayer->m_iTeamNum( ) )
		//			iSettingIndex = SETTING_MATERIALS_ENEMY;
		//		else
		//			iSettingIndex = SETTING_MATERIALS_TEAM;
		//	}
		//	break;
		//
		//	case ClassID_CC4:
		//	{
		//		iSettingIndex = SETTING_MATERIALS_C4;
		//	}
		//	break;
		//
		//	case ClassID_CPlantedC4:
		//	{
		//		iSettingIndex = SETTING_MATERIALS_PLANTED_C4;
		//	}
		//	break;
		//
		//	case ClassID_CBaseAnimating:
		//	{
		//		iSettingIndex = SETTING_MATERIALS_DEFUSER;
		//	}
		//	break;
		//
		//	case ClassID_CHEGrenade:
		//	{
		//		iSettingIndex = SETTING_MATERIALS_HE;
		//	}
		//	break;
		//
		//	case ClassID_CFlashbang:
		//	{
		//		iSettingIndex = SETTING_MATERIALS_FLASH;
		//	}
		//	break;
		//
		//	case ClassID_CSmokeGrenade:
		//	{
		//		iSettingIndex = SETTING_MATERIALS_SMOKE;
		//	}
		//	break;
		//
		//	case ClassID_CDecoyGrenade:
		//	{
		//		iSettingIndex = SETTING_MATERIALS_DECOY;
		//	}
		//	break;
		//
		//	case ClassID_CIncendiaryGrenade:
		//	{
		//		iSettingIndex = SETTING_MATERIALS_INCENDIARY;
		//	}
		//	break;
		//
		//	case ClassID_CBaseCSGrenadeProjectile: // hegrenade & flashbang
		//	{
		//		if ( strstr( _Info.pModel->szName, PX_XOR( "flashbang" ) ) != nullptr )
		//			iSettingIndex = SETTING_MATERIALS_PROJECTILE_FLASH;
		//		else if ( strstr( _Info.pModel->szName, PX_XOR( "fraggrenade" ) ) != nullptr )
		//			iSettingIndex = SETTING_MATERIALS_PROJECTILE_HE;
		//		else
		//			return false;
		//	}
		//	break;
		//
		//	case ClassID_CSmokeGrenadeProjectile:
		//	{
		//		iSettingIndex = SETTING_MATERIALS_PROJECTILE_SMOKE;
		//	}
		//	break;
		//
		//	case ClassID_CDecoyProjectile:
		//	{
		//		iSettingIndex = SETTING_MATERIALS_PROJECTILE_DECOY;
		//	}
		//	break;
		//
		//	case ClassID_CMolotovProjectile:
		//	{
		//		iSettingIndex = SETTING_MATERIALS_PROJECTILE_INCENDIARY;
		//	}
		//	break;
		//
		//	default:
		//	{
		//		if ( pEntity->IsWeapon( ) )
		//			iSettingIndex = SETTING_MATERIALS_WEAPONS;
		//		if ( strstr( _Info.pModel->szName, PX_XOR( "arms" ) ) != nullptr 
		//				  || strstr( _Info.pModel->szName, PX_XOR( "sleeve" ) ) != nullptr )
		//			iSettingIndex = SETTING_MATERIALS_SELF;
		//		else
		//			return false;
		//	}
		//	break;
		//}
		//
		//return SetMaterial( pLocalPlayer, pContext, _State, _Info, pMatrix, draw_model_execute_t( fnDrawModelExecute ), pEntity, iSettingIndex );
	}

	void PX_API RenderEntities( player_ptr_t pLocalPlayer )
	{
		for ( auto i = 0; i < pEntityList->GetMaxEntities( ); i++ )
		{
			const auto pEntity = entity_ptr_t( pEntityList->GetClientEntity( i ) );
			if ( pEntity == nullptr )
				continue;
			auto iSettingIndex = 0;

			switch ( pEntity->GetClientClass( )->m_ClassID )
			{
				case ClassID_CCSPlayer:
				{
					if ( !player_ptr_t( pEntity )->IsAlive( ) )
						return;
					if ( player_ptr_t( pEntity )->m_iTeamNum( ) != pLocalPlayer->m_iTeamNum( ) )
						iSettingIndex = SETTING_MATERIALS_ENEMY;
					else
						iSettingIndex = SETTING_MATERIALS_TEAM;
				}
				break;

				case ClassID_CC4:
				{
					iSettingIndex = SETTING_MATERIALS_C4;
				}
				break;

				case ClassID_CPlantedC4:
				{
					iSettingIndex = SETTING_MATERIALS_PLANTED_C4;
				}
				break;

				case ClassID_CBaseAnimating:
				{
					iSettingIndex = SETTING_MATERIALS_DEFUSER;
				}
				break;

				case ClassID_CHEGrenade:
				{
					iSettingIndex = SETTING_MATERIALS_HE;
				}
				break;

				case ClassID_CFlashbang:
				{
					iSettingIndex = SETTING_MATERIALS_FLASH;
				}
				break;

				case ClassID_CSmokeGrenade:
				{
					iSettingIndex = SETTING_MATERIALS_SMOKE;
				}
				break;

				case ClassID_CDecoyGrenade:
				{
					iSettingIndex = SETTING_MATERIALS_DECOY;
				}
				break;

				case ClassID_CIncendiaryGrenade:
				{
					iSettingIndex = SETTING_MATERIALS_INCENDIARY;
				}
				break;

				case ClassID_CBaseCSGrenadeProjectile: // hegrenade & flashbang
				{
					//continue;
					const auto iModelIndex = reinterpret_cast< CBaseViewModel* >( pEntity )->m_nModelIndex( );
					if ( iModelIndex == pModelInfo->GetModelIndex( PX_XOR( "models/Weapons/w_eq_flashbang_dropped.mdl" ) ) )
						iSettingIndex = SETTING_MATERIALS_PROJECTILE_FLASH;
					else if ( iModelIndex == pModelInfo->GetModelIndex( PX_XOR( "models/Weapons/w_eq_fraggrenade_dropped.mdl" ) ) )
						iSettingIndex = SETTING_MATERIALS_PROJECTILE_HE;
				}
				break;

				case ClassID_CSmokeGrenadeProjectile:
				{
					iSettingIndex = SETTING_MATERIALS_PROJECTILE_SMOKE;
				}
				break;

				case ClassID_CDecoyProjectile:
				{
					iSettingIndex = SETTING_MATERIALS_PROJECTILE_DECOY;
				}
				break;

				case ClassID_CMolotovProjectile:
				{
					iSettingIndex = SETTING_MATERIALS_PROJECTILE_INCENDIARY;
				}
				break;

				default:
				{
					//continue;
					if ( pEntity->IsWeapon( ) )
						iSettingIndex = SETTING_MATERIALS_WEAPONS;
					else
						continue;
				}
				break;
			}

			if ( !pEntity->GetClientRenderable( ) || !pEntity->GetClientRenderable( )->GetModel( ) )
				continue;

			auto& _Config = _Settings._Awareness._Materials._Entities[ iSettingIndex ];
			if ( !_Config.bEnabled.Get( ) )
				continue;

			const auto clrVisible = _Config.seqColor[ STATE_VISIBLE ].GetCurrentColor( );
			
			if ( _Config.bDrawAboveAll.Get( ) )
			{
				const auto clrInvisible = _Config.seqColor[ STATE_INVISIBLE ].GetCurrentColor( );
				const auto pCurrent = _Config.bFlat.Get( ) ? matMaterials[ MATERIAL_FLAT_IGNOREZ ].pMaterial : matMaterials[ MATERIAL_IGNOREZ ].pMaterial;

				pCurrent->SetMaterialVarFlag( MATERIAL_VAR_WIREFRAME, _Config.bWireFrame.Get( ) );
				pCurrent->AlphaModulate( clrInvisible.afl );
				pCurrent->ColorModulate( clrInvisible.rfl, clrInvisible.gfl, clrInvisible.bfl );
				pModelRender->ForcedMaterialOverride( pCurrent );
				pEntity->DrawModel( 1, 255 );
			}

			const auto pCurrent = _Config.bFlat.Get( ) ? matMaterials[ MATERIAL_FLAT ].pMaterial : matMaterials[ MATERIAL_DEFAULT ].pMaterial;

			pCurrent->SetMaterialVarFlag( MATERIAL_VAR_WIREFRAME, _Config.bWireFrame.Get( ) );
			pCurrent->AlphaModulate( clrVisible.afl );
			pCurrent->ColorModulate( clrVisible.rfl, clrVisible.gfl, clrVisible.bfl );
			pModelRender->ForcedMaterialOverride( pCurrent );
			pEntity->DrawModel( 1, 255 );

			pModelRender->ForcedMaterialOverride( nullptr );
		}
	}

	bool PX_API SetMaterial( player_ptr_t pLocalPlayer, IMatRenderContext* pContext, const DrawModelState_t& _State, const ModelRenderInfo_t& _Info, matrix3x4_t* pMatrix, draw_model_execute_t fnDrawModelExecute, entity_ptr_t pEntity, int iSettingIndex )
	{
		auto& _Config = _Settings._Awareness._Materials._Entities[ iSettingIndex ];
		if ( !_Config.bEnabled.Get( ) )
			return false;

		const auto clrVisible = _Config.seqColor[ STATE_VISIBLE ].GetCurrentColor( );

		if( _Config.bDrawAboveAll.Get( ) )
		{
			const auto clrInvisible = _Config.seqColor[ STATE_INVISIBLE ].GetCurrentColor( );
			const auto pCurrent = _Config.bFlat.Get( ) ? matMaterials[ MATERIAL_FLAT_IGNOREZ ].pMaterial : matMaterials[ MATERIAL_IGNOREZ ].pMaterial;

			pCurrent->SetMaterialVarFlag( MATERIAL_VAR_WIREFRAME, _Config.bWireFrame.Get( ) );
			pCurrent->AlphaModulate( clrInvisible.afl );
			pCurrent->ColorModulate( clrInvisible.rfl, clrInvisible.gfl, clrInvisible.bfl );
			pModelRender->ForcedMaterialOverride( pCurrent );
			fnDrawModelExecute( pModelRender, pContext, _State, _Info, pMatrix );			
		}

		const auto pCurrent = _Config.bFlat.Get( ) ? matMaterials[ MATERIAL_FLAT ].pMaterial : matMaterials[ MATERIAL_DEFAULT ].pMaterial;

		pCurrent->SetMaterialVarFlag( MATERIAL_VAR_WIREFRAME, _Config.bWireFrame.Get( ) );
		pCurrent->AlphaModulate( clrVisible.afl );
		pCurrent->ColorModulate( clrVisible.rfl , clrVisible.gfl, clrVisible.bfl );
		pModelRender->ForcedMaterialOverride( pCurrent );
		fnDrawModelExecute( pModelRender, pContext, _State, _Info, pMatrix );
		return true;
	}
}
