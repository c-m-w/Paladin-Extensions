#pragma once

#define PI 3.1415926535897932384626f

typedef long long moment;

extern HINSTANCE hInst;
extern std::atomic< bool > bExitState;
extern std::vector< std::thread > tThreads;

void Wait( unsigned int );
moment GetTime( );

template< typename datatype > void Limit( datatype &xStatus, datatype xMinimum, datatype xMaximum )
{
	if ( xMinimum > xStatus )
	{
		xStatus = xMinimum;
	}
	else if ( xStatus > xMaximum )
	{
		xStatus = xMaximum;
	}
}

enum class EQuitReasons
{
	UNKNOWN = -1,
	LOAD_LIBRARY_ERROR,
	SUCCESS,
	BLACKLISTED_CALL,
	PANIC
};

enum class EPremium
{
	BANNED = -2,
	EXPIRED,
	NOT_PREMIUM,
	PREMIUM
};

enum class EElevation
{
	UNTESTED = -1,
	NOT_ADMIN,
	ADMIN
};

enum class EAnticheatStatus
{
	NOT_FOUND = -1,
	FAILED,
	KILLED
};

/// CSGO stuff

#define MAX_ANGLE_DELTA 22.f // Max angle delta per tick
#define FL_ONGROUND (1 << 0) // At rest / on the ground
#define FL_DUCKING (1 << 1)  // Player flag -- Player is fully crouched
#define KS_DEFAULT 0b100 // default command state
#define KS_PRESS 0b1     // +command
#define KS_TICK 0b10     // +command, tick, -command

typedef unsigned int flag;
typedef unsigned short total;
typedef unsigned __int8 uint8;
typedef DWORD handle;

struct angle_t
{
	float pitch, yaw, roll; // y, x, z
	bool operator==( angle_t );
	bool operator!=( angle_t );
	angle_t operator+( angle_t );
	angle_t operator-( angle_t );
	angle_t &operator+=( angle_t );
	angle_t &operator-=( angle_t );
	angle_t operator*=( float rhs );
};

struct color_t
{
	uint8 r, g, b, a;
};

struct coordinate_t
{
	float x, y, z;
};

struct vector_t
{
	float dx, dy, dz;

	vector_t( );
	vector_t( coordinate_t, coordinate_t );
};

class CGlobalVars
{
public:
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

enum class EMoveType
{
	NONE,
	WALK = 2,
	NOCLIP = 8,
	LADDER,
};

enum class ESignOnState
{
	CONNECTED = 2,
	SPAWNED = 5,
	FULL,
	CHANGELEVEL
};

enum class ELifeState
{
	ALIVE,
	KILLCAM,
	DEAD
};

enum class ETeam
{
	NONE,
	SPECTATOR,
	TERRORISTS,
	COUNTERTERRORISTS
};

enum class EWeaponType
{
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

enum class EWeapon
{
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
