/// Awareness.hpp

#pragma once

struct IAwarenessContextInternal: IAwarenessContext
{
	void flee() override;
	void foo( ) override;
	void* quid;
};
