#include "MainFrame.h"
#include <wx/wx.h>

MainFrame::MainFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(600, 400))
{
    wxPanel* panel = new wxPanel(this);

    availableModulesList = new wxListBox(panel, wxID_ANY, wxPoint(20, 20), wxSize(200, 250));
    selectedModulesList = new wxListBox(panel, wxID_ANY, wxPoint(360, 20), wxSize(200, 250));

    addModuleButton = new wxButton(panel, wxID_ANY, "Add Module", wxPoint(240, 120));

    LoadModules();

    addModuleButton->Bind(wxEVT_BUTTON, &MainFrame::OnAddModuleClicked, this);
}

void MainFrame::LoadModules()
{
    // Hardcoded na teraz, potem z pliku .dll można wczytać
    moduleNames = {"test.dll", "core.dll", "ram.dll"};

    for (const auto& name : moduleNames) {
        availableModulesList->Append(name);
    }
}

void MainFrame::OnAddModuleClicked(wxCommandEvent& event)
{
    int selected = availableModulesList->GetSelection();
    if (selected == wxNOT_FOUND) {
        wxMessageBox("No module selected.", "Error", wxOK | wxICON_ERROR);
        return;
    }

    wxString module = availableModulesList->GetString(selected);

    selectedModulesList->Append(module);
    availableModulesList->Delete(selected);
}
