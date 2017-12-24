#include "../dllmain.h"

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
	return *this * rhs;
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
