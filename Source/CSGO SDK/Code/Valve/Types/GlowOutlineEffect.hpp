#pragma once

#include "UtlVector.hpp"
#include "../Interfaces/IClientEntity.hpp"

class GlowObjectDefinition_t
{
public:
	GlowObjectDefinition_t( )
	{
		memset( this, 0, sizeof( *this ) );
	}

	class IClientEntity *m_pEntity;    //0x0000
	union
	{
		Vector m_vGlowColor;           //0x0004
		struct
		{
			float m_flRed;           //0x0004
			float m_flGreen;         //0x0008
			float m_flBlue;          //0x000C
		};
	};

	float m_flAlpha;                 //0x0010
	uint8_t pad_0014[ 8 ];               //0x0014
	float m_flFullBloomAmount;       //0x001C
	uint8_t pad_0020[ 4 ];			   //0x0020
	bool m_bRenderWhenOccluded;     //0x0024
	bool m_bRenderWhenUnoccluded;   //0x0025
	bool m_bFullBloomRender;        //0x0026
	uint8_t pad_0027[ 5 ];               //0x0027
	int m_nGlowStyle;              //0x002C
	int m_nSplitScreenSlot;        //0x0030
	int m_nNextFreeSlot;           //0x0034

	bool IsUnused( ) const
	{
		return m_nNextFreeSlot != ENTRY_IN_USE;
	}

	static constexpr int END_OF_FREE_LIST = -1;
	static constexpr int ENTRY_IN_USE = -2;
}; //Size: 0x0038 (56)

class CGlowObjectManager
{
public:

	int RegisterGlowObject( IClientEntity *pEntity, int nSplitScreenSlot )
	{
		int nIndex;
		if ( m_nFirstFreeSlot == GlowObjectDefinition_t::END_OF_FREE_LIST )
			nIndex = m_GlowObjectDefinitions.AddToTail( );
		else
		{
			nIndex = m_nFirstFreeSlot;
			m_nFirstFreeSlot = m_GlowObjectDefinitions[ nIndex ].m_nNextFreeSlot;
		}

		m_GlowObjectDefinitions[ nIndex ].m_pEntity = pEntity;
		m_GlowObjectDefinitions[ nIndex ].m_nSplitScreenSlot = nSplitScreenSlot;
		m_GlowObjectDefinitions[ nIndex ].m_nNextFreeSlot = GlowObjectDefinition_t::ENTRY_IN_USE;

		return nIndex;
	}

	void UnregisterGlowObject( int nGlowObjectHandle )
	{
		m_GlowObjectDefinitions[ nGlowObjectHandle ].m_nNextFreeSlot = m_nFirstFreeSlot;
		m_GlowObjectDefinitions[ nGlowObjectHandle ].m_pEntity = nullptr;
		m_nFirstFreeSlot = nGlowObjectHandle;
	}

	void SetEntity( int nGlowObjectHandle, IClientEntity *pEntity )
	{
		m_GlowObjectDefinitions[ nGlowObjectHandle ].m_pEntity = pEntity;
	}

	void SetColor( int nGlowObjectHandle, const Vector &vGlowColor )
	{
		m_GlowObjectDefinitions[ nGlowObjectHandle ].m_vGlowColor = vGlowColor;
	}

	void SetAlpha( int nGlowObjectHandle, float flAlpha )
	{
		m_GlowObjectDefinitions[ nGlowObjectHandle ].m_flAlpha = flAlpha;
	}

	void SetRenderFlags( int nGlowObjectHandle, bool bRenderWhenOccluded, bool bRenderWhenUnoccluded )
	{
		m_GlowObjectDefinitions[ nGlowObjectHandle ].m_bRenderWhenOccluded = bRenderWhenOccluded;
		m_GlowObjectDefinitions[ nGlowObjectHandle ].m_bRenderWhenUnoccluded = bRenderWhenUnoccluded;
	}

	bool IsRenderingWhenOccluded( int nGlowObjectHandle ) const
	{
		return m_GlowObjectDefinitions[ nGlowObjectHandle ].m_bRenderWhenOccluded;
	}

	bool IsRenderingWhenUnoccluded( int nGlowObjectHandle ) const
	{
		return m_GlowObjectDefinitions[ nGlowObjectHandle ].m_bRenderWhenUnoccluded;
	}

	bool HasGlowEffect( IClientEntity *pEntity ) const
	{
		for ( auto i = 0; i < m_GlowObjectDefinitions.Count( ); i++ )
			if ( !m_GlowObjectDefinitions[ i ].IsUnused( ) && m_GlowObjectDefinitions[ i ].m_pEntity == pEntity )
				return true;

		return false;
	}

	CUtlVector< GlowObjectDefinition_t > m_GlowObjectDefinitions; //0x0000
	int m_nFirstFreeSlot;                                       //0x000C
};
