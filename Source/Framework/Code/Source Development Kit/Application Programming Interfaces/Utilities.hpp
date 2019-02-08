/// Utilities.hpp

#pragma once

/** \brief Contains utilities to be used in other areas of the framework / other projects. */
namespace Utilities
{

	struct location_t
	{
		float x, y;

		location_t( ) = default;
		location_t( float _x, float _y );

		location_t operator-( const location_t &rhs );
		location_t operator+( const location_t &rhs );
		bool operator!=( const location_t &rhs );

		void Rotate( float flAngle, location_t locRotationPoint );
		void Invalidate( );
		bool Valid( ) const;
		float Length( ) const;
		float Angle( ) const;
	};

	using vector2_t = location_t;

	vector2_t GetScreenSize( );
}

#include "Utilities.inl"
