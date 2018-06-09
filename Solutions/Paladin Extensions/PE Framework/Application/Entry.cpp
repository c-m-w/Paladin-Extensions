/// Entry.cpp

#include <Windows.h>

#include "../Framework.hpp"

namespace Paladin
{
	HINSTANCE hinstWin;
	HINSTANCE hinstDLL;
};

extern void OnLaunch( );
extern void OnAttach( );
extern void OnDetach( );

#if defined( UNICODE )
int WINAPI wWinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow )
#else
int WINAPI WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow )
#endif
{
	Paladin::hinstWin = hInstance;

#if defined( _DEBUG )
	AllocConsole( );
	freopen_s( new FILE * { nullptr }, "CONOUT$", "w", stdout );
#endif

	OnLaunch( );
	return NULL;
}

void Detach( )
{
#if defined( _DEBUG )
	FreeConsole( );
#endif
	OnDetach( );
	FreeLibraryAndExitThread( Paladin::hinstDLL, 0 );
}

DWORD WINAPI ThreadProc( _In_ LPVOID lpParameter )
{
#if defined( _DEBUG )
	AllocConsole( );
	freopen_s( new FILE * { nullptr }, "CONOUT$", "w", stdout );
#endif

	OnAttach( );
	return NULL;
}

BOOL WINAPI DllMain( _In_ HINSTANCE hinstDLL, _In_ DWORD fdwReason, _In_ LPVOID lpvReserved )
{
	switch ( fdwReason )
	{
		case DLL_PROCESS_ATTACH:
		{
			DisableThreadLibraryCalls( hinstDLL );
			Paladin::hinstDLL = hinstDLL;

			HANDLE hThreadProc = CreateThread( nullptr, 0, ThreadProc, lpvReserved, 0, nullptr );
			if ( !hThreadProc || hThreadProc == INVALID_HANDLE_VALUE )
				return FALSE;

			return TRUE;
		}
		case DLL_PROCESS_DETACH:
#if defined( _DEBUG )
			FreeConsole( );
#endif
			OnDetach( );
			return TRUE;
		default:
			return FALSE;
	}
}

