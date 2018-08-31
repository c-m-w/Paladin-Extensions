/// Types.cpp

#define PX_USE_NAMESPACES
#include "../PX Framework.hpp"

namespace PX::Types
{
	module_t::module_t( std::wstring _wstrName )
	{
		wstrName = _wstrName;
		hModule = GetModuleHandle( wstrName.c_str( ) );
	}

	bool module_t::Succeeded( )
	{
		return hModule != nullptr;
	}

	ptr_t module_t::FindPattern( std::string strPattern )
	{
		const auto fnIDAPatternToBytes = [ = ]( )
		{
			std::vector< int > vecBytes { };
			auto iCurrentByteCount = 0;
			char szCurrentBytes[ 2 ] { };

			for each( auto& ch in strPattern )
			{
				if ( ch == '?' )
					vecBytes.emplace_back( -1 );
				else if ( ch != ' ' )
				{
					szCurrentBytes[ iCurrentByteCount ] = ch;
					iCurrentByteCount++;
					if ( iCurrentByteCount == 2 )
					{
						char* szBuffer;
						vecBytes.emplace_back( strtol( szCurrentBytes, &szBuffer, 16 ) );
						iCurrentByteCount = 0;
					}
				}
			}
			return vecBytes;
		};

		const auto vecByteForm = fnIDAPatternToBytes( );
		for( auto ptr = ptr_t( hModule ); ptr < GetModuleEnd( hModule ); ptr++ )
		{
			auto bFound = true;
			for ( auto u = 0u; u < vecByteForm.size( ); u++ )
			{
				auto iValue = vecByteForm[ u ];
				if ( iValue == -1 )
					continue;
				if ( *reinterpret_cast< byte_t* >( ptr + u ) != iValue )
				{
					bFound = false;
					break;
				}
			}

			if ( bFound )
				return ptr;
		}
		return 0u;
	}

	SColor::SColor( std::initializer_list< ptr_t > initInputs )
	{
		px_assert( initInputs.size( ) == 1 );
		for each ( auto initInput in initInputs )
		{
			delete pColor;
			pColor = reinterpret_cast< UColor* >( initInput );
		}
	}

	SColor::SColor( std::initializer_list< int > initInputs )
	{
		px_assert( initInputs.size( ) <= 4 );
		auto u = 0u;
		for each ( auto initInput in initInputs )
		{
			pColor->b[ u ] = byte_t( initInput );
			u++;
		}
		for ( auto uu = 4u; uu > u + 1; uu-- )
			pColor->b[ uu ] = UCHAR_MAX;
	}

	SColor::SColor( std::initializer_list< float > initInputs )
	{
		px_assert( initInputs.size( ) <= 4 );
		auto u = 0u;
		for each ( auto initInput in initInputs )
		{
			pColor->b[ u ] = byte_t( initInput > 1.f ? initInput : initInput * 255.f );
			u++;
		}
		for ( auto uu = 4u; uu > u + 1; uu-- )
			pColor->b[ uu ] = UCHAR_MAX;
	}

	//SColor::~SColor( )
	//{
	//	delete pColor;
	//}

	unsigned SColor::GetRGBA( ) const
	{
		return pColor->u;
	}

	unsigned SColor::GetARGB( ) const
	{
		return D3DCOLOR_ARGB( pColor->b[ COLOR_ALPHA ], pColor->b[ COLOR_RED ], pColor->b[ COLOR_GREEN ], pColor->b[ COLOR_BLUE ] );
	}

	void SColor::PutHex( const unsigned uValue ) const
	{
		pColor->u = uValue;
	}

	byte_t SColor::GetRed( ) const
	{
		if ( pColor == nullptr )
			return UCHAR_MAX;
		return pColor->b[ COLOR_RED ];
	}

	byte_t SColor::GetGreen( ) const
	{
		if ( pColor == nullptr )
			return UCHAR_MAX;
		return pColor->b[ COLOR_GREEN ];
	}

	byte_t SColor::GetBlue( ) const
	{
		if ( pColor == nullptr )
			return UCHAR_MAX;
		return pColor->b[ COLOR_BLUE ];
	}

	byte_t SColor::GetAlpha( ) const
	{
		if ( pColor == nullptr )
			return UCHAR_MAX;
		return pColor->b[ COLOR_ALPHA ];
	}

	void SColor::PutRed( const byte_t bValue ) const
	{
		pColor->b[ COLOR_RED ] = bValue;
	}

	void SColor::PutGreen( const byte_t bValue ) const
	{
		pColor->b[ COLOR_GREEN ] = bValue;
	}

	void SColor::PutBlue( const byte_t bValue ) const
	{
		pColor->b[ COLOR_BLUE ] = bValue;
	}

	void SColor::PutAlpha( const byte_t bValue ) const
	{
		pColor->b[ COLOR_ALPHA ] = bValue;
	}

	float SColor::GetRedFloat( ) const
	{
		return GetRed( ) / 255.f;
	}

	float SColor::GetGreenFloat( ) const
	{
		return GetGreen( ) / 255.f;
	}

	float SColor::GetBlueFloat( ) const
	{
		return GetBlue( ) / 255.f;
	}

	float SColor::GetAlphaFloat( ) const
	{
		return GetAlpha( ) / 255.f;
	}

	void SColor::PutRedFloat( const float flValue ) const
	{
		PutRed( byte_t( flValue <= 1.f ? flValue * 255u : flValue ) );
	}

	void SColor::PutGreenFloat( const float flValue ) const
	{
		PutGreen( byte_t( flValue <= 1.f ? flValue * 255u : flValue ) );
	}

	void SColor::PutBlueFloat( const float flValue ) const
	{
		PutBlue( byte_t( flValue <= 1.f ? flValue * 255u : flValue ) );
	}

	void SColor::PutAlphaFloat( const float flValue ) const
	{
		PutAlpha( byte_t( flValue <= 1.f ? flValue * 255u : flValue ) );
	}

	byte_t SColor::CalculateLuminance( ) const
	{
		return static_cast< byte_t >( 0.2126f * float( GetRed( ) ) + 0.7152f * float( GetGreen( ) ) + 0.0722f * float( GetBlue( ) ) );
	}

	byte_t SColor::operator[ ]( const int iColor ) const
	{
		return pColor->b[ iColor ];
	}

	float SColor::operator[ ]( const float flColor ) const
	{
		return float( pColor->b[ int( flColor ) ] ) / 255.f;
	}

	color_t SColorSequence::GetGradient( color_t clrStart, color_t clrEnd, float flProgress )
	{
		px_assert( flProgress >= 0.f && flProgress <= 1.f );
		return { clrStart.r + byte_t( ( clrEnd.r - clrStart.r ) * flProgress ),
					clrStart.g + byte_t( ( clrEnd.g - clrStart.g ) * flProgress ),
					clrStart.b + byte_t( ( clrEnd.b - clrStart.b ) * flProgress ),
					clrStart.a + byte_t( ( clrEnd.a - clrStart.a ) * flProgress ) };
	}

	//bool SColor::operator==( const SColor& rhs ) const
	//{
	//	return pColor->u == rhs.pColor->u;
	//}
	//
	//bool SColor::operator!=( const SColor& rhs ) const
	//{
	//	return !( *this == rhs );
	//}

	SColorSequence::SColorSequence( color_t clrFirstSequence, moment_t mmtFirstSequence )
	{
		PutNewColorSequence( clrFirstSequence, mmtFirstSequence );
	}

	SColorSequence::SColorSequence( color_t* clrColors, moment_t* mmtDurations, std::size_t zSequences )
	{
		for ( std::size_t z = 0; z < zSequences; z++ )
		{
			sqInfo[ z ].clrColor = clrColors[ z ];
			sqInfo[ z ].mmtDuration = mmtDurations[ z ];
		}
	}

	color_t SColorSequence::GetCurrentColor( )
	{
		px_assert( zSequences );

		if ( zSequences == 1 )
			return sqInfo[ 0 ].clrColor;

		mmtTotalDuration = 0;
		for ( std::size_t z = 0u; z < zSequences; z++ )
			mmtTotalDuration += sqInfo[ z ].mmtDuration;
		auto mmtCurrentProgress = GetMoment( ) % mmtTotalDuration;
		auto mmtPassedProgress = 0ull;

		for ( std::size_t z = 0u; z < zSequences; z++ )
			if ( sqInfo[ z ].mmtDuration < mmtCurrentProgress - mmtPassedProgress )
				mmtPassedProgress += sqInfo[ z ].mmtDuration;
			else
				return GetGradient( sqInfo[ z ].clrColor, sqInfo[ z + 1 != zSequences ? z + 1 : 0 ].clrColor,
									float( mmtCurrentProgress - mmtPassedProgress ) / float( sqInfo[ z ].mmtDuration ) );

		px_assert( false );
	}

	color_t& SColorSequence::GetColor( unsigned uColor )
	{
		px_assert( zSequences > uColor );
		return sqInfo[ uColor ].clrColor;
	}

	moment_t& SColorSequence::GetDuration( unsigned uDuration )
	{
		px_assert( zSequences > uDuration );
		return sqInfo[ uDuration ].mmtDuration;
	}

	void SColorSequence::PutNewColorSequence( const color_t& clrNewColor, moment_t mmtDuration )
	{
		if ( zSequences >= 7 )
			return;

		sqInfo[ zSequences ].clrColor = clrNewColor;
		sqInfo[ zSequences ].mmtDuration = mmtDuration;
		zSequences++;
	}

	void SColorSequence::DeleteColorSequence( unsigned uPosition )
	{
		if ( zSequences <= uPosition )
			return;

		for ( auto s = uPosition; s < zSequences - 1; s++ )
		{
			sqInfo[ s ].clrColor = sqInfo[ s + 1 ].clrColor;
			sqInfo[ s ].mmtDuration = sqInfo[ s + 1 ].mmtDuration;
		}

		zSequences--;
	}
}