/// Linkage.inl

#pragma once

template< typename _t > bool Modules::module_info_t::operator( )( const char *szInterface, _t *pOutput ) const
{
	if ( _CreateInterface == nullptr )
		return LOG( WARNING, APPLICATION, "Attempting to call CreateInterface when it was not found." ), nullptr;

	if ( ( *reinterpret_cast< void ** >( pOutput ) = _CreateInterface( szInterface, nullptr ) ) == nullptr )
		return LOG( ERROR, APPLICATION, "Interface %s is outdated.", szInterface ), false;

	return true;
}
