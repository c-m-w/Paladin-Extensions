#pragma once

struct WeaponSkin
{
	int ID; //Skin ID
	float Wear; //Not actual name but rather value
	int StatTrak; //Tracks ur stats mate
	char Name[64]; //Idk how long names can be, temp is 64 bytes
	//std::string Name; //Ideally you'd use one of these bad boys but w/e
	int Seed; //Have fun figuring this shit out
};

class SkinChanger
{
public:
	SkinChanger(); //How do I inject an mp3 file into counterstrike??

//Skins
private:
	WeaponSkin Knife; //Maybe allow for T/CT variation?
	WeaponSkin Glove; //Same as above
	WeaponSkin C4; //You used to be able to do with Unity, it was 10/10 to have an abyss C4, but it doesn't mod much (you could also have name tags on them)
	//Some collection of WeaponSkin objects, maybe a vector or map that you look up ID's with and get data from there for guns
};