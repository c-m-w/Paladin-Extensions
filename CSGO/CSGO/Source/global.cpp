#include "dllmain.h"

HINSTANCE hInst = nullptr;
bool bExitState = false;
std::vector< std::thread > tThreads;

void Wait( unsigned long ulSleepTime )
{
	std::this_thread::sleep_for( std::chrono::milliseconds( ulSleepTime ) );
}

moment GetMoment( )
{
	return std::chrono::duration_cast< std::chrono::milliseconds >( std::chrono::system_clock::now( ).time_since_epoch( ) ).count( );
}

bool angle_t::operator==( angle_t rhs )
{
	return pitch == rhs.pitch && yaw == rhs.yaw && roll == rhs.roll;
}

bool angle_t::operator!=( angle_t rhs )
{
	return !( *this == rhs );
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

angle_t angle_t::operator+=( angle_t rhs )
{
	return *this + rhs;
}

angle_t angle_t::operator-=( angle_t rhs )
{
	return *this - rhs;
}

angle_t angle_t::operator/=( float rhs )
{
	return *this / rhs;
}

angle_t angle_t::operator*=( float rhs )
{
	return *this* rhs;
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
	return flRealTime == rhs.flRealTime && ulFrameCount == rhs.ulFrameCount && flAbsoluteFrameTime == rhs.flAbsoluteFrameTime
			&& flAbsoluteFrameStartTimeStdDev == rhs.flAbsoluteFrameStartTimeStdDev && flCurrentTime == rhs.flCurrentTime
			&& flFrameTime == rhs.flFrameTime && ulMaxClients == rhs.ulMaxClients && ulTickCount == rhs.ulTickCount
			&& flIntervalPerTick == rhs.flIntervalPerTick && flInterpolationAmount == rhs.flInterpolationAmount;
}

bool CGlobalVars::operator!=( CGlobalVars rhs )
{
	return !( *this == rhs );
}
