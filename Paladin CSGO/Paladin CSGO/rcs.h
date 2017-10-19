#pragma once

class rcs 
{
public:
<<<<<<< HEAD:PaladinCSGO/PaladinCSGO/RCS.h
    rcs(); //Temporary placeholder, might not need it later on

=======
    rcs();
    ~rcs();
>>>>>>> ee3a7866ef14639ec735cc8a6942a47e618ff85d:Paladin CSGO/Paladin CSGO/rcs.h
private:
    bool onShoot; //Only compensate for recoil when shooting
    float pitchScale, yawScale; //How much recoil to compensate for recoil/yaw (mind the roll)
    int smooth; //Amount of smootheness to apply between shots?
    int deadTime; //Time or bullet count to ignore when starting to shoot initially
    int timeout; //Stop recoil control after certain time (this makes no sense, usually you'd want to start with no RCS, then have it activate over time?)
};
