#include "z80cpuUiMod.hpp"
#include <ctime> 
#include <sstream>
#include <iomanip>
#include <stdio.h>

using namespace std;

const char* moduleName = "z80 cpu";
const char* moduleDescription = "UI module for displaying z80 cpu state";
const uint16_t moduleMajorVersion = 1;
const uint16_t moduleMinorVersion = 1;
const uint16_t protocolVersion = 1;

UiModulePanel::UiModulePanel(wxControl* parent, void* instance, void** interfaces) :
    wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize), 
    instance((struct Instance*) instance),
    interfaces(interfaces),
    refresherTimer(this) {
        // the refresh code
        Bind(wxEVT_TIMER, &UiModulePanel::OnTimer, this);
        refresherTimer.Start(250);
    }

// timer
void UiModulePanel::OnTimer(wxTimerEvent& event)
{
    wxLongLong now = wxGetLocalTimeMillis();
}

wxPanel* getPanel(wxControl* parent, void* instance, void** interfaces)
{
    return new UiModulePanel(parent, instance, interfaces);
}
