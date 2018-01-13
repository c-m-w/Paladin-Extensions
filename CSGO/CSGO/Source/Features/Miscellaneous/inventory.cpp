#include "../../dllmain.h"

void CInventory::SetKnifeModel( )
{
	//TODO: Make knife mdoel changed!
}

void CInventory::SetSkin( weaponentity_t wepWeapon )
{
	address_t< int > iHighID = { 0, 0, 0x2FA0 + wepWeapon.dwWeaponBase, -1 };
	address_t< weapon_t > wepWeaponSkinBase = { 0, 0, 0x3168 + wepWeapon.dwWeaponBase, wepWeapon.wepWeapon };
	printf( "%i\n", sizeof(EPaintKit) );
	mem.Set( iHighID );
	mem.Set( wepWeaponSkinBase );
}

void CInventory::ForceUpdate( )
{
	address_t< int > iForceUpdate = { 0, 0, 0x174 + eng.GetClientState( ), -1 };
	mem.Set( iForceUpdate );
}

void CInventory::Inventory( )
{
	weapon_t wepDeagle = { plrLocalPlayer.xValue._My_val.iAccount, plrLocalPlayer.xValue._My_val.iAccount,  EPaintKit::COBALTDISRUPTION, 24, 0.01f, -1 };
	weaponentity_t wepWeaponEntity { };
	address_t< int > iItemDefinitionIndex = { 0, 0, 0x2F88 };
	for ( int i = 0; i <= 8; i++ )
	{
		wepWeaponEntity.dwWeaponBase = eng.GetEntityBase( ( eng.GetLocalPlayer( ).hMyWeapons[ i ] & 0xFFF ) - 1 );
		DWORD dwOldItemDefinitionIndex = iItemDefinitionIndex.dwLocation;
		iItemDefinitionIndex.dwLocation += wepWeaponEntity.dwWeaponBase;
		mem.Get( iItemDefinitionIndex );
		wepWeaponEntity.iWeaponIndex = iItemDefinitionIndex.xValue._My_val;
		iItemDefinitionIndex.dwLocation = dwOldItemDefinitionIndex;

		switch ( EWeapon( wepWeaponEntity.iWeaponIndex ) )
		{
			case EWeapon::DEAGLE:
				wepWeaponEntity.wepWeapon = wepDeagle;
				SetSkin( wepWeaponEntity );
				break;
			default:
				break;
		}
	}
}

CInventory inv;
