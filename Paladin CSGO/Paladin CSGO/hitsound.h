#pragma once
class hitsound {
public:
    hitsound();
    ~hitsound();

private:
    int pitch, duration;
    bool soundFile;
    char fileLocation[/*MAX_PATH*/260];
};
