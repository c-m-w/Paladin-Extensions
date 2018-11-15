/// Game Events.hpp

#pragma once

namespace PX::Events
{
	bool PX_API AddEventCallback( Types::event_callback_t fnCallback, Types::cstr_t szEventName, bool bServerSide );
	void PX_API RemoveEventCallbacks( );
}
