#include "../../dllmain.h"

void CInventory::SetKnifeModel( )
{
	//TODO: Make knife mdoel changed!
}

void CInventory::SetSkin( weapon_t wepWeapon, const DWORD dwWeaponBase )
{
	const int iIDHIGH = -1;
	DWORD dwOldIdHigh = iHighID.dwLocation;
	DWORD dwOldOwnerHigh = wepWeaponSkinBase.dwLocation;

	iHighID.dwLocation += dwWeaponBase;
	iHighID.xValue = iIDHIGH;

	wepWeaponSkinBase.dwLocation += dwWeaponBase;
	wepWeaponSkinBase.xValue = wepWeapon;

	mem.Set( iHighID );
	mem.Set( wepWeaponSkinBase );

	iHighID.dwLocation = dwOldIdHigh;
	wepWeaponSkinBase.dwLocation = dwOldOwnerHigh;

	if(GetAsyncKeyState(VK_F8)) ForceUpdate( );
}

void CInventory::ForceUpdate( )
{
	address_t< int > iForceUpdate = { 0, 0, 0x174 + eng.GetClientState( ), -1 };
	mem.Set( iForceUpdate );
}

void CInventory::Inventory( )
{
	weapon_t wepDeagle = { plrLocalPlayer.xValue._My_val.iAccount, plrLocalPlayer.xValue._My_val.iAccount,  EPaintKit::DRAGONLORE, 24, 0.01f, 100 };

	for ( int i { }; i <= 8; i++ )
	{
		DWORD dwWeaponBase = eng.GetEntityBase( ( eng.GetLocalPlayer( ).hMyWeapons[ i ] & 0xFFF ) - 1 );

		if ( dwWeaponBase )
		{
			DWORD dwOldItemdefinitionIndex = iItemDefinitionIndex.dwLocation;
			iItemDefinitionIndex.dwLocation += dwWeaponBase;
			mem.Get( iItemDefinitionIndex );
			iItemDefinitionIndex.dwLocation = dwOldItemdefinitionIndex;
		}

		switch ( EWeapon( iItemDefinitionIndex.xValue._My_val ) )
		{
			case EWeapon::DEAGLE:
				SetSkin( wepDeagle, dwWeaponBase );
				break;
			default:
				break;
		}
	}
}

CInventory inv;
