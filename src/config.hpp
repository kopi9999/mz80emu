#ifndef FILE_OPERATIONS
#define FILE_OPERATIONS

#include "main.hpp"

enum CrashCode loadConfig(struct Modules*, struct InstanceInfo*, struct InterfacesInfo*, struct ClockInfo*, struct UiModules*, struct UiInstanceInfo*);
enum CrashCode rawDataToFile(std::vector<std::string>, std::vector<std::string>, struct RawInterfacesInfo, struct RawClockInfo);

#endif
