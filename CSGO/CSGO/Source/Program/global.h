#pragma once
#include "../main.h"

#define PI 3.141593f

extern HINSTANCE hInst;
extern std::atomic<bool> bExitState;
extern std::vector<std::thread> threads;

void Wait(const unsigned int z);
unsigned int GetTime();

struct Angle {
	float pitch, yaw, roll; // y, x, z
};

struct Coordinate {
	float x, y, z;
};

struct Color {
	unsigned __int8 r, g, b, a;
};

enum WeaponType {
	KNIFE,
	PISTOL,
	SMG,
	RIFLE,
	SHOTGUN,
	SNIPER,
	LMG,
	BOMB,
	PLACEHOLDER,
	GRENADE,
	UNKNOWN
};