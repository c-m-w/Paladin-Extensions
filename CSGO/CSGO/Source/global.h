#pragma once

// global defines
#define PI 3.141593f
#define MILLISECONDS_PER_SECOND 1000.f

#define PREMIUM_USERS unsigned __int8(55)
#define MESSAGE( Title, Text, Type ) MessageBox( nullptr, Text, Title, Type | MB_OK )
#define DECEMBER_FIRST moment(1512086400000) // time since epoch in milliseconds to december first 2017
#define DAY moment(8640000) // day in milliseconds

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
#define LS_ALIVE (1 << 8) //
#define ENTITY_DISTANCE 0x10 // Distance between entities

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

// TODO TEST

class CPlayer
{
private:
	BYTE pad_0x0[ 0x60 ];
public:
	int bIsAutoaimTarget; // 0x60
private:
	BYTE pad_0x64[ 0xc ];
public:
	int clrRender; // 0x70
	int cellbits; // 0x74
private:
	BYTE pad_0x78[ 0x4 ];
public:
	int cellX; // 0x7c
	int cellY; // 0x80
	int cellZ; // 0x84
private:
	BYTE pad_0x88[ 0x64 ];
public:
	int fEffects; // 0xec
	int iTeamNum; // 0xf0
	int iPendingTeamNum; // 0xf4
	int nNextThinkTick; // 0xf8
	int iHealth; // 0xfc
	int fFlags; // 0x100
	vector_t vecViewOffset; // 0x104
	vector_t vecVelocity; // 0x110
	vector_t vecBaseVelocity; // 0x11c
private:
	BYTE pad_0x150[ 0x30 ];
public:
	vector_t angRotation; // 0x128
	vector_t vecOrigin; // 0x134
	float flFriction; // 0x140
	int moveparent; // 0x144
	int hOwnerEntity; // 0x148
	int hGroundEntity; // 0x14c
	char* iName; // 0x150
private:
	BYTE pad_0x154[ 0x100 ];
public:
	int nModelIndex; // 0x254
	int nRenderFX; // 0x256
	int nRenderMode; // 0x257
	int nWaterLevel; // 0x25a
	int lifeState; // 0x25b
	int flAnimTime; // 0x25c
private:
	BYTE pad_0x260[ 0x4 ];
public:
	int flSimulationTime; // 0x264
private:
	BYTE pad_0x268[ 0xD ];
public:
	int bClientSideRagdoll; // 0x275
private:
	BYTE pad_0x279[ 0x4F ];
public:
	float flUseLookAtAngle; // 0x2c8
private:
	BYTE pad_0x2cc[ 0x1c ];
public:
	int iParentAttachment; // 0x2e8
private:
	BYTE pad_0x2ec[ 0x4 ];
public:
	float fadeMinDist; // 0x2f0
	float fadeMaxDist; // 0x2f4
	float flFadeScale; // 0x2f8
private:
	BYTE pad_0x2fc[ 0x9C ];
public:
	float flElasticity; // 0x398
	float flShadowCastDistance; // 0x39c
private:
	BYTE pad_0x3a0[ 0xd0 ];
public:
	int CollisionGroup; // 0x470
private:
	BYTE pad_0x474[ 0x4c2 ];
public:
	int bSimulatedEveryTick; // 0x936
	int bAnimatedEveryTick; // 0x937
	int bAlternateSorting; // 0x938
	int bSpotted; // 0x939
	bool bSpottedBy[ 65 ]; // 0x93a
private:
	BYTE pad_0x97b[ 0x1 ];
public:
	int bSpottedByMask[ 2 ]; // 0x97c
	int nMinCPULevel; // 0x984
	int nMaxCPULevel; // 0x985
	int nMinGPULevel; // 0x986
	int nMaxGPULevel; // 0x987
	int iTextureFrameIndex; // 0x988
private:
	BYTE pad_0x98c[ 0x8 ];
public:
	int hEffectEntity; // 0x994
	int nHitboxSet; // 0x9fc
private:
	BYTE pad_0xa00[ 0x14 ];
public:
	float flCycle; // 0xa14
	float flPlaybackRate; // 0xa18
	int nSkin; // 0xa1c
	int nBody; // 0xa20
private:
	BYTE pad_0xa24[ 0x14 ];
public:
	int nNewSequenceParity; // 0xa38
	int nResetEventsParity; // 0xa3c
private:
	BYTE pad_0xa40[ 0x8 ];
public:
	int flEncodedController[ 4 ]; // 0xa48
	int nMuzzleFlashParity; // 0xa58
private:
	BYTE pad_0xa5c[ 0x1c14 ];
public:
	vector_t vecForce; // 0x2670
	int nForceBone; // 0x267c
private:
	BYTE pad_0x2680[ 0x30 ];
public:
	int bClientSideFrameReset; // 0x26b0
private:
	BYTE pad_0x26b4[ 0x34 ];
public:
	float flFrozen; // 0x26e8
private:
	BYTE pad_0x26ec[ 0x4c ];
public:
	float flModelScale; // 0x2738
	int ScaleType; // 0x273c
private:
	BYTE pad_0x2740[ 0x24 ];
public:
	int flPoseParameter[ 24 ]; // 0x2764
private:
	BYTE pad_0x27c4[ 0xc8 ];
public:
	int bClientSideAnimation; // 0x288c
private:
	BYTE pad_0x2890[ 0x1c ];
public:
	int nSequence; // 0x28ac
private:
	BYTE pad_0x28b0[ 0x84 ];
public:
	int hLightingOrigin; // 0x2934
private:
	BYTE pad_0x2938[ 0x2 ];
public:
	int bSuppressAnimSounds; // 0x293a
private:
	BYTE pad_0x293c[ 0xA4 ];
public:
	vector_t viewtarget; // 0x29e0
private:
	BYTE pad_0x29ec[ 0x2c ];
public:
	int flexWeight[ 96 ]; // 0x2a18
private:
	BYTE pad_0x2b98[ 0x2c ];
public:
	int blinktoggle; // 0x2bc4
private:
	BYTE pad_0x2bc8[ 0x198 ];
public:
	float flNextAttack; // 0x2d60
	int LastHitGroup; // 0x2d64
	int iAmmo[ 32 ]; // 0x2d68
	int hMyWeapons[ 64 ]; // 0x2de8
	int hActiveWeapon; // 0x2ee8
	float flTimeOfLastInjury; // 0x2eec
	int nRelativeDirectionOfLastInjury;// 0x2ef0
private:
	BYTE pad_0x2ef4[ 0x4C ];
public:
	int iCoachingTeam; // 0x2f40
private:
	BYTE pad_0x2f44[ 0x26C ];
public:
	int hTonemapController; // 0x31b0
private:
	BYTE pad_0x31b2[ 0x16 ];
public:
	int iFOV; // 0x31c8
	int iFOVStart; // 0x31cc
private:
	BYTE pad_0x31d0[ 0x14 ];
public:
	int ladderSurfaceProps; // 0x31e4
private:
	BYTE pad_0x31e8[ 0x4 ];
public:
	float flFOVTime; // 0x31ec
private:
	BYTE pad_0x31f0[ 0x18 ];
public:
	vector_t vecLadderNormal; // 0x3208
private:
	BYTE pad_0x3214[ 0x24 ];
public:
	int iBonusProgress; // 0x3238
	int iBonusChallenge; // 0x323c
	float flMaxspeed; // 0x3240
	int hZoomOwner; // 0x3244
private:
	BYTE pad_0x3248[ 0xc ];
public:
	int vphysicsCollisionState; // 0x3254
private:
	BYTE pad_0x3258[ 0x8c ];
public:
	int afPhysicsFlags; // 0x32e4
	int hVehicle; // 0x32e8
	int hLastWeapon; // 0x32ec
	int hViewModel; // 0x32f0
private:
	BYTE pad_0x32f4[ 0x24 ];
public:
	int fOnTarget; // 0x3318
	int hUseEntity; // 0x331c
	int iDefaultFOV; // 0x3320
private:
	BYTE pad_0x3324[ 0x8 ];
public:
	int hViewEntity; // 0x332c
	int bShouldDrawPlayerWhileUsingViewEntity;// 0x3330
	int hConstrapublicEntity; // 0x3334
	vector_t vecConstrapublicCenter; // 0x3338
	float flConstrapublicRadius; // 0x3344
	float flConstrapublicWidth; // 0x3348
	float flConstrapublicSpeedFactor; // 0x334c
	int bConstrapublicPastRadius; // 0x3350
private:
	BYTE pad_0x3354[ 0x8 ];
public:
	int iDeathPostEffect; // 0x335c
	int iObserverMode; // 0x3360
	int bActiveCameraMan; // 0x3364
	int bCameraManXRay; // 0x3365
	int bCameraManOverview; // 0x3366
	int bCameraManScoreBoard; // 0x3367
	int uCameraManGraphs; // 0x3368
private:
	BYTE pad_0x336c[ 0x8 ];
public:
	int hObserverTarget; // 0x3374
private:
	BYTE pad_0x3378[ 0x34 ];
public:
	float flDeathTime; // 0x33ac
	float fForceTeam; // 0x33b0
private:
	BYTE pad_0x33b4[ 0x60 ];
public:
	int nTickBase; // 0x3414
private:
	BYTE pad_0x3418[ 0x160 ];
public:
	float flLaggedMovementValue; // 0x3578
private:
	BYTE pad_0x357c[ 0x1c ];
public:
	char* szLastPlaceName; // 0x3598
private:
	BYTE pad_0x359c[ 0x20 ];
public:
	int ubEFNopublicInterpParity; // 0x35bc
private:
	BYTE pad_0x35c0[ 0x1bc ];
public:
	int hPostProcessCtrl; // 0x377c
	int hColorCorrectionCtrl; // 0x3780
private:
	BYTE pad_0x3784[ 0x4 ];
public:
	int hPlayerFogCtrl; // 0x3788
private:
	BYTE pad_0x378C[ 0x100 ];
public:
	int bIsScoped; // 0x388c
	int bIsWalking; // 0x388d
	int bResumeZoom; // 0x388e
	int iPlayerState; // 0x3890
	int bIsDefusing; // 0x3894
	int bIsGrabbingHostage; // 0x3895
	int bIsRescuing; // 0x3896
	float fImmuneToGunGameDamageTime;// 0x3898
private:
	BYTE pad_0x389c[ 0x4 ];
public:
	int bGunGameImmunity; // 0x38a0
	int bHasMovedSinceSpawn; // 0x38a1
	int bMadeFinalGunGameProgressiveKill;// 0x38a2
	int iGunGameProgressiveWeaponIndex;// 0x38a4
	int iNumGunGameTRKillPopublic; // 0x38a8
	int iNumGunGameKillsWithCurrentWeapon;// 0x38ac
	int iNumRoundKills; // 0x38b0
	int iNumRoundKillsHeadshots; // 0x38b4
	float fMolotovUseTime; // 0x38b8
	float fMolotovDamageTime; // 0x38bc
	int bInBombZone; // 0x38c0
	int bInBuyZone; // 0x38c1
	int bInNoDefuseArea; // 0x38c2
	int iThrowGrenadeCounter; // 0x38c4
	int bWaitForNoAttack; // 0x38c8
	int bIsRespawningForDMBonus; // 0x38c9
	float flGuardianTooFarDistFrac; // 0x38cc
	float flDetectedByEnemySensorTime;// 0x38d0
private:
	BYTE pad_0x38d4[ 0x4 ];
public:
	int bKilledByTaser; // 0x38d8
	int iMoveState; // 0x38dc
	int bCanMoveDuringFreezePeriod;// 0x38e0
	int isCurrentGunGameLeader; // 0x38e1
	int isCurrentGunGameTeamLeader;// 0x38e2
	char* szArmsModel; // 0x38e3
private:
	BYTE pad_0x38e7[ 0xfd ];
public:
	float flLowerBodyYawTarget; // 0x39e4
	int bStrafing; // 0x39e8
private:
	BYTE pad_0x39ec[ 0x68a8 ];
public:
	int iAddonBits; // 0xa294
	int iPrimaryAddon; // 0xa298
	int iSecondaryAddon; // 0xa29c
	int iProgressBarDuration; // 0xa2a0
	float flProgressBarStartTime; // 0xa2a4
	float flStamina; // 0xa2a8
	int iDirection; // 0xa2ac
	int iShotsFired; // 0xa2b0
	int nNumFastDucks; // 0xa2b4
	int bDuckOverride; // 0xa2b8
	int bNightVisionOn; // 0xa2b9
	int bHasNightVision; // 0xa2ba
	float flVelocityModifier; // 0xa2bc
	float flGroundAccelLinearFracLastTime;// 0xa2c0
	int iStartAccount; // 0xa2c4
	int totalHitsOnServer; // 0xa2c8
private:
	BYTE pad_0xa2cc[ 0x4 ];
public:
	int hRagdoll; // 0xa2d0
	int hCarriedHostage; // 0xa2d4
	int hCarriedHostageProp; // 0xa2d8
private:
	BYTE pad_0xa2dc[ 0x18 ];
public:
	float flFlashMaxAlpha; // 0xa2f4
	float flFlashDuration; // 0xa2f8
private:
	BYTE pad_0xa2fc[ 0x40 ];
public:
	int iMatchStats_Kills[ 30 ]; // 0xa33c
	int iMatchStats_Damage[ 30 ]; // 0xa3b4
	int iMatchStats_EquipmentValue[ 30 ];// 0xa42c
	int iMatchStats_MoneySaved[ 30 ];// 0xa4a4
	int iMatchStats_KillReward[ 30 ];// 0xa51c
	int iMatchStats_LiveTime[ 30 ];// 0xa594
	int iMatchStats_Deaths[ 30 ]; // 0xa60c
	int iMatchStats_Assists[ 30 ];// 0xa684
	int iMatchStats_HeadShotKills[ 30 ];// 0xa6fc
	int iMatchStats_Objective[ 30 ];// 0xa774
	int iMatchStats_CashEarned[ 30 ];// 0xa7ec
	int iMatchStats_UtilityDamage[ 30 ];// 0xa864
	int iMatchStats_EnemiesFlashed[ 30 ];// 0xa8dc
private:
	BYTE pad_0xa954[ 0x60 ];
public:
	int nQuestProgressReason; // 0xa9b4
	int unCurrentEquipmentValue; // 0xa9b8
	int unRoundStartEquipmentValue;// 0xa9ba
	int unFreezetimeEndEquipmentValue;// 0xa9bc
	int rank[ 6 ]; // 0xa9c0
	int unMusicID; // 0xa9d8
	int iAccount; // 0xa9dc
	int bHasHelmet; // 0xa9e0
	int bHasHeavyArmor; // 0xa9e1
	int iClass; // 0xa9e4
	int ArmorValue; // 0xa9e8
	float angEyeAngles[ 2 ]; // 0xa9ec
private:
	BYTE pad_0xa9f4[ 0x4 ];
public:
	int bHasDefuser; // 0xa9f8
	int bInHostageRescueZone; // 0xa9f9
private:
	BYTE pad_0xa9fd[ 0xd ];
public:
	int bHud_MiniScoreHidden; // 0xaa0a
	int bHud_RadarHidden; // 0xaa0b
	int nLastKillerIndex; // 0xaa0c
	int nLastConcurrentKilled; // 0xaa10
	int nDeathCamMusic; // 0xaa14
private:
	BYTE pad_0xaa18[ 0xfc ];
public:
	int cycleLatch; // 0xab14
private:
	BYTE pad_0xab18[ 0x4 ];
public:
	bool bPlayerDominated[ 65 ]; // 0xab1c
	bool bPlayerDominatingMe[ 65 ];// 0xab5d
private:
	BYTE pad_0xab9e[ 0x2 ];
public:
	int iWeaponPurchasesThisRound[ 64 ];// 0xaba0
private:
	BYTE pad_0xaca0[ 0x8 ];
public:
	int bIsLookingAtWeapon; // 0xaca8
	int bIsHoldingLookAtWeapon; // 0xaca9
private:
	BYTE pad_0xacad[ 0x94 ];
public:
	int bIsAssassinationTarget; // 0xad41
	int bIsControllingBot; // 0xad42
	int bCanControlObservedBot; // 0xad43
	int iControlledBotEntIndex; // 0xad44
private:
	BYTE pad_0xad48[ 0x8 ];
public:
	int bHasControlledBotThisRound;// 0xad50
}; // total size = 0xad51
