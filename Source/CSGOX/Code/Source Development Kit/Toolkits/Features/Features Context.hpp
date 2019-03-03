/// Features Context.hpp

#pragma once

struct IBaseContext
{
	virtual void flee( ) = 0;
	CBasePlayer* pLocalPlayer;
};

struct IAwarenessContext: IBaseContext
{
	virtual void foo( ) = 0;
	void* bar;
};

struct ICombatContext: IBaseContext
{
	virtual void foo( ) = 0;
	void* bar;
};

struct IMiscellaneousContext: IBaseContext
{
	virtual void foo( ) = 0;
	void* bar;
};
