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

	pWindowHeader->SetSize( { PixelsToInches( recLocation.w ), CWindowHeader::HEIGHT } );
	AddObject( pWindowHeader, { } );
}

void CWindow::CreateDrawables( )
{
	vecDrawables.emplace_back( new CDrawable( ) )->Rectangle( GetAbsoluteLocation( ), BACKGROUND_DARK );
}
