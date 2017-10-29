#include "main.h"

int main() {
    //Alloc mem
    Engine * eng = new Engine();

    //Use mem
    if (!eng->attach()) {
        Debug(ERR, "Unable to attach\n");
        LogLastError();
        system("PAUSE");
        return 0;
    }

    if (!eng->init()) {
        Debug(ERR, "Unable to initialize\n");
        LogLastError();
        system("PAUSE");
        return 0;
    }

    std::thread thread([eng]() {
                   eng->test();
               });

    while (!GetAsyncKeyState(VK_F4)) {
        wait(100);
    }

    thread.join();

    system("PAUSE");

    //Free mem
    delete eng;

    return 0;
}
