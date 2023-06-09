#pragma once

class CCSWeaponInfo
{
public:
	void *vftbl; // 0x0
	char *consoleName; // 0x4
	char pad_0008[ 12 ]; // 0x8
	int iMaxClip1; // 0x1A
	int iMaxClip2; // 0x1Es
	int iDefaultClip1; // 0x22
	int iDefaultClip2; // 0x26
	char pad_0024[ 8 ]; // 0x2A
	char *szWorldModel; // 0x32
	char *szViewModel;
	char *szDroppedModel;
	char pad_0038[ 4 ];
	char *N0000023E;
	char pad_0040[ 56 ];
	char *szEmptySound;
	char pad_007C[ 4 ];
	char *szBulletType;
	char pad_0084[ 4 ];
	char *szHudName;
	char *szWeaponName;
	char pad_0090[ 56 ];
	int WeaponType;
	int iWeaponPrice;
	int iKillAward;
	char *szAnimationPrefix;
	float flCycleTime;
	float flCycleTimeAlt;
	float flTimeToIdle;
	float flIdleInterval;
	char pax_0x0x00E3[ 4 ];
	bool bFullAuto;
	char pad_0x00E5[ 3 ];
	int iDamage;
	float flArmorRatio;
	int iBullets;
	float flPenetration;
	float flFlinchVelocityModifierLarge;
	float flFlinchVelocityModifierSmall;
	float flRange;
	float flRangeModifier;
	float flThrowVelocity;
	char pad_0x010C[ 12 ];
	bool bHasSilencer;
	char pad_0x0119[ 3 ];
	char *pSilencerModel;
	int iCrosshairMinDistance;
	int iCrosshairDeltaDistance;
	float flMaxPlayerSpeed;
	float flMaxPlayerSpeedAlt;
	float flSpread;
	float flSpreadAlt;
	float flInaccuracyCrouch;
	float flInaccuracyCrouchAlt;
	float flInaccuracyStand;
	float flInaccuracyStandAlt;
	float flInaccuracyJumpInitial;
	float flInaccuracyJump;
	float flInaccuracyJumpAlt;
	float flInaccuracyLand;
	float flInaccuracyLandAlt;
	float flInaccuracyLadder;
	float flInaccuracyLadderAlt;
	float flInaccuracyFire;
	float flInaccuracyFireAlt;
	float flInaccuracyMove;
	float flInaccuracyMoveAlt;
	float flInaccuracyReload;
	int iRecoilSeed;
	float flRecoilAngle;
	float flRecoilAngleAlt;
	float flRecoilAngleVariance;
	float flRecoilAngleVarianceAlt;
	float flRecoilMagnitude;
	float flRecoilMagnitudeAlt;
	float flRecoilMagnitudeVariance;
	float flRecoilMagnitudeVarianceAlt;
	float flRecoveryTimeCrouch;
	float flRecoveryTimeStand;
	float flRecoveryTimeCrouchFinal;
	float flRecoveryTimeStandFinal;
	int iRecoveryTransitionStartBullet;
	int iRecoveryTransitionEndBullet;
	bool bUnzoomAfterShot;
	bool bHideViewModelZoomed;
	char pad_0x01B5[ 2 ];
	char iZoomLevels[ 3 ];
	int iZoomFOV[ 2 ];
	float fZoomTime[ 3 ];
	char *szWeaponClass;
	float flAddonScale;
	char pad_0x01DC[ 4 ];
	char *szEjectBrassEffect;
	char *szTracerEffect;
	int iTracerFrequency;
	int iTracerFrequencyAlt;
	char *szMuzzleFlashEffect_1stPerson;
	char pad_0x01F4[ 4 ];
	char *szMuzzleFlashEffect_3rdPerson;
	char pad_0x01FC[ 4 ];
	char *szMuzzleSmokeEffect;
	float flHeatPerShot;
	char *szZoomInSound;
	char *szZoomOutSound;
	float flInaccuracyPitchShift;
	float flInaccuracySoundThreshold;
	float flBotAudibleRange;
	char pad_0x0218[ 8 ];
	char *pWrongTeamMsg;
	bool bHasBurstMode;
	char pad_0x0225[ 3 ];
	bool bIsRevolver;
	bool bCannotShootUnderwater;
};
