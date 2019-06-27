/// CText.hpp

#pragma once

class CText: public IWidget
{
private:

	void CreateDrawables( ) override;

	void InitializeText( );

	std::string strText = ENC( "Default Text" );
	EFont _Font = FONT_TAHOMA;
	double dSize = 0.0625;
	EAlignment _Horizontal = ALIGNMENT_LEFT;
	EAlignment _Vertical = ALIGNMENT_TOP;
	bitmap_t _Bitmap { };

public:

	CText( );

	void SetText( const std::string& strNewText );
	void SetFont( EFont _NewFont );
	void SetHeight( double dNewSize );
	void SetAlignment( EAlignment _NewHorizontal, EAlignment _NewVertical );
	Utilities::vector2_t GetTextSize( );
};
