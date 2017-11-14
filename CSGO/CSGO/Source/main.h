#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <thread>
#include <atomic>
#include <string>
#include <vector>

#include "Program/debug.h"
#include "Program/global.h"
extern Global gbl;
#include "Program/config.h"
extern Config cfg;
#include "Program/interface.h"
extern Interface men;
#include "Program/memory.h"
extern MemoryManager mem;

#include "Features/engine.h"
extern Engine eng;

#include "Features/Miscellaneous/automation.h"
extern Automation aut;

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
