#pragma once

typedef unsigned FLAG;
typedef unsigned EHANDLE;

#define FL_ONGROUND ( 1 << 0 ) // At rest / on the ground
#define FL_DUCKING ( 1 << 1 ) // Player FLAG -- Player is fully crouched
#define	LIFE_ALIVE 0 // alive
#define	LIFE_DYING 1 // playing death animation or still falling off of a ledge waiting to hit ground
#define	LIFE_DEAD 2 // dead. lying still.
#define ACTION_NONE 0b0 // -command
#define ACTION_PRESS 0b1 // +command
#define ACTION_TICK 0b10 // +command, tick, -command
#define ACTION_DEFAULT 0b100 // default command state
#define INDEX_DISTANCE_ENTITY 0x10 // Distance between entities
#define INDEX_DISTANCE_GLOW 0xA310

#define MAX_ANGLE_DELTA 22.f // Max angle delta per tick
#define MAX_SENSITIVITY 1000.f
#define MIN_SENSITIVITY 0.f
#define MAX_FLASHALPHA 255.f
#define MIN_FLASHALPHA 0.f
#define MAX_FIELDOFVIEW 180
#define MIN_FIELDOFVIEW 0
#define MAX_PITCH 89.f
#define MIN_PITCH ( -89.f )
#define MAX_YAW 180.f
#define MIN_YAW ( -180.f )
#define MAX_ROLL 50.f
#define MIN_ROLL 50.f

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

enum class EPaintKits // FIXME naming TODO @cole
{
	Groundwater = 2,
	CandyApple,
	ForestDDPAT = 5,
	ArcticCamo,
	DesertStorm = 8,
	BengalTiger,
	Copperhead,
	Skulls,
	CrimsonWeb,
	BlueStreak,
	RedLaminate,
	Gunsmoke,
	JungleTiger,
	UrbanDDPAT,
	Virus = 20,
	GraniteMarbleized,
	ContrastSpray,
	ForestLeaves = 25,
	LichenDashed,
	BoneMask,
	AnodizedNavy,
	SnakeCamo = 30,
	Silver = 32,
	HotRod,
	MetallicDDPAT,
	Ossified = 36,
	Blaze,
	Fade,
	Bulldozer,
	Night,
	Copper,
	BlueSteel,
	Stained,
	CaseHardened,
	Contractor = 46,
	Colony,
	DragonTattoo,
	LightningStrike = 51,
	Slaughter = 59,
	DarkWater,
	Hypnotic,
	Bloomstick,
	ColdBlooded = 67,
	CarbonFiber = 70,
	Scorpion,
	SafariMesh,
	Wings,
	PolarCamo,
	BlizzardMarbleized,
	WinterForest,
	BorealForest,
	ForestNight,
	OrangeDDPAT = 83,
	PinkDDPAT,
	Mudder = 90,
	Cyanospatter = 92,
	Caramel,
	Grassland = 95,
	BlueSpruce,
	Ultraviolet = 98,
	SandDune,
	Storm,
	Tornado,
	Whiteout,
	GrasslandLeaves = 104,
	PolarMesh = 107,
	Condemned = 110,
	GlacierMesh,
	SandMesh = 116,
	SageSpray = 119,
	JungleSpray = 122,
	SandSpray = 124,
	UrbanPerforated = 135,
	WavesPerforated,
	OrangePeel = 141,
	UrbanMasked = 143,
	JungleDashed = 147,
	SandDashed,
	UrbanDashed,
	Jungle = 151,
	Demolition = 153,
	Afterimage,
	BulletRain,
	DeathbyKitty,
	Palm,
	Walnut,
	Brass,
	Splash = 162,
	ModernHunter = 164,
	SplashJam,
	BlazeOrange,
	RadiationHazard,
	NuclearThreat,
	FalloutWarning,
	Predator,
	IrradiatedAlert,
	BlackLaminate,
	BOOM = 174,
	Scorched,
	FadedZebra,
	Memento,
	Doomkitty,
	NuclearThreat1,
	FireSerpent,
	Corticera,
	EmeraldDragon,
	Overgrowth,
	Corticera1,
	GoldenKoi,
	WaveSpray,
	Zirka,
	Graven,
	BrightWater,
	BlackLimba,
	Tempest,
	Shattered,
	BonePile,
	Spitfire,
	Demeter,
	Emerald,
	AnodizedNavy1,
	Hazard,
	DrySeason,
	MayanDreams,
	Palm1,
	JungleDDPAT,
	RustCoat,
	Mosaico,
	Jungle1,
	Tornado1,
	Facets,
	SandDune1,
	Groundwater1,
	AnodizedGunmetal,
	OceanFoam,
	Graphite,
	OceanFoam1,
	Graphite1,
	XRay,
	BlueTitanium,
	BloodTiger,
	Hexane,
	Hive,
	Hemoglobin,
	Serum,
	BloodintheWater,
	Nightshade,
	WaterSigil,
	GhostCamo,
	BlueLaminate,
	ElectricHive,
	BlindSpot,
	AzureZebra,
	SteelDisruption,
	CobaltDisruption,
	CrimsonWeb1,
	TropicalStorm,
	AshWood,
	VariCamo,
	NightOps,
	UrbanRubble,
	VariCamoBlue,
	CaliCamo = 240,
	HuntingBlind,
	ArmyMesh,
	GatorMesh,
	Teardown,
	ArmyRecon,
	AmberFade,
	DamascusSteel,
	RedQuartz,
	CobaltQuartz,
	FullStop,
	PitViper,
	SilverQuartz,
	AcidFade,
	Nitro,
	Asiimov,
	TheKraken,
	Guardian,
	Mehndi,
	Redline,
	Pulse,
	Marina,
	RoseIron,
	RisingSkull,
	Sandstorm,
	Kami,
	Magma,
	CobaltHalftone,
	TreadPlate,
	TheFuschiaIsNow,
	Victoria,
	Undertow,
	TitaniumBit,
	Heirloom,
	CopperGalaxy,
	RedFragCam,
	Panther,
	Stainless,
	BlueFissure,
	Asiimov1,
	Chameleon,
	Corporal,
	Redline1,
	Trigon,
	Heat,
	Terrain,
	Antique,
	Pulse1,
	Sergeant,
	Sandstorm1,
	Guardian1,
	HeavenGuard,
	DeathRattle = 293,
	GreenApple,
	Franklin,
	Meteorite,
	Tuxedo,
	ArmySheen,
	CagedSteel,
	EmeraldPinstripe,
	AtomicAlloy,
	Vulcan,
	Isaac,
	Slashed,
	Torque,
	Antique1,
	Retribution,
	Kami1,
	Howl,
	Curse,
	DesertWarfare,
	Cyrex,
	Orion,
	HeavenGuard1,
	PoisonDart,
	Jaguar,
	Bratatat,
	RoadRash,
	Detour,
	RedPython,
	MasterPiece,
	Nitro1,
	RustCoat1,
	Chalice = 325,
	Knight,
	Chainmail,
	HandCannon,
	DarkAge,
	Briar,
	RoyalBlue = 332,
	Indigo,
	Twist,
	Module,
	DesertStrike,
	Tatter,
	Pulse2,
	Caiman,
	JetSet,
	FirstClass,
	Leather,
	Commuter,
	DragonLore,
	FirstClass1,
	CoachClass,
	Pilot,
	RedLeather,
	Osiris,
	Tigris,
	Conspiracy,
	FowlPlay,
	WaterElemental,
	UrbanHazard,
	DesertStrike1,
	Koi,
	Ivory,
	Supernova,
	Asiimov2,
	Cyrex1,
	Abyss,
	Labyrinth,
	Traveler,
	BusinessClass,
	OlivePlaid,
	GreenPlaid,
	Reactor,
	SettingSun,
	NuclearWaste,
	BoneMachine,
	Styx,
	NuclearGarden,
	Contamination,
	Toxic,
	RadiationHazard1,
	ChemicalGreen,
	HotShot,
	FalloutWarning1,
	Cerberus,
	WastelandRebel,
	Grinder,
	Murky,
	Basilisk,
	Griffin,
	Firestarter,
	Dart,
	UrbanHazard1,
	Cartel,
	FireElemental,
	Highwayman,
	Cardiac,
	Delusion,
	Tranquility,
	Cartel1,
	Manowar,
	UrbanShock,
	Naga,
	Chatterbox,
	Catacombs,
	DragonKing,
	SystemLock,
	Malachite,
	DeadlyPoison,
	Muertos,
	Serenity,
	Grotto,
	Quicksilver,
	TigerTooth = 409,
	DamascusSteel1,
	DamascusSteel2,
	MarbleFade = 413,
	RustCoat2,
	Doppler,
	Doppler1,
	Doppler2,
	Doppler3,
	Doppler4,
	Doppler5,
	Doppler6,
	EliteBuild,
	ArmorCore,
	WormGod,
	BronzeDeco,
	Valence,
	MonkeyBusiness,
	Eco,
	Djinn,
	HyperBeast,
	Heat1,
	Manowar1,
	NeonRider,
	Origami,
	PolePosition,
	GrandPrix,
	TwilightGalaxy,
	Chronos,
	Hades,
	IcarusFell,
	MinotaursLabyrinth,
	Asterion,
	Pathfinder,
	Daedalus,
	HotRod1,
	Medusa,
	Duelist,
	PandorasBox,
	Poseidon,
	MooninLibra,
	SuninLeo,
	ShippingForecast,
	Emerald1,
	ParaGreen,
	AkihabaraAccept,
	Hydroponic,
	BambooPrint,
	BambooShadow,
	BambooForest,
	AquaTerrace,
	CounterTerrace = 462,
	Terrace,
	NeonKimono,
	OrangeKimono,
	CrimsonKimono,
	MintKimono,
	MidnightStorm,
	SunsetStorm,
	SunsetStorm1,
	Daybreak,
	ImpactDrill,
	Seabird,
	AquamarineRevenge,
	HyperBeast1,
	YellowJacket,
	NeuralNet,
	RocketPop,
	BunsenBurner,
	EvilDaimyo,
	Nemesis,
	RubyPoisonDart,
	Loudmouth,
	Ranger,
	Handgun,
	EliteBuild1,
	Cyrex2,
	Riot,
	Torque1,
	FrontsideMisty,
	DualingDragons,
	SurvivorZ,
	Flux,
	StoneCold,
	Wraiths,
	NebulaCrusader,
	GoldenCoil,
	Rangeen,
	CobaltCore,
	SpecialDelivery,
	Wingshot,
	GreenMarine,
	BigIron,
	KillConfirmed,
	Scumbria,
	PointDisarray,
	Ricochet,
	FuelRod,
	Corinthian,
	Retrobution,
	TheExecutioner,
	RoyalPaladin,
	PowerLoader = 514,
	Imperial,
	Shapewood,
	Yorick,
	Outbreak,
	TigerMoth,
	Avalanche,
	TecluBurner,
	Fade1,
	AmberFade1,
	FuelInjector,
	EliteBuild2,
	PhoticZone,
	KumichoDragon,
	Cartel2,
	Valence1,
	Triumvirate,
	RoyalLegion = 532,
	TheBattlestar,
	LapisGator,
	Praetorian,
	Impire,
	HyperBeast2,
	Necropos,
	Jambiya,
	LeadConduit,
	Doppler7 = 617,
	Doppler8,
	Doppler9,
	Ultraviolet1,
	Ultraviolet2,
	Charred = 10006,
	Snakebite,
	Bronzed,
	Leather1,
	SpruceDDPAT,
	LunarWeave = 10013,
	Convoy = 10015,
	CrimsonWeave,
	Superconductor = 10018,
	Arid,
	Slaughter1 = 10021,
	Eclipse = 10024,
	Spearmint = 10026,
	Boom,
	CoolMint,
	ForestDDPAT1 = 10030,
	CrimsonKimono1 = 10033,
	EmeraldWeb,
	Foundation,
	Badlands,
	PandorasBox1,
	HedgeMaze,
	Guerrilla,
	Diamondback,
	FleetFlock = 541,
	JudgementofAnubis,
	RedAstor,
	Ventilators,
	OrangeCrash,
	Firefight,
	Spectre,
	ChanticosFire,
	Bioleak,
	Oceanic,
	Asiimov3,
	Fubar,
	Atlas,
	GhostCrusader,
	ReEntry,
	PrimalSaber,
	BlackTie,
	Lore,
	Lore1,
	Lore2,
	Lore3,
	Lore4,
	BlackLaminate1,
	BlackLaminate2,
	BlackLaminate3,
	BlackLaminate4,
	BlackLaminate5,
	GammaDoppler,
	GammaDoppler1,
	GammaDoppler2,
	GammaDoppler3,
	GammaDoppler4,
	Autotronic,
	Autotronic1,
	Autotronic2,
	Autotronic3,
	Autotronic4,
	BrightWater1,
	BrightWater2,
	Freehand,
	Freehand1,
	Freehand2,
	Aristocrat,
	Phobos,
	ViolentDaimyo,
	WastelandRebel1,
	MechaIndustries,
	DesolateSpace,
	Carnivore,
	Exo,
	ImperialDragon,
	IronClad,
	Chopper,
	Harvester,
	Reboot,
	Limelight,
	Bloodsport,
	Aerial,
	IceCap,
	NeonRevolution,
	SydMead,
	Imprint,
	Directive,
	RollCage,
	Scumbria1,
	Ventilator,
	Weasel,
	Petroglyph,
	Airlock,
	Dazzle,
	Grim,
	Powercore,
	Triarch,
	FuelInjector1,
	Briefing,
	Slipstream,
	Polymer = 622,
	Ironwork,
	Dragonfire,
	RoyalConsorts,
	MechaIndustries1,
	Cirrus,
	Stinger,
	BlackSand,
	SandScale,
	Flashback,
	BuzzKill,
	Sonar,
	Gila,
	Turf,
	ShallowGrave,
	Cyrex3,
	WastelandPrincess,
	Bloodsport1,
	FeverDream,
	JungleSlipstream,
	Blueprint,
	Xiangliu,
	Decimator,
	OxideBlaze,
	Capillary,
	CrimsonTsunami,
	EmeraldPoisonDart,
	Akoben,
	Ripple,
	LastDive,
	Scaffold,
	NeoNoir,
	Seasons,
	Zander,
	OrbitMk01,
	Blueprint1,
	CobraStrike,
	Macabre,
	HyperBeast3,
	SugarRush,
	OniTaiji,
	Briefing1,
	Hellfire,
	Aloha,
	HardWater,
	Woodsman,
	RedRock,
	DeathGrip,
	DeathsHead,
	CutOut,
	MetalFlowers,
	Morris,
	Triqua,
	TheEmpress,
	HighRoller,
	Hunter,
	SeeYaLater,
	Goo,
	OffWorld,
	LeadedGlass,
	Oceanic1,
	LlamaCannon,
	CrackedOpal,
	JungleSlipstream1,
	Phantom,
	Tacticat,
	Exposure,
	Ziggy
};

struct audio_t
{
	float flFrameRate { };
	vector_t vecLocalSound[8] { };
	int iSoundScapeIndex { };
	int iLocalBits { };
	int iEntIndex { };
};

struct fog_t
{
	vector_t vecDirPrimary { }; // 0x0
	int iColorPrimary { }; // 0xc
	int iColorSecondary { }; // 0x10
	int iColorPrimaryLerpTo { }; // 0x14
	int iColorSecondaryLerpTo { }; // 0x18
	float flStart { }; // 0x1c
	float flEnd { }; // 0x20
	float flFarZ { };
	float flMaxDensity { }; // 0x28
	float flMaxDensityLerpTo { };
	float flLerpTime { };
	float flDuration { };
	int iEnable { }; // 0x40
	int iBlend { };
	float flZoomFogScale { };
	float flHDRColorScale { };
};

struct skybox3D_t
{
	int iScale { };
	vector_t vecOrigin { };
	int iArea { };
private:
	BYTE x14[0x4] { };
public:
	fog_t fogFog;
};

struct attributelist_t
{
	int iLengthprop32; // 0x0
	int iAttributeDefinitionIndex; // 0x4
	int iRawValue32; // 0x8
	int iRawInitialValue32; // 0xc
	int iRefundableCurrency; // 0x10
	bool bSetBonus; // 0x14
};

struct glow_t
{
	DWORD dwEntityBase { };
	float flRed { };
	float flGreen { };
	float flBlue { };
	float flAlpha { };
private:
	BYTE x14[ 0x8 ] { };
public:
	float flBloomAmount { }; // 0x22
	float localplayeriszeropoint3 { }; // 0x26
	bool bRenderWhenOccluded { }; // 0x27
	bool bRenderWhenUnoccluded { }; // 0x28
	bool bFullBloom { }; // 0x29
private:
	BYTE x30[ 0x1 ] { };
public:
	int iFullBloomStencilTestValue { }; // 0x31
private:
	BYTE x35[ 0x4 ] { };
public:
	int iSplitScreenSlot { };
	int iNextFreeSlot { };
};

class CGlobalVars
{
public:
	float flRealTime; // 0x0
	unsigned uiFrameCount; // 0x4
	float flAbsoluteFrameTime; // 0x8
	float flAbsoluteFrameStartTimeStdDev; // 0xc
	float flCurrentTime; // 0x10
	float flFrameTime; // 0x14
	unsigned uiMaxClients; // 0x18
	unsigned uiTickCount; // 0xc
	float flIntervalPerTick; // 0x20
	float flInterpolationAmount; // 0x24
};

class CPlayer
{
public:
	float flHDRColorScale { };
private:
	BYTE x4[0x5C] { };
public:
	bool bAutoaimTarget { }; // 0x60
private:
	BYTE x64[0xC] { };
public:
	color_t clrRender { }; // 0x70
	int iCellBits { }; // 0x74
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
	int iTeamNum { }; // 0xf0
	int iPendingTeamNum { }; // 0xf4
	int iNextThinkTick { }; // 0xf8
	int iHealth { }; // 0xfc
	FLAG fFlags { }; // 0x100
	vector_t vecViewOffset { }; // 0x104
	vector_t vecVelocity { }; // 0x110
	vector_t vecBaseVelocity { }; // 0x11c
	angle_t angRotation { }; // 0x128
	coordinate_t corOrigin { }; // 0x134
	float flFriction { }; // 0x140
	int iMoveParent { }; // 0x144
	EHANDLE hOwnerEntity { }; // 0x148
	EHANDLE hGroundEntity { }; // 0x14c
	char *szName { }; // 0x150
private:
	BYTE x154[0x100] { };
public:
	unsigned short usModelIndex { }; // 0x254
	unsigned __int8 unRenderFX { }; // 0x256
	unsigned short usRenderMode { }; // 0x257
	unsigned __int8 unWaterLevel { }; // 0x25a
	BYTE bLifeState { }; // 0x25b
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
	int iParentAttachment { }; // 0x2e8
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
	int iCollisionGroup { }; // 0x470
private:
	BYTE x474[0x4C2] { }; // CParticleSystem class
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
	int iTextureFrameIndex { }; // 0x988
private:
	BYTE x98C[0x8] { };
public:
	EHANDLE hEffectEntity { }; // 0x994
private:
	BYTE x998[0x64] { };
public:
	int iHitboxSet { }; // 0x9fc
private:
	BYTE xA00[0x14] { };
public:
	float flCycle { }; // 0xa14
	float flPlaybackRate { }; // 0xa18
	int iSkin { }; // 0xa1c
	int iBody { }; // 0xa20
private:
	BYTE xA24[0x14] { };
public:
	int iNewSequenceParity { }; // 0xa38
	int iResetEventsParity { }; // 0xa3c
private:
	BYTE xA40[0x8] { };
public:
	float flEncodedController[4] { }; // 0xa48
	int iMuzzleFlashParity { }; // 0xa58
private:
	BYTE xA5C[0x1C14] { }; // CSun class
public:
	vector_t vecForce { }; // 0x2670
	int iForceBone { }; // 0x267c
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
	int iScaleType { }; // 0x273c
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
	int iSequence { }; // 0x28ac
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
	int iLastHitGroup { }; // 0x2d64
	int iAmmo[32] { }; // 0x2d68
	EHANDLE hMyWeapons[64] { }; // 0x2de8
	EHANDLE hActiveWeapon { }; // 0x2ee8
	float flTimeOfLastInjury { }; // 0x2eec
	int iRelativeDirectionOfLastInjury { }; // 0x2ef0
private:
	BYTE x2EF4[0x4C] { };
public:
	int iCoachingTeam { }; // 0x2f40
private:
	BYTE x2F44[0x6B] { };
public:
	char chAreaBits[32] { }; // 0x2fb0
	char chAreaPortalBits[24] { }; // 0x2fd0
	BYTE x2FE8[0x8] { };
	float flFOVRate { }; // 0x2ff0
	int iHideHUD { }; // 0x2ff4
	int iDuckTimeMsecs { }; // 0x2ff8
	int iDuckJumpTimeMsecs { }; // 0x2ffc
	int iJumpTimeMsecs { }; // 0x3000
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
	skybox3D_t skybox3DSkybox3D; // 0x30d8
	audio_t audio; // 0x313C
	EHANDLE hTonemapController { }; // 0x31b0
private:
	BYTE x31B4[0x12] { };
public:
	int iFOV { }; // 0x31c8
	int iFOVStart { }; // 0x31cc
private:
	BYTE x31D0[0x14] { };
public:
	int iLadderSurfaceProps { }; // 0x31e4
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
	int iBonusProgress { }; // 0x3238
	int iBonusChallenge { }; // 0x323c
	float flMaxspeed { }; // 0x3240
	EHANDLE hZoomOwner { }; // 0x3244
private:
	BYTE x3248[0xC] { };
public:
	int iPhysicsCollisionState { }; // 0x3254
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
	int iDefaultFOV { }; // 0x3320
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
	int iDeathPostEffect { }; // 0x335c
	int iObserverMode { }; // 0x3360
	bool bActiveCameraMan { }; // 0x3364
	bool bCameraManXRay { }; // 0x3365
	bool bCameraManOverview { }; // 0x3366
	bool bCameraManScoreBoard { }; // 0x3367
	int iCameraManGraphs { }; // 0x3368
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
	int iTickBase { }; // 0x3414
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
	int iPlayerState { }; // 0x3890
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
	int iGunGameProgressiveWeaponIndex { }; // 0x38a4
	int iNumGunGameTrKillPopublic { }; // 0x38a8
	int iNumGunGameKillsWithCurrentWeapon { }; // 0x38ac
	int iNumRoundKills { }; // 0x38b0
	int iNumRoundKillsHeadshots { }; // 0x38b4
	FLAG fMolotovUseTime { }; // 0x38b8
	FLAG fMolotovDamageTime { }; // 0x38bc
	bool bBombZone { }; // 0x38c0
	bool bBuyZone { }; // 0x38c1
	bool bNoDefuseArea { }; // 0x38c2
	int iThrowGrenadeCounter { }; // 0x38c4
	bool bWaitForNoAttack { }; // 0x38c8
	bool bRespawningForDmBonus { }; // 0x38c9
	float flGuardianTooFarDistFrac { }; // 0x38cc
	float flDetectedByEnemySensorTime { }; // 0x38d0
private:
	BYTE x38D4[0x4] { };
public:
	bool bKilledByTaser { }; // 0x38d8
	int iMoveState { }; // 0x38dc
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
	int iAddonBits { }; // 0xa294
	int iPrimaryAddon { }; // 0xa298
	int iSecondaryAddon { }; // 0xa29c
	int iProgressBarDuration { }; // 0xa2a0
	float flProgressBarStartTime { }; // 0xa2a4
	float flStamina { }; // 0xa2a8
	int iDirection { }; // 0xa2ac
	int iShotsFired { }; // 0xa2b0
	int iNumFastDucks { }; // 0xa2b4
	bool bDuckOverride { }; // 0xa2b8
	bool bNightVisionOn { }; // 0xa2b9
	bool bHasNightVision { }; // 0xa2ba
	float flVelocityModifier { }; // 0xa2bc
	float flGroundAccelLinearFracLastTime { }; // 0xa2c0
	int iStartAccount { }; // 0xa2c4
	int iHitsOnServer { }; // 0xa2c8
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
	int iMatchStatsKills[30] { }; // 0xa33c
	int iMatchStatsDamage[30] { }; // 0xa3b4
	int iMatchStatsEquipmentValue[30] { }; // 0xa42c
	int iMatchStatsMoneySaved[30] { }; // 0xa4a4
	int iMatchStatsKillReward[30] { }; // 0xa51c
	int iMatchStatsLiveTime[30] { }; // 0xa594
	int iMatchStatsDeaths[30] { }; // 0xa60c
	int iMatchStatsAssists[30] { }; // 0xa684
	int iMatchStatsHeadShotKills[30] { }; // 0xa6fc
	int iMatchStatsObjective[30] { }; // 0xa774
	int iMatchStatsCashEarned[30] { }; // 0xa7ec
	int iMatchStatsUtilityDamage[30] { }; // 0xa864
	int iMatchStatsEnemiesFlashed[30] { }; // 0xa8dc
private:
	BYTE xA954[0x8A0] { };
public:
	int iQuestProgressReason { }; // 0xb1f4
	unsigned short usCurrentEquipmentValue { }; // 0xb1f8
	unsigned short usRoundStartEquipmentValue { }; // 0xb1fa
	unsigned short usFreezetimeEndEquipmentValue { }; // 0xb1fc
	int iRank[6] { }; // 0xb200
	unsigned short usMusicID { }; // 0xb218
private:
	BYTE xB21A[0xE] { };
public:
	int iAccount { }; // 0xb228
	bool bHasHelmet { }; // 0xb22c
	bool bHasHeavyArmor { }; // 0xb22d
private:
	BYTE xB22E[0x6] { };
public:
	int iClass { }; // 0xb234
	int iArmorValue { }; // 0xb238
	angle_t angEyeAngles { }; // 0xb23c
	bool bHasDefuser { }; // 0xb248
	bool bHostageRescueZone { }; // 0xb249
private:
	BYTE xB24A[0x20] { };
public:
	bool bHudMiniScoreHidden { }; // 0xb26a
	bool bHudRadarHidden { }; // 0xb26b
	int iLastKillerIndex { }; // 0xb26c
	int iLastConcurrentKilled { }; // 0xb270
	int iDeathCamMusic { }; // 0xb274
private:
	BYTE xB278[0xEC] { };
public:
	int iCycleLatch { }; // 0xb364
private:
	BYTE xB368[0x4] { };
public:
	bool bPlayerDominated[65] { }; // 0xb36c
	bool bPlayerDominatingMe[65] { }; // 0xb3ad
private:
	BYTE xB3AE[0x2] { };
public:
	int iWeaponPurchasesThisRound[64] { }; // 0xb3f0
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
	int iControlledBotEntIndex { }; // 0xb898
private:
	BYTE xB89B[0x8] { };
public:
	bool bHasControlledBotThisRound { }; // 0xb8a4
}; // total size = 0xb8a8

class CEngine
{
public:
	// engine - global
	CGlobalVars GetGlobalVars( );
	void SetGlobalVars( CGlobalVars ); // careful! unlimited
	bool GetSendPackets( );
	void SetSendPackets( bool );

	// engine - clientstate
	DWORD GetClientState( );
	ESignOnState GetSignOnState( );
	angle_t GetViewAngle( );
	void SetViewAngle( angle_t ); // sets view angles automatically normalized and clamped

	// client - global
	FLAG GetAttack( );
	void SetAttack( FLAG );
	FLAG GetJump( );
	void SetJump( FLAG );
	float GetSensitivity( );
	void SetSensitivity( float ); // sets sensitivity limited to 0 and 1000

	// client - entities
	DWORD GetEntityBase( int );
	CPlayer GetEntity( int );
	void SetEntity( int, CPlayer );

	// client - localplayer
	DWORD GetLocalPlayerBase( );
	CPlayer GetLocalPlayer( );
	void SetLocalPlayer( CPlayer );

	// general
	float GetPixelToAngleYaw( );
	float GetPixelToAnglePitch( );
	angle_t ClampAngle( angle_t ); // clamps angles to 89, 180, and 50
	angle_t NormalizeAngle( angle_t ); // sets angle to sensitivity, limits delta to 22 degrees
	angle_t VectorToAngle( coordinate_t, coordinate_t );
};

extern CEngine eng;
