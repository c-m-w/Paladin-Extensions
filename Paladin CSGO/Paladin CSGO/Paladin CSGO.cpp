#include "Paladin CSGO.h"
int main() {
    AllocConsole();
    AttachConsole(GetCurrentProcessId());
    freopen("CON", "w", stderr);
    freopen("CON", "w", stdout);
    Application::EnableVisualStyles();
    PaladinCSGO::PaladinCSGO formPaladin;
    Application::Run(%formPaladin);
}
BOOL WINAPI dllmain(_In_ HINSTANCE instance, _In_ DWORD reason, _In_ LPVOID extra) {
    if (reason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(instance);
        CreateThread(0, 0, LPTHREAD_START_ROUTINE(main), instance, 0, 0);
    }
}
