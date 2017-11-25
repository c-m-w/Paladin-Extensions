#include "main.h"

void Cheat() 
{
	//Init global pointers
	dbg = new Debug;

	//Check for null pointers
	if (dbg == nullptr) 
	{
		Cleanup();
		return;
	}

	//Initialize console
	if (!dbg->Init()) 
	{
		//Get last error to see what went wrong
		dbg->LogLastErrorB();
		Cleanup();
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

	system("PAUSE");

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
