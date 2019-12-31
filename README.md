# ModuleBase
This is the base class from which all threaded modules will inherit. It implements functionality generic to all modules with a vector of pipes and scheduling based on function runtime and ideal frequency.
The pure virtual function `ModuleBase::periodicRoutine()` is where children will implement functionality specific to the module. The constructor is left unimplemented due to differences in module structure. 
`Error.h` is a place for modules to define global custom errors that will be used by the error module to provide detailed stacktrace like reporting in the log files.
Guidelines for module writing:
- Since this is an abstract class, `msInterval` and `pipes` will have to be passed in through the constructor and assigned; keep this standard.
- Encapsulate into `periodicRoutine()`, as it the only thing that is called.
- Ensure that you manage your own state; `ModuleBase::init()` does not mean the robot is enabled.
- Provide specific and descriptive errors, although the module name is not required in the error message (the error module extracts a pseudo-stacktrace from pipe metadata)
- Don't modify `ModuleBase`, instead write custom functionality in your own class.

The ordering of your pipe vector matters; it makes things significantly easier during graph construction:
- `YourChildClass::pipes[0]` is used internally by `ModuleBase::init()` to report overrun errors; use this to report your custom errors as well
- Document your code; the graph constructor is responsible for figuring out how to permute pipes so that everything is connected correctly
