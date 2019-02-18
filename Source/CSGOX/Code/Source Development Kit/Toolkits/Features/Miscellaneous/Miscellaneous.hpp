/// Miscellaneous.hpp

#pragma once

#include "../Features Context.hpp"

struct IMiscellaneousContextInternal: IMiscellaneousContext
{
	void foo( ) override;
	void* quid;
};
