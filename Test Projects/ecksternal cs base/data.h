#pragma once
#define uint8_t __int8

struct angle {
    float pitch, yaw, roll; // y, x, z
};

struct coord {
    float x, y, z;
};

struct color {
    uint8_t r, g, b, a;
};

//For debug printing
enum DBG_MSG {
    SCS = 0,
    DBG = 1,
    WRN = 2,
    ERR = 3
};
