/// Color.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#include "../../Framework.hpp"

color_t::color_t( )
{
	memset( &_Data, 0xFFFFFFFFui32, sizeof _Data );
}

color_t::color_t( unsigned uData )
{
	_Data.u = uData;
}

color_t::color_t( std::initializer_list< unsigned char > initData )
{
	if ( initData.size( ) == 0 || initData.size( ) > 4 )
		throw std::runtime_error( XOR( "Invalid array index" ) );

	auto u = 0u;
	for each ( const auto const &bData in initData )
	{
		_Data.b[ u ] = bData;
		u++;
	}
	for ( auto uu = 3u; uu >= u + 1; uu-- )
		_Data.b[ uu ] = UCHAR_MAX;
}

color_t::color_t( std::initializer_list< int > initData )
{
	if ( initData.size( ) == 0 )
	{
		memset( &_Data, 0xFFFFFFFFui32, sizeof _Data );
		return;
	}
	if ( initData.size( ) > 4 )
		throw std::runtime_error( XOR( "Invalid array index" ) );

	auto u = 0u;
	for each ( const auto const &iData in initData )
	{
		_Data.b[ u ] = iData;
		u++;
	}
	for ( auto uu = 3u; uu >= u + 1; uu-- )
		_Data.b[ uu ] = UCHAR_MAX;
}

color_t::color_t( std::initializer_list< float > initData )
{
	if ( initData.size( ) == 0 || initData.size( ) > 4 )
		throw std::runtime_error( XOR( "Invalid array index" ) );

	auto u = 0u;
	for each ( const auto const &flData in initData )
	{
		_Data.b[ u ] = flData > 1.f ? flData : flData * 255.f;
		u++;
	}
	for ( auto uu = 3u; uu >= u + 1; uu-- )
		_Data.b[ uu ] = UCHAR_MAX;
}

unsigned char color_t::operator[]( std::size_t zColor ) const
{
	if ( zColor > 3.f )
		throw std::runtime_error( XOR( "Invalid array index" ) );
	return _Data.b[ zColor ];
}

float color_t::operator[]( float flColor ) const
{
	if ( flColor < 0.f || flColor > 3.f )
		throw std::runtime_error( XOR( "Invalid array index" ) );
	return float( _Data.b[ int( floorf( flColor ) ) ] ) / 255.f;
}

bool color_t::operator==( const color_t &rhs ) const
{
	return _Data.u == rhs.GetRGBA( );
}

bool color_t::operator!=( const color_t &rhs ) const
{
	return !( *this == rhs );
}

color_t &color_t::operator=( const color_t &rhs )
{
	_Data.u = rhs.GetRGBA( );
	return *this;
}

unsigned color_t::GetRGBA( ) const
{
	return _Data.u;
}

unsigned color_t::GetARGB( ) const
{
	return _Data.b[ COLOR_ALPHA ] << 24 | _Data.b[ COLOR_RED ] << 16 | _Data.b[ COLOR_GREEN ] << 8 | _Data.b[ COLOR_BLUE ];
}

unsigned color_t::PutRGBA( unsigned uData )
{
	return _Data.u = uData;
}

unsigned color_t::PutARGB( unsigned uData )
{
	return _Data.u = uData & 0xFF000000 | ( uData & 0x00FF0000 ) << 8 | ( uData & 0x0000FF00 ) << 16 | ( uData & 0x000000FF ) << 24;
}

unsigned char color_t::GetRed( ) const
{
	return _Data.b[ COLOR_RED ];
}

unsigned char color_t::GetGreen( ) const
{
	return _Data.b[ COLOR_GREEN ];
}

unsigned char color_t::GetBlue( ) const
{
	return _Data.b[ COLOR_BLUE ];
}

unsigned char color_t::GetAlpha( ) const
{
	return _Data.b[ COLOR_ALPHA ];
}

unsigned char color_t::PutRed( unsigned char bData )
{
	return _Data.b[ COLOR_RED ] = bData;
}

unsigned char color_t::PutGreen( unsigned char bData )
{
	return _Data.b[ COLOR_GREEN ] = bData;
}

unsigned char color_t::PutBlue( unsigned char bData )
{
	return _Data.b[ COLOR_BLUE ] = bData;
}

unsigned char color_t::PutAlpha( unsigned char bData )
{
	return _Data.b[ COLOR_ALPHA ] = bData;
}

float color_t::GetRedFraction( ) const
{
	return float( _Data.b[ COLOR_RED ] ) / 255.f;
}

float color_t::GetGreenFraction( ) const
{
	return float( _Data.b[ COLOR_GREEN ] ) / 255.f;
}

float color_t::GetBlueFraction( ) const
{
	return float( _Data.b[ COLOR_BLUE ] ) / 255.f;
}

float color_t::GetAlphaFraction( ) const
{
	return float( _Data.b[ COLOR_ALPHA ] ) / 255.f;
}

float color_t::PutRedFraction( float flData )
{
	return _Data.b[ COLOR_RED ] = flData * 255.f;
}

float color_t::PutGreenFraction( float flData )
{
	return _Data.b[ COLOR_GREEN ] = flData * 255.f;
}

float color_t::PutBlueFraction( float flData )
{
	return _Data.b[ COLOR_BLUE ] = flData * 255.f;
}

float color_t::PutAlphaFraction( float flData )
{
	return _Data.b[ COLOR_ALPHA ] = flData * 255.f;
}

void *color_t::GetDataPointer( ) const
{
	return static_cast< void* >( const_cast< decltype( _Data ) * >( &_Data ) );
}

double color_t::Get709Luminance( ) const
{
	return _Data.b[ COLOR_ALPHA ] * ( 0.2126 * _Data.b[ COLOR_RED ] + 0.7152 * _Data.b[ COLOR_GREEN ] + 0.0722 * _Data.b[ COLOR_BLUE ] );
}

double color_t::Get601Luminance( ) const
{
	return _Data.b[ COLOR_ALPHA ] * ( 0.299 * _Data.b[ COLOR_RED ] + 0.587 * _Data.b[ COLOR_GREEN ] + 0.114 * _Data.b[ COLOR_BLUE ] );
}

color_t CColor::GetGradient( color_t clrStart, color_t clrEnd, float flProgress )
{
	return
	{
		clrStart.r + unsigned char( ( clrEnd.r - clrStart.r ) * flProgress ),
		clrStart.g + unsigned char( ( clrEnd.g - clrStart.g ) * flProgress ),
		clrStart.b + unsigned char( ( clrEnd.b - clrStart.b ) * flProgress ),
		clrStart.a + unsigned char( ( clrEnd.a - clrStart.a ) * flProgress )
	};
}

CColor::CColor( color_t clrFirstSequence, Utilities::moment_t mmtFirstSequence )
{
	pSequences[ 0 ].clr = clrFirstSequence;
	pSequences[ 0 ].mmtDuration = mmtFirstSequence;
	zSequences = 1;
}

CColor::CColor( std::vector< sequence_t > vecSequences )
{
	if ( vecSequences.empty( ) )
		throw std::runtime_error( XOR( "Invalid array index" ) );

	zSequences = vecSequences.size( );

	auto u = 0u;
	for each ( auto &seq in vecSequences )
		pSequences[ u ] = seq;
}

color_t CColor::GetColor( )
{
	if ( zSequences == 0 )
		throw std::runtime_error( XOR( "Invalid array index" ) );

	if ( zSequences == 1 )
		return pSequences[ 0 ].clr;

	mmtTotalDuration = 0;
	for ( std::size_t z = 0u; z < zSequences; z++ )
		mmtTotalDuration += pSequences[ z ].mmtDuration;
	auto mmtCurrentProgress = GetMoment( ) / 10000ull % mmtTotalDuration;
	auto mmtPassedProgress = 0ull;

	for ( std::size_t z = 0u; z < zSequences; z++ )
		if ( pSequences[ z ].mmtDuration < mmtCurrentProgress - mmtPassedProgress )
			mmtPassedProgress += pSequences[ z ].mmtDuration;
		else
			return GetGradient( pSequences[ z ].clr, pSequences[ z + 1 != zSequences ? z + 1 : 0 ].clr,
								float( mmtCurrentProgress - mmtPassedProgress ) / float( pSequences[ z ].mmtDuration ) );

	throw std::runtime_error( XOR( "Invalid array index" ) );
}

CColor::sequence_t CColor::GetSequence( std::size_t zSequence )
{
	if ( zSequences <= zSequence )
		throw std::runtime_error( XOR( "Invalid array index" ) );

	return pSequences[ zSequence ];
}

CColor::sequence_t CColor::operator[]( std::size_t zSequence )
{
	return GetSequence( zSequence );
}

void CColor::PutNewColorSequence( sequence_t seq )
{
	if ( zSequences == 7 )
		return;

	pSequences[ zSequences ] = seq;
	zSequences++;
}

CColor &CColor::operator<<( sequence_t seq )
{
	PutNewColorSequence( seq );
	return *this;
}

void CColor::DeleteColorSequence( std::size_t zSequence )
{
	for ( auto s = zSequence; s < zSequences - 1; s++ )
	{
		pSequences[ s ].clr = pSequences[ s + 1 ].clr;
		pSequences[ s ].mmtDuration = pSequences[ s + 1 ].mmtDuration;
	}

	pSequences[ zSequences - 1 ].clr = { };
	pSequences[ zSequences - 1 ].mmtDuration = { };

	zSequences--;
}

CColor &CColor::operator>>( std::size_t zSequence )
{
	DeleteColorSequence( zSequence );
	return *this;
}