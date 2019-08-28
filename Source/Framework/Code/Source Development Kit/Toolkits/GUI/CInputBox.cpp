/// CInputBox.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#include "../../../Framework.hpp"

void CInputBox::CreateDrawables( )
{}

CInputBox::CInputBox( ) :
	IWidget( WIDGET_BUTTON, CURSOR_IBEAM )
{ 
	SetColor( COLOR_INDEX_PRIMARY, STATE_DORMANT, TEXT_DARK );
	SetColor( COLOR_INDEX_PRIMARY, STATE_ACTIVATED, TEXT_NORMAL );
	SetColor( COLOR_INDEX_PRIMARY, STATE_HOVERING, TEXT_NORMAL );
	SetColor( COLOR_INDEX_PRIMARY, STATE_CLICKING, TEXT_NORMAL );
	SetColor( COLOR_INDEX_SECONDARY, STATE_DORMANT, BACKGROUND_DEFAULT );
	SetColor( COLOR_INDEX_SECONDARY, STATE_ACTIVATED, BACKGROUND_DEFAULT );
	SetColor( COLOR_INDEX_SECONDARY, STATE_HOVERING, BACKGROUND_DEFAULT );
	SetColor( COLOR_INDEX_SECONDARY, STATE_CLICKING, BACKGROUND_DEFAULT );
	SetColor( COLOR_INDEX_TERTIARY, STATE_DORMANT, BLUE );
}

void CInputBox::AddFilter( EFilter _NewFilter )
{
	*reinterpret_cast< unsigned* >( &_CurrentFilter ) |= _NewFilter;
}

void CInputBox::RemoveFilter( EFilter _FilterToRemove )
{
	*reinterpret_cast< unsigned* >( &_CurrentFilter ) &= ~_FilterToRemove;
}

void CInputBox::NewCharacter( char chInsertion )
{
	if ( strBuffer.length( ) >= zMaxLength )
		return;

	if ( _CurrentMode == MODE_INSERT )
		strBuffer.insert( strBuffer.begin( ) + uInsertionPoint, chInsertion );
	else
		strBuffer[ uInsertionPoint ] = chInsertion;
}

void CInputBox::SetMaxLength( std::size_t zNewLength )
{
	zMaxLength = zNewLength;
}

void CInputBox::OnKeyTyped( char chCharacter )
{
	if ( _CurrentFilter & FILTER_LETTERS && FILTERS[ int( log( double( FILTER_LETTERS ) ) / log( 2.0 ) ) ]( chCharacter )
		 || _CurrentFilter & FILTER_NUMERIC && FILTERS[ int( log( double( FILTER_NUMERIC ) / log( 2.0 ) ) ) ]( chCharacter )
		 || _CurrentFilter & FILTER_SPECIAL_CHARACTERS && FILTERS[ int( log( double( FILTER_SPECIAL_CHARACTERS ) ) / log( 2.0 ) ) ]( chCharacter )
		 || _CurrentFilter & FILTER_SPECIAL_CHARACTERS && FILTERS[ int( log( double( FILTER_SPACE ) ) / log( 2.0 ) ) ]( chCharacter ) )
		NewCharacter( chCharacter );
}
