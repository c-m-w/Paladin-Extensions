/// IWidget.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#include "../../../Framework.hpp"

IWidget::IWidget( EWidget _Type, ECursorType _Cursor ) :
	IInteractable( INTERACTABLE_WIDGET ), _Type( _Type ), _Cursor( _Cursor )
{ }

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
