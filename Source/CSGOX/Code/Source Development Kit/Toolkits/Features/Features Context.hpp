/// Features Context.hpp

#pragma once

#include "../../../CSGOX.hpp"

struct IAwarenessContext
{
	virtual void foo( );
	void* bar;
};

struct ICombatContext
{
	virtual void foo( );
	void* bar;
};

struct IMiscellaneousContext
{
	virtual void foo( );
	void* bar;
};
