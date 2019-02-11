/// Utilities.hpp

#pragma once

/** \brief Contains utilities to be used in other areas of the framework / other projects. */
namespace Utilities
{
	/** \brief Datatype to store time. */
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

	/** \brief Gets the time since epoch in milliseconds. */
	/** \return Time since epoch in milliseconds. */
	template< typename _t = std::chrono::milliseconds >moment_t GetMoment( );
	template< typename _t = std::chrono::milliseconds >void Pause( moment_t mmtPauseLength = 1ui64 );

	/** \brief Supports any combination of static string casting conversion of "std::basic_string< _ch, char_traits< _ch >, allocator< _ch > >" */
	/** \tparam _To Desired string type */
	/** \tparam _From Current string */
	/** \return Converted string in desired type */
	template< typename _To, typename _From > _To string_cast( const _From& );
	/** \brief Supports any combination of string casting conversion of "_ch" and to "std::basic_string< _ch, char_traits< _ch >, allocator< _ch > >" */
	/** \tparam _To Desired string type */
	/** \tparam _From Current string */
	/** \return Converted string in desired type */
	template< typename _To, typename _From > _To string_cast( _From* );

	/** \brief Unsigned char string literal identifier */
	/** \param chSource Character */
	/** \return unsigned char version of array */
	unsigned char operator""_b( char chSource );
	/** \brief Unsigned char string literal identifier */
	/** \param ch16Source Character */
	/** \return unsigned char version of array */
	unsigned char operator""_b( char16_t ch16Source );
	/** \brief Unsigned char string literal identifier */
	/** \param ch32Source Character */
	/** \return unsigned char version of array */
	unsigned char operator""_b( char32_t ch32Source );
	/** \brief Unsigned char string literal identifier */
	/** \param wchSource Character */
	/** \return unsigned char version of array */
	unsigned char operator""_b( wchar_t wchSource );
	/** \brief Unsigned char string literal identifier */
	/** \param szSource Array of characters */
	/** \param zSize Length of array */
	/** \return unsigned char version of array */
	const unsigned char* operator""_b( const char *szSource, std::size_t zSize );
	/** \brief Unsigned char string literal identifier */
	/** \param sz16Source Array of characters */
	/** \param zSize Length of array */
	/** \return unsigned char version of array */
	const unsigned char* operator""_b( const char16_t *sz16Source, std::size_t zSize );
	/** \brief Unsigned char string literal identifier */
	/** \param sz32Source Array of characters */
	/** \param zSize Length of array */
	/** \return unsigned char version of array */
	const unsigned char* operator""_b( const char32_t *sz32Source, std::size_t zSize );
	/** \brief Unsigned char string literal identifier */
	/** \param wszSource Array of characters */
	/** \param zSize Length of array */
	/** \return unsigned char version of array */
	const unsigned char* operator""_b( const wchar_t *wszSource, std::size_t zSize );

}

#include "Utilities.inl"
