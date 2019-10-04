/// CWindow.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#include "../../../Framework.hpp"

CWindow::CWindow( const rectangle_t &recLocation )
{
	SetLocation( recLocation.vecLocation );
	SetSize( recLocation.vecSize );
	SetColor( COLOR_INDEX_PRIMARY, STATE_DORMANT, BACKGROUND_DARK );
	SetStrictBounds( true );
	DrawBackground( );
}

void CWindow::ShowIcon( )
{
	bUseIcon = true;
}

void CWindow::SetTitle( const std::string &strNewTitle )
{
	strTitle = strNewTitle;
}

void CWindow::SetSubtitle( const std::string &strNewSubtitle )
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

void CWindow::Popup( CWindow *pNewPopup, bool bAbleToClosePopup )
{
	if ( pPopup )
		return;

	pPopup = pNewPopup;
	pPopupContainer = new CContainer( );
	pPopupContainer->DrawBackground( );
	pPopupContainer->SetSize( recLocation.vecSize );
	pPopupContainer->SetColor( COLOR_INDEX_PRIMARY, STATE_DORMANT, { 0, 0, 0, 100 } );
	pPopupContainer->GetAlphaRatio( ) = 0.0;

	pAlphaAnimation = new animated_value_t< double >( &pPopupContainer->GetAlphaRatio( ) );
	pAlphaAnimation->SetAnimationTime( POPUP_FADE_TIME );
	pAlphaAnimation->SetStateValue( STATE_DORMANT, 1.0 );
	pAlphaAnimation->AnimateValue( 1.0, 0.0 );

	pPopupContainer->AddAnimatedValue( pAlphaAnimation );
	AddObject( pPopupContainer, { } );
	pPopupContainer->AddObject( pPopup, { recLocation.w / 2.0 - pPopup->GetSize( ).x / 2.0, recLocation.h / 2.0 - pPopup->GetSize( ).y / 2.0 } );

	pPopup->GetRelativeLocation( ).y = -pPopup->GetLocation( ).y;
	pLocationAnimation = new animated_value_t< vector2_t >( &pPopup->GetRelativeLocation( ) );
	pLocationAnimation->SetAnimationTime( POPUP_MOVE_TIME );
	pLocationAnimation->SetStateValue( STATE_DORMANT, { } );
	pLocationAnimation->SetEaseType( EASE_BOUNCE );
	pPopup->AddAnimatedValue( pLocationAnimation );
	pLocationAnimation->AnimateValue( { }, pPopup->GetRelativeLocation( ) );

	if ( bAbleToClosePopup )
		pPopupContainer->GetCallbacks( ).AddCallback( [ & ]( CKeyState _State )
		{
			if ( _State )
				ClosePopup( );

			return true;
		}, VK_LBUTTON );
}

void CWindow::ClosePopup( )
{
	if ( !pPopup )
		return;

	RemoveObject( pPopupContainer );
	pPopupContainer->RemoveAnimatedValue( pAlphaAnimation );
	pPopup->RemoveAnimatedValue( pLocationAnimation );
	delete pAlphaAnimation;
	delete pLocationAnimation;
	_GUI.FreeInteractable( pPopupContainer );
	pPopupContainer = nullptr;
	pPopup = nullptr;
}

void CWindow::Initialize( )
{
	const auto pWindowHeader = new CWindowHeader( bUseIcon, strTitle, strSubtitle, _OnMinimize, _OnClose );

	pWindowHeader->SetSize( { recLocation.w, CWindowHeader::HEIGHT } );
	AddObject( pWindowHeader, { } );
}
