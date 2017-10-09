#pragma once
#define CONFIG_H
class config {
    char cfg[255];
    bool error = false;
public:
    int quit = -1;
    float version = 1.0f;
    const bool checkAc = false; // dont put this one in config
    int keyExit; // all variables must be in config file
    int keyReload;
    bool isHits;
    int hitsPitch;
    int hitsTime;
    bool isSmooth;
    int smoothFactorMin;
    int smoothFactorMax;
    bool isBhop;
    float bhopHitchance;
    int bhopNextDelay;
    int bhopDirection;
    int keyBhop;
    bool isTrig;
    bool isTrigSlow;
    bool isTrigDelay;
    int trigDelayMin;
    int trigDelayMax;
    int trigDelayNextMin;
    int trigDelayNextMax;
    int trigTimeout;
    int keyTrig;
    bool isSlow;
    int slowFactor;
    int slowTimeout;
    bool isRcs;
    int rcsIgnoreShots;
    float rcsXMin;
    float rcsYMin;
    float rcsXMax;
    float rcsYMax;
    bool isAim;
    int aimBone;
    float aimDisplace;
    float aimOver;
    int aimTimeout;
    int keyAim;
    config();
    // read from config
    template<class size> void readConfig(char * setting, char * subsetting, size & status);
    // write to config
    template<class size> void writeConfig(char * setting, char * subsetting, size status);
    // open config, create if doesn't exist
    bool loadConfig();
    // read loaded config, replace impossible values
    bool readConfig();
    ~config();
};
