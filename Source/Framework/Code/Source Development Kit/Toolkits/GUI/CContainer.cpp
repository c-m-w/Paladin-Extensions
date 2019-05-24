/// CContainer.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#include "../../../Framework.hpp"

CContainer::CContainer( const rectangle_t &recLocation ) :
	IInteractable( recLocation )
{ }

void CContainer::AddObject( IInteractable *pObject, const vector2_t& vecRelative )
{
	vecObjects.emplace_back( pObject );
	pObject->SetLocation( vecRelative );
	pObject->PreCreateDrawables( );
}

void CContainer::Draw( )
{
	for ( auto& pObject : vecObjects )
		pObject->Draw( );
}
