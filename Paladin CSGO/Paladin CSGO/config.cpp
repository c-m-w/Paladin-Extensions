#include "stdafx.h"
#include "config.h"
config::config() {
    keyExit = VK_F4;
    keyReload = VK_F5;
    keyAim = VK_RBUTTON;
    keyTrig = VK_XBUTTON2;
    keyBhop = VK_XBUTTON1;
    isHits = true;
    hitsPitch = 500;
    hitsTime = 50;
    isSmooth = true;
    smoothFactorMin = 7;
    smoothFactorMax = 10;
    isSlow = true;
    slowFactor = 2;
    isBhop = true;
    bhopHitchance = 100.f;
    bhopNextDelay = 20;
    bhopDirection = -1;
    isAim = true;
    aimBone = 8;
    aimDisplace = 0.f;
    aimOver = 1.1f;
    isRcs = true;
    rcsIgnoreShots = 1;
    rcsXMin = 0.9f;
    rcsXMax = 1.1f;
    rcsYMin = 0.9f;
    rcsYMax = 1.1f;
    isTrig = true;
    isTrigSlow = true;
    isTrigDelay = false;
    trigDelayMin = 10;
    trigDelayMax = 20;
    trigDelayNextMin = 7;
    trigDelayNextMax = 10;
}
template<class size> void config::readConfig(char * setting, char * subsetting, size & status) {
    char temp[255];
    if (!GetPrivateProfileStringA(setting, subsetting, nullptr, temp, 255, cfg)) {
        error = true;
    }
    status = atof(temp);
}
template<class size> void config::writeConfig(char * setting, char * subsetting, size status) {
    char temp[255];
    if (std::is_same<size, int>::value || std::is_same<size, bool>::value) {
        sprintf_s(temp, "%d", status);
    } else {
        sprintf_s(temp, "%.2f", status);
    }
    WritePrivateProfileStringA(setting, subsetting, temp, cfg);
}
bool config::loadConfig() {
    char tempChar[MAX_PATH];
    GetModuleFileName(nullptr, tempChar, MAX_PATH);
    memset(cfg, 0, 255);
    strcpy_s(cfg, std::string(tempChar).substr(NULL, std::string(tempChar).find_last_of("/\\") + 1).c_str());
    strcat_s(cfg, "config.txt");
    struct stat buffer;
    if (stat(cfg, &buffer) != 0) {
        writeConfig<int>("Key Binds", "Terminate", keyExit);
        writeConfig<int>("Key Binds", "Reload Config", keyReload);
        writeConfig<int>("Key Binds", "Aimbot", keyAim);
        writeConfig<int>("Key Binds", "Triggerbot", keyTrig);
        writeConfig<int>("Key Binds", "Bunny Hop", keyBhop);
        writeConfig<bool>("Hit Sound", "Enabled", isHits);
        writeConfig<int>("Hit Sound", "Pitch", hitsPitch);
        writeConfig<int>("Hit Sound", "Duration", hitsTime);
        writeConfig<bool>("Smoothing", "Enabled", isSmooth);
        writeConfig<int>("Smoothing", "Factor Minimum", smoothFactorMin);
        writeConfig<int>("Smoothing", "Factor Maximum", smoothFactorMax);
        writeConfig<bool>("Slow Aim", "Enabled", isSlow);
        writeConfig<int>("Slow Aim", "Slowing Factor", slowFactor);
        writeConfig<bool>("Bunny Hop", "Enabled", isBhop);
        writeConfig<float>("Bunny Hop", "Hit Chance", bhopHitchance);
        writeConfig<int>("Bunny Hop", "Following Jump Delay", bhopNextDelay);
        writeConfig<int>("Bunny Hop", "Direction", bhopDirection);
        writeConfig<bool>("Aimbot", "Enabled", isAim);
        writeConfig<int>("Aimbot", "Target Bone", aimBone);
        writeConfig<float>("Aimbot", "Targetting Displacement", aimDisplace);
        writeConfig<float>("Aimbot", "Over Compensation", aimOver);
        writeConfig<bool>("Recoil Control", "Enabled", isRcs);
        writeConfig<int>("Recoil Control", "Ignore Shot Count", rcsIgnoreShots);
        writeConfig<float>("Recoil Control", "Minimum X Compensation", rcsXMin);
        writeConfig<float>("Recoil Control", "Maximum X Compensation", rcsXMax);
        writeConfig<float>("Recoil Control", "Minimum Y Compensation", rcsYMin);
        writeConfig<float>("Recoil Control", "Maximum Y Compensation", rcsYMax);
        writeConfig<bool>("Triggerbot", "Enabled", isTrig);
        writeConfig<bool>("Triggerbot", "Slowed Trigger", isTrigSlow);
        writeConfig<bool>("Triggerbot", "Delay Enabled", isTrigDelay);
        writeConfig<int>("Triggerbot", "Minimum First Shot Delay", trigDelayMin);
        writeConfig<int>("Triggerbot", "Maximum First Shot Delay", trigDelayMax);
        writeConfig<int>("Triggerbot", "Minimum Following Shot Delay", trigDelayNextMin);
        writeConfig<int>("Triggerbot", "Maximum Following Shot Delay", trigDelayNextMax);
        writeConfig<int>("Debug", "Quit Reason", quit);
        writeConfig<float>("Debug", "Version", version);
        return false;
    }
    return true;
}
bool config::readConfig() {
    float cfgver;
    readConfig<float>("Debug", "Version", cfgver);
    if (cfgver == version) {
        readConfig<std::atomic<int>>("Key Binds", "Terminate", keyExit);
        readConfig<std::atomic<int>>("Key Binds", "Reload Config", keyReload);
        readConfig<std::atomic<int>>("Key Binds", "Aimbot", keyAim);
        readConfig<std::atomic<int>>("Key Binds", "Triggerbot", keyTrig);
        readConfig<std::atomic<int>>("Key Binds", "Bunny Hop", keyBhop);
        readConfig<std::atomic<bool>>("Hit Sound", "Enabled", isHits);
        readConfig<std::atomic<int>>("Hit Sound", "Pitch", hitsPitch);
        readConfig<std::atomic<int>>("Hit Sound", "Duration", hitsTime);
        readConfig<std::atomic<bool>>("Smoothing", "Enabled", isSmooth);
        readConfig<std::atomic<int>>("Smoothing", "Factor Minimum", smoothFactorMin);
        readConfig<std::atomic<int>>("Smoothing", "Factor Maximum", smoothFactorMax);
        readConfig<std::atomic<bool>>("Slow Aim", "Enabled", isSlow);
        readConfig<std::atomic<int>>("Slow Aim", "Slowing Factor", slowFactor);
        readConfig<std::atomic<bool>>("Bunny Hop", "Enabled", isBhop);
        readConfig<std::atomic<float>>("Bunny Hop", "Hit Chance", bhopHitchance);
        readConfig<std::atomic<int>>("Bunny Hop", "Following Jump Delay", bhopNextDelay);
        readConfig<std::atomic<int>>("Bunny Hop", "Direction", bhopDirection);
        readConfig<std::atomic<bool>>("Aimbot", "Enabled", isAim);
        readConfig<std::atomic<int>>("Aimbot", "Target Bone", aimBone);
        readConfig<std::atomic<float>>("Aimbot", "Targetting Displacement", aimDisplace);
        readConfig<std::atomic<float>>("Aimbot", "Over Compensation", aimOver);
        readConfig<std::atomic<bool>>("Recoil Control", "Enabled", isRcs);
        readConfig<std::atomic<int>>("Recoil Control", "Ignore Shot Count", rcsIgnoreShots);
        readConfig<std::atomic<float>>("Recoil Control", "Minimum X Compensation", rcsXMin);
        readConfig<std::atomic<float>>("Recoil Control", "Maximum X Compensation", rcsXMax);
        readConfig<std::atomic<float>>("Recoil Control", "Minimum Y Compensation", rcsYMin);
        readConfig<std::atomic<float>>("Recoil Control", "Maximum Y Compensation", rcsYMax);
        readConfig<std::atomic<bool>>("Triggerbot", "Enabled", isTrig);
        readConfig<std::atomic<bool>>("Triggerbot", "Slowed Trigger", isTrigSlow);
        readConfig<std::atomic<bool>>("Triggerbot", "Delay Enabled", isTrigDelay);
        readConfig<std::atomic<int>>("Triggerbot", "Minimum First Shot Delay", trigDelayMin);
        readConfig<std::atomic<int>>("Triggerbot", "Maximum First Shot Delay", trigDelayMax);
        readConfig<std::atomic<int>>("Triggerbot", "Minimum Following Shot Delay", trigDelayNextMin);
        readConfig<std::atomic<int>>("Triggerbot", "Maximum Following Shot Delay", trigDelayNextMax);
        if (keyExit <= 0) {
            keyExit = VK_F4;
        }
        if (keyReload <= 0) {
            keyReload = VK_F5;
        }
        if (isHits) {
            if (hitsPitch < 1) {
                hitsPitch = 500;
            }
            if (hitsTime < 1) {
                hitsTime = 50;
            }
        }
        if (isSmooth) {
            if (smoothFactorMin < 0) {
                smoothFactorMin = 0;
            }
            if (smoothFactorMin > smoothFactorMax) {
                smoothFactorMax = smoothFactorMin._My_val;
            }
        }
        if (isBhop) {
            if (bhopHitchance < 0.f || bhopHitchance > 100.f) {
                bhopHitchance = 100.f;
            }
            if (bhopNextDelay < 1) {
                bhopNextDelay = 1;
            }
            if (bhopDirection != (1 | -1)) {
                bhopDirection = -1;
            }
            if (keyBhop <= 0) {
                keyBhop = VK_XBUTTON1;
            }
        }
        if (isTrig) {
            if (trigDelayMax < trigDelayMin) {
                trigDelayMax = trigDelayMin._My_val;
            }
            if (trigDelayNextMin < 7) {
                trigDelayNextMin = 7;
            }
            if (trigDelayNextMax < trigDelayNextMin) {
                trigDelayNextMax = trigDelayNextMin._My_val;
            }
            if (trigDelayNextMin < 7) {
                trigDelayNextMin = 7;
            }
            if (keyTrig <= 0) {
                keyTrig = VK_XBUTTON2;
            }
        }
        if (isSlow) {
            if (slowFactor < 2) {
                slowFactor = 2;
            }
        }
        if (isRcs) {
            if (rcsIgnoreShots < 1) {
                rcsIgnoreShots = 1;
            }
            if (rcsXMin < 0.f) {
                rcsXMin = 0.f;
            }
            if (rcsXMax < rcsXMin) {
                rcsXMax = rcsXMin._My_val;
            }
            if (rcsYMin < 0.f) {
                rcsYMin = 0.f;
            }
            if (rcsYMax < rcsYMin) {
                rcsYMax = rcsYMin._My_val;
            }
        }
        if (isAim) {
            if (aimBone < 0) {
                aimBone = 8;
            }
            if (aimOver <= 0.f) {
                aimOver = 1.f;
            }
            if (keyAim <= 0) {
                keyAim = VK_LBUTTON;
            }
        }
    } else {
        error = true;
    }
    if (error) {
        keyExit = VK_F4;
        keyReload = VK_F5;
        keyAim = VK_RBUTTON;
        keyTrig = VK_XBUTTON2;
        keyBhop = VK_XBUTTON1;
        isSmooth = true;
        smoothFactorMin = 7;
        smoothFactorMax = 10;
        isSlow = true;
        slowFactor = 2;
        isBhop = true;
        bhopHitchance = 100.f;
        isAim = true;
        aimBone = 8;
        aimDisplace = 0.f;
        aimOver = 1.1f;
        isRcs = true;
        rcsIgnoreShots = 1;
        rcsXMin = 0.9f;
        rcsXMax = 1.1f;
        rcsYMin = 0.9f;
        rcsYMax = 1.1f;
        isTrig = true;
        isTrigSlow = true;
        isTrigDelay = false;
        trigDelayMin = 10;
        trigDelayMax = 20;
        trigDelayNextMin = 7;
        trigDelayNextMax = 10;
    }
    return !error;
}
config::~config() {
    writeConfig<int>("Debug", "Quit Reason", quit);
}
