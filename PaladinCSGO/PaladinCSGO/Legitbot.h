#pragma once

//Aimbot target selection priority
enum LB_PRIORITY
{
	LB_KILL = 0,
	LB_DMG = 1,
	LB_DIST = 2,
	LB_FOV = 3
};

class LegitBot
{
public:
	//Placeholder, we might not need a constructor later on
	LegitBot();

private:
	bool AttackTeam; //Attack teammates
	bool Spotted; //Only shoot enemies you can see
	bool BSilent; //What the fuck?

	int HitArea; //ID of hitbox/bone to use

	float FoV; //FoV of legitbot

	float Curve; //Curve scale?
	int SmootheFactor; //Based on "denominating factor"?
	float Overaim; //Overaim scale (or amount?)

	int Timeout; //Stop following after certain time

	int VerDisp; //Vertical displacement (angle? units? scale?)

	LB_PRIORITY Priority[4]; //Can change later, hold priorities in order from most important to last

	int Backtrack; //MS to backtrack
};