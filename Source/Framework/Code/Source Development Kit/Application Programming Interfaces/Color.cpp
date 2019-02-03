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

color_t::color_t( std::initializer_list<unsigned char> initData )
{
	if ( initData.size( ) > 4 )
		throw std::runtime_error( XOR( "Invalid array index" ) );

	auto u = 0u;
	for each ( const auto const& bData in initData )
	{
		_Data.b[ u ] = bData;
		u++;
	}
	for ( auto uu = 3u; uu >= u + 1; uu-- )
		_Data.b[ uu ] = UCHAR_MAX;
}

color_t::color_t( std::initializer_list<int> initData )
{
	if ( initData.size( ) > 4 )
		throw std::runtime_error( XOR( "Invalid array index" ) );

	auto u = 0u;
	for each ( const auto const& iData in initData )
	{
		_Data.b[ u ] = iData;
		u++;
	}
	for ( auto uu = 3u; uu >= u + 1; uu-- )
		_Data.b[ uu ] = UCHAR_MAX;
}

color_t::color_t( std::initializer_list<float> initData )
{
	if ( initData.size( ) > 4 )
		throw std::runtime_error( XOR( "Invalid array index" ) );

	auto u = 0u;
	for each ( const auto const& flData in initData )
	{
		_Data.b[ u ] = flData > 1.f ? flData : flData * 255.f;
		u++;
	}
	for ( auto uu = 3u; uu >= u + 1; uu-- )
		_Data.b[ uu ] = UCHAR_MAX;
}

unsigned char color_t::operator[]( int iColor ) const
{
	if ( iColor < 0.f || iColor > 3.f )
		throw std::runtime_error( XOR( "Invalid array index" ) );
	return _Data.b[ iColor ];
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

unsigned color_t::GetRGBA( ) const
{
	return _Data.u;
}

unsigned color_t::GetARGB( ) const
{
	return _Data.b[ COLOR_ALPHA ] << 24 | _Data.b[ COLOR_RED ] << 16 | _Data.b[ COLOR_GREEN ] << 8 | _Data.b[ COLOR_BLUE ];
}

void color_t::PutRGBA( unsigned uData )
{
	_Data.u = uData;
}

void color_t::PutARGB( unsigned uData )
{
	_Data.u = uData & 0xFF000000 | ( uData & 0x00FF0000 ) << 8 | ( uData & 0x0000FF00 ) << 16 | ( uData & 0x000000FF ) << 24;
}

unsigned char color_t::GetRed( ) const
{
	return _Data.b[ COLOR_RED ];
}

unsigned char color_t::GetGreen( )const
{
	return _Data.b[ COLOR_GREEN ];
}

unsigned char color_t::GetBlue( )const
{
	return _Data.b[ COLOR_BLUE ];
}

unsigned char color_t::GetAlpha( )const
{
	return _Data.b[ COLOR_ALPHA ];
}

void color_t::PutRed( unsigned char bData )
{
	_Data.b[ COLOR_RED ] = bData;
}

void color_t::PutGreen( unsigned char bData )
{
	_Data.b[ COLOR_GREEN ] = bData;
}

void color_t::PutBlue( unsigned char bData )
{
	_Data.b[ COLOR_BLUE ] = bData;
}

void color_t::PutAlpha( unsigned char bData )
{
	_Data.b[ COLOR_ALPHA ] = bData;
}

float color_t::GetRedFraction( )const
{
	return float( _Data.b[ COLOR_RED ] ) / 255.f;
}

float color_t::GetGreenFraction( )const
{
	return float( _Data.b[ COLOR_GREEN ] ) / 255.f;
}

float color_t::GetBlueFraction( )const
{
	return float( _Data.b[ COLOR_BLUE ] ) / 255.f;
}

float color_t::GetAlphaFraction( )const
{
	return float( _Data.b[ COLOR_ALPHA ] ) / 255.f;
}

void color_t::PutRedFraction( float flData )
{
	_Data.b[ COLOR_RED ] = flData * 255.f;
}

void color_t::PutGreenFraction( float flData )
{
	_Data.b[ COLOR_GREEN ] = flData * 255.f;
}

void color_t::PutBlueFraction( float flData )
{
	_Data.b[ COLOR_BLUE ] = flData * 255.f;
}

void color_t::PutAlphaFraction( float flData )
{
	_Data.b[ COLOR_ALPHA ] = flData * 255.f;
}

void *color_t::GetDataPointer( )const
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
