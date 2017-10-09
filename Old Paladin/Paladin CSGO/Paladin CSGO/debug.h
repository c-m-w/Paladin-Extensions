#pragma once
#define DEBUG_H
class debug {
    bool wantDebug;
public:
    // Errors
    // module wrapping
    static void error1() {
        MessageBox(nullptr, "Fatal Error 1: Game Attach\nAre you running the cheat as admin?", "bhopfu1's Multihack", MB_ICONERROR | MB_OK);
    }
    static void error2() {
        MessageBox(nullptr, "Fatal Error 2: Module Wrapping\nAre you running the cheat as admin?", "bhopfu1's Multihack", MB_ICONERROR | MB_OK);
    }
    static void error3() {
        MessageBox(nullptr, "Fatal Error 3: Subscription Time\nDid you renew your subscription?", "bhopfu1's Multihack", MB_ICONERROR | MB_OK);
    }
    // Warnings
    // game instance
    static void warning1() {
        MessageBox(nullptr, "Warning 1: Game Instance -> Not locatable\nDid the game close?", "bhopfu1's Multihack", MB_ICONWARNING | MB_OK);
    }
    // ac scanning
    static void warning2() {
        MessageBox(nullptr, "Warning 2: AC Scanning -> Terminated processes\nWas some anticheat open?", "bhopfu1's Multihack", MB_ICONWARNING | MB_OK);
    }
    // config loading
    static void warning3() {
        MessageBox(nullptr, "Warning 3: Config File -> Using Defaults\nIs there a config file?", "bhopfu1's Multihack", MB_ICONWARNING | MB_OK);
    }
    // config reading
    static void warning4() {
        MessageBox(nullptr, "Warning 4: Config File -> Using Defaults\nIs the config file formatted for this version?", "bhopfu1's Multihack", MB_ICONWARNING | MB_OK);
    }
    // Notices
    // elevation token
    static void notice1() {
        MessageBox(nullptr, "Notice 1: Cheat Instance\nIs the cheat already running?", "bhopfu1's Multihack", MB_ICONINFORMATION | MB_OK);
    }
    // already running cheat
    static void notice2() {
        MessageBox(nullptr, "Notice 2: Elevation Token\nDid you run the cheat as admin?", "bhopfu1's Multihack", MB_ICONINFORMATION | MB_OK);
    }
    explicit debug(bool toDebug);
    void setup() const;
    void notOwner() const;
    void owner() const;
    void done() const;
    void notAcScanning() const;
    void cantKill() const;
    void noAnticheat() const;
    void setPriority() const;
    void configLoad() const;
    void attachRead() const;
    void attachAll() const;
    void attached() const;
    void moduleWrap() const;
    void moduleWrapped() const;
    void memorySetup() const;
    void configRead() const;
    void threading() const;
    void complete() const;
    void active() const;
    void reload() const;
    void reset() const;
    void exitKey() const;
    ~debug();
};
