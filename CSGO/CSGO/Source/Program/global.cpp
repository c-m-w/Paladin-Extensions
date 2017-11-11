#include "../main.h"

HINSTANCE hInst = NULL;
std::atomic<bool> bExitState;
std::vector<std::thread> threads;

inline void Wait(const unsigned int z) 
{
	std::this_thread::sleep_for(std::chrono::milliseconds(z));
}

inline unsigned int GetTime() 
{
	return static_cast<unsigned int>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
}