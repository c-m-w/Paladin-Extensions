#pragma once
#define MEMORY_H
class memory: public config {
    const float pi = 3.14159265358979323846f;
    struct vector {
        float x, y, z;
    };
    struct coordinate {
        int x, y;
    };
    HANDLE snapHandle;
    PROCESSENTRY32 processEntry;
    MODULEENTRY32 moduleEntry;
    DWORD access;
    DWORD pointerLocalPlayer = 0xAAEC3C;
    DWORD pointerClientState = 0x5A4344;
    DWORD offsetConnection = 0x108;
    DWORD offsetCrosshair = 0xB294;
    DWORD offsetFlag = 0x100;
    DWORD offsetSensitivity = 0xAB433C;
    DWORD offsetSensitivityPtr = offsetSensitivity - 0x2C;
    DWORD offsetHits = 0x3344;
    DWORD offsetShotFired = 0xA2A0;
    DWORD offsetViewPunch = 0x301C;
    DWORD offsetPlayerLocation = 0x134;
    DWORD offsetEntities = 0x4A8C02C;
    DWORD localPlayer;
    DWORD clientState;
    DWORD entityEnemy;
    vector enemyBone;
    vector viewPunchCurrent;
    vector viewPunchPrevious;
    vector localPlayerLocation;
    int flag;
    int inCross;
    int winSens;
    int shotFired;
    int shotsLanded;
    int sensitivity;
    bool wasInCross = false;
    float sens;
    float convertMouse;
    coordinate screen;
    coordinate mouseAim;
    coordinate mouseRcs;
    std::atomic<int> shotFiredPrevious;
    std::atomic<vector> aimTo;
    std::atomic<vector> rcsTo;
    // read process memory 
    template<class size> void rpm(DWORD read, size & write);
    // write process memory
    template<class size> void wpm(DWORD read, size & write);
    std::atomic<bool> timeToExit = false;
    // pattern scan
    static BOOL patternCompare(BYTE * pData, BYTE * bMask, char * szMask);
    // find pattern
    DWORD findPattern(BYTE * mask, char * szMask, DWORD address, DWORD length) const;
public:
    const LPCSTR gameName = "Counter-Strike: Global Offensive";
    char const * gameExe = "csgo.exe";
    const LPCSTR acName = "Steam";
    char const * acExe = "steam.exe";
    const LPCSTR acName2 = "FACEIT AC";
    char const * acExe2 = "faceitclient.exe";
    HANDLE gameHandle = nullptr;
    int connection;
    // ctor
    memory();
    // shorthand sleep in ms
    static void z(int z);
    // attach to game
    bool gameAttach();
    // module wrapping
    DWORD_PTR moduleWrapping(TCHAR * moduleName);
    // set access
    void setAccess(DWORD accessI);
    // initial memory set up
    void initialize(DWORD_PTR clientModule, DWORD_PTR engineModule);
    // termination
    bool closeThreads(bool exit);
    // exit check
    bool exit(bool isContinue) const;
    // bhop script
    void bhop();
    // trigger bot
    void trigger();
    // slow aim
    void slowaim();
    // recoil control system
    void rcs();
    // aimbot
    void aim();
    // hitsound
    void hits();
    // dctor
    ~memory();
};
