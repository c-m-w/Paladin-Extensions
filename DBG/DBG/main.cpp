#include "main.h"

HINSTANCE hInst = nullptr;

std::atomic<bool> bEjecting = false;
std::atomic<bool> bExit = false;
std::vector<std::thread> threads;

void Panic()
{
	Wait(2000);
	FreeLibraryAndExitThread(hInst, 0);
}

void Cleanup(bool exit)
{
	//Global flag for threads to stop
	bExit = true;

	//Wait on each thread to exit
	for (auto &t : threads)
		if (t.joinable())
			t.join();

	//Free global object memory
	if (dbg != nullptr)
		delete dbg;

	if (mem != nullptr)
		delete mem;

	if (eng != nullptr)
		delete eng;

	if (aut != nullptr)
		delete aut;

	//If we want to exit and are not in the process of ejecting, create a new thread to unload and exit current thread
	if (exit)
	{
		if (!bEjecting)
		{
			bEjecting = true;
			CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(Panic), nullptr, NULL, nullptr);
		}
	}
}

void FeatureA(bool bFeatureState, uint32_t timeout, int uiFeatureKey, std::function<void()> func)
{
	while (bFeatureState) 
	{
		if (bExit)
			return;

		if (GetAsyncKeyState(uiFeatureKey))
			func();
		else
			Wait(timeout);
	}
}

void FeatureB(bool bFeatureState, uint32_t timeout, std::function<void()> func)
{
	while (bFeatureState) 
	{
		if (bExit)
			return;

		func();
		Wait(timeout);
	}
}

void Cheat() 
{
	//Init global pointers
	dbg = new Debug;
	mem = new MemoryManager;
	eng = new Engine;
	aut = new Automation;

	//Check for null pointers
	if (dbg == nullptr || mem == nullptr || eng == nullptr || aut == nullptr) 
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

	/*
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

	printf("\n");
	*/

	dbg->SetColorMode(FULL);

	dbg->LogDebugMsg(DBG, "Attaching to game");

	if (!mem->AttachToGame()) 
	{
		dbg->LogDebugMsg(ERR, "Failed to attach to game");
		Cleanup();
		return;
	}

	dbg->LogDebugMsg(SCS, "Attached to game");

	mem->InitializeAddresses();

	dbg->LogDebugMsg(DBG, "Creating threads");

	//Create feature threads
	//std::function<void(Automation const&)> tdAutoJump = std::bind(&Automation::AutoJump, aut);
	std::thread tAutoJump(FeatureA, true, 1, VK_SPACE, std::bind(&Automation::AutoJump, aut));
	threads.push_back(std::move(tAutoJump));

	/*
	std::thread tAutoJump(&Automation::AutoJump, aut);
	threads.push_back(std::move(tAutoJump));
	*/

	dbg->LogDebugMsg(SCS, "Threads created");

	dbg->LogDebugMsg(SCS, "Cheat initialized, hold F4 to exit cheat");

	while (!GetAsyncKeyState(VK_F4))
		Wait(200);

	Cleanup(true);
}

BOOL WINAPI DllMain(HINSTANCE hInstDll, DWORD fdwReason, LPVOID lpvReserved) 
{
	switch (fdwReason) 
	{
		case DLL_PROCESS_ATTACH:
			SetLastError(0);
			DisableThreadLibraryCalls(hInstDll);
			hInst = hInstDll;
			CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(Cheat), nullptr, NULL, nullptr);
			break;

		case DLL_PROCESS_DETACH:
			Cleanup();
			break;
	}
	return TRUE;
}
