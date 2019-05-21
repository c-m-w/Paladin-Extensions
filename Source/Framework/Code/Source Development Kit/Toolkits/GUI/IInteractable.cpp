/// IInteractable.hpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#include "../../../Framework.hpp"

IInteractable::IInteractable( const rectangle_t &recLocation ) :
	IDrawable( recLocation )
{ }

void IInteractable::PreStateChange( )
{
	PreCreateDrawables( );
	OnStateChange( );
}

rectangle_t IInteractable::GetAbsoluteLocation( )
{
	if ( pParent != nullptr )
		return GetLocation( ) + pParent->GetLocation( );

	return GetLocation( );
}

vector2_t IInteractable::GetPadding( )
{
	return vecPadding;
}

double IInteractable::GetNetWidth( )
{
	return GetPadding( ).x + GetSize( ).x;
}

void IInteractable::OnStateChange( )
{ }

void IInteractable::OnClick( CKeyState _State )
{ }

void IInteractable::OnRightClick( CKeyState _State )
{ }

void IInteractable::OnKeyPress( key_t _Code, CKeyState _State )
{ }

void IInteractable::OnKeyTyped( char chCharacter, CKeyState _State )
{ }

void IInteractable::OnScroll( int iScrollAmount )
{ }
