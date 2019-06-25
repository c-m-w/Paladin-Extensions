/// Interface.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#include "../../../Framework.hpp"

IInteractable* CGUI::GetHoveredInteractable( IContainer* pContainer /*= nullptr*/ )
{
	if ( pContainer == nullptr )
	{
		if ( vecWindows.empty( ) )
			return nullptr;

		pContainer = vecWindows.front( );
	}

	for ( auto& pInteractable : pContainer->GetContainedInteractables( ) )
		if ( pInteractable->GetAbsoluteLocation( ).LocationInRectangle( _Input.GetMouseLocation( ) ) )
		{
			if ( pInteractable->IsInteractableType( INTERACTABLE_CONTAINER ) )
				return GetHoveredInteractable( reinterpret_cast< IContainer* >( pInteractable ) );

			return pInteractable;
		}

	if ( pContainer->GetAbsoluteLocation( ).LocationInRectangle( _Input.GetMouseLocation( ) ) )
		return pContainer;

	return nullptr;
}

void CGUI::FindHoveredInteractable( )
{
	const auto pNewHoveredInteractable = GetHoveredInteractable( );

	if ( pNewHoveredInteractable != pHoveredInteractable )
	{
		if ( pHoveredInteractable )
			pHoveredInteractable->RemoveState( STATE_HOVERING );

		if ( pNewHoveredInteractable != nullptr )
			pNewHoveredInteractable->AddState( STATE_HOVERING );
	}

	pHoveredInteractable = pNewHoveredInteractable;
}

void CGUI::ResetActiveInteractable( )
{
	pActiveInteractable->RemoveState( STATE_ACTIVATED );
	pActiveInteractable = nullptr;
}

void CGUI::DrawCursor( ECursorType _Cursor )
{
	// temp until svg
	constexpr char* CURSOR_PATHS[ 3 ]
	{
		R"(Cursor\Arrow.png)",
		R"(Cursor\Hand.png)",
		R"(Cursor\I Beam.png)"
	};
	constexpr auto CURSOR_SIZE = 50.0;
	const auto vecMouseLocation = _Input.GetMouseLocation( );
	const auto pCursor = new CDrawable( );

	pCursor->Rectangle( { vecMouseLocation.x - CURSOR_SIZE / 2.0, vecMouseLocation.y - CURSOR_SIZE / 2.0, CURSOR_SIZE, CURSOR_SIZE }, 0xFFFFFFFF );
	pCursor->SetTexture( CURSOR_PATHS[ _Cursor ] );
	pCursor->Draw( );
	pCursor->Destroy( );
	delete pCursor;
}

void CGUI::Setup( )
{
	if ( bAddedCallbacks )
		return;

	_Input.AddCallback( [ & ]( CKeyState _State )
	{
		if ( !bActive )
			return false;

		if ( _State )
		{
			if ( pActiveInteractable )
				pActiveInteractable->RemoveState( STATE_ACTIVATED | STATE_CLICKING );

			if ( pHoveredInteractable )
				pHoveredInteractable->AddState( STATE_ACTIVATED | STATE_CLICKING );

			pActiveInteractable = pHoveredInteractable;
		}
		else if( pActiveInteractable )
			pActiveInteractable->RemoveState( STATE_CLICKING );

		if ( pHoveredInteractable )
			pHoveredInteractable->OnClick( _State );

		return true;
	}, VK_LBUTTON );

	_Input.AddCallback( [ & ]( CKeyState( _State ) )
	{
		if ( !bActive )
			return false;

		if ( pHoveredInteractable )
			pHoveredInteractable->OnRightClick( _State );

		return true;
	}, VK_RBUTTON );

	_Input.AddCallback( [ & ]( key_t _Key, CKeyState _State )
	{
		if ( !bActive )
			return false;

		if ( pActiveInteractable )
			pActiveInteractable->OnKeyPress( _Key, _State );

		return true;
	} );

	_Input.AddCallback( [ & ]( key_t _Key )
	{
		if ( !bActive )
			return false;

		if ( pActiveInteractable )
			pActiveInteractable->OnKeyTyped( _Key );

		return true;
	} );

	_Input.AddCallback( [ & ]( short _ScrollAmount, int iMouseX, int iMouseY )
	{
		if ( !bActive )
			return false;

		if ( pHoveredInteractable )
			pHoveredInteractable->OnScroll( _ScrollAmount );

		return true;
	} );

	_Input.AddCallback( [ & ]( int iMouseX, int iMouseY )
	{
		if ( !bActive )
			return false;

		FindHoveredInteractable( );

		return true;

	} );

	bAddedCallbacks = true;
}

void CGUI::AddWindow( CWindow* pWindow )
{
	for ( auto& p : vecWindows )
		if ( p == pWindow )
			return;

	vecWindows.emplace_back( pWindow );
	pWindow->PreCreateDrawables( );
}

void CGUI::RemoveWindow( CWindow *pWindow )
{
	for ( auto u = 0u; u < vecWindows.size( ); u++ )
		if ( vecWindows[ u ] == pWindow )
		{
			vecWindows.erase( vecWindows.begin( ) + u );

			if ( vecWindows[ u ] == vecWindows.front( ) )
				ResetActiveInteractable( ), FindHoveredInteractable( );
		}
}

void CGUI::Draw( )
{
	SetCursor( nullptr );
	while ( ShowCursor( FALSE ) > 0 );

	for ( auto i = int( vecWindows.size( ) ) - 1; i >= 0; i-- )
		vecWindows[ i ]->PreDraw( );

	if ( !_Drawing.GetTarget( )->CursorOnWindow( ) )
		return;

	if ( pHoveredInteractable != nullptr )
		if ( pHoveredInteractable->IsInteractableType( INTERACTABLE_WIDGET ) )
			return DrawCursor( reinterpret_cast< IWidget* >( pHoveredInteractable )->GetCursorType( ) );

	DrawCursor( CURSOR_ARROW );
}

void CGUI::Deactivate( )
{
	bActive = false;
	while ( ShowCursor( TRUE ) <= 0 );
}

void CGUI::Activate( )
{
	bActive = true;
}

namespace Interface
{
	
}
