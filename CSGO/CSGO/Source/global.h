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
	angle_t operator+=( angle_t );
	angle_t operator-=( angle_t );
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
#define FL_DUCKING (1 << 1) // Player FLAG -- Player is fully crouched
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
typedef unsigned int FLAG;
typedef unsigned int EHANDLE;

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

class CPlayer
{
	BYTE x0[0x60];
public:
	bool bAutoaimTarget; // 0x60
private:
	BYTE x64[0xC];
public:
	color_t clrRender; // 0x70
	int cellbits; // 0x74
private:
	BYTE x78[0x4];
public:
	coordinate_t corCell; // 0x7c
private:
	BYTE x88[0x64]; // TODO dormancy
public:
	FLAG fEffects; // 0xec
	int iTeamNum; // 0xf0
	int iPendingTeamNum; // 0xf4
	unsigned int nNextThinkTick; // 0xf8
	int iHealth; // 0xfc
	FLAG fFlags; // 0x100
	vector_t vecViewOffset; // 0x104
	vector_t vecVelocity; // 0x110
	vector_t vecBaseVelocity; // 0x11c
	angle_t angRotation; // 0x128
	coordinate_t corOrigin; // 0x134
	float flFriction; // 0x140
	int moveparent; // 0x144
	EHANDLE hOwnerEntity; // 0x148
	EHANDLE hGroundEntity; // 0x14c
	char* iName; // 0x150
private:
	BYTE x154[0x100];
public:
	unsigned short nModelIndex; // 0x254
	unsigned __int8 nRenderFX; // 0x256
	unsigned short nRenderMode; // 0x257
	unsigned __int8 nWaterLevel; // 0x25a
	bool lifeState; // 0x25b
	float flAnimTime; // 0x25c
private:
	BYTE x260[0x4];
public:
	float flSimulationTime; // 0x264
private:
	BYTE x268[0xD];
public:
	bool bClientSideRagdoll; // 0x275
private:
	BYTE x279[0x4F];
public:
	float flUseLookAtAngle; // 0x2c8
private:
	BYTE x2CC[0x1C];
public:
	int iParentAttachment; // 0x2e8
private:
	BYTE x2EC[0x4];
public:
	float fadeMinDist; // 0x2f0
	float fadeMaxDist; // 0x2f4
	float flFadeScale; // 0x2f8
private:
	BYTE x2FC[0x9C];
public:
	float flElasticity; // 0x398
	float flShadowCastDistance; // 0x39c
private:
	BYTE x3A0[0xD0];
public:
	int CollisionGroup; // 0x470
private:
	BYTE x474[0x4C2];
public:
	bool bSimulatedEveryTick; // 0x936
	bool bAnimatedEveryTick; // 0x937
	bool bAlternateSorting; // 0x938
	bool bSpotted; // 0x939
	bool bSpottedBy[64]; // 0x93a
	bool bSpottedByMask[10]; // 0x97a
	unsigned __int8 nMinCPULevel; // 0x984
	unsigned __int8 nMaxCPULevel; // 0x985
	unsigned __int8 nMinGPULevel; // 0x986
	unsigned __int8 nMaxGPULevel; // 0x987
	int iTextureFrameIndex; // 0x988
private:
	BYTE x98C[0x8];
public:
	EHANDLE hEffectEntity; // 0x994
private:
	BYTE x998[0x64];
public:
	unsigned int nHitboxSet; // 0x9fc
private:
	BYTE xA00[0x14];
public:
	float flCycle; // 0xa14
	float flPlaybackRate; // 0xa18
	unsigned int nSkin; // 0xa1c
	unsigned int nBody; // 0xa20
private:
	BYTE xA24[0x14];
public:
	unsigned int nNewSequenceParity; // 0xa38
	unsigned int nResetEventsParity; // 0xa3c
private:
	BYTE xA40[0x8];
public:
	float flEncodedController[4]; // 0xa48
	unsigned int nMuzzleFlashParity; // 0xa58
private:
	BYTE xA5C[0x1C14];
public:
	vector_t vecForce; // 0x2670
	unsigned int nForceBone; // 0x267c
private:
	BYTE x2680[0x30];
public:
	bool bClientSideFrameReset; // 0x26b0
private:
	BYTE x26B4[0x34];
public:
	float flFrozen; // 0x26e8
private:
	BYTE x26EC[0x4C];
public:
	float flModelScale; // 0x2738
	int ScaleType; // 0x273c
private:
	BYTE x2740[0x24];
public:
	float flPoseParameter[24]; // 0x2764
private:
	BYTE x27C4[0xC8];
public:
	bool bClientSideAnimation; // 0x288c
private:
	BYTE x2890[0x1C];
public:
	unsigned int nSequence; // 0x28ac
private:
	BYTE x28B0[0x84];
public:
	EHANDLE hLightingOrigin; // 0x2934
private:
	BYTE x2938[0x2];
public:
	bool bSuppressAnimSounds; // 0x293a
private:
	BYTE x293C[0xA4];
public:
	vector_t viewtarget; // 0x29e0
private:
	BYTE x29EC[0x2C];
public:
	float flexWeight[96]; // 0x2a18
private:
	BYTE x2B98[0x2C];
public:
	bool blinktoggle; // 0x2bc4
private:
	BYTE x2BC8[0x198];
public:
	float flNextAttack; // 0x2d60
	int LastHitGroup; // 0x2d64
	int iAmmo[32]; // 0x2d68
	EHANDLE hMyWeapons[64]; // 0x2de8
	EHANDLE hActiveWeapon; // 0x2ee8
	float flTimeOfLastInjury; // 0x2eec
	unsigned int nRelativeDirectionOfLastInjury; // 0x2ef0
private:
	BYTE x2EF4[0x4C];
public:
	int iCoachingTeam; // 0x2f40
private:
	BYTE x2F44[0x26C]; // TODO get aimpunch and whatnot
public:
	EHANDLE hTonemapController; // 0x31b0
private:
	BYTE x31B4[0x12];
public:
	int iFOV; // 0x31c8
	int iFOVStart; // 0x31cc
private:
	BYTE x31D0[0x14];
public:
	int ladderSurfaceProps; // 0x31e4
private:
	BYTE x31F8[0x4];
public:
	float flFOVTime; // 0x31ec
private:
	BYTE x31F0[0x18];
public:
	vector_t vecLadderNormal; // 0x3208
private:
	BYTE x3214[0x24];
public:
	int iBonusProgress; // 0x3238
	int iBonusChallenge; // 0x323c
	float flMaxspeed; // 0x3240
	EHANDLE hZoomOwner; // 0x3244
private:
	BYTE x3248[0xC];
public:
	int vphysicsCollisionState; // 0x3254
private:
	BYTE x3258[0x8C];
public:
	FLAG fPhysicsFlags; // 0x32e4
	EHANDLE hVehicle; // 0x32e8
	EHANDLE hLastWeapon; // 0x32ec
	EHANDLE hViewModel; // 0x32f0
private:
	BYTE x32F4[0x24];
public:
	FLAG fOnTarget; // 0x3318
	EHANDLE hUseEntity; // 0x331c
	int iDefaultFOV; // 0x3320
private:
	BYTE x3324[0x8];
public:
	EHANDLE hViewEntity; // 0x332c
	bool bShouldDrawPlayerWhileUsingViewEntity; // 0x3330
	EHANDLE hConstrapublicEntity; // 0x3334
	vector_t vecConstrapublicCenter; // 0x3338
	float flConstrapublicRadius; // 0x3344
	float flConstrapublicWidth; // 0x3348
	float flConstrapublicSpeedFactor; // 0x334c
	bool bConstrapublicPastRadius; // 0x3350
private:
	BYTE x3354[0x8];
public:
	int iDeathPostEffect; // 0x335c
	int iObserverMode; // 0x3360
	bool bActiveCameraMan; // 0x3364
	bool bCameraManXRay; // 0x3365
	bool bCameraManOverview; // 0x3366
	bool bCameraManScoreBoard; // 0x3367
	unsigned int uCameraManGraphs; // 0x3368
private:
	BYTE x336C[0x8];
public:
	EHANDLE hObserverTarget; // 0x3374
private:
	BYTE x3378[0x34];
public:
	float flDeathTime; // 0x33ac
	FLAG fForceTeam; // 0x33b0
private:
	BYTE x33B4[0x60];
public:
	unsigned int nTickBase; // 0x3414
private:
	BYTE x3418[0x160];
public:
	float flLaggedMovementValue; // 0x3578
private:
	BYTE x357C[0x1C];
public:
	char* szLastPlaceName; // 0x3598
private:
	BYTE x359C[0x20];
public:
	unsigned int ubEFNopublicInterpParity; // 0x35bc
private:
	BYTE x35C0[0x1BC];
public:
	EHANDLE hPostProcessCtrl; // 0x377c
	EHANDLE hColorCorrectionCtrl; // 0x3780
private:
	BYTE x3784[0x4];
public:
	EHANDLE hPlayerFogCtrl; // 0x3788
private:
	BYTE x378C[0x100];
public:
	bool bScoped; // 0x388c
	bool bWalking; // 0x388d
	bool bResumeZoom; // 0x388e
	int iPlayerState; // 0x3890
	bool bDefusing; // 0x3894
	bool bGrabbgHostage; // 0x3895
	bool bRescuing; // 0x3896
	FLAG fImmuneToGunGameDamageTime; // 0x3898
private:
	BYTE x389C[0x4];
public:
	bool bGunGameImmunity; // 0x38a0
	bool bHasMovedSinceSpawn; // 0x38a1
	bool bMadeFinalGunGameProgressiveKill; // 0x38a2
	int iGunGameProgressiveWeaponIndex; // 0x38a4
	int iNumGunGameTRKillPopublic; // 0x38a8
	int iNumGunGameKillsWithCurrentWeapon; // 0x38ac
	int iNumRoundKills; // 0x38b0
	int iNumRoundKillsHeadshots; // 0x38b4
	FLAG fMolotovUseTime; // 0x38b8
	FLAG fMolotovDamageTime; // 0x38bc
	bool bBombZone; // 0x38c0
	bool bBuyZone; // 0x38c1
	bool bNoDefuseArea; // 0x38c2
	int iThrowGrenadeCounter; // 0x38c4
	bool bWaitForNoAttack; // 0x38c8
	bool bRespawningForDMBonus; // 0x38c9
	float flGuardianTooFarDistFrac; // 0x38cc
	float flDetectedByEnemySensorTime; // 0x38d0
private:
	BYTE x38D4[0x4];
public:
	bool bKilledByTaser; // 0x38d8
	int iMoveState; // 0x38dc
	bool bCanMoveDuringFreezePeriod; // 0x38e0
	bool isCurrentGunGameLeader; // 0x38e1
	bool isCurrentGunGameTeamLeader; // 0x38e2
	char* szArmsModel; // 0x38e4
private:
	BYTE x38E8[0xFC];
public:
	float flLowerBodyYawTarget; // 0x39e4
	bool bStrafing; // 0x39e8
private:
	BYTE x39EC[0x68A8];
public:
	int iAddonBits; // 0xa294
	int iPrimaryAddon; // 0xa298
	int iSecondaryAddon; // 0xa29c
	int iProgressBarDuration; // 0xa2a0
	float flProgressBarStartTime; // 0xa2a4
	float flStamina; // 0xa2a8
	int iDirection; // 0xa2ac
	int iShotsFired; // 0xa2b0
	unsigned int nNumFastDucks; // 0xa2b4
	bool bDuckOverride; // 0xa2b8
	bool bNightVisionOn; // 0xa2b9
	bool bHasNightVision; // 0xa2ba
	float flVelocityModifier; // 0xa2bc
	float flGroundAccelLinearFracLastTime; // 0xa2c0
	int iStartAccount; // 0xa2c4
	unsigned int totalHitsOnServer; // 0xa2c8
private:
	BYTE xA2CC[0x4];
public:
	EHANDLE hRagdoll; // 0xa2d0
	EHANDLE hCarriedHostage; // 0xa2d4
	EHANDLE hCarriedHostageProp; // 0xa2d8
private:
	BYTE xA2DC[0x18];
public:
	float flFlashMaxAlpha; // 0xa2f4
	float flFlashDuration; // 0xa2f8
private:
	BYTE xA2FC[0x40];
public:
	int iMatchStats_Kills[30]; // 0xa33c
	int iMatchStats_Damage[30]; // 0xa3b4
	int iMatchStats_EquipmentValue[30]; // 0xa42c
	int iMatchStats_MoneySaved[30]; // 0xa4a4
	int iMatchStats_KillReward[30]; // 0xa51c
	int iMatchStats_LiveTime[30]; // 0xa594
	int iMatchStats_Deaths[30]; // 0xa60c
	int iMatchStats_Assists[30]; // 0xa684
	int iMatchStats_HeadShotKills[30]; // 0xa6fc
	int iMatchStats_Objective[30]; // 0xa774
	int iMatchStats_CashEarned[30]; // 0xa7ec
	int iMatchStats_UtilityDamage[30]; // 0xa864
	int iMatchStats_EnemiesFlashed[30]; // 0xa8dc
private:
	BYTE xA954[0x8A0];
public:
	unsigned int nQuestProgressReason; // 0xb1f4
	unsigned short unCurrentEquipmentValue; // 0xb1f8
	unsigned short unRoundStartEquipmentValue; // 0xb1fa
	unsigned short unFreezetimeEndEquipmentValue; // 0xb1fc
	int rank[6]; // 0xb200
	unsigned short unMusicID; // 0xb218
private:
	BYTE xB21A[0xE];
public:
	int iAccount; // 0xb228
	bool bHasHelmet; // 0xb22c
	bool bHasHeavyArmor; // 0xb22d
private:
	BYTE xB22E[0x6];
public:
	int iClass; // 0xb234
	int iArmorValue; // 0xb238
	angle_t angEyeAngles; // 0xb23c
	bool bHasDefuser; // 0xb248
	bool bHostageRescueZone; // 0xb249
private:
	BYTE xB24A[0x20];
public:
	bool bHud_MiniScoreHidden; // 0xb26a
	bool bHud_RadarHidden; // 0xb26b
	unsigned int nLastKillerIndex; // 0xb26c
	unsigned int nLastConcurrentKilled; // 0xb270
	unsigned int nDeathCamMusic; // 0xb274
private:
	BYTE xB278[0xEC];
public:
	int cycleLatch; // 0xb364
private:
	BYTE xB368[0x4];
public:
	bool bPlayerDominated[65]; // 0xb36c
	bool bPlayerDominatingMe[65]; // 0xb3ad
private:
	BYTE xB3AE[0x2];
public:
	int iWeaponPurchasesThisRound[64]; // 0xb3f0
private:
	BYTE xB4F0[0x308];
public:
	bool bLookingAtWeapon; // 0xb7f8
	bool bHoldingLookAtWeapon; // 0xb7f9
private:
	BYTE xB7FA[0x98];
public:
	bool bAssassinationTarget; // 0xb895
	bool bControllingBot; // 0xb896
	bool bCanControlObservedBot; // 0xb897
	int iControlledBotEntIndex; // 0xb898
private:
	BYTE xB89B[0x8];
public:
	bool bHasControlledBotThisRound; // 0xb8a4
}; // total size = 0xb8a5