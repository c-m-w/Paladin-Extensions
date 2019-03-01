/// CSGOX.hpp

#pragma once

#define DLL_ENTRY
#define USE_NAMESPACES
#define USE_DEFINITIONS
#include "../../Framework/Code/Framework.hpp"

#include "Development Environment/Memory.hpp"

#if defined USE_INTERNAL_NAMESPACES
using namespace Modules;
using namespace Interfaces;
#endif

#if defined USE_INTERNAL_DEFINITIONS
#define GAME_MEM ( _GameMemory )
#endif
