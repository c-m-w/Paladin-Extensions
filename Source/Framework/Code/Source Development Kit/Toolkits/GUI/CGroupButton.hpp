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

	void CreateDrawables( ) override;
	void CreateTextBitmap( );

	std::string strText = ENC( "Button" );
	bitmap_t _TextBitmap { };
	EButtonType _Type = BUTTON_LEFT;

public:

	static constexpr auto TEXT_HEIGHT = 0.125;
	static constexpr auto FONT = FONT_ROBOTO;
	static constexpr auto ROUNDING = 0.2;

	CGroupButton( );

	void SetText( const std::string& strNewText );
	void SetType( EButtonType _NewType );
};
