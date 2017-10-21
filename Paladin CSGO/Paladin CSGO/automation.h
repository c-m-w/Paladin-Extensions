#pragma once
#include "dllmain.h"

class automation {
public:
    automation();
    ~automation();
private:
    bool autoPistol;
    bool autoJump;
    int minimumDelay;
    bool edgeJump;
};
