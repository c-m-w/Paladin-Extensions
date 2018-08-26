/// Glow.cpp

#include "../../PX CSGO.hpp"

using namespace PX::Information;
using namespace PX::Tools;
using namespace Pointers;

namespace PX::Features::Awareness
{
	void PX_API GlowEntities( )
	{
		const auto pLocalPlayer = GetLocalPlayer( );
		if ( nullptr == pLocalPlayer )
			return;

		GlowObjectDefinition_t* pObject;
		for( auto i = 0; i < pGlowObjectManager->m_GlowObjectDefinitions.Count( ) 
			 && nullptr != ( pObject = &pGlowObjectManager->m_GlowObjectDefinitions[ i ] ); i++ )
		{
			if ( pObject->IsUnused( ) )
				continue;
		
			const auto pEntity = reinterpret_cast< CBasePlayer* >( pObject->m_pEntity );
			if ( nullptr == pEntity || !pEntity->IsPlayer( ) || !pEntity->IsAlive( ) )
				continue;

			pObject->m_flRed = 1.f;
			pObject->m_flAlpha = 1.f;
			pObject->m_bRenderWhenOccluded = true;
			pObject->m_bRenderWhenUnoccluded = false;
			pObject->m_nGlowStyle = 0;
			pObject->m_bFullBloomRender = false;
			pObject->m_flFullBloomAmount = 1.f;
		}
	}
}
