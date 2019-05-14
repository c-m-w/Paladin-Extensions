/// Interface.hpp

#pragma once

namespace Interface
{
	constexpr auto TITLE_HEIGHT = 16;
	constexpr auto WINDOW_ICON_HEIGHT = 18;
	constexpr auto STANDARD_HEIGHT = 12;
	constexpr auto SMALL_HEIGHT = 8;
	constexpr auto CHECKBOX_TEXT_HEIGHT = 11.5f;

	inline const static color_t CLEAR = color_t( { 0, 0, 0, 0 } );
	inline const static color_t WHITE = color_t( { 255, 255, 255, 255 } );
	inline const static color_t SHADOW = color_t( { 0, 0, 0, 100 } );
	inline const static color_t BLACK = color_t( { 0, 0, 0, 255 } );
	inline const static color_t BACKGROUND_DARK = color_t( { 33, 36, 40, 255 } );
	inline const static color_t BACKGROUND_LIGHT = color_t( { 61, 65, 72, 255 } );
	inline const static color_t BACKGROUND_DEFAULT = color_t( { 45, 50, 56, 255 } );
	inline const static color_t BACKGROUND_DIM = color_t( { 0, 0, 0, 100 } );
	inline const static color_t OUTLINE_DARK = color_t( { 56, 60, 64, 255 } );
	inline const static color_t OUTLINE_LIGHT = color_t( { 73, 76, 83, 255 } );
	inline const static color_t TEXT_NORMAL = color_t( { 255, 255, 255, 255 } );
	inline const static color_t TEXT_DARK = color_t( { 175, 180, 187, 255 } );
	inline const static color_t BLUE = color_t( { 34, 145, 232, 255 } );
	inline const static color_t TRANSLUCENT_BLUE = color_t( { 34, 145, 232, 100 } );
	inline const static color_t VIVID_BLUE = color_t( { 13, 59, 95, 255 } );
	inline const static color_t VIVID_BLUE_ACTIVE = color_t( { 4, 56, 98, 255 } );
	inline const static color_t DARK_BLUE = color_t( { 43, 60, 75, 255 } );
	inline const static color_t BUTTON_TEXT = color_t( { 33, 150, 243, 255 } );
	inline const static color_t BUTTON_BACKGROUND_DORMANT = color_t( { 0, 0, 0, 0 } );
	inline const static color_t BUTTON_BACKGROUND_HOVER = color_t( { 33, 150, 243, 26 } );
	inline const static color_t BUTTON_BACKGROUND_ACTIVE = color_t( { 33, 150, 243, 51 } );
	static auto NO_CALLBACK = [ & ]( )
	{ };

	enum EShape
	{
		SHAPELESS = -1,
		UNSHAPED,
		MONOGON,
		DIGON,
		TRIGON,
		TRIANGLE = 3,
		TETRAGON,
		QUADRILATERAL = 4,
		RECTANGLE = 4,
		SQUARE = 4,
		PENTAGON,
		HEXAGON,
		HEPTAGON,
		OCTAGON,
		NONAGON,
		DECAGON,
		CIRCLE // when will we ever use an 11+ sided shape?
	};

	enum EWidgetType
	{
		SHAPE,
		TEXT,
		TEXTURE
	};

	class IDrawable
	{
	public:
		virtual void Draw( ) = 0;
	};

	class IContainer;
	class IWidgetBase;
	class IWidget;
	class ISymbolicWidget;

	class IContainer: public IDrawable
	{
	public:
		Utilities::vector2_t vecOrigin;
		Utilities::vector2_t vecDimensions;

		std::array< CColor, RECTANGLE > clrFillColors;
		std::array< CColor, RECTANGLE > clrBorderColors;
		std::array< CColor, RECTANGLE > clrOutlineColors;

		std::array< double, RECTANGLE > dbRounding;

		std::vector< IWidgetBase* > vecWidgets;
		std::vector< std::pair< EWidgetType, EShape > > vecWidgetInfo;
	};

	class IWidgetBase: public IDrawable
	{
	public:
		IContainer* pParent;
	};

	template< const EShape _Shape > class IWidget: public IWidgetBase
	{
	public:
		std::array< Utilities::vector2_t, _Shape > iVertices;

		double dbBorderThickness;
		double dbOutlineThickness;

		std::array< CColor, _Shape > clrFillColors;
		std::array< CColor, _Shape > clrBorderColors;
		std::array< CColor, _Shape > clrOutlineColors;

		std::array< double, _Shape > dbRounding;
	};

	class ISymbolicWidget: public IWidgetBase
	{
		Utilities::vector2_t vecOrigin;
		Utilities::vector2_t vecRenderBoundaries;

		std::string strContent;

		std::array< double, RECTANGLE > dbRenderRounding;

		std::array< CColor, RECTANGLE > clrBackgroundFillColors;
		
		std::array< CColor, RECTANGLE > clrFillColors;
		std::array< CColor, RECTANGLE > clrOutlineColors;
	};
}
