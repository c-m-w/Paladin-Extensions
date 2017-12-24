#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <thread>
#include <string>
#include <vector>

#include "Global/debug.h"
#include "Global/typedefs.h"
#include "Global/defines.h"
#include "Global/enums.h"
#include "Global/structs.h"
#include "Global/functions.h"

#include "Global/Game/gametypedefs.h"
#include "Global/Game/gamedefines.h"
#include "Global/Game/gameenums.h"
#include "Global/Game/gamestructs.h"
#include "Global/Game/gameclasses.h"
#include "Global/Game/gameengine.h"

#include "Program/general.h"
#include "Program/config.h"
#include "Program/interface.h"
#include "Program/memory.h"

#include "Features/Awareness/noflash.h"
#include "Features/Awareness/radar.h"
#include "Features/Awareness/sonar.h"

#include "Features/Combat/recoilcontrol.h"
#include "Features/Combat/trigger.h"

#include "Features/Miscellaneous/airstuck.h"
#include "Features/Miscellaneous/automation.h"
#include "Features/Miscellaneous/fakelag.h"
#include "Features/Miscellaneous/fov.h"
#include "Features/Miscellaneous/hitsound.h"
