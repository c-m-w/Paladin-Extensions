/// CWindow.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#include "../../../Framework.hpp"

CWindow::CWindow( const rectangle_t& recLocation )
{
	SetLocation( recLocation.vecLocation );
	SetSize( recLocation.vecSize );
	SetColor( COLOR_INDEX_PRIMARY, STATE_DORMANT, BACKGROUND_DARK );
	DrawBackground( );
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

void CWindow::Popup( CWindow *pNewPopup, bool bNewCanClosePopup )
{
	if ( pPopup )
		return;

	pPopup = pNewPopup;
	pPopupContainer = new CContainer( );
	pPopupContainer->DrawBackground( );
	pPopupContainer->SetSize( recLocation.vecSize );
	pPopupContainer->SetColor( COLOR_INDEX_PRIMARY, STATE_DORMANT, { 0, 0, 0, 100 } );
	AddObject( pPopupContainer, { } );
	pPopupContainer->AddObject( pPopup, { recLocation.w / 2.0 - pPopup->GetSize( ).x / 2.0, recLocation.h / 2.0 - pPopup->GetSize( ).y / 2.0 } );
	if ( ( bCanClosePopup = bNewCanClosePopup ) )
		pPopupContainer->GetCallbacks( ).AddCallback( [ & ]( CKeyState _State )
	{
		ClosePopup( );
		return true;
	}, VK_LBUTTON );
}

void CWindow::ClosePopup( )
{
	if ( !pPopup )
		return;

	RemoveObject( pPopupContainer );
	delete pPopupContainer;
}

void CWindow::Initialize( )
{
	const auto recLocation = GetAbsoluteLocation( );
	const auto pWindowHeader = new CWindowHeader( bUseIcon, strTitle, strSubtitle, _OnMinimize, _OnClose );

	pWindowHeader->SetSize( { PixelsToInches( recLocation.w ), CWindowHeader::HEIGHT } );
	AddObject( pWindowHeader, { } );
}
