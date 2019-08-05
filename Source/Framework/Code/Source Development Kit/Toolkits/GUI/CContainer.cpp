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

void CContainer::UpdateScrollbarInformation( )
{
	if ( !bEnableScrollbar )
		return;

	const auto bInitialHorizontal = bHorizontal;
	const auto bInitialVertical = bVertical;

	vecBoundary = { };

	for ( auto& pInteractable : vecInteractables )
	{
		const auto recInteractableLocation = pInteractable->GetLocation( );
		const auto vecBoundaries = vector2_t( recInteractableLocation.x + recInteractableLocation.w, recInteractableLocation.y + recInteractableLocation.h ) - vecScrollAmount;

		vecBoundary.x = std::max( vecBoundaries.x, vecBoundary.x );
		vecBoundary.y = std::max( vecBoundaries.y, vecBoundary.y );
	}

	if ( vecBoundary.x > recLocation.w )
		bHorizontal = true;
	else
		vecScrollAmount.x = 0.0, bHorizontal = false;

	if ( vecBoundary.y > recLocation.h )
		bVertical = true;
	else
		vecScrollAmount.y = 0.0, bVertical = false;

	if ( bInitialHorizontal == bHorizontal
		 && bInitialVertical == bVertical )
		return;

	UpdateScrollbars( );
	ClampScroll( );
}

void CContainer::UpdateScrollbars( )
{
	RemoveObject( pHorizontal );
	RemoveObject( pVertical );

	delete pHorizontal;
	delete pVertical;

	pHorizontal = pVertical = nullptr;

	if ( bHorizontal )
		pHorizontal = new CScrollbar( ), pHorizontal->SetType( SCROLLBAR_HORIZONTAL ), pHorizontal->SetParent( this ), AddObject( pHorizontal, pHorizontal->CalculateRelativeLocation( ) );

	if ( bVertical )
		pVertical = new CScrollbar( ), pVertical->SetType( SCROLLBAR_VERTICAL ), pVertical->SetParent( this ), AddObject( pVertical, pVertical->CalculateRelativeLocation( ) );

	ClampScroll( );
}

void CContainer::ClampScroll( )
{
	if ( pHorizontal )
		vecScrollAmount.x = std::clamp( vecScrollAmount.x, 0.0, vecBoundary.x - recLocation.w + ( pVertical ? CScrollbar::WIDTH : 0.0 ) );

	if ( pVertical )
		vecScrollAmount.y = std::clamp( vecScrollAmount.y, 0.0, vecBoundary.y - recLocation.h + ( pHorizontal ? CScrollbar::WIDTH : 0.0 ) );
}

CContainer::CContainer( ):
	IInteractable( INTERACTABLE_CONTAINER )
{ }

void CContainer::SetStrictBounds( bool bNewStrictBounds )
{
	bStrictBounds = bNewStrictBounds;
}

bool CContainer::GetStrictBounds( )
{
	return bStrictBounds;
}

void CContainer::EnableScrollbars( )
{
	bEnableScrollbar = true;
	UpdateScrollbarInformation( );
}

void CContainer::DrawBackground( )
{
	bDrawBackground = true;
	bCreateDrawables = true;
}

double& CContainer::GetAlphaRatio( )
{
	return dbAlphaRatio;
}

vector2_t CContainer::GetScrollOffset( )
{
	return vecScrollAmount;
}

void CContainer::AddObject( IInteractable *pObject, const vector2_t& vecRelative )
{
	for ( auto& pInteractable : vecInteractables )
		if ( pInteractable == pObject )
			return;

	vecInteractables.emplace_back( pObject );
	pObject->SetParent( this );
	pObject->SetLocation( vecRelative );
	pObject->PreCreateDrawables( );
	UpdateScrollbarInformation( );
}

void CContainer::RemoveObject( IInteractable *pObject )
{
	for ( auto z = 0u; z < vecInteractables.size( ); z++ )
		if ( vecInteractables[ z ] == pObject )
			return vecInteractables.erase( vecInteractables.begin( ) + z ), pObject->SetLocation( { } );
}

const std::deque< IInteractable* >& CContainer::GetContainedInteractables( )
{
	return vecInteractables;
}

bool CContainer::OnScroll( int iScrollAmount )
{
	if ( !pVertical )
		return false;

	pVertical->Scroll( iScrollAmount );

	return true;
}
