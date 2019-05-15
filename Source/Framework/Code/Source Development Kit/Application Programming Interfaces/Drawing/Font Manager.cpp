/// Font Manager.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#define USE_DEFINITIONS
#include "../../../Framework.hpp"

bitmap_t::bitmap_t( unsigned char* pData, std::size_t zData, const Utilities::vector2_t& vecSize ):
	vecSize( vecSize )
{
	if ( std::size_t( vecSize.x * vecSize.y ) != zData )
		throw std::runtime_error( ENC( "Invalid bitmap dimensions." ) );

	vecBytes.resize( zData );
	memcpy( &vecBytes[ 0 ], pData, zData );
}

bitmap_t::bitmap_t( const std::vector< unsigned char > & vecBytes, const Utilities::vector2_t & vecSize ):
	vecBytes( vecBytes ), vecSize( vecSize )
{
	if ( std::size_t( vecSize.x * vecSize.y ) != vecBytes.size( ) )
		throw std::runtime_error( ENC( "Invalid bitmap dimensions." ) );
}

std::size_t bitmap_t::GetBitIndex( unsigned x, unsigned y ) const
{
	return y * std::size_t( vecSize.x ) + x;
}

void bitmap_t::ConcatenateHorizontal( const bitmap_t& _Other )
{
	if ( vecSize.y != _Other.vecSize.y )
		throw std::runtime_error( ENC( "Invalid bitmap dimensions." ) );

	const auto zOldWidth = std::size_t( vecSize.x );
	const auto vecOldBytes = vecBytes;

	vecSize.x += _Other.vecSize.x;
	vecBytes.resize( std::size_t( vecSize.x * vecSize.y ) );

	for ( auto y = 0u; y < std::size_t( vecSize.y ); y++ )
		for ( auto x = 0u; x < std::size_t( vecSize.x ); x++ )
		{
			unsigned char bNewValue;

			if ( x > zOldWidth )
				bNewValue = _Other.vecBytes[ _Other.GetBitIndex( x - zOldWidth, y ) ];
			else
			{
				const auto zIndex = std::size_t( y * zOldWidth + x );
				bNewValue = vecOldBytes[ zIndex ];
			}

			vecBytes[ GetBitIndex( x, y ) ] = bNewValue;
		}
}

void bitmap_t::ConcatenateVertical( const bitmap_t & _Other )
{
	if ( vecSize.x != _Other.vecSize.x )
		throw std::runtime_error( ENC( "Invalid bitmap dimensions." ) );
	throw std::exception( );
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

		if ( FT_New_Memory_Face( _Instance, reinterpret_cast< unsigned char* >( strData[ 0 ] ), strData.size( ), 0, &_Fonts[ i ] ) != 0 )
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

vector2_t CFontManager::CalculateTextSize( char *szText, EFont _Font, double dbSize )
{
	
}

bitmap_t CFontManager::CreateBitmap( char *szText, EFont _Font, double dbSize, color_t clrText )
{
	
}
