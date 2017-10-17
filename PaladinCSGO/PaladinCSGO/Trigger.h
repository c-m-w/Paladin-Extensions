#pragma once

//I also combine this with slow aim since I feel they belong together
class Trigger
{
public:
	Trigger(); //We might not need this later on

//Trigger stuff
private:
	bool InCross; //0 = Unity style, 1 = logical way a triggerbot should work

	int Delay; //Time to wait before shooting upon seeing

	int MaxBullets; //Max bullets to shoot until stopping

	bool Burst; //For auto firing weapons
	int PostBurst; //Shots to fire after a burst?

	bool Slow; //What's slow trigger? Maybe meant for slow aim?

//Slow aim stuff
private:
	float Factor; //How much to slow down aiming by
	int Timeout; //How long to slow down aim for in ms
};