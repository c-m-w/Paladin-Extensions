#pragma once
struct color {
    int r, g, b, a;
};
class esp {
public:
    esp(); //Might not need later on
    //Glow stuff
private:
    bool glowEnemyOnly; //Don't glow teammates
    bool glowSpotted; //Only glow when enemy is visible
    bool glowHp; //Make glow color change based on HP
    color glowColor;
    bool glowWeapons; //Make weapons glow
    bool glowNades; //Make grenades glow (account for active/dropped nades)
    bool glowKits; //Make kits glow
    bool glowHostages; //Make hostages glow
    bool glowBomb; //Make C4 glow (dropped and planted)
    //Cham stuff
private:
    bool chamEnemyOnly; //Don't cham teammates
    bool chamMode; //0 - Normal Colorized, 1 - Flat Colorized
    bool chamSpotted; //Only cham visible parts of enemy
    bool chamHp; //Make cham color change based on HP
    color chamColor;
    //Radar
private:
    bool radarActive; //Gee I wonder
    bool radarMode; //0 - Cirlce, 1 - Square
    //Sonar
private:
    bool sonarActive; //What a mystery
    int sonarSpeed; //Speed of scan line
    int sonarFrequency; //How often it goes by
    int sonarMaxDist; //How far sonar will scan
    int curveFactor; //?????
};
