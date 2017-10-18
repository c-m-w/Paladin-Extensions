#pragma once
class rcs {
public:
    rcs();
    ~rcs();
private:
    bool onShoot; //Only compensate for recoil when shooting
    float pitchScale, yawScale; //How much recoil to compensate for recoil/yaw (mind the roll)
    int smooth; //Amount of smootheness to apply between shots?
    int deadTime; //Time or bullet count to ignore when starting to shoot initially
    int timeout; //Stop recoil control after certain time (this makes no sense, usually you'd want to start with no RCS, then have it activate over time?)
};
