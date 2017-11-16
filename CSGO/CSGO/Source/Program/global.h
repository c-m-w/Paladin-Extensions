#pragma once
#include "../main.h"

#define PI 3.141593f

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
	SIGN_ON_STATE_CHALLENGE = 1,
	SIGN_ON_STATE_CONNECTED,
	SIGN_ON_STATE_NEW,
	SIGN_ON_STATE_PRESPAWN,
	SIGN_ON_STATE_SPAWNED,
	SIGN_ON_STATE_FULL,
	SIGN_ON_STATE_CHANGELEVEL
};

enum Keystroke {
	RELEASE = 4,
	PRESS = 5,
	SCROLL = 6
};

enum Weapons {
	DEAGLE = 1,
	ELITE,
	FIVESEVEN,
	GLOCK,
	AK47 = 7,
	AUG,
	AWP,
	FAMAS,
	G3SG1,
	GALILAR = 13,
	M249,
	M4A1 = 16,
	MAC10,
	P90 = 19,
	UMP45 = 24,
	XM1014,
	BIZON,
	MAG7,
	NEGEV,
	SAWEDOFF,
	TEC9,
	TASER,
	HKP2000,
	MP7,
	MP9,
	NOVA,
	P250_CZ75A,
	SCAR20 = 38,
	SG556,
	SSG08,
	KNIFEGG,
	KNIFE,
	FLASHBANG,
	HEGRENADE,
	SMOKEGRENADE,
	MOLOTOV,
	DECOY,
	INCGRENADE,
	C4,
	MAX
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
