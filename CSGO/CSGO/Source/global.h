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
public:
	private: BYTE pad_0x0[ 0x60 ];
	public: int bIsAutoaimTarget; // 0x60
	private: BYTE pad_0x64[ 0xc ];
	public: int clrRender; // 0x70
	public: int cellbits; // 0x74
	private: BYTE pad_0x78[ 0x4 ];
	public: int cellX; // 0x7c
	public: int cellY; // 0x80
	public: int cellZ; // 0x84
	private: BYTE pad_0x88[ 0x64 ];
	public: int fEffects; // 0xec
	public: int iTeamNum; // 0xf0
	public: int iPendingTeamNum; // 0xf4
	public: int nNextThinkTick; // 0xf8
	public: int iHealth; // 0xfc
	public: int fFlags; // 0x100
	public: float vecViewOffset[ 3 ]; // 0x104
	public: float vecVelocity[ 3 ];			// 0x110
	public: vector_t	 vecBaseVelocity;			// 0x11c
	private: BYTE pad_0x150[ 0x30 ];
	public: vector_t angRotation;				// 0x128
	public: vector_t	 vecOrigin;				// 0x134
	public: float flFriction;				// 0x140
	public: int moveparent;					// 0x144
	public: int hOwnerEntity; // 0x148
	public: int hGroundEntity; // 0x14c
	public: char* iName;					// 0x150
	private: BYTE pad_0x154[ 0x100 ];
	public: int nModelIndex;				// 0x254
	public: int nRenderFX;				// 0x256
	public: int nRenderMode;				// 0x257
	public: int nWaterLevel;				// 0x25a
	public: int lifeState;				// 0x25b
	public: int flAnimTime;				// 0x25c
	private: BYTE pad_0x260[ 0x4 ];
	public: int flSimulationTime;		 // 0x264
	private: BYTE pad_0x268[ 0xD ];
	public: int bClientSideRagdoll;	 // 0x275
	private: BYTE pad_0x279[ 0x4F ];
	public: float flUseLookAtAngle; // 0x2c8
	private: BYTE pad_0x2cc[ 0x1c ];
	public: int iParentAttachment; // 0x2e8
	private: BYTE pad_0x2ec[ 0x4 ];
	public: float fadeMinDist;				// 0x2f0
	public: float fadeMaxDist;				// 0x2f4
	public: float flFadeScale;				// 0x2f8
	private: BYTE pad_0x2fc[ 0x9C ];
	public: float flElasticity;				// 0x398
	public: float flShadowCastDistance; // 0x39c
	private: BYTE pad_0x3a0[ 0xd0 ];
	public: int CollisionGroup; // 0x470
	private: BYTE pad_0x474[ 0x4c2 ];
	public: int bSimulatedEveryTick; // 0x936
	public: int bAnimatedEveryTick; // 0x937
	public: int bAlternateSorting; // 0x938
	public: int bSpotted;					// 0x939
	public: bool bSpottedBy[ 65 ]; // 0x93a
	private: BYTE pad_0x97b[ 0x1 ];
	public: int bSpottedByMask[ 2 ]; // 0x97c
	public: int nMinCPULevel;				// 0x984
	public: int nMaxCPULevel;				// 0x985
	public: int nMinGPULevel;				// 0x986
	public: int nMaxGPULevel;				// 0x987
	public: int iTextureFrameIndex;		// 0x988
	private: BYTE pad_0x98c[ 0x8 ];
	public: int hEffectEntity; // 0x994
	public: int nHitboxSet;				// 0x9fc
	private: BYTE pad_0xa00[ 0x14 ];
	public: float flCycle;					// 0xa14
	public: float flPlaybackRate; // 0xa18
	public: int nSkin;					// 0xa1c
	public: int nBody;					// 0xa20
	private: BYTE pad_0xa24[ 0x14 ];
	public: int nNewSequenceParity;		// 0xa38
	public: int nResetEventsParity;		// 0xa3c
	private: BYTE pad_0xa40[ 0x8 ];
	public: int flEncodedController[ 4 ]; // 0xa48
	public: int nMuzzleFlashParity; // 0xa58
	private: BYTE pad_0xa5c[ 0x1c14 ];
	public: vector_t	 vecForce;					// 0x2670
	public: int nForceBone;				// 0x267c
	private: BYTE pad_0x2680[ 0x30 ];
	public: int bClientSideFrameReset; // 0x26b0
	private: BYTE pad_0x26b4[ 0x34 ];
	public: float flFrozen;					// 0x26e8
	private: BYTE pad_0x26ec[ 0x4c ];
	public: float flModelScale;				// 0x2738
	public: int ScaleType;				// 0x273c
	private: BYTE pad_0x2740[ 0x24 ];
	public: int flPoseParameter[ 24 ];	// 0x2764
	private: BYTE pad_0x27c4[ 0xc8 ];
	public: int bClientSideAnimation; // 0x288c
	private: BYTE pad_0x2890[ 0x1c ];
	public: int nSequence;				// 0x28ac
	private: BYTE pad_0x28b0[ 0x84 ];
	public: int hLightingOrigin;			// 0x2934
	private: BYTE pad_0x2938[ 0x2 ];
	public: int bSuppressAnimSounds; // 0x293a
	private: BYTE pad_0x293c[ 0xA4 ];
	public: vector_t	 viewtarget;				// 0x29e0
	private: BYTE pad_0x29ec[ 0x2c ];
	public: int flexWeight[ 96 ]; // 0x2a18
	private: BYTE pad_0x2b98[ 0x2c ];
	public: int blinktoggle;				// 0x2bc4
	private: BYTE pad_0x2bc8[ 0x198 ];
	public: float flNextAttack;				// 0x2d60
	public: int LastHitGroup;				// 0x2d64
	public: int iAmmo[ 32 ];				// 0x2d68
	public: int hMyWeapons[ 64 ]; // 0x2de8
	public: int hActiveWeapon; // 0x2ee8
	public: float flTimeOfLastInjury; // 0x2eec
	public: int nRelativeDirectionOfLastInjury;// 0x2ef0
	private: BYTE pad_0x2ef4[ 0x4C ];
	public: int iCoachingTeam; // 0x2f40
	private: BYTE pad_0x2f44[ 0x26C ];
	public: int hTonemapController; // 0x31b0
	private: BYTE pad_0x31b2[ 0x16 ];
	public: int iFOV;						// 0x31c8
	public: int iFOVStart;				// 0x31cc
	private: BYTE pad_0x31d0[ 0x14 ];
	public: int ladderSurfaceProps; // 0x31e4
	private: BYTE pad_0x31e8[ 0x4 ];
	public: float flFOVTime;				// 0x31ec
	private: BYTE pad_0x31f0[ 0x18 ];
	public: vector_t	 vecLadderNormal; // 0x3208
	private: BYTE pad_0x3214[ 0x24 ];
	public: int iBonusProgress; // 0x3238
	public: int iBonusChallenge; // 0x323c
	public: float flMaxspeed;				// 0x3240
	public: int hZoomOwner;				// 0x3244
	private: BYTE pad_0x3248[ 0xc ];
	public: int vphysicsCollisionState; // 0x3254
	private: BYTE pad_0x3258[ 0x8c ];
	public: int afPhysicsFlags; // 0x32e4
	public: int hVehicle;					// 0x32e8
	public: int hLastWeapon;				// 0x32ec
	public: int hViewModel; // 0x32f0
	private: BYTE pad_0x32f4[ 0x24 ];
	public: int fOnTarget;				// 0x3318
	public: int hUseEntity;				// 0x331c
	public: int iDefaultFOV;				// 0x3320
	private: BYTE pad_0x3324[ 0x8 ];
	public: int hViewEntity;				// 0x332c
	public: int bShouldDrawPlayerWhileUsingViewEntity;// 0x3330
	public: int hConstrapublicEntity; // 0x3334
	public: vector_t	 vecConstrapublicCenter; // 0x3338
	public: float flConstrapublicRadius; // 0x3344
	public: float flConstrapublicWidth; // 0x3348
	public: float flConstrapublicSpeedFactor; // 0x334c
	public: int bConstrapublicPastRadius; // 0x3350
	private: BYTE	pad_0x3354[ 0x8 ];
	public: int iDeathPostEffect; // 0x335c
	public: int iObserverMode; // 0x3360
	public: int bActiveCameraMan; // 0x3364
	public: int bCameraManXRay; // 0x3365
	public: int bCameraManOverview; // 0x3366
	public: int bCameraManScoreBoard; // 0x3367
	public: int uCameraManGraphs; // 0x3368
	private: BYTE pad_0x336c[ 0x8 ];
	public: int hObserverTarget; // 0x3374
	private: BYTE pad_0x3378[ 0x34 ];
	public: float flDeathTime;				// 0x33ac
	public: float fForceTeam;				// 0x33b0
	private: BYTE pad_0x33b4[ 0x60 ];
	public: int nTickBase;				// 0x3414
	private: BYTE pad_0x3418[ 0x160 ];
	public: float flLaggedMovementValue; // 0x3578
	private: BYTE pad_0x357c[ 0x1c ];
	public: char* szLastPlaceName; // 0x3598
	private: BYTE pad_0x359c[ 0x20 ];
	public: int ubEFNopublicInterpParity; // 0x35bc
	private: BYTE pad_0x35c0[ 0x1bc ];
	public: int hPostProcessCtrl; // 0x377c
	public: int hColorCorrectionCtrl; // 0x3780
	private: BYTE pad_0x3784[ 0x4 ];
	public: int hPlayerFogCtrl; // 0x3788
	private: BYTE pad_0x378C[ 0x100 ];
	public: int bIsScoped;				// 0x388c
	public: int bIsWalking;				// 0x388d
	public: int bResumeZoom;				// 0x388e
	public: int iPlayerState;				// 0x3890
	public: int bIsDefusing;				// 0x3894
	public: int bIsGrabbingHostage; // 0x3895
	public: int bIsRescuing;				// 0x3896
	public: float fImmuneToGunGameDamageTime;// 0x3898
	private: BYTE pad_0x389c[ 0x4 ];
	public: int bGunGameImmunity; // 0x38a0
	public: int bHasMovedSinceSpawn; // 0x38a1
	public: int bMadeFinalGunGameProgressiveKill;// 0x38a2
	public: int iGunGameProgressiveWeaponIndex;// 0x38a4
	public: int iNumGunGameTRKillPopublic; // 0x38a8
	public: int iNumGunGameKillsWithCurrentWeapon;// 0x38ac
	public: int iNumRoundKills;			// 0x38b0
	public: int iNumRoundKillsHeadshots; // 0x38b4
	public: float fMolotovUseTime; // 0x38b8
	public: float fMolotovDamageTime; // 0x38bc
	public: int bInBombZone;				// 0x38c0
	public: int bInBuyZone;				// 0x38c1
	public: int bInNoDefuseArea; // 0x38c2
	public: int iThrowGrenadeCounter; // 0x38c4
	public: int bWaitForNoAttack;			// 0x38c8
	public: int bIsRespawningForDMBonus; // 0x38c9
	public: float flGuardianTooFarDistFrac; // 0x38cc
	public: float flDetectedByEnemySensorTime;// 0x38d0
	private: BYTE pad_0x38d4[ 0x4 ];
	public: int bKilledByTaser; // 0x38d8
	public: int iMoveState;				// 0x38dc
	public: int bCanMoveDuringFreezePeriod;// 0x38e0
	public: int isCurrentGunGameLeader; // 0x38e1
	public: int isCurrentGunGameTeamLeader;// 0x38e2
	public: char* szArmsModel;				// 0x38e3
	private: BYTE pad_0x38e7[ 0xfd ];
	public: float flLowerBodyYawTarget; // 0x39e4
	public: int bStrafing;				// 0x39e8
	private: BYTE pad_0x39ec[ 0x68a8 ];
	public: int iAddonBits;				// 0xa294
	public: int iPrimaryAddon; // 0xa298
	public: int iSecondaryAddon; // 0xa29c
	public: int iProgressBarDuration; // 0xa2a0
	public: float flProgressBarStartTime; // 0xa2a4
	public: float flStamina;				// 0xa2a8
	public: int iDirection;				// 0xa2ac
	public: int iShotsFired;				// 0xa2b0
	public: int nNumFastDucks; // 0xa2b4
	public: int bDuckOverride; // 0xa2b8
	public: int bNightVisionOn; // 0xa2b9
	public: int bHasNightVision; // 0xa2ba
	public: float flVelocityModifier; // 0xa2bc
	public: float flGroundAccelLinearFracLastTime;// 0xa2c0
	public: int iStartAccount; // 0xa2c4
	public: int totalHitsOnServer; // 0xa2c8
	private: BYTE pad_0xa2cc[ 0x4 ];
	public: int hRagdoll;					// 0xa2d0
	public: int hCarriedHostage;			// 0xa2d4
	public: int hCarriedHostageProp; // 0xa2d8
	private: BYTE pad_0xa2dc[ 0x18 ];
	public: float flFlashMaxAlpha; // 0xa2f4
	public: float flFlashDuration; // 0xa2f8
	private: BYTE pad_0xa2fc[ 0x40 ];
	public: int iMatchStats_Kills[ 30 ]; // 0xa33c
	public: int iMatchStats_Damage[ 30 ]; // 0xa3b4
	public: int iMatchStats_EquipmentValue[ 30 ];// 0xa42c
	public: int iMatchStats_MoneySaved[ 30 ];// 0xa4a4
	public: int iMatchStats_KillReward[ 30 ];// 0xa51c
	public: int iMatchStats_LiveTime[ 30 ];// 0xa594
	public: int iMatchStats_Deaths[ 30 ];	// 0xa60c
	public: int iMatchStats_Assists[ 30 ];// 0xa684
	public: int iMatchStats_HeadShotKills[ 30 ];// 0xa6fc
	public: int iMatchStats_Objective[ 30 ];// 0xa774
	public: int iMatchStats_CashEarned[ 30 ];// 0xa7ec
	public: int iMatchStats_UtilityDamage[ 30 ];// 0xa864
	public: int iMatchStats_EnemiesFlashed[ 30 ];// 0xa8dc
	private: BYTE pad_0xa954[ 0x60 ];
	public: int nQuestProgressReason;		// 0xa9b4
	public: int unCurrentEquipmentValue; // 0xa9b8
	public: int unRoundStartEquipmentValue;// 0xa9ba
	public: int unFreezetimeEndEquipmentValue;// 0xa9bc
	public: int rank[ 6 ];				// 0xa9c0
	public: int unMusicID;				// 0xa9d8
	public: int iAccount;					// 0xa9dc
	public: int bHasHelmet;				// 0xa9e0
	public: int bHasHeavyArmor; // 0xa9e1
	public: int iClass;					// 0xa9e4
	public: int ArmorValue;				// 0xa9e8
	public: float angEyeAngles[ 2 ];		// 0xa9ec
	private: BYTE pad_0xa9f4[ 0x4 ];
	public: int bHasDefuser;				// 0xa9f8
	public: int bInHostageRescueZone; // 0xa9f9
	private: BYTE pad_0xa9fd[ 0xd ];
	public: int bHud_MiniScoreHidden; // 0xaa0a
	public: int bHud_RadarHidden; // 0xaa0b
	public: int nLastKillerIndex; // 0xaa0c
	public: int nLastConcurrentKilled; // 0xaa10
	public: int nDeathCamMusic; // 0xaa14
	private: BYTE pad_0xaa18[ 0xfc ];
	public: int cycleLatch;				// 0xab14
	private: BYTE pad_0xab18[ 0x4 ];
	public: bool bPlayerDominated[ 65 ]; // 0xab1c
	public: bool bPlayerDominatingMe[ 65 ];// 0xab5d
	private: BYTE pad_0xab9e[ 0x2 ];
	public: int iWeaponPurchasesThisRound[ 64 ];// 0xaba0
	private: BYTE pad_0xaca0[ 0x8 ];
	public: int bIsLookingAtWeapon; // 0xaca8
	public: int bIsHoldingLookAtWeapon; // 0xaca9
	private: BYTE pad_0xacad[ 0x94 ];
	public: int bIsAssassinationTarget; // 0xad41
	public: int bIsControllingBot;		// 0xad42
	public: int bCanControlObservedBot; // 0xad43
	public: int iControlledBotEntIndex; // 0xad44
	private: BYTE pad_0xad48[ 0x8 ];
	public: int bHasControlledBotThisRound;// 0xad50
};