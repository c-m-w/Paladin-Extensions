/// IDrawable.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#include "../../../Framework.hpp"

IDrawable::IDrawable( IDrawable *pParent, const rectangle_t& recLocation ):
	recLocation( recLocation )
{ }

IDrawable::IDrawable( const rectangle_t& recLocation ) :
	recLocation( recLocation )
{ }

rectangle_t IDrawable::GetLocation( )
{
	return recLocation;
}

vector2_t IDrawable::GetSize( )
{
	return recLocation.vecSize;
}

void IDrawable::PreCreateDrawables( )
{
	vecDrawables.clear( );
	CreateDrawables( );
}

void IDrawable::SetLocation( const vector2_t &vecNew )
{
	recLocation.vecLocation = vecNew;
}

void IDrawable::Draw( )
{
	for ( auto& pDrawable : vecDrawables )
		pDrawable->Draw( );
}
