/// IWidget.hpp

#pragma once

#include "GUI.hpp"

enum EWidget
{
	WIDGET_NONE,
	WIDGET_IMAGE,
	WIDGET_VECTOR_GRAPHIC,
	WIDGET_TEXT,
	WIDGET_GROUP_BUTTON,
	WIDGET_BUTTON,
	WIDGET_SCROLLBAR,
	WIDGET_MAX
};

enum ECursorType
{
	CURSOR_NONE,
	CURSOR_ARROW,
	CURSOR_HAND,
	CURSOR_IBEAM,
	CURSOR_MAX
};

class IWidget: public IInteractable
{
protected:

	EWidget _Type = WIDGET_NONE;
	ECursorType _Cursor = CURSOR_ARROW;

public:

	IWidget( EWidget _Type, ECursorType _Cursor );

	bool IsWidgetType( EWidget _TestType );
	ECursorType GetCursorType( );
	void SetCursorType( ECursorType _NewCursor );
};
