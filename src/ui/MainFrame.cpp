#include "MainFrame.h"
#include <wx/sizer.h>

MainFrame::MainFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600))
{
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    availableModules = {"mod1.dll", "mod2.dll", "mod3.dll"};

    wxBoxSizer* moduleSizer = new wxBoxSizer(wxHORIZONTAL);
    availableModulesList = new wxListBox(panel, wxID_ANY);
    selectedModulesList = new wxListBox(panel, wxID_ANY);
    wxButton* addModuleButton = new wxButton(panel, wxID_ANY, "Add Module");
    addModuleButton->Bind(wxEVT_BUTTON, &MainFrame::OnAddModule, this);

    moduleSizer->Add(availableModulesList, 1, wxALL | wxEXPAND, 5);
    moduleSizer->Add(addModuleButton, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    moduleSizer->Add(selectedModulesList, 1, wxALL | wxEXPAND, 5);

    wxBoxSizer* instanceSizer = new wxBoxSizer(wxHORIZONTAL);
    instanceList = new wxListBox(panel, wxID_ANY);
    wxButton* addInstanceButton = new wxButton(panel, wxID_ANY, "Add Instance");
    addInstanceButton->Bind(wxEVT_BUTTON, &MainFrame::OnAddInstance, this);
    instanceSizer->Add(instanceList, 1, wxALL | wxEXPAND, 5);
    instanceSizer->Add(addInstanceButton, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    wxBoxSizer* interfaceSizer = new wxBoxSizer(wxHORIZONTAL);
    interfacesList = new wxListBox(panel, wxID_ANY);
    wxButton* createInterfacesButton = new wxButton(panel, wxID_ANY, "Create Interface Array");
    createInterfacesButton->Bind(wxEVT_BUTTON, &MainFrame::OnCreateInterfaceArray, this);
    interfaceSizer->Add(interfacesList, 1, wxALL | wxEXPAND, 5);
    interfaceSizer->Add(createInterfacesButton, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    wxBoxSizer* clockSizer = new wxBoxSizer(wxHORIZONTAL);
    clockPeriodInput = new wxTextCtrl(panel, wxID_ANY);
    clockDepthInput = new wxTextCtrl(panel, wxID_ANY);
    clockSizer->Add(new wxStaticText(panel, wxID_ANY, "Clock Period:"), 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    clockSizer->Add(clockPeriodInput, 1, wxALL | wxEXPAND, 5);
    clockSizer->Add(new wxStaticText(panel, wxID_ANY, "Clock Depth:"), 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    clockSizer->Add(clockDepthInput, 1, wxALL | wxEXPAND, 5);

    strobeUpInstanceList = new wxListBox(panel, wxID_ANY);
    strobeDownInstanceList = new wxListBox(panel, wxID_ANY);

    mainSizer->Add(moduleSizer, 0, wxALL | wxEXPAND, 5);
    mainSizer->Add(instanceSizer, 0, wxALL | wxEXPAND, 5);
    mainSizer->Add(interfaceSizer, 0, wxALL | wxEXPAND, 5);
    mainSizer->Add(clockSizer, 0, wxALL | wxEXPAND, 5);
    mainSizer->Add(new wxStaticText(panel, wxID_ANY, "Strobe Up Instances:"), 0, wxLEFT | wxTOP, 5);
    mainSizer->Add(strobeUpInstanceList, 0, wxALL | wxEXPAND, 5);
    mainSizer->Add(new wxStaticText(panel, wxID_ANY, "Strobe Down Instances:"), 0, wxLEFT | wxTOP, 5);
    mainSizer->Add(strobeDownInstanceList, 0, wxALL | wxEXPAND, 5);

    panel->SetSizer(mainSizer);

    RefreshModules();
}

void MainFrame::OnAddModule(wxCommandEvent& event) {
    int sel = availableModulesList->GetSelection();
    if (sel != wxNOT_FOUND) {
        wxString module = availableModulesList->GetString(sel);
        selectedModules.push_back(module.ToStdString());
        availableModules.erase(availableModules.begin() + sel);
        RefreshModules();
    }
}

void MainFrame::OnAddInstance(wxCommandEvent& event) {
    int sel = selectedModulesList->GetSelection();
    if (sel != wxNOT_FOUND) {
        wxString module = selectedModulesList->GetString(sel);
        std::string instName = "Inst" + std::to_string(instanceNames.size()) + " [" + module.ToStdString() + "]";
        instanceNames.push_back(instName);
        RefreshInstances();
        RefreshStrobeLists();
    }
}

void MainFrame::OnCreateInterfaceArray(wxCommandEvent& event) {
    int sel = instanceList->GetSelection();
    if (sel != wxNOT_FOUND) {
        std::vector<std::string> ifaces;
        for (int i = 0; i < 2; ++i) {
            ifaces.push_back("iface_" + std::to_string(i));
        }
        instanceInterfaces[sel] = ifaces;
        interfacesList->Clear();
        for (const auto& iface : ifaces) {
            interfacesList->AppendString(iface);
        }
    }
}

void MainFrame::RefreshModules() {
    availableModulesList->Clear();
    for (const auto& mod : availableModules) {
        availableModulesList->AppendString(mod);
    }

    selectedModulesList->Clear();
    for (const auto& mod : selectedModules) {
        selectedModulesList->AppendString(mod);
    }
}

void MainFrame::RefreshInstances() {
    instanceList->Clear();
    for (const auto& inst : instanceNames) {
        instanceList->AppendString(inst);
    }
}

void MainFrame::RefreshStrobeLists() {
    strobeUpInstanceList->Clear();
    strobeDownInstanceList->Clear();
    for (const auto& inst : instanceNames) {
        strobeUpInstanceList->AppendString(inst);
        strobeDownInstanceList->AppendString(inst);
    }
}
