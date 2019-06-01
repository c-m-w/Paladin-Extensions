/// Font Manager.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#define USE_DEFINITIONS
#include "../../../Framework.hpp"

bitmap_t::bitmap_t( unsigned char* pData, const Utilities::vector2_t& vecSize ):
	vecSize( vecSize )
{
	const auto zData = std::size_t( vecSize.x * vecSize.y );

	vecBytes.resize( zData );
	memcpy( &vecBytes[ 0 ], pData, zData );
}

bitmap_t::bitmap_t( const std::vector< unsigned char > & vecBytes, const Utilities::vector2_t & vecSize ):
	vecBytes( vecBytes ), vecSize( vecSize )
{
	if ( std::size_t( vecSize.x * vecSize.y ) != vecBytes.size( ) )
		throw std::runtime_error( ENC( "Invalid bitmap dimensions." ) );
}

bitmap_t::bitmap_t( const vector2_t &vecSize ) :
	vecSize( vecSize )
{
	vecBytes.resize( std::size_t( vecSize.x * vecSize.y ) );
}

std::size_t bitmap_t::GetBitIndex( unsigned x, unsigned y ) const
{
	return y * std::size_t( vecSize.x ) + x;
}

std::vector< DWORD > bitmap_t::GetColoredBitmapBytes( DWORD dwARGB ) const
{
	std::vector< DWORD > vecBitmap { };

	vecBitmap.resize( vecBytes.size( ) );
	for ( auto z = 0u; z < vecBitmap.size( ); z++ )
	{
		const auto bAlpha = unsigned char( double( vecBytes[ z ] ) / 255.0 * double( dwARGB & 0xFF ) );
		if ( bAlpha > 0 )
			vecBitmap[ z ] = ( dwARGB & 0x00FFFFFF ) | ( bAlpha << 24 );
	}
	
	return vecBitmap;
}

void bitmap_t::Resize( const vector2_t &vecNewSize )
{
	const auto _OldBitmap = *this;

	vecSize = vecNewSize;
	vecBytes.clear( );
	vecBytes.resize( std::size_t( vecSize.x * vecSize.y ) );

	for ( auto y = 0u; y < std::size_t( vecSize.y )
		  && y < std::size_t( _OldBitmap.vecSize.y ); y++ )
		for ( auto x = 0u; x < std::size_t( vecSize.x )
			  && x < std::size_t( _OldBitmap.vecSize.x ); x++ )
			vecBytes[ GetBitIndex( x, y ) ] = _OldBitmap.vecBytes[ _OldBitmap.GetBitIndex( x, y ) ];
}

void bitmap_t::Insert( vector2_t vecLocation, const bitmap_t &_Other )
{
	vector2_t vecDifference { vecSize.x - ( vecLocation.x + _Other.vecSize.x ), vecSize.y - ( vecLocation.y + _Other.vecSize.y ) };

	if ( vecDifference.x < 0.0
		 || vecDifference.y < 0.0 )
	{
		if ( vecDifference.x > 0.0 )
			vecDifference.x = 0.0;
		else
			vecDifference.x = -vecDifference.x;

		if ( vecDifference.y > 0.0 )
			vecDifference.y = 0.0;
		else
			vecDifference.y = -vecDifference.y;

		Resize( vecSize + vecDifference );
	}

	for ( auto y = 0u; y < std::size_t( _Other.vecSize.y ); y++ )
		for ( auto x = 0u; x < std::size_t( _Other.vecSize.x ); x++ )
			if ( _Other.vecBytes[ _Other.GetBitIndex( x, y ) ] > 0 )
				vecBytes[ GetBitIndex( x + std::size_t( vecLocation.x ), y + std::size_t( vecLocation.y ) ) ] |= _Other.vecBytes[ _Other.GetBitIndex( x, y ) ];
}

void bitmap_t::ConcatenateHorizontal( const bitmap_t& _Other )
{
	Insert( { vecSize.x, 0.0 }, _Other );
}

void bitmap_t::ConcatenateVertical( const bitmap_t & _Other )
{
	Insert( { 0.0, vecSize.y }, _Other );
}

void bitmap_t::ShiftUpward( unsigned uMagnitude )
{
	const auto _OldBitmap = *this;
	memset( &vecBytes[ 0 ], 0, vecBytes.size( ) );

	if ( uMagnitude >= std::size_t( vecSize.y ) )
		return;

	for ( auto y = uMagnitude; y < std::size_t( vecSize.y ); y++ )
		for ( auto x = 0u; x < std::size_t( vecSize.x ); x++ )
			vecBytes[ GetBitIndex( x, y - uMagnitude ) ] = _OldBitmap.vecBytes[ _OldBitmap.GetBitIndex( x, y ) ];
}

void bitmap_t::ShiftDownward( unsigned uMagnitude )
{
	const auto _OldBitmap = *this;
	memset( &vecBytes[ 0 ], 0, vecBytes.size( ) );

	if ( uMagnitude >= std::size_t( vecSize.y ) )
		return;

	for ( auto y = std::size_t( vecSize.y ) - 1; y >= uMagnitude; y-- )
		for ( auto x = 0u; x < std::size_t( vecSize.x ); x++ )
			vecBytes[ GetBitIndex( x, y ) ] = _OldBitmap.vecBytes[ _OldBitmap.GetBitIndex( x, y - uMagnitude ) ];
}

void bitmap_t::ShiftLeftward( unsigned uMagnitude )
{
	const auto _OldBitmap = *this;
	memset( &vecBytes[ 0 ], 0, vecBytes.size( ) );

	if ( uMagnitude >= std::size_t( vecSize.x ) )
		return;

	for ( auto x = uMagnitude; x < std::size_t( vecSize.x ); x++ )
		for ( auto y = 0u; y < std::size_t( vecSize.y ); y++ )
			vecBytes[ GetBitIndex( x - uMagnitude, y ) ] = _OldBitmap.vecBytes[ _OldBitmap.GetBitIndex( x, y ) ];
}

void bitmap_t::ShiftRightward( unsigned uMagnitude )
{
	const auto _OldBitmap = *this;
	memset( &vecBytes[ 0 ], 0, vecBytes.size( ) );

	if ( uMagnitude >= std::size_t( vecSize.x ) )
		return;

	for ( auto x = std::size_t( vecSize.x ) - 1; x <= uMagnitude; x-- )
		for ( auto y = 0u; y < std::size_t( vecSize.y ); y++ )
			vecBytes[ GetBitIndex( x, y ) ] = _OldBitmap.vecBytes[ _OldBitmap.GetBitIndex( x - uMagnitude, y ) ];
}

bool bitmap_t::VerticalRowEmpty( unsigned uRow )
{
	if ( uRow >= std::size_t( vecSize.x ) )
		return false;

	auto bReturn = true;

	for ( auto y = 0u; y < std::size_t( vecSize.y )
		  && bReturn; y++ )
		bReturn &= !vecBytes[ GetBitIndex( uRow, y ) ];

	return bReturn;
}

bool bitmap_t::HorizontalRowEmpty( unsigned uRow )
{
	if ( uRow >= std::size_t( vecSize.y ) )
		return false;

	auto bReturn = true;

	for ( auto x = 0u; x < std::size_t( vecSize.x )
		  && bReturn; x++ )
		bReturn &= !vecBytes[ GetBitIndex( x, uRow ) ];

	return bReturn;
}

void bitmap_t::Clip( )
{
	auto uVerticalClipping = 0u, uHorizontalClipping = 0u;

	while ( VerticalRowEmpty( 0 ) )
		ShiftLeftward( 1 ), uHorizontalClipping++;

	while ( VerticalRowEmpty( std::size_t( vecSize.x ) - uHorizontalClipping - 1) )
		uHorizontalClipping++;

	while ( HorizontalRowEmpty( 0 ) )
		ShiftUpward( 1 ), uVerticalClipping;

	while ( HorizontalRowEmpty( std::size_t( vecSize.y ) - uVerticalClipping - 1 ) )
		uVerticalClipping++;

	Resize( vecSize - vector2_t( double( uHorizontalClipping ), double( uVerticalClipping ) ) );
}

bool CFontManager::Initialize( )
{
	if ( FT_Init_FreeType( &_Instance ) != 0 )
		return LOG( ERROR, DRAWING, "Unable to initialize freetype." ), false;

	for ( auto i = 0; i < FONT_MAX; i++ )
	{
		const auto& strFont = strFonts[ i ];
		const auto& strData = RESOURCES.GetResource( strFont );
		if ( strData.empty( ) )
			return LOG( ERROR, DRAWING, "Unable to get font %s.", strFont.c_str( ) ), false;

		if ( FT_New_Memory_Face( _Instance, reinterpret_cast< unsigned char* >( const_cast< char* >( &strData[ 0 ] ) ), strData.size( ), 0, &_Fonts[ i ] ) != 0 )
			return LOG( ERROR, DRAWING, "UNable to add font %s.", strFont.c_str( ) ), false;
	}

	return true;
}

void CFontManager::Uninitialize( )
{
	for ( auto& _Face : _Fonts )
		FT_Done_Face( _Face );

	FT_Done_FreeType( _Instance );
}

char* CFontManager::RenderGlyph( char* szText )
{
	if ( *reinterpret_cast< unsigned short* >( szText ) == ICON_SIGNATURE )
	{
		szText += sizeof( unsigned short );
		const auto uCharacterIndex = FT_Get_Char_Index( _Fonts[ FONT_ICON ], *szText );
		FT_Load_Glyph( _Fonts[ FONT_ICON ], uCharacterIndex, FT_LOAD_DEFAULT );
	}
	else
	{
		const auto uCharacterIndex = FT_Get_Char_Index( _CurrentFont, *szText );
		FT_Load_Glyph( _CurrentFont, uCharacterIndex, FT_LOAD_DEFAULT );
	}

	FT_Render_Glyph( _CurrentFont->glyph, FT_RENDER_MODE_NORMAL );
	return szText + 1;
}

bitmap_t CFontManager::CreateBitmap( char *szText, EFont _Font, double dbSize, double dbRotation )
{
	const auto vecDPI = GetScreenDPI( );
	FT_Matrix _RotationMatrix { };
	bitmap_t _Return { };
	auto uAdvance = 0u, uPreviousIndex = 0u;
	auto dbVerticalOffset = 0.0;

	dbRotation /= 180.0;
	dbRotation *= vector2_t::PI;
	_CurrentFont = _Fonts[ _Font ];
	_RotationMatrix.xx = FT_Fixed( cos( dbRotation ) * 0x10000 );
	_RotationMatrix.xy = FT_Fixed( -sin( dbRotation ) * 0x10000 );
	_RotationMatrix.yx = FT_Fixed( sin( dbRotation ) * 0x10000 );
	_RotationMatrix.yy = FT_Fixed( cos( dbRotation ) * 0x10000 );

	FT_Set_Char_Size( _CurrentFont, 0, std::size_t( dbSize ) << 6, int( vecDPI.x ), int( vecDPI.y ) );

	while ( *szText != 0 )
	{
		FT_Vector vecKerning { };
		FT_Set_Transform( _CurrentFont, &_RotationMatrix, nullptr );
		szText = RenderGlyph( szText );

		if ( uPreviousIndex != 0u )
			FT_Get_Kerning( _CurrentFont, uPreviousIndex, _CurrentFont->glyph->glyph_index, FT_KERNING_DEFAULT, &vecKerning );

		uAdvance += vecKerning.x >> 6;
		if ( _CurrentFont->glyph->bitmap.buffer != nullptr )
		{
			auto dbHorizontalLocation = double( uAdvance ) + double( _CurrentFont->glyph->bitmap_left );
			auto dbCurrentVerticalOffset = dbSize - double( _CurrentFont->glyph->bitmap_top ) + dbVerticalOffset;

			if ( dbHorizontalLocation < 0.0 )
			{
				_Return.Resize( { _Return.vecSize.x - dbHorizontalLocation, _Return.vecSize.y } );
				dbHorizontalLocation *= -1.0;
				uAdvance += dbHorizontalLocation;
			}

			if ( dbCurrentVerticalOffset < 0.0 )
			{
				dbCurrentVerticalOffset *= -1.0;
				dbVerticalOffset += dbCurrentVerticalOffset;
				_Return.Resize( { _Return.vecSize.x, _Return.vecSize.y + dbCurrentVerticalOffset } );
				_Return.ShiftDownward( std::size_t( dbCurrentVerticalOffset ) );
			}

			_Return.Insert( { dbHorizontalLocation, dbCurrentVerticalOffset },
							{ _CurrentFont->glyph->bitmap.buffer, { double( _CurrentFont->glyph->bitmap.width ), double( _CurrentFont->glyph->bitmap.rows ) } } );
			uAdvance += std::max( int( _CurrentFont->glyph->advance.x >> 6 ), int( dbHorizontalLocation ) - int( uAdvance ) + int( _CurrentFont->bbox.xMax - _CurrentFont->bbox.xMin >> 6 ) );
			uPreviousIndex = _CurrentFont->glyph->glyph_index;
		}
	}

	_Return.Clip( );
	return _Return;
}

vector2_t CFontManager::CalculateTextSize( char* szText, EFont _Font, double dbSize, double dbRotation )
{
	return CreateBitmap( szText, _Font, dbSize, dbRotation ).vecSize;
}
