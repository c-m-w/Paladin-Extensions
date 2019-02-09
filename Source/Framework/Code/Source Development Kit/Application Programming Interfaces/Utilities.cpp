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

	moment_t GetMoment( )
	{
		auto iFileTime = 0i64;
		GetSystemTimePreciseAsFileTime( reinterpret_cast< PFILETIME >( &iFileTime ) );
		return iFileTime - 116444736000000000ui64;
	}

	void Wait( moment_t mmtWaitLength /*= 0ui64*/ )
	{
		if ( mmtWaitLength == 0 )
			return;
		if ( mmtWaitLength == ULLONG_MAX )
			Sleep( ULLONG_MAX );

		HANDLE hTimer = nullptr;
		if ( ( hTimer = CreateWaitableTimer( nullptr, TRUE, nullptr ) ) == nullptr )
			return std::this_thread::sleep_for( std::chrono::nanoseconds( mmtWaitLength * 100 ) ); // todo log

		LARGE_INTEGER li;
		li.QuadPart = -__int64( mmtWaitLength );
		if ( SetWaitableTimer( hTimer, &li, 0, nullptr, nullptr, FALSE ) == 0 )
		{
			if ( CloseHandle( hTimer ) == 0 )
				return std::this_thread::sleep_for( std::chrono::nanoseconds( mmtWaitLength * 100 ) ); // todo log
			return std::this_thread::sleep_for( std::chrono::nanoseconds( mmtWaitLength * 100 ) ); // todo log
		}

		if ( WaitForSingleObject( hTimer, INFINITE ) != WAIT_TIMEOUT )
		{
			if ( CloseHandle( hTimer ) == 0 )
				return std::this_thread::sleep_for( std::chrono::nanoseconds( mmtWaitLength * 100 ) ); // todo log
			return std::this_thread::sleep_for( std::chrono::nanoseconds( mmtWaitLength * 100 ) );	 // todo log
		}

		if ( CloseHandle( hTimer ) == 0 )
			; // todo log
	}

	void Pause( moment_t mmtPauseLength /*= ULLONG_MAX*/ )
	{
		Sleep( mmtPauseLength / 10000 );
	}

	void OpenLink( const std::string &strLink )
	{
		ShellExecute( nullptr, XOR( "open" ), strLink.c_str( ), nullptr, nullptr, SW_SHOWNORMAL );
	}
}
