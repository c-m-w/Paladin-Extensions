/// Types.cpp

#include "PX Precompiled.hpp"
#define PX_USE_NAMESPACES
#include "../PX Framework.hpp"

namespace PX::Types
{
	toggle_t::toggle_t( ): bEnabled( false ), vecKeyBinds( { } )
	{ }

	toggle_t::toggle_t( bool _bEnabled ) : bEnabled( _bEnabled ), vecKeyBinds( { } )
	{ }

	void toggle_t::AddToList( )
	{
		px_assert( pConfigStructure != nullptr && zConfigStructureSize > 0 );
		if ( bAttemptedToAddToList || this < pConfigStructure || ptr_t( this ) > ptr_t( pConfigStructure ) + zConfigStructureSize )
			return;

		if ( !bAddedToList )
		{
			bAddedToList = true;
			vecToggles.emplace_back( this );
		}
		bAttemptedToAddToList = true;
	}

	bool &toggle_t::Get( )
	{
		AddToList( );
		return bEnabled;
	}

	bool &toggle_t::UseKeyBinds( )
	{
		AddToList( );
		return bUseKeybinds;
	}

	std::vector< toggle_t::keybind_t > &toggle_t::GetBinds( )
	{
		AddToList( );
		return vecKeyBinds;
	}

	toggle_t &toggle_t::operator=( bool _bEnabled )
	{
		AddToList( );
		bEnabled = _bEnabled;
		return *this;
	}

	bool toggle_t::operator!( )
	{
		AddToList( );
		return !bEnabled;
	}

	line_t::line_t( const D3DXVECTOR2 *_pVertices, std::size_t _sVertices, float _flWidth, DWORD _dwColor, BOOL _bAntiAlias /*= TRUE*/ ): drawing_t< D3DXVECTOR2 >( _pVertices, _sVertices )
	{
		dwColor = _dwColor;
		flWidth = _flWidth;
		bAntiAlias = _bAntiAlias;
	}

	polygon_t::polygon_t( const vertex_t *_pVertices, std::size_t _sVertices, std::size_t _sPrimitives, D3DPRIMITIVETYPE _ptType ): drawing_t< vertex_t >( _pVertices, _sVertices )
	{
		sPrimitives = _sPrimitives;
		ptType = _ptType;
	}

	text_t::text_t( int _iFont, int _x, int _y, const wchar_t *_wszText, bool _bOutlined, DWORD _dwFlags, DWORD _dwColor, DWORD _dwOutline ) : iFont( _iFont ), x( _x ), y( _y ), wstrText( _wszText ), bOutlined( _bOutlined ), dwFlags( _dwFlags ), dwColor( _dwColor ), dwOutline( _dwOutline )
	{ }

	module_t::module_t( wstr_t _wstrName )
	{
		wstrName = _wstrName;
		hModule = GetModuleHandle( wstrName.c_str( ) );
	}

	bool module_t::Succeeded( )
	{
		return hModule != nullptr;
	}

	ptr_t module_t::FindPattern( str_t strPattern )
	{
		const auto fnIDAPatternToBytes = [ = ]( )
		{
			std::vector< int > vecBytes { };
			auto iCurrentByteCount = 0;
			char szCurrentBytes[ 2 ] { };

			for each ( auto &ch in strPattern )
			{
				if ( ch == '?' )
					vecBytes.emplace_back( -1 );
				else if ( ch != ' ' )
				{
					szCurrentBytes[ iCurrentByteCount ] = ch;
					iCurrentByteCount++;
					if ( iCurrentByteCount == 2 )
					{
						char *szBuffer;
						vecBytes.emplace_back( strtol( szCurrentBytes, &szBuffer, 16 ) );
						iCurrentByteCount = 0;
					}
				}
			}
			return vecBytes;
		};

		const auto vecByteForm = fnIDAPatternToBytes( );
		for ( auto ptr = ptr_t( hModule ); ptr < GetModuleEnd( hModule ); ptr++ )
		{
			auto bFound = true;
			for ( auto u = 0u; u < vecByteForm.size( ); u++ )
			{
				auto iValue = vecByteForm[ u ];
				if ( iValue == -1 )
					continue;
				if ( *reinterpret_cast< byte_t * >( ptr + u ) != iValue )
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
			pColor = reinterpret_cast< UColor * >( initInput );
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
		for ( auto uu = 3u; uu >= u + 1; uu-- )
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
		for ( auto uu = 3u; uu >= u + 1; uu-- )
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
		const auto flFactor = pColor->b[ COLOR_ALPHA ] / 255.f;
		return D3DCOLOR_ARGB( pColor->b[ COLOR_ALPHA ], byte_t( pColor->b[ COLOR_RED ] * flFactor ), byte_t( pColor->b[ COLOR_GREEN ] * flFactor ), byte_t( pColor->b[ COLOR_BLUE ] * flFactor ) );
	}

	unsigned SColor::PutHex( const unsigned uValue ) const
	{
		return pColor->u = uValue;
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

	byte_t SColor::PutRed( const byte_t bValue ) const
	{
		return pColor->b[ COLOR_RED ] = bValue;
	}

	byte_t SColor::PutGreen( const byte_t bValue ) const
	{
		return pColor->b[ COLOR_GREEN ] = bValue;
	}

	byte_t SColor::PutBlue( const byte_t bValue ) const
	{
		return pColor->b[ COLOR_BLUE ] = bValue;
	}

	byte_t SColor::PutAlpha( const byte_t bValue ) const
	{
		return pColor->b[ COLOR_ALPHA ] = bValue;
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

	float SColor::PutRedFloat( const float flValue ) const
	{
		return PutRed( byte_t( flValue <= 1.f ? flValue * 255u : flValue ) );
	}

	float SColor::PutGreenFloat( const float flValue ) const
	{
		return PutGreen( byte_t( flValue <= 1.f ? flValue * 255u : flValue ) );
	}

	float SColor::PutBlueFloat( const float flValue ) const
	{
		return PutBlue( byte_t( flValue <= 1.f ? flValue * 255u : flValue ) );
	}

	float SColor::PutAlphaFloat( const float flValue ) const
	{
		return PutAlpha( byte_t( flValue <= 1.f ? flValue * 255u : flValue ) );
	}

	byte_t SColor::CalculateLuminance( ) const
	{
		return byte_t( 0.2126 * double( GetRed( ) ) + 0.7152 * double( GetGreen( ) ) + 0.0722 * double( GetBlue( ) ) );
	}

	byte_t SColor::operator[ ]( const int iColor ) const
	{
		return pColor->b[ iColor ];
	}

	float SColor::operator[ ]( const float flColor ) const
	{
		return float( pColor->b[ int( flColor ) ] ) / 255.f;
	}

	bool SColor::operator==( const SColor &rhs ) const
	{
		return this->Hex == rhs.Hex;
	}

	bool SColor::operator!=( const SColor &rhs ) const
	{
		return !( *this == rhs );
	}

	color_t SColorSequence::GetGradient( color_t clrStart, color_t clrEnd, float flProgress )
	{
		px_assert( flProgress >= 0.f && flProgress <= 1.f );
		return {
			clrStart.r + byte_t( ( clrEnd.r - clrStart.r ) * flProgress ),
			clrStart.g + byte_t( ( clrEnd.g - clrStart.g ) * flProgress ),
			clrStart.b + byte_t( ( clrEnd.b - clrStart.b ) * flProgress ),
			clrStart.a + byte_t( ( clrEnd.a - clrStart.a ) * flProgress )
		};
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

	SColorSequence::SColorSequence( ) PX_NOX
	{
		PutNewColorSequence( { 0, 0, 0, 255 }, 1000 );
	}

	SColorSequence::SColorSequence( color_t clrFirstSequence, moment_t mmtFirstSequence )
	{
		PutNewColorSequence( clrFirstSequence, mmtFirstSequence );
	}

	SColorSequence::SColorSequence( color_t *clrColors, moment_t *mmtDurations, std::size_t zSequences )
	{
		for ( std::size_t z = 0; z < zSequences; z++ )
		{
			PutNewColorSequence( clrColors[ z ], mmtDurations[ z ] );
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
		auto mmtCurrentProgress = GetMoment( ) / 10000ull % mmtTotalDuration;
		auto mmtPassedProgress = 0ull;

		for ( std::size_t z = 0u; z < zSequences; z++ )
			if ( sqInfo[ z ].mmtDuration < mmtCurrentProgress - mmtPassedProgress )
				mmtPassedProgress += sqInfo[ z ].mmtDuration;
			else
				return GetGradient( sqInfo[ z ].clrColor, sqInfo[ z + 1 != zSequences ? z + 1 : 0 ].clrColor,
									float( mmtCurrentProgress - mmtPassedProgress ) / float( sqInfo[ z ].mmtDuration ) );

		throw;
	}

	color_t &SColorSequence::GetColor( unsigned uColor )
	{
		px_assert( zSequences > uColor );
		return sqInfo[ uColor ].clrColor;
	}

	moment_t &SColorSequence::GetDuration( unsigned uDuration )
	{
		px_assert( zSequences > uDuration );
		return sqInfo[ uDuration ].mmtDuration;
	}

	void SColorSequence::PutNewColorSequence( const color_t &clrNewColor, moment_t mmtDuration )
	{
		if ( zSequences >= 7 )
			return; //review can we use? DeleteColorSequence( 0 );

		sqInfo[ zSequences ].clrColor = clrNewColor;
		sqInfo[ zSequences ].mmtDuration = mmtDuration;
		zSequences++;
	}

	void SColorSequence::DeleteColorSequence( unsigned uPosition )
	{
		px_assert( uPosition < zSequences );

		for ( auto s = uPosition; s < zSequences - 1; s++ )
		{
			sqInfo[ s ].clrColor = sqInfo[ s + 1 ].clrColor;
			sqInfo[ s ].mmtDuration = sqInfo[ s + 1 ].mmtDuration;
		}

		sqInfo[ zSequences - 1 ].clrColor = { };
		sqInfo[ zSequences - 1 ].mmtDuration = { };

		zSequences--;
	}
}
