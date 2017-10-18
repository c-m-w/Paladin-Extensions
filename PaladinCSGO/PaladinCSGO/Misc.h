#pragma once
class misc 
{
public:
    misc(); //You know the drill

//Removals
private:
    float flashScale; //How much to reduce flash alpha by (maybe change flash color to black or something as well? pfeature right there)
    
//Visuals
private:
    float worldFov; //Overall FoV
    float viewFov; //Viewmodel FoV
   
//Other
private:
    bool autoPistol; //Yes
    bool autoJump; //Very
    int minNextDelay; //MS to wait between jumps (anti SMAC or something?)
    bool edgeJump; //Indeed
   
//Hit sounds
private:
    bool useFile; //Use a premade sound file, otherwise use a beep
    char soundFile[/*MAX_PATH*/ 260]; //Location of sound file (define the thing for MAX_PATH lmao)
    int pitch; //Pitch of beep
    int duration; //Duration of beep
};
