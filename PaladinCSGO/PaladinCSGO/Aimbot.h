#pragma once
//Aimbot target selection priority
enum priority {
    kill = 0,
    damage = 1,
    health = 2,
    distance = 3
};
class aimbot {
public:
    //Placeholder, we might not need a constructor later on
    aimbot();
private:
    bool attackTeam; //Attack teammates
    bool spotted; //Only shoot enemies you can see
    int hitArea; //ID of hitbox/bone to use
    bool bSilent; //What the fuck?
    float fov; //FoV of legitbot
    float curve; //Curve scale?
    int smoothFactor; //Based on "denominating factor"?
    float overaim; //Overaim scale (or amount?)
    int displace; //Vertical displacement (angle? units? scale?)
    int timeout; //Stop following after certain time
    int backtrack; //MS to backtrack
    priority priority[4]; //Can change later, hold priorities in order from most important to last
};
