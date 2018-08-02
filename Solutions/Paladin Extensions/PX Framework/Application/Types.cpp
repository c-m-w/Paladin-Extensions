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

		byte_t color_t::CalculateLuminance( )
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

		color_t::color_t( int* iNewColors )
		{
			color_t( reinterpret_cast< byte_t* >( iNewColors ) );
		}

		color_t::color_t( int iRed, int iGreen, int iBlue, int iAlpha )
		{
			color_t( byte_t( iRed ), byte_t( iGreen ), byte_t( iBlue ), byte_t( iAlpha ) );
		}

		color_t::color_t( int iRed, int iGreen, int iBlue )
		{
			color_t( byte_t( iRed ), byte_t( iGreen ), byte_t( iBlue ) );
		}

		color_t::color_t( const float* flNewColors )
		{
			const bool bContainsAlphaData = sizeof flNewColors == 16;
			if ( flNewColors[ COLOR_RED ] > 1.f || flNewColors[ COLOR_GREEN ] > 1.f || flNewColors[ COLOR_BLUE ] > 1.f || flNewColors ? flNewColors[ COLOR_ALPHA ] > 1.f : false )
			{
				bColors[ COLOR_RED ] = byte_t( flNewColors[ COLOR_RED ] );
				bColors[ COLOR_GREEN ] = byte_t( flNewColors[ COLOR_GREEN ] );
				bColors[ COLOR_BLUE ] = byte_t( flNewColors[ COLOR_BLUE ]  );
				bColors[ COLOR_ALPHA ] = bContainsAlphaData ? byte_t( flNewColors[ COLOR_ALPHA ] ) : UCHAR_MAX;
			}
			else
			{
				bColors[ COLOR_RED ] = byte_t( flNewColors[ COLOR_RED ] * 255.f );
				bColors[ COLOR_GREEN ] = byte_t( flNewColors[ COLOR_GREEN ] * 255.f );
				bColors[ COLOR_BLUE ] = byte_t( flNewColors[ COLOR_BLUE ] * 255.f );
				bColors[ COLOR_ALPHA ] = bContainsAlphaData ? byte_t( flNewColors[ COLOR_ALPHA ] * 255.f ) : UCHAR_MAX;
			}
		}

		color_t::color_t( float flRed, float flGreen, float flBlue, float flAlpha )
		{
			if ( flRed > 1.f || flGreen > 1.f || flBlue > 1.f || flAlpha > 1.f )
			{
				bColors[ COLOR_RED ] = byte_t( flRed );
				bColors[ COLOR_GREEN ] = byte_t( flGreen );
				bColors[ COLOR_BLUE ] = byte_t( flBlue );
				bColors[ COLOR_ALPHA ] = byte_t( flAlpha );
			}
			else
			{
				bColors[ COLOR_RED ] = byte_t( flRed * 255.f );
				bColors[ COLOR_GREEN ] = byte_t( flGreen * 255.f );
				bColors[ COLOR_BLUE ] = byte_t( flBlue * 255.f );
				bColors[ COLOR_ALPHA ] = byte_t( flAlpha * 255.f );
			}
		}

		color_t::color_t( float flRed, float flGreen, float flBlue )
		{
			if ( flRed > 1.f || flGreen > 1.f || flBlue > 1.f )
			{
				bColors[ COLOR_RED ] = byte_t( flRed );
				bColors[ COLOR_GREEN ] = byte_t( flGreen );
				bColors[ COLOR_BLUE ] = byte_t( flBlue );
			}
			else
			{
				bColors[ COLOR_RED ] = byte_t( flRed * 255.f );
				bColors[ COLOR_GREEN ] = byte_t( flGreen * 255.f );
				bColors[ COLOR_BLUE ] = byte_t( flBlue * 255.f );
			}
			bColors[ COLOR_ALPHA ] = UCHAR_MAX;
		}

		byte_t color_t::operator[ ]( int clrColor )
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
