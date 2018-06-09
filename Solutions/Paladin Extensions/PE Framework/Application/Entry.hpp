/// Entry.hpp

#pragma once

#if defined( ENTRY_AS_WIN ) && !defined( ENTRY_AS_DLL ) && !defined( ENTRY_AS_NONE )

namespace Paladin
{
	extern HINSTANCE hinstWin;
};

void OnLaunch( );

#if defined( UNICODE )
int WINAPI wWinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow );
#else
int WINAPI WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow );
#endif

#elif !defined( ENTRY_AS_WIN ) && defined( ENTRY_AS_DLL ) && !defined( ENTRY_AS_NONE )

namespace Paladin
{
	extern HINSTANCE hinstDLL;
};

void OnAttach( );
void OnDetach( );

void Detach( );
DWORD WINAPI ThreadProc( _In_ LPVOID lpParameter );
BOOL WINAPI DllMain( _In_ HINSTANCE hinstDLL, _In_ DWORD fdwReason, _In_ LPVOID lpvReserved );

#endif
