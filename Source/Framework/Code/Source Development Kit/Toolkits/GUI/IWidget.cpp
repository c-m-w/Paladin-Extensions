/// IWidget.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#include "../../../Framework.hpp"

IWidget::IWidget( EWidget _Type ) :
	IInteractable( INTERACTABLE_WIDGET ), _Type( _Type )
{ }
