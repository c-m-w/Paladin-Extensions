/// Types.cpp

#include "../PX Framework.hpp"

namespace PX::Types
{
	byte_t color_t::GetRed( )
	{
		return ( *ptrColor & 0xFF000000u ) >> 24;
	}

	byte_t color_t::GetGreen( )
	{
		return ( *ptrColor & 0x00FF0000u ) >> 16;
	}

	byte_t color_t::GetBlue( )
	{
		return ( *ptrColor & 0x0000FF00u ) >> 8;
	}

	byte_t color_t::GetAlpha( )
	{
		return *ptrColor & 0x000000FFu;
	}

	void color_t::PutRed( byte_t bValue )
	{
		*ptrColor &= 0x00FFFFFFu;
		*ptrColor |= bValue << 24;
	}

	void color_t::PutGreen( byte_t bValue )
	{
		*ptrColor &= 0xFF00FFFFu;
		*ptrColor |= bValue << 16;
	}

	void color_t::PutBlue( byte_t bValue )
	{
		*ptrColor &= 0xFFFF00FFu;
		*ptrColor |= bValue << 8;
	}

	void color_t::PutAlpha( byte_t bValue )
	{
		*ptrColor &= 0xFFFFFF00u;
		*ptrColor |= bValue;
	}

	float color_t::GetRedFloat( )
	{
		return GetRed( ) / 255.f;
	}

	float color_t::GetGreenFloat( )
	{
		return GetGreen( ) / 255.f;
	}

	float color_t::GetBlueFloat( )
	{
		return GetBlue( ) / 255.f;
	}

	float color_t::GetAlphaFloat( )
	{
		return GetAlpha( ) / 255.f;
	}

	void color_t::PutRedFloat( float flValue )
	{
		PutRed( byte_t( flValue <= 1.f ? flValue * 255u : flValue ) );
	}

	void color_t::PutGreenFloat( float flValue )
	{
		PutGreen( byte_t( flValue <= 1.f ? flValue * 255u : flValue ) );
	}

	void color_t::PutBlueFloat( float flValue )
	{
		PutBlue( byte_t( flValue <= 1.f ? flValue * 255u : flValue ) );
	}

	void color_t::PutAlphaFloat( float flValue )
	{
		PutAlpha( byte_t( flValue <= 1.f ? flValue * 255u : flValue ) );
	}

	ptr_t color_t::GetAsHex( )
	{
		return *ptrColor;
	}

	byte_t color_t::CalculateLuminance( )
	{
		return static_cast< byte_t >( 0.2126f * float( GetRed( ) ) + 0.7152f * float( GetGreen( ) ) + 0.0722f * float( GetBlue( ) ) );
	}

	color_t::color_t( byte_t* bNewColors ):
		ptrColor( new ptr_t { 0x0u } )
	{
		std::memcpy( ptrColor, bNewColors, sizeof bNewColors );
	}

	color_t::color_t( byte_t bRed, byte_t bGreen, byte_t bBlue, byte_t bAlpha ):
		ptrColor( new ptr_t { 0x0u } )
	{
		PutRed( bRed );
		PutGreen( bGreen );
		PutBlue( bBlue );
		PutAlpha( bAlpha );
	}

	color_t::color_t( byte_t bRed, byte_t bGreen, byte_t bBlue ):
		ptrColor( new ptr_t { 0x0u } )
	{
		PutRed( bRed );
		PutGreen( bGreen );
		PutBlue( bBlue );
		PutAlpha( UCHAR_MAX );
	}

	color_t::color_t( int* iNewColors )
	{
		*this = color_t( reinterpret_cast< byte_t* >( iNewColors ) );
	}

	color_t::color_t( int iRed, int iGreen, int iBlue, int iAlpha )
	{
		*this = color_t( byte_t( iRed ), byte_t( iGreen ), byte_t( iBlue ), byte_t( iAlpha ) );
	}

	color_t::color_t( int iRed, int iGreen, int iBlue )
	{
		*this = color_t( byte_t( iRed ), byte_t( iGreen ), byte_t( iBlue ) );
	}

	color_t::color_t( const float* flNewColors )
	{
		const bool bContainsAlphaData = sizeof flNewColors == 16;
		if ( flNewColors[ COLOR_RED ] > 1.f || flNewColors[ COLOR_GREEN ] > 1.f || flNewColors[ COLOR_BLUE ] > 1.f || flNewColors ? flNewColors[ COLOR_ALPHA ] > 1.f : false )
		{
			PutRed( byte_t( flNewColors[ COLOR_RED ] ) );
			PutGreen( byte_t( flNewColors[ COLOR_GREEN ] ) );
			PutBlue( byte_t( flNewColors[ COLOR_BLUE ] ) );
			PutAlpha( bContainsAlphaData ? byte_t( flNewColors[ COLOR_ALPHA ] ) : UCHAR_MAX );
		}
		else
		{
			PutRed( byte_t( flNewColors[ COLOR_RED ] * 255.f ) );
			PutGreen( byte_t( flNewColors[ COLOR_GREEN ] * 255.f ) );
			PutBlue( byte_t( flNewColors[ COLOR_BLUE ] * 255.f ) );
			PutAlpha( bContainsAlphaData ? byte_t( flNewColors[ COLOR_ALPHA ] * 255.f ) : UCHAR_MAX );
		}
	}

	color_t::color_t( float flRed, float flGreen, float flBlue, float flAlpha )
	{
		if ( flRed > 1.f || flGreen > 1.f || flBlue > 1.f || flAlpha > 1.f )
		{
			PutRed( byte_t( flRed ) );
			PutGreen( byte_t( flGreen ) );
			PutBlue( byte_t( flBlue ) );
			PutAlpha( byte_t( flAlpha ) );
		}
		else
		{
			PutRed( byte_t( flRed * 255.f ) );
			PutGreen( byte_t( flGreen * 255.f ) );
			PutBlue( byte_t( flBlue * 255.f ) );
			PutAlpha( byte_t( flAlpha * 255.f ) );
		}
	}

	color_t::color_t( float flRed, float flGreen, float flBlue )
	{
		if ( flRed > 1.f || flGreen > 1.f || flBlue > 1.f )
		{
			PutRed( byte_t( flRed ) );
			PutGreen( byte_t( flGreen ) );
			PutBlue( byte_t( flBlue ) );
		}
		else
		{
			PutRed( byte_t( flRed * 255.f ) );
			PutGreen( byte_t( flGreen * 255.f ) );
			PutBlue( byte_t( flBlue * 255.f ) );
		}
		PutAlpha( UCHAR_MAX );
	}

	color_t::color_t( ptr_t* ptrNewAddress )
	{
		ptrColor = ptrNewAddress;
	}

	byte_t color_t::operator[ ]( int iColor )
	{
		union dad
		{
			ptr_t a;
			byte_t b[ 4 ];
		};

		auto p = reinterpret_cast< dad* >( ptrColor );

		return p->b[ iColor ];
	}

	bool color_t::operator==( const color_t& rhs )
	{
		return *ptrColor == *rhs.ptrColor;
	}

	bool color_t::operator!=( const color_t& rhs )
	{
		return *ptrColor != *rhs.ptrColor;
	}
}
