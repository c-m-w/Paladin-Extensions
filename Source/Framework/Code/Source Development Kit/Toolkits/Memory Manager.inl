/// Memory Manager.inl

#pragma once

template< typename _t > bool worker_t::Push( _t _Value )
{
	static_assert( sizeof( _t ) == sizeof( DWORD )
				   || sizeof( _t ) == sizeof( WORD ) );

	if ( !bSuspended )
		return _Log.Log( EPrefix::WARNING, ELocation::MEMORY_MANAGER, ENC( "Attempting to push a value onto stack without suspending thread first." ) ), false;

	CONTEXT _ThreadContext;
	if ( !GetContext( _ThreadContext ) )
		return false;

	_ThreadContext.Esp -= sizeof( _t );
	return _MemoryManager.Write( reinterpret_cast< void * >( _ThreadContext.Esp ), _Value )
		&& SetContext( _ThreadContext );
}

template< typename _t > bool worker_t::Pop( _t &_Out )
{
	static_assert( sizeof( _t ) == sizeof( DWORD )
				   || sizeof( _t ) == sizeof( WORD ) );

	if ( !bSuspended )
		return _Log.Log( EPrefix::WARNING, ELocation::MEMORY_MANAGER, ENC( "Attempting to pop a value from the stack without suspending thread first." ) ), false;

	CONTEXT _ThreadContext;
	if ( !GetContext( _ThreadContext )
		 || !_MemoryManager.Read( reinterpret_cast< void * >( _ThreadContext.Esp ), _Out ) )
		return false;

	_ThreadContext.Esp += sizeof( _t );
	return SetContext( _ThreadContext );
}

template< typename _t > bool CMemoryManager::Read( void* pAddress, _t _Out )
{
	return Read( pAddress, &_Out, sizeof( _t ) );
}

template< typename _t > bool CMemoryManager::Write( void* pAddress, _t _Value )
{
	return Write( pAddress, reinterpret_cast< void * >( &_Value ), sizeof( _t ) );
}
