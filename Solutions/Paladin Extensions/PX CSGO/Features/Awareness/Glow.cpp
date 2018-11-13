/// Glow.cpp

#include "PX Precompiled.hpp"
#include "../../PX CSGO.hpp"

using namespace PX::Information;
using namespace PX::Tools;
using namespace Pointers;

namespace PX::Features::Awareness
{
	auto glwConfig = &_Settings._Awareness._Glow;

	void PX_API FormGlowArray( );
	void PX_API GlowPlayer( player_ptr_t pLocalPlayer, player_ptr_t pPlayer, GlowObjectDefinition_t *pObject );
	void PX_API GlowEntity( player_ptr_t pLocalPlayer, entity_ptr_t pEntity, GlowObjectDefinition_t *pObject, int iSettingIndex );
	void PX_API ResetDefinition( GlowObjectDefinition_t *pObject );

	void PX_API GlowEntities( )
	{
		const auto pLocalPlayer = GetLocalPlayer( );
		if ( nullptr == pLocalPlayer )
			return;

		FormGlowArray( );
		GlowObjectDefinition_t *pObject;
		for ( auto i = 0; i < pGlowObjectManager->m_GlowObjectDefinitions.Count( )
			  && nullptr != ( pObject = &pGlowObjectManager->m_GlowObjectDefinitions[ i ] ); i++ )
		{
			if ( pObject->IsUnused( ) )
				continue;

			const auto pEntity = entity_ptr_t( pObject->m_pEntity );
			if ( nullptr == pEntity )
				continue;
			switch ( pEntity->GetClientClass( )->m_ClassID )
			{
				case ClassID_CCSPlayer:
				{
					GlowPlayer( pLocalPlayer, player_ptr_t( pEntity ), pObject );
				}
				break;

				case ClassID_CC4:
				{
					GlowEntity( pLocalPlayer, pEntity, pObject, SETTING_ENTITY_C4 );
				}
				break;

				case ClassID_CPlantedC4:
				{
					GlowEntity( pLocalPlayer, pEntity, pObject, SETTING_ENTITY_PLANTED_C4 );
				}
				break;

				case ClassID_CBaseAnimating:
				{
					GlowEntity( pLocalPlayer, pEntity, pObject, SETTING_ENTITY_DEFUSER );
				}
				break;

				case ClassID_CChicken:
				{
					GlowEntity( pLocalPlayer, pEntity, pObject, SETTING_ENTITY_CHICKEN );
				}

				case ClassID_CHEGrenade:
				{
					GlowEntity( pLocalPlayer, pEntity, pObject, SETTING_ENTITY_GRENADE_HE );
				}
				break;

				case ClassID_CFlashbang:
				{
					GlowEntity( pLocalPlayer, pEntity, pObject, SETTING_ENTITY_GRENADE_FLASH );
				}
				break;

				case ClassID_CSmokeGrenade:
				{
					GlowEntity( pLocalPlayer, pEntity, pObject, SETTING_ENTITY_GRENADE_SMOKE );
				}
				break;

				case ClassID_CDecoyGrenade:
				{
					GlowEntity( pLocalPlayer, pEntity, pObject, SETTING_ENTITY_GRENADE_DECOY );
				}
				break;

				case ClassID_CIncendiaryGrenade:
				{
					GlowEntity( pLocalPlayer, pEntity, pObject, SETTING_ENTITY_GRENADE_INCENDIARY );
				}
				break;

				case ClassID_CBaseCSGrenadeProjectile: // hegrenade & flashbang
				{
					const auto iModelIndex = reinterpret_cast< CBaseViewModel * >( pEntity )->m_nModelIndex( );
					if ( iModelIndex == Other::GetModelIndex( ITEM_WEAPON_FLASHBANG ) )
						GlowEntity( pLocalPlayer, pEntity, pObject, SETTING_ENTITY_GRENADE_PROJECTILE_FLASH );
					else if ( iModelIndex == Other::GetModelIndex( ITEM_WEAPON_HEGRENADE ) )
						GlowEntity( pLocalPlayer, pEntity, pObject, SETTING_ENTITY_GRENADE_PROJECTILE_HE );
				}
				break;

				case ClassID_CSmokeGrenadeProjectile:
				{
					GlowEntity( pLocalPlayer, pEntity, pObject, SETTING_ENTITY_GRENADE_PROJECTILE_SMOKE );
				}
				break;

				case ClassID_CDecoyProjectile:
				{
					GlowEntity( pLocalPlayer, pEntity, pObject, SETTING_ENTITY_GRENADE_PROJECTILE_DECOY );
				}
				break;

				case ClassID_CMolotovProjectile:
				{
					GlowEntity( pLocalPlayer, pEntity, pObject, SETTING_ENTITY_GRENADE_PROJECTILE_INCENDIARY );
				}
				break;

				default:
				{
					if ( pEntity->IsWeapon( ) )
						GlowEntity( pLocalPlayer, pEntity, pObject, SETTING_ENTITY_WEAPONS );
				}
					break;
			}
		}
	}

	void PX_API FormGlowArray( )
	{
		for ( auto i = 0; i < pEntityList->GetMaxEntities( ); i++ )
		{
			const auto pEntity = entity_ptr_t( pEntityList->GetClientEntity( i ) );
			if ( nullptr == pEntity )
				continue;

			const auto iClassID = pEntity->GetClientClass( )->m_ClassID;
			if ( iClassID != ClassID_CCSPlayer
				&& iClassID != ClassID_CC4
				&& iClassID != ClassID_CPlantedC4
				&& iClassID != ClassID_CBaseAnimating
				&& !pEntity->IsWeapon( ) )
				continue;
			if ( !pGlowObjectManager->HasGlowEffect( pEntity ) )
				*reinterpret_cast< int * >( ptr_t( pEntity ) + 0xA330 ) = pGlowObjectManager->RegisterGlowObject( pEntity, -1 );
		}
	}

	void PX_API GlowPlayer( player_ptr_t pLocalPlayer, player_ptr_t pPlayer, GlowObjectDefinition_t *pObject )
	{
		if ( !pPlayer->IsAlive( ) )
			return;

		auto &_Current = glwConfig->_Players[ pLocalPlayer->m_iTeamNum( ) == pPlayer->m_iTeamNum( ) ? 0 : 1 ];
		if ( !_Current.bEnabled )
			return ResetDefinition( pObject );

		const auto iState = pPlayer->IsDormant( ) ? STATE_DORMANT : pLocalPlayer->CanSeePlayer( pPlayer, _Current.bMindSmoke.Get( ) ) ? STATE_VISIBLE : STATE_INVISIBLE;
		const auto clrCurrent = _Current.seqColor[ iState ].GetCurrentColor( );

		if ( clrCurrent.a == 0 )
			return ResetDefinition( pObject );

		if ( _Current.bHealthBasedColor.Get( ) )
		{
			const auto iHealth = pPlayer->m_iHealth( );
			pObject->m_flRed = ( 100.f - iHealth ) / 100.f;
			pObject->m_flGreen = 1.f - pObject->m_flRed;
			pObject->m_flBlue = 0.f;
			pObject->m_flAlpha = clrCurrent.afl;
		}
		else
		{
			pObject->m_flRed = clrCurrent.GetRedFloat( );
			pObject->m_flGreen = clrCurrent.GetGreenFloat( );
			pObject->m_flBlue = clrCurrent.GetBlueFloat( );
			pObject->m_flAlpha = clrCurrent.GetAlphaFloat( );
		}
		pObject->m_bFullBloomRender = _Current.bFullBloom.Get( );
		pObject->m_flFullBloomAmount = pObject->m_bFullBloomRender ? _Current.flFullBloomAmount : 1.f;
		pObject->m_nGlowStyle = _Current.iGlowStyle;
		pObject->m_bRenderWhenOccluded = true;
		pObject->m_bRenderWhenUnoccluded = false;
	}

	void PX_API GlowEntity( player_ptr_t pLocalPlayer, entity_ptr_t pEntity, GlowObjectDefinition_t *pObject, int iSettingIndex )
	{
		auto &_Current = glwConfig->_Entities[ iSettingIndex ];
		if ( !_Current.bEnabled )
			return ResetDefinition( pObject );

		auto vecLocation = pEntity->m_vecOrigin( );
		vecLocation.z += 0.5f;
		const auto iState = pLocalPlayer->CanSeePosition( vecLocation, _Current.bMindSmoke.Get( ), pEntity ) ? STATE_VISIBLE : STATE_INVISIBLE;
		const auto clrCurrent = _Current.seqColor[ iState ].GetCurrentColor( );
		if ( clrCurrent.a == 0 )
			return ResetDefinition( pObject );

		pObject->m_flRed = clrCurrent.GetRedFloat( );
		pObject->m_flGreen = clrCurrent.GetGreenFloat( );
		pObject->m_flBlue = clrCurrent.GetBlueFloat( );
		pObject->m_flAlpha = clrCurrent.GetAlphaFloat( );
		pObject->m_bFullBloomRender = _Current.bFullBloom.Get( );
		pObject->m_flFullBloomAmount = pObject->m_bFullBloomRender ? _Current.flFullBloomAmount : 1.f;
		pObject->m_nGlowStyle = _Current.iGlowStyle;
		pObject->m_bRenderWhenOccluded = true;
		pObject->m_bRenderWhenUnoccluded = false;
	}

	void PX_API ResetDefinition( GlowObjectDefinition_t *pObject )
	{
		pObject->m_flRed = pObject->m_flGreen = pObject->m_flBlue = pObject->m_flAlpha = pObject->m_flFullBloomAmount = 0.f;
		pObject->m_bRenderWhenOccluded = pObject->m_bRenderWhenUnoccluded = pObject->m_bFullBloomRender = false;
		pObject->m_nGlowStyle = 0;
	}
}
