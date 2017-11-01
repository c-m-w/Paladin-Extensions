#include "main.h"

void wait(unsigned int t)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(t));
}

inline int msTime()
{
	return static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
}