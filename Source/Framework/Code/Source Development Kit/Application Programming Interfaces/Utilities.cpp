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

	vector2_t::operator vector3_t( ) const
	{
		return vector3_t( x, y, 0.0 );
	}

	vector2_t::operator D3DXVECTOR2( ) const
	{
		return D3DXVECTOR2( float( x ), float( y ) );
	}

	vector2_t::operator double( ) const
	{
		return Length( );
	}

	vector2_t vector2_t::operator+( double rhs ) const
	{
		return { x + rhs, y + rhs };
	}

	vector2_t vector2_t::operator-( double rhs ) const
	{
		return { x - rhs, y - rhs };
	}

	vector2_t vector2_t::operator*( double rhs ) const
	{
		return { x * rhs, y * rhs };
	}

	vector2_t vector2_t::operator/( double rhs ) const
	{
		return { x / rhs, y / rhs };
	}

	vector2_t vector2_t::operator+=( double rhs )
	{
		x += rhs;
		y += rhs;
		return *this;
	}

	vector2_t vector2_t::operator-=( double rhs )
	{
		x -= rhs;
		y -= rhs;
		return *this;
	}

	vector2_t vector2_t::operator*=( double rhs )
	{
		x *= rhs;
		y *= rhs;
		return *this;
	}

	vector2_t vector2_t::operator/=( double rhs )
	{
		x /= rhs;
		y /= rhs;
		return *this;
	}

	vector2_t vector2_t::operator+( const vector2_t &rhs ) const
	{
		return { x + rhs.x, y + rhs.y };
	}

	vector2_t vector2_t::operator-( const vector2_t &rhs ) const
	{
		return { x - rhs.x, y - rhs.y };
	}

	vector2_t vector2_t::operator*( const vector2_t &rhs ) const
	{
		return { x * rhs.x, y * rhs.y };
	}

	vector2_t vector2_t::operator/( const vector2_t &rhs ) const
	{
		return { x / rhs.x, y / rhs.y };
	}

	vector2_t vector2_t::operator+=( const vector2_t &rhs )
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	vector2_t vector2_t::operator-=( const vector2_t &rhs )
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	vector2_t vector2_t::operator*=( const vector2_t &rhs )
	{
		x *= rhs.x;
		y *= rhs.y;
		return *this;
	}

	vector2_t vector2_t::operator/=( const vector2_t &rhs )
	{
		x /= rhs.x;
		y /= rhs.y;
		return *this;
	}

	std::vector< vector2_t > vector2_t::GetCirclePoints( double dbRadius, std::size_t zResolution, double dbStartAngle /*= 0.0*/, double dbRatio /*= 1.0*/ )
	{
		if ( zResolution <= 2 || dbRatio > 1.0 || dbRatio <= 0.0 )
			throw std::runtime_error( ENC( "this shouldnt happen" ) );

		const auto dbRotation = 360.0 * dbRatio / double( zResolution );
		auto dbTotal = 0.0;
		vector2_t vecStart { 0.0, -dbRadius };
		std::vector< vector2_t > vecReturn { };
		vecReturn.resize( zResolution + 1 );
		if ( dbStartAngle != 0.0 )
			vecStart.Rotate( dbStartAngle, { } );

		for ( auto z = 0u; z <= zResolution; z++ )
		{
			vecReturn[ z ] = vecStart;
			vecReturn[ z ].Rotate( dbTotal, { } );
			dbTotal += dbRotation;
		}

		return vecReturn;
	}

	double vector2_t::Length( ) const
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
		return atan2( y, x ) * 180.0 / PI;
	}

	void vector2_t::Rotate( double dAngle, const vector2_t& vecRotationPoint )
	{
		const auto dRadians = dAngle / 180.0 * PI;
		const auto dSin = std::sin( dRadians );
		const auto dCos = std::cos( dRadians );
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

	vector3_t::operator vector2_t( ) const
	{
		return vector2_t( x, y );
	}

	vector3_t::operator D3DXVECTOR3( ) const
	{
		return D3DXVECTOR3( float( x ), float( y ), float( z ) );
	}

	vector3_t::operator double( ) const
	{
		return Length( );
	}

	vector3_t vector3_t::operator+( double rhs ) const
	{
		return { x + rhs, y + rhs, z + rhs };
	}

	vector3_t vector3_t::operator-( double rhs ) const
	{
		return { x - rhs, y - rhs, z - rhs };
	}

	vector3_t vector3_t::operator*( double rhs ) const
	{
		return { x * rhs, y * rhs, z * rhs };
	}

	vector3_t vector3_t::operator/( double rhs ) const
	{
		return { x / rhs, y / rhs, z / rhs };
	}

	vector3_t vector3_t::operator+=( double rhs )
	{
		x += rhs;
		y += rhs;
		z += rhs;
		return *this;
	}

	vector3_t vector3_t::operator-=( double rhs )
	{
		x -= rhs;
		y -= rhs;
		z -= rhs;
		return *this;
	}

	vector3_t vector3_t::operator*=( double rhs )
	{
		x *= rhs;
		y *= rhs;
		z *= rhs;
		return *this;
	}

	vector3_t vector3_t::operator/=( double rhs )
	{
		x /= rhs;
		y /= rhs;
		z /= rhs;
		return *this;
	}

	vector3_t vector3_t::operator+( const vector3_t &rhs ) const
	{
		return { x + rhs.x, y + rhs.y, z + rhs.z };
	}

	vector3_t vector3_t::operator-( const vector3_t &rhs ) const
	{
		return { x - rhs.x, y - rhs.y, z - rhs.z };
	}

	vector3_t vector3_t::operator*( const vector3_t &rhs ) const
	{
		return { x * rhs.x, y * rhs.y, z * rhs.z };
	}

	vector3_t vector3_t::operator/( const vector3_t &rhs ) const
	{
		return { x / rhs.x, y / rhs.y, z / rhs.z };
	}

	vector3_t vector3_t::operator+=( const vector3_t &rhs )
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	vector3_t vector3_t::operator-=( const vector3_t &rhs )
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	vector3_t vector3_t::operator*=( const vector3_t &rhs )
	{
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;
		return *this;
	}

	vector3_t vector3_t::operator/=( const vector3_t &rhs )
	{
		x /= rhs.x;
		y /= rhs.y;
		z /= rhs.z;
		return *this;
	}

	double vector3_t::Length( ) const
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

	vector2_t GetScreenDPI( )
	{
		static vector2_t vecDPI { };

		if ( vecDPI.x == 0.0 || vecDPI.y == 0.0 )
		{
			ID2D1Factory* pFactory = nullptr;
			auto flDPIX = 0.f, flDPIY = 0.f;

			if ( !SUCCEEDED( D2D1CreateFactory( D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory ) ) )
				throw std::runtime_error( ENC( "Unable to get DPI." ) );

			pFactory->GetDesktopDpi( &flDPIX, &flDPIY );
			pFactory->Release( );

			vecDPI.x = double( flDPIX );
			vecDPI.y = double( flDPIY );
		}

		return vecDPI;
	}

	vector2_t InchesToPixels( const vector2_t& vecInches )
	{
		return GetScreenDPI( ) * vecInches;
	}
}
