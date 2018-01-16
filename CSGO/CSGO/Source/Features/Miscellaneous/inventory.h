#pragma once

class CInventory
{
	void SetKnifeModel( );
	void SetSkin( weapon_t, DWORD );
public:
	void Inventory( );
};

extern CInventory inv;
