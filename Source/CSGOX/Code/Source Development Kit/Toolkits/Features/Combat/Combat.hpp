/// Combat.hpp

#pragma once

#include "../Features Context.hpp"

struct ICombatContextInternal: ICombatContext
{
	void foo( ) override;
	enum ETargetPriorities
	{
		PHYSICAL,
		HEALTH,
		CROSSHAIR,
	};
	void GetNearestTarget( ETargetPriorities enumPriority );
};

#include "Aim Assistance.hpp"
