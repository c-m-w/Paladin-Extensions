#pragma once
#include "includes.h"

#include "Program/general.h"
#include "Program/config.h"
#include "Program/interface.h"
#include "Program/memory.h"

#include "Features/engine.h"
#include "Features/Miscellaneous/automation.h"

void Feature(bool, void (*)(), unsigned int);
void Feature(bool, void (*)(), unsigned int, int);
void CleanUp();
void Panic();
void Cheat();
BOOL WINAPI DllMain(HINSTANCE, DWORD, LPVOID);

/* Conventions:
 * Start everything with a capital
 * * Variables must start with a lowercase including their datatype (bExitState, dwClientBase)
 * * Variables must also include their inheritance prefix with an underscore (lp_fFlags for framed Local Player Flags)
 * Every function should be a verb (get, set, clamp)
 * * Instead of Alive or IsAlive, do GetLifeState
 * Everything should be English
 * * Instead of OffsetX for a function, do GetHorizontalDistance
 * Always clean your code with ReSharper before committing
 * * Retest to make sure it doesn't break anything!
 */
