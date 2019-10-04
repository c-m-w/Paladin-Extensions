/// C_EconItemView.h

#pragma once

class C_EconItemView
{
public:
	int32_t &m_bInitialized( ) const
	{
		static auto ptrOffset = Memory::FindOffset( ENC( "DT_BaseAttributableItem" ), "m_bInitialized" );
		return *reinterpret_cast< int32_t* >( uintptr_t( this ) + ptrOffset );
	};
	NETVAR_REFERENCE( int32_t, m_iItemDefinitionIndex, ENC("DT_BaseAttributableItem"), ENC("m_iItemDefinitionIndex") );
	NETVAR_REFERENCE( int32_t, m_iEntityLevel, ENC("DT_BaseAttributableItem"), ENC("m_iEntityLevel") );
	NETVAR_REFERENCE( int32_t, m_iAccountID, ENC("DT_BaseAttributableItem"), ENC("m_iAccountID") );
	NETVAR_REFERENCE( int32_t, m_iItemIDLow, ENC("DT_BaseAttributableItem"), ENC("m_iItemIDLow") );
	NETVAR_REFERENCE( int32_t, m_iItemIDHigh, ENC("DT_BaseAttributableItem"), ENC("m_iItemIDHigh") );
	NETVAR_REFERENCE( int32_t, m_iEntityQuality, ENC("DT_BaseAttributableItem"), ENC("m_iEntityQuality") );
};
