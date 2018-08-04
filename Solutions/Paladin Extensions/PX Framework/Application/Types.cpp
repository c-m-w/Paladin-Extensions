/// Types.cpp

#include "../PX Framework.hpp"

namespace PX::Types
{

	color_t::color_t( ): pColor( new UColor )
	{ }

	color_t::color_t( ptr_t* ptrNewAddress )
	{
		pColor = reinterpret_cast< UColor* >( ptrNewAddress );
	}

	color_t::color_t( byte_t* bNewColors ): pColor( new UColor )
	{
		std::memcpy( pColor, bNewColors, sizeof( UColor ) );
	}

	color_t::color_t( int* iNewColors ) : pColor( new UColor )
	{
		std::memcpy( pColor, iNewColors, sizeof( UColor ) );
	}

	color_t::color_t( const float* flNewColors, const unsigned __int8 nColorsCount ) : pColor( new UColor )
	{
		if ( !dbg::Assert( nColorsCount == 4 || nColorsCount == 3 ) )
			return;
		PutRedFloat( flNewColors[ COLOR_RED ] );
		PutGreenFloat( flNewColors[ COLOR_GREEN ] );
		PutBlueFloat( flNewColors[ COLOR_BLUE ] );
		PutAlphaFloat( nColorsCount == 4 ? flNewColors[ COLOR_ALPHA ] : 255.f );
	}

	color_t::color_t( const byte_t bRed, const byte_t bGreen, const byte_t bBlue, const byte_t bAlpha ): pColor( new UColor )
	{
		PutRed( bRed );
		PutGreen( bGreen );
		PutBlue( bBlue );
		PutAlpha( bAlpha );
	}

	color_t::color_t( const byte_t bRed, const byte_t bGreen, const byte_t bBlue ): pColor( new UColor )
	{
		PutRed( bRed );
		PutGreen( bGreen );
		PutBlue( bBlue );
		PutAlpha( UCHAR_MAX );
	}

	color_t::color_t( const int iRed, const int iGreen, const int iBlue, const int iAlpha ): pColor( new UColor )
	{
		PutRed( byte_t( iRed ) );
		PutGreen( byte_t( iGreen ) );
		PutBlue( byte_t( iBlue ) );
		PutAlpha( byte_t( iAlpha ) );
	}

	color_t::color_t( const int iRed, const int iGreen, const int iBlue ): pColor( new UColor )
	{
		PutRed( byte_t( iRed ) );
		PutGreen( byte_t( iGreen ) );
		PutBlue( byte_t( iBlue ) );
		PutAlpha( UCHAR_MAX );
	}

	color_t::color_t( const float flRed, const float flGreen, const float flBlue, const float flAlpha ): pColor( new UColor )
	{
		PutRedFloat( flRed );
		PutGreenFloat( flGreen );
		PutBlueFloat( flBlue );
		PutAlphaFloat( flAlpha );
	}

	color_t::color_t( const float flRed, const float flGreen, const float flBlue ): pColor( new UColor )
	{
		PutRedFloat( flRed );
		PutGreenFloat( flGreen );
		PutBlueFloat( flBlue );
		PutAlpha( UCHAR_MAX );
	}

	color_t::~color_t( )
	{
		delete pColor;
	}

	unsigned color_t::GetHex( ) const
	{
		return pColor->u;
	}

	void color_t::PutHex( const unsigned uValue ) const
	{
		pColor->u = uValue;
	}

	byte_t color_t::GetRed( ) const
	{
		return pColor->b[ COLOR_RED ];
	}

	byte_t color_t::GetGreen( ) const
	{
		return pColor->b[ COLOR_GREEN ];
	}

	byte_t color_t::GetBlue( ) const
	{
		return pColor->b[ COLOR_BLUE ];
	}

	byte_t color_t::GetAlpha( ) const
	{
		return pColor->b[ COLOR_ALPHA ];
	}

	void color_t::PutRed( const byte_t bValue ) const
	{
		pColor->b[ COLOR_RED ] = bValue;
	}

	void color_t::PutGreen( const byte_t bValue ) const
	{
		pColor->b[ COLOR_GREEN ] = bValue;
	}

	void color_t::PutBlue( const byte_t bValue ) const
	{
		pColor->b[ COLOR_BLUE ] = bValue;
	}

	void color_t::PutAlpha( const byte_t bValue ) const
	{
		pColor->b[ COLOR_ALPHA ] = bValue;
	}

	float color_t::GetRedFloat( ) const
	{
		return GetRed( ) / 255.f;
	}

	float color_t::GetGreenFloat( ) const
	{
		return GetGreen( ) / 255.f;
	}

	float color_t::GetBlueFloat( ) const
	{
		return GetBlue( ) / 255.f;
	}

	float color_t::GetAlphaFloat( ) const
	{
		return GetAlpha( ) / 255.f;
	}

	void color_t::PutRedFloat( const float flValue ) const
	{
		PutRed( byte_t( flValue <= 1.f ? flValue * 255u : flValue ) );
	}

	void color_t::PutGreenFloat( const float flValue ) const
	{
		PutGreen( byte_t( flValue <= 1.f ? flValue * 255u : flValue ) );
	}

	void color_t::PutBlueFloat( const float flValue ) const
	{
		PutBlue( byte_t( flValue <= 1.f ? flValue * 255u : flValue ) );
	}

	void color_t::PutAlphaFloat( const float flValue ) const
	{
		PutAlpha( byte_t( flValue <= 1.f ? flValue * 255u : flValue ) );
	}

	byte_t color_t::CalculateLuminance( ) const
	{
		return static_cast< byte_t >( 0.2126f * float( GetRed( ) ) + 0.7152f * float( GetGreen( ) ) + 0.0722f * float( GetBlue( ) ) );
	}

	byte_t color_t::operator[ ]( const int iColor ) const
	{
		return pColor->b[ iColor ];
	}

	bool color_t::operator==( const color_t& rhs ) const
	{
		return pColor->u == rhs.pColor->u;
	}

	bool color_t::operator!=( const color_t& rhs ) const
	{
		return !( *this == rhs );
	}
}
