/// IWidget.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#include "../../../Framework.hpp"

constexpr unsigned WIDGET_SIZES[ WIDGET_MAX ]
{
	0,
	sizeof( CImage ),
	sizeof( CVectorGraphic ),
	sizeof( CText ),
	sizeof( CGroupButton ),
	sizeof( CButton )
};

IWidget::IWidget( EWidget _Type, ECursorType _Cursor ) :
	IInteractable( WIDGET_SIZES[ _Type ], INTERACTABLE_WIDGET ), _Type( _Type ), _Cursor( _Cursor )
{ }

void IWidget::OnClick( CKeyState _State )
{
	if ( _OnClick && _State )
		_OnClick( );

	OnWidgetClick( );
}

bool IWidget::IsWidgetType( EWidget _TestType )
{
	return _Type == _TestType;
}

ECursorType IWidget::GetCursorType( )
{
	return _Cursor;
}

void IWidget::SetCursorType( ECursorType _NewCursor )
{
	_Cursor = _NewCursor;
}

void IWidget::SetCallback( callback_t _NewOnClick )
{
	_OnClick = _NewOnClick;
	if ( _Cursor == CURSOR_ARROW )
		_Cursor = CURSOR_HAND;
}

void IWidget::OnWidgetClick( )
{ }
