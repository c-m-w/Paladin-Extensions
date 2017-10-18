#include "dllmain.h"

BOOL WINAPI dllmain(const HMODULE instanceSelf, const DWORD callReason, LPVOID none) {
    if (callReason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(instanceSelf);

        // TODO our enter stuff here

    } else if (callReason == DLL_PROCESS_DETACH) {

        FreeLibraryAndExitThread(instanceSelf, quitReason); // TODO define quitReason in config, save quit reason to config

    }

    return 0;
}
