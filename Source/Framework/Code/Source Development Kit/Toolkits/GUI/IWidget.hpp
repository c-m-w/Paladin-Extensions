/// IWidget.hpp

#pragma once

#include "GUI.hpp"

enum EWidget
{
	WIDGET_NONE,
	WIDGET_IMAGE,
	WIDGET_VECTOR_GRAPHIC,
	WIDGET_TEXT,
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
	Utilities::callback_t _OnClick = nullptr;

public:

	IWidget( EWidget _Type, ECursorType _Cursor );

	void OnClick( CKeyState _State ) override;
	bool IsWidgetType( EWidget _TestType );
	ECursorType GetCursorType( );
	void SetCursorType( ECursorType _NewCursor );
	void SetCallback( Utilities::callback_t _NewOnClick );
	virtual void OnWidgetClick( );
};
