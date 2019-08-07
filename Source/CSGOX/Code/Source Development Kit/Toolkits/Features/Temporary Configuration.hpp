/// Temporary Configuration

#pragma once

struct Cfg
{
	struct Bhop
	{
		inline static bool bUseJumpButton = true;
		inline static bool bUseKeybind = true;
		inline static key_t _Key = VK_SPACE;
		inline static unsigned __int8 u8MaximumExtraJumps = 7ui8;
		inline static bool bJumpBeforeHopping = true;
		inline static bool bJumpAfterHopping = true;
	};
} _Cfg; // can dump this object to disk
