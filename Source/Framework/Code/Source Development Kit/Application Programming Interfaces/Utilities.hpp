/// Utilities.hpp

#pragma once

/** \brief Contains utilities to be used in other areas of the framework / other projects. */
namespace Utilities
{
	/** \brief Datatype to store time. */
	using moment_t = unsigned __int64;

	struct vector3_t;

	struct vector2_t
	{
		constexpr static auto PI = 3.1415926535897932;
		double x = 0.0, y = 0.0;

		vector2_t( ) = default;
		vector2_t( double x, double y );
		~vector2_t( ) = default;

		explicit operator vector3_t( ) const;
		explicit operator D3DXVECTOR2( ) const;
		explicit operator double( ) const;
		vector2_t operator+( double rhs );
		vector2_t operator-( double rhs );
		vector2_t operator*( double rhs );
		vector2_t operator/( double rhs );
		vector2_t operator+( const vector2_t& rhs );
		vector2_t operator-( const vector2_t& rhs );
		vector2_t operator*( const vector2_t& rhs );
		vector2_t operator/( const vector2_t& rhs );
		vector2_t operator^( double rhs );

		double Length( ) const;
		void Round( );
		double Angle( ) const;
		void Rotate( float flAngle, vector2_t vecRotationPoint );
		void Invalidate( );
		bool Valid( ) const;
	};

	struct vector3_t
	{
		double x = 0.0, y = 0.0, z = 0.0;

		vector3_t( ) = default;
		vector3_t( double x, double y, double z );
		~vector3_t( ) = default;

		explicit operator vector2_t( ) const;
		explicit operator D3DXVECTOR3( ) const;
		explicit operator double( ) const;
		vector3_t operator+( double rhs );
		vector3_t operator-( double rhs );
		vector3_t operator*( double rhs );
		vector3_t operator/( double rhs );
		vector3_t operator+( const vector3_t& rhs );
		vector3_t operator-( const vector3_t& rhs );
		vector3_t operator*( const vector3_t& rhs );
		vector3_t operator/( const vector3_t& rhs );
		vector3_t operator^( double rhs );

		double Length( ) const;
		void Round( );
		vector2_t Angle( ) const;
		void Invalidate( );
		bool Valid( ) const;
	};

	/** \brief Gets the time since epoch */
	/** \tparam _t Duration type to return time in (nanoseconds highest supported) */
	/** \return Time since epoch in specified duration. */
	template< typename _t = std::chrono::milliseconds >moment_t GetMoment( );
	/** \brief Suspends current thread execution */
	/** \tparam _t Duration type to pause (nanoseconds highest supported) */
	/** \param mmtPauseLength Length to pause in specified duration */
	template< typename _t = std::chrono::milliseconds >void Pause( moment_t mmtPauseLength = 1ui64 );

	/** \brief Supports any combination of static string casting conversion of "std::basic_string< _ch, char_traits< _ch >, allocator< _ch > >" */
	/** \tparam _To Desired string type */
	/** \tparam _From Current string */
	/** \param _From String to convert */
	/** \return Converted string in desired type */
	template< typename _To, typename _From > _To string_cast( const _From& );
	/** \brief Supports any combination of string casting conversion of "_ch" and to "std::basic_string< _ch, char_traits< _ch >, allocator< _ch > >" */
	/** \tparam _To Desired string type */
	/** \tparam _From Current string */
	/** \param _From String to convert */
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
