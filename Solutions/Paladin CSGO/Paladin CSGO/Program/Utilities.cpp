#include "../main.hpp"
#include "Utilities.hpp"

DWORD Utilities::PatternScan( void *pModule, const char *szPattern, int iDisplacement )
{ }

CreateInterfaceFn Utilities::GetModuleFactory( HMODULE hModule )
{ }

template< typename _Datatype > _Datatype *Utilities::GetInterface( CreateInterfaceFn ifInterfaceCast, const char *szInterface )
{ }

void Utilities::CaptureInterfaces( )
{ }

void Utilities::HookAll( )
{ }

void Utilities::UnhookAll( )
{ }
