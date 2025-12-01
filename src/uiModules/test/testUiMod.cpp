#include "testUiMod.hpp"

const char* moduleName = "test";
const char* moduleDescription = "UI module for testing emulator module";
const uint16_t moduleMajorVersion = 1;
const uint16_t moduleMinorVersion = 1;
const uint16_t protocolVersion = 1;

UiModuleFrame::UiModuleFrame(void* instance, void** interfaces) :
    wxFrame(nullptr, wxID_ANY, "mz80emu", wxDefaultPosition, wxSize(800, 600)), 
    instance((struct Instance*) instance),
    interfaces(interfaces) {}


class wxFrame* getFrame(void* instance, void** interfaces)
{
    return new UiModuleFrame(instance, interfaces);
}
