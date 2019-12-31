#ifndef MODULEBASE_H
#define MODULEBASE_H

#include <vector>
#include <thread>
#include <chrono>

#include "Error.h"
#include "GenericPipe.h"

// Abstract Class ModuleBase, inherit from this to create a module
// Note: This class cannot be instantiated directly; this is by design

class ModuleBase {
    public:
    std::vector<GenericPipe*> pipes; // Refer to: https://github.com/Saint-Francis-Robotics-Team2367/pipes
    int msInterval; // Interval on which to call periodicRoutine() -- Can be set dynamically, but know that the target interval has no bearing on the actual execution time

    virtual void periodicRoutine() = 0; // Pure Virtual Function -- This is the function you have to implement in your child class 
    
    virtual void init() final; // Init is implemented as it is common between modules, it is declared 'final' so that it is not overriden 
};

#endif