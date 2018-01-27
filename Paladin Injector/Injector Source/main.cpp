#include "main.h"

int _stdcall Main( )
{
	return 0;
}

#ifdef _DEBUG

int CALLBACK WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow )
{
	SET_DEBUG( );

	LPWSTR *argv = nullptr;
	int argc = 0;

	argv = CommandLineToArgvW(GetCommandLine(), &argc);

	if (argv == nullptr)
	{
		LogDebugMessage(ERR, L"Unable to get argument list");
		Sleep(7000);
		RESTORE_DEBUG();
		return 1;
	}

	if (argc != 2) 
	{
		LogDebugMessage(ERR, L"Invalid argument count");
		Sleep(7000);
		RESTORE_DEBUG();
		return 1;
	}

	LogDebugMessage(DBG, L"Injecting %s", argv[1]);

	DWORD csgo = getFirstCSGO();

	LogDebugMessage(DBG, L"Process ID: %lu", csgo);

	if (!Inject(argv[1], csgo))
		LogDebugMessage(ERR, L"Error injecting");
	else
		LogDebugMessage(SCS, L"Injected");

	LogDebugMessage(DBG, L"Done");

	LocalFree(argv);

	Sleep(7000);

	//Main( );
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
