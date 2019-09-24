/// CEconItem.hpp

#pragma once

enum ItemQuality
{
	ITEM_QUALITY_DEFAULT,
	ITEM_QUALITY_GENUINE,
	ITEM_QUALITY_VINTAGE,
	ITEM_QUALITY_UNUSUAL,
	ITEM_QUALITY_SKIN,
	ITEM_QUALITY_COMMUNITY,
	ITEM_QUALITY_DEVELOPER,
	ITEM_QUALITY_SELFMADE,
	ITEM_QUALITY_CUSTOMIZED,
	ITEM_QUALITY_STRANGE,
	ITEM_QUALITY_COMPLETED,
	ITEM_QUALITY_UNK2,
	ITEM_QUALITY_TOURNAMENT
};

enum ItemRarity
{
	ITEM_RARITY_DEFAULT,
	ITEM_RARITY_COMMON,
	ITEM_RARITY_UNCOMMON,
	ITEM_RARITY_RARE,
	ITEM_RARITY_MYTHICAL,
	ITEM_RARITY_LEGENDARY,
	ITEM_RARITY_ANCIENT,
	ITEM_RARITY_IMMORTAL
};

class CEconItem
{
public:
	unsigned short *GetEconItemData( );
	void UpdateEquippedState( unsigned int state );
	uint32_t *GetInventory( );
	uint32_t *GetAccountID( );
	uint16_t *GetDefIndex( );
	uint64_t *GetItemID( );
	uint64_t *GetOriginalID( );
	unsigned char *GetFlags( );
	void SetQuality( ItemQuality quality );
	void SetRarity( ItemRarity rarity );
	void SetOrigin( int origin );
	void SetLevel( int level );
	void SetInUse( bool in_use );
	void SetCustomName( const char *name );
	void SetCustomDesc( const char *name );
	void SetPaintSeed( float seed );
	void SetPaintKit( float kit );
	void SetPaintWear( float wear );
	void SetStatTrak( int val );
	void AddSticker( int index, int kit, float wear, float scale, float rotation );

	template< typename TYPE > void SetAttributeValue( int index, TYPE val )
	{
		//todo
		//auto v15 = ( DWORD* )GameUtils::GetItemSchema( );
		//auto v16 = *( DWORD * )( v15[ 72 ] + 4 * index );
		//
		//static auto fnSetDynamicAttributeValue
		//		= reinterpret_cast< int(__thiscall*)( CEconItem *, DWORD, void * ) >(
		//			Pattern::FindSignature( "client.dll", "55 8B EC 83 E4 F8 83 EC 3C 53 8B 5D 08 56 57 6A 00" )
		//		);
		//
		//fnSetDynamicAttributeValue( this, v16, &val );
	}
};

inline uint32_t *CEconItem::GetAccountID( )
{
	return reinterpret_cast< uint32_t* >( this + 0x1C );
}

inline uint64_t *CEconItem::GetItemID( )
{
	return reinterpret_cast< uint64_t* >( this + 0x8 );
}

inline uint64_t *CEconItem::GetOriginalID( )
{
	return reinterpret_cast< uint64_t* >( this + 0x10 );
}

inline uint16_t *CEconItem::GetDefIndex( )
{
	return reinterpret_cast< uint16_t* >( this + 0x24 );
}

inline uint32_t *CEconItem::GetInventory( )
{
	return reinterpret_cast< uint32_t* >( this + 0x20 );
}

inline unsigned char *CEconItem::GetFlags( )
{
	return reinterpret_cast< unsigned char* >( this + 0x30 );
}

inline unsigned short *CEconItem::GetEconItemData( )
{
	return reinterpret_cast< unsigned short* >( this + 0x26 );
}

inline void CEconItem::UpdateEquippedState( unsigned int state )
{
	//todo
	//static auto fnUpdateEquippedState
	//		= reinterpret_cast< int(__thiscall*)( CEconItem *, unsigned int ) >(
	//			Pattern::FindSignature( "client.dll", "55 8B EC 8B 45 08 8B D0 C1 EA 10" )
	//		);
	//
	//fnUpdateEquippedState( this, state );
}

inline void CEconItem::AddSticker( int index, int kit, float wear, float scale, float rotation )
{
	SetAttributeValue< int >( 113 + 4 * index, kit );
	SetAttributeValue< float >( 114 + 4 * index, wear );
	SetAttributeValue< float >( 115 + 4 * index, scale );
	SetAttributeValue< float >( 116 + 4 * index, rotation );
}

inline void CEconItem::SetStatTrak( int val )
{
	SetAttributeValue< int >( 80, val );
	SetAttributeValue< int >( 81, 0 );
	SetQuality( ITEM_QUALITY_STRANGE );
}

inline void CEconItem::SetPaintKit( float kit )
{
	SetAttributeValue< float >( 6, kit );
}

inline void CEconItem::SetPaintSeed( float seed )
{
	SetAttributeValue< float >( 7, seed );
}

inline void CEconItem::SetPaintWear( float wear )
{
	SetAttributeValue< float >( 8, wear );
}

inline void CEconItem::SetQuality( ItemQuality quality )
{
	auto data = *GetEconItemData( );
	*GetEconItemData( ) = data ^ ( data ^ 32 * quality ) & 0x1E0;
}

inline void CEconItem::SetRarity( ItemRarity rarity )
{
	auto data = *GetEconItemData( );
	*GetEconItemData( ) = ( data ^ ( rarity << 11 ) ) & 0x7800 ^ data;
}

inline void CEconItem::SetOrigin( int origin )
{
	auto data = *GetEconItemData( );
	*GetEconItemData( ) = data ^ ( ( unsigned __int8 )data ^ ( unsigned __int8 )origin ) & 0x1F;
}

inline void CEconItem::SetLevel( int level )
{
	auto data = *GetEconItemData( );
	*GetEconItemData( ) = data ^ ( data ^ ( level << 9 ) ) & 0x600;
}

inline void CEconItem::SetInUse( bool in_use )
{
	auto data = *GetEconItemData( );
	*GetEconItemData( ) = data & 0x7FFF | ( in_use << 15 );
}

inline void CEconItem::SetCustomName( const char *name )
{
	//todo
	//static auto Address = Pattern::FindSignature( "client.dll", "E8 ? ? ? ? 8B 46 78 C1 E8 0A A8 01 74 13 8B 46 34" );
	//static auto fnSetCustomName
	//		= reinterpret_cast< CEconItem*(__thiscall*)( void *, const char * ) >(
	//			*reinterpret_cast< uintptr_t* >( Address + 1 ) + Address + 5
	//		);
	//
	//fnSetCustomName( this, name );
}

inline void CEconItem::SetCustomDesc( const char *name )
{
	//todo
	//static auto Address = Pattern::FindSignature( "client.dll", "E8 ? ? ? ? 33 DB 39 5E 3C 7E 5E" );
	//static auto fnSetCustomDesc
	//		= reinterpret_cast< CEconItem*(__thiscall*)( void *, const char * ) >(
	//			*reinterpret_cast< uintptr_t* >( Address + 1 ) + Address + 5
	//		);
	//
	//fnSetCustomDesc( this, name );
}
