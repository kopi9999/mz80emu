#include "MemoryModule.hpp"
#include <wx/sizer.h>

MemoryModule::MemoryModule(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600))
{
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* moduleSizer = new wxBoxSizer(wxHORIZONTAL);
    
    panel->SetSizer(mainSizer);

}
