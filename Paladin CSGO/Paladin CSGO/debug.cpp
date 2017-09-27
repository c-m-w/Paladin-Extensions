#include "stdafx.h"
#include "debug.h"
debug::debug(const bool toDebug) {
    wantDebug = toDebug;
    if (toDebug && wantDebug) {
        AllocConsole();
        for (auto x = 1; x <= 30; x++) {
            std::cout << "\n";
        }
    } else {
        FreeConsole();
    }
}
void debug::setup() const {
    if (wantDebug) {
        std::cout << "Doing initial setup...\n\n";
    }
}
void debug::notOwner() const {
    if (wantDebug) {
        std::cout << "Not owner of cheat!\n\n";
    }
}
void debug::owner() const {
    if (wantDebug) {
        std::cout << "Owner of cheat!\n\n";
    }
}
void debug::done() const {
    if (wantDebug) {
        std::cout << "Done.\n\n";
    }
}
void debug::notAcScanning() const {
    if (wantDebug) {
        std::cout << "Not scanning for anticheat.\n\n";
    }
}
void debug::cantKill() const {
    if (wantDebug) {
        std::cout << "Can't kill running anticheat!\n\n";
    }
}
void debug::noAnticheat() const {
    if (wantDebug) {
        std::cout << "No anticheat detected.\n\n";
    }
}
void debug::setPriority() const {
    if (wantDebug) {
        std::cout << "Set Priority to High.\n\n";
    }
}
void debug::configLoad() const {
    if (wantDebug) {
        std::cout << "Loaded config.\n\n";
    }
}
void debug::attachRead() const {
    if (wantDebug) {
        std::cout << "Attaching to game with read only access...\n\n";
    }
}
void debug::attachAll() const {
    if (wantDebug) {
        std::cout << "Attaching to game with full access...\n\n";
    }
}
void debug::attached() const {
    if (wantDebug) {
        std::cout << "Attached.\n\n";
    }
}
void debug::moduleWrap() const {
    if (wantDebug) {
        std::cout << "Wrapping Module(s)...\n\n";
    }
}
void debug::moduleWrapped() const {
    if (wantDebug) {
        std::cout << "Module(s) wrapped.\n\n";
    }
}
void debug::memorySetup() const {
    if (wantDebug) {
        std::cout << "Memory setup.\n\n";
    }
}
void debug::configRead() const {
    if (wantDebug) {
        std::cout << "Read config.\n\n";
    }
}
void debug::threading() const {
    if (wantDebug) {
        std::cout << "Threads setup.\n\n";
    }
}
void debug::complete() const {
    if (wantDebug) {
        std::cout << "Finished set up.\n\n";
    }
}
void debug::active() const {
    if (wantDebug) {
        std::cout << "The cheat is now active!\n\n";
    }
}
void debug::reload() const {
    if (wantDebug) {
        std::cout << "Reloaded!\n\n";
    }
}
void debug::reset() const {
    if (wantDebug) {
        std::cout << "Reset.\n\n";
    }
}
void debug::exitKey() const {
    if (wantDebug) {
        std::cout << "\nExit key pressed!\nTerminating...\n\n";
    }
}
debug::~debug() {
    if (wantDebug) {
        std::cout << "Terminated!";
    }
}
