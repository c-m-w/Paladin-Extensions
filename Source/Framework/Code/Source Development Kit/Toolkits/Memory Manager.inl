/// Memory Manager.inl

#pragma once

template< typename _t > bool CMemoryManager::Read( void* pAddress, _t& _Out )
{
	return Read( pAddress, &_Out, sizeof( _t ) );
}

template< typename _t > bool CMemoryManager::Write( void* pAddress, _t& _Value )
{
	return Write( pAddress, &_Value, sizeof( _t ) );
}
