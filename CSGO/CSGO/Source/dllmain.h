#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <thread>
#include <string>
#include <vector>

#include "global.h"
#include "debug.h"

#include "Program/general.h"
#include "Program/config.h"
#include "Program/interface.h"
#include "Program/memory.h"

#include "Features/engine.h"

#include "Features/Awareness/hitsound.h"
#include "Features/Awareness/noflash.h"
#include "Features/Awareness/radar.h"
#include "Features/Awareness/sonar.h"

#include "Features/Combat/recoilcontrol.h"
#include "Features/Combat/trigger.h"

#include "Features/Miscellaneous/airstuck.h"
#include "Features/Miscellaneous/automation.h"
#include "Features/Miscellaneous/fakelag.h"
#include "Features/Miscellaneous/fov.h"

/* Conventions:
 * Start naming on everything with a capital
 * * Variables must start with a lowercase including their datatype (bExitState, dwClientBase)
 * * * EEnum
 * * * * NUMS ARE ALL CAPITALS
 * * * CClass
 * * * struct_t
 * * * typedef
 * * * b bool/byte
 * * * f FLAG
 * * * n nano (__int8)
 * * * un unsigned nano (unsigned __int8)
 * * * s short int
 * * * us unsigned short
 * * * i int
 * * * u unsigned int (total, c are alternatives - pls do not use these)
 * * * l long
 * * * ul unsigned long
 * * * clr color
 * * * cor coordinate
 * * * ang angle
 * * * mnt moment
 * * * vec vector
 * * * fl float
 * * * db double
 * * * ch char
 * * * sz string of chars
 * * * str string
 * * * dw dword
 * * * fn function
 * * * h handle
 * * * p pointer
 * * * lp long pointer
 * * * x unknown (_ is an alternative - pls do not use this)
 * * Variables must also include their inheritance prefix with an underscore (lp_fFlags for frame Local Player Flags)
 * Every function should be a verb (get, set, clamp)
 * * Instead of Alive or IsAlive, do GetLifeState
 * Everything should be English
 * * Instead of OffsetX for a function, do GetHorizontalDistance
 * Always clean your code with ReSharper before committing
 * * Retest to make sure it doesn't break anything!
 */
