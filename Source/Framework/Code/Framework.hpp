/// Framework.hpp

#pragma once

#define XOR( _String ) ( _String )

#define NO_ENTRY
#if defined _DEBUG
	#define ACKNOWLEDGED_ENTRY_WARNING_1
#endif
#include "Development Environment/Entry Manager.hpp"

#include "Source Development Kit/Application Programming Interfaces/Utilities.hpp"
#include "Source Development Kit/Application Programming Interfaces/Base Interface.hpp"
#include "Source Development Kit/Application Programming Interfaces/Cryptography.hpp"
#include "Source Development Kit/Application Programming Interfaces/Filesystem.hpp"
#include "Development Environment/Logging.hpp"
#include "Source Development Kit/Application Programming Interfaces/Connectivity.hpp"

#if defined USE_NAMESPACES
using namespace Utilities;
#endif

#if defined USE_DEFINITIONS
#define CRYPTO ( _Cryptography )
#define FS ( _Filesystem )
#define LOG ( _Log )
#define NET ( _Connection )
#endif
