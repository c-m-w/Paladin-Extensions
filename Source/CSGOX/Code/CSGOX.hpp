/// CSGOX.hpp

#pragma once

#define DLL_ENTRY
#define USE_NAMESPACES
#define USE_DEFINITIONS
#include "../../Framework/Code/Framework.hpp"

#include "../../CSGO SDK/Code/CSGO SDK.hpp"

#include "Source Development Kit/Toolkits/Features/Hook.hpp"

#include "Source Development Kit/Application Programming Interface/Hooks.hpp"

#if defined USE_INTERNAL_DEFINITIONS
#define LINK ( _Linker )
#define HOOKS ( _Hooks )
#endif
