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

	vector2_t::vector2_t( POINT p ) :
		x( p.x ), y( p.y )
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

	bool vector2_t::operator==( const vector2_t &rhs ) const
	{
		return x == rhs.x && y == rhs.y;
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

	vector2_t vector2_t::ToPixels( ) const
	{
		return InchesToPixels( *this );
	}

	vector2_t vector2_t::ToInches( ) const
	{
		return PixelsToInches( *this );
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

	timer_t::timer_t( moment_t mmtLength ):
		mmtLength( mmtLength )
	{ }

	timer_t::timer_t( moment_t mmtLength, ETimerBehaviour _EndBehaviour ) :
		mmtLength( mmtLength ), _EndBehaviour( _EndBehaviour )
	{ }

	void timer_t::Stop( )
	{
		mmtPauseTime = GetMoment( );
		bPaused = true;
	}

	void timer_t::Start( )
	{
		if ( mmtStart == 0 )
			mmtStart = GetMoment( );
		else
			mmtStart += GetRatio( ) * mmtLength;

		bPaused = false;
	}

	void timer_t::Reset( )
	{
		mmtStart = 0;
		bPaused = true;
	}

	void timer_t::SetLength( moment_t mmtNewLength )
	{
		const auto dRatio = GetRatio( );
		mmtStart += ( 1.0 - dRatio ) * ( double( mmtNewLength ) - double( mmtLength ) );
		mmtLength = mmtNewLength;
	}

	void timer_t::SetRatio( double dRatio )
	{
		mmtStart = mmtStart + mmtLength * dRatio;
	}

	void timer_t::SetEndBehaviour( ETimerBehaviour _NewEndBehaviour )
	{
		_EndBehaviour = _NewEndBehaviour;
	}

	bool timer_t::Running( ) const
	{
		return !bPaused;
	}

	bool timer_t::Finished( ) const
	{
		return GetMoment( ) > mmtStart + mmtLength;
	}

	double timer_t::GetRatio( ) const
	{
		if ( mmtStart == 0 )
			return 0.0;

		const auto mmtCurrent = GetMoment( ) - mmtStart;

		if ( mmtCurrent <= mmtLength )
			return double( mmtCurrent ) / double( mmtLength );

		switch( _EndBehaviour )
		{
			case BEHAVIOUR_CLAMP:
			{
				return 1.0;
			}

			case BEHAVIOUR_REFLECT:
			{
				const auto iReflections = moment_t( mmtCurrent / mmtLength );
				const auto dbRatio = double( mmtCurrent % mmtLength ) / double( mmtLength );

				return iReflections % 2 == 1 ? 1.0 - dbRatio : dbRatio;
			}

			case BEHAVIOUR_RESTART:
			{
				return double( mmtCurrent % mmtLength ) / double( mmtLength );
			}

			default:
			{
				return 0.0;
			}
		}
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

	double InchesToPixels( double dInches )
	{
		return GetScreenDPI( ).x * dInches;
	}

	double PixelsToInches( double dPixels )
	{
		return dPixels / GetScreenDPI( ).x;
	}

	vector2_t InchesToPixels( const vector2_t& vecInches )
	{
		auto vecReturn = GetScreenDPI( ) * vecInches;
		vecReturn.Round( );
		return vecReturn;
	}

	vector2_t PixelsToInches( const vector2_t &vecPixels )
	{
		return vecPixels / GetScreenDPI( );
	}

	double EaseIn( EEaseType _Type, const timer_t &_Timer )
	{
		return EaseIn( _Type, _Timer.GetRatio( ) );
	}

	double EaseIn( EEaseType _Type, double dRatio )
	{
		dRatio = std::clamp( dRatio, 0.0, 1.0 );

		switch( _Type )
		{
			case EASE_SINE1:
			{
				return sin( PI / 2 * dRatio );
			}

			case EASE_SINE2:
			{
				return 0.5 * sin( PI * ( dRatio - 0.5 ) ) + 0.5;
			}

			case EASE_INVSINE1:
			{
				return asin( dRatio ) * 2.0 / PI;
			}

			case EASE_INVSINE2:
			{
				return asin( 2.0 * ( dRatio - 0.5 ) ) / PI + 0.5;
			}

			case EASE_RADICAL:
			{
				return pow( dRatio, 1.0 / 3.0 );
			}

			case EASE_BOUNCE:
			{
				return -abs( cos( PI * pow( 5.0, 1.06 * dRatio ) ) ) / pow( 75.0, dRatio ) + 1.0;
			}

			case EASE_ELASTIC:
			{
				return sin( 10 * PI * dRatio ) / ( 1.75 * pow( 75.0, dRatio ) ) + 1;
			}

			case EASE_OVER_BACK:
			{
				return pow( dRatio, 0.5 ) / ( 1.3 * pow( 3.0, dRatio - 1.0 ) ) + 1.0 - 1.0 / 1.3;
			}

			default:
			{
				return 0.0;
			}
		}
	}

	double EaseOut( EEaseType _Type, const timer_t &_Timer )
	{
		return EaseOut( _Type, _Timer.GetRatio( ) );
	}

	double EaseOut( EEaseType _Type, double dRatio )
	{
		return 1.0 - EaseIn( _Type, dRatio );
	}
}
