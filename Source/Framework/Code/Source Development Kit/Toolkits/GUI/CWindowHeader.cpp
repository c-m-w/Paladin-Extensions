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

	pBackground->Rectangle( recLocation, BACKGROUND_DARK );
	pLine->Line( { recLocation.x, dTop }, { recLocation.x + recLocation.w, dTop }, 0, OUTLINE_LIGHT );
	pLine->SetDrawingType( D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP );
}

CWindowHeader::CWindowHeader( bool bUseIcon, const std::string& strTitle, const std::string& strSubtitle, const Utilities::callback_t& _OnClose ) :
	bUseIcon( bUseIcon ), strTitle( strTitle ), strSubtitle( strSubtitle ), _OnClose( _OnClose )
{ }

void CWindowHeader::Initialize( )
{
	const auto recLocation = GetAbsoluteLocation( );
	const auto pRow = new CHorizontalRow( );

	pRow->SetSize( recLocation.vecSize );
	AddObject( pRow, { } );
	if ( bUseIcon )
	{
		const auto pIcon = new CVectorGraphic( ENC( "PX Logo.svg" ) );

		pRow->AddWidget( pIcon, ICON_SIZE );
	}

	if ( !strTitle.empty( ) )
	{
		const auto pTitle = new CText( );

		pTitle->SetText( strTitle );
		pTitle->SetFont( FONT_ROBOTO_BOLD );
		pTitle->SetHeight( 16.0 );
		pTitle->SetAlignment( ALIGNMENT_LEFT, ALIGNMENT_CENTER );
		pTitle->SetPadding( { 5.0, 0.0 } );
		pTitle->SetColor( TEXT_NORMAL );
		pRow->AddWidget( pTitle, pTitle->GetTextSize( ).x );
	}

	if ( !strSubtitle.empty( ) )
	{
		const auto pSubtitle = new CText( );

		pSubtitle->SetText( strSubtitle );
		pSubtitle->SetFont( FONT_ROBOTO );
		pSubtitle->SetHeight( 16.0 );
		pSubtitle->SetAlignment( ALIGNMENT_LEFT, ALIGNMENT_CENTER );
		pSubtitle->SetPadding( { 5.0, 0.0 } );
		pSubtitle->SetColor( TEXT_DARK );
		pRow->AddWidget( pSubtitle, pSubtitle->GetTextSize( ).x );
	}
}
