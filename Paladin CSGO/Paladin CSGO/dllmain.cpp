#include "dllmain.h"
// todo debug stuff (maybe make class?)
// todo hwid stuff (maybe make class?)
BOOL WINAPI dllmain(HMODULE hSelf, const DWORD cReason, void*) {
    if (cReason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hSelf);

        // TODO our enter stuff here

    } else if (cReason == DLL_PROCESS_DETACH) {

        //FreeLibraryAndExitThread(instanceSelf, quitReason); // TODO define quitReason in config, save quit reason to config

    }

    return 0;
}
