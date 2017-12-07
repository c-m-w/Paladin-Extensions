#include "main.h"

HINSTANCE hInst = nullptr;
std::atomic<bool> bExitState = false;
std::vector<std::thread> tThreads;

void Wait(unsigned int z) {
	std::this_thread::sleep_for(std::chrono::milliseconds(z));
}

Time GetTime() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}
