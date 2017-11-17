#pragma once
#include "main.h"

#define PI 3.141593f
#define FLAG_ON_GROUND (1 << 0)

extern HINSTANCE hInst;
extern std::atomic<bool> bExitState;
extern std::vector<std::thread> threads;

void Wait(unsigned int z);
unsigned int GetTime();

struct Angle {
	float pitch, yaw, roll; // y, x, z
};

struct Color {
	unsigned __int8 r, g, b, a;
};

struct Coordinate {
	float x, y, z;
};

enum SignOnState {
	SIGN_ON_STATE_CONNECTED = 2,
	SIGN_ON_STATE_SPAWNED = 5,
	SIGN_ON_STATE_FULL,
	SIGN_ON_STATE_CHANGELEVEL
};

enum Keystroke {
	RELEASE = 4,
	PRESS = 5,
	SCROLL = 6
};

enum Weapons {
	WEAPON_DEAGLE = 1,
	WEAPON_ELITE,
	WEAPON_FIVESEVEN,
	WEAPON_GLOCK,
	WEAPON_AK47 = 7,
	WEAPON_AUG,
	WEAPON_AWP,
	WEAPON_FAMAS,
	WEAPON_G3SG1,
	WEAPON_GALILAR = 13,
	WEAPON_M249,
	WEAPON_M4A1 = 16,
	WEAPON_MAC10,
	WEAPON_P90 = 19,
	WEAPON_UMP45 = 24,
	WEAPON_XM1014,
	WEAPON_BIZON,
	WEAPON_MAG7,
	WEAPON_NEGEV,
	WEAPON_SAWEDOFF,
	WEAPON_TEC9,
	WEAPON_TASER,
	WEAPON_HKP2000,
	WEAPON_MP7,
	WEAPON_MP9,
	WEAPON_NOVA,
	WEAPON_P250_CZ75A,
	WEAPON_SCAR20 = 38,
	WEAPON_SG556,
	WEAPON_SSG08,
	WEAPON_KNIFEGG,
	WEAPON_KNIFE,
	WEAPON_FLASHBANG,
	WEAPON_HEGRENADE,
	WEAPON_SMOKEGRENADE,
	WEAPON_MOLOTOV,
	WEAPON_DECOY,
	WEAPON_INCGRENADE,
	WEAPON_C4
};

enum WeaponType {
	KNIVES,
	PISTOLS,
	SMGS,
	RIFLES,
	SHOTGUNS,
	SNIPERS,
	LMGS,
	BOMBS,
	GRENADES = 9
};
