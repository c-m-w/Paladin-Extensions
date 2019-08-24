/// CWindowHeader.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#include "../../../Framework.hpp"

void CWindowHeader::CreateDrawables( )
{
	const auto recLocation = GetAbsoluteLocation( );
	const auto pBackground = vecDrawables.emplace_back( new CDrawable( ) );
	const auto pLine = vecDrawables.emplace_back( new CDrawable( ) );
	const auto dTop = recLocation.y + recLocation.h;

	pBackground->Rectangle( recLocation, GetCurrentColor( COLOR_INDEX_PRIMARY ) );
	pLine->Line( { recLocation.x, dTop }, { recLocation.x + recLocation.w, dTop }, 0, GetCurrentColor( COLOR_INDEX_SECONDARY ) );
	pLine->SetDrawingType( D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP );
}

CWindowHeader::CWindowHeader( bool bUseIcon, const std::string& strTitle, const std::string& strSubtitle, const callback_t& _OnMinimize, const callback_t& _OnClose ) :
	bUseIcon( bUseIcon ), strTitle( strTitle ), strSubtitle( strSubtitle ), _OnMinimize( _OnMinimize ), _OnClose( _OnClose )
{
	SetColor( COLOR_INDEX_PRIMARY, STATE_DORMANT, BACKGROUND_DARK );
	SetColor( COLOR_INDEX_SECONDARY, STATE_DORMANT, OUTLINE_LIGHT );
}

CWindowHeader::~CWindowHeader( )
{
	if ( pMinimizeSizeAnimation )
	{
		delete pMinimizeSizeAnimation;
		pMinimizeSizeAnimation = nullptr;
	}

	if ( pCloseSizeAnimation )
	{
		delete pCloseSizeAnimation;
		pCloseSizeAnimation = nullptr;
	}
}

void CWindowHeader::Initialize( )
{
	const auto recLocation = GetAbsoluteLocation( );
	const auto pRow = new CHorizontalRow( );

	pRow->SetSize( recLocation.vecSize.ToInches( ) );
	AddObject( pRow, { } );
	if ( bUseIcon )
	{
		const auto pIcon = new CVectorGraphic( );

		pIcon->SetSize( { ICON_SIZE, pRow->GetSize( ).y } );
		pIcon->SetResourceName( ENC( "PX Logo.svg" ) );
		pRow->AddWidget( pIcon );
	}

	if ( !strTitle.empty( ) )
	{
		const auto pTitle = new CText( );

		pTitle->SetText( strTitle );
		pTitle->SetFont( FONT_ROBOTO );
		pTitle->SetWeight( WEIGHT_BOLD );
		pTitle->SetHeight( 1.0 / 6.0 );
		pTitle->SetAlignment( ALIGNMENT_LEFT, ALIGNMENT_CENTER );
		pTitle->SetSize( { pTitle->GetTextSize( ).ToInches( ).x, pRow->GetSize( ).y } );
		pTitle->SetPadding( { 0.05, 0.0 } );
		pTitle->SetColor( COLOR_INDEX_PRIMARY, STATE_DORMANT, TEXT_NORMAL );
		pRow->AddWidget( pTitle );
	}

	if ( !strSubtitle.empty( ) )
	{
		const auto pSubtitle = new CText( );

		pSubtitle->SetText( strSubtitle );
		pSubtitle->SetFont( FONT_ROBOTO );
		pSubtitle->SetHeight( 1.0 / 6.0 );
		pSubtitle->SetAlignment( ALIGNMENT_LEFT, ALIGNMENT_CENTER );
		pSubtitle->SetSize( { pSubtitle->GetTextSize( ).ToInches( ).x, pRow->GetSize( ).y } );
		pSubtitle->SetPadding( { 0.05, 0.0 } );
		pSubtitle->SetColor( COLOR_INDEX_PRIMARY, STATE_DORMANT, TEXT_DARK );
		pRow->AddWidget( pSubtitle );
	}

	pRow->SetAlignment( HALIGNMENT_RIGHT );

	if ( _OnMinimize )
	{
		const auto pMinimize = new CVectorGraphic( );
		
		pMinimizeSizeAnimation = new animated_value_t< vector2_t >( &pMinimize->GetRelativeSize( ) );
		pMinimizeSizeAnimation->SetStateValue( STATE_HOVERING, { 0.0625, 0.0625 } );
		pMinimizeSizeAnimation->SetStateValue( STATE_CLICKING, { 0.0625, 0.0625 } );
		pMinimize->SetSize( { 0.20833333333, 0.20833333333 } );
		pMinimize->SetResourceName( ENC( R"(Icons\Minus.svg)" ) );
		pMinimize->SetColor( COLOR_INDEX_PRIMARY, STATE_DORMANT, BLUE );
		pMinimize->SetColor( COLOR_INDEX_PRIMARY, STATE_INTERACTED, DARK_BLUE );
		pMinimize->SetPadding( { 0.05, pRow->GetSize( ).y / 2.0 - 0.10416666666 } );
		pMinimize->GetCallbacks( ).AddCallback( [ & ]( CKeyState _State )
		{
			if ( _State )
				_OnMinimize( );

			return true;
		}, VK_LBUTTON );
		pMinimize->AddAnimatedValue( pMinimizeSizeAnimation );
		pMinimize->SetCursorType( CURSOR_HAND );
		pRow->AddWidget( pMinimize );
	}

	if ( _OnClose )
	{

		const auto pClose = new CVectorGraphic( );

		pCloseSizeAnimation = new animated_value_t< vector2_t >( &pClose->GetRelativeSize( ) );
		pCloseSizeAnimation->SetStateValue( STATE_HOVERING, { 0.0625, 0.0625 } );
		pCloseSizeAnimation->SetStateValue( STATE_CLICKING, { 0.0625, 0.0625 } );
		pClose->SetSize( { 0.20833333333, 0.20833333333 } );
		pClose->SetResourceName( ENC( R"(Icons\Times.svg)" ) );
		pClose->SetColor( COLOR_INDEX_PRIMARY, STATE_DORMANT, BLUE );
		pClose->SetColor( COLOR_INDEX_PRIMARY, STATE_INTERACTED, DARK_BLUE );
		pClose->SetPadding( { 0.05, pRow->GetSize( ).y / 2.0 - 0.10416666666 } );
		pClose->GetCallbacks( ).AddCallback( [ & ]( CKeyState _State )
		{
			if ( _State )
				_OnClose( );

			return true;
		}, VK_LBUTTON );
		pClose->AddAnimatedValue( pCloseSizeAnimation );
		pClose->SetCursorType( CURSOR_HAND );
		pRow->AddWidget( pClose );
	}
}
