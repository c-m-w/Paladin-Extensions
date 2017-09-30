#include "stdafx.h"
class standard;
void main() {
    debug out(true); // ENTER to debug
    auto dbg = &out;
    dbg->setup();
    standard all;
    auto std = &all;
    try {
        if (std->multi > 1) {
            dbg->notice1();
            throw 2;
        }
    } catch (int error) {
        std->quit = error;
        return;
    }
    dbg->done();
    try {
        const auto own = std->ownerCheck();
        if (!own) {
            dbg->notOwner();
            throw 0;
        }
        if (own == -1) {
            dbg->error3();
            return;
        }
    } catch (int error) {
        std->quit = error;
        return;
    }
    dbg->owner();
    std::thread tForce([&std]() {
                   std->force();
                   return;
               });
    if (!std->adminCheck()) {
        dbg->notice2();
    } else if (SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS)) {
        dbg->setPriority();
    }
    if (std->checkAc) {
        const auto ac0 = std->killAc(std->gameName, *std->gameExe);
        const auto ac1 = std->killAc(std->acName, *std->acExe);
        const auto ac2 = std->killAc(std->acName2, *std->acExe2);
        try {
            if (!ac0 || !ac1 || !ac2) {
                dbg->cantKill();
                std->multi = true;
                if (tForce.joinable()) {
                    tForce.join();
                }
                throw 1;
            }
        } catch (int error) {
            std->quit = error;
            return;
        }
        if (ac0 || ac1 || ac2) {
            dbg->warning2();
        } else {
            dbg->noAnticheat();
        }
    } else {
        dbg->notAcScanning();
    }
    if (!std->loadConfig()) {
        dbg->warning3();
    }
    dbg->configLoad();
reset:
    std->setAccess(PROCESS_VM_READ);
    dbg->attachRead();
    if (!std->gameAttach()) {
        dbg->error1();
    }
    dbg->done();
    dbg->moduleWrap();
    const auto clientModule = std->moduleWrapping(_T("client.dll"));
    const auto engineModule = std->moduleWrapping(_T("engine.dll"));
    try {
        if (!clientModule || !engineModule) {
            std->multi = true;
            if (tForce.joinable()) {
                tForce.join();
            }
            dbg->error2();
            throw 3;
        }
    } catch (int error) {
        std->quit = error;
        return;
    }
    dbg->moduleWrapped();
reconnect:
    std->initialize(clientModule, engineModule);
    dbg->memorySetup();
reload:
    do {
        std->z(1);
    } while (!std->closeThreads(false));
    if (!std->readConfig()) {
        dbg->warning4();
    }
    std::thread tBhop([&std]() {
                  std->bhop();
              });
    std::thread tTrig([&std]() {
                  std->trigger();
              });
    std::thread tSlow([&std]() {
                  std->slowaim();
              });
    std::thread tRcs([&std]() {
                 std->rcs();
             });
    std::thread tAim([&std]() {
                 std->aim();
             });
    std::thread tHit([&std]() {
                 std->hits();
             });
    dbg->threading();
    std->multi = true;
    if (tForce.joinable()) {
        tForce.join();
    }
    dbg->complete();
    dbg->active();
    while (true) {
        if (GetAsyncKeyState(std->keyReload)) {
            while (GetAsyncKeyState(std->keyReload)) {
                std->z(1);
            }
            dbg->reload();
            do {
                std->z(1);
            } while (!std->closeThreads(true));
            tBhop.join();
            tTrig.join();
            tSlow.join();
            tRcs.join();
            tAim.join();
            tHit.join();
            goto reload;
        }
        std->z(1);
        if (!FindWindowA(nullptr, std->gameName)) {
            dbg->warning1();
            do {
                std->z(1);
            } while (!std->closeThreads(true));
            tBhop.join();
            tTrig.join();
            tSlow.join();
            tRcs.join();
            tAim.join();
            tHit.join();
            for (auto x = 0; x <= 30; x++) {
                std::cout << "\n";
            }
            dbg->reset();
            goto reset;
        }
        std->z(1);
        if (GetAsyncKeyState(std->keyExit)) {
            dbg->exitKey();
            do {
                std->z(1);
            } while (!std->closeThreads(true));
            tBhop.join();
            tTrig.join();
            tSlow.join();
            tRcs.join();
            tAim.join();
            tHit.join();
            return;
        }
        std->z(1);
        if (std->connection != 6) {
            while (std->connection != 6) {
                if (!FindWindowA(nullptr, std->gameName)) {
                    dbg->warning1();
                    do {
                        std->z(1);
                    } while (!std->closeThreads(true));
                    tBhop.join();
                    tTrig.join();
                    tSlow.join();
                    tRcs.join();
                    tAim.join();
                    tHit.join();
                    for (auto x = 0; x <= 30; x++) {
                        std::cout << "\n";
                    }
                    dbg->reset();
                    goto reset;
                }
                std->z(1);
                if (GetAsyncKeyState(std->keyExit)) {
                    dbg->exitKey();
                    do {
                        std->z(1);
                    } while (!std->closeThreads(true));
                    tBhop.join();
                    tTrig.join();
                    tSlow.join();
                    tRcs.join();
                    tAim.join();
                    tHit.join();
                    return;
                }
                std->z(1);
            }
            goto reconnect;
        }
    }
}
