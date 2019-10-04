/// CButton.hpp

#pragma once

class CButton: public IWidget
{
private:

	void SetDefaultSize( ) override;
	void CreateDrawables( ) override;
	void CreateTextBitmap( );

	std::string strText = ENC( "Button" );
	bitmap_t _TextBitmap { };
	animated_value_t< Utilities::vector2_t > *_SizeAnimation = new animated_value_t< Utilities::vector2_t >( &vecRelativeSize );
	animated_value_t< Utilities::vector2_t > *_LocationAnimation = new animated_value_t< Utilities::vector2_t >( &vecRelativeLocation );

public:

	static constexpr auto TEXT_HEIGHT = 0.10416666666;
	static constexpr auto TEXT_SPACING = 0.10416666666;
	static constexpr auto FONT = FONT_ROBOTO;
	static constexpr auto FONT_WEIGHT = WEIGHT_BOLD;
	static constexpr auto ROUNDING = 0.2;
	static constexpr auto LOCATION_ANIMATION_TIME = 50ull;

	CButton( );

	void SetText( const std::string &strNewText );
};
