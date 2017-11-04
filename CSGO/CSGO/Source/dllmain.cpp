#include "dllmain.h"

/* Key:
 * 0 -> successfully exited
 * 1 -> initial library loading failed
 * 2 -> called for blacklisted reason
 */
DWORD WINAPI Main(LPVOID lpvBase) {
	// TODO cheat quit reason that's saved in config on exit
	return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDll, DWORD fdwReason, LPVOID lpvReserved) {
	// TODO DLL quit reason that's saved in config on exit
	switch (fdwReason) {
		case DLL_PROCESS_ATTACH:
			DisableThreadLibraryCalls(hinstDll); // don't call us for DLL_THREAD_ATTACH/DLL_THREAD_DETACH
			CreateThread(nullptr, 0, Main, hinstDll, 0, nullptr); // start cheat
			FreeLibraryAndExitThread(hinstDll, 0/*REPLACE WITH QUIT REASON*/); // once thread is done, exit
		case DLL_PROCESS_DETACH:
			if (lpvReserved == nullptr) {
				FreeLibraryAndExitThread(hinstDll, 0/*QUIT REASON*/); // program is terminating
			}
			return 1/*REPLACE WITH QUIT REASON*/; // someone is trying to unload our cheat from the outside
		default:
			return 2/*REPLACE WITH QUIT REASON*/; // we're being called with DLL_THREAD_ATTACH/DLL_THREAD_DETACH, we messed up
	}
}
