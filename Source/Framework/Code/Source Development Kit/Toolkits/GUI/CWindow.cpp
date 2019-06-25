/// CWindow.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#include "../../../Framework.hpp"

CWindow::CWindow( const rectangle_t& recLocation )
{
	SetLocation( recLocation.vecLocation );
	SetSize( recLocation.vecSize );
}

void CWindow::ShowIcon( )
{
	bUseIcon = true;
}

void CWindow::SetTitle( const std::string& strNewTitle )
{
	strTitle = strNewTitle;
}

void CWindow::SetSubtitle( const std::string& strNewSubtitle )
{
	strSubtitle = strNewSubtitle;
}

void CWindow::SetMinimizeCallback( callback_t _OnMinimizeCallback )
{
	_OnMinimize = _OnMinimizeCallback;
}

void CWindow::SetCloseCallback( callback_t _OnCloseCallback )
{
	_OnClose = _OnCloseCallback;
}

void CWindow::Initialize( )
{
	const auto recLocation = GetAbsoluteLocation( );
	const auto pWindowHeader = new CWindowHeader( bUseIcon, strTitle, strSubtitle, _OnMinimize, _OnClose );

	pWindowHeader->SetSize( { recLocation.w, CWindowHeader::HEIGHT } );
	AddObject( pWindowHeader, { } );
}

void CWindow::CreateDrawables( )
{
	color_t clrColor = BACKGROUND_DARK;
	vecDrawables.emplace_back( new CDrawable( ) );


	if ( _State & STATE_CLICKING )
		clrColor = BLUE;
	else if ( _State & STATE_ACTIVATED )
		clrColor = DARK_BLUE;
	else if ( _State & STATE_HOVERING )
		clrColor = BACKGROUND_LIGHT;

	vecDrawables.back( )->Rectangle( GetAbsoluteLocation( ), clrColor );
}
