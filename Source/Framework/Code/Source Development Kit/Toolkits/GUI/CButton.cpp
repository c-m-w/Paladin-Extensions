/// CButton.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#include "../../../Framework.hpp"

void CButton::SetDefaultSize( )
{
	SetSize( PixelsToInches( _TextBitmap.vecSize ) + TEXT_SPACING * 2.0 );
}

void CButton::CreateDrawables( )
{
	const auto recLocation = GetAbsoluteLocation( );
	const auto pFill = vecDrawables.emplace_back( new CDrawable( ) );
	const auto pText = vecDrawables.emplace_back( new CDrawable( ) );
	const auto vecLocation = recLocation.FindSpace( _TextBitmap.vecSize, ALIGNMENT_CENTER, ALIGNMENT_CENTER );

	pFill->RoundedRectangle( recLocation, GetCurrentColor( COLOR_INDEX_SECONDARY ), ROUNDING );
	pText->Rectangle( { vecLocation, _TextBitmap.vecSize }, 0xFFFFFFFF );
	pText->SetTexture( _TextBitmap, GetCurrentColor( COLOR_INDEX_PRIMARY ) );
}

void CButton::CreateTextBitmap( )
{
	_TextBitmap = _FontManager.CreateBitmap( &strText[ 0 ], FONT, FONT_WEIGHT, false, InchesToPixels( TEXT_HEIGHT ) );
}

CButton::CButton( ) :
	IWidget( WIDGET_BUTTON, CURSOR_HAND )
{
	CreateTextBitmap( );
	SetColor( COLOR_INDEX_PRIMARY, STATE_DORMANT, TEXT_NORMAL );
	SetColor( COLOR_INDEX_SECONDARY, STATE_DORMANT, LIGHT_BLUE );
	SetColor( COLOR_INDEX_SECONDARY, STATE_HOVERING, LIGHT_BLUE_ACTIVE );
	SetColor( COLOR_INDEX_SECONDARY, STATE_CLICKING, LIGHT_BLUE_ACTIVE );

	_SizeAnimation->SetStateValue( STATE_HOVERING, { 0.02083333333, 0.02083333333 } );
	_SizeAnimation->SetStateValue( STATE_CLICKING, { 0.02083333333, 0.02083333333 } );
	_LocationAnimation->SetStateValue( STATE_CLICKING, { 0.01041666666, 0.01041666666 } );
	_LocationAnimation->SetAnimationTime( LOCATION_ANIMATION_TIME );
	AddAnimatedValue( _SizeAnimation );
	AddAnimatedValue( _LocationAnimation );
}

void CButton::SetText( const std::string& strNewText )
{
	strText.clear( );
	bCreateDrawables = true;
	std::transform( strNewText.begin( ), strNewText.end( ), std::back_inserter( strText ), toupper );
	CreateTextBitmap( );
}
