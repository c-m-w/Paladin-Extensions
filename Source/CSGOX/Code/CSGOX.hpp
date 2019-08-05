/// CSGOX.hpp

#pragma once

#define DLL_ENTRY
#define USE_NAMESPACES
#define USE_DEFINITIONS
#include "../../Framework/Code/Framework.hpp"

#include "../../CSGO SDK/Code/SDK.hpp"

#include "Development Environment/Linkage.hpp"
#include "Source Development Kit/Application Programming Interface/Hooks.hpp"

#if defined USE_INTERNAL_NAMESPACES
using namespace Modules;
using namespace Interfaces;
#endif

#if defined USE_INTERNAL_DEFINITIONS
#define LINK ( _Linker )
#define HOOKS ( _Hooks )
#endif
