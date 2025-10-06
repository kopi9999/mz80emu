#include "MainFrame.hpp"
#include <wx/wx.h>

MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, "mz80emu", wxDefaultPosition, wxSize(800, 600)) {
    wxPanel* panel = new wxPanel(this);
    //RefreshModules();
}