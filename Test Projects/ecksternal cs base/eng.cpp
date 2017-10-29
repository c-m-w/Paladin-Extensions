#include "main.h"

Engine::Engine() {
    this->hGame = nullptr;

    this->clientDll = NULL;
    this->engineDll = NULL;

    this->clientOffs = 0x5A765C;
    this->client = NULL;

    this->clientStateOffs = 0x108;
    this->clientState = NULL;
}

Engine::~Engine() {
    //Clean up engine
}

bool Engine::attach() {
    DWORD dwProcessId = NULL;

    while (!GetWindowThreadProcessId(FindWindowA(nullptr, "Counter-Strike: Global Offensive"), &dwProcessId)) {
        Debug(DBG, "Searching for CSGO\n");
        wait(1000);
    }

    this->hGame = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, false, dwProcessId);

    if (!this->hGame) {
        Debug(ERR, "Invalid game handle\n");
        return false;
    }

    Debug(SCS, "Attached to game\n");

    HANDLE hSnapshot = INVALID_HANDLE_VALUE;

    for (int i = 0; i < 5; i++, wait(2000)) {

        do {
            SetLastError(0);
            hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcessId);
            wait(10);
        } while (hSnapshot == INVALID_HANDLE_VALUE || GetLastError() == ERROR_BAD_LENGTH);

        if (hSnapshot == INVALID_HANDLE_VALUE) {
            Debug(ERR, "Invalid module snapshot\n");
            return false;
        }

        Debug(SCS, "Module snapshot created\n");

        MODULEENTRY32 me = {};
        me.dwSize = sizeof(MODULEENTRY32);

        if (Module32First(hSnapshot, &me)) {
            do {
                if (!_stricmp(me.szModule, "client.dll"))
                    this->clientDll = (DWORD)me.modBaseAddr;
                else if (!_stricmp(me.szModule, "engine.dll"))
                    this->engineDll = (DWORD)me.modBaseAddr;
            } while (Module32Next(hSnapshot, &me));
            CloseHandle(hSnapshot);
        }

        if (this->clientDll && this->engineDll) {
            Debug(SCS, "Modules found\n");
            Debug(SCS, "Client.dll: 0x%p\n", this->clientDll);
            Debug(SCS, "Engine.dll: 0x%p\n", this->engineDll);
            return true;
        }

        Debug(DBG, "Modules not found, retrying");
        Debug(DBG, "Client.dll: 0x%p\n", this->clientDll);
        Debug(DBG, "Engine.dll: 0x%p\n", this->engineDll);
    }

    Debug(ERR, "Unable to get modules\n");

    return false;
}

bool Engine::init() {
    this->client = rpm<DWORD>(this->engineDll + this->clientOffs);

    Debug(DBG, "Client: 0x%p\n", this->client);

    return true;
}

void Engine::test() {
    while (!GetAsyncKeyState(VK_F4)) {
        this->clientState = rpm<DWORD>(this->client + this->clientStateOffs);
        Debug(DBG, "[0x%p] %d\n", (DWORD)this->client + (DWORD)this->clientStateOffs, this->clientState);
        wait(3000);
    }
}
