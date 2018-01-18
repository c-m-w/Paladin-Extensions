#include "../../main.h"

void CInventory::SetKnifeModel( )
{
	//TODO: Make knife mdoel changed!
}

void CInventory::SetSkin( weapon_t wepWeapon, DWORD dwWeaponBase )
{
	DWORD dwOldIdHigh = iHighID.dwLocation;
	DWORD dwOldOwnerHigh = wepWeaponSkinBase.dwLocation;

	iHighID.dwLocation += dwWeaponBase;
	iHighID.xValue = -1;

	wepWeaponSkinBase.dwLocation += dwWeaponBase;
	wepWeaponSkinBase.xValue = wepWeapon;

	mem.Set( iHighID );
	mem.Set( wepWeaponSkinBase );

	iHighID.dwLocation = dwOldIdHigh;
	wepWeaponSkinBase.dwLocation = dwOldOwnerHigh;

	if ( GetAsyncKeyState( VK_F8 ) )
	{
		eng.ForceUpdate( );
	}
}

void CInventory::Inventory( )
{
	weapon_t wepDeagle = { plrLocalPlayer.xValue.iAccount, plrLocalPlayer.xValue.iAccount, DRAGONLORE, 24, 0.01f, 100 }; // TODO tranny, high = low why? iaccount twice

	for ( int i { }; i <= 8; i++ )
	{
		DWORD dwWeaponBase = eng.GetEntityBase( ( eng.GetLocalPlayer( ).hMyWeapons[ i ] & INDEX_ENTITY_MASK ) - 1 );

		if ( dwWeaponBase )
		{
			DWORD dwOldItemdefinitionIndex = iItemDefinitionIndex.dwLocation;
			iItemDefinitionIndex.dwLocation += dwWeaponBase;
			mem.Get( iItemDefinitionIndex );
			iItemDefinitionIndex.dwLocation = dwOldItemdefinitionIndex;
		}

		switch ( EWeapon( iItemDefinitionIndex.xValue ) )
		{
			case DEAGLE:
			{
				SetSkin( wepDeagle, dwWeaponBase );
				break;
			}
			default:
			{
				break;
			}
		}
	}
}

CInventory inv;
