#pragma once
#define CONFIG_H
class config {
    char cfg[255];
    bool error = false;
public:
    int quit = -1;
    float version = 1.0f;
    const bool checkAc = false; // dont put this one in config
    std::atomic<int> keyExit; // all variables must be in config file
    std::atomic<int> keyReload;
    std::atomic<bool> isHits;
    std::atomic<int> hitsPitch;
    std::atomic<int> hitsTime;
    std::atomic<bool> isSmooth;
    std::atomic<int> smoothFactorMin;
    std::atomic<int> smoothFactorMax;
    std::atomic<bool> isBhop;
    std::atomic<float> bhopHitchance;
    std::atomic<int> bhopNextDelay;
    std::atomic<int> bhopDirection;
    std::atomic<int> keyBhop;
    std::atomic<bool> isTrig;
    std::atomic<bool> isTrigSlow;
    std::atomic<bool> isTrigDelay;
    std::atomic<int> trigDelayMin;
    std::atomic<int> trigDelayMax;
    std::atomic<int> trigDelayNextMin;
    std::atomic<int> trigDelayNextMax;
    std::atomic<int> keyTrig;
    std::atomic<bool> isSlow;
    std::atomic<int> slowFactor;
    std::atomic<bool> isRcs;
    std::atomic<int> rcsIgnoreShots;
    std::atomic<float> rcsXMin;
    std::atomic<float> rcsYMin;
    std::atomic<float> rcsXMax;
    std::atomic<float> rcsYMax;
    std::atomic<bool> isAim;
    std::atomic<int> aimBone;
    std::atomic<float> aimDisplace;
    std::atomic<float> aimOver;
    std::atomic<int> keyAim;
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
