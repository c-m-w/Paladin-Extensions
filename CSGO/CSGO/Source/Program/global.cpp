#include "global.h"

void Global::Wait(const unsigned int z) {
	std::this_thread::sleep_for(std::chrono::milliseconds(z));
}

unsigned int Global::GetTime() const {
	return static_cast<unsigned int>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
}

Global gbl;
