#pragma once

class Misc
{
public:
	Misc(); //You know the drill

//Removals
private:
	float FlashScale; //How much to reduce flash alpha by (maybe change flash color to black or something as well? pfeature right there)

//Visuals
private:
	float WorldFoV; //Overall FoV
	float ViewFoV; //Viewmodel FoV

//Other
private:
	bool AutoPistol; //Yes

	bool AutoJump; //Very
	int MinDelay; //MS to wait between jumps (anti SMAC or something?)

	bool EdgeJump; //Indeed

//Hit sounds
private:
	bool UseFile; //Use a premade sound file, otherwise use a beep
	char SoundFile[/*MAX_PATH*/ 260]; //Location of sound file (define the thing for MAX_PATH lmao)

	int Pitch; //Pitch of beep
	int Duration; //Duration of beep
};