/// CScrollbar.hpp

#pragma once

enum EScrollbarType
{
	SCROLLBAR_VERTICAL,
	SCROLLBAR_HORIZONTAL,
	SCROLLBAR_MAX
};

class CScrollbar: public IWidget
{
private:

	Utilities::vector2_t CalculateRelativeLocation( );
	double GetBarSize( );
	Utilities::vector2_t GetBarLocation( );
	rectangle_t GetBarRectangle( );
	void CreateDrawables( ) override;
	void SetDefaultSize( ) override;

	EScrollbarType _Type = SCROLLBAR_VERTICAL;
	Utilities::vector2_t vecPendingScrollAmount { };
	Utilities::vector2_t vecClickLocation { };

public:

	static constexpr auto SCROLL_DELTA = 120.0;
	static constexpr auto WIDTH = 0.10416666666;
	constexpr static auto SCROLL_AMOUNT = 0.5;

	CScrollbar( );

	void SetType( EScrollbarType _NewType );
	void Scroll( int iScrollAmount );
	void IncreaseScroll( );
	void DecreaseScroll( );
	void AppendScrollAmount( const Utilities::vector2_t &vecAmount );
	void NewFrame( ) override;
	void OnClick( CKeyState _State ) override;
	void OnMouseMove( const Utilities::vector2_t &vecMouseLocation ) override;

	friend class CContainer;
};
