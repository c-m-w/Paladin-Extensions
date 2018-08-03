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
	typedef void( PX_API fn_callback_t )( );

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
		};
		UColor* pColor;

	public:
		color_t( );
		explicit color_t( ptr_t* ptrNewAddress );
		explicit color_t( byte_t* bNewColors );
		explicit color_t( int* iNewColors );
		color_t( const float* flNewColors, const unsigned __int8 nColorsCount );
		color_t( byte_t bRed, byte_t bGreen, byte_t bBlue, byte_t bAlpha );
		color_t( byte_t bRed, byte_t bGreen, byte_t bBlue );
		color_t( int iRed, int iGreen, int iBlue, int iAlpha );
		color_t( int iRed, int iGreen, int iBlue );
		color_t( float flRed, float flGreen, float flBlue, float flAlpha );
		color_t( float flRed, float flGreen, float flBlue );
		~color_t( );

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
		bool operator==( const color_t& rhs ) const;
		bool operator!=( const color_t& rhs ) const;
	};
}
