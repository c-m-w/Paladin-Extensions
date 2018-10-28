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

	std::vector< IClientRenderable* > vecRenderables { };

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
		if ( !pModelRender->IsForcedMaterialOverride( ) )
		{
			for ( const auto& pRenderable : vecRenderables )
				if ( _State.m_pRenderable == pRenderable )
					return true;
		}
		else
			return false;

		if ( strstr( _Info.pModel->szName, PX_XOR( "arms" ) ) != nullptr
			 || strstr( _Info.pModel->szName, PX_XOR( "sleeve" ) ) != nullptr )
			return SetMaterial( pLocalPlayer, pContext, _State, _Info, pMatrix, draw_model_execute_t( fnDrawModelExecute ), nullptr, SETTING_MATERIALS_SELF );

		const auto pEntity = entity_ptr_t( pEntityList->GetClientEntity( _Info.entity_index ) );
		if ( pEntity ) // a player's active weapons are rendered with the entity index of the posessing player.
		{
			if ( strstr( _Info.pModel->szName, PX_XOR( R"(weapons/)" ) ) != nullptr )
				return SetMaterial( pLocalPlayer, pContext, _State, _Info, pMatrix, draw_model_execute_t( fnDrawModelExecute ),
									nullptr, strstr( _Info.pModel->szName, PX_XOR( "v_" ) ) != nullptr ? SETTING_MATERIALS_HELD_WEAPONS : SETTING_MATERIALS_PLAYER_WEAPONS );
			if( player_ptr_t( pEntity )->IsAlive( ) )
				return SetMaterial( pLocalPlayer, pContext, _State, _Info, pMatrix, draw_model_execute_t( fnDrawModelExecute ),
									nullptr, player_ptr_t( pEntity )->m_iTeamNum( ) != pLocalPlayer->m_iTeamNum( ) ? SETTING_MATERIALS_ENEMY : SETTING_MATERIALS_TEAM );
		}

		return false;
	}

	void PX_API RenderEntities( player_ptr_t pLocalPlayer )
	{
		const auto fnDrawEntity = [ ]( settings_t::awareness_t::materials_t::entity_t& _Config, entity_ptr_t pEntity )
		{
			if ( !_Config.bEnabled.Get( ) )
				return;

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
		};

		vecRenderables.clear( );

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
					const auto hWeapons = player_ptr_t( pEntity )->m_hMyWeapons( );
					const auto hActiveWeapon = player_ptr_t( pEntity )->m_hActiveWeapon( );
					for( auto h = 0; h < 8; h++ )
					{
						const auto hWeapon = hWeapons[ h ];
						if ( hWeapon && hWeapon != hActiveWeapon )
							fnDrawEntity( _Settings._Awareness._Materials._Entities[ SETTING_MATERIALS_PLAYER_WEAPONS ], hWeapon );
					}
					continue;
				}

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
					if ( pEntity->IsWeapon( ) )
						iSettingIndex = SETTING_MATERIALS_WEAPONS;
					else
						continue;
				}
				break;
			}

			fnDrawEntity( _Settings._Awareness._Materials._Entities[ iSettingIndex ], pEntity );
			vecRenderables.emplace_back( pEntity->GetClientRenderable( ) );
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
		pModelRender->ForcedMaterialOverride( nullptr );
		return true;
	}
}
