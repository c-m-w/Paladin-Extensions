#include "main.h"

int _stdcall Main( )
{
	return 0;
}

#ifdef _DEBUG

int CALLBACK WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow )
{
	SET_DEBUG( );
	Main( );
	RESTORE_DEBUG( );
}

#else

BOOL WINAPI DllMain( _In_ HINSTANCE hInstDll, _In_ DWORD dwReason, _In_ LPVOID lpvReserved )
{
	switch ( dwReason )
	{
		case DLL_PROCESS_ATTACH:
		{
			DisableThreadLibraryCalls( hInstDll );
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

#endif
