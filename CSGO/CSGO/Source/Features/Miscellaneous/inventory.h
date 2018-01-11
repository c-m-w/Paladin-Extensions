#pragma once

struct weapon_t
{
	int iOriginalOwnerXuidLow;
	int iOriginalOwnerXuidHigh;
	int iFallbackPaintKit; // 0x3168
	int iFallbackSeed; // 0x316c
	float flFallbackWear; // 0x3170
	int iFallbackStatTrak; // 0x3174
};

struct weaponentity_t
{
	DWORD dwWeaponBase;
	int iWeaponIndex;
	weapon_t wepWeapon;
};

class CInventory
{
	void ForceUpdate( );
	void SetKnifeModel( );
	void SetSkin( weaponentity_t );
public:
	void Inventory( );
};

extern CInventory inv;
