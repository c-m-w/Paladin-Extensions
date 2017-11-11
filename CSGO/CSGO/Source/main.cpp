#include "main.h"

/* Key:
 * 0 -> successfully exited
 * 1 -> initial library loading failed
 * 2 -> called for blacklisted reason
 */

void CleanUp() 
{
	bExitState = true;

	for (auto &t : threads)
		if (t.joinable())
			t.join();
}

void Panic(const int code)
{
	CleanUp();
	FreeLibraryAndExitThread(hInst, code);
}

void Cheat()
{
#ifndef _DEBUG
	AllocConsole();
#endif
	Wait(5000);
	//Make threads, add them to threads vector, return this function (close if error)
}

BOOL WINAPI DllMain(const HINSTANCE hinstDll, const DWORD fdwReason, LPVOID lpvReserved) 
{
	switch (fdwReason) 
	{
		case DLL_PROCESS_ATTACH:
			DisableThreadLibraryCalls(hinstDll);
			hInst = hinstDll;
			CreateThread(nullptr, 0, LPTHREAD_START_ROUTINE(Cheat), nullptr, 0, nullptr);
			break;

		case DLL_PROCESS_DETACH:
			CleanUp();
			break;
	}
	return true;
}
