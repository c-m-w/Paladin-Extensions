/// PX Framework.hpp

#pragma once

// Global - These files provide assistance in compilation management
#include "Definitions.hpp"

// External - These files need to be included dynamically
#include <vurtun/nuklear.h>
#include <vurtun/demo/d3d9/nuklear_d3d9.h>

// Application - These files provide general utilities for application development
#include "Application/Types.hpp"
#include "Application/Tools.hpp"
#include "Application/Debug.hpp"
#include "Application/Input Manager.hpp"
#include "Application/File Manager.hpp"

// Security - These files provide specific functionality for ensuring security and verifying authenticity
#include "Security/Cryptography.hpp"
#include "Security/System Management.hpp"
#include "Security/Connectivity.hpp"
// Analysis Protection - These files provide specific functionality to prevent analysis
#include "Security/Analysis Protection/Analysis Protection.hpp"

// Drawing - These files provide specific functionality for creating visuals
#include "Design/Render Engine.hpp"
#include "Design/Drawing.hpp"
#include "Design/User Interface.hpp"

#if defined PX_USE_NAMESPACES
using namespace PX;
#endif
