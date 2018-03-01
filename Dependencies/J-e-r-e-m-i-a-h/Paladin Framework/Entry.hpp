#pragma once
#include "../Framework.hpp"

#ifdef ENTRY_AS_WIN

void OnLaunch( );

namespace Paladin
{
	HINSTANCE hinstWin;
};

#ifdef UNICODE
int WINAPI wWinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow )
#else
int WINAPI WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow )
#endif
{
	Paladin::hinstWin = hInstance;

	OnLaunch( );
	return NULL;
}

#elseifdef ENTRY_AS_DLL

void OnAttach( );
void OnDetach( );

namespace Paladin
{
	HINSTANCE hinstDLL;
};

DWORD WINAPI ThreadProc( _In_ LPVOID lpParameter )
{
	OnAttach( );
	return NULL;
}

BOOL WINAPI DllMain( _In_ HINSTANCE hinstDLL, _In_ DWORD fdwReason, _In_ LPVOID lpvReserved )
{
	switch ( fdwReason )
	{
		case DLL_PROCESS_ATTACH:
		{
			Paladin::hinstDLL = hinstDLL;

			HANDLE hThreadProc = CreateThread( nullptr, 0, ThreadProc, lpvReserved, 0, nullptr );
			if ( !hThreadProc || hThreadProc == INVALID_HANDLE_VALUE )
				return FALSE;

			DisableThreadLibraryCalls( hinstDLL );
			return TRUE;
		}
		case DLL_PROCESS_DETACH:
			OnDetach( );
			return TRUE;
		default:
			return FALSE;
	}
}

#elseifndef ENTRY_AS_NONE
#warning "No entry method defined. Use '#define ENTRY_AS_WIN' or '#define ENTRY_AS_DLL' when including the framework to use automatic entry creation. Use '#define ENTRY_AS_NONE' to disable automatic entry creation."
#endif
