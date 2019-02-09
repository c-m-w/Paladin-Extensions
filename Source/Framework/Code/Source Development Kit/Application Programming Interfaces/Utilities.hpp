/// Utilities.hpp

#pragma once

/** \brief Contains utilities to be used in other areas of the framework / other projects. */
namespace Utilities
{
	/** \brief Datatype to store time. Maximum precision is tenths of microseconds */
	using moment_t = unsigned __int64;

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


	/** \brief Gets the time since UNIX epoch */
	/** \return Time since epoch to the tenth of a microsecond. */
	moment_t GetMoment( );
	void Wait( moment_t mmtWaitLength = 0ui64 );
	void Pause( moment_t mmtPauseLength = ULLONG_MAX );
	void OpenLink( const std::string& strLink );
}

#include "Utilities.inl"
