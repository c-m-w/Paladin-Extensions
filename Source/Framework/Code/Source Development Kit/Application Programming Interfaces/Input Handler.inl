/// Input Handler.inl

#pragma once

template< > std::vector< key_typed_callback_t > &callbacks_t::GetCallbacks< key_typed_callback_t >( )
{
	return vecKeyTypedCallbacks;
}

template< > std::vector< global_key_callback_t > &callbacks_t::GetCallbacks< global_key_callback_t >( )
{
	return vecGlobalKeyCallbacks;
}

template< > std::vector< mouse_move_callback_t > &callbacks_t::GetCallbacks< mouse_move_callback_t >( )
{
	return vecMouseMoveCallbacks;
};

template< > std::vector< scroll_callback_t > &callbacks_t::GetCallbacks< scroll_callback_t >( )
{
	return vecScrollCallbacks;
}

template< typename _t > void CInputHandler::AddCallback( _t _Callback )
{
	_Callbacks.AddCallback( _Callback );
}
