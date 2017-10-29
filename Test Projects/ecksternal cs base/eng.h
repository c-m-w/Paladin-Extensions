#pragma once
class Engine {
private:
    HANDLE hGame;
    DWORD clientDll;
    DWORD engineDll;
    DWORD clientOffs;
    DWORD client;
    DWORD clientStateOffs;
    DWORD clientState;
private:
    angle curAngles;
public:
    Engine();
    ~Engine();
    bool attach();
    bool init();
public:
    void test();
public:
    template<class t> t rpm(DWORD addr) {
        t tmp;
        ReadProcessMemory(hGame, (LPVOID)addr, &tmp, sizeof(t), nullptr);
        return tmp;
    }

    template<class t> void wpm(DWORD addr, t & val) {
        WriteProcessMemory(hGame, (LPVOID)addr, val, sizeof(t), nullptr);
    }
};
