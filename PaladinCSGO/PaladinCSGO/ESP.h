#pragma once

//ToDo: Add color options, maybe have a seperate dedicated class for colors?
class ESP
{
public:
	ESP(); //Might not need later on

//Glow stuff
private:
	bool EnemyOnly; //Don't glow teammates

	bool Spotted; //Only glow when enemy is visible

	bool GlowHP; //Make glow color change based on HP
	
	bool GlowWeapons; //Make weapons glow
	bool GlowNades; //Make grenades glow (account for active/dropped nades)
	bool GlowKits; //Make kits glow
	bool GlowHostages; //Make hostages glow
	bool GlowBomb; //Make C4 glow (dropped and planted)

//Cham stuff
private:
	int ChamMode; //0 - Flat, 1 - Full, 2 - Wire, 3 - Point
	
	bool Spotted; //Only cham visible parts of enemy

	bool ChamHP; //Make cham color change based on HP

//Radar
private:
	bool RadarActive; //Gee I wonder
	int RadarMode; //0 - Ingame, 1 - Window

//Sonar
private:
	bool SonarActive; //What a mystery

	int SonarSpeed; //Speed of scan line
	int Frequency; //How often it goes by
	int SonarMaxDist; //How far sonar will scan
	int CurveFactor; //?????
};