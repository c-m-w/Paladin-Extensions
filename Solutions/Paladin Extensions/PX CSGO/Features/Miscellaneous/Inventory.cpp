/// Inventory.cpp

#include "PX Precompiled.hpp"
#include "../../PX CSGO.hpp"

using namespace PX;
using namespace Tools;

namespace PX::Features::Miscellaneous
{
	void PX_API SetModelSequence( CRecvProxyData* pData, CBaseViewModel* pViewModel )
	{
		if ( pData == nullptr
			 || pViewModel == nullptr )
			return;

		const auto pOwner = pEntityList->GetClientEntityFromHandle( pViewModel->m_hOwner( ) );
		if ( pOwner == nullptr )
			return;

		auto& lSequence = pData->m_Value.m_Int;
		auto& szModelName = pModelInfo->GetModel( pViewModel->m_nModelIndex( ) )->szName;

		if( 0 == strcmp( szModelName, PX_XOR( "models/weapons/v_knife_butterfly.mdl" ) ) )
		{
			
		}
		/*else if( 0 == strcmp( szModelName, )) )*/
	}
}
