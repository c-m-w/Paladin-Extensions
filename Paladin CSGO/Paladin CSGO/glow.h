#pragma once
#include "dllmain.h"

class glow {
public:
    glow();
    ~glow();
private:
    bool glowEnemyOnly; // Don't glow teammates
    bool glowSpotted; // Only glow when enemy is visible
    bool glowHp; // Make glow color change based on HP
    color glowColor;
    bool glowWeapons; // Make weapons glow
    bool glowNades; // Make grenades glow (account for active/dropped nades)
    bool glowKits; // Make kits glow
    bool glowHostages; // Make hostages glow
    bool glowBomb; // Make C4 glow (dropped and planted)
};
