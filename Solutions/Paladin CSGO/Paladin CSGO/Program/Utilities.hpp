#pragma once

namespace Utilities
{
	// General functions
	DWORD PatternScan( void *pModule, const char *szPattern, int iDisplacement = 0 );

	// SDK functions
	CreateInterfaceFn GetModuleFactory( HMODULE hModule );
	template< class _Datatype > _Datatype *GetInterface( CreateInterfaceFn ifInterfaceCast, const char *szInterface );
	void CaptureInterfaces( );

	// Hooking functions
	void HookAll( );
	void UnhookAll( );
}
