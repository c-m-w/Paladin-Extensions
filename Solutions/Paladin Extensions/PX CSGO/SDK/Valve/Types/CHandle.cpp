#include "../../../PX CSGO.hpp"

inline IHandleEntity* CBaseHandle::Get( ) const
{
	return PX::Information::Pointers::pEntityList->GetClientEntityFromHandle( *this );
}
