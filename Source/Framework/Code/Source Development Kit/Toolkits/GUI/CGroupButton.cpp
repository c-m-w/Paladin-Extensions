/// CGroupButton.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#include "../../../Framework.hpp"

void CGroupButton::CreateDrawables( )
{
	const auto recLocation = GetAbsoluteLocation( );
	const auto pOutline = vecDrawables.emplace_back( new CDrawable( ) );
	const auto pFill = vecDrawables.emplace_back( new CDrawable( ) );
	const auto pText = vecDrawables.emplace_back( new CDrawable( ) );
	const auto vecLocation = recLocation.FindSpace( _TextBitmap.vecSize, ALIGNMENT_CENTER, ALIGNMENT_CENTER );
	bool bRounding[ ] = { _Type == BUTTON_LEFT, _Type == BUTTON_RIGHT, _Type == BUTTON_RIGHT, _Type == BUTTON_LEFT };

	pOutline->SetDrawingType( D3D11_PRIMITIVE_TOPOLOGY_LINELIST );
	pOutline->RoundedRectangle( recLocation, bRounding, GetCurrentColor( COLOR_INDEX_PRIMARY ), ROUNDING );
	pFill->RoundedRectangle( recLocation, bRounding, GetCurrentColor( COLOR_INDEX_SECONDARY ), ROUNDING );
	pText->Rectangle( { vecLocation, _TextBitmap.vecSize }, 0xFFFFFFFF );
	pText->SetTexture( _TextBitmap, GetCurrentColor( COLOR_INDEX_TERTIARY ) );
}

void CGroupButton::CreateTextBitmap( )
{
	_TextBitmap = _FontManager.CreateBitmap( &strText[ 0 ], FONT, WEIGHT_REGULAR, false, InchesToPixels( TEXT_HEIGHT ) );
}

CGroupButton::CGroupButton( ) :
	IWidget( WIDGET_GROUP_BUTTON, CURSOR_HAND )
{
	CreateTextBitmap( );
	SetColor( COLOR_INDEX_PRIMARY, STATE_DORMANT, VIVID_BLUE );
	SetColor( COLOR_INDEX_PRIMARY, STATE_HOVERING, 0 );
	SetColor( COLOR_INDEX_PRIMARY, STATE_CLICKING, 0 );
	SetColor( COLOR_INDEX_SECONDARY, STATE_DORMANT, 0 );
	SetColor( COLOR_INDEX_SECONDARY, STATE_HOVERING, VIVID_BLUE );
	SetColor( COLOR_INDEX_SECONDARY, STATE_CLICKING, TRANSLUCENT_BLUE );
	SetColor( COLOR_INDEX_TERTIARY, STATE_DORMANT, BUTTON_TEXT );

	_SizeAnimation->SetStateValue( STATE_HOVERING, { 0.0625, 0.0625 } );
	_SizeAnimation->SetStateValue( STATE_CLICKING, { 0.0625, 0.0625 } );
	AddAnimatedValue( _SizeAnimation );
}

void CGroupButton::SetText( const std::string& strNewText )
{
	strText = strNewText;
	CreateTextBitmap( );
}

void CGroupButton::SetType( EButtonType _NewType )
{
	_Type = _NewType;
}
