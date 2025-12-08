#include "testUiMod.hpp"
#include <wx/tglbtn.h>

const char* moduleName = "test";
const char* moduleDescription = "UI module for testing emulator module";
const uint16_t moduleMajorVersion = 1;
const uint16_t moduleMinorVersion = 1;
const uint16_t protocolVersion = 1;

UiModulePanel::UiModulePanel(wxControl* parent, void* instance, void** interfaces) :
    wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize), 
    instance((struct Instance*) instance),
    interfaces(interfaces) {
        wxToggleButton *overrideClockPeriodButton = new wxToggleButton(this, wxID_ANY, "button");
    }


wxPanel* getPanel(wxControl* parent, void* instance, void** interfaces)
{
    return new UiModulePanel(parent, instance, interfaces);
}
