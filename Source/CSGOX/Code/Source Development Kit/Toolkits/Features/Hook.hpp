/// Hook.hpp

#pragma once

#include "Temporary Configuration.hpp"

struct SCreateMoveContext
{
	/*CCSPlayer*/CBasePlayer *pLocalPlayer;
	CUserCmd *pCommand;
};

#include "Movement.hpp"

inline std::vector< std::function< void( SCreateMoveContext ) > > vecBeginCreateMove { };
inline std::vector< std::function< void( SCreateMoveContext ) > > vecEndCreateMove { };

inline void AddAllFns( )
{
	vecBeginCreateMove.emplace_back( Bhop );
}
