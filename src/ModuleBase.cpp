#include "ModuleBase.h"

void ModuleBase::init() {
    if(!msInterval) {
        pipes[0]->blockingAcquirePipe();
        pipes[0]->pushQueue(ERR_MSINTERVAL_NOT_SET);
        pipes[0]->releasePipe();
        return;
    }

    while(true) {
        auto nextRun = std::chrono::steady_clock::now() + std::chrono::milliseconds(msInterval);

        periodicRoutine();

        if(std::chrono::steady_clock::now() > nextRun) { // periodicRoutine() has overrun its set interval
            pipes[0]->blockingAcquirePipe();
            pipes[0]->pushQueue(ERR_PERIODICINTERVAL_OVERRUN);
            pipes[0]->releasePipe();
            continue;
        }

        std::this_thread::sleep_until(nextRun);
    }
}