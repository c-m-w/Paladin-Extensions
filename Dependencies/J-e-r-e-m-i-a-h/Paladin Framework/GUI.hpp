#pragma once
#define NK_IMPLEMENTATION
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#include <vurtun/nuklear.h>
#include "../Framework.hpp"

namespace Paladin
{
	class CGUI;
	extern CGUI gui;

	class CGUI
	{ };

	CGUI gui;
}
