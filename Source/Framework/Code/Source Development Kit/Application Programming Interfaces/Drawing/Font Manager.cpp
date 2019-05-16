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

void bitmap_t::Resize( const vector2_t &vecNewSize )
{
	const auto _OldBitmap = *this;

	vecSize = vecNewSize;
	vecBytes.resize( std::size_t( vecSize.x * vecSize.y ) );

	for ( auto y = 0u; y < std::size_t( vecSize.y )
		  && y < std::size_t( _OldBitmap.vecSize.y ); y++ )
		for ( auto x = 0u; x < std::size_t( vecSize.x )
			  && x < std::size_t( _OldBitmap.vecSize.x ); x++ )
			vecBytes[ GetBitIndex( x, y ) ] = _OldBitmap.vecBytes[ _OldBitmap.GetBitIndex( x, y ) ];
}

void bitmap_t::Insert( const vector2_t &vecLocation, const bitmap_t &_Other )
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
			vecBytes[ GetBitIndex( x + std::size_t( vecLocation.x ), y + std::size_t( vecLocation.y ) ) ] = _Other.vecBytes[ _Other.GetBitIndex( x, y ) ];
}

void bitmap_t::ConcatenateHorizontal( const bitmap_t& _Other )
{
	Insert( { vecSize.x, 0.0 }, _Other );
}

void bitmap_t::ConcatenateVertical( const bitmap_t & _Other )
{
	Insert( { 0.0, vecSize.y }, _Other );
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

bitmap_t CFontManager::CreateBitmap( char *szText, EFont _Font, double dbSize )
{
	const auto vecDPI = GetScreenDPI( );
	bitmap_t _Return { };
	auto uAdvance = 0u, uPreviousIndex = 0u;

	_CurrentFont = _Fonts[ _Font ];
	FT_Set_Char_Size( _CurrentFont, 0, std::size_t( dbSize ) << 6, int( vecDPI.x ), int( vecDPI.y ) );

	while ( *szText != 0 )
	{
		FT_Vector vecKerning { };
		szText = RenderGlyph( szText );

		if ( uPreviousIndex != 0u )
			FT_Get_Kerning( _CurrentFont, uPreviousIndex, _CurrentFont->glyph->glyph_index, FT_KERNING_DEFAULT, &vecKerning );

		_Return.Insert( { double( uAdvance + ( vecKerning.x >> 6 ) ), dbSize - double( _CurrentFont->glyph->bitmap_top ) }, 
						{ _CurrentFont->glyph->bitmap.buffer, { double( _CurrentFont->glyph->bitmap.width ), double( _CurrentFont->glyph->bitmap.rows ) } } );

		uAdvance += _CurrentFont->glyph->advance.x >> 6;
		uPreviousIndex = _CurrentFont->glyph->glyph_index;
	}

	for ( auto y = 0; y < (int)_Return.vecSize.y; y++ )
	{
		for ( auto x = 0; x < (int) _Return.vecSize.x; x++ )
			std::cout << ( _Return.vecBytes[ y * (int)_Return.vecSize.x + x ] > 0 ) ? '8' : '0';

		std::cout << std::endl;
	}

	return _Return;
}

vector2_t CFontManager::CalculateTextSize( char* szText, EFont _Font, double dbSize )
{
	return CreateBitmap( szText, _Font, dbSize ).vecSize;
}
