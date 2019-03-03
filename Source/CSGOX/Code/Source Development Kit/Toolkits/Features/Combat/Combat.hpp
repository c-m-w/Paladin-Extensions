/// Combat.hpp

#pragma once

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
