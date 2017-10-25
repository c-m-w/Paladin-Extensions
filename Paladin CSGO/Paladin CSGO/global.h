#pragma once
#include "dllmain.h"

#define PI 3.141593f

inline void wait(const unsigned int z) {
    std::this_thread::sleep_for(std::chrono::milliseconds(z));
}

inline int msTime() {

    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

struct address {
    DWORD offset; // original
    DWORD cl; // current location in memory
};

struct angle {
    float pitch, yaw, roll; // y, x, z
};

struct coordinate {
    float x, y, z;
};

struct color {
    uint8_t r, g, b, a; // unsigned __int8
};


angle angleCurrent;

inline bool normalize(angle & angle) {
    bool change = false;
    // clamp
    if (angle.pitch > 89.f) {
        angle.pitch = 89.f;
        change = true;
    }
    else if (angle.pitch < -89.f) {
        angle.pitch = -89.f;
        change = true;
    }
    while (angle.yaw > 180.f) {
        angle.yaw -= 360.f;
        change = true;
    }
    while (angle.yaw < -180.f) {
        angle.yaw += 360.f;
        change = true;
    }
    if (angle.roll > 50.f) {
        angle.roll = 50.f;
        change = true;
    }
    if (angle.roll < -50.f) {
        angle.roll = 50.f;
        change = true;
    }

    // normalize
    if (hypot(angle.pitch - angleCurrent.pitch, angle.yaw - angleCurrent.yaw) > 22.f /*&& !Smoothing*/) {
        if (angle.pitch - angleCurrent.pitch > 0) {
            //TODO
        }
        else if (angle.pitch - angleCurrent.pitch < 0) {
            //TODO
        }
        if (angle.yaw - angleCurrent.yaw > 0) {
            //TODO
        }
        else if (angle.yaw - angleCurrent.yaw < 0) {
            //TODO
        }
        change = true;
    }
    return change;
}

inline bool round(angle & angleTo) {
    //TODO
}
