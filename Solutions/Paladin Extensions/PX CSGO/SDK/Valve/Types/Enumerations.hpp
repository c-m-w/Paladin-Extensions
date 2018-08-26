/// Enumerations.hpp

#pragma once

enum CSWeaponType
{
	WEAPONTYPE_KNIFE = 0,
	WEAPONTYPE_PISTOL,
	WEAPONTYPE_SUBMACHINEGUN,
	WEAPONTYPE_RIFLE,
	WEAPONTYPE_SHOTGUN,
	WEAPONTYPE_SNIPER_RIFLE,
	WEAPONTYPE_MACHINEGUN,
	WEAPONTYPE_C4,
	WEAPONTYPE_PLACEHOLDER,
	WEAPONTYPE_GRENADE,
	WEAPONTYPE_UNKNOWN
};

enum EClassID
{
	ClassID_CAI_BaseNPC = 0,
	ClassID_CAK47,
	ClassID_CBaseAnimating,
	ClassID_CBaseAnimatingOverlay,
	ClassID_CBaseAttributableItem,
	ClassID_CBaseButton,
	ClassID_CBaseCombatCharacter,
	ClassID_CBaseCombatWeapon,
	ClassID_CBaseCSGrenade,
	ClassID_CBaseCSGrenadeProjectile,
	ClassID_CBaseDoor,
	ClassID_CBaseEntity,
	ClassID_CBaseFlex,
	ClassID_CBaseGrenade,
	ClassID_CBaseParticleEntity,
	ClassID_CBasePlayer,
	ClassID_CBasePropDoor,
	ClassID_CBaseTeamObjectiveResource,
	ClassID_CBaseTempEntity,
	ClassID_CBaseToggle,
	ClassID_CBaseTrigger,
	ClassID_CBaseViewModel,
	ClassID_CBaseVPhysicsTrigger,
	ClassID_CBaseWeaponWorldModel,
	ClassID_CBeam,
	ClassID_CBeamSpotlight,
	ClassID_CBoneFollower,
	ClassID_CBreakableProp,
	ClassID_CBreakableSurface,
	ClassID_CC4,
	ClassID_CCascadeLight,
	ClassID_CChicken,
	ClassID_CColorCorrection,
	ClassID_CColorCorrectionVolume,
	ClassID_CCSGameRulesProxy,
	ClassID_CCSPlayer,
	ClassID_CCSPlayerResource,
	ClassID_CCSRagdoll,
	ClassID_CCSTeam,
	ClassID_CDEagle,
	ClassID_CDecoyGrenade,
	ClassID_CDecoyProjectile,
	ClassID_CDynamicLight,
	ClassID_CDynamicProp,
	ClassID_CEconEntity,
	ClassID_CEconWearable,
	ClassID_CEmbers,
	ClassID_CEntityDissolve,
	ClassID_CEntityFlame,
	ClassID_CEntityFreezing,
	ClassID_CEntityParticleTrail,
	ClassID_CEnvAmbientLight,
	ClassID_CEnvDetailController,
	ClassID_CEnvDOFController,
	ClassID_CEnvParticleScript,
	ClassID_CEnvProjectedTexture,
	ClassID_CEnvQuadraticBeam,
	ClassID_CEnvScreenEffect,
	ClassID_CEnvScreenOverlay,
	ClassID_CEnvTonemapController,
	ClassID_CEnvWind,
	ClassID_CFEPlayerDecal,
	ClassID_CFireCrackerBlast,
	ClassID_CFireSmoke,
	ClassID_CFireTrail,
	ClassID_CFish,
	ClassID_CFlashbang,
	ClassID_CFogController,
	ClassID_CFootstepControl,
	ClassID_CFunc_Dust,
	ClassID_CFunc_LOD,
	ClassID_CFuncAreaPortalWindow,
	ClassID_CFuncBrush,
	ClassID_CFuncConveyor,
	ClassID_CFuncLadder,
	ClassID_CFuncMonitor,
	ClassID_CFuncMoveLinear,
	ClassID_CFuncOccluder,
	ClassID_CFuncReflectiveGlass,
	ClassID_CFuncRotating,
	ClassID_CFuncSmokeVolume,
	ClassID_CFuncTrackTrain,
	ClassID_CGameRulesProxy,
	ClassID_CHandleTest,
	ClassID_CHEGrenade,
	ClassID_CHostage,
	ClassID_CHostageCarriableProp,
	ClassID_CIncendiaryGrenade,
	ClassID_CInferno,
	ClassID_CInfoLadderDismount,
	ClassID_CInfoOverlayAccessor,
	ClassID_CItem_Healthshot,
	ClassID_CItemDogTags,
	ClassID_CKnife,
	ClassID_CKnifeGG,
	ClassID_CLightGlow,
	ClassID_CMaterialModifyControl,
	ClassID_CMolotovGrenade,
	ClassID_CMolotovProjectile,
	ClassID_CMovieDisplay,
	ClassID_CParticleFire,
	ClassID_CParticlePerformanceMonitor,
	ClassID_CParticleSystem,
	ClassID_CPhysBox,
	ClassID_CPhysBoxMultiplayer,
	ClassID_CPhysicsProp,
	ClassID_CPhysicsPropMultiplayer,
	ClassID_CPhysMagnet,
	ClassID_CPlantedC4,
	ClassID_CPlasma,
	ClassID_CPlayerResource,
	ClassID_CPointCamera,
	ClassID_CPointCommentaryNode,
	ClassID_CPointWorldText,
	ClassID_CPoseController,
	ClassID_CPostProcessController,
	ClassID_CPrecipitation,
	ClassID_CPrecipitationBlocker,
	ClassID_CPredictedViewModel,
	ClassID_CProp_Hallucination,
	ClassID_CPropDoorRotating,
	ClassID_CPropJeep,
	ClassID_CPropVehicleDriveable,
	ClassID_CRagdollManager,
	ClassID_CRagdollProp,
	ClassID_CRagdollPropAttached,
	ClassID_CRopeKeyframe,
	ClassID_CSCAR17,
	ClassID_CSceneEntity,
	ClassID_CSensorGrenade,
	ClassID_CSensorGrenadeProjectile,
	ClassID_CShadowControl,
	ClassID_CSlideshowDisplay,
	ClassID_CSmokeGrenade,
	ClassID_CSmokeGrenadeProjectile,
	ClassID_CSmokeStack,
	ClassID_CSpatialEntity,
	ClassID_CSpotlightEnd,
	ClassID_CSprite,
	ClassID_CSpriteOriented,
	ClassID_CSpriteTrail,
	ClassID_CStatueProp,
	ClassID_CSteamJet,
	ClassID_CSun,
	ClassID_CSunlightShadowControl,
	ClassID_CTeam,
	ClassID_CTeamplayRoundBasedRulesProxy,
	ClassID_CTEArmorRicochet,
	ClassID_CTEBaseBeam,
	ClassID_CTEBeamEntPoint,
	ClassID_CTEBeamEnts,
	ClassID_CTEBeamFollow,
	ClassID_CTEBeamLaser,
	ClassID_CTEBeamPoints,
	ClassID_CTEBeamRing,
	ClassID_CTEBeamRingPoint,
	ClassID_CTEBeamSpline,
	ClassID_CTEBloodSprite,
	ClassID_CTEBloodStream,
	ClassID_CTEBreakModel,
	ClassID_CTEBSPDecal,
	ClassID_CTEBubbles,
	ClassID_CTEBubbleTrail,
	ClassID_CTEClientProjectile,
	ClassID_CTEDecal,
	ClassID_CTEDust,
	ClassID_CTEDynamicLight,
	ClassID_CTEEffectDispatch,
	ClassID_CTEEnergySplash,
	ClassID_CTEExplosion,
	ClassID_CTEFireBullets,
	ClassID_CTEFizz,
	ClassID_CTEFootprintDecal,
	ClassID_CTEFoundryHelpers,
	ClassID_CTEGaussExplosion,
	ClassID_CTEGlowSprite,
	ClassID_CTEImpact,
	ClassID_CTEKillPlayerAttachments,
	ClassID_CTELargeFunnel,
	ClassID_CTEMetalSparks,
	ClassID_CTEMuzzleFlash,
	ClassID_CTEParticleSystem,
	ClassID_CTEPhysicsProp,
	ClassID_CTEPlantBomb,
	ClassID_CTEPlayerAnimEvent,
	ClassID_CTEPlayerDecal,
	ClassID_CTEProjectedDecal,
	ClassID_CTERadioIcon,
	ClassID_CTEShatterSurface,
	ClassID_CTEShowLine,
	ClassID_CTesla,
	ClassID_CTESmoke,
	ClassID_CTESparks,
	ClassID_CTESprite,
	ClassID_CTESpriteSpray,
	ClassID_CTest_ProxyToggle_Networkable,
	ClassID_CTestTraceline,
	ClassID_CTEWorldDecal,
	ClassID_CTriggerPlayerMovement,
	ClassID_CTriggerSoundOperator,
	ClassID_CVGuiScreen,
	ClassID_CVoteController,
	ClassID_CWaterBullet,
	ClassID_CWaterLODControl,
	ClassID_CWeaponAug,
	ClassID_CWeaponAWP,
	ClassID_CWeaponBaseItem,
	ClassID_CWeaponBizon,
	ClassID_CWeaponCSBase,
	ClassID_CWeaponCSBaseGun,
	ClassID_CWeaponCycler,
	ClassID_CWeaponElite,
	ClassID_CWeaponFamas,
	ClassID_CWeaponFiveSeven,
	ClassID_CWeaponG3SG1,
	ClassID_CWeaponGalil,
	ClassID_CWeaponGalilAR,
	ClassID_CWeaponGlock,
	ClassID_CWeaponHKP2000,
	ClassID_CWeaponM249,
	ClassID_CWeaponM3,
	ClassID_CWeaponM4A1,
	ClassID_CWeaponMAC10,
	ClassID_CWeaponMag7,
	ClassID_CWeaponMP5Navy,
	ClassID_CWeaponMP7,
	ClassID_CWeaponMP9,
	ClassID_CWeaponNegev,
	ClassID_CWeaponNOVA,
	ClassID_CWeaponP228,
	ClassID_CWeaponP250,
	ClassID_CWeaponP90,
	ClassID_CWeaponSawedoff,
	ClassID_CWeaponSCAR20,
	ClassID_CWeaponScout,
	ClassID_CWeaponSG550,
	ClassID_CWeaponSG552,
	ClassID_CWeaponSG556,
	ClassID_CWeaponSSG08,
	ClassID_CWeaponTaser,
	ClassID_CWeaponTec9,
	ClassID_CWeaponTMP,
	ClassID_CWeaponUMP45,
	ClassID_CWeaponUSP,
	ClassID_CWeaponXM1014,
	ClassID_CWorld,
	ClassID_DustTrail,
	ClassID_MovieExplosion,
	ClassID_ParticleSmokeGrenade,
	ClassID_RocketTrail,
	ClassID_SmokeTrail,
	ClassID_SporeExplosion,
	ClassID_SporeTrail,
	CLASSID_MAX
};

enum EItemDefinitionIndex
{
	ITEM_NONE = 0,
	ITEM_WEAPON_DEAGLE = 1,
	ITEM_WEAPON_ELITE = 2,
	ITEM_WEAPON_FIVESEVEN = 3,
	ITEM_WEAPON_GLOCK = 4,
	ITEM_WEAPON_AK47 = 7,
	ITEM_WEAPON_AUG = 8,
	ITEM_WEAPON_AWP = 9,
	ITEM_WEAPON_FAMAS = 10,
	ITEM_WEAPON_G3SG1 = 11,
	ITEM_WEAPON_GALILAR = 13,
	ITEM_WEAPON_M249 = 14,
	ITEM_WEAPON_M4A1 = 16,
	ITEM_WEAPON_MAC10 = 17,
	ITEM_WEAPON_P90 = 19,
	ITEM_WEAPON_MP5SD = 23,
	ITEM_WEAPON_UMP45 = 24,
	ITEM_WEAPON_XM1014 = 25,
	ITEM_WEAPON_PPBIZON = 26,
	ITEM_WEAPON_MAG7 = 27,
	ITEM_WEAPON_NEGEV = 28,
	ITEM_WEAPON_SAWEDOFF = 29,
	ITEM_WEAPON_TEC9 = 30,
	ITEM_WEAPON_ZEUS = 31,
	ITEM_WEAPON_P2000 = 32,
	ITEM_WEAPON_MP7 = 33,
	ITEM_WEAPON_MP9 = 34,
	ITEM_WEAPON_NOVA = 35,
	ITEM_WEAPON_P250 = 36,
	ITEM_WEAPON_SCAR20 = 38,
	ITEM_WEAPON_SG553 = 39,
	ITEM_WEAPON_SSG08 = 40,
	ITEM_WEAPON_CTKNIFE = 41,
	ITEM_WEAPON_CTKNIFE2 = 42,
	ITEM_WEAPON_FLASHBANG = 43,
	ITEM_WEAPON_HEGRENADE = 44,
	ITEM_WEAPON_SMOKEGRENADE = 45,
	ITEM_WEAPON_MOLOTOV = 46,
	ITEM_WEAPON_DECOYGRENADE = 47,
	ITEM_WEAPON_INCENDIARYGRENADE = 48,
	ITEM_WEAPON_C4EXPLOSIVE = 49,
	ITEM_WEAPON_MEDISHOT = 57,
	ITEM_WEAPON_TKNIFE = 59,
	ITEM_WEAPON_M4A1S = 60,
	ITEM_WEAPON_USPS = 61,
	ITEM_WEAPON_CZ75AUTO = 63,
	ITEM_WEAPON_R8REVOLVER = 64,
	ITEM_WEAPON_TACTICALAWARENESSGRENADE = 68,
	ITEM_WEAPON_BAYONET = 500,
	ITEM_WEAPON_KNIFE_FLIP = 505,
	ITEM_WEAPON_KNIFE_GUT = 506,
	ITEM_WEAPON_KNIFE_KARAMBIT = 507,
	ITEM_WEAPON_KNIFE_M9_BAYONET = 508,
	ITEM_WEAPON_KNIFE_TACTICAL = 509,
	ITEM_WEAPON_KNIFE_FALCHION = 512,
	ITEM_WEAPON_KNIFE_SURVIVAL_BOWIE = 514,
	ITEM_WEAPON_KNIFE_BUTTERFLY = 515,
	ITEM_WEAPON_KNIFE_SHADOW_DAGGERS = 516,
	ITEM_WEAPON_KNIFE_URSUS = 519,
	ITEM_WEAPON_KNIFE_NAVAJA = 520,
	ITEM_WEAPON_KNIFE_STILLETTO = 522,
	ITEM_WEAPON_KNIFE_TALON = 523,
	ITEM_GLOVE_BLOODHOUND = 5027,
	ITEM_GLOVE_T = 5028,
	ITEM_GLOVE_CT = 5029,
	ITEM_GLOVE_SPORTY = 5030,
	ITEM_GLOVE_DRIVER = 5031,
	ITEM_GLOVE_HAND_WRAP = 5032,
	ITEM_GLOVE_MOTORCYCLE = 5033,
	ITEM_GLOVE_SPECIALIST = 5034,
	ITEM_GLOVE_HYDRA = 5035,
	ITEM_MAX
};

enum EItemQuality
{
	QUALITY_KNIFE = 3,
	QUALITY_GLOVE,
	QUALITY_VALVE = 6,
	QUALITY_SOUVENIER = 12,
	QUALITY_MAX
};

enum ECSPlayerBones
{
	PELVIS = 0,
	SPINE_0,
	SPINE_1,
	SPINE_2,
	SPINE_3,
	NECK_0,
	HEAD_0,
	CLAVICLE_L,
	ARM_UPPER_L,
	ARM_LOWER_L,
	HAND_L,
	FINGER_MIDDLE_META_L,
	FINGER_MIDDLE_0_L,
	FINGER_MIDDLE_1_L,
	FINGER_MIDDLE_2_L,
	FINGER_PINKY_META_L,
	FINGER_PINKY_0_L,
	FINGER_PINKY_1_L,
	FINGER_PINKY_2_L,
	FINGER_INDEX_META_L,
	FINGER_INDEX_0_L,
	FINGER_INDEX_1_L,
	FINGER_INDEX_2_L,
	FINGER_THUMB_0_L,
	FINGER_THUMB_1_L,
	FINGER_THUMB_2_L,
	FINGER_RING_META_L,
	FINGER_RING_0_L,
	FINGER_RING_1_L,
	FINGER_RING_2_L,
	WEAPON_HAND_L,
	ARM_LOWER_L_TWIST,
	ARM_LOWER_L_TWIST1,
	ARM_UPPER_L_TWIST,
	ARM_UPPER_L_TWIST1,
	CLAVICLE_R,
	ARM_UPPER_R,
	ARM_LOWER_R,
	HAND_R,
	FINGER_MIDDLE_META_R,
	FINGER_MIDDLE_0_R,
	FINGER_MIDDLE_1_R,
	FINGER_MIDDLE_2_R,
	FINGER_PINKY_META_R,
	FINGER_PINKY_0_R,
	FINGER_PINKY_1_R,
	FINGER_PINKY_2_R,
	FINGER_INDEX_META_R,
	FINGER_INDEX_0_R,
	FINGER_INDEX_1_R,
	FINGER_INDEX_2_R,
	FINGER_THUMB_0_R,
	FINGER_THUMB_1_R,
	FINGER_THUMB_2_R,
	FINGER_RING_META_R,
	FINGER_RING_0_R,
	FINGER_RING_1_R,
	FINGER_RING_2_R,
	WEAPON_HAND_R,
	ARM_LOWER_R_TWIST,
	ARM_LOWER_R_TWIST1,
	ARM_UPPER_R_TWIST,
	ARM_UPPER_R_TWIST1,
	LEG_UPPER_L,
	LEG_LOWER_L,
	ANKLE_L,
	BALL_L,
	LFOOT_LOCK,
	LEG_UPPER_L_TWIST,
	LEG_UPPER_L_TWIST1,
	LEG_UPPER_R,
	LEG_LOWER_R,
	ANKLE_R,
	BALL_R,
	RFOOT_LOCK,
	LEG_UPPER_R_TWIST,
	LEG_UPPER_R_TWIST1,
	FINGER_PINKY_L_END,
	FINGER_PINKY_R_END,
	VALVEBIPED_WEAPON_BONE,
	LH_IK_DRIVER,
	PRIMARY_JIGGLE_JNT,
	ECSPLAYERBONES_MAX
};

enum EHitGroups
{
	HITGROUP_HEAD = 1,
	HITGROUP_UPPERBODY,
	HITGROUP_LOWERBODY,
	HITGROUP_LEFTARM,
	HITGROUP_RIGHTARM,
	HITGROUP_LEFTLEG,
	HITGROUP_RIGHTLEG,
	HITGROUP_MAX
};

enum EntityFlags
{
	FL_ONGROUND = ( 1 << 0 ),
	FL_DUCKING = ( 1 << 1 ),
	FL_WATERJUMP = ( 1 << 2 ),
	FL_ONTRAIN = ( 1 << 3 ),
	FL_INRAIN = ( 1 << 4 ),
	FL_FROZEN = ( 1 << 5 ),
	FL_ATCONTROLS = ( 1 << 6 ),
	FL_CLIENT = ( 1 << 7 ),
	FL_FAKECLIENT = ( 1 << 8 ),
	ENTITYFLAGS_MAX
};

enum LifeState: unsigned char
{
	LIFE_ALIVE = 0,// alive
	LIFE_DYING = 1, // playing death animation or still falling off of a ledge waiting to hit ground
	LIFE_DEAD = 2, // dead. lying still.
	LIFESTATE_MAX
};

enum WeaponSound_t
{
	EMPTY,
	SINGLE,
	SINGLE_NPC,
	WPN_DOUBLE, // Can't be "DOUBLE" because windows.h uses it.
	DOUBLE_NPC,
	BURST,
	RELOAD,
	RELOAD_NPC,
	MELEE_MISS,
	MELEE_HIT,
	MELEE_HIT_WORLD,
	SPECIAL1,
	SPECIAL2,
	SPECIAL3,
	TAUNT,
	FAST_RELOAD,
	// Add new shoot sound types here
	REVERSE_THE_NEW_SOUND,
	NUM_SHOOT_SOUND_TYPES,
	MAX_WEAPONSOUND
};

enum MoveType_t
{
	MOVETYPE_NONE = 0,
	MOVETYPE_ISOMETRIC,
	MOVETYPE_WALK,
	MOVETYPE_STEP,
	MOVETYPE_FLY,
	MOVETYPE_FLYGRAVITY,
	MOVETYPE_VPHYSICS,
	MOVETYPE_PUSH,
	MOVETYPE_NOCLIP,
	MOVETYPE_LADDER,
	MOVETYPE_OBSERVER,
	MOVETYPE_CUSTOM,
	MOVETYPE_LAST = MOVETYPE_CUSTOM,
	MOVETYPE_MAX_BITS = 4,
	MAX_MOVETYPE
};
