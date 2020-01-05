// Krishna Mani FRC 2020

#include "Constructor.h"

/*
constructThreadedRobot() maps (a) => std::thread(a->init()) over a set of ModuleBase subclasses, using compile time polymorphism
Constructor's constructor must create a set of std::function<SubClass*> objects that have been passed correctly created pointers to GenericPipes

The C++ typesystem implements metatypes, but these are not exposed (currently a proposal for inclusion in C++23)
Having access to the metatype would make this code really clean and simple (have a metatype array, where each module is an element)

To make your subclass of ModuleBase able to placed and routed in the graph, initialize the variable std::vector<uint8_t> constructorArgs = {moduleID1, moduleID2, moduleID3, etc.};
The constructor will fail if you say you have a connection to a module, but that module does not say it has a connection to you
*/

bool Constructor::constructThreadedRobot(std::vector<ModuleBase*> modules) {
    std::vector< std::vector<GenericPipe*> > pipes = {{ nullptr }};
		
		// There is certainly a better way to do this
		for (uint8_t i = 0; i < modules.size(); i++) {
			ModuleBase* thisModule = modules[i];
			std::vector<uint8_t> thisArg = thisModule->constructorArgs;

			for (uint8_t j = 0; j < thisArg.size(); j++) {
				if (pipes[i][j] != nullptr) { continue; }

				uint8_t reference = thisArg[j]; // The target module connection
				
				if (reference == i) { return false; }// No self-referential connections
			
				std::vector<uint8_t> targetArg = modules[reference]->constructorArgs;
				
				// For the web to make sense, i must be in targetArg
				uint8_t positionInTarget;

				for (uint8_t k = 0; k < targetArg.size(); k++) {
						if (i == targetArg[k]) { positionInTarget = k; break; }
						if (k == (targetArg.size() - 1)) { return false; }
				}

				pipes[i][j] = pipes[reference][positionInTarget] = new GenericPipe();
			}
		}
    // For each element of the vector<ModuleBase*>, create a new thread for the function ModuleBase::init and pass it the correct pipes

    for (uint8_t i = 0; i < modules.size(); i++) { std::thread(&ModuleBase::init, modules[i], pipes[i]); }
		return true;
}
