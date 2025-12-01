#ifndef MODULE_INTERNAL
#define MODULE_INTERNAL

#ifdef _WIN32
    #include "uiModuleWindows.hpp"
#else
    #include "uiModule.hpp"
#endif

extern const char* moduleName;
extern const char* moduleDescription;
extern const uint16_t moduleMajorVersion;
extern const uint16_t moduleMinorVersion;
extern const uint16_t protocolVersion;
extern const uint16_t interfacesNumber;
extern const char* interfacesDescriptions[];

class wxFrame* getFrame(void* instance, void** interfaces);

#endif
