#pragma once
struct weaponSkin {
    int id; //Skin ID
    float wear; //Not actual name but rather value
    int statTrak; //Tracks ur stats mate
    char name[64]; //Idk how long names can be, temp is 64 bytes
    //std::string Name; //Ideally you'd use one of these bad boys but w/e
    int seed; //Have fun figuring this shit out
};
class skinChanger {
public:
    skinChanger(); //How do I inject an mp3 file into counterstrike??
    //Skins
private:
    weaponSkin primary;
    weaponSkin secondary;
    weaponSkin knife; //Maybe allow for T/CT variation?
    weaponSkin glove; //Same as above
    weaponSkin c4; //You used to be able to do with Unity, it was 10/10 to have an abyss C4, but it doesn't mod much (you could also have name tags on them)
    weaponSkin taser;
    //Some collection of WeaponSkin objects, maybe a vector or map that you look up ID's with and get data from there for guns
};
