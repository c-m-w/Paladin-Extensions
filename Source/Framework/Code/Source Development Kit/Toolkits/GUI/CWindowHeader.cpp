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
	const auto dTop = recLocation.y + recLocation.h - UNDERLINE_HEIGHT / 2.0;

	pBackground->Rectangle( recLocation, BACKGROUND_DARK );
	pLine->Line( { recLocation.x, dTop }, { recLocation.x + recLocation.w, dTop }, UNDERLINE_HEIGHT, OUTLINE_LIGHT );
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

		pIcon->SetSize( { ICON_SIZE, ICON_SIZE } );
		pRow->AddWidget( pIcon );
	}
}
