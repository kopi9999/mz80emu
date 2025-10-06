#include "MemoryModule.hpp"
#include <wx/sizer.h>

MainFrame::MainFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600))
{
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* instanceSizer = new wxBoxSizer(wxHORIZONTAL);
    instanceList = new wxListBox(panel, wxID_ANY);
   
    panel->SetSizer(mainSizer);

}

