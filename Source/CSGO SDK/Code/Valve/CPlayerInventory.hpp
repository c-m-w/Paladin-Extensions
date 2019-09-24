/// CPlayerInventory.hpp

#pragma once

class CPlayerInventory
{
public:
	void RemoveItem( uint64_t ID )
	{
		//todo
		//static auto fnRemoveItem
		//		= reinterpret_cast< int(__thiscall*)( void *, int64_t ) >(
		//			Pattern::FindSignature( "client.dll", "55 8B EC 83 E4 F8 56 57 FF 75 0C 8B F1" )
		//		);
		//
		//fnRemoveItem( this, ID );
	}

	void RemoveItem( CEconItem *item )
	{
		RemoveItem( *item->GetItemID( ) );
		GetBaseTypeCache( )->RemoveObject( item );
	}

	void ClearInventory( )
	{
		auto BaseTypeCache = this->GetBaseTypeCache( );
		auto items = BaseTypeCache->GetEconItems( );
		for ( auto item: items )
		{
			RemoveItem( *item->GetItemID( ) );
			BaseTypeCache->RemoveObject( item );
		}
	}

	CSharedObjectTypeCache *GetBaseTypeCache( )
	{
		//todo
		//static auto fnGCSDK_CGCClient_FindSOCache
		//		= reinterpret_cast< uintptr_t(__thiscall*)( uintptr_t, uint64_t, uint64_t, bool ) >(
		//			Pattern::FindSignature( "client.dll", "55 8B EC 83 E4 F8 83 EC 1C 0F 10 45 08" )
		//		);
		//
		//static auto fnGCSDK_CSharedObjectCache_CreateBaseTypeCache
		//		= reinterpret_cast< CSharedObjectTypeCache*(__thiscall*)( uintptr_t, int ) >(
		//			Pattern::FindSignature( "client.dll", "55 8B EC 51 53 56 8B D9 8D 45 08" )
		//		);
		////g_GCClientSystem = **reinterpret_cast<uintptr_t**>(Pattern::FindSignature("client.dll", "8B 0D ? ? ? ? 6A 00 83 EC 10") + 0x2);
		//auto SOCahce = fnGCSDK_CGCClient_FindSOCache( g_Valve.g_GCClientSystem + 0x70, *reinterpret_cast< uint64_t* >( this + 0x8 ), *reinterpret_cast< uint64_t* >( this + 0x10 ), 0 );
		//
		//return fnGCSDK_CSharedObjectCache_CreateBaseTypeCache( SOCahce, 1 );
	}

	uint32_t GetSteamID( )
	{
		return *reinterpret_cast< uint32_t* >( this + 0x8 );
	}

	CUtlVector< C_EconItemView* > *GetInventoryItems( )
	{
		return reinterpret_cast< CUtlVector< C_EconItemView* >* >( this + 0x2C );
	}

	bool AddEconItem( CEconItem *item, int a3, int a4, char a5 )
	{
		//todo
		//static auto fnAddEconItem
		//		= reinterpret_cast< C_EconItemView*(__thiscall*)( void *, CEconItem *, int, int, char ) >(
		//			Pattern::FindSignature( "client.dll", "55 8B EC 83 E4 F8 A1 ? ? ? ? 83 EC 14 53 56 57 8B F9 8B 08" )
		//		);
		//
		//GetBaseTypeCache( )->AddObject( item );
		//
		//auto ret = fnAddEconItem( this, item, a3, a4, a5 );
		//
		//if ( ret )
		//{
		//	auto i = GetInventoryItemByItemID( *item->GetItemID( ) );
		//
		//	*reinterpret_cast< bool* >( ( uintptr_t )i + 0xA1 ) = 1;
		//}
		//
		//return ret;
	}
};
