#pragma once

// global defines
#define PI 3.141593f
#define MILLISECONDS_PER_SECOND 1000.f

#define PREMIUM_USERS unsigned __int8(55)
#define DECEMBER_FIRST moment(1512086400000) // time since epoch in milliseconds to december first 2017
#define DAY moment(8640000) // day in milliseconds

#define MESSAGE( Title, Text, Type ) MessageBox( nullptr, Text, Title, Type | MB_OK );

// global typedefs
typedef long long moment;
typedef BYTE unknown;

// global structs
struct angle_t
{
	float pitch, yaw, roll; // y, x, z

	bool operator==( angle_t );
	bool operator!=( angle_t );
	angle_t operator+( angle_t );
	angle_t operator-( angle_t );
	angle_t operator*( float );
	angle_t operator/( float );
	angle_t &operator+=( angle_t );
	angle_t &operator-=( angle_t );
	angle_t operator*=( float );
	angle_t operator/=( float );
};

struct color_t
{
	BYTE r, g, b, a;
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

// global variables
extern HINSTANCE hInst;
extern bool bExitState;
extern std::vector< std::thread > tThreads;

// global functions
void Wait( unsigned );
moment GetMoment( );

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

template< typename datatype > void Absolute( datatype &xStatus )
{
	if ( xStatus < 0 )
	{
		xStatus = -xStatus;
	}
}

// global enums
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

// defines
#define MAX_ANGLE_DELTA 22.f // Max angle delta per tick
#define FL_ONGROUND (1 << 0) // At rest / on the ground
#define FL_DUCKING (1 << 1) // Player flag -- Player is fully crouched
#define FA_DEFAULT 0b100 // default command state
#define FA_PRESS 0b1 // +command
#define FA_TICK 0b10 // +command, tick, -command
#define ENTITY_DISTANCE 0x10 //Distance between entities

#define MAX_SENSITIVITY 1000.f
#define MIN_SENSITIVITY 0.f
#define MAX_FLASHALPHA 255.f
#define MIN_FLASHALPHA 0.f
#define MAX_FIELDOFVIEW 180
#define MIN_FIELDOFVIEW 0
#define MAX_PITCH 89.f
#define MIN_PITCH -89.f
#define MAX_YAW 180.f
#define MIN_YAW -180.f
#define MAX_ROLL 50.f
#define MIN_ROLL 50.f

// typedefs
typedef unsigned long long flag;
typedef unsigned short total;
typedef unsigned long handle;

// enums
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

// classes
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

	bool operator==( CGlobalVars );
	bool operator!=( CGlobalVars );
};

class CBaseEntity
{
	BYTE pad_0x0[ 0x70 ];		// 0x0000
public:
	color_t clrRender;			// 0x0070
private:
	BYTE pad_0x74[ 0x75 ];		// 0x0074
public:
	bool bDormant;				// 0x00E9
private:
	BYTE pad_0xEA[ 0x6 ];		// 0x00EA
public:
	ETeam tTeamNum;				// 0x00F0
private:
	BYTE pad_0xF4[ 0x8 ];		// 0x00F4
public:
	int iHealth;				// 0x00FC
	int fFlags;					// 0x0100
	angle_t angViewOffset;		// 0x0104
	vector_t vecVelocity;		// 0x0110
private:
	BYTE pad_0x11C[ 0xC ];		// 0x011C
public:
	angle_t angRotation;		// 0x0128
	coordinate_t corOrigin;		// 0x0134
private:
	BYTE pad_0x140[ 0x118 ];	// 0x0140
public:
	EMoveType mtMoveType;		// 0x0258
private:
	BYTE pad_0x259[ 0x2 ];		// 0x0259
public:
	ELifeState lsLifeState;		// 0x025B
private:
	BYTE pad_0x025D[ 0x6DC ];	// 0x025D
public:
	bool bSpotted;				// 0x0939
	// TODO m_bHasDefuser, m_bIsDefusing, m_bIsScoped, m_iNumRoundKills, m_bHasHelmet, 
};

class CLocalPlayer: public CBaseEntity
{
	BYTE pad_0x025D[ 0x2DC1 ];	// 0x301C
public:
	angle_t angAimPunch; 		// 0x301C
private:
	BYTE pad_0x3028[ 0x2E4 ];	// 0x3028
public:
	int iDefaultFOV;			// 0x330C
private:
	BYTE pad_0x330E[ 0x5AA ]; 	// 0x330E
public:
	int iThrowGrenadeCounter;	// 0x38B8
private:
	BYTE pad_0x38BA[ 0x69F6 ]; 	// 0x38BA
public:
	int iShotsFired;			// 0xA2B0
private:
	BYTE pad_0xA2B2[ 0x16 ];	// 0xA2B2
public:
	total totalHitsOnServer;	// 0xA2C8
private:
	BYTE pad_0xA2CA[ 0x2C ];	// 0xA2CA
public:
	float flFlashMaxAlpha;		// 0xA2F4
};								// 0x025C +1byte
