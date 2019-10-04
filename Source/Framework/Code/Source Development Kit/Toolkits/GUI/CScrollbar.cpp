/// Scrollbar.hpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#include "../../../Framework.hpp"

vector2_t CScrollbar::CalculateRelativeLocation( )
{
	const auto recParent = pParent->GetLocation( );

	return _Type == SCROLLBAR_VERTICAL ? vector2_t( recParent.w - WIDTH, 0.0 ) : vector2_t( 0.0, recParent.h - WIDTH );
}

double CScrollbar::GetBarSize( )
{
	if ( _Type == SCROLLBAR_VERTICAL )
		return pParent->recLocation.h / pParent->vecBoundary.y * recLocation.h;

	return pParent->recLocation.w / pParent->vecBoundary.x * recLocation.w;
}

vector2_t CScrollbar::GetBarLocation( )
{
	auto dbParentSize = 0.0, dbMax = 0.0, dbTotalSize = 0.0,
		 dbScrollAmount = 0.0;

	if ( _Type == SCROLLBAR_VERTICAL )
		dbParentSize = pParent->recLocation.h, dbMax = pParent->vecBoundary.y + ( pParent->bHorizontal ? WIDTH : 0.0 ), dbTotalSize = recLocation.h, dbScrollAmount = pParent->vecScrollAmount.y;
	else
		dbParentSize = pParent->recLocation.w, dbMax = pParent->vecBoundary.x + ( pParent->bVertical ? WIDTH : 0.0 ), dbTotalSize = recLocation.w, dbScrollAmount = pParent->vecScrollAmount.x;

	const auto dbMaxMovement = dbTotalSize - GetBarSize( );
	const auto dbMaxScrollAmount = dbMax - dbParentSize;
	const auto dbScrollRatio = dbScrollAmount / dbMaxScrollAmount;
	const auto dbLocation = dbScrollRatio * dbMaxMovement;

	if ( _Type == SCROLLBAR_VERTICAL )
		return { pParent->recLocation.w - WIDTH, dbLocation };

	return { dbLocation, pParent->recLocation.h - WIDTH };
}

rectangle_t CScrollbar::GetBarRectangle( )
{
	const auto dbSize = GetBarSize( );
	const auto vecLocation = GetBarLocation( );

	if ( _Type == SCROLLBAR_VERTICAL )
		return rectangle_t( vecLocation, { WIDTH, dbSize } ).ToPixels( );

	return rectangle_t( vecLocation, { dbSize, WIDTH } ).ToPixels( );
}

void CScrollbar::CreateDrawables( )
{
	const auto recLocation = GetAbsoluteLocation( );
	const auto pScrollbar = vecDrawables.emplace_back( new CDrawable( ) );
	const auto pRectangle = vecDrawables.emplace_back( new CDrawable( ) );

	pScrollbar->RoundedRectangle( GetBarRectangle( ), GetCurrentColor( COLOR_INDEX_PRIMARY ), 0.5 );
	pRectangle->Rectangle( recLocation, GetCurrentColor( COLOR_INDEX_SECONDARY ) );
}

void CScrollbar::SetDefaultSize( )
{
	const auto recParent = pParent->GetLocation( );

	if ( _Type == SCROLLBAR_VERTICAL )
		return SetSize( vector2_t( WIDTH, recParent.h - ( pParent->bHorizontal ? WIDTH : 0.0 ) ) );

	SetSize( vector2_t( recParent.w - ( pParent->bVertical ? WIDTH : 0.0 ), WIDTH ) );
}

CScrollbar::CScrollbar( ):
	IWidget( WIDGET_SCROLLBAR, CURSOR_HAND )
{
	SetColor( COLOR_INDEX_PRIMARY, STATE_DORMANT, TRANSLUCENT_BLUE );
	SetColor( COLOR_INDEX_PRIMARY, STATE_HOVERING, BLUE );
	SetColor( COLOR_INDEX_PRIMARY, STATE_CLICKING, BLUE );
	SetColor( COLOR_INDEX_SECONDARY, STATE_DORMANT, BACKGROUND_DIM );
	SetScrollImmune( true );
}

void CScrollbar::SetType( EScrollbarType _NewType )
{
	_Type = _NewType;

	if ( pParent )
		SetDefaultSize( );
}

void CScrollbar::Scroll( int iScrollAmount )
{
	const auto vecStart = pParent->vecScrollAmount;
	auto &dbScroll = _Type == SCROLLBAR_VERTICAL ? pParent->vecScrollAmount.y : pParent->vecScrollAmount.x;

	dbScroll += double( iScrollAmount ) / -SCROLL_DELTA * SCROLL_AMOUNT;
	pParent->ClampScroll( );

	if ( vecStart != pParent->vecScrollAmount )
		UpdateContainerContents( pParent );
}

void CScrollbar::IncreaseScroll( )
{
	const auto vecStart = pParent->vecScrollAmount;

	if ( _Type == SCROLLBAR_VERTICAL )
		pParent->vecScrollAmount.y += SCROLL_AMOUNT;
	else
		pParent->vecScrollAmount.x += SCROLL_AMOUNT;

	pParent->ClampScroll( );

	if ( vecStart != pParent->vecScrollAmount )
		UpdateContainerContents( pParent );
}

void CScrollbar::DecreaseScroll( )
{
	const auto vecStart = pParent->vecScrollAmount;

	if ( _Type == SCROLLBAR_VERTICAL )
		pParent->vecScrollAmount.y -= SCROLL_AMOUNT;
	else
		pParent->vecScrollAmount.x -= SCROLL_AMOUNT;

	pParent->ClampScroll( );

	if ( vecStart != pParent->vecScrollAmount )
		UpdateContainerContents( pParent );
}

void CScrollbar::AppendScrollAmount( const vector2_t &vecAmount )
{
	vecPendingScrollAmount += vecAmount;
}

void CScrollbar::NewFrame( )
{
	const auto dbAmount = _Type == SCROLLBAR_VERTICAL ? vecPendingScrollAmount.y : vecPendingScrollAmount.x;

	if ( dbAmount == 0.0 )
		return;

	Scroll( int( PixelsToInches( dbAmount ) * -SCROLL_DELTA / SCROLL_AMOUNT ) );
	vecPendingScrollAmount = { };
}

void CScrollbar::OnClick( CKeyState _State )
{
	if ( _State )
	{
		const auto vecMouse = _Input.GetMouseLocation( );
		const auto recBar = GetBarRectangle( );

		if ( recBar.LocationInRectangle( vecMouse ) )
			vecClickLocation = vecMouse;
		else
		{
			if ( _Type == SCROLLBAR_VERTICAL )
			{
				if ( vecMouse.y < recBar.y )
					DecreaseScroll( );
				else
					IncreaseScroll( );
			}
			else
			{
				if ( vecMouse.x < recBar.x )
					DecreaseScroll( );
				else
					IncreaseScroll( );
			}
		}
	}
}

void CScrollbar::OnMouseMove( const vector2_t &vecMouseLocation )
{
	const auto vecDifference = vecMouseLocation - vecClickLocation;

	AppendScrollAmount( vecDifference );

	vecClickLocation = vecMouseLocation;
}
