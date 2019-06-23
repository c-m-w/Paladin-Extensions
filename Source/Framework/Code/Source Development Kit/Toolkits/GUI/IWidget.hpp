/// IWidget.hpp

#pragma once

#include "GUI.hpp"

enum EWidget
{
	WIDGET_NONE,
	WIDGET_IMAGE,
	WIDGET_VECTOR_GRAPHIC,
	WIDGET_MAX
};

class IWidget: public IInteractable
{
protected:

	EWidget _Type = WIDGET_NONE;

public:

	IWidget( EWidget _Type );

	friend class CHorizontalRow;
	friend class CVerticalRow;
};
