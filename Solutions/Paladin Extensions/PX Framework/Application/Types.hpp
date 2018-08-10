/// Types.hpp

#pragma once

namespace PX::Types
{
	/** \brief Paladin constant char string. */
	typedef const char* cstr_t;
	/** \brief Paladin wide constant char string. */
	typedef const wchar_t* wcstr_t;
	/** \brief Paladin address variable. */
	typedef uintptr_t ptr_t;
	/** \brief Paladin byte datatype. Stores one byte of data. */
	typedef unsigned char byte_t;
	/** \brief Paladin callback function type. */
	typedef void( PX_API* callback_t )( );
	/** \brief Paladin time datatype, long enough to hold any time type, down to microseconds. */
	typedef unsigned long long moment_t;
	
	/** \brief Type to hold colors. */
	struct color_t
	{
		/** \brief Enumeration of colors to index the bColors array. */
		enum EColor
		{
			COLOR_RED,
			COLOR_GREEN,
			COLOR_BLUE,
			COLOR_ALPHA,
			COLOR_MAX
		};

	private:
		union UColor
		{
			unsigned u;
			byte_t b[ COLOR_MAX ];
		} *pColor = new UColor { UINT_MAX };

	public:
		color_t( ) = default;
		color_t( std::initializer_list< ptr_t > initInputs );
		color_t( std::initializer_list< int > initInputs );
		color_t( std::initializer_list< float > initInputs );
		//~color_t( );

		unsigned GetHex( ) const;
		void PutHex( unsigned uValue ) const;
		__declspec( property( get = GetHex, put = PutHex ) ) unsigned Hex;

		byte_t GetRed( ) const;
		byte_t GetGreen( ) const;
		byte_t GetBlue( ) const;
		byte_t GetAlpha( ) const;
		void PutRed( byte_t bValue ) const;
		void PutGreen( byte_t bValue ) const;
		void PutBlue( byte_t bValue ) const;
		void PutAlpha( byte_t bValue ) const;
		__declspec( property( get = GetRed, put = PutRed ) ) byte_t r;
		__declspec( property( get = GetGreen, put = PutGreen ) ) byte_t g;
		__declspec( property( get = GetBlue, put = PutBlue ) ) byte_t b;
		__declspec( property( get = GetAlpha, put = PutAlpha ) ) byte_t a;

		float GetRedFloat( ) const;
		float GetGreenFloat( ) const;
		float GetBlueFloat( ) const;
		float GetAlphaFloat( ) const;
		void PutRedFloat( float flValue ) const;
		void PutGreenFloat( float flValue ) const;
		void PutBlueFloat( float flValue ) const;
		void PutAlphaFloat( float flValue ) const;
		__declspec( property( get = GetRedFloat, put = PutRedFloat ) ) float rfl;
		__declspec( property( get = GetGreenFloat, put = PutGreenFloat ) ) float gfl;
		__declspec( property( get = GetBlueFloat, put = PutBlueFloat ) ) float bfl;
		__declspec( property( get = GetAlphaFloat, put = PutAlphaFloat ) ) float afl;

		byte_t CalculateLuminance( ) const;
		void SetLuminance( ) = delete;
		__declspec( property( get = CalculateLuminance, put = SetLuminance ) ) byte_t Luminance;

		byte_t operator[ ]( int iColor ) const;
		float operator[ ]( float flColor ) const;
		//bool operator==( const color_t& rhs ) const;
		//bool operator!=( const color_t& rhs ) const;
	};

	struct color_sequence_t
	{
		static color_t GetGradient( color_t clrStart, color_t clrEnd, float flProgress );
		struct sequence_info_t
		{
			color_t clrColor;
			moment_t mmtDuration;
		};
	private:
		sequence_info_t sqInfo[ 7 ];
		moment_t mmtTotalDuration = 0;
	public:
		std::size_t sSequences = 0u;
		color_sequence_t( ) = default;
		color_sequence_t( color_t clrFirstSequence, moment_t mmtFirstSequence );
		color_sequence_t( color_t* clrColors, moment_t* mmtDurations, std::size_t sSequences );

		color_t GetCurrentColor( );
		void PutCurrentColor( ) = delete;

		color_t& GetColor( unsigned uColor );
		moment_t& GetDuration( unsigned uDuration );

		void PutNewColorSequence( const color_t& clrNewColor, moment_t mmtDuration ); // todo: overload <<
		void DeleteColorSequence( unsigned uPosition ); // todo: overload >>
		
		//void operator<<( sequence_info_t );
		//void operator>>( unsigned uPosition );
	};
}
