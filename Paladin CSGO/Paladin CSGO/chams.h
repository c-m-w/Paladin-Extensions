#pragma once
struct color {
    int r, g, b, a;
};

class chams {
public:
    chams();
    ~chams();
private:
    bool flatWhite;
    color chamColor;
    bool throughWalls;
    bool chamHPColor;
};
