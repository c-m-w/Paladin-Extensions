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

	vector2_t GetScreenSize( )
	{
		const auto hwDesktop = GetDesktopWindow( );
		RECT recDesktop { };

		GetWindowRect( hwDesktop, &recDesktop );
		return { float( recDesktop.right - recDesktop.left ), float( recDesktop.bottom - recDesktop.top ) };
	}

	unsigned __int64 GetMoment( )
	{




		return std::chrono::duration_cast< std::chrono::milliseconds >( std::chrono::system_clock::now( ).time_since_epoch( ) ).count( ); // todo @jeremy the other nanosecond thing doesnt work aaaaa

		timespec _Time { };
		timespec_get( &_Time, TIME_UTC );
		return _Time.tv_nsec / 100ui64;
	}

	void Pause( unsigned __int64 mmtPauseLength )
	{
		std::this_thread::sleep_for( std::chrono::milliseconds( mmtPauseLength ) );

		//static const auto NtDelayExecution = static_cast< SWindowsAPI::fnNtDelayExecution >( GetFunctionPointer( SWindowsAPI::NtDelayExecution ) );
		//if ( nullptr == NtDelayExecution ) // their system must be really messed up if it can't find delay execution
		//	return Sleep( DWORD( mmtPauseLength ) );
		//
		//const auto mmtEndTarget = GetMoment( ) + mmtPauseLength * 10000ull - 5000ull; // 10,000 is milliseconds to 100 nanoseconds conversion
		//
		//LARGE_INTEGER liDelayInterval;
		//liDelayInterval.QuadPart = -1ll;
		//
		//while ( GetMoment( ) < mmtEndTarget )
		//	NtDelayExecution( FALSE, &liDelayInterval );
	}
}
