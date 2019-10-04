/// Font Manager.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#define USE_DEFINITIONS
#include "../../../Framework.hpp"

bitmap_t::bitmap_t( unsigned char *pData, const Utilities::vector2_t &vecSize ):
	vecSize( vecSize )
{
	const auto zData = std::size_t( vecSize.x * vecSize.y );

	vecBytes.resize( zData );
	memcpy( &vecBytes[ 0 ], pData, zData );
}

bitmap_t::bitmap_t( const std::vector< unsigned char > &vecBytes, const Utilities::vector2_t &vecSize ):
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

std::vector< DWORD > bitmap_t::GetColoredBitmapBytes( DWORD dwRBGA ) const
{
	std::vector< DWORD > vecBitmap { };

	vecBitmap.resize( vecBytes.size( ) );
	for ( auto z = 0u; z < vecBitmap.size( ); z++ )
	{
		const auto bAlpha = unsigned char( double( vecBytes[ z ] ) / 255.0 * double( ( dwRBGA & 0xFF000000 ) >> 24 ) );
		if ( bAlpha > 0 )
			vecBitmap[ z ] = ( dwRBGA & 0x00FFFFFF ) | ( bAlpha << 24 );
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

void bitmap_t::ConcatenateHorizontal( const bitmap_t &_Other )
{
	Insert( { vecSize.x, 0.0 }, _Other );
}

void bitmap_t::ConcatenateVertical( const bitmap_t &_Other )
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
	if ( uMagnitude >= std::size_t( vecSize.y )
		|| uMagnitude == 0 )
		return;

	const auto _OldBitmap = *this;
	memset( &vecBytes[ 0 ], 0, vecBytes.size( ) );

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

	while ( VerticalRowEmpty( std::size_t( vecSize.x ) - uHorizontalClipping - 1 ) )
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
		for ( auto u = 0; u < WEIGHT_MAX; u++ )
			for ( auto b = 0; b < 2; b++ )
			{
				auto strFontDirectory = strRelativeFontDirectory + strFontDirectories[ i ] + strWeightTitles[ u ];

				if ( b )
					strFontDirectory += strItalicizedSuffix;

				strFontDirectory += strFontFileExtension;
				const auto &strData = RESOURCES.GetResource( strFontDirectory );

				if ( strData.empty( ) )
					return LOG( ERROR, DRAWING, "Unable to get font %s. Italicized: %i.", ( strFontDirectories[ i ] + strWeightTitles[ u ] ).c_str( ), b ), false;

				if ( FT_New_Memory_Face( _Instance, reinterpret_cast< unsigned char* >( const_cast< char* >( &strData[ 0 ] ) ), strData.size( ), 0, &_Fonts[ i ][ u ][ b ] ) != 0 )
					return LOG( ERROR, DRAWING, "Unable to add font %s. Italicized: %i.", ( strFontDirectories[ i ] + strWeightTitles[ u ] ).c_str( ), b ), false;
			}

	return true;
}

void CFontManager::Uninitialize( )
{
	for ( auto &_Font: _Fonts )
		for ( auto &_Weights: _Font )
			for ( auto &_Face: _Weights )
				FT_Done_Face( _Face );

	FT_Done_FreeType( _Instance );
}

char *CFontManager::RenderGlyph( char *szText )
{
	const auto uCharacterIndex = FT_Get_Char_Index( _CurrentFont, *szText );

	FT_Load_Glyph( _CurrentFont, uCharacterIndex, FT_LOAD_DEFAULT );
	FT_Render_Glyph( _CurrentFont->glyph, FT_RENDER_MODE_NORMAL );
	return szText + 1;
}

bitmap_t CFontManager::CreateBitmap( char *szText, EFont _Font, EFontWeight _Weight, bool bItalic, double dbSize )
{
	const auto vecDPI = GetScreenDPI( );
	bitmap_t _Return { };
	auto uAdvance = 0u, uPreviousIndex = 0u;
	auto dbVerticalOffset = 0.0;

	_CurrentFont = _Fonts[ _Font ][ _Weight ][ bItalic ];

	FT_Set_Char_Size( _CurrentFont, 0, std::size_t( dbSize ) << 6, int( vecDPI.x ), int( vecDPI.y ) );

	while ( *szText != 0 )
	{
		FT_Vector vecKerning { };
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
				uAdvance += dbHorizontalLocation * 2.0;
			}

			if ( dbCurrentVerticalOffset < 0.0 )
			{
				dbCurrentVerticalOffset *= -1.0;
				dbVerticalOffset += dbCurrentVerticalOffset;
				_Return.Resize( { _Return.vecSize.x, _Return.vecSize.y + dbCurrentVerticalOffset } );
				if ( uPreviousIndex )
					_Return.ShiftDownward( std::size_t( dbCurrentVerticalOffset ) );
			}

			_Return.Insert( { dbHorizontalLocation, dbCurrentVerticalOffset },
							{ _CurrentFont->glyph->bitmap.buffer, { double( _CurrentFont->glyph->bitmap.width ), double( _CurrentFont->glyph->bitmap.rows ) } } );
			uPreviousIndex = _CurrentFont->glyph->glyph_index;
		}
		uAdvance += _CurrentFont->glyph->advance.x >> 6;
	}

	_Return.Clip( );
	return _Return;
}

vector2_t CFontManager::CalculateTextSize( char *szText, EFont _Font, EFontWeight _Weight, bool bItalic, double dbSize )
{
	return CreateBitmap( szText, _Font, _Weight, bItalic, dbSize ).vecSize;
}
