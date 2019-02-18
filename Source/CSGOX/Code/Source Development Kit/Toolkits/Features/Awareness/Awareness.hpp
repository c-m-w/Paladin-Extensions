/// Awareness.hpp

#pragma once

#include "../Features Context.hpp"

struct IAwarenessContextInternal: IAwarenessContext
{
	void foo( ) override;
	void* quid;
};
