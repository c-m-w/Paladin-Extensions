#include "dllmain.h"

HINSTANCE hInst = nullptr;
bool bExitState = false;
std::vector< std::thread > tThreads;

void Wait( unsigned int nSleepTime )
{
	std::this_thread::sleep_for( std::chrono::milliseconds( nSleepTime ) );
}

moment GetTime( )
{
	return std::chrono::duration_cast< std::chrono::milliseconds >( std::chrono::system_clock::now( ).time_since_epoch( ) ).count( );
}

bool angle_t::operator==( angle_t rhs )
{
	if ( pitch == rhs.pitch && yaw == rhs.yaw && roll == rhs.roll )
	{
		return true;
	}
	return false;
}

bool angle_t::operator!=( angle_t rhs )
{
	if ( *this == rhs )
	{
		return false;
	}
	return true;
}

angle_t angle_t::operator+( angle_t rhs )
{
	pitch += rhs.pitch;
	yaw += rhs.yaw;
	roll += rhs.roll;
	return *this;
}

angle_t angle_t::operator-( angle_t rhs )
{
	pitch -= rhs.pitch;
	yaw -= rhs.yaw;
	roll -= rhs.roll;
	return *this;
}

angle_t angle_t::operator*( float rhs )
{
	pitch *= rhs;
	yaw *= rhs;
	roll *= rhs;
	return *this;
}

angle_t angle_t::operator/( float rhs )
{
	pitch /= rhs;
	yaw /= rhs;
	roll /= rhs;
	return *this;
}

angle_t &angle_t::operator+=( angle_t rhs )
{
	*this = *this + rhs;
	return *this;
}

angle_t &angle_t::operator-=( angle_t rhs )
{
	*this = *this - rhs;
	return *this;
}

angle_t angle_t::operator/=( float rhs )
{
	*this = *this / rhs;
	return *this;
}

angle_t angle_t::operator*=( float rhs )
{
	*this = *this * rhs;
	return *this;
}

vector_t::vector_t( )
{
	dx = 0;
	dy = 0;
	dz = 0;
}

vector_t::vector_t( coordinate_t corOrigin, coordinate_t corDestination )
{
	dx = corDestination.x - corOrigin.x;
	dy = corDestination.y - corOrigin.y;
	dz = corDestination.z - corOrigin.z;
}

bool CGlobalVars::operator==( CGlobalVars rhs )
{
	if ( realtime == rhs.realtime && framecount == rhs.framecount && absoluteframetime == rhs.absoluteframetime
		&& absoluteframestarttimestddev == rhs.absoluteframestarttimestddev && curtime == rhs.curtime
		&& frametime == rhs.frametime && maxClients == rhs.maxClients && tickcount == rhs.tickcount
		&& interval_per_tick == rhs.interval_per_tick && interpolation_amount == rhs.interpolation_amount )
	{
		return true;
	}
	return false;
}

bool CGlobalVars::operator!=( CGlobalVars rhs )
{
	if ( *this == rhs )
	{
		return false;
	}
	return true;
}
