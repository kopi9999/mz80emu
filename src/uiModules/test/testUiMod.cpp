#include "testUiMod.hpp"

UiModuleFrame::UiModuleFrame(void* instance, void** interfaces) :
    wxFrame(nullptr, wxID_ANY, "mz80emu", wxDefaultPosition, wxSize(800, 600)), 
    instance((struct Instance*) instance),
    interfaces(interfaces) {}


class wxFrame* getFrame(void* instance, void** interfaces)
{
    return new UiModuleFrame(instance, interfaces);
}
