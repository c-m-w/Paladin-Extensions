/// Utilities.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#include "../../Framework.hpp"

namespace Utilities
{
	location_t::location_t( float _x, float _y ): x( _x ), y( _y )
	{ }

	location_t location_t::operator-( const location_t &rhs )
	{
		return location_t( x - rhs.x, y - rhs.y );
	}

	location_t location_t::operator+( const location_t &rhs )
	{
		return location_t( x + rhs.x, y + rhs.y );
	}

	bool location_t::operator!=( const location_t &rhs )
	{
		return x != rhs.x
				|| y != rhs.y;
	}

	void location_t::Rotate( float flAngle, location_t locRotationPoint )
	{
		const auto flRadians = D3DXToRadian( flAngle );
		const auto flSin = sin( flRadians );
		const auto flCos = cos( flRadians );
		const D3DXVECTOR2 vecRelative { float( x - locRotationPoint.x ), float( y - locRotationPoint.y ) };

		x = ( vecRelative.x * flCos ) - ( vecRelative.y * flSin ) + locRotationPoint.x;
		y = ( vecRelative.x * flSin ) + ( vecRelative.y * flCos ) + locRotationPoint.y;
	}

	void location_t::Invalidate( )
	{
		x = y = std::nanf( nullptr );
	}

	bool location_t::Valid( ) const
	{
		return !std::isnan( x ) && !std::isnan( y );
	}

	float location_t::Length( ) const
	{
		return powf( powf( x, 2.f ) + powf( y, 2.f ), 0.5f );
	}

	float location_t::Angle( ) const
	{
		return D3DXToDegree( atanf( y / x ) );
	}
}
