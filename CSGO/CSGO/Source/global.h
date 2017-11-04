#pragma once
#include "dllmain.h"
#define PI 3.141593f

/* Conventions:
 * Start everything with a capital
 * * Variables must start with a lowercase including their datatype (bExitState, dwClientBase)
 * Every function should be a verb (get, clamp)
 * * Instead of Alive or IsAlive, do GetLifeState
 * Everything should be English
 * * Instead of OffsetX for a function, do GetHorizontalDistance
 * Always clean your code with ReSharper before committing
 * * Retest to make sure it doesn't break anything!
 */
struct Angle {
	float pitch, yaw, roll; // y, x, z
};

struct Coordinate {
	float x, y, z;
};

struct Color {
	unsigned __int8 r, g, b, a;
};

inline void Wait(const unsigned int z) {
	std::this_thread::sleep_for(std::chrono::milliseconds(z));
}

inline int GetTimeMs() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

enum CsWeaponType {
	WEAPONTYPE_KNIFE = 0,
	WEAPONTYPE_PISTOL,
	WEAPONTYPE_SUBMACHINEGUN,
	WEAPONTYPE_RIFLE,
	WEAPONTYPE_SHOTGUN,
	WEAPONTYPE_SNIPER_RIFLE,
	WEAPONTYPE_MACHINEGUN,
	WEAPONTYPE_C4,
	WEAPONTYPE_PLACEHOLDER,
	WEAPONTYPE_GRENADE,
	WEAPONTYPE_UNKNOWN
};
