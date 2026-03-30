#include "z80cpuUiMod.hpp"
#include <ctime> 
#include <sstream>
#include <iomanip>
#include <stdio.h>
#include <wx/gbsizer.h>

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
        wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
        wxBoxSizer* registerSizer = new wxBoxSizer(wxHORIZONTAL);
        wxBoxSizer* firstColumnRegisterSizer = new wxBoxSizer(wxVERTICAL);
        wxBoxSizer* secondColumnRegisterSizer = new wxBoxSizer(wxVERTICAL);


        firstColumnRegisterSizer->Add(new wxStaticText(this, wxID_ANY, "Main registers"), 0, wxEXPAND | wxALL, 5);
        wxFlexGridSizer* mainRegistersGrid = new wxFlexGridSizer(4, 3, 5, 5);
        mainRegistersGrid->AddGrowableCol(0, 1);
        mainRegistersGrid->AddGrowableCol(1, 1);
        mainRegistersGrid->Add(new EditableLabel(this, &this->instance->A), 0, wxEXPAND, 0);
        mainRegistersGrid->Add(new EditableLabel(this, &this->instance->F), 0, wxEXPAND, 0);
        mainRegistersGrid->Add(new wxStaticText(this, wxID_ANY, "AF"));
        mainRegistersGrid->Add(new EditableLabel(this, &this->instance->B), 0, wxEXPAND, 0);
        mainRegistersGrid->Add(new EditableLabel(this, &this->instance->C), 0, wxEXPAND, 0);
        mainRegistersGrid->Add(new wxStaticText(this, wxID_ANY, "BC"));
        mainRegistersGrid->Add(new EditableLabel(this, &this->instance->D), 0, wxEXPAND, 0);
        mainRegistersGrid->Add(new EditableLabel(this, &this->instance->E), 0, wxEXPAND, 0);
        mainRegistersGrid->Add(new wxStaticText(this, wxID_ANY, "DE"));
        mainRegistersGrid->Add(new EditableLabel(this, &this->instance->H), 0, wxEXPAND, 0);
        mainRegistersGrid->Add(new EditableLabel(this, &this->instance->L), 0, wxEXPAND, 0);
        mainRegistersGrid->Add(new wxStaticText(this, wxID_ANY, "HL"));
        firstColumnRegisterSizer->Add(mainRegistersGrid, 1, wxEXPAND | wxALL, 5);

        firstColumnRegisterSizer->Add(new wxStaticText(this, wxID_ANY, "Index registers"), 0, wxEXPAND | wxALL, 5);
        wxFlexGridSizer* indexRegistersGrid = new wxFlexGridSizer(3, 3, 5, 5);
        indexRegistersGrid->AddGrowableCol(0, 1);
        indexRegistersGrid->AddGrowableCol(1, 1);
        indexRegistersGrid->Add(new EditableLabel(this, ((uint8_t*)&this->instance->IX) + 1), 0, wxEXPAND, 0);
        indexRegistersGrid->Add(new EditableLabel(this, ((uint8_t*)&this->instance->IX)), 0, wxEXPAND, 0);
        indexRegistersGrid->Add(new wxStaticText(this, wxID_ANY, "IX"));
        indexRegistersGrid->Add(new EditableLabel(this, ((uint8_t*)&this->instance->IY) + 1), 0, wxEXPAND, 0);
        indexRegistersGrid->Add(new EditableLabel(this, ((uint8_t*)&this->instance->IY)), 0, wxEXPAND, 0);
        indexRegistersGrid->Add(new wxStaticText(this, wxID_ANY, "IY"));
        indexRegistersGrid->Add(new EditableLabel(this, ((uint8_t*)&this->instance->SP) + 1), 0, wxEXPAND, 0);
        indexRegistersGrid->Add(new EditableLabel(this, ((uint8_t*)&this->instance->SP)), 0, wxEXPAND, 0);
        indexRegistersGrid->Add(new wxStaticText(this, wxID_ANY, "SP"));
        firstColumnRegisterSizer->Add(indexRegistersGrid, 1, wxEXPAND | wxALL, 5);
        
        firstColumnRegisterSizer->Add(new wxStaticText(this, wxID_ANY, "Interfaces"), 0, wxEXPAND | wxALL, 5);
        wxGridBagSizer* firstInterfacesGrid = new wxGridBagSizer(5, 5);
        firstInterfacesGrid->Add(new EditableLabel(this, ((uint8_t*) this->interfaces[0]) + 1), wxGBPosition(0, 0), wxGBSpan(1, 1), wxEXPAND);
        firstInterfacesGrid->Add(new EditableLabel(this, ((uint8_t*) this->interfaces[0])), wxGBPosition(0, 1), wxGBSpan(1, 1), wxEXPAND);
        firstInterfacesGrid->Add(new wxStaticText(this, wxID_ANY, "address bus"), wxGBPosition(0, 2), wxGBSpan(1, 1));
        firstInterfacesGrid->Add(new EditableLabel(this, (uint8_t*) this->interfaces[1]), wxGBPosition(1, 0), wxGBSpan(1, 2), wxEXPAND);
        firstInterfacesGrid->Add(new wxStaticText(this, wxID_ANY, "data bus"), wxGBPosition(1, 2), wxGBSpan(1, 1));
        firstInterfacesGrid->AddGrowableCol(0, 1);
        firstInterfacesGrid->AddGrowableCol(1, 1);
        wxFlexGridSizer* secondInterfacesGrid = new wxFlexGridSizer(2, 7, 5, 5);
        secondInterfacesGrid->AddGrowableCol(0, 1);
        secondInterfacesGrid->AddGrowableCol(1, 1);
        secondInterfacesGrid->AddGrowableCol(2, 1);
        secondInterfacesGrid->AddGrowableCol(3, 1);
        secondInterfacesGrid->AddGrowableCol(4, 1);
        secondInterfacesGrid->AddGrowableCol(5, 1);
        secondInterfacesGrid->AddGrowableCol(6, 1);
        secondInterfacesGrid->Add(new OneBitLabel(this, "m1", (uint8_t*) this->interfaces[2], 0b00000001), 0, wxEXPAND, 0);
        secondInterfacesGrid->Add(new OneBitLabel(this, "mreq", (uint8_t*) this->interfaces[3], 0b00000001), 0, wxEXPAND, 0);
        secondInterfacesGrid->Add(new OneBitLabel(this, "iorq", (uint8_t*) this->interfaces[4], 0b00000001), 0, wxEXPAND, 0);
        secondInterfacesGrid->Add(new OneBitLabel(this, "rd", (uint8_t*) this->interfaces[5], 0b00000001), 0, wxEXPAND, 0);
        secondInterfacesGrid->Add(new OneBitLabel(this, "wr", (uint8_t*) this->interfaces[6], 0b00000001), 0, wxEXPAND, 0);
        secondInterfacesGrid->Add(new OneBitLabel(this, "rfsh", (uint8_t*) this->interfaces[7], 0b00000001), 0, wxEXPAND, 0);
        secondInterfacesGrid->Add(new OneBitLabel(this, "halt", (uint8_t*) this->interfaces[8], 0b00000001), 0, wxEXPAND, 0);
        secondInterfacesGrid->Add(new OneBitLabel(this, "wait", (uint8_t*) this->interfaces[9], 0b00000001), 0, wxEXPAND, 0);
        secondInterfacesGrid->Add(new OneBitLabel(this, "int", (uint8_t*) this->interfaces[10], 0b00000001), 0, wxEXPAND, 0);
        secondInterfacesGrid->Add(new OneBitLabel(this, "nmi", (uint8_t*) this->interfaces[11], 0b00000001), 0, wxEXPAND, 0);
        secondInterfacesGrid->Add(new OneBitLabel(this, "reset", (uint8_t*) this->interfaces[12], 0b00000001), 0, wxEXPAND, 0);
        secondInterfacesGrid->Add(new OneBitLabel(this, "busrq", (uint8_t*) this->interfaces[13], 0b00000001), 0, wxEXPAND, 0);
        secondInterfacesGrid->Add(new OneBitLabel(this, "busack", (uint8_t*) this->interfaces[14], 0b00000001), 0, wxEXPAND, 0);
        firstColumnRegisterSizer->Add(firstInterfacesGrid, 1, wxEXPAND | wxALL, 5);
        firstColumnRegisterSizer->Add(secondInterfacesGrid, 1, wxEXPAND | wxALL, 5);

        secondColumnRegisterSizer->Add(new wxStaticText(this, wxID_ANY, "Alternate (shadow) registers"), 0, wxEXPAND | wxALL, 5);
        wxFlexGridSizer* alternateRegistersGrid = new wxFlexGridSizer(4, 3, 5, 5);
        alternateRegistersGrid->AddGrowableCol(0, 1);
        alternateRegistersGrid->AddGrowableCol(1, 1);
        alternateRegistersGrid->Add(new EditableLabel(this, &this->instance->Aprim), 0, wxEXPAND, 0);
        alternateRegistersGrid->Add(new EditableLabel(this, &this->instance->Fprim), 0, wxEXPAND, 0);
        alternateRegistersGrid->Add(new wxStaticText(this, wxID_ANY, "AF'"));
        alternateRegistersGrid->Add(new EditableLabel(this, &this->instance->Bprim), 0, wxEXPAND, 0);
        alternateRegistersGrid->Add(new EditableLabel(this, &this->instance->Cprim), 0, wxEXPAND, 0);
        alternateRegistersGrid->Add(new wxStaticText(this, wxID_ANY, "BC'"));
        alternateRegistersGrid->Add(new EditableLabel(this, &this->instance->Dprim), 0, wxEXPAND, 0);
        alternateRegistersGrid->Add(new EditableLabel(this, &this->instance->Eprim), 0, wxEXPAND, 0);
        alternateRegistersGrid->Add(new wxStaticText(this, wxID_ANY, "DE'"));
        alternateRegistersGrid->Add(new EditableLabel(this, &this->instance->Hprim), 0, wxEXPAND, 0);
        alternateRegistersGrid->Add(new EditableLabel(this, &this->instance->Lprim), 0, wxEXPAND, 0);
        alternateRegistersGrid->Add(new wxStaticText(this, wxID_ANY, "HL'"));
        secondColumnRegisterSizer->Add(alternateRegistersGrid, 1, wxEXPAND | wxALL, 5);

        secondColumnRegisterSizer->Add(new wxStaticText(this, wxID_ANY, "Other registers"), 0, wxEXPAND | wxALL, 5);
        wxFlexGridSizer* otherRegistersGrid = new wxFlexGridSizer(1, 3, 5, 5);
        otherRegistersGrid->AddGrowableCol(0, 1);
        otherRegistersGrid->AddGrowableCol(1, 1);
        otherRegistersGrid->Add(new EditableLabel(this, &this->instance->I), 0, wxEXPAND, 0);
        otherRegistersGrid->Add(new EditableLabel(this, &this->instance->R), 0, wxEXPAND, 0);
        otherRegistersGrid->Add(new wxStaticText(this, wxID_ANY, "I/R"));
        secondColumnRegisterSizer->Add(otherRegistersGrid, 1, wxEXPAND | wxALL, 5);

        secondColumnRegisterSizer->Add(new wxStaticText(this, wxID_ANY, "Program counter"), 0, wxEXPAND | wxALL, 5);
        wxFlexGridSizer* programCounterGrid = new wxFlexGridSizer(1, 3, 5, 5);
        programCounterGrid->AddGrowableCol(0, 1);
        programCounterGrid->AddGrowableCol(1, 1);
        programCounterGrid->Add(new EditableLabel(this, ((uint8_t*)&this->instance->PC) + 1), 0, wxEXPAND, 0);
        programCounterGrid->Add(new EditableLabel(this, ((uint8_t*)&this->instance->PC)), 0, wxEXPAND, 0);
        programCounterGrid->Add(new wxStaticText(this, wxID_ANY, "PC"));
        secondColumnRegisterSizer->Add(programCounterGrid, 1, wxEXPAND | wxALL, 5);

        secondColumnRegisterSizer->Add(new wxStaticText(this, wxID_ANY, "Status"), 0, wxEXPAND | wxALL, 5);
        wxFlexGridSizer* statusGrid = new wxFlexGridSizer(1, 7, 5, 5);
        statusGrid->AddGrowableCol(0, 1);
        statusGrid->AddGrowableCol(1, 1);
        statusGrid->AddGrowableCol(2, 1);
        statusGrid->AddGrowableCol(3, 1);
        statusGrid->AddGrowableCol(4, 1);
        statusGrid->AddGrowableCol(5, 1);
        statusGrid->Add(new OneBitLabel(this, "S", &this->instance->F, 0b10000000), 0, wxEXPAND, 0);
        statusGrid->Add(new OneBitLabel(this, "Z", &this->instance->F, 0b01000000), 0, wxEXPAND, 0);
        statusGrid->Add(new OneBitLabel(this, "H", &this->instance->F, 0b00010000), 0, wxEXPAND, 0);
        statusGrid->Add(new OneBitLabel(this, "P/V", &this->instance->F, 0b00000100), 0, wxEXPAND, 0);
        statusGrid->Add(new OneBitLabel(this, "N", &this->instance->F, 0b00000010), 0, wxEXPAND, 0);
        statusGrid->Add(new OneBitLabel(this, "C", &this->instance->F, 0b00000001), 0, wxEXPAND, 0);
        statusGrid->Add(new wxStaticText(this, wxID_ANY, "Flags"));
        secondColumnRegisterSizer->Add(statusGrid, 1, wxEXPAND | wxALL, 5);


        registerSizer->Add(firstColumnRegisterSizer, 1, wxEXPAND | wxALL, 5);
        registerSizer->Add(secondColumnRegisterSizer, 1, wxEXPAND | wxALL, 5);
        mainSizer->Add(registerSizer, 0, wxEXPAND, 0);
        this->SetSizer(mainSizer);


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