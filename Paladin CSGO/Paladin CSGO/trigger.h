#pragma once
#include "dllmain.h"

class trigger {
public:
    trigger();
    ~trigger();
private:
    int spottedDelay;
    bool inCross;
    int maxBulletCount;
    int postBurst;
    bool slowTrigger;
};
