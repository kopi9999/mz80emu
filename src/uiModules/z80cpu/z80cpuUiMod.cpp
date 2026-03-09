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

        secondColumnRegisterSizer->Add(new wxStaticText(this, wxID_ANY, "Program counter"), 0, wxEXPAND | wxALL, 5);
        wxFlexGridSizer* programCounterGrid = new wxFlexGridSizer(1, 3, 5, 5);
        programCounterGrid->AddGrowableCol(0, 1);
        programCounterGrid->AddGrowableCol(1, 1);
        programCounterGrid->Add(new EditableLabel(this, ((uint8_t*)&this->instance->PC) + 1), 0, wxEXPAND, 0);
        programCounterGrid->Add(new EditableLabel(this, ((uint8_t*)&this->instance->PC)), 0, wxEXPAND, 0);
        programCounterGrid->Add(new wxStaticText(this, wxID_ANY, "PC"));
        secondColumnRegisterSizer->Add(programCounterGrid, 1, wxEXPAND | wxALL, 5);

        secondColumnRegisterSizer->Add(new wxStaticText(this, wxID_ANY, "Status"), 0, wxEXPAND | wxALL, 5);


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