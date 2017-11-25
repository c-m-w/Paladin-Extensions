#pragma once

//Defines
#define PI 3.141593f
#define FL_ONGROUND (1 << 0) // Touching ground
#define FL_DUCKING (1 << 1)  // Fully crouched

//Typedefs
typedef unsigned int frame;
typedef unsigned short total;

//Enums
enum class MoveType 
{
	NONE,		// never moves
	WALK = 2,	// Player only - moving on the ground
	NOCLIP = 8,	// No gravity, no collisions, still do velocity/avelocity
	LADDER,		// Used by players only when going onto a ladder
	OBSERVER,	// Observer movement, depends on player's observer mode
};

enum class SignOnState 
{
	CONNECTED = 2,
	SPAWNED = 5,
	FULL,
	CHANGELEVEL
};

enum class Keystroke 
{
	RELEASE = 4,
	PRESS = 5,
	SCROLL = 6
};

enum class LifeState 
{
	ALIVE,
	KILLCAM,
	DEAD
};

enum class Team 
{
	NONE = 0,
	SPECTATOR = 1,
	TERRORISTS = 2,
	COUNTERTERRORISTS = 3
};

enum class WeaponType 
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

enum class Weapon 
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

//Structs
struct Angle
{
	float pitch, yaw, roll; // y, x, z
};

struct Color
{
	uint8_t r, g, b, a;
};

struct Coordinate
{
	float x, y, z;
};