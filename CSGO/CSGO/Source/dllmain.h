#pragma once
#include <Windows.h>
#include <thread>
#include <TlHelp32.h>
#include <atomic>
#define PI 3.141593f
std::atomic<bool> bExitState;


inline void Wait(const unsigned int z) {
	std::this_thread::sleep_for(std::chrono::milliseconds(z));
}

inline unsigned int GetTime() {
	return static_cast<unsigned int>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
}

#include "Program/debug.h"
#include "Program/memory.h"
MemoryManager mem;
#include "Program/menu.h"
#include "Program/config.h"


#include "Miscellaneous/Automation.h"




/* Conventions:
* Start everything with a capital
* * Variables must start with a lowercase including their datatype (bExitState, dwClientBase)
* * Variables must also include their inheritance prefix with an underscore (lp_iFlags for integer Local Player Flags)
* Every function should be a verb (get, set, clamp)
* * Instead of Alive or IsAlive, do GetLifeState
* Everything should be English
* * Instead of OffsetX for a function, do GetHorizontalDistance
* Always clean your code with ReSharper before committing
* * Retest to make sure it doesn't break anything!
*/