/// Glow.cpp

#include "PX Precompiled.hpp"
#include "../../PX CSGO.hpp"

using namespace PX::Information;
using namespace PX::Tools;
using namespace Pointers;

namespace PX::Features::Awareness
{
	auto glwConfig = &_Settings._Awareness._Glow;

	void PX_API GlowPlayer( player_ptr_t pLocalPlayer, player_ptr_t pPlayer, GlowObjectDefinition_t* pObject );
	void PX_API GlowEntity( player_ptr_t pLocalPlayer, entity_ptr_t pEntity, GlowObjectDefinition_t* pObject, int iSettingIndex );
	void PX_API ResetDefinition( GlowObjectDefinition_t* pObject );

	void PX_API GlowEntities( )
	{
		const auto pLocalPlayer = GetLocalPlayer( );
		if ( nullptr == pLocalPlayer )
			return;

		GlowObjectDefinition_t* pObject;
		for( auto i = 0; i < pGlowObjectManager->m_GlowObjectDefinitions.Count( ) 
			 && nullptr != ( pObject = &pGlowObjectManager->m_GlowObjectDefinitions[ i ] ); i++ )
		{
			if ( pObject->IsUnused( ) )
				continue;
		
			const auto pEntity = entity_ptr_t( pObject->m_pEntity );
			if ( nullptr == pEntity )
				continue;
			switch( pEntity->GetClientClass( )->m_ClassID )
			{
				case ClassID_CCSPlayer:
				{
					GlowPlayer( pLocalPlayer, player_ptr_t( pEntity ), pObject );
				}
				break;

				case ClassID_CC4:
				case ClassID_CPlantedC4:
				{
					GlowEntity( pLocalPlayer, pEntity, pObject, 1 );
				}
				break;

				case ClassID_CBaseAnimating:
				{
					GlowEntity( pLocalPlayer, pEntity, pObject, 2 );
				}
				break;

				default:
				{
					if ( pEntity->IsGrenade( ) )
						GlowEntity( pLocalPlayer, pEntity, pObject, 3 );
					else if ( pEntity->IsWeapon( ) )
						GlowEntity( pLocalPlayer, pEntity, pObject, 0 );
				}
				break;
			}
		}
	}

	void PX_API GlowPlayer( player_ptr_t pLocalPlayer, player_ptr_t pPlayer, GlowObjectDefinition_t* pObject )
	{
		if ( !pPlayer->IsAlive( ) )
			return;

		auto& _Current = glwConfig->_Players[ pLocalPlayer->m_iTeamNum( ) == pPlayer->m_iTeamNum( ) ? 0 : 1 ];
		if ( !_Current.bEnabled )
			return;

		const auto iState = pPlayer->IsDormant( ) ? STATE_DORMANT : pLocalPlayer->CanSeePlayer( pPlayer, _Current.bMindSmoke.Get( ) ) ? STATE_VISIBLE : STATE_INVISIBLE;
		if ( !_Current.bStates[ iState ] )
			return ResetDefinition( pObject );

		if( _Current.bHealthBasedColor.Get( ) )
		{
			const auto iHealth = pPlayer->m_iHealth( );
			pObject->m_flRed = ( 100.f - iHealth ) / 100.f;
			pObject->m_flGreen = 1.f - pObject->m_flRed;
			pObject->m_flBlue = 0.f;
			pObject->m_flAlpha = 1.f;
		}
		else
		{
			const auto clrCurrent = _Current.seqColor[ iState ].GetCurrentColor( );
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

	void PX_API GlowEntity( player_ptr_t pLocalPlayer, entity_ptr_t pEntity, GlowObjectDefinition_t* pObject, int iSettingIndex )
	{
		auto& _Current = glwConfig->_Entities[ iSettingIndex ];
		if ( !_Current.bEnabled )
			return;

		const auto iState = pLocalPlayer->PositionInSight( pEntity->m_vecOrigin( ), _Current.bMindSmoke.Get( ), pEntity ) ? STATE_VISIBLE : STATE_INVISIBLE;
		if ( !_Current.bStates[ iState ] )
			return ResetDefinition( pObject );

		const auto clrCurrent = _Current.seqColor[ iState ].GetCurrentColor( );
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

	void PX_API ResetDefinition( GlowObjectDefinition_t* pObject )
	{
		pObject->m_flRed = pObject->m_flGreen = pObject->m_flBlue = pObject->m_flAlpha = pObject->m_flFullBloomAmount = 0.f;
		pObject->m_bRenderWhenOccluded = pObject->m_bRenderWhenUnoccluded = pObject->m_bFullBloomRender = false;
		pObject->m_nGlowStyle = 0;
	}
}
