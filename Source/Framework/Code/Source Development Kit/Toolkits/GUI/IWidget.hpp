/// IWidget.hpp

#pragma once

#include "GUI.hpp"

enum EWidget
{
	WIDGET_NONE
};

class IWidget: public IInteractable
{
protected:

	EWidget _Type = WIDGET_NONE;

public:


	friend class CRow;
};
