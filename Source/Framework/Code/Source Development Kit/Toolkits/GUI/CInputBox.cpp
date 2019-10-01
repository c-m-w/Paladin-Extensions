/// CInputBox.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#include "../../../Framework.hpp"

void CInputBox::CreateDrawables( )
{
	const auto recLocation = GetAbsoluteLocation( );
	const auto pFill = vecDrawables.emplace_back( new CDrawable( ) );
	const auto pOutline = vecDrawables.emplace_back( new CDrawable( ) );

	pFill->RoundedRectangle( recLocation, GetCurrentColor( COLOR_INDEX_SECONDARY ), ROUNDING );
	pOutline->SetDrawingType( D3D11_PRIMITIVE_TOPOLOGY_LINELIST );
	pOutline->RoundedRectangle( recLocation, GetCurrentColor( COLOR_INDEX_TERTIARY ), ROUNDING );

	if ( !strBuffer.empty( ) )
		vecDrawables.emplace_back( new CDrawable( ) )->Rectangle( recLocation, 0xFFFFFFFF ), vecDrawables.back( )->SetTexture( _FontManager.CreateBitmap( &strBuffer[ 0 ], FONT, FONT_WEIGHT, false, InchesToPixels( TEXT_HEIGHT ) ), GetCurrentColor( COLOR_INDEX_PRIMARY ) );
}

CInputBox::CInputBox( ) :
	IWidget( WIDGET_BUTTON, CURSOR_IBEAM )
{ 
	SetColor( COLOR_INDEX_PRIMARY, STATE_DORMANT, TEXT_DARK );
	SetColor( COLOR_INDEX_PRIMARY, STATE_ACTIVATED, TEXT_NORMAL );
	SetColor( COLOR_INDEX_PRIMARY, STATE_HOVERING, TEXT_NORMAL );
	SetColor( COLOR_INDEX_PRIMARY, STATE_CLICKING, TEXT_NORMAL );
	SetColor( COLOR_INDEX_SECONDARY, STATE_DORMANT, BACKGROUND_DARK );
	SetColor( COLOR_INDEX_SECONDARY, STATE_ACTIVATED, BACKGROUND_DEFAULT );
	SetColor( COLOR_INDEX_SECONDARY, STATE_HOVERING, BACKGROUND_DEFAULT );
	SetColor( COLOR_INDEX_SECONDARY, STATE_CLICKING, BACKGROUND_DEFAULT );
	SetColor( COLOR_INDEX_TERTIARY, STATE_DORMANT, OUTLINE_DARK );
	SetColor( COLOR_INDEX_TERTIARY, STATE_ACTIVATED, OUTLINE_LIGHT );
	SetColor( COLOR_INDEX_TERTIARY, STATE_HOVERING, OUTLINE_LIGHT );
	SetColor( COLOR_INDEX_TERTIARY, STATE_CLICKING, OUTLINE_LIGHT );
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

	uInsertionPoint++;
	PreCreateDrawables( );
}

void CInputBox::SetMaxLength( std::size_t zNewLength )
{
	zMaxLength = zNewLength;
}

std::string CInputBox::GetBuffer( )
{
	return strBuffer;
}

void CInputBox::OnKeyTyped( char chCharacter )
{
	if ( _CurrentFilter & FILTER_LETTERS && FILTERS[ int( log( double( FILTER_LETTERS ) ) / log( 2.0 ) ) ]( chCharacter )
		 || _CurrentFilter & FILTER_NUMERIC && FILTERS[ int( log( double( FILTER_NUMERIC ) / log( 2.0 ) ) ) ]( chCharacter )
		 || _CurrentFilter & FILTER_SPECIAL_CHARACTERS && FILTERS[ int( log( double( FILTER_SPECIAL_CHARACTERS ) ) / log( 2.0 ) ) ]( chCharacter )
		 || _CurrentFilter & FILTER_SPECIAL_CHARACTERS && FILTERS[ int( log( double( FILTER_SPACE ) ) / log( 2.0 ) ) ]( chCharacter ) )
		NewCharacter( chCharacter );
}

void CInputBox::OnCopy( )
{
	MessageBox( nullptr, strBuffer.c_str( ), "menfuck", 0);
}

void CInputBox::OnPaste( )
{
	
}
