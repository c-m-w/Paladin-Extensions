/// CGroupButton.hpp

#pragma once

enum EButtonType
{
	BUTTON_LEFT,
	BUTTON_CENTER,
	BUTTON_RIGHT,
	BUTTON_MAX
};

class CGroupButton: public IWidget
{
private:

	void SetDefaultSize( ) override;
	void CreateDrawables( ) override;
	void CreateTextBitmap( );

	std::string strText = ENC( "Button" );
	bitmap_t _TextBitmap { };
	EButtonType _Type = BUTTON_LEFT;
	animated_value_t< Utilities::vector2_t > *_SizeAnimation = new animated_value_t< Utilities::vector2_t >( &vecRelativeSize );

public:

	static constexpr auto TEXT_HEIGHT = 0.125;
	static constexpr auto TEXT_SPACING = 0.10416666666;
	static constexpr auto FONT = FONT_ROBOTO;
	static constexpr auto ROUNDING = 0.2;

	CGroupButton( );

	void SetText( const std::string &strNewText );
	void SetType( EButtonType _NewType );
};
