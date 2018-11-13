/// Inventory.cpp

#include "PX Precompiled.hpp"
#include "../../PX CSGO.hpp"

using namespace PX;
using namespace Tools;
using namespace Information;
using namespace Pointers;
using namespace Other;

namespace PX::Features::Miscellaneous
{
	settings_t::miscellaneous_t::inventory_t::team_t* pConfig = nullptr;

	struct
	{
		CBaseHandle hGlove { };
	} _InventoryContext;

	bool PX_API ModifyPaintKit( CBaseAttributableItem* pEntity );
	bool PX_API ModifyKnifeModel( player_ptr_t pLocalPlayer, CBaseCombatWeapon* pWeapon );
	bool PX_API ModifyGloveModel( player_ptr_t pLocalPlayer );
	void PX_API DestroyWearables( player_ptr_t pLocalPlayer );

	void PX_API ModifyInventory( )
	{
		static ptr_t ptrOldWeapons[ 8 ] { };
		if ( !pEngineClient->IsInGame( ) )
			return;

		const auto pLocalPlayer = GetLocalPlayer( );
		if ( pLocalPlayer == nullptr
			 || !pLocalPlayer->IsAlive( ) )
			return DestroyWearables( pLocalPlayer );

		pConfig = pLocalPlayer->m_iTeamNum( ) == 3
			? &_Settings._Miscellaneous._Inventory._CounterTerrorist
			: &_Settings._Miscellaneous._Inventory._Terrorist;
		auto bForceUpdate = false;

		const auto hActiveWeapon = pLocalPlayer->m_hActiveWeapon( );

		if ( hActiveWeapon != nullptr )
		{
			if ( hActiveWeapon->IsKnife( ) )
				if ( ModifyKnifeModel( pLocalPlayer, hActiveWeapon.Get( ) ) )
					bForceUpdate = true;
		}

		const auto hWeapons = pLocalPlayer->m_hMyWeapons( );
		const auto iLocalPlayerIndex = pLocalPlayer->EntIndex( );
		for( auto i = 0; i < 8; i++ )
		{
			const auto hWeapon = hWeapons[ i ];
			const auto pOwner = pEntityList->GetClientEntityFromHandle( hWeapon );
			if ( pOwner != nullptr )
				if( pOwner->EntIndex( ) == iLocalPlayerIndex )
					if( ModifyPaintKit( reinterpret_cast< CBaseAttributableItem* >( pEntityList->GetClientEntityFromHandle( hWeapon ) ) )
						&& ptr_t( hWeapon.Get( ) ) != ptrOldWeapons[ i ] )
						bForceUpdate = true;

			ptrOldWeapons[ i ] = ptr_t( hWeapon.Get( ) );
		}

		if ( _InventoryContext.hGlove != nullptr )
			if ( ModifyPaintKit( reinterpret_cast< CBaseAttributableItem* >( pEntityList->GetClientEntityFromHandle( _InventoryContext.hGlove ) ) ) )
				bForceUpdate = true;

		if ( ModifyGloveModel( pLocalPlayer ) )
			bForceUpdate = true;

		if ( bForceUpdate )
			pClientState->ForceFullUpdate( );
	}

	bool PX_API ModifyPaintKit( CBaseAttributableItem* pEntity )
	{
		const auto pItem = pEntity->m_Item( );
		const auto iIndex = pItem->m_iItemDefinitionIndex( );
		const auto pCurrentConfig = &pConfig->_PaintKits[ iIndex ];
		auto bReturn = false;

		if ( pCurrentConfig->iPaintKitID != pEntity->m_nFallbackPaintKit( )
			 || pCurrentConfig->bStatTrak.Get( )
			 && pCurrentConfig->iStatTrakCounter != pEntity->m_nFallbackStatTrak( )
			 || pCurrentConfig->bSouvenier.Get( )
			 && pItem->m_iEntityQuality( ) != QUALITY_SOUVENIER
			 || pCurrentConfig->flWear != pEntity->m_flFallbackWear( )
			 || pCurrentConfig->iSeed != pEntity->m_nFallbackSeed( ) )
			bReturn = true;

		pEntity->m_nFallbackPaintKit( ) = pCurrentConfig->iPaintKitID;
		if ( pCurrentConfig->bStatTrak.Get( ) )
		{
			pItem->m_iEntityQuality( ) = QUALITY_STATTRAK;
			pEntity->m_nFallbackStatTrak( ) = pCurrentConfig->iStatTrakCounter;
		}
		else
			pEntity->m_nFallbackStatTrak( ) = -1;
		if ( pCurrentConfig->bSouvenier.Get( ) )
			pItem->m_iEntityQuality( ) = QUALITY_SOUVENIER;

		if ( reinterpret_cast< CBaseCombatWeapon* >( pEntity )->IsKnife( ) )
			pItem->m_iEntityQuality( ) = QUALITY_KNIFE;

		if ( strlen( pCurrentConfig->szName ) != 0 )
			pEntity->m_szCustomName( ) = pCurrentConfig->szName;
		else
			pEntity->m_szCustomName( ) = nullptr;

		pEntity->m_flFallbackWear( ) = pCurrentConfig->flWear;
		pEntity->m_nFallbackSeed( ) = pCurrentConfig->iSeed;
		pEntity->m_OriginalOwnerXuidHigh( ) = 0;
		pEntity->m_OriginalOwnerXuidLow( ) = 0;

		return bReturn;
	}

	bool PX_API ModifyKnifeModel( player_ptr_t pLocalPlayer, CBaseCombatWeapon* pWeapon )
	{
		constexpr auto fnSetModelIndex = [ ]( CBaseViewModel* vm, int i )
		{
			vm->m_nModelIndex( ) = i;
			vm->m_nViewModelIndex( ) = i;
		};

		auto bReturn = false;

		if ( !pConfig->bModifyKnifeModel.Get( ) )
			return bReturn;

		const auto pViewModel = pLocalPlayer->m_hViewModel( );
		if ( pViewModel == nullptr )
			return bReturn;

		const auto pItem = pWeapon->m_Item( );
		auto& iItemDefinitionIndex = pItem->m_iItemDefinitionIndex( );
		const auto iKnifeModelIndex = GetModelIndex( pConfig->_Models.iKnifeModel );
		if ( iKnifeModelIndex == 0 )
			return bReturn;

		pItem->m_iItemIDHigh( ) = -1;
		pItem->m_iEntityQuality( ) = QUALITY_KNIFE;
		fnSetModelIndex( reinterpret_cast< CBaseViewModel* >( pWeapon ), iKnifeModelIndex );
		if( iItemDefinitionIndex != pConfig->_Models.iKnifeModel )
			bReturn = true;
		iItemDefinitionIndex = pConfig->_Models.iKnifeModel;

		if( pViewModel->m_nModelIndex( ) != iKnifeModelIndex )
			fnSetModelIndex( pViewModel, iKnifeModelIndex );
		return bReturn;
	}

	bool PX_API ModifyGloveModel( player_ptr_t pLocalPlayer )
	{
		constexpr auto fnUpdateGlove = [ ]( CBaseAttributableItem* pEntity, player_ptr_t pLocalPlayer, short sItemDefinitionIndex, int iModelIndex )
		{
			auto bReturn = false;
			const auto pItem = pEntity->m_Item( );
			const auto pViewModel = reinterpret_cast< CBaseViewModel* >( pEntity );

			pItem->m_iItemIDHigh( ) = -1;
			pItem->m_iItemDefinitionIndex( ) = sItemDefinitionIndex;
			pItem->m_iEntityQuality( ) = QUALITY_GLOVE;
			pItem->m_iAccountID( ) = pLocalPlayer->GetPlayerInformation( ).xuid_low;
			if ( pViewModel->m_nModelIndex( ) != iModelIndex )
				bReturn = true;

			pViewModel->m_nModelIndex( ) = iModelIndex;
			reinterpret_cast< void( __thiscall* )( void*, int ) >( ( *reinterpret_cast< void*** >( pEntity ) )[ 75 ] )( pEntity, iModelIndex );
			return bReturn;
		};

		if ( !pConfig->bModifyGloveModel )
		{
			DestroyWearables( pLocalPlayer );
			return false;
		}

		const auto hWearables = pLocalPlayer->m_hMyWearables( );
		if ( hWearables == nullptr )
			return false;

		const auto iModelIndex = GetModelIndex( pConfig->_Models.iGloveModel );
		const auto pGloveEntity = reinterpret_cast< CBaseAttributableItem* >( pEntityList->GetClientEntityFromHandle( *hWearables ) );
		if ( pGloveEntity != nullptr ) // already created glove
			return fnUpdateGlove( pGloveEntity, pLocalPlayer, pConfig->_Models.iGloveModel, iModelIndex );

		const auto pOldGlove = reinterpret_cast< CBaseAttributableItem* >( pEntityList->GetClientEntityFromHandle( _InventoryContext.hGlove ) );
		if ( pOldGlove != nullptr ) // recover old glove
		{
			*hWearables = pOldGlove;
			return fnUpdateGlove( pOldGlove, pLocalPlayer, pConfig->_Models.iGloveModel, iModelIndex );
		}

		for( auto pClass = pClientBase->GetAllClasses(  ); pClass != nullptr; pClass = pClass->m_pNext )
		{
			if ( pClass->m_ClassID != ClassID_CEconWearable )
				continue;

			const auto iModelEntry = pEntityList->GetHighestEntityIndex( ) + 1,
				iSerialNumber = GenerateRandomNumber( 0, 0x1000 );
			pClass->m_pCreateFn( iModelEntry, iSerialNumber );
			_InventoryContext.hGlove = *hWearables = CBaseHandle( iModelEntry | iSerialNumber << 16 );

			const auto pNewGlove = reinterpret_cast< CBaseCombatWeapon* >( pEntityList->GetClientEntityFromHandle( *hWearables ) );
			const auto pViewModel = reinterpret_cast< CBaseViewModel* >( pNewGlove );
			const auto pItem = pNewGlove->m_Item( );
			const auto pNetworkClient = pNewGlove->GetClientNetworkable( );
			auto vecPos = Vector( 10000.f, 10000.f, 1000.f );

			//pItem->m_iItemIDHigh( ) = -1;
			//pItem->m_iItemDefinitionIndex( ) = pConfig->_Models.iGloveModel;
			//pItem->m_iEntityQuality( ) = QUALITY_GLOVE;
			//pItem->m_iAccountID( ) = pLocalPlayer->GetPlayerInformation( ).xuid_low;
			//pViewModel->m_nModelIndex( ) = iModelIndex;
			//reinterpret_cast< void( __thiscall* )( void*, int ) >( ( *reinterpret_cast< void*** >( pNewGlove ) )[ 75 ] )( pViewModel, iModelIndex );

			fnUpdateGlove( pNewGlove, pLocalPlayer, pConfig->_Models.iGloveModel, iModelIndex );

			pNetworkClient->PreDataUpdate( 0 );
			pNewGlove->SetABSOrigin( vecPos );
			//pNewGlove->GetIndex( ) = -1;
			return true;
		}
		return false;
	}

	void PX_API DestroyWearables( player_ptr_t pLocalPlayer )
	{
		_InventoryContext.hGlove = nullptr;
		if ( pLocalPlayer == nullptr )
			return;

		const auto hWearables = pLocalPlayer->m_hMyWearables( );
		if ( hWearables == nullptr )
			return;

		const auto pGloveEntity = reinterpret_cast< CBaseAttributableItem* >( pEntityList->GetClientEntityFromHandle( *hWearables ) );
		if( pGloveEntity != nullptr )
		{
			const auto pNetworkable = pGloveEntity->GetClientNetworkable( );
			pNetworkable->SetDestroyedOnRecreateEntities( );
			pNetworkable->Release( );
			*hWearables = nullptr;
		}
	}

	void PX_API SetModelSequence( CRecvProxyData* pData, CBaseViewModel* pViewModel )
	{
		if ( pData == nullptr
			 || pViewModel == nullptr )
			return;

		const auto pOwner = pEntityList->GetClientEntityFromHandle( pViewModel->m_hOwner( ) );
		if ( pOwner == nullptr )
			return;

		auto& lSequence = pData->m_Value.m_Int;
		const auto sIndex = GetDefinitionIndex( pViewModel->m_nModelIndex( ) );

		switch( sIndex )
		{
			case ITEM_WEAPON_KNIFE_BUTTERFLY:
			{
				switch ( lSequence )
				{
					case SEQUENCE_DEFAULT_DRAW:
					{
						lSequence = GenerateRandomNumber( SEQUENCE_BUTTERFLY_DRAW, SEQUENCE_BUTTERFLY_DRAW2 );
					}
					break;

					case SEQUENCE_DEFAULT_LOOKAT01:
					{
						lSequence = GenerateRandomNumber( SEQUENCE_BUTTERFLY_LOOKAT01, SEQUENCE_BUTTERFLY_LOOKAT03 );
					}
					break;

					default:
					{
						lSequence++;
					}
				}
			}
			break;

			case ITEM_WEAPON_KNIFE_FALCHION:
			{
				switch( lSequence )
				{
					case SEQUENCE_DEFAULT_IDLE2:
					{
						lSequence = SEQUENCE_FALCHION_IDLE1;
					}
					break;

					case SEQUENCE_DEFAULT_HEAVY_MISS1:
					{
						lSequence = GenerateRandomNumber( SEQUENCE_FALCHION_HEAVY_MISS1, SEQUENCE_FALCHION_HEAVY_MISS1_NOFLIP );
					}
					break;

					case SEQUENCE_DEFAULT_LOOKAT01:
					{
						lSequence = GenerateRandomNumber( SEQUENCE_FALCHION_LOOKAT01, SEQUENCE_FALCHION_LOOKAT02 );
					}
					break;

					case SEQUENCE_DEFAULT_DRAW:
					case SEQUENCE_DEFAULT_IDLE1:
						break;

					default:
					{
						lSequence++;
					}
				}
			}
			break;

			case ITEM_WEAPON_KNIFE_SHADOW_DAGGERS:
			{
				switch( lSequence )
				{
					case SEQUENCE_DEFAULT_IDLE2:
					{
						lSequence = SEQUENCE_DAGGERS_IDLE1;
					}
					break;

					case SEQUENCE_DEFAULT_LIGHT_MISS1:
					case SEQUENCE_DEFAULT_LIGHT_MISS2:
					{
						lSequence = GenerateRandomNumber( SEQUENCE_DAGGERS_LIGHT_MISS1, SEQUENCE_DAGGERS_LIGHT_MISS5 );
					}
					break;

					case SEQUENCE_DEFAULT_HEAVY_MISS1:
					{
						lSequence = GenerateRandomNumber( SEQUENCE_DAGGERS_HEAVY_MISS1, SEQUENCE_DAGGERS_HEAVY_MISS2 );
					}
					break;

					case SEQUENCE_DEFAULT_HEAVY_HIT1:
					case SEQUENCE_DEFAULT_HEAVY_BACKSTAB:
					case SEQUENCE_DEFAULT_LOOKAT01:
					{
						lSequence += 3;
					}
					break;

					case SEQUENCE_DEFAULT_DRAW:
					case SEQUENCE_DEFAULT_IDLE1:
						break;

					default:
					{
						lSequence += 2;
					}
				}
			}
			break;

			case ITEM_WEAPON_KNIFE_SURVIVAL_BOWIE:
			{
				switch( lSequence )
				{
					case SEQUENCE_DEFAULT_DRAW:
					case SEQUENCE_DEFAULT_IDLE1:
						break;

					case SEQUENCE_DEFAULT_IDLE2:
					{
						lSequence = SEQUENCE_BOWIE_IDLE1;
					}
					break;

					default:
						lSequence--;
				}
			}
			break;

			case ITEM_WEAPON_KNIFE_URSUS:
			{
				switch( lSequence )
				{
					case SEQUENCE_DEFAULT_DRAW:
					{
						lSequence = GenerateRandomNumber( SEQUENCE_BUTTERFLY_DRAW, SEQUENCE_BUTTERFLY_DRAW2 );
					}
					break;

					case SEQUENCE_DEFAULT_LOOKAT01:
					{
						lSequence = GenerateRandomNumber( SEQUENCE_BUTTERFLY_LOOKAT01, SEQUENCE_BUTTERFLY_LOOKAT03 );
					}
					break;

					default:
					{
						lSequence++;
					}
				}
			}
			break;

			case ITEM_WEAPON_KNIFE_STILLETTO:
			{
				switch(lSequence )
				{
					case SEQUENCE_DEFAULT_LOOKAT01:
					{
						lSequence = GenerateRandomNumber( 12, 13 );
					}
					break;

					default:
						break;
				}
			}
			break;

			case ITEM_WEAPON_KNIFE_TALON:
			{
				switch(lSequence )
				{
					case SEQUENCE_DEFAULT_LOOKAT01:
					{
						lSequence = GenerateRandomNumber( 14, 15 );
					}
					break;

					default:
						break;
				}
			}
			break;

			default:
				break;
		}
	}
}
