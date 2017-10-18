#pragma once
class aim {
    enum priority {
        kill = 0,
        damage = 1,
        health = 2,
        distance = 3
    };

public:
    aim();
    ~aim();
private:
    bool targetTeam; //If the aimbot should teammates for targetting
    bool targetMode; //If the aimbot should use inCross or FOV for targetting
    float targetFov; //Fov of legitbot
    bool targetSpotted; //If the aimbot should enforce targets must be spotted on Radar
    priority targetPriority[4]; //Can change later, hold priorities in order from most important to last
    int targetArea; //ID of hitbox/bone to use
    bool bSilent; //"Force Move-to-Target limited to FOV" pSilent (bSilent)
    float aimCurve; //Curve Factor
    int aimSmooth; //Smoothness Factor
    float aimOver; //Overaim scale (or amount?)
    int aimDisplace; //Vertical displacement (units)
    int timeout; //Stop following after certain time
    int backtrack; //ms to backtrack
};
