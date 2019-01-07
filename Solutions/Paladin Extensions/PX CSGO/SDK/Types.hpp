/// Types.hpp

#pragma once

namespace PX::Types
{
	using player_ptr_t = Tools::CBasePlayer*;
	using entity_ptr_t = Tools::CBaseEntity*;
	using event_callback_t = void( PX_API*)( IGameEvent * );
}

using PX::Types::player_ptr_t;
using PX::Types::entity_ptr_t;
