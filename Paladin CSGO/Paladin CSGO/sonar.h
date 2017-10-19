#pragma once
class sonar {
public:
    sonar();
    ~sonar();
private:
    int pitch, duration, frequency;
    bool file;
    char fileLocation[/*MAX_PATH*/260];
    int curveFactor;
    int maxDistance;
};
