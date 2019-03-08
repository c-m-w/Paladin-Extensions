/// CSGO SDK.hpp

#pragma once

// Valve/CSGO SDK
#include "networksystem/netchannel.h"

// Extension of SDK
#define EXTEND_SDK_CLASS( CClassName ) class PX_##CClassName: public CClassName
#define EXTENDED_SDK_CLASS( CClassName ) PX_##CClassName
#define EXTEND_SDK_STRUCT( SStructName ) class PX_##SStructName: public SStructName
#define EXTENDED_SDK_STRUCT( SStructName ) PX_##SStructName
#include "CNetChannel Extended.hpp"
