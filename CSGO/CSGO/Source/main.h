#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <thread>
#include <atomic>
#include <vector>

#define PI 3.141593f

void panic(int code);

#include "Program/debug.h"
#include "Program/global.h"
#include "Program/memory.h"
#include "Program/menu.h"
#include "Program/config.h"
#include "Program/singletons.h" //Might be useful to put before config (and maybe menu)

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