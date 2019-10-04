/// Font Manager.hpp

#pragma once

enum EFont
{
	FONT_OPEN_SANS,
	FONT_ROBOTO,
	FONT_ROBOTO_MONO,
	FONT_MAX
};

enum EFontWeight
{
	WEIGHT_THIN,
	WEIGHT_LIGHT,
	WEIGHT_REGULAR,
	WEIGHT_MEDIUM,
	WEIGHT_BOLD,
	WEIGHT_MAX
};

struct bitmap_t
{
	std::vector< unsigned char > vecBytes { };
	Utilities::vector2_t vecSize { };

	bitmap_t( ) = default;
	bitmap_t( unsigned char *pData, const Utilities::vector2_t &vecSize );
	bitmap_t( const std::vector< unsigned char > &vecBytes, const Utilities::vector2_t &vecSize );
	bitmap_t( const Utilities::vector2_t &vecSize );

	[ [ nodiscard ] ] std::size_t GetBitIndex( unsigned x, unsigned y ) const;
	[ [ nodiscard ] ] std::vector< DWORD > GetColoredBitmapBytes( DWORD dwRBGA ) const;
	void Resize( const Utilities::vector2_t &vecNewSize );
	void Insert( Utilities::vector2_t vecLocation, const bitmap_t &_Other );
	void ConcatenateHorizontal( const bitmap_t &_Other );
	void ConcatenateVertical( const bitmap_t &_Other );
	void ShiftUpward( unsigned uMagnitude );
	void ShiftDownward( unsigned uMagnitude );
	void ShiftLeftward( unsigned uMagnitude );
	void ShiftRightward( unsigned uMagnitude );
	bool VerticalRowEmpty( unsigned uRow );
	bool HorizontalRowEmpty( unsigned uRow );
	void Clip( );
};

class CFontManager: public IBase
{
private:

	bool Initialize( ) override;
	void Uninitialize( ) override;

	char *RenderGlyph( char *szText );

	const std::string strRelativeFontDirectory = ENC( "Fonts\\" );
	const std::string strFontDirectories[ FONT_MAX ]
	{
		ENC( "Open Sans\\" ),
		ENC( "Roboto\\" ),
		ENC( "Roboto Mono\\" )
	};
	const std::string strWeightTitles[ WEIGHT_MAX ]
	{
		ENC( "Thin" ),
		ENC( "Light" ),
		ENC( "Regular" ),
		ENC( "Medium" ),
		ENC( "Bold" )
	};
	const std::string strItalicizedSuffix = ENC( "Italic" );
	const std::string strFontFileExtension = ENC( ".ttf" );
	FT_Library _Instance = nullptr;
	FT_Face _Fonts[ FONT_MAX ][ WEIGHT_MAX ][ 2 ] { }, _CurrentFont { };

public:

	bitmap_t CreateBitmap( char *szText, EFont _Font, EFontWeight _Weight, bool bItalic, double dbSize );
	Utilities::vector2_t CalculateTextSize( char *szText, EFont _Font, EFontWeight _Weight, bool bItalic, double dbSize );
} inline _FontManager;
