#pragma once

class CInventory
{
	void ForceUpdate( );
	void SetKnifeModel( );
	void SetSkin( weapon_t, DWORD );
public:
	void Inventory( );
};

extern CInventory inv;
