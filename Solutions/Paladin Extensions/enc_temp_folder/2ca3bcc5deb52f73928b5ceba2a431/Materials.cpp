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
		MATERIAL_REFLECTIVE,
		MATERIAL_GLOW,
		MATERIAL_GLASS,
		MATERIAL_CRYSTAL,
		MATERIAL_GOLD,
		MATERIAL_MAX
	};

	struct material_t
	{
		std::string wstrData, wstrFileName, strTextureGroup;
		IMaterial* pMaterial;
		bool bCreateFile;
		material_t( std::string w, std::string f, std::string g ): wstrData( w ), wstrFileName( f ), strTextureGroup( g ), pMaterial( nullptr ), bCreateFile( true )
		{ }

		material_t( std::string f, std::string g ): wstrFileName( f ), strTextureGroup( g ), pMaterial( nullptr ), bCreateFile( false )
		{ }
	};

	material_t matMaterials[ MATERIAL_MAX ]
	{
		material_t( PX_XOR( // MATERIAL_DEFAULT
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
)#" ), PX_XOR( "default" ), TEXTURE_GROUP_MODEL ),

		material_t( PX_XOR( // MATERIAL_DEFAULT_IGNOREZ
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
)#" ), PX_XOR( "default_ignorez" ), TEXTURE_GROUP_MODEL ),

		material_t( PX_XOR( // MATERIAL_DEFAULT_FLAT
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
)#" ), PX_XOR( "default_flat" ), TEXTURE_GROUP_MODEL ),

		material_t( PX_XOR( // MATERIAL_DEFAULT_FLAT_IGNOREZ
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
)#" ), PX_XOR( "default_flat_ignorez" ), TEXTURE_GROUP_MODEL ),

		///

		material_t( PX_XOR( R"(models/player/ct_fbi/ct_fbi_glass)" ), TEXTURE_GROUP_OTHER ),
		material_t( PX_XOR( R"(dev/glow_armsrace)" ), TEXTURE_GROUP_OTHER ),
		material_t( PX_XOR( R"(models/inventory_items/cologne_prediction/cologne_prediction_glass)" ), TEXTURE_GROUP_OTHER ),
		material_t( PX_XOR( R"(models/inventory_items/trophy_majors/crystal_clear)" ), TEXTURE_GROUP_OTHER ),
		material_t( PX_XOR( R"(models/inventory_items/trophy_majors/gold)" ), TEXTURE_GROUP_OTHER )
	};

	std::vector< std::pair< int, Vector > > vecLocations { };

	bool PX_API CreateMaterials( )
	{
		for ( auto& material : matMaterials )
		{
			if( material.bCreateFile )
				std::ofstream( PX_XOR( "csgo\\materials\\" ) + material.wstrFileName + PX_XOR( ".vmt" ) ) << material.wstrData;
			if ( ( material.pMaterial = pMaterialSystem->FindMaterial( material.wstrFileName.empty( ) ? nullptr : material.wstrFileName.c_str( ), material.bCreateFile ? TEXTURE_GROUP_MODEL : TEXTURE_GROUP_OTHER ) ) == nullptr )
				return false;
		}
		return true;
	}

	void PX_API RemoveMaterials( )
	{
		for ( auto& material : matMaterials )
			std::remove( ( PX_XOR( "csgo\\materials\\" ) + material.wstrFileName + PX_XOR( ".vmt" ) ).c_str( ) );
	}

	int PX_API GetSettingIndex( entity_ptr_t pEntity );
	bool PX_API SetMaterial( IMatRenderContext* pContext, const DrawModelState_t& _State, const ModelRenderInfo_t& _Info, matrix3x4_t* pMatrix, draw_model_execute_t fnDrawModelExecute, entity_ptr_t pEntity, int iSettingIndex );

	void PX_API SetEntityLocations( )
	{
		for ( auto i = 0; i < pEntityList->GetMaxEntities( ); i++ )
		{
			const auto pEntity = entity_ptr_t( pEntityList->GetClientEntity( i ) );
			if ( pEntity == nullptr )
				continue;

			const auto iSettingIndex = GetSettingIndex( pEntity );
			if ( iSettingIndex == -1 )
				continue;

			if ( _Settings._Awareness._Materials._Entities[ iSettingIndex ].bEnabled.Get( ) )
			{
				vecLocations.emplace_back( );
				auto& location = vecLocations.back( );
				location.first = pEntity->EntIndex( );
				location.second = pEntity->m_vecOrigin( );
				pEntity->m_vecOrigin( ) = Vector( 0, 0, 0 );
				pEntity->SetABSOrigin( pEntity->m_vecOrigin( ) );
			}
		}
	}

	bool PX_API OverrideMaterial( player_ptr_t pLocalPlayer, IMatRenderContext* pContext, const DrawModelState_t& _State, const ModelRenderInfo_t& _Info, matrix3x4_t* pMatrix, void* fnDrawModelExecute )
	{
		if ( pModelRender->IsForcedMaterialOverride( ) )
			return false;

		if ( strstr( _Info.pModel->szName, PX_XOR( "arms" ) ) != nullptr
			 || strstr( _Info.pModel->szName, PX_XOR( "sleeve" ) ) != nullptr )
			return SetMaterial( pContext, _State, _Info, pMatrix, draw_model_execute_t( fnDrawModelExecute ), nullptr, SETTING_MATERIALS_SELF );

		if ( strstr( _Info.pModel->szName, PX_XOR( R"(chicken/chicken)" ) ) != nullptr )
			return SetMaterial( pContext, _State, _Info, pMatrix, draw_model_execute_t( fnDrawModelExecute ), nullptr, SETTING_MATERIALS_CHICKEN );

		const auto pEntity = entity_ptr_t( pEntityList->GetClientEntity( _Info.entity_index ) );
		if ( pEntity ) // a player's active weapons are rendered with the entity index of the posessing player.
		{
			if ( strstr( _Info.pModel->szName, PX_XOR( R"(weapons/)" ) ) != nullptr )
			{
				if ( strstr( _Info.pModel->szName, PX_XOR( R"(_dropped)" ) ) != nullptr )
					return SetMaterial( pContext, _State, _Info, pMatrix, draw_model_execute_t( fnDrawModelExecute ),
										nullptr, SETTING_MATERIALS_WEAPONS );
				return SetMaterial( pContext, _State, _Info, pMatrix, draw_model_execute_t( fnDrawModelExecute ),
									nullptr, strstr( _Info.pModel->szName, PX_XOR( "v_" ) ) != nullptr ? SETTING_MATERIALS_HELD_WEAPONS : SETTING_MATERIALS_PLAYER_WEAPONS );
			}
			auto strLower = std::string( _Info.pModel->szName );
			for ( auto& character : strLower )
				character = std::tolower( character );

			if ( strLower.find( PX_XOR( "varianta" ) ) != std::string::npos )
				return SetMaterial( pContext, _State, _Info, pMatrix, draw_model_execute_t( fnDrawModelExecute ),
									nullptr, player_ptr_t( pEntity )->m_iTeamNum( ) != pLocalPlayer->m_iTeamNum( ) ? SETTING_MATERIALS_ENEMY : SETTING_MATERIALS_TEAM );
			if ( strLower.find( PX_XOR( "variantb" ) ) != std::string::npos )
				return SetMaterial( pContext, _State, _Info, pMatrix, draw_model_execute_t( fnDrawModelExecute ),
									nullptr, player_ptr_t( pEntity )->m_iTeamNum( ) != pLocalPlayer->m_iTeamNum( ) ? SETTING_MATERIALS_ENEMY_CORPSE : SETTING_MATERIALS_TEAM_CORPSE );
		}

		return false;
	}

	void PX_API RenderEntities( )
	{
		for ( auto i = 0; i < pEntityList->GetMaxEntities( ); i++ )
		{
			const auto pEntity = entity_ptr_t( pEntityList->GetClientEntity( i ) );
			if ( pEntity == nullptr )
				continue;

			if ( pEntity->GetClientClass( )->m_ClassID == ClassID_CCSPlayer )
			{
				const auto hWeapons = player_ptr_t( pEntity )->m_hMyWeapons( );
				const auto hActiveWeapon = player_ptr_t( pEntity )->m_hActiveWeapon( );
				for ( auto h = 0; h < 8; h++ )
				{
					const auto hWeapon = hWeapons[ h ];
					if ( hWeapon && hWeapon != hActiveWeapon )
					{
						for ( auto u = 0u; u < vecLocations.size( ); u++ )
							if ( vecLocations[ u ].first == hWeapon->EntIndex( ) )
							{
								hWeapon->SetABSOrigin( vecLocations[ u ].second );
								hWeapon->m_vecOrigin( ) = vecLocations[ u ].second;
								vecLocations.erase( vecLocations.begin( ) + u );
								hWeapon->DrawModel( 1, 255 );
								break;
							}
					}
				}
				if ( player_ptr_t( pEntity )->IsAlive( ) )
					continue;
				std::cout << "men" << std::endl;
			}

			for ( auto u = 0u; u < vecLocations.size( ); u++ )
				if ( vecLocations[ u ].first == pEntity->EntIndex( ) )
				{
					pEntity->SetABSOrigin( vecLocations[ u ].second );
					pEntity->m_vecOrigin( ) = vecLocations[ u ].second;
					vecLocations.erase( vecLocations.begin( ) + u );
					pEntity->DrawModel( 1, 255 );
					break;
				}
		}
		vecLocations.clear( );
	}

	int PX_API GetSettingIndex( entity_ptr_t pEntity )
	{
		auto iSettingIndex = -1;

		switch ( pEntity->GetClientClass( )->m_ClassID )
		{
			case ClassID_CCSPlayer:
			{
				const auto pLocalPlayer = GetLocalPlayer( );
				if ( pLocalPlayer != nullptr )
					if ( !player_ptr_t( pEntity )->IsAlive( ) )
						iSettingIndex = player_ptr_t( pEntity )->m_iTeamNum( ) == pLocalPlayer->m_iTeamNum( ) ? SETTING_MATERIALS_TEAM_CORPSE : SETTING_MATERIALS_ENEMY_CORPSE;
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

			case ClassID_CChicken:
			{
				iSettingIndex = SETTING_MATERIALS_CHICKEN;
			}
			break;

			default:
			{
				if ( pEntity->IsWeapon( ) )
					iSettingIndex = SETTING_MATERIALS_WEAPONS;
			}
			break;
		}

		return iSettingIndex;
	}

	bool PX_API SetMaterial( IMatRenderContext* pContext, const DrawModelState_t& _State, const ModelRenderInfo_t& _Info, matrix3x4_t* pMatrix, draw_model_execute_t fnDrawModelExecute, entity_ptr_t pEntity, int iSettingIndex )
	{
		const auto fnDrawModel = [ & ]( int iMaterialSetting, bool bWireFrame, color_t clrVisible, const color_t& clrInvisible, bool bDrawForeground = true )
		{
			IMaterial* pForeground = nullptr;

			if( iMaterialSetting == MATERIAL_IGNOREZ || iMaterialSetting == MATERIAL_FLAT_IGNOREZ )
			{
				const auto pCurrent = matMaterials[ iMaterialSetting ].pMaterial;
				pForeground = matMaterials[ iMaterialSetting == MATERIAL_IGNOREZ ? MATERIAL_DEFAULT : MATERIAL_FLAT ].pMaterial;

				pCurrent->SetMaterialVarFlag( MATERIAL_VAR_WIREFRAME, bWireFrame );
				pCurrent->AlphaModulate( clrInvisible.afl );
				pCurrent->ColorModulate( clrInvisible.rfl, clrInvisible.gfl, clrInvisible.bfl );
				pModelRender->ForcedMaterialOverride( pCurrent );
				fnDrawModelExecute( pModelRender, pContext, _State, _Info, pMatrix );
			}

			if ( bDrawForeground )
			{
				if ( !pForeground )
					pForeground = matMaterials[ iMaterialSetting ].pMaterial;

				pForeground->SetMaterialVarFlag( MATERIAL_VAR_WIREFRAME, bWireFrame );
				pForeground->AlphaModulate( clrVisible.afl );
				pForeground->ColorModulate( clrVisible.rfl, clrVisible.gfl, clrVisible.bfl );
				pModelRender->ForcedMaterialOverride( pForeground );
				fnDrawModelExecute( pModelRender, pContext, _State, _Info, pMatrix );
			}
			pModelRender->ForcedMaterialOverride( nullptr );
		};

		auto& _Config = _Settings._Awareness._Materials._Entities[ iSettingIndex ];
		if ( !_Config.bEnabled.Get( ) )
			return false;

		if ( _Config.bWireFrameUnderlay.Get( ) )
			fnDrawModel( MATERIAL_FLAT_IGNOREZ, true, _Config.seqWireFrameUnderlay[ STATE_VISIBLE ].GetCurrentColor( ), _Config.seqWireFrameUnderlay[ STATE_INVISIBLE ].GetCurrentColor( ), false );

		fnDrawModel( _Config.iMaterial, _Config.bWireFrame.Get( ), _Config.seqColor[ STATE_VISIBLE ].GetCurrentColor( ), _Config.seqColor[ STATE_INVISIBLE ].GetCurrentColor( ) );

		if( _Config.bWireFrameOverlay.Get( ) )
			fnDrawModel( MATERIAL_FLAT_IGNOREZ, true, _Config.seqWireFrameOverlay[ STATE_VISIBLE ].GetCurrentColor( ), _Config.seqWireFrameOverlay[ STATE_INVISIBLE ].GetCurrentColor( ) );

		return true;
	}
}
