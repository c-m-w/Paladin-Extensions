/// Tools.cpp

#include "../PX Framework.hpp"


namespace PX::Tools
{
	using namespace Types;

	void PX_API EmitSound( Types::wcstr_t szFileName )
	{
		const static auto strSoundDirectory = Files::GetDirectory( 1 ) + PX_XOR( LR"(\Resources\Sound\)" );
		PlaySound( ( strSoundDirectory + szFileName ).c_str( ), nullptr, SND_ASYNC );
	}

	//std::string PX_API FormatShellcode( Types::byte_t* bByteArray )
	//{
	//	std::string strFormatted { };
	//	for ( int i { }; i < sizeof bByteArray; i++ )
	//	{
	//		strFormatted += PX_XOR( R"(\x)" );
	//		strFormatted.resize( strFormatted.size( ) + 2 ); // +2 because max length of a byte in digits is 2.
	//		sprintf( &strFormatted[ 0 ], PX_XOR( "%s%02X" ), strFormatted.c_str( ), bByteArray[ i ] );
	//	}
	//	return strFormatted;
	//}

	unsigned* GetScreenDimensions( )
	{
		static unsigned uScreenDimensions[ 2 ];
		uScreenDimensions[ 0 ] = GetSystemMetrics( SM_CXSCREEN );
		uScreenDimensions[ 1 ] = GetSystemMetrics( SM_CYSCREEN );
		return uScreenDimensions;
	}

	color_t::color_t( ): pColor( new UColor )
	{
		for each ( auto& bColor in pColor->b )
			bColor = XOR::LinearCongruentialGenerator( 0 ) % UCHAR_MAX;
	}

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

	float color_t::operator[ ]( const float flColor ) const
	{
		return float( pColor->b[ int( flColor ) ] ) / 255.f;
	}

	bool color_t::operator==( const color_t& rhs ) const
	{
		return pColor->u == rhs.pColor->u;
	}

	bool color_t::operator!=( const color_t& rhs ) const
	{
		return !( *this == rhs );
	}

	color_t color_t::operator+=( const color_t& rhs )
	{
		r += rhs.r;
		g += rhs.g;
		b += rhs.b;
		a += rhs.a;
		return *this;
	}

	color_t color_sequence_t::GetGradient( color_t clrStart, color_t clrEnd, float flProgress )
	{
		return color_t( byte_t( fabs( float( clrEnd.r - clrStart.r ) ) / flProgress ) + clrStart.r,
						byte_t( fabs( float( clrEnd.g - clrStart.g ) ) / flProgress ) + clrStart.g,
						byte_t( fabs( float( clrEnd.b - clrStart.b ) ) / flProgress ) + clrStart.b,
						byte_t( fabs( float( clrEnd.a - clrStart.a ) ) / flProgress ) + clrStart.a );
	}

	color_sequence_t::color_sequence_t( color_t clrFirstSequence, moment_t mmtFirstSequence )
	{
		PutNewColorSequence( clrFirstSequence, mmtFirstSequence );
	}

	color_sequence_t::color_sequence_t( color_t* clrColors, moment_t* mmtDurations, std::size_t sSequences )
	{
		for ( std::size_t s = 0; s < sSequences; s++ )
		{
			sqInfo[ s ].clrColor = clrColors[ s ];
			sqInfo[ s ].mmtDuration = mmtDurations[ s ];
		}
	}

	color_t color_sequence_t::GetCurrentColor( )
	{
		dbg::Assert( sSequences );

		mmtTotalDuration = 0;
		for ( std::size_t s = 0u; s < sSequences; s++ )
			mmtTotalDuration += sqInfo[ s ].mmtDuration;
		auto mmtCurrentProgress = GetMoment( ) % mmtTotalDuration;
		auto mmtPassedProgress = 0ull;

		for ( std::size_t s = 0u; s < sSequences; s++ )
			if ( sqInfo[ s ].mmtDuration < mmtCurrentProgress - mmtPassedProgress )
				mmtPassedProgress += sqInfo[ s ].mmtDuration;
			else
				return GetGradient( sqInfo[ s ].clrColor, sqInfo[ s < 7 ? s - 1 : 0 ].clrColor,
									float( mmtTotalDuration ) / float( mmtCurrentProgress ) );

		// how did we get here? todo: test cases to get us here
		dbg::Assert( false );
	}

	color_t& color_sequence_t::GetColor( unsigned uColor )
	{
		dbg::Assert( sSequences > uColor );
		return sqInfo[ uColor ].clrColor;
	}

	moment_t& color_sequence_t::GetDuration( unsigned uDuration )
	{
		dbg::Assert( sSequences > uDuration );
		return sqInfo[ uDuration ].mmtDuration;
	}

	void color_sequence_t::PutNewColorSequence( color_t clrNewColor, moment_t mmtDuration )
	{
		dbg::Assert( sSequences < 7 );
		sqInfo[ sSequences ].clrColor = clrNewColor;
		sqInfo[ sSequences ].mmtDuration = mmtDuration;
		sSequences++;
	}

	void color_sequence_t::DeleteColorSequence( unsigned uPosition )
	{
		dbg::Assert( sSequences > uPosition );

		for ( auto s = uPosition; s < sSequences; s++ )
		{
			sqInfo[ s ].clrColor = sqInfo[ s + 1 ].clrColor;
			sqInfo[ s ].mmtDuration = sqInfo[ s + 1 ].mmtDuration;
		}
	}
}
