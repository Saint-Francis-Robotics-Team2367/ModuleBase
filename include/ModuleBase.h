// Krishna Mani FRC 2020 : Base class for all robot threaded modules

#ifndef MODULEBASE_H
#define MODULEBASE_H

#include <vector>
#include <thread>
#include <chrono>

#include "GenericPipe.h"

// ModuleBase Errors do not pollute Custom Error Namespace
#define ERR_MSINTERVAL_NOT_SET 1
#define ERR_PERIODICINTERVAL_OVERRUN 2

/**
 * Abstract Class ModuleBase, inherit from this to create a module
 * Note: This class cannot be instantiated directly; this is by design
 * Note: Do not implement a constructor; the only place where doing init stuff is guaranteed to be safe is periodicInit() 
 */

class ModuleBase {
    public:

    std::vector<GenericPipe*> pipes; // Refer to: https://github.com/Saint-Francis-Robotics-Team2367/pipes
    std::vector<uint8_t> constructorArgs; 

    int msInterval; 

    void init(std::vector<GenericPipe*>); // Init is implemented as it is common between modules

    // Pure Virtual Functions; these are two functions that you implement when you subclass this
    virtual void periodicRoutine() = 0;
    virtual void periodicInit() = 0;

};

#endif
