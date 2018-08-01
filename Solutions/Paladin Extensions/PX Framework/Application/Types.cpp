/// Types.cpp

#include "../PX Framework.hpp"

namespace PX
{
	namespace Types
	{
		byte_t color_t::GetRed( )
		{
			return bColors[ COLOR_RED ];
		}

		byte_t color_t::GetGreen( )
		{
			return bColors[ COLOR_GREEN ];
		}

		byte_t color_t::GetBlue( )
		{
			return bColors[ COLOR_BLUE ];
		}

		byte_t color_t::GetAlpha( )
		{
			return bColors[ COLOR_ALPHA ];
		}

		void color_t::PutRed( byte_t bValue )
		{
			bColors[ COLOR_RED ] = bValue;
		}

		void color_t::PutGreen( byte_t bValue )
		{
			bColors[ COLOR_GREEN ] = bValue;
		}

		void color_t::PutBlue( byte_t bValue )
		{
			bColors[ COLOR_BLUE ] = bValue;
		}

		void color_t::PutAlpha( byte_t bValue )
		{
			bColors[ COLOR_ALPHA ] = bValue;
		}

		float color_t::GetRedFloat( )
		{
			return bColors[ COLOR_RED ] / 255.f;
		}

		float color_t::GetGreenFloat( )
		{
			return bColors[ COLOR_GREEN ] / 255.f;
		}

		float color_t::GetBlueFloat( )
		{
			return bColors[ COLOR_BLUE ] / 255.f;
		}

		float color_t::GetAlphaFloat( )
		{
			return bColors[ COLOR_ALPHA ] / 255.f;
		}

		void color_t::PutRedFloat( float flValue )
		{
			bColors[ COLOR_RED ] = byte_t( flValue <= 1.f ? flValue * 255u : flValue );
		}

		void color_t::PutGreenFloat( float flValue )
		{
			bColors[ COLOR_GREEN ] = byte_t( flValue <= 1.f ? flValue * 255u : flValue );
		}

		void color_t::PutBlueFloat( float flValue )
		{
			bColors[ COLOR_BLUE ] = byte_t( flValue <= 1.f ? flValue * 255u : flValue );
		}

		void color_t::PutAlphaFloat( float flValue )
		{
			bColors[ COLOR_ALPHA ] = byte_t( flValue <= 1.f ? flValue * 255u : flValue );
		}

		byte_t color_t::Luminance( )
		{
			return static_cast< byte_t >( 0.2126f * float( bColors[ COLOR_RED ] ) + 0.7152f * float( bColors[ COLOR_GREEN ] ) + 0.0722f * float( bColors[ COLOR_BLUE ] ) );
		}

		color_t::color_t( byte_t* bNewColors )
		{
			std::memcpy( &bColors[ 0 ], bNewColors, sizeof bNewColors );
		}

		color_t::color_t( byte_t bRed, byte_t bGreen, byte_t bBlue, byte_t bAlpha )
		{
			bColors[ COLOR_RED ] = bRed;
			bColors[ COLOR_GREEN ] = bGreen;
			bColors[ COLOR_BLUE ] = bBlue;
			bColors[ COLOR_ALPHA ] = bAlpha;
		}

		color_t::color_t( byte_t bRed, byte_t bGreen, byte_t bBlue )
		{
			bColors[ COLOR_RED ] = bRed;
			bColors[ COLOR_GREEN ] = bGreen;
			bColors[ COLOR_BLUE ] = bBlue;
			bColors[ COLOR_ALPHA ] = UCHAR_MAX;
		}

		color_t::color_t( float* flNewColors )
		{
			bColors[ COLOR_RED ] = flNewColors[ COLOR_RED ];
			bColors[ COLOR_GREEN ] = flNewColors[ COLOR_GREEN ];
			bColors[ COLOR_BLUE ] = flNewColors[ COLOR_BLUE ];
			bColors[ COLOR_ALPHA ] = flNewColors[ COLOR_ALPHA ];
		}

		color_t::color_t( float flRed, float flGreen, float flBlue, float flAlpha )
		{
			bColors[ COLOR_RED ] = byte_t( flRed <= 1.f ? flRed * 255.f : flRed );
			bColors[ COLOR_GREEN ] = byte_t( flGreen <= 1.f ? flGreen * 255.f : flGreen );
			bColors[ COLOR_BLUE ] = byte_t( flBlue <= 1.f ? flBlue * 255.f : flBlue );
			bColors[ COLOR_ALPHA ] = byte_t( flAlpha <= 1.f ? flAlpha * 255.f : flAlpha );
		}

		color_t::color_t( float flRed, float flGreen, float flBlue )
		{
			bColors[ COLOR_RED ] = byte_t( flRed <= 1.f ? flRed * 255.f : flRed );
			bColors[ COLOR_GREEN ] = byte_t( flGreen <= 1.f ? flGreen * 255.f : flGreen );
			bColors[ COLOR_BLUE ] = byte_t( flBlue <= 1.f ? flBlue * 255.f : flBlue );
			bColors[ COLOR_ALPHA ] = UCHAR_MAX;
		}

		byte_t color_t::operator[ ]( EColor clrColor )
		{
			return bColors[ clrColor ];
		}

		bool color_t::operator==( const color_t& rhs )
		{
			return bColors == rhs.bColors;
		}

		bool color_t::operator!=( const color_t& rhs )
		{
			return bColors != rhs.bColors;
		}
	}
}
