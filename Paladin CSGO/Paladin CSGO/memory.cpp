#include "memory.h"

memory::memory() {
}

memory::~memory() {
    if (hGame != nullptr || hGame != INVALID_HANDLE_VALUE) {
        CloseHandle(hGame);
    }
}

bool memory::attach() {
    // open process
    DWORD dwProcessId;
    while (!GetWindowThreadProcessId(FindWindowA(nullptr, "Counter-Strike: Global Offensive"), &dwProcessId)) {
        wait(1000);
    }
    hGame = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE, false, dwProcessId);
    if (!hGame) {
        return false;
    }

    // walk & wrap modules
    const int startTime = msTime(); // const -> start time shouldn't change
    HANDLE hSnapshot;
    while (10000 < msTime() - startTime) {
        do {
            SetLastError(0);
            hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcessId);
            wait(1);
        } while (hSnapshot == INVALID_HANDLE_VALUE && GetLastError() == ERROR_BAD_LENGTH);
        if (hSnapshot == INVALID_HANDLE_VALUE) {
            return false;
        }
        MODULEENTRY32 me;
        me.dwSize = sizeof(MODULEENTRY32);
        if (Module32First(hSnapshot, &me)) {
            do {
                if (!_stricmp(me.szModule, "client.dll")) {
                    clientDll = DWORD_PTR(me.modBaseAddr);
                }
                else if (!_stricmp(me.szModule, "engine.dll")) {
                    engineDll = DWORD_PTR(me.modBaseAddr);
                }
            } while (Module32Next(hSnapshot, &me) || !clientDll && !engineDll);
            CloseHandle(hSnapshot);
        }
        if (!clientDll || !engineDll) {
            wait(1000);
            continue;
        }
        return true;
    }
    return false;
}

template<class size> void memory::rpm(const DWORD read, size & write) {
    ReadProcessMemory(hGame, LPVOID(read), &write, sizeof(size), nullptr);
}

template<class size> void memory::wpm(const DWORD read, size & write) {
    WriteProcessMemory(hGame, LPVOID(read), &write, sizeof(size), nullptr);
}

bool memory::patternCompare() {
}

DWORD memory::findPattern() {
}
