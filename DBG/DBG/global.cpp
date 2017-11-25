#include "main.h"

HINSTANCE hInst = nullptr;
std::atomic<bool> bEjecting = false;
std::atomic<bool> bExitState = false;
std::vector<std::thread> threads;

void Panic()
{
	FreeLibraryAndExitThread(hInst, 0);
}

void Cleanup(bool exit) 
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

	//If we want to exit and are not in the process of ejecting, create a new thread to unload and exit current thread
	if (exit) 
	{
		if (!bEjecting) 
		{
			bEjecting = true;
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Panic, NULL, NULL, NULL);
		}
	}
}

void Wait(unsigned int z) 
{
	std::this_thread::sleep_for(std::chrono::milliseconds(z));
}

unsigned int GetTime()
{
	return static_cast<unsigned int>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
}