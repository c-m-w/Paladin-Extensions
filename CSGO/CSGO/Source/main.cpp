#include "main.h"

/* Key:
 * 0 -> successfully exited
 * 1 -> initial library loading failed
 * 2 -> called for blacklisted reason
 */

void cleanup() 
{
	bExitState = true;

	for (auto &t : threads)
		if (t.joinable())
			t.join();
}

void panic(int code)
{
	cleanup();
	FreeLibraryAndExitThread(hInst, code);
}

void cheat()
{
	//Make threads, add them to threads vector, return this function (close if error)
}

BOOL WINAPI DllMain(HINSTANCE hinstDll, DWORD fdwReason, LPVOID lpvReserved) 
{
	switch (fdwReason) 
	{
		case DLL_PROCESS_ATTACH:
			DisableThreadLibraryCalls(hinstDll);
			hInst = hinstDll;
			CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)cheat, NULL, 0, nullptr);
			break;

		case DLL_PROCESS_DETACH:
			cleanup();
			break;
	}
	return true;
}
