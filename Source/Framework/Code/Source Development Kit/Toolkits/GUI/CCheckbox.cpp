/// CCheckbox.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#include "../../../Framework.hpp"

void CCheckbox::Initialize( )
{
	pIcon = new CVectorGraphic( );
	pSubject = new CText( );

	pIcon->SetResourceName( pEnabled && *pEnabled ? strEnabledIcon : strDisabledIcon );
	pIcon->GetCallbacks( ).AddCallback( [ & ]( CKeyState _State )
	{
		if ( !_State )
			return false;

		if ( pEnabled != nullptr )
			*pEnabled = !*pEnabled, pIcon->SetColor( COLOR_INDEX_PRIMARY, STATE_DORMANT, *pEnabled ? DARK_BLUE : TEXT_DARK ), pIcon->SetColor( COLOR_INDEX_PRIMARY, STATE_HOVERING, *pEnabled ? BLUE : TEXT_NORMAL ), pIcon->SetColor( COLOR_INDEX_PRIMARY, STATE_CLICKING, *pEnabled ? BLUE : TEXT_NORMAL );

		return true;
	}, VK_LBUTTON );
	pIcon->SetCursorType( CURSOR_HAND );
	pIcon->SetSize( { recLocation.h, recLocation.h } );
	pIcon->SetColor( COLOR_INDEX_PRIMARY, STATE_DORMANT, pEnabled && *pEnabled ? DARK_BLUE : TEXT_DARK );
	pIcon->SetColor( COLOR_INDEX_PRIMARY, STATE_HOVERING, pEnabled && *pEnabled ? BLUE : TEXT_NORMAL );
	pIcon->SetColor( COLOR_INDEX_PRIMARY, STATE_CLICKING, pEnabled && *pEnabled ? BLUE : TEXT_NORMAL );

	_LocationAnimation = new animated_value_t< vector2_t >( &pIcon->GetRelativeLocation( ) );
	_LocationAnimation->SetStateValue( STATE_CLICKING, { 0.01041666666, 0.01041666666 } );
	_LocationAnimation->SetAnimationTime( 100ull );
	pIcon->AddAnimatedValue( _LocationAnimation );
	_SizeAnimation = new animated_value_t< vector2_t >( &pIcon->GetRelativeSize( ) );
	_SizeAnimation->SetStateValue( STATE_HOVERING, { 0.02083333333, 0.02083333333 } );
	_SizeAnimation->SetStateValue( STATE_CLICKING, { 0.02083333333, 0.02083333333 } );
	_SizeAnimation->SetAnimationTime( 100ull );
	pIcon->AddAnimatedValue( _SizeAnimation );

	pSubject->SetText( strSubject );
	pSubject->SetHeight( TEXT_HEIGHT );
	pSubject->SetFont( FONT );
	pSubject->SetSize( pSubject->GetTextSize( ) );
	pSubject->SetColor( COLOR_INDEX_PRIMARY, STATE_DORMANT, TEXT_DARK );
	AddObject( pSubject, { recLocation.h + SPACING, ( ICON_HEIGHT - TEXT_HEIGHT ) / 2.0 } );
	AddObject( pIcon, { } );
}

void CCheckbox::SetSubject( const std::string& strNewSubject )
{
	strSubject = strNewSubject;
	bCreateDrawables = true;

	if ( pSubject )
		pSubject->SetText( strSubject );
}

void CCheckbox::SetVariable( bool* pNewEnabled )
{
	pEnabled = pNewEnabled;
}

vector2_t CCheckbox::CalculateRequiredSpace( )
{
	return { ICON_HEIGHT + SPACING + PixelsToInches( _FontManager.CreateBitmap( &strSubject[ 0 ], FONT, WEIGHT_REGULAR, false, TEXT_HEIGHT ).vecSize.x ), ICON_HEIGHT };
}

