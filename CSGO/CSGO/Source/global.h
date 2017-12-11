#pragma once

#define PI 3.141593f

typedef long long Time;

extern HINSTANCE hInst;
extern std::atomic<bool> bExitState;
extern std::vector<std::thread> tThreads;

void Wait(unsigned int);
Time GetTime();

template<typename datatype> void Limit(datatype &Status, datatype Minimum, datatype Maximum) {
	if (Minimum > Status) {
		Status = Minimum;
	} else if (Status > Maximum) {
		Status = Maximum;
	}
}

enum class EQuitReasons {
	UNKNOWN = -1,
	LOAD_LIBRARY_ERROR,
	SUCCESS,
	BLACKLISTED_CALL,
	PANIC
};

enum class EPremium {
	BANNED = -2,
	EXPIRED = -1,
	NOT_PREMIUM,
	PREMIUM
};

enum class EElevation {
	UNTESTED = -1,
	NOT_ADMIN,
	ADMIN
};

enum class EAnticheatStatus {
	NOT_FOUND = -1,
	FAILED,
	KILLED
};

/// CSGO stuff

#define FL_ONGROUND (1 << 0) // At rest / on the ground
#define FL_DUCKING (1 << 1)  // Player flag -- Player is fully crouched

typedef unsigned int frame;
typedef unsigned short total;
typedef unsigned __int8 uint8;
typedef DWORD handle;

struct Angle {
	float pitch, yaw, roll; // y, x, z
};

struct Color {
	uint8 r, g, b, a;
};

struct Coordinate {
	float x, y, z;
};

struct Vector {
	float dx, dy, dz;
	Vector(Coordinate cOrigin, Coordinate cEndPoint) {
		dx = cEndPoint.x - cOrigin.x;
		dy = cEndPoint.y - cOrigin.y;
		dz = cEndPoint.z - cOrigin.z;
	}
};

struct CGlobalVars {
	float realtime;
	int framecount;
	float absoluteframetime;
	float absoluteframestarttimestddev;
	float curtime;
	float frametime;
	int maxClients;
	int tickcount;
	float interval_per_tick;
	float interpolation_amount;
};

enum class EMoveType {
	NONE, // never moves
	WALK = 2, // Player only - moving on the ground
	NOCLIP = 8, // No gravity, no collisions, still do velocity/avelocity
	LADDER, // Used by players only when going onto a ladder
	OBSERVER, // Observer movement, depends on player's observer mode
};

enum class ESignOnState {
	CONNECTED = 2,
	SPAWNED = 5,
	FULL,
	CHANGELEVEL
};

enum class EKeystroke {
	RELEASE = 4,
	PRESS,
	SCROLL
};

enum class ELifeState {
	ALIVE,
	KILLCAM,
	DEAD
};

enum class ETeam {
	NONE,
	SPECTATOR,
	TERRORISTS,
	COUNTERTERRORISTS
};

enum class EWeaponType {
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

enum class EWeapon {
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
	P250,
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
	KNIFE_T = 59,
	M4A1_SILENCER,
	USP_SILENCER,
	CZ75A = 63,
	REVOLVER,
	KNIFE_BAYONET = 500,
	KNIFE_FLIP = 505,
	KNIFE_GUT,
	KNIFE_KARAMBIT,
	KNIFE_M9_BAYONET,
	KNIFE_TACTICAL,
	KNIFE_FALCHION = 512,
	KNIFE_BOWIE = 514,
	KNIFE_BUTTERFLY,
	KNIFE_PUSH
};
