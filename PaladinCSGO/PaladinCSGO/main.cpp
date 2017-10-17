#include "main.h"
int main() {
    AllocConsole();
    AttachConsole(GetCurrentProcessId());
    freopen("CON", "w", stdout);
    return 0;
}
bool WINAPI dllmain(HMODULE instanceSelf, DWORD callReason, LPVOID none) {
    if (callReason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(instanceSelf);
        CreateThread(0, 0, LPTHREAD_START_ROUTINE(main), instanceSelf, 0, 0);
    } else if (callReason == DLL_PROCESS_DETACH) {
        // TODO
    }
    return false;
}
