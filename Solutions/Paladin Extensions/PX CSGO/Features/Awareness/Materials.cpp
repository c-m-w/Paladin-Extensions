/// Materials.cpp

#include "PX Precompiled.hpp"
#include "../../PX CSGO.hpp"

using namespace PX;
using namespace Information;
using namespace Pointers;
using namespace Tools;

namespace PX::Features::Awareness
{
	bool PX_API SetMaterial( player_ptr_t pLocalPlayer, IMatRenderContext* pContext, const DrawModelState_t& _State, const ModelRenderInfo_t& _Info, matrix3x4_t* pMatrix, void* fnDrawModelExecute, entity_ptr_t pEntity, int iSettingIndex );

	bool PX_API OverrideMaterial( player_ptr_t pLocalPlayer, IMatRenderContext* pContext, const DrawModelState_t& _State, const ModelRenderInfo_t& _Info, matrix3x4_t* pMatrix, void* fnDrawModelExecute )
	{
		const auto pEntity = entity_ptr_t( pEntityList->GetClientEntity( _Info.entity_index ) );
		if ( pEntity == nullptr )
			return false;
		auto iSettingIndex = 0;

		switch ( pEntity->GetClientClass( )->m_ClassID )
		{
			case ClassID_CCSPlayer:
			{
				if ( !player_ptr_t( pEntity )->IsAlive( ) )
					return false;
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
				if ( strstr( _Info.pModel->szName, PX_XOR( "flashbang" ) ) != nullptr )
					iSettingIndex = SETTING_MATERIALS_PROJECTILE_FLASH;
				else if ( strstr( _Info.pModel->szName, PX_XOR( "fraggrenade" ) ) != nullptr )
					iSettingIndex = SETTING_MATERIALS_PROJECTILE_HE;
				else
					return false;
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
				else if ( strstr( _Info.pModel->szName, PX_XOR( "arms" ) ) != nullptr )
					iSettingIndex = SETTING_MATERIALS_ARMS;
				else if ( strstr( _Info.pModel->szName, PX_XOR( "sleeve" ) ) != nullptr )
					iSettingIndex = SETTING_MATERIALS_SLEEVES;
				else
					return false;
			}
			break;
		}

		return SetMaterial( pLocalPlayer, pContext, _State, _Info, pMatrix, fnDrawModelExecute, pEntity, iSettingIndex );
	}

	bool PX_API SetMaterial( player_ptr_t pLocalPlayer, IMatRenderContext* pContext, const DrawModelState_t& _State, const ModelRenderInfo_t& _Info, matrix3x4_t* pMatrix, void* fnDrawModelExecute, entity_ptr_t pEntity, int iSettingIndex )
	{
		auto& _Config = _Settings._Awareness._Materials._Entities[ iSettingIndex ];
		if ( !_Config.bEnabled.Get( ) )
			return false;

		const auto iState = pEntity->IsDormant( ) ? STATE_DORMANT :
			pEntity->IsPlayer( ) ? ( pLocalPlayer->CanSeePlayer( player_ptr_t( pEntity ), _Config.bMindSmoke.Get( ) ) ? STATE_VISIBLE : STATE_INVISIBLE )
			: pLocalPlayer->CanSeePosition( pEntity->m_vecOrigin( ), _Config.bMindSmoke.Get( ), pEntity ) ? STATE_VISIBLE : STATE_INVISIBLE;
		const auto clrPrimary = _Config.seqColor[ iState ].GetCurrentColor( );
		if ( clrPrimary.a == 0 )
			return false;
		const auto clrSecondary = _Config.seqColor[ iState == STATE_VISIBLE ? STATE_INVISIBLE : STATE_VISIBLE ].GetCurrentColor( );

	}
}
