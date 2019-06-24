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
	sizeof( CText )
};

IWidget::IWidget( EWidget _Type, ECursorType _Cursor ) :
	IInteractable( WIDGET_SIZES[ _Type ], INTERACTABLE_WIDGET ), _Type( _Type ), _Cursor( _Cursor )
{ }

bool IWidget::IsWidgetType( EWidget _TestType )
{
	return _Type == _TestType;
}

ECursorType IWidget::GetCursorType( )
{
	return _Cursor;
}
