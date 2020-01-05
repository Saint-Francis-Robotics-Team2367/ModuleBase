// Krishna Mani FRC 2020
// See documentation: https://github.com/Saint-Francis-Robotics-Team2367/ModuleBase

#include "ModuleBase.h"

void ModuleBase::init(std::vector<GenericPipe*> pipes) {
    this->pipes = pipes; // Previously handled by the function ModuleBase::plumber(), it wasn't necessary to have two functions

    periodicInit(); // Run the module's init

    if (!msInterval) { // Make sure that the interval is set after init
        pipes[0]->blockingAcquirePipe();
        pipes[0]->pushQueue(ERR_MSINTERVAL_NOT_SET);
        pipes[0]->releasePipe();
        return;
    }

    while (true) { // Can add some termination flag in the future if necessary
        auto nextRun = std::chrono::steady_clock::now() + std::chrono::milliseconds(msInterval);

        periodicRoutine(); // Run the module's code
        
        // Optimize this
        if (std::chrono::steady_clock::now() > nextRun) { // periodicRoutine() has overrun its set interval
            pipes[0]->blockingAcquirePipe();
            pipes[0]->pushQueue(ERR_PERIODICINTERVAL_OVERRUN);
            pipes[0]->releasePipe();
            continue;
        }

        std::this_thread::sleep_until(nextRun);
    }
}
