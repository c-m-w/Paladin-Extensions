#pragma once

struct angle_t
{
	float pitch, yaw, roll; // rotation of x/pitch axis, rotation of y/yaw axis, rotation of z/roll axis; visibly y, x, z

	bool operator==( angle_t );
	bool operator!=( angle_t );
	angle_t operator+( angle_t );
	angle_t operator-( angle_t );
	angle_t operator*( float );
	angle_t operator/( float );
	angle_t operator+=( angle_t );
	angle_t operator-=( angle_t );
	angle_t operator*=( float );
	angle_t operator/=( float );
};

struct color_t
{
	BYTE r, g, b, a;
};

struct coordinate_t
{
	float x, y, z;
};

struct vector_t
{
	float dx, dy, dz;

	vector_t( );
	vector_t( coordinate_t, coordinate_t );
};
