/// Game Events.cpp

#include "PX Precompiled.hpp"
#include "../PX CSGO.hpp"

namespace PX::Events
{
	std::vector< std::string > vecAddedCallbacks { };
	std::vector< std::pair< event_callback_t, cstr_t > > vecEventCallbacks { };

	class CListener: public IGameEventListener2
	{
		void FireGameEvent( IGameEvent* pEvent ) override
		{
			const std::string strName = pEvent->GetName( );
			for ( const auto& callback : vecEventCallbacks )
				if ( callback.second == strName )
					callback.first( pEvent );
		}

		int GetEventDebugID( ) override
		{
			return EVENT_DEBUG_ID_INIT;
		}
	} event_listener;

	bool PX_API AddEventCallback( event_callback_t fnCallback, cstr_t szEventName, bool bServerSide )
	{
		for ( const auto& strEvent : vecAddedCallbacks )
			if ( strEvent == szEventName )
				return false;

		vecEventCallbacks.emplace_back( fnCallback, szEventName );
		return pEvents->AddListener( &event_listener, szEventName, bServerSide );
	}
}
