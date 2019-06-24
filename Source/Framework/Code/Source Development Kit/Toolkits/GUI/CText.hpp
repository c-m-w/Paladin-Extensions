/// CText.hpp

#pragma once

class CText: public IWidget
{
private:

	void CreateDrawables( ) override;

	void InitializeText( );

	std::string strText = ENC( "Default Text" );
	EFont _Font = FONT_TAHOMA;
	double dSize = 6.0;
	EAlignment _Horizontal = ALIGNMENT_LEFT;
	EAlignment _Vertical = ALIGNMENT_TOP;
	color_t clrText = 0xFFFFFFFF;
	bitmap_t _Bitmap { };

public:

	CText( );

	void SetText( const std::string& strNewText );
	void SetFont( EFont _NewFont );
	void SetHeight( double dNewSize );
	void SetAlignment( EAlignment _NewHorizontal, EAlignment _NewVertical );
	void SetColor( const color_t& clrNewText );
	Utilities::vector2_t GetTextSize( );
};
