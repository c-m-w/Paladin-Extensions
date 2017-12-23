#pragma once

// global defines
#define PI 3.141593f
#define MILLISECONDS_PER_SECOND 1000.f

#define PREMIUM_USERS unsigned __int8(55)
#define MESSAGE( Title, Text, Type ) MessageBox( nullptr, Text, Title, (Type) | MB_OK )
#define DECEMBER_FIRST moment(1512086400000) // time since epoch in milliseconds to december first 2017
#define DAY moment(8640000) // day in milliseconds

// global typedefs
typedef long long moment;

// global structs
struct angle_t {
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

struct color_t {
	BYTE r, g, b, a;
};

struct coordinate_t {
	float x, y, z;
};

struct vector_t {
	float dx, dy, dz;

	vector_t( );
	vector_t( coordinate_t, coordinate_t );
};

// global variables
extern HINSTANCE hInst;
extern bool bExitState;
extern std::vector< std::thread > tThreads;

// global functions
void Wait( unsigned long );
moment GetMoment( );

template< typename xDatatype, typename xDatatype2 > void Limit( xDatatype &xStatus, xDatatype2 xMinimum, xDatatype2 xMaximum ) {
	if ( xDatatype( xMinimum ) > xStatus ) {
		xStatus = xDatatype( xMinimum );
	} else if ( xStatus > xDatatype( xMaximum ) ) {
		xStatus = xDatatype( xMaximum );
	}
}

template< typename xDatatype > void Absolute( xDatatype &xStatus ) {
	if ( xStatus < 0 ) {
		xStatus = -xStatus;
	}
}

// global enums
enum class EQuitReasons {
	UNKNOWN = -1,
	LOAD_LIBRARY_ERROR,
	SUCCESS,
	BLACKLISTED_CALL,
	PANIC
};

enum class EPremium {
	BANNED = -2,
	EXPIRED,
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
#define MIN_PITCH (-89.f)
#define MAX_YAW 180.f
#define MIN_YAW (-180.f)
#define MAX_ROLL 50.f
#define MIN_ROLL 50.f

// typedefs
typedef unsigned long FLAG;
typedef unsigned long EHANDLE;

// enums
enum class EMoveType {
	NONE,
	WALK = 2,
	NOCLIP = 8,
	LADDER,
};

enum class ESignOnState {
	CONNECTED = 2,
	SPAWNED = 5,
	FULL,
	CHANGELEVEL
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

// classes
class CGlobalVars {
public:
	float flRealTime;
	unsigned long ulFrameCount;
	float flAbsoluteFrameTime;
	float flAbsoluteFrameStartTimeStdDev;
	float flCurrentTime;
	float flFrameTime;
	unsigned long ulMaxClients;
	unsigned long ulTickCount;
	float flIntervalPerTick;
	float flInterpolationAmount;

	bool operator==( CGlobalVars );
	bool operator!=( CGlobalVars );
};

struct audio_t {
	vector_t localSound[8] { };
	int soundscapeIndex { };
	int localBits { };
	int entIndex { };
};

struct fog_t {
	vector_t dirPrimary { };
	int colorPrimary { };
	int colorSecondary { };
	BYTE unknown2[0x8] { };
	float start { };
	float end { };
	BYTE unknown3[0x4] { };
	float maxdensity { };
	BYTE unknown4[0x14] { };
	int enable { };
	int blend { };
	BYTE unknown5[0x3] { };
	float flHDRColorScale { };
};

struct skybox3D_t {
	int scale { };
	vector_t origin { };
	int area { };
	BYTE unknown1[0x4] { };
	fog_t fog;
	BYTE unknown2[0x4] { };
};

struct attributelist_t {
	int lengthprop32; // 0x0
	int iAttributeDefinitionIndex; // 0x4
	int iRawValue32; // 0x8
	int iRawInitialValue32; // 0xc
	int nRefundableCurrency; // 0x10
	int bSetBonus; // 0x14
};

class CPlayer {
	BYTE x0[0x60] { };
public:
	bool bAutoaimTarget { }; // 0x60
private:
	BYTE x64[0xC] { };
public:
	color_t clrRender { }; // 0x70
	int cellbits { }; // 0x74
private:
	BYTE x78[0x4] { };
public:
	coordinate_t corCell { }; // 0x7c
private:
	BYTE x88[0x61] { };
public:
	bool bDormant { }; // 0xe9
private:
	BYTE xEA[0x2] { };
public:
	FLAG fEffects { }; // 0xec
	unsigned long ulTeamNum { }; // 0xf0
	unsigned long ulPendingTeamNum { }; // 0xf4
	unsigned long ulNextThinkTick { }; // 0xf8
	unsigned long ulHealth { }; // 0xfc
	FLAG fFlags { }; // 0x100
	vector_t vecViewOffset { }; // 0x104
	vector_t vecVelocity { }; // 0x110
	vector_t vecBaseVelocity { }; // 0x11c
	angle_t angRotation { }; // 0x128
	coordinate_t corOrigin { }; // 0x134
	float flFriction { }; // 0x140
	int moveparent { }; // 0x144
	EHANDLE hOwnerEntity { }; // 0x148
	EHANDLE hGroundEntity { }; // 0x14c
	char *iName { }; // 0x150
private:
	BYTE x154[0x100] { };
public:
	unsigned short usModelIndex { }; // 0x254
	unsigned __int8 unRenderFX { }; // 0x256
	unsigned short usRenderMode { }; // 0x257
	unsigned __int8 unWaterLevel { }; // 0x25a
	bool lifeState { }; // 0x25b
	float flAnimTime { }; // 0x25c
private:
	BYTE x260[0x4] { };
public:
	float flSimulationTime { }; // 0x264
private:
	BYTE x268[0xD] { };
public:
	bool bClientSideRagdoll { }; // 0x275
private:
	BYTE x279[0x4F] { };
public:
	float flUseLookAtAngle { }; // 0x2c8
private:
	BYTE x2CC[0x1C] { };
public:
	long lParentAttachment { }; // 0x2e8
private:
	BYTE x2EC[0x4] { };
public:
	float fadeMinDist { }; // 0x2f0
	float fadeMaxDist { }; // 0x2f4
	float flFadeScale { }; // 0x2f8
private:
	BYTE x2FC[0x9C] { };
public:
	float flElasticity { }; // 0x398
	float flShadowCastDistance { }; // 0x39c
private:
	BYTE x3A0[0xD0] { };
public:
	long lCollisionGroup { }; // 0x470
private:
	BYTE x474[0x4C2] { };
public:
	bool bSimulatedEveryTick { }; // 0x936
	bool bAnimatedEveryTick { }; // 0x937
	bool bAlternateSorting { }; // 0x938
	bool bSpotted { }; // 0x939
	bool bSpottedBy[64] { }; // 0x93a
	bool bSpottedByMask[10] { }; // 0x97a
	unsigned __int8 unMinCPULevel { }; // 0x984
	unsigned __int8 unMaxCPULevel { }; // 0x985
	unsigned __int8 unMinGPULevel { }; // 0x986
	unsigned __int8 unMaxGPULevel { }; // 0x987
	long lTextureFrameIndex { }; // 0x988
private:
	BYTE x98C[0x8] { };
public:
	EHANDLE hEffectEntity { }; // 0x994
private:
	BYTE x998[0x64] { };
public:
	unsigned long ulHitboxSet { }; // 0x9fc
private:
	BYTE xA00[0x14] { };
public:
	float flCycle { }; // 0xa14
	float flPlaybackRate { }; // 0xa18
	unsigned long ulSkin { }; // 0xa1c
	unsigned long ulBody { }; // 0xa20
private:
	BYTE xA24[0x14] { };
public:
	unsigned long ulNewSequenceParity { }; // 0xa38
	unsigned long ulResetEventsParity { }; // 0xa3c
private:
	BYTE xA40[0x8] { };
public:
	float flEncodedController[4] { }; // 0xa48
	unsigned long ulMuzzleFlashParity { }; // 0xa58
private:
	BYTE xA5C[0x1C14] { };
public:
	vector_t vecForce { }; // 0x2670
	unsigned long ulForceBone { }; // 0x267c
private:
	BYTE x2680[0x30] { };
public:
	bool bClientSideFrameReset { }; // 0x26b0
private:
	BYTE x26B4[0x34] { };
public:
	float flFrozen { }; // 0x26e8
private:
	BYTE x26EC[0x4C] { };
public:
	float flModelScale { }; // 0x2738
	long lScaleType { }; // 0x273c
private:
	BYTE x2740[0x24] { };
public:
	float flPoseParameter[24] { }; // 0x2764
private:
	BYTE x27C4[0xC8] { };
public:
	bool bClientSideAnimation { }; // 0x288c
private:
	BYTE x2890[0x1C] { };
public:
	unsigned long ulSequence { }; // 0x28ac
private:
	BYTE x28B0[0x84] { };
public:
	EHANDLE hLightingOrigin { }; // 0x2934
private:
	BYTE x2938[0x2] { };
public:
	bool bSuppressAnimSounds { }; // 0x293a
private:
	BYTE x293C[0xA4] { };
public:
	vector_t viewtarget { }; // 0x29e0
private:
	BYTE x29EC[0x2C] { };
public:
	float flexWeight[96] { }; // 0x2a18
private:
	BYTE x2B98[0x2C] { };
public:
	bool blinktoggle { }; // 0x2bc4
private:
	BYTE x2BC8[0x198] { };
public:
	float flNextAttack { }; // 0x2d60
	long lLastHitGroup { }; // 0x2d64
	long lAmmo[32] { }; // 0x2d68
	EHANDLE hMyWeapons[64] { }; // 0x2de8
	EHANDLE hActiveWeapon { }; // 0x2ee8
	float flTimeOfLastInjury { }; // 0x2eec
	unsigned long ulRelativeDirectionOfLastInjury { }; // 0x2ef0
private:
	BYTE x2EF4[0x4C] { };
public:
	long lCoachingTeam { }; // 0x2f40
private:
	BYTE x2F44[0x6B] { };
public:
	char chAreaBits[32] { }; // 0x2fb0
	char chAreaPortalBits[24] { }; // 0x2fd0
	BYTE x2FE8[0x8] { };
	float flFOVRate { }; // 0x2ff0
	long lHideHUD { }; // 0x2ff4
	unsigned long ulDuckTimeMsecs { }; // 0x2ff8
	unsigned long ulDuckJumpTimeMsecs { }; // 0x2ffc
	unsigned long ulJumpTimeMsecs { }; // 0x3000
	float flFallVelocity { }; // 0x3004
private:
	BYTE x3008[0x4] { };
public:
	float flStepSize { }; // 0x300C
	vector_t viewPunchAngle { }; // 0x3010
	vector_t aimPunchAngle { }; // 0x301c
	vector_t aimPunchAngleVel { }; // 0x3028
	bool bDucked { }; // 0x3034
	bool bDucking { }; // 0x3035
	bool bInDuckJump { }; // 0x3036
	bool bDrawViewmodel { }; // 0x3037
	bool bWearingSuit { }; // 0x3038
	bool bPoisoned { }; // 0x3039
	bool bAllowAutoMovement { }; // 0x303a
private:
	BYTE x303B[0x9d] { };
public:
	skybox3D_t skybox3d; // 0x30d8
	audio_t audio; // 0x313C
	EHANDLE hTonemapController { }; // 0x31b0
private:
	BYTE x31B4[0x12] { };
public:
	unsigned long ulFOV { }; // 0x31c8
	unsigned long ulFOVStart { }; // 0x31cc
private:
	BYTE x31D0[0x14] { };
public:
	int ladderSurfaceProps { }; // 0x31e4
private:
	BYTE x31F8[0x4] { };
public:
	float flFOVTime { }; // 0x31ec
private:
	BYTE x31F0[0x18] { };
public:
	vector_t vecLadderNormal { }; // 0x3208
private:
	BYTE x3214[0x24] { };
public:
	long lBonusProgress { }; // 0x3238
	long lBonusChallenge { }; // 0x323c
	float flMaxspeed { }; // 0x3240
	EHANDLE hZoomOwner { }; // 0x3244
private:
	BYTE x3248[0xC] { };
public:
	int vphysicsCollisionState { }; // 0x3254
private:
	BYTE x3258[0x8C] { };
public:
	FLAG fPhysicsFlags { }; // 0x32e4
	EHANDLE hVehicle { }; // 0x32e8
	EHANDLE hLastWeapon { }; // 0x32ec
	EHANDLE hViewModel { }; // 0x32f0
private:
	BYTE x32F4[0x24] { };
public:
	FLAG fOnTarget { }; // 0x3318
	EHANDLE hUseEntity { }; // 0x331c
	unsigned long ulDefaultFOV { }; // 0x3320
private:
	BYTE x3324[0x8] { };
public:
	EHANDLE hViewEntity { }; // 0x332c
	bool bShouldDrawPlayerWhileUsingViewEntity { }; // 0x3330
	EHANDLE hConstrapublicEntity { }; // 0x3334
	vector_t vecConstrapublicCenter { }; // 0x3338
	float flConstrapublicRadius { }; // 0x3344
	float flConstrapublicWidth { }; // 0x3348
	float flConstrapublicSpeedFactor { }; // 0x334c
	bool bConstrapublicPastRadius { }; // 0x3350
private:
	BYTE x3354[0x8] { };
public:
	long lDeathPostEffect { }; // 0x335c
	long lObserverMode { }; // 0x3360
	bool bActiveCameraMan { }; // 0x3364
	bool bCameraManXRay { }; // 0x3365
	bool bCameraManOverview { }; // 0x3366
	bool bCameraManScoreBoard { }; // 0x3367
	unsigned long ulCameraManGraphs { }; // 0x3368
private:
	BYTE x336C[0x8] { };
public:
	EHANDLE hObserverTarget { }; // 0x3374
private:
	BYTE x3378[0x34] { };
public:
	float flDeathTime { }; // 0x33ac
	FLAG fForceTeam { }; // 0x33b0
private:
	BYTE x33B4[0x60] { };
public:
	unsigned long ulTickBase { }; // 0x3414
private:
	BYTE x3418[0x160] { };
public:
	float flLaggedMovementValue { }; // 0x3578
private:
	BYTE x357C[0x1C] { };
public:
	char *szLastPlaceName { }; // 0x3598
private:
	BYTE x359C[0x20] { };
public:
	BYTE bEfNoInterpParity { }; // 0x35bc
private:
	BYTE x35C0[0x1BC] { };
public:
	EHANDLE hPostProcessCtrl { }; // 0x377c
	EHANDLE hColorCorrectionCtrl { }; // 0x3780
private:
	BYTE x3784[0x4] { };
public:
	EHANDLE hPlayerFogCtrl { }; // 0x3788
private:
	BYTE x378C[0x100] { };
public:
	bool bScoped { }; // 0x388c
	bool bWalking { }; // 0x388d
	bool bResumeZoom { }; // 0x388e
	long lPlayerState { }; // 0x3890
	bool bDefusing { }; // 0x3894
	bool bGrabbgHostage { }; // 0x3895
	bool bRescuing { }; // 0x3896
	FLAG fImmuneToGunGameDamageTime { }; // 0x3898
private:
	BYTE x389C[0x4] { };
public:
	bool bGunGameImmunity { }; // 0x38a0
	bool bHasMovedSinceSpawn { }; // 0x38a1
	bool bMadeFinalGunGameProgressiveKill { }; // 0x38a2
	unsigned long ulGunGameProgressiveWeaponIndex { }; // 0x38a4
	unsigned long ulNumGunGameTrKillPopublic { }; // 0x38a8
	unsigned long ulNumGunGameKillsWithCurrentWeapon { }; // 0x38ac
	unsigned long ulNumRoundKills { }; // 0x38b0
	unsigned long ulNumRoundKillsHeadshots { }; // 0x38b4
	FLAG fMolotovUseTime { }; // 0x38b8
	FLAG fMolotovDamageTime { }; // 0x38bc
	bool bBombZone { }; // 0x38c0
	bool bBuyZone { }; // 0x38c1
	bool bNoDefuseArea { }; // 0x38c2
	long lThrowGrenadeCounter { }; // 0x38c4
	bool bWaitForNoAttack { }; // 0x38c8
	bool bRespawningForDmBonus { }; // 0x38c9
	float flGuardianTooFarDistFrac { }; // 0x38cc
	float flDetectedByEnemySensorTime { }; // 0x38d0
private:
	BYTE x38D4[0x4] { };
public:
	bool bKilledByTaser { }; // 0x38d8
	long lMoveState { }; // 0x38dc
	bool bCanMoveDuringFreezePeriod { }; // 0x38e0
	bool isCurrentGunGameLeader { }; // 0x38e1
	bool isCurrentGunGameTeamLeader { }; // 0x38e2
	char *szArmsModel { }; // 0x38e4
private:
	BYTE x38E8[0xFC] { };
public:
	float flLowerBodyYawTarget { }; // 0x39e4
	bool bStrafing { }; // 0x39e8
private:
	BYTE x39EC[0x68A8] { };
public:
	long lAddonBits { }; // 0xa294
	long lPrimaryAddon { }; // 0xa298
	long lSecondaryAddon { }; // 0xa29c
	long lProgressBarDuration { }; // 0xa2a0
	float flProgressBarStartTime { }; // 0xa2a4
	float flStamina { }; // 0xa2a8
	long lDirection { }; // 0xa2ac
	unsigned long ulShotsFired { }; // 0xa2b0
	unsigned long ulNumFastDucks { }; // 0xa2b4
	bool bDuckOverride { }; // 0xa2b8
	bool bNightVisionOn { }; // 0xa2b9
	bool bHasNightVision { }; // 0xa2ba
	float flVelocityModifier { }; // 0xa2bc
	float flGroundAccelLinearFracLastTime { }; // 0xa2c0
	long lStartAccount { }; // 0xa2c4
	unsigned long ulHitsOnServer { }; // 0xa2c8
private:
	BYTE xA2CC[0x4] { };
public:
	EHANDLE hRagdoll { }; // 0xa2d0
	EHANDLE hCarriedHostage { }; // 0xa2d4
	EHANDLE hCarriedHostageProp { }; // 0xa2d8
private:
	BYTE xA2DC[0x18] { };
public:
	float flFlashMaxAlpha { }; // 0xa2f4
	float flFlashDuration { }; // 0xa2f8
private:
	BYTE xA2FC[0x40] { };
public:
	unsigned long ulMatchStatsKills[30] { }; // 0xa33c
	unsigned long ulMatchStatsDamage[30] { }; // 0xa3b4
	unsigned long ulMatchStatsEquipmentValue[30] { }; // 0xa42c
	unsigned long ulMatchStatsMoneySaved[30] { }; // 0xa4a4
	unsigned long ulMatchStatsKillReward[30] { }; // 0xa51c
	unsigned long ulMatchStatsLiveTime[30] { }; // 0xa594
	unsigned long ulMatchStatsDeaths[30] { }; // 0xa60c
	unsigned long ulMatchStatsAssists[30] { }; // 0xa684
	unsigned long ulMatchStatsHeadShotKills[30] { }; // 0xa6fc
	unsigned long ulMatchStatsObjective[30] { }; // 0xa774
	unsigned long ulMatchStatsCashEarned[30] { }; // 0xa7ec
	unsigned long ulMatchStatsUtilityDamage[30] { }; // 0xa864
	unsigned long ulMatchStatsEnemiesFlashed[30] { }; // 0xa8dc
private:
	BYTE xA954[0x8A0] { };
public:
	unsigned long ulQuestProgressReason { }; // 0xb1f4
	unsigned short usCurrentEquipmentValue { }; // 0xb1f8
	unsigned short usRoundStartEquipmentValue { }; // 0xb1fa
	unsigned short usFreezetimeEndEquipmentValue { }; // 0xb1fc
	int rank[6] { }; // 0xb200
	unsigned short usMusicID { }; // 0xb218
private:
	BYTE xB21A[0xE] { };
public:
	long lAccount { }; // 0xb228
	bool bHasHelmet { }; // 0xb22c
	bool bHasHeavyArmor { }; // 0xb22d
private:
	BYTE xB22E[0x6] { };
public:
	long lClass { }; // 0xb234
	unsigned long ulArmorValue { }; // 0xb238
	angle_t angEyeAngles { }; // 0xb23c
	bool bHasDefuser { }; // 0xb248
	bool bHostageRescueZone { }; // 0xb249
private:
	BYTE xB24A[0x20] { };
public:
	bool bHudMiniScoreHidden { }; // 0xb26a
	bool bHudRadarHidden { }; // 0xb26b
	unsigned long ulLastKillerIndex { }; // 0xb26c
	unsigned long ulLastConcurrentKilled { }; // 0xb270
	unsigned long ulDeathCamMusic { }; // 0xb274
private:
	BYTE xB278[0xEC] { };
public:
	int cycleLatch { }; // 0xb364
private:
	BYTE xB368[0x4] { };
public:
	bool bPlayerDominated[65] { }; // 0xb36c
	bool bPlayerDominatingMe[65] { }; // 0xb3ad
private:
	BYTE xB3AE[0x2] { };
public:
	unsigned long ulWeaponPurchasesThisRound[64] { }; // 0xb3f0
private:
	BYTE xB4F0[0x308] { };
public:
	bool bLookingAtWeapon { }; // 0xb7f8
	bool bHoldingLookAtWeapon { }; // 0xb7f9
private:
	BYTE xB7FA[0x98] { };
public:
	bool bAssassinationTarget { }; // 0xb895
	bool bControllingBot { }; // 0xb896
	bool bCanControlObservedBot { }; // 0xb897
	long lControlledBotEntIndex { }; // 0xb898
private:
	BYTE xB89B[0x8] { };
public:
	bool bHasControlledBotThisRound { }; // 0xb8a4
}; // total size = 0xb8a8
