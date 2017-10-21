#pragma once
#include "dllmain.h"

class memory {
public:
    memory();
    ~memory();
private:
    bool attach();
    HANDLE hGame;
    DWORD_PTR clientDll;
    DWORD_PTR engineDll;
    template<class size> void rpm(DWORD read, size & write);
    template<class size> void wpm(DWORD read, size & write);
    static bool patternCompare(/*TODO*/);
    static DWORD findPattern(/*TODO*/);
};
