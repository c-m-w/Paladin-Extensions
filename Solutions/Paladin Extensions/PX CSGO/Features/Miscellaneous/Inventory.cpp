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
	settings_t::miscellaneous_t::inventory_t::team_t *pConfig = nullptr;

	struct
	{
		bool bForceUpdate = false, bClearHud = false;
		CBaseHandle hGlove { };
	} _InventoryContext;

	bool PX_API ModifyPaintKit( player_ptr_t pLocalPlayer, CBaseAttributableItem *pEntity );
	bool PX_API ModifyKnifeModel( player_ptr_t pLocalPlayer, CBaseCombatWeapon *pWeapon );
	bool PX_API ModifyGloveModel( player_ptr_t pLocalPlayer );
	void PX_API DestroyWearables( player_ptr_t pLocalPlayer );
	void PX_API ForceEntityUpdate( CBaseCombatWeapon *pEntity );

	void PX_API ModifyInventory( )
	{
		static int iOldWeapons[ 8 ] { };
		if ( !pEngineClient->IsInGame( ) )
			return;

		const auto pLocalPlayer = GetLocalPlayer( );
		if ( pLocalPlayer == nullptr
			|| !pLocalPlayer->IsAlive( ) )
			return DestroyWearables( pLocalPlayer );

		pConfig = pLocalPlayer->m_iTeamNum( ) == 3 ? &_Settings._Miscellaneous._Inventory._CounterTerrorist : &_Settings._Miscellaneous._Inventory._Terrorist;

		const auto hWeapons = pLocalPlayer->m_hMyWeapons( );
		const auto iXuidLow = pLocalPlayer->GetPlayerInformation( ).xuid_low;

		for ( auto i = 0; i < 8; i++ )
		{
			const auto hWeapon = hWeapons[ i ];
			if ( hWeapon != nullptr )
			{
				if ( hWeapon->IsKnife( ) )
					if ( ModifyKnifeModel( pLocalPlayer, hWeapon.Get( ) ) )
						_InventoryContext.bForceUpdate = true;

				const auto iEntityIndex = hWeapon->EntIndex( );
				if ( hWeapon->m_OriginalOwnerXuidLow( ) == iXuidLow
					&& !hWeapon->IsGrenade( )
					&& hWeapon->IsWeapon( )
					&& hWeapon->GetClientClass( )->m_ClassID != ClassID_CC4 )
				{
					ModifyPaintKit( pLocalPlayer, reinterpret_cast< CBaseAttributableItem* >( pEntityList->GetClientEntityFromHandle( hWeapon ) ) );
					if ( iEntityIndex != iOldWeapons[ i ] )
						_InventoryContext.bForceUpdate = _InventoryContext.bClearHud = true;
				}

				iOldWeapons[ i ] = iEntityIndex;
			}
			else
				iOldWeapons[ i ] = -1;
		}

		if ( _InventoryContext.hGlove != nullptr )
			if ( ModifyPaintKit( pLocalPlayer, reinterpret_cast< CBaseAttributableItem* >( pEntityList->GetClientEntityFromHandle( _InventoryContext.hGlove ) ) ) )
				_InventoryContext.bForceUpdate = _InventoryContext.bClearHud = true;

		if ( ModifyGloveModel( pLocalPlayer ) )
			_InventoryContext.bForceUpdate = _InventoryContext.bClearHud = true;

		if ( _InventoryContext.bForceUpdate )
		{
			pClientState->ForceFullUpdate( );
			_InventoryContext.bForceUpdate = false;
		}
		else if ( _InventoryContext.bClearHud
			&& !pLocalPlayer->IsDormant( ) )
		{
			const auto pHudWeaponSelection = FindHudElement< ptr_t >( PX_XOR( "CCSGO_HudWeaponSelection" ) );
			if ( pHudWeaponSelection != nullptr )
			{
				const auto pHudWeapons = reinterpret_cast< void* >( ptr_t( pHudWeaponSelection ) - 0xA0 );
				const auto pWeapons = reinterpret_cast< int* >( ptr_t( pHudWeapons ) + 0x80 );
				if ( pWeapons != nullptr
					&& *pWeapons > 0 )
				{
					static auto pClearHudWeaponIcon = reinterpret_cast< int( __thiscall*)( void *, int ) >( Modules::mClient.FindPattern( jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Signatures" ) ][ PX_XOR( "Clear Hud Weapon" ) ].get< str_t >( ) )
						+ jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Offsets" ) ][ PX_XOR( "Clear Hud Weapon" ) ].get< int >( ) );
					for ( auto i = 0; i < *pWeapons; i++ )
						i = pClearHudWeaponIcon( pHudWeapons, i );

					//*pWeapons = 0;
					_InventoryContext.bClearHud = false;
				}
			}
		}
	}

	void PX_API ForceUpdate( )
	{
		_InventoryContext.bForceUpdate = true;
		_InventoryContext.bClearHud = true;
	}

	bool PX_API ModifyPaintKit( player_ptr_t pLocalPlayer, CBaseAttributableItem *pEntity )
	{
		if ( !pConfig->bModifyInventory )
			return false;

		const auto pItem = pEntity->m_Item( );
		const auto iIndex = pItem->m_iItemDefinitionIndex( );
		const auto pCurrentConfig = &pConfig->_PaintKits[ iIndex ];
		const auto bIsKnife = pEntity->IsWeapon( ) && reinterpret_cast< CBaseCombatWeapon* >( pEntity )->IsKnife( );
		auto bReturn = false;

		pItem->m_iItemIDHigh( ) = -1;
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

		if ( bIsKnife )
			pItem->m_iEntityQuality( ) = QUALITY_KNIFE;

		char szName[ 161 ] { };
		if ( pCurrentConfig->bUseCustomName.Get( ) )
			for ( auto i = 0; i < strlen( pCurrentConfig->szName ); i++ )
				szName[ i ] = pCurrentConfig->szName[ i ];
		memcpy( &pEntity->m_szCustomName( ), szName, 161 );
		// = pCurrentConfig->bUseCustomName.Get( ) ? pCurrentConfig->szName : nullptr;
		pEntity->m_flFallbackWear( ) = pCurrentConfig->flWear;
		pEntity->m_nFallbackSeed( ) = pCurrentConfig->iSeed;
		pEntity->m_OriginalOwnerXuidHigh( ) = 0;
		pEntity->m_OriginalOwnerXuidLow( ) = 0;
		pItem->m_iAccountID( ) = pLocalPlayer->GetPlayerInformation( ).xuid_low;

		return bReturn;
	}

	bool PX_API ModifyKnifeModel( player_ptr_t pLocalPlayer, CBaseCombatWeapon *pWeapon )
	{
		constexpr auto fnSetModelIndex = [ ]( CBaseViewModel *vm, int i )
		{
			//	vm->m_nWorldModelIndex( ) = i + 1;
			vm->m_nModelIndex( ) = i;
			vm->m_nViewModelIndex( ) = i;
		};

		auto bReturn = false;

		if ( !pConfig->bModifyKnifeModel.Get( ) )
			return bReturn;

		const auto pItem = pWeapon->m_Item( );
		auto &iItemDefinitionIndex = pItem->m_iItemDefinitionIndex( );
		const auto iKnifeModelIndex = GetModelIndex( pConfig->_Models.iKnifeModel );
		if ( iKnifeModelIndex == 0 )
			return bReturn;

		pItem->m_iItemIDHigh( ) = -1;
		pItem->m_iEntityQuality( ) = QUALITY_KNIFE;
		fnSetModelIndex( reinterpret_cast< CBaseViewModel* >( pWeapon ), iKnifeModelIndex );
		if ( iItemDefinitionIndex != pConfig->_Models.iKnifeModel )
			bReturn = true;
		iItemDefinitionIndex = pConfig->_Models.iKnifeModel;

		const auto pViewModel = pLocalPlayer->m_hViewModel( );
		if ( pViewModel == nullptr
			|| pViewModel->m_hWeapon( ) != pWeapon )
			return bReturn;

		if ( pViewModel->m_nModelIndex( ) != iKnifeModelIndex )
			fnSetModelIndex( pViewModel, iKnifeModelIndex );
		return bReturn;
	}

	bool PX_API ModifyGloveModel( player_ptr_t pLocalPlayer )
	{
		constexpr auto fnUpdateGlove = [ ]( CBaseAttributableItem *pEntity, player_ptr_t pLocalPlayer, short sItemDefinitionIndex, int iModelIndex )
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
			reinterpret_cast< void( __thiscall*)( void *, int ) >( ( *reinterpret_cast< void*** >( pEntity ) )[ 75 ] )( pEntity, iModelIndex );
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

		for ( auto pClass = pClientBase->GetAllClasses( ); pClass != nullptr; pClass = pClass->m_pNext )
		{
			if ( pClass->m_ClassID != ClassID_CEconWearable )
				continue;

			const auto iModelEntry = pEntityList->GetHighestEntityIndex( ) + 1,
					   iSerialNumber = GenerateRandomNumber( 0, 0x1000 );
			pClass->m_pCreateFn( iModelEntry, iSerialNumber );
			_InventoryContext.hGlove = *hWearables = CBaseHandle( iModelEntry | iSerialNumber << 16 );

			const auto pNewGlove = reinterpret_cast< CBaseCombatWeapon* >( pEntityList->GetClientEntityFromHandle( *hWearables ) );
			const auto pNetworkClient = pNewGlove->GetClientNetworkable( );
			auto vecPos = Vector( 10000.f, 10000.f, 1000.f );

			fnUpdateGlove( pNewGlove, pLocalPlayer, pConfig->_Models.iGloveModel, iModelIndex );
			ModifyPaintKit( pLocalPlayer, pNewGlove );

			pNetworkClient->PreDataUpdate( 0 );
			pNewGlove->SetABSOrigin( vecPos );
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
		if ( pGloveEntity != nullptr )
		{
			const auto pNetworkable = pGloveEntity->GetClientNetworkable( );
			pNetworkable->SetDestroyedOnRecreateEntities( );
			pNetworkable->Release( );
			*hWearables = nullptr;
		}
	}

	void PX_API ForceEntityUpdate( CBaseCombatWeapon *pEntity )
	{
		const auto pItem = pEntity->m_Item( );
		std::cout << pEntity->GetCSWeaponData( )->szWeaponName << std::endl;

		pEntity->m_bCustomMaterialInitialized( ) = pEntity->m_nFallbackPaintKit( ) <= 0;
		pEntity->m_CustomMaterials( )->RemoveAll( );
		pItem->m_CustomMaterials( )->RemoveAll( );
		ClearRefCountedVector( pItem->m_VisualsDataProcessors( ) );

		pEntity->PostDataUpdate( 0 );
		pEntity->OnDataChanged( 0 );
	}

	void PX_API SetModelSequence( CRecvProxyData *pData, CBaseViewModel *pViewModel )
	{
		if ( pData == nullptr
			|| pViewModel == nullptr )
			return;

		const auto pOwner = pEntityList->GetClientEntityFromHandle( pViewModel->m_hOwner( ) );
		if ( pOwner == nullptr )
			return;

		auto &lSequence = pData->m_Value.m_Int;
		const auto sIndex = GetDefinitionIndex( pViewModel->m_nModelIndex( ) );

		switch ( sIndex )
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
				switch ( lSequence )
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
				switch ( lSequence )
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
				switch ( lSequence )
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

			case ITEM_WEAPON_KNIFE_STILLETTO:
			{
				switch ( lSequence )
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
				switch ( lSequence )
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
