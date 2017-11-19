#include "main.h"

void Cleanup() 
{
	//Global flag for threads to stop
	bExitState = true;

	//Wait on each thread to exit
	for (auto &t : threads)
		if (t.joinable())
			t.join();

	//Free global object memory
	if (dbg != nullptr)
		delete dbg;
}

void Panic() 
{
	Cleanup();
	FreeLibraryAndExitThread(hInst, 0);
}

void Cheat() 
{
	//Init global pointers
	dbg = new Debug;

	//Initialize things
	if (!dbg->Init()) 
	{
		//Get last error to see what went wrong
		dbg->LogLastErrorB();
		return;
	}

	dbg->SetColorMode(MONO);
	dbg->LogDebugMsg(DBG, "Debug");
	dbg->LogDebugMsg(SCS, "Success");
	dbg->LogDebugMsg(WRN, "Warning");
	dbg->LogDebugMsg(ERR, "Error");
	dbg->LogDebugMsg(LER, "Last Error");

	printf("\n");

	dbg->SetColorMode(DUAL);
	dbg->LogDebugMsg(DBG, "Debug");
	dbg->LogDebugMsg(SCS, "Success");
	dbg->LogDebugMsg(WRN, "Warning");
	dbg->LogDebugMsg(ERR, "Error");
	dbg->LogDebugMsg(LER, "Last Error");

	printf("\n");

	dbg->SetColorMode(FULL);
	dbg->LogDebugMsg(DBG, "Debug");
	dbg->LogDebugMsg(SCS, "Success");
	dbg->LogDebugMsg(WRN, "Warning");
	dbg->LogDebugMsg(ERR, "Error");
	dbg->LogDebugMsg(LER, "Last Error");

	Wait(5000);

	Panic();
}

BOOL WINAPI DllMain(HINSTANCE hInstDll, DWORD fdwReason, LPVOID lpvReserved) 
{
	switch (fdwReason) 
	{
		case DLL_PROCESS_ATTACH:
			SetLastError(0);
			DisableThreadLibraryCalls(hInstDll);
			hInst = hInstDll;
			CreateThread(nullptr, 0, LPTHREAD_START_ROUTINE(Cheat), nullptr, 0, nullptr);
			break;

		case DLL_PROCESS_DETACH:
			Cleanup();
			break;
	}
	return TRUE;
}
