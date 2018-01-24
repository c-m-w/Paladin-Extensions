#include "main.h"

int _stdcall Main( )
{
	return 0;
}

BOOL WINAPI DllMain( _In_ HINSTANCE hInstDll, _In_ DWORD dwReason, _In_ LPVOID lpvReserved )
{
	switch ( dwReason )
	{
		case DLL_PROCESS_ATTACH:
		{
			DisableThreadLibraryCalls( hInstDll );
			SET_DEBUG( );
			HANDLE hCheat = CreateThread( nullptr, 0, LPTHREAD_START_ROUTINE( Main ), nullptr, 0, nullptr );
			if ( !hCheat || hCheat == INVALID_HANDLE_VALUE )
			{
				return FALSE;
			}
			return TRUE;
		}
		case DLL_PROCESS_DETACH:
		{
			if ( lpvReserved == nullptr )
			{
				// Cleanup
				return TRUE;
			}
		}
		default:
		{
			return FALSE;
		}
	}
}
