#pragma once
#include "includes.h"
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
