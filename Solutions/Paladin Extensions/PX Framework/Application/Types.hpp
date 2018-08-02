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
	/** \brief Paladin time datatype, long enough to hold any time type, down to microseconds. */
	typedef unsigned long long moment_t;
	/** \brief Paladin type for post data. */
	struct post_data_t
	{
		std::string strIdentifier, strValue;
		post_data_t( std::string strIdentifier, std::string strValue )
		{
			this->strIdentifier = strIdentifier;
			this->strValue = strValue;
		}
	};

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
		ptr_t* ptrColor;

	public:
		byte_t GetRed( );
		byte_t GetGreen( );
		byte_t GetBlue( );
		byte_t GetAlpha( );

		void PutRed( byte_t bValue );
		void PutGreen( byte_t bValue );
		void PutBlue( byte_t bValue );
		void PutAlpha( byte_t bValue );

		float GetRedFloat( );
		float GetGreenFloat( );
		float GetBlueFloat( );
		float GetAlphaFloat( );

		void PutRedFloat( float flValue );
		void PutGreenFloat( float flValue );
		void PutBlueFloat( float flValue );
		void PutAlphaFloat( float flValue );

		ptr_t GetAsHex( );

		byte_t CalculateLuminance( );
		void SetLuminance( ) = delete;


		color_t( ) = default;
		color_t( byte_t* bNewColors );
		color_t( byte_t bRed, byte_t bGreen, byte_t bBlue, byte_t bAlpha );
		color_t( byte_t bRed, byte_t bGreen, byte_t bBlue );
		color_t( int* iNewColors );
		color_t( int iRed, int iGreen, int iBlue, int iAlpha );
		color_t( int iRed, int iGreen, int iBlue );
		color_t( const float* flNewColors );
		color_t( float flRed, float flGreen, float flBlue, float flAlpha );
		color_t( float flRed, float flGreen, float flBlue );
		color_t( ptr_t* ptrNewAddress );
		~color_t( ) = default;

		byte_t operator[ ]( int iColor );
		bool operator==( const color_t& rhs );
		bool operator!=( const color_t& rhs );

		__declspec( property( get = CalculateLuminance, put = SetLuminance ) ) byte_t Luminance;

		__declspec( property( get = GetRed, put = PutRed ) ) byte_t r;
		__declspec( property( get = GetGreen, put = PutGreen ) ) byte_t g;
		__declspec( property( get = GetBlue, put = PutBlue ) ) byte_t b;
		__declspec( property( get = GetAlpha, put = PutAlpha ) ) byte_t a;

		__declspec( property( get = GetRedFloat, put = PutRedFloat ) ) float rfl;
		__declspec( property( get = GetGreenFloat, put = PutGreenFloat ) ) float gfl;
		__declspec( property( get = GetBlueFloat, put = PutBlueFloat ) ) float bfl;
		__declspec( property( get = GetAlphaFloat, put = PutAlphaFloat ) ) float afl;

		//ptr_t *dwclr = &pColors->u;
	};
}
