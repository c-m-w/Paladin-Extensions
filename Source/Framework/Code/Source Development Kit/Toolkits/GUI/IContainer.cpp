/// IContainer.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#include "../../../Framework.hpp"

void IContainer::Draw( )
{
	for ( auto& pDrawable : vecDrawables )
		pDrawable->Draw( );

	for ( auto& pObject : vecInteractables )
		pObject->PreDraw( );
}

IContainer::IContainer( ):
	IInteractable( 1, INTERACTABLE_CONTAINER )
{ }

void IContainer::AddObject( IInteractable *pObject, const vector2_t& vecRelative )
{
	vecInteractables.emplace_back( pObject );
	pObject->SetLocation( vecRelative );
	pObject->PreCreateDrawables( );
	pObject->SetParent( this );
}

void IContainer::RemoveObject( IInteractable *pObject )
{
	for ( auto z = 0u; z < vecInteractables.size( ); z++ )
		if ( vecInteractables[ z ] == pObject )
			return vecInteractables.erase( vecInteractables.begin( ) + z ), void( );
}

const std::vector<IInteractable *> & IContainer::GetContainedInteractables( )
{
	return vecInteractables;
}
