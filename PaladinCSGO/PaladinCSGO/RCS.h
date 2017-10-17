#pragma once

class RCS
{
public:
	RCS(); //Temporary placeholder, might not need it later on

private:
	bool OnShoot; //Only compensate for recoil when shooting
	
	float PitchScale, YawScale; //How much recoil to compensate for recoil/yaw (mind the roll)

	float NextSmoothe; //Amount of smootheness to apply between shots?

	int DeadTime; //Time or bullet count to ignore when starting to shoot initially
	int Timeout; //Stop recoil control after certain time (this makes no sense, usually you'd want to start with no RCS, then have it activate over time?)
};