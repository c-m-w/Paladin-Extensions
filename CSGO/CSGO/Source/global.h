#pragma once
#include "debug.h"

extern HINSTANCE hInst;
extern std::atomic<bool> bExitState;
extern std::vector<std::thread> threads;

void Wait(unsigned int z);
unsigned int GetTime();

typedef unsigned long frame;
typedef unsigned short total;
typedef unsigned __int8 uint8;

struct Angle {
	float pitch, yaw, roll; // y, x, z
};

struct Color {
	uint8 r, g, b, a;
};

struct Coordinate {
	float x, y, z;
};

#define PI 3.141593f
#define FL_ONGROUND (1 << 0) // At rest / on the ground
#define FL_DUCKING (1 << 1)  // Player flag -- Player is fully crouched

enum MoveType {
	MOVETYPE_NONE, // never moves
	MOVETYPE_WALK = 2, // Player only - moving on the ground
	MOVETYPE_NOCLIP = 8, // No gravity, no collisions, still do velocity/avelocity
	MOVETYPE_LADDER, // Used by players only when going onto a ladder
	MOVETYPE_OBSERVER, // Observer movement, depends on player's observer mode
};

enum SignOnState {
	SIGNONSTATE_CONNECTED = 2,
	SIGNONSTATE_SPAWNED = 5,
	SIGNONSTATE_FULL,
	SIGNONSTATE_CHANGELEVEL
};

enum Keystroke {
	RELEASE = 4,
	PRESS = 5,
	SCROLL = 6
};

enum LifeState {
	LIFESTATE_ALIVE,
	LIFESTATE_KILLCAM,
	LIFESTATE_DEAD
};

enum Team {
	TEAM_NONE = 0,
	TEAM_SPECTATOR = 1,
	TEAM_TERRORISTS = 2,
	TEAM_COUNTERTERRORISTS = 3
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

enum Weapon {
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
	WEAPON_P250,
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
	WEAPON_C4,
	WEAPON_KNIFE_T = 59,
	WEAPON_M4A1_SILENCER,
	WEAPON_USP_SILENCER,
	WEAPON_CZ75A = 63,
	WEAPON_REVOLVER,
	WEAPON_KNIFE_BAYONET = 500,
	WEAPON_KNIFE_FLIP = 505,
	WEAPON_KNIFE_GUT,
	WEAPON_KNIFE_KARAMBIT,
	WEAPON_KNIFE_M9_BAYONET,
	WEAPON_KNIFE_TACTICAL,
	WEAPON_KNIFE_FALCHION = 512,
	WEAPON_KNIFE_BOWIE = 514,
	WEAPON_KNIFE_BUTTERFLY,
	WEAPON_KNIFE_PUSH
};
