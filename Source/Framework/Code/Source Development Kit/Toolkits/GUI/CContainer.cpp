/// CContainer.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#include "../../../Framework.hpp"

void CContainer::CreateDrawables( )
{
	if ( bDrawBackground )
		vecDrawables.emplace_back( new CDrawable( ) )->Rectangle( GetAbsoluteLocation( ), GetCurrentColor( COLOR_INDEX_PRIMARY ) );
}

void CContainer::Draw( )
{
	for ( auto& pDrawable : vecDrawables )
		pDrawable->Draw( );

	for ( auto& pObject : vecInteractables )
		pObject->PreDraw( );
}

CContainer::CContainer( ):
	IInteractable( 1, INTERACTABLE_CONTAINER )
{ }

void CContainer::DrawBackground( )
{
	bDrawBackground = true;
}

void CContainer::AddObject( IInteractable *pObject, const vector2_t& vecRelative )
{
	vecInteractables.emplace_back( pObject );
	pObject->SetLocation( vecRelative );
	pObject->PreCreateDrawables( );
	pObject->SetParent( this );
}

void CContainer::RemoveObject( IInteractable *pObject )
{
	for ( auto z = 0u; z < vecInteractables.size( ); z++ )
		if ( vecInteractables[ z ] == pObject )
			return vecInteractables.erase( vecInteractables.begin( ) + z ), void( );
}

const std::vector<IInteractable *> & CContainer::GetContainedInteractables( )
{
	return vecInteractables;
}
