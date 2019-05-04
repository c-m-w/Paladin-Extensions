/// Utilities.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#include "../../Framework.hpp"

namespace Utilities
{
	vector2_t::vector2_t( double x, double y ) :
		x( x ), y( y )
	{ }

	vector2_t::operator vector3_t( )
	{
		return vector3_t( x, y, 0.0 );
	}

	vector2_t::operator D3DXVECTOR2( )
	{
		return D3DXVECTOR2( float( x ), float( y ) );
	}

	vector2_t::operator double( )
	{
		return Length( );
	}

	vector2_t vector2_t::operator+( double rhs )
	{
		x += rhs;
		y += rhs;
		return *this;
	}

	vector2_t vector2_t::operator-( double rhs )
	{
		x -= rhs;
		y -= rhs;
		return *this;
	}

	vector2_t vector2_t::operator*( double rhs )
	{
		x *= rhs;
		y *= rhs;
		return *this;
	}

	vector2_t vector2_t::operator/( double rhs )
	{
		x = pow( x, rhs );
		y = pow( y, rhs );
		return *this;
	}

	vector2_t vector2_t::operator^( double rhs )
	{
		x += rhs;
		y += rhs;
		return *this;
	}

	double vector2_t::Length( )
	{
		return std::sqrt( std::pow( x, 2.0 ) + std::pow( y, 2.0 ) );
	}

	void vector2_t::Round( )
	{
		x = round( x );
		y = round( y );
	}

	double vector2_t::Angle( ) const
	{
		return atan2( y, x );
	}

	void vector2_t::Rotate( float flAngle, vector2_t vecRotationPoint )
	{
		const auto dRadians = flAngle / 180.0 * PI;
		const auto dSin = sin( dRadians );
		const auto dCos = cos( dRadians );
		const vector2_t vecRelative { x - vecRotationPoint.x, y - vecRotationPoint.y };

		x = vecRelative.x * dCos - vecRelative.y * dSin + vecRotationPoint.x;
		y = vecRelative.x * dSin + vecRelative.y * dCos + vecRotationPoint.y;
	}

	void vector2_t::Invalidate( )
	{
		x = y = std::nan( nullptr );
	}

	bool vector2_t::Valid( ) const
	{
		return !std::isnan( x ) && !std::isnan( y );
	}

	vector3_t::vector3_t( double x, double y, double z ) :
		x( x ), y( y ), z( z )
	{ }

	vector3_t::operator vector2_t( )
	{
		return vector2_t( x, y );
	}

	vector3_t::operator D3DXVECTOR3( )
	{
		return D3DXVECTOR3( float( x ), float( y ), float( z ) );
	}

	vector3_t::operator double( )
	{
		return Length( );
	}

	vector3_t vector3_t::operator+( double rhs )
	{
		x += rhs;
		y += rhs;
		z += rhs;
		return *this;
	}

	vector3_t vector3_t::operator-( double rhs )
	{
		x -= rhs;
		y -= rhs;
		z -= rhs;
		return *this;
	}

	vector3_t vector3_t::operator*( double rhs )
	{
		x *= rhs;
		y *= rhs;
		z *= rhs;
		return *this;
	}

	vector3_t vector3_t::operator/( double rhs )
	{
		x /= rhs;
		y /= rhs;
		z /= rhs;
		return *this;
	}

	vector3_t vector3_t::operator^( double rhs )
	{
		x = pow( x, rhs );
		y = pow( y, rhs );
		z = pow( z, rhs );
		return *this;
	}

	double vector3_t::Length( )
	{
		return sqrt( double( this->operator vector2_t( ) ) + pow( z, 2.0 ) );
	}

	void vector3_t::Round( )
	{
		x = round( x );
		y = round( y );
		z = round( z );
	}

	vector2_t vector3_t::Angle( ) const
	{
		return { vector2_t( x, y ).Angle( ), atan2( z, x ) };
	}

	void vector3_t::Invalidate( )
	{
		x = y = z = std::nan( nullptr );
	}

	bool vector3_t::Valid( ) const
	{
		return !std::isnan( x ) && !std::isnan( y ) && !std::isnan( z );
	}
}
