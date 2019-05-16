/// Font Manager.hpp

#pragma once

enum EFont
{
	FONT_TAHOMA,
	FONT_TAHOMA_BOLD,
	FONT_ROBOTO,
	FONT_ROBOTO_BOLD,
	FONT_ENVY,
	FONT_ICON,
	FONT_MAX
};

struct bitmap_t
{
	std::vector< unsigned char > vecBytes { };
	Utilities::vector2_t vecSize { };

	bitmap_t( ) = default;
	bitmap_t( unsigned char* pData, const Utilities::vector2_t& vecSize );
	bitmap_t( const std::vector< unsigned char >& vecBytes, const Utilities::vector2_t& vecSize );
	bitmap_t( const Utilities::vector2_t& vecSize );

	[ [ nodiscard ] ] std::size_t GetBitIndex( unsigned x, unsigned y ) const;
	void Resize( const Utilities::vector2_t& vecNewSize );
	void Insert( const Utilities::vector2_t& vecLocation, const bitmap_t& _Other );
	void ConcatenateHorizontal( const bitmap_t& _Other );
	void ConcatenateVertical( const bitmap_t& _Other );
};

struct glyph_t
{
	
};

class CFontManager: public IBase
{
private:

	constexpr static unsigned short ICON_SIGNATURE = 0xFF69;

	bool Initialize( ) override;
	void Uninitialize( ) override;

	char* RenderGlyph( char* szText );

	const std::string strFonts[ FONT_MAX ]
	{
		ENC( "Fonts\\Tahoma.ttf" ),
		ENC( "Fonts\\Tahoma Bold.ttf" ),
		ENC( "Fonts\\Roboto.ttf" ),
		ENC( "Fonts\\Roboto Bold.ttf" ),
		ENC( "Fonts\\Envy.ttf" ),
		ENC( "Fonts\\Icon.ttf" )
	};
	FT_Library _Instance = nullptr;
	FT_Face _Fonts[ FONT_MAX ] { }, _CurrentFont { };

public:

	bitmap_t CreateBitmap( char* szText, EFont _Font, double dbSize );
	Utilities::vector2_t CalculateTextSize( char* szText, EFont _Font, double dbSize );
} inline _FontManager;
